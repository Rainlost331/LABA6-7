#include "Rhomb.h"

Rhomb::Rhomb(HWND hWnd, int length, int speed, int rotAngle, Direction direction, COLORREF color) :
    Figure(hWnd, length, speed, rotAngle, direction, color)
{
    double A = rotAngle * M_PI / 180;
    double A1 = 2 * M_PI / 4;

    for (int i = 0; i < 4; i++, A += A1) {
        //A+=A1;
        if (i == 0) {
            // RIGHT
            points[i].x = x + length * cos(A);
            points[i].y = y - length * sin(A);
        }

        if (i == 1) {
            // TOP
            points[i].x = x + length * cos(A);
            points[i].y = y - length * sin(A);
        }

        if (i == 2) {
            // LEFT
            points[i].x = x + length * cos(A);
            points[i].y = y - length * sin(A);
        }

        if (i == 3) {
            // BOTTOM
            points[i].x = x + length * cos(A);
            points[i].y = y - length * sin(A);
        }
    }
}

void Rhomb::step()
{
    Figure::step();

    double A = rotAngle * M_PI / 180;
    double A1 = 2 * M_PI / 4;

    for (int i = 0; i < 4; i++, A += A1) {
        //A+=A1;
        if (i == 0) {
            // RIGHT
            points[i].x = x + (length / 2) * cos(A);
            points[i].y = y - (length / 2) * sin(A);
        }

        if (i == 1) {
            // TOP
            points[i].x = x + length * cos(A);
            points[i].y = y - length * sin(A);
        }

        if (i == 2) {
            // LEFT
            points[i].x = x + (length / 2) * cos(A);
            points[i].y = y - (length / 2) * sin(A);
        }

        if (i == 3) {
            // BOTTOM
            points[i].x = x + length * cos(A);
            points[i].y = y - length * sin(A);
        }
    }
}

void Rhomb::draw(int Reg)
{
    HPEN pen = CreateAndGetPen(Reg, color);
    HDC hdc = GetDC(hWnd);

    SelectObject(hdc, pen);
    MoveToEx(hdc, points[0].x, points[0].y, 0);

    for (int i = 1; i < 4; i++) {
        LineTo(hdc, points[i].x, points[i].y);
    }

    LineTo(hdc, points[0].x, points[0].y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}
