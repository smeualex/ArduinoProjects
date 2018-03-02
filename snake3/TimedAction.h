#ifndef TIMEDACTION_H
#define TIMEDACTION_H

#include "Arduino.h"

#define NO_PREDELAY         0
#define EXECUTE_INDEFINETLY 0

class TimedAction {
private:
    bool active;
    unsigned long previous;
    unsigned long interval;
    unsigned long nExecutionsBeforeStop;
    unsigned long execCounter;
    void(*execute)();                      // called each time the timer expires
    void(*postExecute)();                   // if set called after nExecutions have occured

    void __execute();

public:
    TimedAction() { active = false; execute = NULL; interval = 0L; previous = 0L; postExecute = NULL; execCounter = 0; nExecutionsBeforeStop = EXECUTE_INDEFINETLY; }
    TimedAction(unsigned long interval, void(*function)(), void(*postFunction)() = NULL, unsigned long n = EXECUTE_INDEFINETLY);
    TimedAction(unsigned long prev, unsigned long interval, void(*function)(), void(*postFunction)() = NULL, unsigned long n = EXECUTE_INDEFINETLY);

    void reset();
    void disable();
    void enable();
    void check();

    void setInterval(unsigned long interval);

    bool isActive() { return active; }
    unsigned long getExecutionCounter() { return execCounter; }
    void registerCallback(void(*function)()) { execute = function; }
    void registerPostExecCallback(void(*function)()) { postExecute = function; }
};

#endif