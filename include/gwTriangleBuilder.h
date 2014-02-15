#ifndef GWTRIANGLEBUILDER_H
#define GWTRIANGLEBUILDER_H

#include "gwGeomertyObjectBuilder.h"

namespace GW {
class TriangleBuilder : public GeometryObjectBuilder {
public:
    TriangleBuilder();
    virtual ~TriangleBuilder();
    virtual void buildGeometryObject(const std::string &name,
        const float colorValues[3], const Ogre::Vector3 * vertexesCoords,
        Ogre::SceneManager * sm);

protected:


private:


};
}
#endif //GWTRIANGLEBUILDER_H
