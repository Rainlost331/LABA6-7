#include "Circle.h"

Circle::Circle(HWND hWnd, int length, int speed, int rotAngle, Direction direction, float unnecessaryPart, COLORREF color) :
    Figure(hWnd, length, speed, rotAngle, direction, color)
{
    this->unnecessaryPart = unnecessaryPart;
}

void Circle::draw(int Reg)
{
    HPEN pen = CreateAndGetPen(Reg, color);
    HDC hdc;

    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, x, y, 0);
    AngleArc(hdc, x, y, length, rotAngle, 360 - 360 * unnecessaryPart);
    LineTo(hdc, x, y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}
