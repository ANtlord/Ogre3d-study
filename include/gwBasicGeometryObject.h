#ifndef GWBASICGEOMETRYOBJECT_H
#define GWBASICGEOMETRYOBJECT_H
#include <iostream>
#include <OgreMesh.h>
#include <OgreVector3.h>
#include <OgreNode.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>

namespace GW {

class BasicGeometryObject {
public:
    BasicGeometryObject();
    BasicGeometryObject(const std::string &name, const float colorValues[3], const short &vertexNum,
        const uint16_t &numTriangles, const Ogre::Vector3 * vertexesCoords, Ogre::SceneManager * sm);
    virtual ~BasicGeometryObject();

    void setColor(const float& red, const float& green, const float& blue);
    void setColor(const float values[3]);
    void setNumVertexes(const short &value);
    void setNumTriangles(const short &value);
    void setName(const std::string &value);

    std::string getName() const;
    Ogre::MeshPtr getOgreMeshPtr() const;
    Ogre::SceneNode * getNode() const;
    Ogre::Entity * getEntity() const;

protected:


private:
    unsigned short _numVertexes;
    unsigned short _numTriangles;
    unsigned _color[3];
    std::string _name;
    Ogre::MeshPtr _mesh;
    Ogre::SceneNode * _node;
    Ogre::Entity * _entity;

};

}
#endif //GWBASICGEOMETRYOBJECT_H
