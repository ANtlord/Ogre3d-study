#include "gwAndroidSys.h"
#include <gainput/gainput.h>


/**
 * This enumerations for indexing types of input from touchscreen.
 */


enum Button
{
    ButtonConfirm,
    ButtonConfirmDouble,
    ButtonConfirmExtra,
    ButtonHoldGesture,
    ButtonTapGesture,
    ButtonPinching,
    ButtonPinchScale,
    ButtonRotating,
    ButtonRotateAngle,
};

// to system level #preinit resources
static Ogre::DataStreamPtr openAPKFile(AAssetManager* asset_manager, const Ogre::String& fileName)
{
  Ogre::DataStreamPtr stream;
  AAsset* asset = AAssetManager_open(asset_manager, fileName.c_str(), AASSET_MODE_BUFFER);
  if (asset){
    off_t length = AAsset_getLength(asset);
    void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
    memcpy(membuf, AAsset_getBuffer(asset), length);
    AAsset_close(asset);

    stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
  }
  return stream;
}


static void ogre_app_init(app_user_data *data){
  //system level #init resources
#ifdef INCLUDE_RTSHADER_SYSTEM
    LOGI("GW RTSS was included");
#endif
  /********************************* Load resources ****************************/

    Ogre::ArchiveManager::getSingleton().addArchiveFactory(
        new Ogre::APKFileSystemArchiveFactory(
            data->android_app_state->activity->assetManager)
    );

    Ogre::ArchiveManager::getSingleton().addArchiveFactory(
          new Ogre::APKZipArchiveFactory(
              data->android_app_state->activity->assetManager)
    );
    Ogre::FileSystemLayer fs_layer(OGRE_VERSION_NAME);
    Ogre::ConfigFile cf;
    cf.load(openAPKFile(data->android_app_state->activity->assetManager,
                          fs_layer.getConfigFilePath("resources.cfg")));

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String sec, type, arch;

    // go through all specified resource groups
    while (seci.hasMoreElements()){
        sec = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;

        // go through all resource paths
        for (i = settings->begin(); i != settings->end(); i++){
            type = i->first;
            arch = i->second;

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
        }
    }

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    /********************************* Create Scene ****************************/
  GW::App::getSingleton()->createScene();
  #ifdef INCLUDE_RTSHADER_SYSTEM
    Ogre::RTShader::ShaderGenerator::initialize();
    // The Shader generator instance
    Ogre::RTShader::ShaderGenerator* gen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    ShaderGeneratorTechniqueResolverListener * material_mgr_listener = new ShaderGeneratorTechniqueResolverListener(gen);
    Ogre::MaterialManager::getSingleton().addListener(material_mgr_listener);
    gen->addSceneManager(GW::App::getSingleton()->getStateManager()->getCurrState()->getScene());
#endif
}


static int app_setup_display(app_user_data* data){
  // to system level
  LOGI("GW Setup display");

  AConfiguration *config = AConfiguration_new();
  AConfiguration_fromAssetManager(config, data->android_app_state->activity->assetManager);

  if (data->window == NULL){
    Ogre::NameValuePairList opt;
    opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)data->android_app_state->window);
    opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

    data->window = Ogre::Root::getSingleton().createRenderWindow("OgreWindow", 0, 0, false, &opt);
    GW::App::getSingleton()->setupDisplay(data->window);
    ogre_app_init(data);
  } else {
    static_cast<Ogre::AndroidEGLWindow*>(data->window)->_createInternalResources(
      data->android_app_state->window, config
      );
  }

  AConfiguration_delete(config);

  return 0;
}

static void app_term_display(app_user_data* data){
  // to system level
  LOGI("Terminate display");
  static_cast<Ogre::AndroidEGLWindow*>(data->window)->_destroyInternalResources();
}

static void app_draw_frame(app_user_data* data){
  // to system level #add here a add level (scene)
  if(data->window != NULL && data->window->isActive()){
//    LOGI("GW Render frame");
    // data->window->windowMovedOrResized();
    GW::App::getSingleton()->render();
//      data->root->renderOneFrame();
  }
}


