#include "../include/sampleApp.h"
#include <android/log.h>

#include "gwGameState.h"
#include "gwGameStateManager.h"
#include "../include/gwTriangleBuilder.h"

#include "OgreEntity.h"
#include <OgreCamera.h>
#include <OgreMaterialManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreMeshManager.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgreHardwareBuffer.h>
#include <OgreMesh.h>
#include <OgreSubMesh.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "app", __VA_ARGS__))
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

        TriangleBuilder Jamshut;
        float colors[3] = {1,0,0};
        Ogre::Vector3 coords[3];
        Jamshut.buildGeometryObject("customMesh", colors, coords, _scene_manager);

        //Create a light
        Ogre::Light* l = _scene_manager->createLight("MainLight");
        l->setPosition(20,80,50);
    }
