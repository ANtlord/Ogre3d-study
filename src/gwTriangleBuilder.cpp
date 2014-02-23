#include "../include/gwTriangleBuilder.h"
namespace GW {

TriangleBuilder::TriangleBuilder() : GeometryObjectBuilder()
{

}

TriangleBuilder::~TriangleBuilder()
{

}

void TriangleBuilder::buildGeometryObject(const std::string &name,
        const float normalCoords[3], const Ogre::Vector3 * vertexesCoords,
        Ogre::SceneManager * sm, Ogre::String matName, uint16_t x, uint16_t y)
{
    _basicGeometryObject = new BasicGeometryObject(name, normalCoords, 3, 3,
            vertexesCoords, sm, matName);
    _basicGeometryObject->getNode()->translate(x,y,0);
}

}
