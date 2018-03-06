#pragma once

#include "Sound.h"

/* DISPLAY MATRIX CONNECTION PINS       */
#define DIN 2
#define CS  3
#define CLK 4
/* JOYSTICK CONNECTION PINS             */
#define JOYSTICK_X  A2
#define JOYSTICK_Y  A3
#define JOYSTICK_SW A1
/* POTENTIOMETER PIN                    */
#define BRIGHTNESS_CONTROLL_POT A0
/* SPEAKER PIN                          */
#define SPEAKER_PIN 6

//////////////////////////////////////////
// DELAY VALUES

/* delay to check button presses in ms  */
#define DEBOUNCING_DELAY          50

#define POTENTIOMETER_CHECK_DELAY 250

#define GAME_SPEED                150

#define JOYSTICK_SW_CHECK_DELAY   25

//////////////////////////////////////////
// SOUND
#define SND_COOKIE_EATEN_DELAY    100
#define SND_COOKIE_EATEN_TONE     NOTE_F5
//////////////////////////////////////////
// GAME STATE
enum GameState {
    INVALID,                        // initial state untill setup() is done
    RESTARTED,                      // after a restart has occured and game is restarted
    RUNNING,                        // normal running mode
    STOPPED,                        // stopped by button (forced)
    GAMEOVER,                       // game over
    GAMEOVER_FLASH_END_ANIMATION,   // game over with snake flash animation
    TEST_ON                         // only for testing purposes and debug
};
//////////////////////////////////////////