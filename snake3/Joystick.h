#pragma once
#include "globalConstants.h"
#include "movement.h"
#include "DebouncedButton.h"

class Joystick {
private:
    DebouncedButton* sw;

    int pin_X;
    int pin_Y;
    int pin_SW;
    void(*CB_switch)();

public:
    Joystick(const int _x, const int _y, const int _sw, void(*sw_callback)())
    {
        pin_X  = _x;
        pin_Y  = _y;
        pin_SW = _sw;
        CB_switch = sw_callback;

        sw = new DebouncedButton(pin_SW, CB_switch, DEBOUNCING_DELAY);
    };
    ~Joystick() { };

    void checkSwitch() { sw->checkButton(); }
    moveDirection getDirection();
};

