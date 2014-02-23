#ifndef GWTRIANGLEBUILDER_H
#define GWTRIANGLEBUILDER_H

#include "gwGeomertyObjectBuilder.h"

namespace GW {
class TriangleBuilder : public GeometryObjectBuilder {
public:
    TriangleBuilder();
    virtual ~TriangleBuilder();
    virtual void buildGeometryObject(const std::string &name,
        const float normalCoords[3], const float ** vertexesCoords,
        Ogre::SceneManager * sm, Ogre::String matName, short x, short y);

protected:


private:


};
}
#endif //GWTRIANGLEBUILDER_H
