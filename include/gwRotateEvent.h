#ifndef 	__GW_ROTATE_EVENT_H__
#define		__GW_ROTATE_EVENT_H__
#include "gwInputEvent.h"
namespace GW {
class RotateEvent : public InputEvent 
{
public:
    RotateEvent(const float &delta);
};
}
#endif //__GW_ROTATE_EVENT_H__
