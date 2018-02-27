#include "Arduino.h"
#include "DebouncedButton.h"

void DebouncedButton::checkButton()
{
    int currentState = digitalRead(pinNumber);

    if (currentState != lastButtonState)
    {
        lastDebounceTime = millis();
    }

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
        if (true == buttonHandled)
            return;

        buttonCallback();

        buttonHandled = true;
    }
}
