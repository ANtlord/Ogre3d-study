#ifndef 	__GW_PINCH_EVENT_H__
#define		__GW_PINCH_EVENT_H__
#include "gwInputEvent.h"
namespace GW {
class PinchEvent : public InputEvent {
public:
    PinchEvent(const float &delta);
};
}
#endif //__GW_PINCH_EVENT_H__
