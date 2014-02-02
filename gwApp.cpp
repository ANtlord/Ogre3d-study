#include "gwApp.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
namespace GW{
void	gwApp::appInit 		(Ogre::Root *root){
	_root = root;
}
void	gwApp::appClose		(){

}
void 	gwApp::createScene	(){
	Ogre::SceneManager *scene_manager = Ogre::Root::getSingleton().createSceneManager("DefaultSceneManager");

#ifdef INCLUDE_RTSHADER_SYSTEM
    Ogre::RTShader::ShaderGenerator::initialize();
    // The Shader generator instance
    Ogre::RTShader::ShaderGenerator* gen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    ShaderGeneratorTechniqueResolverListener * material_mgr_listener = new ShaderGeneratorTechniqueResolverListener(gen);
    Ogre::MaterialManager::getSingleton().addListener(material_mgr_listener);
    gen->addSceneManager(scene_manager);
#endif
    // app level - init scene


    // Create the camera
    Ogre::Camera *camera = scene_manager->createCamera("PlayerCam");

    // Look back along -Z
    camera->setPosition(Ogre::Vector3(0,0,100));
    camera->lookAt(Ogre::Vector3(0,0,-100));
    camera->setNearClipDistance(5);
    camera->setFarClipDistance(5000);

    // Create one viewport, entire window
    Ogre::Viewport* vp = _window->addViewport(camera);
    vp->setBackgroundColour(Ogre::ColourValue(0.9,0.5,0.5));
    // Alter the camera aspect ratio to match the viewport
    camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    //Set ambient light
    scene_manager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    //add a ogrehead to scene

	Ogre::Entity* ogreHead = scene_manager->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* headNode = scene_manager->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);
    
    //Create a light
    Ogre::Light* l = scene_manager->createLight("MainLight");
    l->setPosition(20,80,50);
}
void 	gwApp::setupDisplay(Ogre::RenderWindow *window){
	_window = window;
}
}