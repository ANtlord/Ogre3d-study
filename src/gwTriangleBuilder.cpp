#include "../include/gwTriangleBuilder.h"
namespace GW {

TriangleBuilder::TriangleBuilder() : GeometryObjectBuilder()
{

}

TriangleBuilder::~TriangleBuilder()
{

}

void TriangleBuilder::buildGeometryObject(const std::string &name,
        const float normalCoords[3], const float ** vertexesCoords,
        Ogre::SceneManager * sm, Ogre::String matName, short x, short y)
{
    _basicGeometryObject = new BasicGeometryObject(name, normalCoords, 3,
            vertexesCoords, sm, matName);
    _basicGeometryObject->getNode()->translate(x,y,0);
}

}
