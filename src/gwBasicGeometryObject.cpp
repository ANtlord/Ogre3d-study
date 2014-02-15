#include "../include/gwBasicGeometryObject.h"

#include <OgreMaterialManager.h>
#include <OgreHardwareBufferManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreMeshManager.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgreHardwareBuffer.h>
#include <OgreSubMesh.h>


namespace GW {

BasicGeometryObject::BasicGeometryObject()
{

}

BasicGeometryObject::BasicGeometryObject(const std::string &name, const float colorValues[3],
        const short &vertexNum, const uint16_t &numTriangles,
        const Ogre::Vector3 * vertexesCoords, Ogre::SceneManager * sm) :
    _numVertexes(vertexNum),
    _numTriangles(numTriangles),
    _name(name)
{
    setColor(colorValues[0], colorValues[1], colorValues[2]);

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

    /* populate the buffer with some data */
    const unsigned char NUM_PARAMS_INDEXES = 6;
    const unsigned char NUM_POSITION_INDEXES = 3;
    for (unsigned short i = 0; i < vertexNum*NUM_PARAMS_INDEXES; ++i) {
        unsigned char idx = i % NUM_PARAMS_INDEXES;
        if (idx < NUM_POSITION_INDEXES) {  // Set position.
            unsigned char idx2 = (i - (idx)) / NUM_POSITION_INDEXES;
            vertices[i] = vertexesCoords[idx2][idx];
        }
        else {  // Set color.
            vertices[i] = colorValues[1];
        }
    }

    //vertices[0] = 0; vertices[1] = 1; vertices[2] = 0; [> position <]
    //vertices[3] = 1; vertices[4] = 0; vertices[5] = 0; [> colour <]

    //vertices[6] = -1; vertices[7] = -1; vertices[8] = 0; [> position <]
    //vertices[9] = 0; vertices[10] = 1; vertices[11] = 0; [> colour <]

    //vertices[12] = 1; vertices[13] = -1; vertices[14] = 0; [> position <]
    //vertices[15] = 0; vertices[16] = 0; vertices[17] = 1; [> colour <]

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

    //Create material
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
            "superMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
            );
    material->setAmbient(Ogre::Real(1), Ogre::Real(0), Ogre::Real(0));

    //[> you can now create an entity/scene node based on your mesh, e.g. <]
    //// TODO: make access to scene_manager
    Ogre::Entity *entity = sm->createEntity("CustomEntity", "CustomMesh", "General");
    _entity = entity;
    entity->setMaterialName("superMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::SceneNode *node = sm->getRootSceneNode()->createChildSceneNode();
    _node = node;
    //node->translate(0,0, -100);
    //node->scale(50., 50., 50.);
    node->attachObject(entity);
}

BasicGeometryObject::~BasicGeometryObject()
{

}

void BasicGeometryObject::setColor(const float& red, const float& green, const float& blue)
{
    _color[0] = red;
    _color[1] = green;
    _color[2] = blue;
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

