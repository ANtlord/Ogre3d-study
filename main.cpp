#include "SampleContext.h"
#include "SamplePlugin.h"
#include "SdkTrays.h"

#include <jni.h>
#include <errno.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <EGL/egl.h>

#include <OgreConfigFile.h>
#include "OgreRoot.h"
#include "OgrePlatform.h"
#include "OgreFileSystemLayer.h"

#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#include "Android/OgreAndroidEGLWindow.h"


#ifdef OGRE_STATIC_LIB

#define OGRE_STATIC_GLES2
#define OGRE_STATIC_OctreeSceneManager

#include "OgreStaticPluginLoader.h"

#endif

#define OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
#define RTSHADER_SYSTEM_BUILD_CORE_SHADERS
#define RTSHADER_SYSTEM_BUILD_EXT_SHADERS

#ifdef INCLUDE_RTSHADER_SYSTEM
#   include "OgreRTShaderSystem.h"
#endif
#ifdef OGRE_STATIC_LIB
#   ifdef OGRE_BUILD_PLUGIN_BSP
#       include "BSP.h"
#   endif
#   ifdef INCLUDE_RTSHADER_SYSTEM
#      include "ShaderSystem.h"
#   endif
#   ifdef INCLUDE_RTSHADER_SYSTEM
#      include "OgreRTShaderSystem.h"
#   endif
#endif



#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "app", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "app", __VA_ARGS__))

/**
 * Our saved state data.
 */
struct saved_state
{
};

/**
 * Shared state for our app.
 */
struct app_user_data
{
  android_app *android_app_state;

  bool init;
  bool animating;

  Ogre::RenderWindow *window;
  Ogre::Root *root;

  saved_state state;

#ifdef OGRE_STATIC_LIB
  Ogre::StaticPluginLoader *plugin_loader;
#endif
};




static Ogre::DataStreamPtr openAPKFile(AAssetManager* asset_manager, const Ogre::String& fileName)
{
  Ogre::DataStreamPtr stream;
  AAsset* asset = AAssetManager_open(asset_manager, fileName.c_str(), AASSET_MODE_BUFFER);
  if (asset)
  {
    off_t length = AAsset_getLength(asset);
    void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
    memcpy(membuf, AAsset_getBuffer(asset), length);
    AAsset_close(asset);

    stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
  }
  return stream;
}


static void ogre_app_init(app_user_data *data)
{

#ifdef USE_RTSHADER_SYSTEM
  // Setup shaders
  Ogre::RTShader::ShaderGenerator::initialize();

  // The Shader generator instance
  Ogre::RTShader::ShaderGenerator* gen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

  // Create and register the material manager listener if it doesn't exist yet.
  if(material_mgr_listener_ == NULL) {
     material_mgr_listener_ = new ShaderGeneratorTechniqueResolverListener(gen);
     Ogre::MaterialManager::getSingleton().addListener(material_mgr_listener_);
  }

  gen->addSceneManager(scene_mgr_);
#endif
  LOGI("Init ogre app");

  /********************************* Misc ****************************/

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

  // Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();

  // // Clear event times
  // Ogre::Root::getSingleton().clearEventTimes();


  /********************************* Load resources ****************************/

  Ogre::ArchiveManager::getSingleton().addArchiveFactory(
    new Ogre::APKFileSystemArchiveFactory(data->android_app_state->activity->assetManager)
    );

  Ogre::ArchiveManager::getSingleton().addArchiveFactory(
    new Ogre::APKZipArchiveFactory(data->android_app_state->activity->assetManager)
    );
  Ogre::FileSystemLayer fs_layer(OGRE_VERSION_NAME);
  Ogre::ConfigFile cf;
  cf.load(openAPKFile(data->android_app_state->activity->assetManager,
                      fs_layer.getConfigFilePath("resources.cfg")));

  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  Ogre::String sec, type, arch;

  // go through all specified resource groups
  while (seci.hasMoreElements())
  {
    sec = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;

    // go through all resource paths
    for (i = settings->begin(); i != settings->end(); i++)
    {
      type = i->first;
      arch = i->second;

      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
    }
  }

  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  /********************************* Create Scene ****************************/

  // Create the SceneManager, in this case a generic one
  Ogre::SceneManager *scene_manager = Ogre::Root::getSingleton().createSceneManager("DefaultSceneManager");

  // Create the camera
  Ogre::Camera *camera = scene_manager->createCamera("PlayerCam");

  // Look back along -Z
  camera->setPosition(Ogre::Vector3(0,0,100));
  camera->lookAt(Ogre::Vector3(0,0,-300));
  camera->setNearClipDistance(5);
  camera->setFarClipDistance(5000);

  // Create one viewport, entire window
  Ogre::Viewport* vp = data->window->addViewport(camera);
  vp->setBackgroundColour(Ogre::ColourValue(0.5,0,0));

  // Alter the camera aspect ratio to match the viewport
  camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

  Ogre::Entity* ogreHead = scene_manager->createEntity("Head", "ogrehead.mesh");

  Ogre::SceneNode* headNode = scene_manager->getRootSceneNode()->createChildSceneNode();
  headNode->attachObject(ogreHead);

  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

  Ogre::MeshManager::getSingleton().createPlane("ground",
                                                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                plane, 1500, 1500, 20, 20, true,
                                                1, 5, 5, Ogre::Vector3::UNIT_Z);

  Ogre::Entity* entGround = scene_manager->createEntity("GroundEntity", "ground");
  scene_manager->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

  entGround->setMaterialName("Examples/Rocky");
  entGround->setCastShadows(false);

  // Set ambient light
  scene_manager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

  // Create a light
  Ogre::Light* l = scene_manager->createLight("MainLight");
  l->setPosition(20,80,50);
}


