#pragma once
#include "Figure.h"

class Circle : public Figure
{
protected:
	float unnecessaryPart; // параметр, отвечающий за удаление ненужной части круга (например, 1/4 или 1/8 и т.д.)
public:
	Circle(HWND hWnd, int length, int speed, int rotAngle, Direction direction, float unnecessaryPart, COLORREF color);
	void draw(int Reg);
};

