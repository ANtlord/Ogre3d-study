#include "../include/gwGeomertyObjectBuilder.h"

namespace GW {

GeometryObjectBuilder::GeometryObjectBuilder()
{

}

GeometryObjectBuilder::~GeometryObjectBuilder()
{

}

BasicGeometryObject * GeometryObjectBuilder::getBasicGeometryObject() const
{
    return _basicGeometryObject;
}

}
