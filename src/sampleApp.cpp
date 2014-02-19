#include "sampleApp.h"
#include "gwGameState.h"
#include "gwGameStateManager.h"
#include "OgreEntity.h"
#include <OgreCamera.h>

GW_IMPLEMENT_APP(sampleApp);

using namespace GW;

void sampleApp::createScene(){
        GameState* state = _states.createState("second");
        Ogre::SceneManager* _scene_manager = state->getScene();
        Ogre::Camera *camera = _scene_manager->createCamera(MainCameraName);
        _states.changeState("second",_window);

        // Look back along -Z
        camera->setPosition(Ogre::Vector3(0,0,100));
        camera->lookAt(Ogre::Vector3(0,0,-100));
        camera->setNearClipDistance(5);
        camera->setFarClipDistance(5000);

        Ogre::Entity* ogreHead = _scene_manager->createEntity("Head", "ogrehead.mesh");
        Ogre::SceneNode* headNode = _scene_manager->getRootSceneNode()->createChildSceneNode();
        headNode->attachObject(ogreHead);
        headNode->scale(0.25f,0.25f,0.25f);

        //Create a light
        Ogre::Light* l = _scene_manager->createLight("MainLight");
        l->setPosition(20,80,50);
    }