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

    Program snake3 size: 8,614 bytes (used 30% of a 28,672 byte maximum) (2.93 secs)
    Minimum Memory Usage: 529 bytes (21% of a 2560 byte maximum)

    Program snake3 size: 8,712 bytes (used 30% of a 28,672 byte maximum) (2.52 secs)
    Minimum Memory Usage: 529 bytes (21% of a 2560 byte maximum)
*/

#include "globalConstants.h"

#include "Snake.h"
#include "Joystick.h"
#include "LedMatrix.h"
#include "TimedAction.h"

Snake snake;
Point cookie;
LedMatrix ledMatrix = LedMatrix(DIN, CLK, CS);
Joystick  joystick = Joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_SW, CB_startStopGame);

TimedAction checkPot_action  (POTENTIOMETER_CHECK_DELAY, potentiometerCheck);
TimedAction joystickSW_action(JOYSTICK_SW_CHECK_DELAY, joystickSwCheck);
TimedAction gameStep_action  (GAME_SPEED, performGameStep);

boolean gameRunning = true;

TimedAction t1(100, f1);
TimedAction t2(110, f2);
TimedAction t3(120, f3);
TimedAction t4(130, f4);

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
    checkPot_action.check();
    joystickSW_action.check();

    if (gameRunning)
    {
        gameStep_action.check();
    }
    else
    {
        t1.check();
        t2.check();
        t3.check();
        t4.check();
    }
}

void potentiometerCheck()
{
    ledMatrix.setLedIntensity(map(analogRead(BRIGHTNESS_CONTROLL_POT), 0, 1023, 1, 15));
}

void joystickSwCheck()
{
    joystick.checkSwitch();
}

void performGameStep()
{
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
    for (int r = 0; r < 7; r++)
    {
        for (int i = 0; i < snake.getLength(); i++)
            ledMatrix.setLed(0, 7-snake[i].x, 7-snake[i].y, 0);
        delay(200);
        for (int i = 0; i < snake.getLength(); i++)
            ledMatrix.setLed(0, 7-snake[i].x, 7-snake[i].y, 1);
        delay(200);
    }
}

void f1()
{
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2);
}

void f2()
{
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2);
}

void f3()
{
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2);
}

void f4()
{
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2);
}
