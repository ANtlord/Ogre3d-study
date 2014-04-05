#ifndef		__GW_APP_H__
#define		__GW_APP_H__

#include "OgrePlatform.h"
#include "ShaderGeneratorTechniqueResolverListener.h"
#include <OgreConfigFile.h>
#include "OgreMaterialManager.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include <map>
#include "gwGameStateManager.h"
#include <android_native_app_glue.h>

namespace GW{

#define GW_IMPLEMENT_APP(appname) \
appname* getApp() { return static_cast<appname*>(appname::getSingleton()); }

#define GW_DECLARE_APP(appname) \
    extern appname* getApp()

class App{
public:
    virtual void appInit(Ogre::Root *root);
    virtual void appClose();
    virtual void createScene();
    virtual void setupDisplay(Ogre::RenderWindow *window);
    virtual void render();
    inline static App*	getSingleton(){
        if (_self) return reinterpret_cast<App*>(_self);
        else {
            _self = new char[sizeof(App)];
            new (_self) App();
            return reinterpret_cast<App*>(_self);
        }
    }
    inline StateManager* getStateManager( ){
        return &_states;
    }
    static AAssetManager * aassetMgr;
protected:
    App();
//    Ogre::SceneManager* _scene_manager;
    static void*_self;
	Ogre::Root *_root;
	Ogre::RenderWindow *_window;
    StateManager _states;
};

//GW_IMPLEMENT_APP(App);
}

#endif		//__GW_APP_H__
