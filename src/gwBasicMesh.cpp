#include "../include/gwBasicMesh.h"
namespace GW {

BasicMesh::BasicMesh()
{

}

BasicMesh::~BasicMesh()
{

}

void BasicMesh::setColor(const float& red, const float& green, const float& blue)
{
    color[0] = red;
    color[1] = green;
    color[2] = blue;
}

}
