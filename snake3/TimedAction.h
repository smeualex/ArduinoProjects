#ifndef TIMEDACTION_H
#define TIMEDACTION_H

#include "Arduino.h"

#define NO_PREDELAY 0

class TimedAction {
  
  public:
    TimedAction(unsigned long interval,void (*function)());
    TimedAction(unsigned long prev,unsigned long interval,void (*function)());
	
	void reset();
	void disable();
	void enable();
	void check();
	
	void setInterval( unsigned long interval );

  private: 
    bool active;
    unsigned long previous;
    unsigned long interval;
    void (*execute)();
};

#endif

/*
|| @changelog
|| | 1.6 2010-10-08 - Alexander Brevig : Changed datatype of interval from unsigned int to unsigned long
|| | 1.5 2009-10-25 - Alexander Brevig : Added setInterval , requested by: Boris Neumann
|| | 1.4 2009-05-06 - Alexander Brevig : Added reset()
|| | 1.3 2009-04-16 - Alexander Brevig : Added disable() and enable(), requested by: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?action=viewprofile;username=ryno
|| | 1.2 2009-04-13 - Alexander Brevig : Added a constructor
|| | 1.1 2009-04-08 - Alexander Brevig : Added an example that demonstrates three arduino examples at once
|| | 1.0 2009-03-23 - Alexander Brevig : Initial Release
|| #
*/