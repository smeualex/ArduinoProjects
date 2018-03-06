#pragma once

/*
 * Movement interface
 * Any class implementing this can act as a movement controller
 * by sending the appropriate move direction to the snake
 *
 */
class IMovement {
public:
    enum moveDirection {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT,
        KEEP_CURRENT,
        STILL
    };
    virtual moveDirection getDirection() = 0;
};
