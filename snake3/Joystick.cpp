#include "Joystick.h"
#include "Arduino.h"

moveDirection Joystick::getDirection()
{
    int x_raw = analogRead(pin_X);
    int y_raw = analogRead(pin_Y);
    int x = map(x_raw, 0, 1023, 1, 11);
    int y = map(y_raw, 0, 1023, 1, 11);

    char logBuf[256];
    sprintf(logBuf, "X: %4d - %2d  |  Y: %4d - %2d",
        x_raw, x, y_raw, y);
    Serial.println(logBuf);

    if( x == 5 && (y ==5 || y == 6))
        return moveDirection::KEEP_CURRENT;

    if( x > 5 && (1 <= y && y <= 11))
        return moveDirection::RIGHT;

    if( x < 5 && (1 <= y && y <= 11))
        return moveDirection::LEFT;

    if( y > 6 && (0 <= x && x <= 9))
        return moveDirection::DOWN;

    if (y < 5 && (0 <= x && x <= 9))
        return moveDirection::UP;
}
