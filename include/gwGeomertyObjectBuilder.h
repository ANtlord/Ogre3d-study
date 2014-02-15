#ifndef GWGEOMETRYOBJECTBUILDER_H
#define GWGEOMETRYOBJECTBUILDER_H

#include "gwBasicGeometryObject.h"
namespace GW {
/*
 * It is abstract class of different basic GeometryObject builers.
 */
class GeometryObjectBuilder {
public:
    GeometryObjectBuilder();
    virtual ~GeometryObjectBuilder();
    BasicGeometryObject * getBasicGeometryObject() const;
    virtual void buildGeometryObject()=0;

protected:


private:
    BasicGeometryObject * _basicGeometryObject;

};
}
#endif //GWGEOMETRYOBJECTBUILDER_H
