#include "shape.h"

void Shape::Set(long x1, long y1, long x2, long y2)
{
    xs1 = x1;
    ys1 = y1;
    xs2 = x2;
    ys2 = y2;
}

void PointShape::Show(HDC hdc)
{
    SetPixel(hdc, xs1, ys1, RGB(0, 0, 0));
}

void LineShape::Show(HDC hdc)
{
    MoveToEx(hdc, xs1, ys1, NULL);
    LineTo(hdc, xs2, ys2);
}

void RectShape::Show(HDC hdc)
{
    HBRUSH hBrush, hBrushOld;

    hBrush = CreateSolidBrush(RGB(192, 192, 192));
    hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

    Rectangle(hdc, xs1, ys1, xs2, ys2);

    SelectObject(hdc, hBrushOld);
    DeleteObject(hBrush);
}

void EllipseShape::Show(HDC hdc)
{
    HBRUSH hBrushOld;

    hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    Ellipse(hdc, xs1, ys1, xs2, ys2);

    SelectObject(hdc, hBrushOld);
}