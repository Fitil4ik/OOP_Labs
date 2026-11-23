#include "framework.h"
#include "lineoo_shape.h"

void LineOOShape::Show(HDC hdc)
{
    long x1 = xs1, y1 = ys1, x2 = xs2, y2 = ys2;
    const long r = 8;

    LineShape::Show(hdc);

    Set(x1 - r, y1 - r, x1 + r, y1 + r);
    EllipseShape::Show(hdc);

    Set(x2 - r, y2 - r, x2 + r, y2 + r);
    EllipseShape::Show(hdc);

    Set(x1, y1, x2, y2);
}