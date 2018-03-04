#pragma once



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
