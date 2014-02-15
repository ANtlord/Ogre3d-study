#ifndef GWTRIANGLEMESHBUILDER_H
#define GWTRIANGLEMESHBUILDER_H
namespace GW {
class TriangleMeshBuilder {
public:
    TriangleMeshBuilder();
    ~TriangleMeshBuilder();

    void createQuad();
    void createTriangle();
    void createCycle();

protected:


private:


};
}
#endif //GWTRIANGLEMESHBUILDER_H
