#include "Joystick.h"
#include "Arduino.h"

/*
 * Read value from X or Y axis
 * Normalize the value to the norm_range interval
 *
 * Returns the distance from center as a signed int
 */
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

    /* We are on one of the diagonals               */
    /* Keep the current direction because we do not */
    /*    have diagonal movement                    */
    if( abs(x) == abs(y) )
        return IMovement::moveDirection::KEEP_CURRENT;

    /* Area I   -> RIGHT                            */
    if (x > 0 && x > y)
        return IMovement::moveDirection::RIGHT;

    /* Area III -> LEFT                             */
    if (x < 0 && x < y)
        return IMovement::moveDirection::LEFT;

    /* Area II  -> DOWN                             */
    /*
     * This is actually the UP direction but due
     * to the way the snake is held in memory the
     * UP / DOWN are reversed
     */
    if (y > 0 && y > x)
        return IMovement::moveDirection::DOWN;

    /* Area IV -> UP                                */
    if (y < 0 && y < x)
        return IMovement::moveDirection::UP;
}
