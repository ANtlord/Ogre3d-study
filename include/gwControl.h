#ifndef		_GW_CONTROL_H__
#define		_GW_CONTROL_H__
#include "gwInputListener.h"
namespace GW{
class Control : public InputListener {
public:
    // InputListener.
    virtual void tapReleased(const TapEvent &e);
    virtual void tapHolded();
    virtual void pinchDown(const PinchEvent &e);
    virtual void rotateDown(const RotateEvent &e);

private:

};
}


#endif		//_GW_CONTROL_H__ {}
