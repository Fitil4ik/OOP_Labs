#pragma once
#include "shape.h"

#define MY_SHAPE_ARRAY_SIZE 116

class MyEditor
{
private:
    Shape** pshape;
    int count;
    Shape* pCurrentShape;
    long xstart, ystart, xend, yend;
    bool isDrawing;
    HWND hwndToolBar;

public:
    MyEditor();
    ~MyEditor();

    void Start(Shape* pShape);
    void OnLBdown(HWND hWnd);
    void OnLBup(HWND hWnd);
    void OnMouseMove(HWND hWnd);
    void OnPaint(HWND hWnd, HDC hdc);
    void OnCreate(HWND hWnd, HINSTANCE hInst);
    void OnSize(HWND hWnd);
    void OnNotify(HWND hWnd, LPARAM lParam);
};