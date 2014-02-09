#ifndef			__GW_ANDROID_SYS_H__
#define			__GW_ANDROID_SYS_H__


#include <gainput/gainput.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <EGL/egl.h>


#include "OgreFileSystemLayer.h"
#define _OgreSampleExport
#define _OgreSampleClassExport

#ifdef OGRE_STATIC_LIB
#  ifdef OGRE_BUILD_RENDERSYSTEM_GLES2
#    undef OGRE_STATIC_GLES
#    define INCLUDE_RTSHADER_SYSTEM
#    define OGRE_STATIC_GLES2
#  endif //OGRE_BUILD_RENDERSYSTEM_GLES2

#  define OGRE_STATIC_OctreeSceneManager
#endif //OGRE_STATIC_LIB

#define OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
#define RTSHADER_SYSTEM_BUILD_CORE_SHADERS
#define RTSHADER_SYSTEM_BUILD_EXT_SHADERS

#ifdef INCLUDE_RTSHADER_SYSTEM
#  include "ShaderSystem.h"
#endif

#include <OgreShaderGenerator.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "app", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "app", __VA_ARGS__))

#include "OgreStaticPluginLoader.h"
#include <jni.h>
#include <OgreSphere.h>
#include <errno.h>

#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#include "Android/OgreAndroidEGLWindow.h"

#ifdef INCLUDE_RTSHADER_SYSTEM
#   include "OgreRTShaderSystem.h"
#endif

#include "gwApp.h"
/**
 * Our saved state data.
 */
struct saved_state{
};

/**
 * Shared state for our app.
 */
class app_user_data : public gainput::InputManager
{
    public:
        android_app *android_app_state;

        bool init;
        bool animating;

        Ogre::RenderWindow *window;
        Ogre::Root *root;

        saved_state state;

        int32_t HandleInput(AInputEvent *event);
        AInputEvent * getEvent();

#ifdef OGRE_STATIC_LIB
        Ogre::StaticPluginLoader *plugin_loader;
#endif
    private:
        static AInputEvent * _event;
};

AInputEvent * app_user_data::_event = NULL;

int32_t app_user_data::HandleInput(AInputEvent *event)
{
    app_user_data::_event = event;
    return gainput::InputManager::HandleInput(event);
}

AInputEvent * app_user_data::getEvent()
{
    return app_user_data::_event;
}

#endif 			//__GW_ANDROID_SYS_H__
