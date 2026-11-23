#pragma once
#include <windows.h>

class ShapeEditor;

class ShapeObjectsEditor
{
private:
    ShapeEditor* pse;
    HWND hwndToolBar;
public:
    ShapeObjectsEditor(void);
    ~ShapeObjectsEditor();

    void StartPointEditor(HWND hWnd);
    void StartLineEditor(HWND hWnd);
    void StartRectEditor(HWND hWnd);
    void StartEllipseEditor(HWND hWnd);
    void OnCreate(HWND hWnd, HINSTANCE hInst);
    void OnSize(HWND hWnd);
    void OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
    void OnLBdown(HWND);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
    void OnPaint(HWND);
};