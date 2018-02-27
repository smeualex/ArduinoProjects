#pragma once

#include "Point.h"
#include "Board.h"
#include "movement.h"

class Snake {
    Board board;

    Point head;
    Point segments[64];
    byte  length;
    moveDirection direction;

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
    moveDirection getCurrentMovingDirection() { return direction; }


    Point& operator[] (int i)
    {
        return segments[i];
    }
};