static int app_setup_display(app_user_data* data)
{
  LOGI("Setup display");

  AConfiguration *config = AConfiguration_new();
  AConfiguration_fromAssetManager(config, data->android_app_state->activity->assetManager);

  if (data->window == NULL)
  {
    Ogre::NameValuePairList opt;
    opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)data->android_app_state->window);
    opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

    data->window = Ogre::Root::getSingleton().createRenderWindow("OgreWindow", 0, 0, false, &opt);
    ogre_app_init(data);
  }
  else
  {
    static_cast<Ogre::AndroidEGLWindow*>(data->window)->_createInternalResources(
      data->android_app_state->window, config
      );
  }

  AConfiguration_delete(config);

  return 0;
}

static void app_term_display(app_user_data* data)
{
  LOGI("Terminate display");
  static_cast<Ogre::AndroidEGLWindow*>(data->window)->_destroyInternalResources();
}

static void app_draw_frame(app_user_data* data)
{
  if(data->window != NULL && data->window->isActive())
  {
    // LOGI("Render frame");
    // data->window->windowMovedOrResized();
    data->root->renderOneFrame();
  }
}


static void app_init(app_user_data* data)
{
  LOGI("App init");
  if(data->init == true)
    return;

  data->root = new Ogre::Root();

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
  LOGI("App shutdown");
  app_term_display(data);

  if (data->init == false)
  {
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
static int32_t app_handle_input(android_app */*app*/, AInputEvent *event)
{
  LOGI("Input received");
  if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
  {
    return 1;
  }
  return 0;
}

/**
 * Process the next main command.
 */
static void app_handle_cmd(android_app *app, int32_t cmd)
{
  app_user_data* data = (app_user_data *) app->userData;
  switch (cmd)
  {
  case APP_CMD_SAVE_STATE:
    LOGI("Save state command");
    // The system has asked us to save our current state.  Do so.
    app->savedState = malloc(sizeof(saved_state));
    *((saved_state*)app->savedState) = data->state;
    app->savedStateSize = sizeof(saved_state);
    break;

  case APP_CMD_INIT_WINDOW:
    LOGI("Init window command");
    // The window is being shown, get it ready.
    if (app->window != NULL && data->init == true)
    {
      app_setup_display(data);
      app_draw_frame(data);
    }
    break;

  case APP_CMD_TERM_WINDOW:
    LOGI("Term window command");
    if(data->init == true && data->window != NULL)
    {
      // The window is being hidden or closed, clean it up.
      app_term_display(data);
    }
    break;

  case APP_CMD_GAINED_FOCUS:
    data->animating = true;
    break;

  case APP_CMD_LOST_FOCUS:
    data->animating = false;
    break;

  default:
    LOGI("Other command");
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
  LOGI("Starting app");
  app_user_data data;

  // Make sure glue isn't stripped.
  app_dummy();

  memset(&data, 0, sizeof(data));
  data.android_app_state = state;
  data.init = false;
  data.animating = false;
  app_init(&data);

  state->userData = &data;
  state->onAppCmd = app_handle_cmd;
  state->onInputEvent = app_handle_input;

  if (state->savedState != NULL)
  {
    // We are starting with a previous saved state; restore from it.
    data.state = *(saved_state*)state->savedState;
  }

  // loop waiting for stuff to do.
  while (1)
  {
    // Read all pending events.
    int ident;
    int events;
    android_poll_source* source;

    // LOGI("Polling events");
    // If not animating, we will block forever waiting for events.
    // If animating, we loop until all events are read, then continue
    // to draw the next frame of animation.
    while ((ident = ALooper_pollAll(data.animating ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
    {
      // Process this event.
      if (source != NULL)
      {
        source->process(state, source);
      }

      // Check if we are exiting.
      if (state->destroyRequested != 0)
      {
        app_shutdown(&data);
        return;
      }
    }

    // LOGI("Drawing frame");
    if (data.animating == true)
    {
      app_draw_frame(&data);
    }
  }
}
