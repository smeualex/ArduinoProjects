////////////////////////////////////////////////////////////////////////////////////////
// Author       : smeualex
// Date         : 25.02.2018
// Version      : 1.00
// Description  : Arduino helper library to callback a function when a button is pressed
//
// TODO 1       : Check for diferent button connections: pulled high, pulled low
// TODO 2       : Create relevant examples
// TODO 3       : Move this into a library of its own
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Arduino.h"

class DebouncedButton {
private:
    int pinNumber;                  /* arduino pin number where the button is connected   */
    void(*buttonCallback)();        /* callback when the button is pressed                */
    
    int buttonState;                /* the current reading from the input pin             */
    int lastButtonState;            /* the previous reading from the input pin            */
    unsigned long lastDebounceTime; /* the last time the output pin was toggled           */
    unsigned long debounceDelay;    /* the debounce time; increase if the output flickers */
    bool buttonHandled;             /* used internally when button's action is handled    */

    void setPinMode(int _pinMode)
    {
        if(_pinMode == INPUT || _pinMode == OUTPUT || _pinMode == INPUT_PULLUP)
            pinMode(pinNumber, _pinMode);
    }

    void setPinState(int state)
    {
        if (state == HIGH || state == LOW)
            digitalWrite(pinNumber, state);
    }

public:
    enum CallbackMethod {
        ONCE_ON_CLICK_DOWN,
        ONCE_ON_CLICK_UP,
        CONTINUOUS
    };

    DebouncedButton(int _pinNumber, 
                    void(*_f)(), 
                    int _delay, 
                    int _pinMode = INPUT_PULLUP, 
                    int _pinState = HIGH)
    {
        pinNumber        = _pinNumber;
        buttonCallback   = _f;
        debounceDelay    = _delay;
        lastDebounceTime = 0;
        lastButtonState  = LOW;
        buttonHandled    = false;

        setPinMode(_pinMode);
        setPinState(_pinState);
    }

    ~DebouncedButton() { };

    /* PUBLIC ACCESSORS                                    */
    void putHigh()              { setPinState(HIGH);        }
    void putLow()               { setPinState(LOW);         }
    void setAsInput()           { setPinMode(INPUT);        }
    void setAsInput_Pullup()    { setPinMode(INPUT_PULLUP); }
    void setAsOutput()          { setPinMode(OUTPUT);       }
    
    void checkButton();
};

