#include "gwApp.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
namespace GW{
gwApp*   gwApp::_self = NULL;
gwApp::gwApp(){

}
void	gwApp::appInit 		(Ogre::Root *root){
	_root = root;
}
void	gwApp::appClose		(){

}
void 	gwApp::createScene	(){
	scene_manager = Ogre::Root::getSingleton().createSceneManager("DefaultSceneManager");

    // Create the camera
    Ogre::Camera *camera = scene_manager->createCamera("PlayerCam");

    // Look back along -Z
    camera->setPosition(Ogre::Vector3(0,0,100));
    camera->lookAt(Ogre::Vector3(0,0,-100));
    camera->setNearClipDistance(5);
    camera->setFarClipDistance(5000);

    // Create one viewport, entire window
    Ogre::Viewport* vp = _window->addViewport(camera);
    vp->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5));
    // Alter the camera aspect ratio to match the viewport
    camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    //Set ambient light
    scene_manager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
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
