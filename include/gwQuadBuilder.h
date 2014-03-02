#ifndef GWQUADBUILDER_H
#define GWQUADBUILDER_H

#include "gwGeomertyObjectBuilder.h"

namespace GW {
/*
 *  SAMPLE USAGE:
 *    const float ** coords2 = new const float*[4];
 *    float *arr;
 *
 *    arr = new float[2];
 *    arr[0] = -1; arr[1] = 1;
 *    coords2[0] = arr;
 *
 *    arr = new float[2];
 *    arr[0] = -1; arr[1] = -1;
 *    coords2[1] = arr;
 *
 *    arr = new float[2];
 *    arr[0] = 1; arr[1] = -1;
 *    coords2[2] = arr;
 *
 *    arr = new float[2];
 *    arr[0] = 1; arr[1] = 1;
 *    coords2[3] = arr;
 *    QuadBuilder Rafshan;
 *    Rafshan.buildGeometryObject("customMesh2", colors, coords2, _scene_manager,
 *            MAT_NAME, 0, -10);
 *
 */
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
