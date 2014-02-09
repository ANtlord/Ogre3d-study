#ifndef GW_INPUT_LISTENER_H
#define GW_INPUT_LISTENER_H
#include <vector>
#include "gwTapEvent.h"
#include "gwPinchEvent.h"
#include "gwRotateEvent.h"
namespace GW {

class InputListener
{
public:
    virtual void tapReleased(const TapEvent &e) = 0;
    virtual void tapHolded() = 0;
    virtual void pinchDown(const PinchEvent &e) = 0;
    virtual void rotateDown(const RotateEvent &e) = 0;

protected:


private:

};

}
#endif //GW_INPUT_LISTENER_H
