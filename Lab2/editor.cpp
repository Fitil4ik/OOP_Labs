#include "editor.h"
#include "resource.h"
#include <cstdlib>

Shape* ShapeEditor::pcshape[MY_SHAPE_ARRAY_SIZE];
int ShapeEditor::count = 0;

ShapeEditor::ShapeEditor(void)
{
    xstart = ystart = xend = yend = 0;
    drawing = false;
    toolId = 0;
}

void ShapeEditor::AddShape(Shape* p)
{
    if (count < MY_SHAPE_ARRAY_SIZE)
        pcshape[count++] = p;
    else
        delete p;
}

void ShapeEditor::ClearShapes()
{
    for (int i = 0; i < count; i++)
    {
        delete pcshape[i];
        pcshape[i] = NULL;
    }
    count = 0;
}

void ShapeEditor::OnLBdown(HWND hWnd)
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xstart = xend = pt.x;
    ystart = yend = pt.y;
    drawing = true;
}

void ShapeEditor::OnLBup(HWND hWnd)
{
    drawing = false;
}

void ShapeEditor::OnMouseMove(HWND hWnd)
{
}

void ShapeEditor::OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc;

    hdc = BeginPaint(hWnd, &ps);
    for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++)
        if (pcshape[i])
            pcshape[i]->Show(hdc);
    EndPaint(hWnd, &ps);
}

void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
    HMENU hMenu, hSubMenu;

    hMenu = GetMenu(hWnd);
    hSubMenu = GetSubMenu(hMenu, 1);
    if ((HMENU)wParam == hSubMenu)
    {
        CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
        CheckMenuItem(hSubMenu, toolId, MF_CHECKED);
    }
}

PointEditor::PointEditor(void)
{
    toolId = IDM_POINT;
}

void PointEditor::OnLBup(HWND hWnd)
{
    if (!drawing) return;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    Shape* p = new PointShape;
    p->Set(pt.x, pt.y, pt.x, pt.y);
    AddShape(p);
    drawing = false;
}

LineEditor::LineEditor(void)
{
    toolId = IDM_LINE;
}

void LineEditor::OnMouseMove(HWND hWnd)
{
    if (!drawing) return;

    POINT pt;
    HPEN hPen, hPenOld;
    HDC hdc;

    hdc = GetDC(hWnd);
    SetROP2(hdc, R2_NOTXORPEN);
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    hPenOld = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, xstart, ystart, NULL);
    LineTo(hdc, xend, yend);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xend = pt.x;
    yend = pt.y;

    MoveToEx(hdc, xstart, ystart, NULL);
    LineTo(hdc, xend, yend);

    SelectObject(hdc, hPenOld);
    DeleteObject(hPen);
    ReleaseDC(hWnd, hdc);
}

void LineEditor::OnLBup(HWND hWnd)
{
    if (!drawing) return;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    Shape* p = new LineShape;
    p->Set(xstart, ystart, pt.x, pt.y);
    AddShape(p);
    drawing = false;
}

RectEditor::RectEditor(void)
{
    toolId = IDM_RECT;
}

void RectEditor::OnMouseMove(HWND hWnd)
{
    if (!drawing) return;

    POINT pt;
    HPEN hPen, hPenOld;
    HBRUSH hBrushOld;
    HDC hdc;

    hdc = GetDC(hWnd);
    SetROP2(hdc, R2_NOTXORPEN);
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    hPenOld = (HPEN)SelectObject(hdc, hPen);
    hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    Rectangle(hdc, xstart, ystart, xend, yend);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xend = pt.x;
    yend = pt.y;

    Rectangle(hdc, xstart, ystart, xend, yend);

    SelectObject(hdc, hBrushOld);
    SelectObject(hdc, hPenOld);
    DeleteObject(hPen);
    ReleaseDC(hWnd, hdc);
}

void RectEditor::OnLBup(HWND hWnd)
{
    if (!drawing) return;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    Shape* p = new RectShape;
    p->Set(xstart, ystart, pt.x, pt.y);
    AddShape(p);
    drawing = false;
}

EllipseEditor::EllipseEditor(void)
{
    toolId = IDM_ELLIPSE;
}

void EllipseEditor::OnMouseMove(HWND hWnd)
{
    if (!drawing) return;

    POINT pt;
    HPEN hPen, hPenOld;
    HBRUSH hBrushOld;
    HDC hdc;
    long dx, dy;

    hdc = GetDC(hWnd);
    SetROP2(hdc, R2_NOTXORPEN);
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    hPenOld = (HPEN)SelectObject(hdc, hPen);
    hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    dx = labs(xend - xstart);
    dy = labs(yend - ystart);
    Ellipse(hdc, xstart - dx, ystart - dy, xstart + dx, ystart + dy);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xend = pt.x;
    yend = pt.y;

    dx = labs(xend - xstart);
    dy = labs(yend - ystart);
    Ellipse(hdc, xstart - dx, ystart - dy, xstart + dx, ystart + dy);

    SelectObject(hdc, hBrushOld);
    SelectObject(hdc, hPenOld);
    DeleteObject(hPen);
    ReleaseDC(hWnd, hdc);
}

void EllipseEditor::OnLBup(HWND hWnd)
{
    if (!drawing) return;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    long dx = labs(pt.x - xstart);
    long dy = labs(pt.y - ystart);

    Shape* p = new EllipseShape;
    p->Set(xstart - dx, ystart - dy, xstart + dx, ystart + dy);
    AddShape(p);
    drawing = false;
}