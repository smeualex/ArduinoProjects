#pragma once
#include "Snake.h"
#include "LedControl.h"

class LedMatrix : public LedControl
{
#define LM_MAX_LED_INTENSITY 15
#define LM_MIN_LED_INTENSITY 1

    int  ledIntensity;
    byte leds[8];
public:
    LedMatrix(int data, int clk, int cs, int n = 1) : LedControl(data, clk, cs, n) { };
    ~LedMatrix() { };

    void startUp();
    void setLedIntensity(int val = 4);

    void updateLedState(Snake& snake, Point& cookie);
    void display(Snake& snake, Point& cookie);
    void display();
    void resetLedState(){ memset(leds, 0, sizeof(leds)); }

    void invertLeds();
};

