#pragma once
#include "IMovement.h"

class KeyboardCtrl : public IMovement {
public:
    KeyboardCtrl() { };
    ~KeyboardCtrl() { };
    /* IMovement implementation */
    moveDirection getDirection();
};

