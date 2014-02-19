#include "../include/gwBasicGeometryObject.h"
#include <android/log.h>

#include <OgreMaterialManager.h>
#include <OgreHardwareBufferManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreMeshManager.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgreHardwareBuffer.h>
#include <OgreSubMesh.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "app", __VA_ARGS__))

namespace GW {

BasicGeometryObject::BasicGeometryObject()
{

}

void BasicGeometryObject::baseConstructor(const std::string &name,
        const float normalCoords[3], const short &vertexNum,
        const uint16_t &numTriangles, const Ogre::Vector3 * vertexesCoords,
        Ogre::SceneManager * sm)
{
    _numVertexes=vertexNum;
    _numTriangles=numTriangles;
    _name=name;
    _entity = NULL;
    _material = NULL;

    setColor(normalCoords[0], normalCoords[1], normalCoords[2]);

    /* create the mesh and a single sub mesh */
    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(name, "General");
    Ogre::SubMesh *subMesh = mesh->createSubMesh();

    /* create the vertex data structure */
    mesh->sharedVertexData = new Ogre::VertexData;
    mesh->sharedVertexData->vertexCount = vertexNum;

    /* declare how the vertices will be represented */
    Ogre::VertexDeclaration *decl = mesh->sharedVertexData->vertexDeclaration;
    size_t offset = 0;

    /* the first three floats of each vertex represent the position */
    decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    /* the second three floats of each vertex represent the colour */
    decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    /* create the vertex buffer */
    Ogre::HardwareVertexBufferSharedPtr vertexBuffer = Ogre::HardwareBufferManager::getSingleton().
        createVertexBuffer(offset, mesh->sharedVertexData->vertexCount,
                Ogre::HardwareBuffer::HBU_STATIC);

    /* lock the buffer so we can get exclusive access to its data */
    float *vertices = static_cast<float *>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

    const unsigned char NUM_PARAMS_INDEXES = 6;
    const unsigned char NUM_POSITION_INDEXES = 3;
    for (unsigned short i = 0; i < vertexNum*NUM_PARAMS_INDEXES; ++i) {
        unsigned char idx = i % NUM_PARAMS_INDEXES;
        if (idx < NUM_POSITION_INDEXES) {  // Set position.
            unsigned char idx2 = (i - idx) / (2*NUM_POSITION_INDEXES);
            vertices[i] = vertexesCoords[idx2][idx];
        }
        else {  // Set color.
            unsigned char idx3 = i % NUM_POSITION_INDEXES;
            vertices[i] = normalCoords[idx3];
        }
    }

    /* unlock the buffer */
    vertexBuffer->unlock();

    /* create the index buffer */
    Ogre::HardwareIndexBufferSharedPtr indexBuffer = Ogre::HardwareBufferManager::getSingleton().
        createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,
                mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC);

    /* lock the buffer so we can get exclusive access to its data */
    uint16_t *indices = static_cast<uint16_t *>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

    /* define our triangle */
    for (unsigned short i = 0; i < vertexNum; i++) {
        indices[i] = i;
    }

    /* unlock the buffer */
    indexBuffer->unlock();

    /* unlock the buffer */
    /* attach the buffers to the mesh */
    mesh->sharedVertexData->vertexBufferBinding->setBinding(0, vertexBuffer);
    subMesh->useSharedVertices = true;
    subMesh->indexData->indexBuffer = indexBuffer;
    subMesh->indexData->indexCount = mesh->sharedVertexData->vertexCount;
    subMesh->indexData->indexStart = 0;

    /* set the bounds of the mesh */
    mesh->_setBounds(Ogre::AxisAlignedBox(-1, -1, -1, 1, 1, 1));
    /* notify the mesh that we're all ready */
    mesh->load();

}

BasicGeometryObject::BasicGeometryObject(const std::string &name, const float normalCoords[3],
        const short &vertexNum, const uint16_t &numTriangles,
        const Ogre::Vector3 * vertexesCoords, Ogre::SceneManager * sm)
{
    baseConstructor(name, normalCoords, vertexNum, numTriangles, vertexesCoords, sm);
}

BasicGeometryObject::BasicGeometryObject(const std::string &name, const float normalCoords[3],
        const short &vertexNum, const uint16_t &numTriangles,
        const Ogre::Vector3 * vertexesCoords, Ogre::SceneManager * sm, Ogre::String matName)
{
    baseConstructor(name, normalCoords, vertexNum, numTriangles, vertexesCoords, sm);
    //Create material
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
            "superMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
            );
    Ogre::Technique* lFirstTechnique = material->getTechnique(0);
    Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0);
    lFirstPass->setDiffuse(0.8f, 0.0f, 0.0f, 1.0f);
    lFirstPass->setAmbient(0.3f, 0.3f, 0.3f);
    lFirstPass->setSpecular(0.0f, 0.0f, 1.0f, 1.0f);
    lFirstPass->setShininess(0.0f);
    lFirstPass->setSelfIllumination(0.1f, 0.1f, 0.1f);

    //[> you can now create an entity/scene node based on your mesh, e.g. <]
    // TODO: make access to scene_manager
    _entity = sm->createEntity("CustomEntity", name, "General");
    _entity->setMaterialName("superMaterial");
    _entity->setCastShadows(false);

    _node = sm->getRootSceneNode()->createChildSceneNode();
    _node->translate(0, 20, -10);
    _node->scale(5., 5., 5.);
    _node->attachObject(_entity);
}

BasicGeometryObject::~BasicGeometryObject()
{

}

void BasicGeometryObject::setColor(const float& red, const float& green,
        const float& blue)
{
    _normalCoords[0] = red;
    _normalCoords[1] = green;
    _normalCoords[2] = blue;
}

void BasicGeometryObject::setColor(const float values[3])
{
    setColor(values[0], values[1], values[2]);
}

void BasicGeometryObject::setNumVertexes(const short &value)
{
    _numVertexes = value;
}

void BasicGeometryObject::setNumTriangles(const short &value)
{
    _numTriangles = value;
}

void BasicGeometryObject::setName(const std::string &value)
{
    _name = value;
}

std::string BasicGeometryObject::getName() const
{
    return _name;
}

Ogre::MeshPtr BasicGeometryObject::getOgreMeshPtr() const
{
    return _mesh;
}

Ogre::SceneNode * BasicGeometryObject::getNode() const
{
    return _node;
}

Ogre::Entity * BasicGeometryObject::getEntity() const
{
    return _entity;
}

}

