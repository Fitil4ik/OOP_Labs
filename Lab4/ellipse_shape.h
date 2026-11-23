#pragma once
#include "shape.h"

class EllipseShape : public virtual Shape
{
public:
    void Show(HDC hdc) override;
    Shape* Duplicate() override { return new EllipseShape(); }
};