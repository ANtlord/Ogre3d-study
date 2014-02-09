#ifndef GW_TAP_EVENT_H
#define GW_TAP_EVENT_H
namespace GW {
class TapEvent {
public:
    TapEvent(const float &x, const float &y);
    ~TapEvent();


protected:
    float getX() const;
    float getY() const;


private:
    float _x;
    float _y;


};
}

#endif //GW_TAP_EVENT_H
