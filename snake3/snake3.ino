/*
Name:		 snake3.ino
Created:	 27/02/2018 12:24:37 PM
Author:	     asmeu
Description: snake game on 8x8 led matrix

Components:
    Arduino Micro
    JoystickCtrl
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

    Program snake3 size: 9,818 bytes (used 34% of a 28,672 byte maximum) (2.95 secs)
    Minimum Memory Usage: 575 bytes (22% of a 2560 byte maximum)

    Program snake3 size: 11,404 bytes (used 40% of a 28,672 byte maximum) (2.33 secs)
    Minimum Memory Usage: 707 bytes (28% of a 2560 byte maximum)

    Program snake3 size: 12,446 bytes (used 43% of a 28,672 byte maximum) (3.85 secs)
    Minimum Memory Usage: 787 bytes (31% of a 2560 byte maximum)
*/

#include "globalConstants.h"

#include "Snake.h"
#include "Sound.h"
#include "Joystick.h"
#include "LedMatrix.h"
#include "TimedAction.h"

#include "KeyboardCtrl.h"
//////////////////////////////////////////////////////////////////////////////////////
// main game objects
//
// buzzer
Sound     speaker(SPEAKER_PIN);
// led matrix configured with its data pins
LedMatrix ledMatrix = LedMatrix(DIN, CLK, CS);
// joystick which acts as the main movement controller
JoystickCtrl joystickCtrl  = JoystickCtrl(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_SW, CB_startStopGame);
KeyboardCtrl keybCtrl;

Snake     snake;
// cookie position
Point     cookie;
//////////////////////////////////////////////////////////////////////////////////////
// game step -> moves the snake 1 steps plus other checks
TimedAction gameStep_action        (GAME_SPEED,                CB_performGameStep);
// potentiometer callback
TimedAction checkPot_action        (POTENTIOMETER_CHECK_DELAY, CB_potentiometerCheck);
// joystick switch
TimedAction joystickSW_action      (JOYSTICK_SW_CHECK_DELAY,   CB_joystickSwCheck);
//////////////////////////////////////////////////////////////////////////////////////
// the game state and end animations 
GameState gameState;
TimedAction gameEndAnimation_action(25, CB_flashEndAnimation, CB_postGameEndAnimation, 7);

TimedAction endGameAnimation_1( 50, CB_randomLedFlasher_1);
TimedAction endGameAnimation_2(110, CB_randomLedFlasher_2);
TimedAction endGameAnimation_3(220, CB_randomLedFlasher_3);
TimedAction endGameAnimation_4(330, CB_randomLedFlasher_4);
//////////////////////////////////////////////////////////////////////////////////////

char note[] = "A4";
int  beat = 4;
int  tempo = 60;

void setup()
{
    Serial.begin(115200);
    // invalid untill setup is finished
    gameState = GameState::INVALID;
    // brightness controll
    pinMode(BRIGHTNESS_CONTROLL_POT, INPUT);
    // init the led displays
    ledMatrix.startUp();
    // register move controllers
    snake.registerMoveController(&joystickCtrl);
    snake.registerMoveController(&keybCtrl);
    // reset the snake
    snake.resetSnake();
    //
    spawnFood();
    // start the game
    gameState = GameState::RUNNING;
}


void loop()
{
    checkPot_action.check();
    joystickSW_action.check();
    switch (gameState)
    {
    case GameState::RUNNING:
        gameStep_action.check();
        break;

    case GameState::RESTARTED:
        gameState = GameState::RUNNING;
        gameEndAnimation_action.reset();
        ledMatrix.resetLedState();
        snake.resetSnake();
        spawnFood();
        break;

    case GameState::GAMEOVER_FLASH_END_ANIMATION:
        gameEndAnimation_action.check();
        break;

    case GameState::GAMEOVER:
        endGameAnimation_1.check();
        endGameAnimation_2.check();
        endGameAnimation_3.check();
        endGameAnimation_4.check();
        break;

    case GameState::STOPPED:
        ledMatrix.clearDisplay(0);
        break;
    }
}

void CB_potentiometerCheck()
{
    ledMatrix.setLedIntensity(map(analogRead(BRIGHTNESS_CONTROLL_POT), 0, 1023, 1, 15));
}

void CB_joystickSwCheck()
{
    joystickCtrl.checkSwitch();
}

void CB_performGameStep()
{
    if (gameState == GameState::RUNNING)
    {
        /* MOVE SNAKE                   */
        // movement is handled by the snake via the movement controller
        snake.moveSnake();

        /* IS WE EATING A COOKIE?!      */
        if (snake.eatsCookie(cookie))
        {
            speaker.playNote(SND_COOKIE_EATEN_TONE, SND_COOKIE_EATEN_DELAY);
            spawnFood();
        }
        else
            snake.removeLastSegment();
        snake.addNewSegment();

        /* UPDATE LED DISPLAY           */
        ledMatrix.display(snake, cookie);

        /* CHECK FOR END-GAME CONDITION */
        if (snake.eatsTail())
        {
            gameState = GameState::GAMEOVER_FLASH_END_ANIMATION;
        }
    }
}

///////////////////////////////////////////////
// JOYSTICK SWITCH CALLBACK
//
// Stop the game if it's running
// Restart it if... anything else
//
void CB_startStopGame()
{
    switch (gameState)
    {
    case GameState::RUNNING:
        gameState = GameState::STOPPED;
        break;

    default:
        gameState = GameState::RESTARTED;
        break;
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

void CB_flashEndAnimation()
{
    for (int i = 0; i < snake.getLength(); i++)
        ledMatrix.setLed(0, 7-snake[i].x, 7-snake[i].y, 0);
    delay(200);
    
    for (int i = 0; i < snake.getLength(); i++)
        ledMatrix.setLed(0, 7-snake[i].x, 7-snake[i].y, 1);
    delay(200);
}

void CB_postGameEndAnimation()
{
    gameState = GameState::GAMEOVER;
}

void CB_randomLedFlasher_1()
{
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2);
}

void CB_randomLedFlasher_2()
{
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2);
}

void CB_randomLedFlasher_3()
{
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2);
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2); delay(5);
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2);
}

void CB_randomLedFlasher_4()
{
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2); delay(5);
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2); delay(5);
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2); delay(5);
    ledMatrix.setLed(0, random(8), random(8), random(1000) % 2); 
}
