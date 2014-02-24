#include "../include/gwBasicGeometryObject.h"
#include <android/log.h>

#include <OgreManualObject.h>
#include <OgreMaterialManager.h>
#include <OgreHardwareBufferManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreMeshManager.h>
#include <OgreHardwareVertexBuffer.h>
#include <OgreHardwareBuffer.h>
#include <OgreSubMesh.h>

#include <ctime>
#include <cstdlib>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "app", __VA_ARGS__))

namespace GW {

BasicGeometryObject::BasicGeometryObject()
{

}

void BasicGeometryObject::baseConstructor(const std::string &name,
        const float normalCoords[3], const short &vertexNum,
        const uint16_t &numTriangles, const float ** vertexesCoords,
        Ogre::SceneManager * sm)
{
    _numVertexes=vertexNum;
    _numTriangles=numTriangles;
    _name=name;

    // Initializing pointers of properties.
    _node = sm->getRootSceneNode()->createChildSceneNode();
    //_mesh = Ogre::MeshManager::getSingleton().createManual(name, "General");

    ////for (char i = 0; i < 3; i++) {
        ////for (char j = 0; j < 3; j++) {
            ////LOGI("GW_MESH %f", vertexesCoords[i][j]);
        ////}
        
    ////}

    //setNormal(normalCoords[0], normalCoords[1], normalCoords[2]);
    //[> create the mesh and a single sub mesh <]
    //Ogre::SubMesh *subMesh = _mesh->createSubMesh();

    //[> create the vertex data structure <]
    //_mesh->sharedVertexData = new Ogre::VertexData;
    //_mesh->sharedVertexData->vertexCount = _numVertexes;

    //[> declare how the vertices will be represented <]
    //Ogre::VertexDeclaration *decl = _mesh->sharedVertexData->vertexDeclaration;
    //size_t offset = 0;

    //[> the first three floats of each vertex represent the position <]
    //decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
    //offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    //[> the second three floats of each vertex represent the colour <]
    //decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
    //offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    //[> create the vertex buffer <]
    //Ogre::HardwareVertexBufferSharedPtr vertexBuffer = Ogre::HardwareBufferManager::getSingleton().
        //createVertexBuffer(offset, _mesh->sharedVertexData->vertexCount,
                //Ogre::HardwareBuffer::HBU_STATIC);

    //[> lock the buffer so we can get exclusive access to its data <]
    //float *vertices = static_cast<float *>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

    //const unsigned char NUM_PARAMS_INDEXES = 6;
    //const unsigned char NUM_POSITION_INDEXES = 3;
    //for (unsigned short i = 0; i < _numVertexes*NUM_PARAMS_INDEXES; ++i) {
        //unsigned char idx = i % NUM_PARAMS_INDEXES;
        //if (idx < NUM_POSITION_INDEXES) {  // Set position.
            //unsigned char idx2 = (i - idx) / (NUM_PARAMS_INDEXES);
            //LOGI("GW_MESH vertexesCoords[%i][%i] %f", idx2, idx, vertexesCoords[idx2][idx]);
            //vertices[i] = vertexesCoords[idx2][idx];
        //}
        //else {  // Set normal.
            //unsigned char idx3 = i % NUM_POSITION_INDEXES;
            //LOGI("GW_MESH normalCoords[%i]=%f", idx3, normalCoords[idx3]);
            //vertices[i] = normalCoords[idx3];
        //}
    //}

    ////vertices[0] = 0; vertices[1] = 1; vertices[2] = 0; [> position <]
    ////vertices[3] = 0; vertices[4] = 0; vertices[5] = 1; [> colour <]

    ////vertices[6] = -1; vertices[7] = -1; vertices[8] = 0; [> position <]
    ////vertices[9] = 0; vertices[10] = 0; vertices[11] = 1; [> colour <]

    ////vertices[12] = 1; vertices[13] = -1; vertices[14] = 0; [> position <]
    ////vertices[15] = 0; vertices[16] = 0; vertices[17] = 1; [> colour <]

    //[> unlock the buffer <]
    //vertexBuffer->unlock();

    //[> create the index buffer <]
    //Ogre::HardwareIndexBufferSharedPtr indexBuffer = Ogre::HardwareBufferManager::getSingleton().
        //createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,
                //_mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC);

    //[> lock the buffer so we can get exclusive access to its data <]
    //uint16_t *indices = static_cast<uint16_t *>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

    //[> define our triangle <]
    //for (unsigned short i = 0; i < _numVertexes; i++) {
        //indices[i] = i;
    //}

    //[> unlock the buffer <]
    //indexBuffer->unlock();

    //[> unlock the buffer <]
    //[> attach the buffers to the mesh <]
    //_mesh->sharedVertexData->vertexBufferBinding->setBinding(0, vertexBuffer);
    //subMesh->useSharedVertices = true;
    //subMesh->indexData->indexBuffer = indexBuffer;
    //subMesh->indexData->indexCount = _mesh->sharedVertexData->vertexCount;
    //subMesh->indexData->indexStart = 0;

    //[> set the bounds of the mesh <]
    //_mesh->_setBounds(Ogre::AxisAlignedBox(-1, -1, -1, 1, 1, 1));
    //[> notify the mesh that we're all ready <]
    //_mesh->load();

    LOGI("GW_MESH _numVertexes=%i", _numVertexes);
    //LOGI("GW_MESH _mesh->sharedVertexData->vertexCount=%i", _mesh->sharedVertexData->vertexCount);
}

BasicGeometryObject::BasicGeometryObject(const std::string &name, const float normalCoords[3],
        const short &vertexNum, const uint16_t &numTriangles,
        const float ** vertexesCoords, Ogre::SceneManager * sm)
{
    baseConstructor(name, normalCoords, vertexNum, numTriangles, vertexesCoords, sm);
}

BasicGeometryObject::BasicGeometryObject(const std::string &name, const float normalCoords[3],
        const short &vertexNum, const uint16_t &numTriangles,
        const float ** vertexesCoords, Ogre::SceneManager * sm, Ogre::String matName)
{
    baseConstructor(name, normalCoords, vertexNum, numTriangles, vertexesCoords, sm);
    //Create material
    _material = Ogre::MaterialManager::getSingleton().getByName(matName);

    Ogre::ManualObject * man = sm->createManualObject(name);
    man->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    //for (int i = 0; i < _numVertexes; ++i) {
        //man->position(vertexesCoords[i][0], vertexesCoords[i][1], vertexesCoords[i][2]);
        //man->normal(0,0,1);
    //}
    int mapSize = 3;
    for(int z = 0; z < mapSize; ++z) {
       for(int x = 0; x < mapSize; ++x) {
          man->position(z,x,0);
          man->normal(0,0,1);
       }
    }

    for(int z = 0; z < mapSize-1; ++z) {
        for(int x = 0; x < mapSize-1; ++x) {
            int i1 = (x) + (z) * mapSize;
            int i2 = (x) + (z + 1) * mapSize;
            int i3 = (x + 1) + (z + 1) * mapSize;
            int i4 = (x + 1) + (z) * mapSize;
            man->triangle(i1, i2, i3);
            LOGI("GW_MESH i1=%i, i2=%i, i3=%i, i4=%i", i1, i2, i3, i4);
        }
    }
    man->end();
        // Generating name for entity.
    std::stringstream strm;
    strm<<time(0)<<std::rand();
    std::string entityName = ("Vasia"+strm.str());

    //[> you can now create an entity/scene node based on your mesh, e.g. <]
    // TODO: make access to scene_manager
    //_entity = sm->createEntity(entityName, name, "General");
    //_entity->setMaterialName("superMaterial");
    //_entity->setCastShadows(false);

    _node->scale(5., 5., 5.);
    _node->attachObject(man);
}

BasicGeometryObject::~BasicGeometryObject()
{
    delete _node;
    delete _entity;
}

void BasicGeometryObject::setNormal(const float& x, const float& y, const float& z)
{
    _normalCoords[0] = x;
    _normalCoords[1] = y;
    _normalCoords[2] = z;
}

void BasicGeometryObject::setNormal(const float values[3])
{
    setNormal(values[0], values[1], values[2]);
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

Ogre::MaterialPtr BasicGeometryObject::getMaterial() const
{
    return _material;
}

}

