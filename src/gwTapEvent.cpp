#include "../include/gwTapEvent.h"
using namespace GW;
TapEvent::TapEvent(const float &x, const float &y)
{
    _x = x;
    _y = y;
}

TapEvent::~TapEvent()
{

}

float TapEvent::getX() const
{
    return _x;
}

float TapEvent::getY() const
{
    return _y;
}
