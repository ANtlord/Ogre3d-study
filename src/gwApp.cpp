#include "gwApp.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
namespace GW{

AAssetManager * App::aassetMgr = NULL;
void*   App::_self = NULL;
App::App(){

}
void App::appInit 		(Ogre::Root *root){
	_root = root;
}
void App::appClose		(){

}
void App::createScene	(){
    GameState* state = _states.createState("first");
    Ogre::SceneManager* _scene_manager = state->getScene();
    Ogre::Camera *camera = _scene_manager->createCamera(MainCameraName);
    _states.changeState("first",_window);
    //
    // Look back along -Z
    camera->setPosition(Ogre::Vector3(0,0,100));
    camera->lookAt(Ogre::Vector3(0,0,-100));
    camera->setNearClipDistance(5);
    camera->setFarClipDistance(5000);

//    Ogre::Entity* ogreHead = _scene_manager->createEntity("Head", "ogrehead.mesh");
//    Ogre::SceneNode* headNode = _scene_manager->getRootSceneNode()->createChildSceneNode();
//	headNode->attachObject(ogreHead);

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
