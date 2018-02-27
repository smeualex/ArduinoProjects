#include "Joystick.h"
#include "Arduino.h"

moveDirection Joystick::getDirection()
{
    int joyX = analogRead(pin_X);
    int joyY = analogRead(pin_Y);

    if (joyX > 498 && joyX < 520 &&
        joyY > 498 && joyY < 520)
        return moveDirection::KEEP_CURRENT;

    if (joyX > 520 && joyX <= 1024 &&
        joyY > 350 && joyY < 730)
    {
        return moveDirection::RIGHT;
    }

    if (joyX >= 0 && joyX < 500 &&
        joyY > 350 && joyY < 731)
    {
        return moveDirection::LEFT;
    }

    if (joyX > 495 && joyX < 900 &&
        joyY >= 0 && joyY < 520)
    {
        return moveDirection::UP;
    }

    if (joyX > 350 && joyX < 730 &&
        joyY > 520 && joyY <= 1024)
    {
        return moveDirection::DOWN;
    }
}
