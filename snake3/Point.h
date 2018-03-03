#pragma once

#include "Arduino.h"

class Point 
{
public:
    Point()                                 { x = 255; y = 255;                   }
    Point(byte pX, byte pY)                 { x = pX; y = pY;                     }
    
    Point& operator=(Point p)               { x = p.x; y = p.y; return *this;     }
    bool operator==(const Point &p) const   { return ((x == p.x) && (y == p.y) ); }
    bool operator!=(const Point &p) const   { return !(*this == p);               }

    byte x;
    byte y;
};

