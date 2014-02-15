#include "../include/gwGeomertyObjectBuilder.h"

namespace GW {

GeometryObjectBuilder::GeometryObjectBuilder() : _basicGeometryObject(NULL)
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
