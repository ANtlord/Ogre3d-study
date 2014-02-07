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

namespace GW{
class App{
public:
    void appInit(Ogre::Root *root);
    void appClose();
    void createScene();
    void setupDisplay(Ogre::RenderWindow *window);
    void render();
    inline static App*	getSingleton(){
        return ( _self ) ? _self : _self = new App;
	}
//	inline Ogre::SceneManager* getSceneManager( ){
//        return _scene_manager;
//	}
private:
    App();
//    Ogre::SceneManager* _scene_manager;
    static App*	_self;
	Ogre::Root *_root;
	Ogre::RenderWindow *_window;
    StateManager _states;
};

}

#endif		//__GW_APP_H__
