#pragma once

enum moveDirection {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    KEEP_CURRENT,
    STILL
};


class IMovement {
public:
    virtual moveDirection getDirection() = 0;
};
