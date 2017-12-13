#ifndef STRINGS_H
#define STRINGS_H

/*
Name:		strings.h
Created:	13/12/2017 15:08:13 PM
Author:	    asm

    This file contains strings used by the main program.
    The strings are stored in the program memory to minimize ram footprint.
*/

#include <avr/pgmspace.h>

#define _ERROR_ "<ERROR>"
#define _OK_ "<OK>"

const PROGMEM char dateTimeValid[]   = _OK_"Received Date Time are valid";
const PROGMEM char dateGenErrorMsg[] = _ERROR_"Invalid Date Supplied";
const PROGMEM char timeGenErrorMsg[] = _ERROR_"Invalid Time Supplied";


inline void _printPGMString(const char* msg, Stream &outStream = Serial)
{
    size_t len = strlen_P(msg);
    for (int i = 0; i < len; i++)
        outStream.print((char)pgm_read_byte_near(msg + i));
    outStream.println();
}
#endif
