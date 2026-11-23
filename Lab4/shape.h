#pragma once
#include <windows.h>

class Shape
{
protected:
    long xs1, ys1, xs2, ys2;
public:
    virtual ~Shape() {}
    void Set(long x1, long y1, long x2, long y2);
    virtual void Show(HDC hdc) = 0;
    virtual void ShowRubber(HDC hdc);
    virtual Shape* Duplicate() = 0;
};