#include "Snake.h"

Snake::Snake()
{
    //board = _board;
    resetSnake();
}

void Snake::resetSnake()
{
    resetSnakeSegments();
    head =  Point (random(8), random(8));
    length = 1;
}

void Snake::resetSnakeSegments()
{ 
    for (int i = 0; i < length; i++)
        segments[i].x = segments[i].y = 255;
}

Snake::~Snake()
{ }

void Snake::removeLastSegment()
{
    int i = -1;
    for (i = 1; i < length; i++)
        segments[i - 1] = segments[i];

    if (i != -1)
        segments[i] = Point(255, 255);
    length--;
}

void Snake::addNewSegment()
{ 
    segments[length] = head;
    length++;
}

boolean Snake::segmentExists(Point p)
{ 
    for (int i = 0; i < length; i++)
        if (segments[i] == p)
            return true;
    return false;
}

void Snake::moveSnake(moveDirection dir)
{ 
    direction = dir;
    switch (dir)
    {
    case moveDirection::UP:
        head.y++;
        if (head.y > 7)
            head.y = 0;
        break;

    case moveDirection::DOWN:
        if (head.y > 0)
            head.y--;
        else
            head.y = 7;
        break;

    case moveDirection::RIGHT:
        if (head.x > 0)
            head.x--;
        else
            head.x = 7;
        break;

    case moveDirection::LEFT:
        head.x++;
        if (head.x > 7)
            head.x = 0;
        break;
    }
}

boolean Snake::eatsTail()
{
    if (length < 4)
        return false;

    for (int i = 0; i < length - 3; i++)
    {
        if (segments[i] == head)
            return true;
    }
    return false;
}