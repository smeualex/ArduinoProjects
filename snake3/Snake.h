#pragma once

#include "Point.h"
#include "movement.h"
#include "IMovement.h"

class Snake {
private:
    Point         head;
    Point         segments[64];
    byte          length;
    moveDirection currentDirection;
    IMovement*    moveCtrlr;

public:
    Snake(IMovement* _moveCtrlr);
    ~Snake();

    void resetSnake();
    void resetSnakeSegments();

    void    removeLastSegment();
    void    addNewSegment();
    boolean segmentExists(Point p);
    
    void    moveSnake();
    
    boolean eatsCookie(Point cookie) { return head == cookie; }
    boolean eatsTail();

    Point getHead()   { return head; }
    byte  getLength() { return length; }
    moveDirection getCurrentMovingDirection() { return currentDirection; }


    Point& operator[] (int i)
    {
        return segments[i];
    }
};

