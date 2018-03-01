#include "Sound.h"

void Sound::playNote(const unsigned int _tone, const unsigned int duration)
{
    pinMode(pin, OUTPUT);

    tone(pin, _tone, duration);
    delay(duration * 0.2);
    noTone(pin);

    pinMode(pin, INPUT);
}