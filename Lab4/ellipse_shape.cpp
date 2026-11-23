#include "framework.h"
#include "ellipse_shape.h"

void EllipseShape::Show(HDC hdc)
{
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
    Ellipse(hdc, xs1, ys1, xs2, ys2);
    SelectObject(hdc, hOldBrush);
}