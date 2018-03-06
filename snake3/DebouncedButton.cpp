#include "Arduino.h"
#include "DebouncedButton.h"

void DebouncedButton::checkButton()
{
    /* read the button's pin value                   */
    int currentState = digitalRead(pinNumber);
    /* if the state has changed get the current time */
    if (currentState != lastButtonState)
    {
        lastDebounceTime = millis();
    }
    /* we have passed our debouncing delay time      */
    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (currentState != buttonState)
        {
            buttonState = currentState;
        }
    }

    lastButtonState = currentState;

    if (lastButtonState == HIGH && buttonHandled == true)
        buttonHandled = false;

    if (lastButtonState == LOW)
    {
        // button is already handled => return
        if (true == buttonHandled)
            return;
        /* CALL THE CALLBACK :) */
        buttonCallback();
        // button has been handled
        buttonHandled = true;
    }
}
