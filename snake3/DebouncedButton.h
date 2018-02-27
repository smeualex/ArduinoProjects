#pragma once
#include "Arduino.h"
class DebouncedButton {
private:
    int pinNumber;
    void(*buttonCallback)();
    
    int buttonState;                // the current reading from the input pin
    int lastButtonState;            // the previous reading from the input pin
    unsigned long lastDebounceTime; // the last time the output pin was toggled
    unsigned long debounceDelay;    // the debounce time; increase if the output flickers
    bool buttonHandled;

public:
    DebouncedButton(int _pinNumber, void(*_f)(), int _delay)
    {
        pinNumber        = _pinNumber;
        buttonCallback   = _f;
        debounceDelay    = _delay;
        lastDebounceTime = 0;
        lastButtonState  = LOW;
        buttonHandled    = false;

        setupButton_InternalPullup_High();
    }

    ~DebouncedButton() { };

    void setupButton_InternalPullup_High()
    {
        pinMode(pinNumber, INPUT_PULLUP);
        digitalWrite(pinNumber, HIGH);
    }

    void checkButton();

};

