#pragma once
#include "shape.h"

class PointShape : public Shape
{
public:
    void Show(HDC hdc) override;
    Shape* Duplicate() override { return new PointShape(); }
};