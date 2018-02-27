#include "LedMatrix.h"

void LedMatrix::startUp()
{
    for (int address = 0; address<getDeviceCount(); address++)
    {
        shutdown(address, false);
        setLedIntensity();
        clearDisplay(address);
    }
}

void LedMatrix::setLedIntensity(int val)
{
    if (ledIntensity != val)
    {
        for (int i = 0; i < getDeviceCount(); i++)
            setIntensity(i, val);
        ledIntensity = val;
    }
}

void LedMatrix::updateLedState(Snake& snake, Point& cookie)
{
    for (byte i = 0; i < snake.getLength(); i++)
        leds[7 - snake[i].y] |= (B10000000 >> (7 - snake[i].x));
    leds[7 - cookie.y] |= (B10000000 >> (7 - cookie.x));
}

void LedMatrix::display(Snake& snake, Point& cookie)
{
    resetLedState();
    updateLedState(snake, cookie);
    for (int d = 0; d < getDeviceCount(); d++)
    {
        for (int i = 0; i < 8; i++)
        {
            setColumn(d, i, leds[i]);
            delayMicroseconds(50);
        }
    }
}