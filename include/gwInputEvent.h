#ifndef 	__GW_INPUT_EVENT_H__
#define		__GW_INPUT_EVENT_H__
namespace GW {
class InputEvent {
public:
    InputEvent(const float &delta);
    ~InputEvent();
    
    float getDelta() const;

protected:


private:
    float _delta;


};
}
#endif //__GW_INPUT_EVENT_H__