static void app_init(app_user_data* data){
    // to system level #add here an app init
    LOGI("GW App init");
    if(data->init == true)
        return;
    data->root = new Ogre::Root();
//    GW::getApp();
//    GW::App::getSingleton()->appInit(data->root);
    getApp()->appInit(data->root);
    // data->root = new Ogre::Root::getSingleton();1

#ifdef OGRE_STATIC_LIB
    data->plugin_loader = new Ogre::StaticPluginLoader();
    data->plugin_loader->load();
#endif
    data->root->setRenderSystem(data->root->getAvailableRenderers().at(0));
    data->root->initialise(false);
    data->init = true;
}

static void app_shutdown(app_user_data* data)
{
  // to system level #add here an app shutdown
  LOGI("GW App shutdown");
  app_term_display(data);

  if (data->init == false){
    return;
  }

  data->init = false;

  delete data->root;
  data->root = NULL;
  data->window = NULL;

#ifdef OGRE_STATIC_LIB
  data->plugin_loader->unload();
  delete data->plugin_loader;
  data->plugin_loader = NULL;
#endif
}

/**
 * Process the next input event.
 */
static int32_t app_handle_input(android_app* app, AInputEvent *event)
{
    app_user_data* inputManager = (app_user_data*)app->userData;
    static bool resSet = false;
    if (!resSet)
    {
        inputManager->SetDisplaySize(ANativeWindow_getWidth(app->window),
                ANativeWindow_getHeight(app->window));
        resSet = true;
    }
    return inputManager->HandleInput(event);
}

/**
 * Process the next main command.
 */
