#include "Arduino.h"
#include "SerialCtrl.h"

IMovement::moveDirection SerialCtrl::getDirection()
{
    switch (Serial.read())
    {
    case 'w':
    case 'W':
        return IMovement::moveDirection::DOWN;
        break;

    case 'a':
    case 'A':
        return IMovement::moveDirection::LEFT;
        break;

    case 's':
    case 'S':
        return IMovement::moveDirection::UP;
        break;

    case 'd':
    case 'D':
        return IMovement::moveDirection::RIGHT;
        break;

    default:
        return IMovement::moveDirection::KEEP_CURRENT;
    }
}
