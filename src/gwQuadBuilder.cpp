#include "../include/gwQuadBuilder.h"

namespace GW {

QuadBuilder::QuadBuilder() : GeometryObjectBuilder()
{

}

QuadBuilder::~QuadBuilder()
{

}

void QuadBuilder::buildGeometryObject(const std::string &name,
        const float normalCoords[3], const float ** vertexesCoords,
        Ogre::SceneManager * sm, Ogre::String matName, short x, short y)
{
    _basicGeometryObject = new BasicGeometryObject(name, normalCoords, 4, 2,
            vertexesCoords, sm, matName);
    _basicGeometryObject->getNode()->translate(x,y,0);
}

}
