#ifndef GWBASICMESH_H
#define GWBASICMESH_H
namespace GW {

class BasicMesh {
public:
    BasicMesh();
    ~BasicMesh();

    void setColor(const float& red, const float& green, const float& blue);

protected:


private:
    unsigned short numTriangles;
    unsigned char color[3];

};

}
#endif //GWBASICMESH_H
