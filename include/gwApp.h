#ifndef		__GW_APP_H__
#define		__GW_APP_H__

#include "OgrePlatform.h"
#include "ShaderGeneratorTechniqueResolverListener.h"
#include <OgreConfigFile.h>
#include "OgreMaterialManager.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
namespace GW{
class gwApp{
public:
	void	appInit(Ogre::Root *root);
	void	appClose();
	void 	createScene();
	void 	setupDisplay(Ogre::RenderWindow *window);
	inline static gwApp*	getSingleton(){
		return ( _self ) ? _self : _self = new gwApp();
	}
	inline Ogre::SceneManager* getSceneManager(){
		return scene_manager;
	}
private:
	gwApp();
	Ogre::SceneManager *scene_manager;
	static gwApp*	_self;
	Ogre::Root *_root;
	Ogre::RenderWindow *_window;
};

}

#endif		//__GW_APP_H__
