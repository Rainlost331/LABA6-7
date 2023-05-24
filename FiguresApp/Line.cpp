#include "Line.h"

Line::Line(HWND hWnd, int length, int speed, int rotAngle, Direction direction, COLORREF color) :
    Figure(hWnd, length, rotAngle, speed, direction, color)
{
    double A = rotAngle * M_PI / 180;
    x1 = x + length * cos(A);
    y1 = y - length * sin(A);
    x2 = x - length * cos(A);
    y2 = y + length * sin(A);
}

void Line::step() {
    Figure::step();

    double A = rotAngle * M_PI / 180;
    x1 = x + length * cos(A);
    y1 = y - length * sin(A);
    x2 = x - length * cos(A);
    y2 = y + length * sin(A);
}

void Line::draw(int Reg) {
    HPEN pen = CreateAndGetPen(Reg, color);
    HDC hdc;

    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, x1, y1, 0);
    LineTo(hdc, x2, y2);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}