static void app_handle_cmd(android_app *app, int32_t cmd){
  app_user_data* data = (app_user_data *) app->userData;
  switch (cmd){
  case APP_CMD_SAVE_STATE:
    LOGI("GW Save state command");
    // The system has asked us to save our current state.  Do so.
    app->savedState = malloc(sizeof(saved_state));
    *((saved_state*)app->savedState) = data->state;
    app->savedStateSize = sizeof(saved_state);
    break;

  case APP_CMD_INIT_WINDOW:
    LOGI("GW Init window command");
    // The window is being shown, get it ready.
    if (app->window != NULL && data->init == true){
      app_setup_display(data);
      app_draw_frame(data);
    } break;

  case APP_CMD_TERM_WINDOW:
    LOGI("GW Term window command");
    if(data->init == true && data->window != NULL){
      // The window is being hidden or closed, clean it up.
      app_term_display(data);
    } break;

  case APP_CMD_GAINED_FOCUS:
    data->animating = true;
    break;

  case APP_CMD_LOST_FOCUS:
    data->animating = false;
    break;

  default:
    LOGI("GW Other command");
    break;
  }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(android_app* state)
{
    LOGI("GW Starting app");
    // Make sure glue isn't stripped.
    app_dummy();
    app_user_data data;

    // Setup device and map for preparing gestures.
    gainput::InputDeviceTouch* touchDevice = data.CreateAndGetDevice<gainput::InputDeviceTouch>();
    GAINPUT_ASSERT(touchDevice);
    gainput::DeviceId touchId = touchDevice->GetDeviceId();
    gainput::InputMap map(data, "testmap");

    // Setup gestures.

    // Just tap.
    gainput::TapGesture* tg = data.CreateAndGetDevice<gainput::TapGesture>();
    GAINPUT_ASSERT(tg);
    tg->Initialize(touchId, gainput::Touch0Down, 500);
    map.MapBool(ButtonTapGesture, tg->GetDeviceId(), gainput::TapTriggered);

    // Pinch.
    gainput::PinchGesture* pg = data.CreateAndGetDevice<gainput::PinchGesture>();
    GAINPUT_ASSERT(pg);
    pg->Initialize(touchId, gainput::Touch0Down,
            touchId, gainput::Touch0X,
            touchId, gainput::Touch0Y,
            touchId, gainput::Touch1Down,
            touchId, gainput::Touch1X,
            touchId, gainput::Touch1Y);
    map.MapBool(ButtonPinching, pg->GetDeviceId(), gainput::PinchTriggered);
    map.MapFloat(ButtonPinchScale, pg->GetDeviceId(), gainput::PinchScale);
    
    // Holding.
    gainput::HoldGesture* hg = data.CreateAndGetDevice<gainput::HoldGesture>();
    GAINPUT_ASSERT(hg);
    hg->Initialize(touchId, gainput::Touch0Down,
            touchId, gainput::Touch0X, 0.1f,
            touchId, gainput::Touch0Y, 0.1f,
            true,
            800);
    map.MapBool(ButtonHoldGesture, hg->GetDeviceId(), gainput::HoldTriggered);

    // Rotation gesture.
    gainput::RotateGesture* rg = data.CreateAndGetDevice<gainput::RotateGesture>();
    GAINPUT_ASSERT(rg);
    rg->Initialize(touchId, gainput::Touch0Down,
            touchId, gainput::Touch0X,
            touchId, gainput::Touch0Y,
            touchId, gainput::Touch1Down,
            touchId, gainput::Touch1X,
            touchId, gainput::Touch1Y);
    map.MapBool(ButtonRotating, rg->GetDeviceId(), gainput::RotateTriggered);
    map.MapFloat(ButtonRotateAngle, rg->GetDeviceId(), gainput::RotateAngle);
    // Finish setup gestures.

    data.root = NULL;
    data.window = NULL; data.android_app_state = state;
    data.init = false;
    data.animating = false;
    app_init(&data);

    state->userData = &data;
    state->onAppCmd = app_handle_cmd;
    state->onInputEvent = app_handle_input;

    if (state->savedState != NULL){
        // We are starting with a previous saved state; restore from it.
        data.state = *(saved_state*)state->savedState;
    }

    // loop waiting for stuff to do.
    while (1) {
        // Read all pending events.
        int ident;
        int events;
        data.Update();
        android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.

        // Handling input events.
        bool isPinch = map.GetBool(ButtonPinching);
        bool isRotate = map.GetBool(ButtonRotating);
        bool isTap = map.GetBoolWasDown(ButtonTapGesture);
        bool isHold = map.GetBool(ButtonHoldGesture);
        if (isPinch || isRotate || isTap || isHold) {
            GW::Control * control = GW::App::getSingleton()->getStateManager()->getCurrState()->getController();
            if (isPinch == true) {
                float delta = map.GetFloat(ButtonPinchScale);
                if (delta != 1.) {   // Calculated by rate.
                    LOGI("GW_INPUT PINCH %f", delta);
                    GW::PinchEvent e(delta);
                    (control != NULL) ? control->pinchDown(e) : LOGI("GW_INPUT TAP: control is null");
                }
            }
            if (isRotate == true) {
                float angle = map.GetFloat(ButtonRotateAngle);
                if ( angle > 0. ) {   // Calculated by radians and every time is positive.
                    LOGI("GW_INPUT ROTATION %f", angle);
                    GW::RotateEvent e(angle);
                    (control != NULL) ?  control->rotateDown(e) : LOGI("GW_INPUT TAP: control is null");
                }
            }

            if (isTap == true) {
                float x = AMotionEvent_getX(data.getEvent(), 0);
                float y = AMotionEvent_getY(data.getEvent(), 0);
                GW::TapEvent e(x, y);
                (control != NULL) ?  control->tapReleased(e) : LOGI("GW_INPUT TAP: control is null");

                LOGI("GW_INPUT TAP: %f;", x);
                LOGI("GW_INPUT TAP: %f;", y);
            }

            if (isHold == true) {
                GW::App::getSingleton()->getStateManager()->getCurrState()->getController()->tapHolded();
            }
        }
        while ((ident = ALooper_pollAll(data.animating ? 0 : -1, NULL, &events, (void**)&source)) >= 0){
            // Process this event.
            if (source != NULL){
                source->process(state, source);
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                app_shutdown(&data);
                return;
            }
        }

        if (data.animating == true) {
            app_draw_frame(&data);
        }
    }
}
