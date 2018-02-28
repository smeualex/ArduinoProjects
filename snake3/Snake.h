#pragma once

#include "Point.h"
#include "movement.h"

class Snake {
    Point head;
    Point segments[64];
    byte  length;
    moveDirection currentDirection;

public:
    Snake();
    ~Snake();

    void resetSnake();
    void resetSnakeSegments();

    void    removeLastSegment();
    void    addNewSegment();
    boolean segmentExists(Point p);
    
    void    moveSnake(moveDirection dir);
    
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

