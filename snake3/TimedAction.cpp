#include "TimedAction.h"

TimedAction::TimedAction(unsigned long intervl,void (*function)(), void(*postFunction)(), unsigned long n)
{
    active = true;
	previous = 0;
	interval = intervl;
	execute = function;
    nExecutionsBeforeStop = n;  
    postExecute = postFunction;
    execCounter = 0;
}

TimedAction::TimedAction(unsigned long prev,unsigned long intervl,void (*function)(), void(*postFunction)(), unsigned long n)
{
	previous = prev;
    TimedAction(intervl, function, postFunction, n);
}

void TimedAction::reset()
{
    previous = millis();
    if (postExecute != NULL && nExecutionsBeforeStop != EXECUTE_INDEFINETLY && execCounter >= nExecutionsBeforeStop)
    {
        execCounter = 0;
        if (!isActive())
            enable();
    }
}

void TimedAction::disable()
{
    active = false;
}

void TimedAction::enable()
{
	active = true;
}


void TimedAction::__execute()
{ 
    if (millis() - previous >= interval)
    {
        previous = millis();
        ++execCounter;
        execute();
    }
}

void TimedAction::check()
{
    if (!isActive())
        return;

    if (nExecutionsBeforeStop == EXECUTE_INDEFINETLY)
    {
        __execute();
    }
    else
    {
        if (execCounter <= nExecutionsBeforeStop)
        {
            __execute();
            if (execCounter == nExecutionsBeforeStop)
            {
                execCounter++;
                postExecute();
            }
        }
        else
        {
            disable();
        }
    }
}

void TimedAction::setInterval( unsigned long intervl)
{
	interval = intervl;
}