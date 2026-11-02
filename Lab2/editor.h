#pragma once
#include <windows.h>
#include "shape.h"

#define MY_SHAPE_ARRAY_SIZE 116

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
    int toolId;

    static Shape* pcshape[MY_SHAPE_ARRAY_SIZE];
    static int count;

    void AddShape(Shape* p);
public:
    ShapeEditor(void);
    void OnLBdown(HWND);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
    void OnPaint(HWND);
    void OnInitMenuPopup(HWND, WPARAM);

    static void ClearShapes();
};

class PointEditor : public ShapeEditor
{
public:
    PointEditor(void);
    void OnLBup(HWND);
};

class LineEditor : public ShapeEditor
{
public:
    LineEditor(void);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
};

class RectEditor : public ShapeEditor
{
public:
    RectEditor(void);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
};

class EllipseEditor : public ShapeEditor
{
public:
    EllipseEditor(void);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
};