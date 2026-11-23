#include "shape_editor.h"
#include "editor.h"
#include "shape.h"
#include "resource.h"
#include <commctrl.h>

ShapeObjectsEditor::ShapeObjectsEditor(void)
{
    pse = NULL;
    hwndToolBar = NULL;
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
    if (pse) delete pse;
    ShapeEditor::ClearShapes();
}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd)
{
    if (pse) delete pse;
    pse = new PointEditor;
    SetWindowTextW(hWnd, L"Режим вводу крапки");
}

void ShapeObjectsEditor::StartLineEditor(HWND hWnd)
{
    if (pse) delete pse;
    pse = new LineEditor;
    SetWindowTextW(hWnd, L"Режим вводу лінії");
}

void ShapeObjectsEditor::StartRectEditor(HWND hWnd)
{
    if (pse) delete pse;
    pse = new RectEditor;
    SetWindowTextW(hWnd, L"Режим вводу прямокутника");
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd)
{
    if (pse) delete pse;
    pse = new EllipseEditor;
    SetWindowTextW(hWnd, L"Режим вводу еліпса");
}

void ShapeObjectsEditor::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    TBBUTTON tbb[4];
    ZeroMemory(tbb, sizeof(tbb));

    tbb[0].iBitmap = 0;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = IDM_POINT;

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = IDM_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = IDM_RECT;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = IDM_ELLIPSE;

    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        1, 4, hInst, IDB_TOOLBAR1, tbb, 4,
        24, 24, 24, 24, sizeof(TBBUTTON));
}

void ShapeObjectsEditor::OnSize(HWND hWnd)
{
    RECT rc, rw;

    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc);
        GetWindowRect(hwndToolBar, &rw);
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void ShapeObjectsEditor::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;

    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case IDM_POINT:
            lstrcpy(lpttt->szText, L"Крапка");
            break;
        case IDM_LINE:
            lstrcpy(lpttt->szText, L"Лінія");
            break;
        case IDM_RECT:
            lstrcpy(lpttt->szText, L"Прямокутник");
            break;
        case IDM_ELLIPSE:
            lstrcpy(lpttt->szText, L"Еліпс");
            break;
        }
    }
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