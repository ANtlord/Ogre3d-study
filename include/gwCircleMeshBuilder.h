#ifndef GWCIRCLEMESHBUILDER_H
#define GWCIRCLEMESHBUILDER_H
namespace GW {
class CircleMeshBuilder {
public:
    CircleMeshBuilder();
    ~CircleMeshBuilder();

    void createQuad();
    void createTriangle();
    void createCycle();

protected:


private:


};
}
#endif //GWCIRCLEMESHBUILDER_H
