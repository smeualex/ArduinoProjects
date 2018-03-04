#include "Snake.h"

byte Snake::controllersAttached = 0;

IMovement::moveDirection Snake::getDirection()
{
    IMovement::moveDirection m = IMovement::moveDirection::KEEP_CURRENT;
    for (int i = 0; i < controllersAttached; i++)
    {
        m = moveCtrlr[i]->getDirection();
        if (m != IMovement::moveDirection::KEEP_CURRENT &&
            m != IMovement::moveDirection::STILL)
            return m;
    }
    return m;
}

void Snake::registerMoveController(IMovement * _moveCtrl)
{
    if (controllersAttached < MAX_MOVEMENT_CTRLS)
    {
        if(_moveCtrl != NULL)
            moveCtrlr[controllersAttached++] = _moveCtrl;
    }
}

void Snake::resetSnake()
{
    currentDirection = (IMovement::moveDirection)random(4);
    head =  Point (random(8), random(8));
    length = 1;
}

void Snake::removeLastSegment()
{
    printSnakeSegments("RM_LS_BF");
    
    for (int i = 1; i < length; i++)
        segments[i - 1] = segments[i];
    length--;

    printSnakeSegments("RM_LS_AF");
}

void Snake::addNewSegment()
{ 
    printSnakeSegments("ADD_S_BF");
    segments[length] = head;
    length++;
    printSnakeSegments("ADD_S_AF");
}

boolean Snake::segmentExists(Point p)
{ 
    for (int i = 0; i < length; i++)
        if (segments[i] == p)
            return true;
    return false;
}

void Snake::moveSnake()
{ 
    IMovement::moveDirection dir = this->getDirection();
    /* CHECK FOR OPPOSITE DIRECTIONS OR CURRENT */
    if (length == 1)
    {
        if( dir != currentDirection && dir != IMovement::moveDirection::KEEP_CURRENT)
            currentDirection = dir;
    }
    else
    {
        if ((dir == IMovement::moveDirection::LEFT  && currentDirection == IMovement::moveDirection::RIGHT) ||
            (dir == IMovement::moveDirection::RIGHT && currentDirection == IMovement::moveDirection::LEFT) ||
            (dir == IMovement::moveDirection::UP    && currentDirection == IMovement::moveDirection::DOWN) ||
            (dir == IMovement::moveDirection::DOWN  && currentDirection == IMovement::moveDirection::UP)
            ||
            (dir == IMovement::moveDirection::KEEP_CURRENT))
        {
            dir = currentDirection;
        }
        else
        {
            currentDirection = dir;
        }
    }

    switch (currentDirection)
    {
    case IMovement::moveDirection::UP:
        head.y++;
        if (head.y > 7)
            head.y = 0;
        break;

    case IMovement::moveDirection::DOWN:
        if (head.y > 0)
            head.y--;
        else
            head.y = 7;
        break;

    case IMovement::moveDirection::RIGHT:
        if (head.x > 0)
            head.x--;
        else
            head.x = 7;
        break;

    case IMovement::moveDirection::LEFT:
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

void Snake::printSnakeSegments(const char* operation)
{
    char buf[32];
    sprintf(buf, ">>%10s<<", operation);
    Serial.print(buf);
    for (int i = 0; i < length; i++)
    {
        sprintf(buf, "[%d,%d]", segments[i].x, segments[i].y);
        Serial.print(buf);
    }
    Serial.println();
}