#pragma once

#include "Point.h"
#include "IMovement.h"

#define MAX_MOVEMENT_CTRLS 3
class Snake {
private:
    Point         head;
    Point         segments[64];
    byte          length;
    moveDirection currentDirection;
    
    /* Have a max. of 3 controllers attached             */
    /* They are checked in the order they are registered */
    /* For example:                                      */
    /*     1. Joystick Controller                        */
    /*     2. Serial Controller                          */
    static byte   controllersAttached;
    IMovement*    moveCtrlr[MAX_MOVEMENT_CTRLS];
    moveDirection getDirection();

public:
    Snake() { };
    ~Snake() { };
    void registerMoveController(IMovement* _moveCtrl);
    /* SNAKE RESET FUNCTIONS                            */
    void    resetSnake();
    void    resetSnakeSegments();
    /* MOVEMENT AND POSITION HANDLING                   */
    void    removeLastSegment();
    void    addNewSegment();
    boolean segmentExists(Point p);
    void    moveSnake();
    boolean eatsCookie(Point cookie) { return head == cookie; }
    boolean eatsTail();
    /* GETTERS                                          */
    Point         getHead()   { return head; }
    byte          getLength() { return length; }
    moveDirection getCurrentMovingDirection() { return currentDirection; }
    /* OPERATORS                                        */
    Point& operator[] (int i)
    {
        return segments[i];
    }
};

