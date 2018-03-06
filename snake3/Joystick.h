#pragma once
#include "globalConstants.h"
#include "DebouncedButton.h"
#include "IMovement.h"

/*
The joystick is handling only 4 movements on X and Y axis.
No diagonal handling on the snake game.

The plane of the joystick is divided into 4 areas as follows:
Area I   : Left
Area II  : Up
Area III : Right
Area IV  : Down

If the joystick is on the diagonals the current movement
direction is kept.

^ Y axis
|
|
+---------+
|\   |   /|
| \  II / |
|  \---/  | ======> +move_threshold
|I |\|/|  |
|I | o-|I-| -------> X axis  - Joystick center & origin
|I |/ \|  |
|  /---\  | ======> -move_threshold
| /     \ |
|/   IV  \|
+---------+
*/

class JoystickCtrl : public IMovement {
private:
    DebouncedButton* sw;    /* Button handler                   */
    void(*CB_switch)();     /* Callback when the SW is pressed  */
    
    int pin_X;              /* Arduino pin for X axis           */
    int pin_Y;              /* Arduino pin for Y axis           */
    int pin_SW;             /* Arduino pin for SW button        */
    
    int norm_range;         /* Normalized range from the raw values coming from the ADC      */
    int move_threshold;     /* Read values in [center-move_threshold, center+move_threshold] */
                            /* are ignored and are not treated as movement                   */
    int center;             /* Center position in the normalized range                       */
    
    int readAxis(int axis); /* Helper method to get X/Y axis values from the joystick        */
public:
    JoystickCtrl(const int _x,              // Arduino X axis pin
                 const int _y,              // Arduino Y axis pin
                 const int _sw,             // Arduino SW pin
                 void(*sw_callback)())      // Button pressed callback
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
    
    IMovement::moveDirection getDirection();
};

