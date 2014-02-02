#ifndef			__GW_ANDROID_SYS_H__
#define			__GW_ANDROID_SYS_H__


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

//#ifdef OGRE_STATIC_LIB
// #   ifdef OGRE_BUILD_PLUGIN_BSP
// #       include "BSP.h"
// #   endif
#ifdef INCLUDE_RTSHADER_SYSTEM
#  include "ShaderSystem.h"
#endif
//#endif

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
GW::gwApp	userapp;
/**
 * Our saved state data.
 */
struct saved_state{
};

/**
 * Shared state for our app.
 */
struct app_user_data{
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


#endif 			//__GW_ANDROID_SYS_H__