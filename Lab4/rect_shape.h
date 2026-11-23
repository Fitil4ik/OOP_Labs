#pragma once
#include "shape.h"

class RectShape : public virtual Shape
{
protected:
    bool isFilled = true;
public:
    void Show(HDC hdc) override;
    Shape* Duplicate() override { return new RectShape(); }
};