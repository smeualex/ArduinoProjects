#pragma once

#include "Arduino.h"
#include <avr/pgmspace.h>

const char Ds4Eb4[] PROGMEM = "D#4/Eb4";
const char E4[]     PROGMEM = "E4";
const char F4[]     PROGMEM = "F4";
const char Fs4Gb4[] PROGMEM = "F#4/Gb4";
const char G4[]     PROGMEM = "G4";
const char Gs4Ab4[] PROGMEM = "G#4/Ab4";
const char A_4[]     PROGMEM = "A4";
const char As4Bb4[] PROGMEM = "A#4/Bb4";
const char B4[]     PROGMEM = "B4";
const char C5[]     PROGMEM = "C5";
const char Cs5Db5[] PROGMEM = "C#5/Db5";
const char D5[]     PROGMEM = "D5";
const char Ds5Eb5[] PROGMEM = "D#5/Eb5";
const char E5[]     PROGMEM = "E5";
const char F5[]     PROGMEM = "F5";
const char Fs5Gb5[] PROGMEM = "F#5/Gb5";
const char G5[]     PROGMEM = "G5";
const char Gs5Ab5[] PROGMEM = "G#5/Ab5";
const char A_5[]     PROGMEM = "A5";
const char As5Bb5[] PROGMEM = "A#5/Bb5";
const char B5[]     PROGMEM = "B5";
const char C6[]     PROGMEM = "C6";
const char Cs6Db6[] PROGMEM = "C#6/Db6";
const char D6[]     PROGMEM = "D6";
const char Ds6Eb6[] PROGMEM = "D#6/Eb6";
const char E6[]     PROGMEM = "E6";
const char F6[]     PROGMEM = "F6";
const char Fs6Gb6[] PROGMEM = "Fs6Gb6";
const char G6[]     PROGMEM = "G6";
const char Rest[]   PROGMEM = "rest";

const static char* const noteNames[] PROGMEM = { Ds4Eb4, E4, F4, Fs4Gb4,G4,Gs4Ab4,A_4,As4Bb4,B4,C5,Cs5Db5,D5,Ds5Eb5,E5,F5,Fs5Gb5,G5,Gs5Ab5,A_5,As5Bb5,B5,C6,Cs6Db6,D6,Ds6Eb6,E6,F6,Fs6Gb6,G6, Rest };

const static int tones[] PROGMEM =
{ 1607, 1516, 1431, 1351, 1275,
1203, 1136, 1072, 1012, 955,
901, 851, 803, 758, 715, 675,
637, 601, 568, 536, 506, 477,
450, 425, 401, 379, 357, 337, 318 };

class Sound {
    int pin;
public:
    Sound(int _pin) 
    { 
        pin = _pin;
    }

    ~Sound() { }

    void playTone(int tone, int duration);
    void playNote(const char* note, int duration);
    void playRest(const int duration);
};

