#ifndef GWQUADBUILDER_H
#define GWQUADBUILDER_H

#include "gwGeomertyObjectBuilder.h"

namespace GW {
class QuadBuilder : public GeometryObjectBuilder {
public:
    QuadBuilder();
    ~QuadBuilder();
    virtual void buildGeometryObject(const std::string &name,
        const float normalCoords[3], const float ** vertexesCoords,
        Ogre::SceneManager * sm, Ogre::String matName, short x, short y);

protected:


private:


};
}
#endif //GWQUADBUILDER_H
