#include "Joystick.h"
#include "Arduino.h"

int JoystickCtrl::readAxis(int axis)
{
    if (axis != pin_X && axis != pin_Y)
        return 0;

    int normValue = map(analogRead(axis), 0, 1023, 0, norm_range);
    int distance_from_center = normValue - center;
    
    if (abs(distance_from_center) < move_threshold)
        distance_from_center = 0;
    
    return distance_from_center;
}

IMovement::moveDirection JoystickCtrl::getDirection()
{
    int x = readAxis(pin_X);
    int y = readAxis(pin_Y);

    if( x == y )
        return IMovement::moveDirection::KEEP_CURRENT;

    if (x > 0 && x > y)
        return IMovement::moveDirection::RIGHT;

    if (x < 0 && x < y)
        return IMovement::moveDirection::LEFT;

    if (y > 0 && y > x)
        return IMovement::moveDirection::DOWN;

    if (y < 0 && y < x)
        return IMovement::moveDirection::UP;
}
