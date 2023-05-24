#include "Figure.h"
#define _USE_MATH_DEFINES
#include <cmath>

Figure::Figure(HWND hWnd, int length, int rotAngle, int speed, Direction direction, COLORREF color)
{
    this->hWnd = hWnd;
    this->length = length;
    this->speed = speed;
    this->rotAngle = rotAngle;
    this->direction = direction;
    this->color = color;
    

    rotAngle = 0;
    N_Reg = 1;
    RECT rect;
    GetClientRect(hWnd, &rect);

    x = rect.right / 2;
    y = rect.bottom / 2;
}

void Figure::step()
{
    rotAngle += speed;
    if (rotAngle >= 360)
    {
        rotAngle -= 360;
    }

    RECT rect;
    GetClientRect(hWnd, &rect);

    if (direction == HORIZONTAL)
    {
        x += speed * N_Reg;
        if (N_Reg == 1) {
            if (x + length >= rect.right) {
                N_Reg = -1;
            }

        }
        else {
            if (x - length <= 0) {
                N_Reg = 1;
            }
        }
    }

    if (direction == VERTICAL)
    {
        y += speed * N_Reg;
        if (N_Reg == 1) {
            if (y + length >= rect.bottom) {
                N_Reg = -1;
            }
        }
        else {
            if (y - length <= 0) {
                N_Reg = 1;
            }
        }
    }
}

HPEN Figure::CreateAndGetPen(int Reg, COLORREF color)
{
    return (Reg == 1) ? CreatePen(PS_SOLID, 1, color) : CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}



MyRavPriamougTreug::MyRavPriamougTreug(HWND hWnd,int length, int speed, int rotAngle, Direction direction, COLORREF col) :
    Figure(hWnd, length, speed, rotAngle, direction, col) {

    p = new POINT[N];

    double A = rotAngle * M_PI / 180;
    double A1 = 2 * M_PI / N;

    for (int i = 0; i < N; i++, A += A1) {
        //A+=A1;
        p[i].x = x + length * cos(A);
        p[i].y = y - length * sin(A);
    }
}

void MyRavPriamougTreug::step() {
    Figure::step();

    double A = rotAngle * M_PI / 180;
    double A1 = 2 * M_PI / N;

    for (int i = 0; i < N; i++, A += A1) {
        //A+=A1;
        p[i].x = x + length * cos(A);
        p[i].y = y - length * sin(A);
    }
}

void MyRavPriamougTreug::draw(int Reg) {
    HPEN pen;

    if (Reg == 1) {
        pen = CreatePen(PS_SOLID, 1, color);
    }
    else {
        pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    }

    HDC hdc;

    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, p[0].x, p[0].y, 0);


    for (int i = 1; i < N; i++) {
        LineTo(hdc, p[i].x, p[i].y);
    }

    LineTo(hdc, p[0].x, p[0].y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}

MyPolygon::MyPolygon(HWND hWnd, int length, int speed, int rotAngle, Direction direction, COLORREF col, int N) :
    Figure(hWnd, length, speed, rotAngle, direction, col)
{
    this->N = N;
    p = new POINT[N];

    double A = rotAngle * M_PI / 180;
    double A1 = 2 * M_PI / N;

    for (int i = 0; i < N; i++, A += A1) {
        //A+=A1;
        p[i].x = x + length * cos(A);
        p[i].y = y - length * sin(A);
    }
}

void MyPolygon::step() {
    Figure::step();

    double A = rotAngle * M_PI / 180;
    double A1 = 2 * M_PI / N;

    for (int i = 0; i < N; i++, A += A1) {
        //A+=A1;
        p[i].x = x + length * cos(A);
        p[i].y = y - length * sin(A);
    }
}

void MyPolygon::draw(int Reg) {
    HPEN pen;

    if (Reg == 1) {
        pen = CreatePen(PS_SOLID, 1, color);
    }
    else {
        pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    }

    HDC hdc;

    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, p[0].x, p[0].y, 0);

    for (int i = 1; i < N; i++) {
        LineTo(hdc, p[i].x, p[i].y);
    }

    LineTo(hdc, p[0].x, p[0].y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}
