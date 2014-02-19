#include "../include/gwTriangleBuilder.h"
namespace GW {

TriangleBuilder::TriangleBuilder() : GeometryObjectBuilder()
{

}

TriangleBuilder::~TriangleBuilder()
{

}

void TriangleBuilder::buildGeometryObject(const std::string &name,
        const float colorValues[3], const Ogre::Vector3 * vertexesCoords,
        Ogre::SceneManager * sm, Ogre::String matName)
{
    _basicGeometryObject = new BasicGeometryObject(name, colorValues, 3, 3,
            vertexesCoords, sm, matName);
}

}
