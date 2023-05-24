#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Figure.h"

class Line : public Figure
{
protected:
    int x1, y1, x2, y2;
public:
    Line(HWND hWnd, int length, int speed, int rotAngle, Direction direction, COLORREF color);
    void step();
    void draw(int Reg);
};

