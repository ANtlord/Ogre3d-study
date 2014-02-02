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
private:
	Ogre::Root *_root;
	Ogre::RenderWindow *_window;
};

}

#endif		//__GW_APP_H__