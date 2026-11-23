#pragma once
#include "line_shape.h"
#include "rect_shape.h"

class CubeShape : public LineShape, public RectShape
{
public:
    CubeShape();
    void Show(HDC hdc) override;
    Shape* Duplicate() override { return new CubeShape(); }
};