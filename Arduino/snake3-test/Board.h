#pragma once
class Board {
private:
    unsigned char w;
    unsigned char h;

public:
    Board();
    Board(unsigned char _w, unsigned char _h);
    ~Board();

    void setW(unsigned char _w) { w = _w; }
    void setH(unsigned char _h) { h = _h; }
    inline bool isPositionInside(char x, char y);
};

