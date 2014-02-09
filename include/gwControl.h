#ifndef		_GW_CONTROL_H__
#define		_GW_CONTROL_H__
#include "gwInputListener.h"
namespace GW{
class Control : public InputListener {
public:
    // InputListener.
    virtual void tapReleased(const TapEvent &e);
    virtual void tapHolded();
    virtual void pinchDown();
    virtual void rotateDown();

private:

};
}


#endif		//_GW_CONTROL_H__
