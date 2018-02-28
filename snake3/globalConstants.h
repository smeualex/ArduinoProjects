#pragma once

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

//////////////////////////////////////////
// DELAY VALUES

/* delay to check button presses in ms  */
#define DEBOUNCING_DELAY          50

#define POTENTIOMETER_CHECK_DELAY 250

#define GAME_SPEED                150

#define JOYSTICK_SW_CHECK_DELAY   25

//////////////////////////////////////////
// DELAY VALUES

enum GameState {
    INVALID,
    RESTARTED,
    RUNNING,
    STOPPED,
    GAMEOVER,
    GAMEOVER_FLASH_END_ANIMATION
};