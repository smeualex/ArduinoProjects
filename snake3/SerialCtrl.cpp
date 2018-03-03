#include "Arduino.h"
#include "SerialCtrl.h"

moveDirection SerialCtrl::getDirection()
{
    switch (Serial.read())
    {
    case 'w':
    case 'W':
        return moveDirection::DOWN;
        break;

    case 'a':
    case 'A':
        return moveDirection::LEFT;
        break;

    case 's':
    case 'S':
        return moveDirection::UP;
        break;

    case 'd':
    case 'D':
        return moveDirection::RIGHT;
        break;

    default:
        return moveDirection::KEEP_CURRENT;
    }
}
