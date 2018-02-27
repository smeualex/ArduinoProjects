#pragma once

#include "Point.h"

class Board {
private:
    unsigned char idx;
    unsigned char w;
    unsigned char h;
    Point foodPosition; // TODO: move from here

public:
    Board()
    {
        Board(0, 8, 8);
    }
    Board(unsigned char _idx, unsigned char _w, unsigned char _h);
    ~Board();

    void setW(unsigned char _w) { w = _w; }
    void setH(unsigned char _h) { h = _h; }
    inline bool isPositionInside(char x, char y);
};

