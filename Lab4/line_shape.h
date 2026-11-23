#pragma once
#include "shape.h"

class LineShape : public virtual Shape
{
public:
    void Show(HDC hdc) override;
    Shape* Duplicate() override { return new LineShape(); }
};