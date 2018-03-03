#pragma once
#include "IMovement.h"

class SerialCtrl : public IMovement {
public:
    SerialCtrl() { };
    ~SerialCtrl() { };
    /* IMovement implementation */
    moveDirection getDirection();
};

