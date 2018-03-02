#pragma once
#include "IMovement.h"
#include "movement.h"

class KeyboardCtrl : public IMovement {
public:
    KeyboardCtrl() { };
    ~KeyboardCtrl() { };
    moveDirection getDirection();
};

