/*
Name:		 snake3.ino
Created:	 27/02/2018 12:24:37 PM
Author:	     asmeu
Description: snake game on 8x8 led matrix

Components:
    Arduino Micro
    Joystick
    8x8 lex matrix


    Program snake3 bits: 7,596 bytes (used 26% of a 28,672 byte maximum) (8.66 secs)
    Minimum Memory Usage: 495 bytes (19% of a 2560 byte maximum)

    Program snake3 bits: 7,650 bytes (used 27% of a 28,672 byte maximum) (1.89 secs)
    Minimum Memory Usage: 493 bytes (19% of a 2560 byte maximum)

    Program snake3 size: 8,268 bytes (used 29% of a 28,672 byte maximum) (9.77 secs)
    Minimum Memory Usage: 496 bytes (19% of a 2560 byte maximum)
*/

#include "globalConstants.h"

#include "Snake.h"
#include "Joystick.h"
#include "LedMatrix.h"

Snake snake;
Point cookie;
LedMatrix ledMatrix = LedMatrix(DIN, CLK, CS);
Joystick  joystick = Joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_SW, CB_startStopGame);


int gameSpeed = 150;


boolean gameRunning = true;

void setup()
{
    // brightness controll
    pinMode(BRIGHTNESS_CONTROLL_POT, INPUT);
    // init the led displays
    ledMatrix.startUp();
    //
    spawnFood();
}

void loop()
{
    ledMatrix.setLedIntensity(map(analogRead(BRIGHTNESS_CONTROLL_POT), 0, 1023, 1, 15));
    joystick.checkSwitch();

    if (gameRunning)
    {
        /* GET DIRECTION AND MOVE SNAKE */
        snake.moveSnake(joystick.getDirection());
        /* IS WE EATING A COOKIE?!      */
        if (snake.eatsCookie(cookie))
            spawnFood();
        else
            snake.removeLastSegment();
        snake.addNewSegment();
        /* UPDATE LED DISPLAY           */
        ledMatrix.display(snake, cookie);
        /* CHECK FOR END-GAME CONDITION */
        if (snake.eatsTail())
        {
            gameRunning = false;
            flashEndAnimation();
        }
    }
    delay(gameSpeed);
}

void CB_startStopGame()
{
    gameRunning = !gameRunning;

    if (gameRunning == false)
    {
        ledMatrix.clearDisplay(0);
    }
    else
    {
        ledMatrix.resetLedState();
        snake.resetSnake();
        spawnFood();
    }
}

void spawnFood()
{
    do
    {
        cookie.x = random(8);
        cookie.y = random(8);
    } while (snake.segmentExists(cookie));
}

void flashEndAnimation()
{
    // TO DO : implement end game animation
}
