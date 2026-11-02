#pragma once
#include <windows.h>

class ShapeEditor;

class ShapeObjectsEditor
{
private:
    ShapeEditor *pse;
public:
    ShapeObjectsEditor(void);
    ~ShapeObjectsEditor();

    void StartPointEditor();
    void StartLineEditor();
    void StartRectEditor();
    void StartEllipseEditor();

    void OnLBdown(HWND);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
    void OnPaint(HWND);
    void OnInitMenuPopup(HWND, WPARAM);
};