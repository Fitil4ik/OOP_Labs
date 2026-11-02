#include "shape_editor.h"
#include "editor.h"
#include "shape.h"

ShapeObjectsEditor::ShapeObjectsEditor(void)
{
    pse = NULL;
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
    if (pse) delete pse;
    ShapeEditor::ClearShapes();
}

void ShapeObjectsEditor::StartPointEditor()
{
    if (pse) delete pse;
    pse = new PointEditor;
}

void ShapeObjectsEditor::StartLineEditor()
{
    if (pse) delete pse;
    pse = new LineEditor;
}

void ShapeObjectsEditor::StartRectEditor()
{
    if (pse) delete pse;
    pse = new RectEditor;
}

void ShapeObjectsEditor::StartEllipseEditor()
{
    if (pse) delete pse;
    pse = new EllipseEditor;
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd)
{
    if (pse) pse->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd)
{
    if (pse)
    {
        pse->OnLBup(hWnd);
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
    if (pse) pse->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnPaint(HWND hWnd)
{
    if (pse)
        pse->OnPaint(hWnd);
    else
    {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
}

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
    if (pse) pse->OnInitMenuPopup(hWnd, wParam);
}