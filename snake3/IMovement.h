#pragma once
#include "movement.h"

class IMovement {
public:
    virtual moveDirection getDirection() = 0;
};