#include "framework.h"
#include "cube_shape.h"

CubeShape::CubeShape()
{
    isFilled = false;
}

void CubeShape::Show(HDC hdc)
{
    long x1 = xs1, y1 = ys1, x2 = xs2, y2 = ys2;
    long dx = x2 - x1;
    long dy = y2 - y1;

    long fLeft = x1 - dx;
    long fTop = y1 - dy;
    long fRight = x1 + dx;
    long fBottom = y1 + dy;

    long shiftX = dx / 2;
    long shiftY = -dy / 2;

    RectShape::Show(hdc);

    Set(x1 + shiftX, y1 + shiftY, x2 + shiftX, y2 + shiftY);
    RectShape::Show(hdc);

    Set(fLeft, fTop, fLeft + shiftX, fTop + shiftY);
    LineShape::Show(hdc);

    Set(fRight, fTop, fRight + shiftX, fTop + shiftY);
    LineShape::Show(hdc);

    Set(fRight, fBottom, fRight + shiftX, fBottom + shiftY);
    LineShape::Show(hdc);

    Set(fLeft, fBottom, fLeft + shiftX, fBottom + shiftY);
    LineShape::Show(hdc);

    Set(x1, y1, x2, y2);
}