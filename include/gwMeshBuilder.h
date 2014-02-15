#ifndef GWMESHBUILDER_H
#define GWMESHBUILDER_H

#include "gwBasicMesh.h"
namespace GW {
class MeshBuilder {
public:
    MeshBuilder();
    ~MeshBuilder();
    BasicMesh * getBasicMesh() const;

    void createQuad();
    void createTriangle();
    void createCycle();

protected:


private:
    BasicMesh * _basicMesh;

};
}
#endif //GWMESHBUILDER_H
