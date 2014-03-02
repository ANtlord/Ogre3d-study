#ifndef GWBASICGEOMETRYOBJECT_H
#define GWBASICGEOMETRYOBJECT_H
#include <iostream>
#include <OgreMesh.h>
#include <OgreVector3.h>
#include <OgreNode.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>

namespace GW {
/*
 * SAMPLE USAGE:
 * const float ** coords3 = new const float*[5];
 * float *arr;
 * 
 * arr = new float[2];
 * arr[0] = 0; arr[1] = -1;
 * coords3[0] = arr;
 * 
 * arr = new float[2];
 * arr[0] = 0.5; arr[1] = 0.5;
 * coords3[1] = arr;
 * 
 * arr = new float[2];
 * arr[0] = -0.5; arr[1] = 1;
 * coords3[2] = arr;
 * 
 * arr = new float[2];
 * arr[0] = -1.0; arr[1] = 0.5;
 * coords3[3] = arr;
 * 
 * arr = new float[2];
 * arr[0] = -1; arr[1] = -0.5;
 * coords3[4] = arr;
 * 
 * BasicGeometryObject * basicGeometryObject = new BasicGeometryObject("qwe", colors, 5,
 *         coords3, _scene_manager, MAT_NAME);
 * basicGeometryObject->getNode()->translate(-10,10,0);
 *
 */
class BasicGeometryObject {
public:
    BasicGeometryObject();

    //BasicGeometryObject(const std::string &name, const float normalCoords[3], const short &vertexNum,
        //const uint16_t &numTriangles, const float ** vertexesCoords, Ogre::SceneManager * sm);

    BasicGeometryObject(const std::string &name, const float normalCoords[3],
            const short &vertexNum, const float ** vertexesCoords,
            Ogre::SceneManager * sm, Ogre::String matName);


    virtual ~BasicGeometryObject();

    void setNormal(const float& x, const float& y, const float& z);
    void setNormal(const float values[3]);
    void setNumVertexes(const short &value);
    void setName(const std::string &value);

    std::string getName() const;
    Ogre::MeshPtr getOgreMeshPtr() const;
    Ogre::SceneNode * getNode() const;
    Ogre::Entity * getEntity() const;
    Ogre::MaterialPtr getMaterial() const;
    int getNumTriangles() const;

protected:


private:
    void baseConstructor(const std::string &name, const float normalCoords[3],
            const short &vertexNum, const float * vertexesCoords,
            Ogre::SceneManager * sm);
    unsigned short _numVertexes;
    unsigned short _numTriangles;
    float _normalCoords[3];
    std::string _name;
    Ogre::MeshPtr _mesh;
    Ogre::SceneNode * _node;
    Ogre::Entity * _entity;
    Ogre::MaterialPtr _material;
    float * _vertexCoords;
};

}
#endif //GWBASICGEOMETRYOBJECT_H
