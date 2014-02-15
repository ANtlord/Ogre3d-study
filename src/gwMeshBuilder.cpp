#include "../include/gwMeshBuilder.h"

namespace GW {


MeshBuilder::MeshBuilder()
{

}

MeshBuilder::~MeshBuilder()
{

}

BasicMesh * MeshBuilder::getBasicMesh() const
{
    return this->_basicMesh;
}

void MeshBuilder::createQuad()
{

}

void MeshBuilder::createTriangle()
{
    /* create the mesh and a single sub mesh */
    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("CustomMesh", "General");
    Ogre::SubMesh *subMesh = mesh->createSubMesh();

    /* create the vertex data structure */
    mesh->sharedVertexData = new Ogre::VertexData;
    mesh->sharedVertexData->vertexCount = 3;

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
    vertices[0] = 0; vertices[1] = 1; vertices[2] = 0; /* position */
    vertices[3] = 1; vertices[4] = 0; vertices[5] = 0; /* colour */

    vertices[6] = -1; vertices[7] = -1; vertices[8] = 0; /* position */
    vertices[9] = 0; vertices[10] = 1; vertices[11] = 0; /* colour */

    vertices[12] = 1; vertices[13] = -1; vertices[14] = 0; /* position */
    vertices[15] = 0; vertices[16] = 0; vertices[17] = 1; /* colour */

    /* unlock the buffer */
    vertexBuffer->unlock();
    
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

    /* you can now create an entity/scene node based on your mesh, e.g. */
    Ogre::Entity *entity = _scene_manager->createEntity("CustomEntity", "CustomMesh", "General");
    entity->setMaterialName("superMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::SceneNode *node = _scene_manager->getRootSceneNode()->createChildSceneNode();
    node->translate(0,0, -100);
    node->scale(50., 50., 50.);
    node->attachObject(entity);
}

void MeshBuilder::createCycle()
{

}

}
