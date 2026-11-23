#include "framework.h"
#include "point_shape.h"

void PointShape::Show(HDC hdc)
{
    SetPixel(hdc, xs1, ys1, RGB(0, 0, 0));
    SetPixel(hdc, xs1 + 1, ys1, RGB(0, 0, 0));
    SetPixel(hdc, xs1, ys1 + 1, RGB(0, 0, 0));
    SetPixel(hdc, xs1 + 1, ys1 + 1, RGB(0, 0, 0));
}