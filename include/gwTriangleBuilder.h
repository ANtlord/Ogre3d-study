#ifndef GWTRIANGLEBUILDER_H
#define GWTRIANGLEBUILDER_H

#include "gwGeomertyObjectBuilder.h"

namespace GW {
/*
 *  SAMPLE USAGE:
 *    TriangleBuilder Jamshut;
 *    float colors[3] = {0,0,1};
 *
 *    const float ** coords = new const float*[3];
 *    float *arr;
 *
 *    // This is LEAK. Must be FIXED.
 *    arr = new float[2];
 *    arr[0] = 0; arr[1] = 1;
 *    coords[0] = arr;
 *
 *    arr = new float[2];
 *    arr[0] = -1; arr[1] = -1;
 *    coords[1] = arr;
 *
 *    arr = new float[2];
 *    arr[0] = 1; arr[1] = -1;
 *    coords[2] = arr;
 *
 *    Jamshut.buildGeometryObject("customMesh", colors, coords, _scene_manager,
 *            MAT_NAME, 10, 10);
 *
 */

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
