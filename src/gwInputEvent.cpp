#include "../include/gwInputEvent.h"
namespace GW {

InputEvent::InputEvent(const float &delta)
{
    _delta = delta;
}
InputEvent::~InputEvent()
{

}

float InputEvent::getDelta() const
{
    return _delta;
}


}
