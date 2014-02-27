#include "../include/sampleApp.h"
#include <android/log.h>

#include "gwGameState.h"
#include "gwGameStateManager.h"
#include "../include/gwTriangleBuilder.h"
#include "../include/gwQuadBuilder.h"

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

    //Create a light
    Ogre::Light* l = _scene_manager->createLight("MainLight");
    l->setPosition(0,0,20);
    l->setType(Ogre::Light::LT_POINT);
    l->setDiffuseColour(1.0f, 0.0f, 1.0f);
    l->setSpecularColour(1.0f, 0.0f, 1.0f);

    //Ogre::SceneNode* lLightSceneNode = NULL;
    //lLightSceneNode = _scene_manager->getRootSceneNode()->createChildSceneNode();
    //lLightSceneNode->setPosition(Ogre::Vector3(0,0,0));
    //lLightSceneNode->attachObject(l);

    Ogre::Entity* ogreHead = _scene_manager->createEntity("Head", "ogrehead.mesh");
    Ogre::String matName = ogreHead->getMesh()->getSubMesh(1)->getMaterialName();
    Ogre::SceneNode* headNode = _scene_manager->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);
    headNode->scale(0.25f,0.25f,0.25f);

    TriangleBuilder Jamshut;
    float colors[3] = {0,0,1};

    const float ** coords = new const float*[3];
    float *arr;

    // This is LEAK. Must be FIXED.
    arr = new float[3];
    arr[0] = 0; arr[1] = 1; arr[2] = 0;
    coords[0] = arr;

    arr = new float[3];
    arr[0] = -1; arr[1] = -1; arr[2] = 0;
    coords[1] = arr;

    arr = new float[3];
    arr[0] = 1; arr[1] = -1; arr[2] = 0;
    coords[2] = arr;

    const std::string MAT_NAME = "superMaterial";
    Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(
            MAT_NAME, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
            );
    Ogre::Technique* lFirstTechnique = mat->getTechnique(0);
    Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0);
    lFirstPass->setDiffuse(0.8f, 0.0f, 0.0f, 1.0f);
    lFirstPass->setAmbient(0.3f, 0.3f, 0.3f);
    lFirstPass->setSpecular(0.0f, 0.0f, 1.0f, 1.0f);
    lFirstPass->setShininess(0.0f);
    lFirstPass->setSelfIllumination(0.1f, 0.1f, 0.1f);

 
    Jamshut.buildGeometryObject("customMesh", colors, coords, _scene_manager,
            MAT_NAME, 10, 10);

    const float ** coords2 = new const float*[4];

    arr = new float[3];
    arr[0] = -1; arr[1] = 1; arr[2] = 0;
    coords2[0] = arr;

    arr = new float[3];
    arr[0] = -1; arr[1] = -1; arr[2] = 0;
    coords2[1] = arr;

    arr = new float[3];
    arr[0] = 1; arr[1] = -1; arr[2] = 0;
    coords2[2] = arr;

    arr = new float[3];
    arr[0] = 1; arr[1] = 1; arr[2] = 0;
    coords2[3] = arr;
    QuadBuilder Rafshan;
    Rafshan.buildGeometryObject("customMesh2", colors, coords2, _scene_manager,
            MAT_NAME, -10, 10);
}
