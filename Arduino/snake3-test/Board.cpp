#include "Board.h"



Board::Board(unsigned char _w, unsigned char _h)
{
    w = _w;
    h = _h;
}

Board::Board():Board(0, 0) { }

Board::~Board()
{ }

inline bool Board::isPositionInside(char x, char y)
{
    return ( (0<=x && x<=w) && (0 <= y && y <= h) );
}
