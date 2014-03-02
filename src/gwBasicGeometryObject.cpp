#include "../include/gwBasicGeometryObject.h"
#include "../include/gwTriangulate.h"

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
#include <vector>

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "app", __VA_ARGS__))

using namespace std;

namespace GW {

BasicGeometryObject::BasicGeometryObject()
{

}

void BasicGeometryObject::baseConstructor(const std::string &name,
        const float normalCoords[3], const short &vertexNum,
        const float * vertexesCoords, Ogre::SceneManager * sm)
{
    _numVertexes=vertexNum;
    _numTriangles=0;
    _name=name;
    _node = sm->getRootSceneNode()->createChildSceneNode();
    setNormal(normalCoords);
}

BasicGeometryObject::BasicGeometryObject(const std::string &name, const float normalCoords[3],
            const short &vertexNum, const float ** vertexesCoords,
            Ogre::SceneManager * sm, Ogre::String matName)
{
    // Convert 2 dimensional array to one dimensional.
    _vertexCoords = new float[vertexNum*2];
    _material = Ogre::MaterialManager::getSingleton().getByName(matName);
    for (int i = 0; i < vertexNum; i++) {
        _vertexCoords[0+2*i] = vertexesCoords[i][0];
        _vertexCoords[1+2*i] = vertexesCoords[i][1];
    }
    baseConstructor(name, normalCoords, vertexNum, _vertexCoords, sm);

    LOGI("GW_MESH 1");

    Ogre::ManualObject * man = sm->createManualObject(name);
    man->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
    for (int i = 0; i < 2*_numVertexes; i+=2) {
        man->position(_vertexCoords[i], _vertexCoords[i+1], 0);
        man->normal(_normalCoords[0], _normalCoords[1], _normalCoords[2]);
    }

    LOGI("GW_MESH 2");
    int triangleNum = 0;
    vector <int*> indices = points_delaunay_naive_2d(vertexNum,
            _vertexCoords, &triangleNum);
    _numTriangles = triangleNum;

    for (int i = 0; i < indices.size(); i++) {
        man->triangle(indices[i][0], indices[i][1], indices[i][2]);
    }

    LOGI("GW_MESH 3");
    man->end();

    LOGI("GW_MESH 4");
    // Generating name for entity.
    std::stringstream strm;
    strm<<time(0)<<std::rand();
    std::string entityName = ("Vasia"+strm.str());

    _node->scale(5., 5., 5.);
    _node->attachObject(man);
    LOGI("GW_MESH 5");
}

BasicGeometryObject::~BasicGeometryObject()
{
    delete _node;
    delete _entity;
    delete _vertexCoords;
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

int BasicGeometryObject::getNumTriangles() const
{
    return _numTriangles;
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

