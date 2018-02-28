#include "Sound.h"

void Sound::playTone(int _tone, int duration)
{
    //tone(pin, _tone, duration);
    for (long i = 0; i < duration * 1000L; i += _tone * 2)
    {
        digitalWrite(pin, HIGH);
        delayMicroseconds(_tone);
        digitalWrite(pin, LOW);
    }
    delayMicroseconds(_tone);
}

void Sound::playNote(const char* note, int duration)
{
    char PGM_note[8];
    int  PGM_tone;
    
    char logBuf[256];
    sprintf(logBuf, " > playNote: %s [%d]", note, duration);
    Serial.println(logBuf);

    for (int i = 0; i < 29; i++)
    {
        strcpy(PGM_note, (char*) pgm_read_word(&(noteNames[i])));
        
        sprintf(logBuf, " > PGM Note: %s", PGM_note);
        Serial.println(logBuf);
        
        if ( !strcmp(PGM_note, note) )
        {
            PGM_tone = pgm_read_word_near(&tones[i]);

            sprintf(logBuf, " > playing note: %s [%d]", PGM_note, PGM_tone);
            Serial.println(logBuf);

            playTone(tones[i], duration);
        }
    }
}