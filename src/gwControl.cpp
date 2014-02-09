#include "gwControl.h"

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "app", __VA_ARGS__))
namespace GW{

// InputListener.
void Control::tapReleased(const TapEvent &e)
{
    LOGI("FUCK");
}

void Control::tapHolded()
{

}

void Control::pinchDown(const PinchEvent &e)
{

}

void Control::rotateDown(const RotateEvent &e)
{

}

// end InputListener.
}
