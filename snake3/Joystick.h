#pragma once
#include "globalConstants.h"
#include "DebouncedButton.h"
#include "IMovement.h"

class JoystickCtrl : public IMovement {
private:
    DebouncedButton* sw;

    int pin_X;
    int pin_Y;
    int pin_SW;
    void(*CB_switch)();
    int readAxis(int axis);

    int norm_range;
    int move_threshold;
    int center;
public:
    JoystickCtrl(const int _x, const int _y, const int _sw, void(*sw_callback)())
    {
        pin_X  = _x;
        pin_Y  = _y;
        pin_SW = _sw;
        CB_switch = sw_callback;

        sw = new DebouncedButton(pin_SW, CB_switch, DEBOUNCING_DELAY);

        norm_range = 12;
        center = norm_range / 2;
        move_threshold = 3;
    };
    ~JoystickCtrl() { delete sw; sw = nullptr; };

    void checkSwitch() { sw->checkButton(); }
    moveDirection getDirection();
};

