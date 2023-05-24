#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "Figure.h"

class Rhomb : public Figure
{
protected:
	POINT points[4];
public:
	Rhomb(HWND hWnd, int length, int speed, int rotAngle, Direction direction, COLORREF color);
	void step();
	void draw(int Reg);
};

