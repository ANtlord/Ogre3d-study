#include "../include/sampleApp.h"
#include <android/log.h>
#include "gwGameState.h"
#include "gwGameStateManager.h"
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

        ///-------------------------
        /* create the mesh and a single sub mesh */
        Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("CustomMesh", "General");
        Ogre::SubMesh *subMesh = mesh->createSubMesh();
        LOGI("GW_MESH 1");
        /* create the vertex data structure */
        mesh->sharedVertexData = new Ogre::VertexData;
        mesh->sharedVertexData->vertexCount = 3;

        /* declare how the vertices will be represented */
        Ogre::VertexDeclaration *decl = mesh->sharedVertexData->vertexDeclaration;
        size_t offset = 0;

        LOGI("GW_MESH 2");
        /* the first three floats of each vertex represent the position */
        decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
        offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

        /* the second three floats of each vertex represent the colour */
        decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
        offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

        LOGI("GW_MESH 3");
        /* create the vertex buffer */
        Ogre::HardwareVertexBufferSharedPtr vertexBuffer = Ogre::HardwareBufferManager::getSingleton().
            createVertexBuffer(offset, mesh->sharedVertexData->vertexCount,
                    Ogre::HardwareBuffer::HBU_STATIC);

        /* lock the buffer so we can get exclusive access to its data */
        float *vertices = static_cast<float *>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

        /* populate the buffer with some data */
        vertices[0] = 0; vertices[1] = 1; vertices[2] = 0; /* position */
        vertices[3] = 1; vertices[4] = 0; vertices[5] = 0; /* colour */

        vertices[6] = -1; vertices[7] = -1; vertices[8] = 0; /* position */
        vertices[9] = 0; vertices[10] = 1; vertices[11] = 0; /* colour */

        vertices[12] = 1; vertices[13] = -1; vertices[14] = 0; /* position */
        vertices[15] = 0; vertices[16] = 0; vertices[17] = 1; /* colour */

        /* unlock the buffer */
        vertexBuffer->unlock();

        LOGI("GW_MESH 4");
        /* create the index buffer */
        Ogre::HardwareIndexBufferSharedPtr indexBuffer = Ogre::HardwareBufferManager::getSingleton().
            createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,
                    mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC);

        /* lock the buffer so we can get exclusive access to its data */
        uint16_t *indices = static_cast<uint16_t *>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

        /* define our triangle */
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;

        LOGI("GW_MESH 5");
        /* unlock the buffer */
        indexBuffer->unlock();

        LOGI("GW_MESH 6");
        /* unlock the buffer */
        /* attach the buffers to the mesh */
        mesh->sharedVertexData->vertexBufferBinding->setBinding(0, vertexBuffer);
        subMesh->useSharedVertices = true;
        subMesh->indexData->indexBuffer = indexBuffer;
        subMesh->indexData->indexCount = mesh->sharedVertexData->vertexCount;
        subMesh->indexData->indexStart = 0;

        LOGI("GW_MESH 7");
        /* set the bounds of the mesh */
        mesh->_setBounds(Ogre::AxisAlignedBox(-1, -1, -1, 1, 1, 1));

        /* notify the mesh that we're all ready */
        mesh->load();

        LOGI("GW_MESH 8");
        //Create material
        
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
                "superMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
                );
        material->setAmbient(Ogre::Real(1), Ogre::Real(0), Ogre::Real(0));

        /* you can now create an entity/scene node based on your mesh, e.g. */
        LOGI("GW_MESH 9");
        Ogre::Entity *entity = _scene_manager->createEntity("CustomEntity", "CustomMesh", "General");
        entity->setMaterialName("superMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        Ogre::SceneNode *node = _scene_manager->getRootSceneNode()->createChildSceneNode();
        node->translate(0,0, -100);
        node->scale(50., 50., 50.);
        node->attachObject(entity);
        ///-------------------------

        //Create a light
        Ogre::Light* l = _scene_manager->createLight("MainLight");
        l->setPosition(20,80,50);
    }
