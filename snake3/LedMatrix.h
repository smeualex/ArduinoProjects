#pragma once
#include "Snake.h"
#include "LedControl.h"

class LedMatrix : public LedControl
{
    int  ledIntensity;
    byte leds[8];
public:
    LedMatrix(int data, int clk, int cs, int n = 1) : LedControl(data, clk, cs, n) { };
    ~LedMatrix() { };

    void startUp();
    void setLedIntensity(int val = 4);

    void updateLedState(Snake& snake, Point& cookie);
    void display(Snake& snake, Point& cookie);
    void resetLedState(){ memset(leds, 0, sizeof(leds)); }
};

