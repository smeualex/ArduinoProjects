#include "Board.h"


Board::Board(unsigned char _w, unsigned char _h, unsigned char _idx)
{
    idx = _idx;
    w = _w;
    h = _h;
}

Board::~Board()
{ }

inline bool Board::isPositionInside(char x, char y)
{
    return ( (0<=x && x<=w) && (0 <= y && y <= h) );
}