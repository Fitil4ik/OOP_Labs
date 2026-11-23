#pragma once
#include <windows.h>
#include "shape.h"

#define MY_SHAPE_ARRAY_SIZE 117

class Editor
{
public:
    virtual ~Editor() {}
    virtual void OnLBdown(HWND) = 0;
    virtual void OnLBup(HWND) = 0;
    virtual void OnMouseMove(HWND) = 0;
    virtual void OnPaint(HWND) = 0;
};

class ShapeEditor : public Editor
{
protected:
    long xstart, ystart, xend, yend;
    bool drawing;

    static Shape* pcshape[MY_SHAPE_ARRAY_SIZE];
    static int count;

    void AddShape(Shape* p);
public:
    ShapeEditor(void);
    void OnLBdown(HWND);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
    void OnPaint(HWND);

    static void ClearShapes();
};

class PointEditor : public ShapeEditor
{
public:
    void OnLBup(HWND);
};

class LineEditor : public ShapeEditor
{
public:
    void OnLBup(HWND);
    void OnMouseMove(HWND);
};

class RectEditor : public ShapeEditor
{
public:
    void OnLBup(HWND);
    void OnMouseMove(HWND);
};

class EllipseEditor : public ShapeEditor
{
public:
    void OnLBup(HWND);
    void OnMouseMove(HWND);
};