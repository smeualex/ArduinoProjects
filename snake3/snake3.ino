/*
Name:		 snake3.ino
Created:	 27/02/2018 12:24:37 PM
Author:	     asmeu
Description: snake game on 8x8 led matrix

Components:
    Arduino Micro
    Joystick
    8x8 lex matrix


    Program snake3 size: 7,596 bytes (used 26% of a 28,672 byte maximum) (8.66 secs)
    Minimum Memory Usage: 495 bytes (19% of a 2560 byte maximum)
*/
#include "LedControl.h"

#include "Snake.h"
#include "DebouncedButton.h"

Snake snake;
Point foodPosition;
boolean gameRunning = true;


const int DIN = 2;
const int CS  = 3;
const int CLK = 4;

const int JOYSTICK_X = A2;
const int JOYSTICK_Y = A3;
const int JOYSTICK_SW = A1;

const int BRIGHTNESS_CONTROLL_POT = A0;

int gameSpeed = 150;
#define DEBOUNCING_DELAY 50      /* delay to check button presses in ms */
DebouncedButton resetButton(JOYSTICK_SW, CB_startStopGame, DEBOUNCING_DELAY);

byte _led[8];
LedControl lc = LedControl(DIN, CLK, CS, 2);

int potValue;
int prevPotValue;

moveDirection dir = moveDirection::RIGHT;

void CB_startStopGame()
{
    gameRunning = !gameRunning;

    if (gameRunning == false)
    {
        lc.clearDisplay(0);
    }
    else
    {
        resetLedState();
        snake.resetSnake();
        spawnFood();
    }
}

void setup()
{
    // init the led displays
    for (int address = 0; address<lc.getDeviceCount(); address++)
    {
        lc.shutdown(address, false);
        lc.setIntensity(address, 5);
        lc.clearDisplay(address);
    }
    // brightness controll
    pinMode(BRIGHTNESS_CONTROLL_POT, INPUT);

    spawnFood();
}

void loop()
{
    setLedIntensity();
    resetButton.checkButton();

    if (gameRunning)
    {
        /* GET DIRECTION AND MOVE SNAKE */
        snake.moveSnake(getDirection(analogRead(JOYSTICK_X),
            analogRead(JOYSTICK_Y)));
        /* IS WE EATING A COOKIE?!      */
        if (!snake.eatsCookie(foodPosition))
            snake.removeLastSegment();
        else
            spawnFood();
        snake.addNewSegment();
        /* UPDATE LED DISPLAY           */
        displayToLedMatrix();
        /* CHECK FOR END-GAME CONDITION */
        if (snake.eatsTail())
        {
            gameRunning = false;
            flashEndAnimation();
        }
    }
    delay(gameSpeed);
}

void setLedIntensity()
{
    potValue = map(analogRead(BRIGHTNESS_CONTROLL_POT), 0, 1023, 1, 15);
    if (prevPotValue != potValue)
    {
        lc.setIntensity(0, potValue);
        prevPotValue = potValue;
    }
}

moveDirection getDirection(int joyX, int joyY)
{
    if (joyX > 498 && joyX < 520 && 
        joyY > 498 && joyY < 520)
        return snake.getCurrentMovingDirection();

    if (joyX > 520 && joyX <= 1024 && 
        joyY > 350 && joyY < 730)
    {
        if (snake.getCurrentMovingDirection() == moveDirection::LEFT && 
            snake.getLength() > 1)
            return snake.getCurrentMovingDirection();
        return moveDirection::RIGHT;
    }

    if (joyX >= 0 && joyX < 500 && 
        joyY > 350 && joyY < 731)
    {
        if (snake.getCurrentMovingDirection() == moveDirection::RIGHT && 
            snake.getLength() > 1)
            return snake.getCurrentMovingDirection();
        return moveDirection::LEFT;
    }

    if (joyX > 495 && joyX < 900 && 
        joyY >= 0 && joyY < 520)
    {
        if (snake.getCurrentMovingDirection() == DOWN && 
            snake.getLength() > 1)
            return snake.getCurrentMovingDirection();
        return moveDirection::UP;
    } 

    if (joyX > 350 && joyX < 730 && 
        joyY > 520 && joyY <= 1024)
    {
        if (snake.getCurrentMovingDirection() == moveDirection::UP && 
            snake.getLength() > 1)
            return snake.getCurrentMovingDirection();
        return moveDirection::DOWN;
    }
}

void updateLedState()
{
    int i = 0;
    while (snake[i].x != 255)
    {
        _led[7 - snake[i].y] |= (B10000000 >> (7 - snake[i].x ));
         i++;
    }
    _led[7 - foodPosition.y] |= (B10000000 >> (7 - foodPosition.x));
}

void resetLedState()
{
    for (int i = 0; i < 8; i++)
        _led[i] = 0;
}

void displayToLedMatrix()
{
    resetLedState();
    updateLedState();
    // refresh led matrix
    for (int i = 7; i >= 0; i--)
    {
        lc.setColumn(0, i, _led[i]);
        delayMicroseconds(50);
    }
}

void spawnFood()
{
    do
    {
        foodPosition.x = random(8);
        foodPosition.y = random(8);
    } while (snake.segmentExists(foodPosition));
}

void print_binary(int v, int num_places)
{
    int mask = 0;

    for (int n = 1; n <= num_places; n++)
        mask = (mask << 1) | 0x0001;
    v = v & mask;

    while (num_places)
    {
        if (v & (0x0001 << num_places - 1))
            Serial.print("1");
        else
            Serial.print("0");
        --num_places;
    }
}


void flashEndAnimation()
{
    // TO DO : implement end game animation
}
