#include "framework.h"
#include "rect_shape.h"

void RectShape::Show(HDC hdc)
{
    long dx = xs2 - xs1;
    long dy = ys2 - ys1;

    if (isFilled)
    {
        HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 128));
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        Rectangle(hdc, xs1 - dx, ys1 - dy, xs1 + dx, ys1 + dy);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }
    else
    {
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
        Rectangle(hdc, xs1 - dx, ys1 - dy, xs1 + dx, ys1 + dy);
        SelectObject(hdc, hOldBrush);
    }
}