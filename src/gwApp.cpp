#include "gwApp.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
namespace GW{
App*   App::_self = NULL;
App::App(){

}
void App::appInit 		(Ogre::Root *root){
	_root = root;
}
void App::appClose		(){

}
void App::createScene	(){
    _scene_manager = Ogre::Root::getSingleton().createSceneManager("DefaultSceneManager");

    // Create the camera
    Ogre::Camera *camera = _scene_manager->createCamera("PlayerCam");

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
//    _scene_manager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
    //add a ogrehead to scene

    Ogre::Entity* ogreHead = _scene_manager->createEntity("Head", "ogrehead.mesh");
    Ogre::SceneNode* headNode = _scene_manager->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);
    
    //Create a light
    Ogre::Light* l = _scene_manager->createLight("MainLight");
    l->setPosition(20,80,50);
}
void App::setupDisplay(Ogre::RenderWindow *window){
	_window = window;
}
void App::render(){
    _root->renderOneFrame();
}
}
