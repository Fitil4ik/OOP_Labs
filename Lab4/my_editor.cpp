#include "framework.h"
#include "Resource.h"
#include <commctrl.h>
#include "my_editor.h"

MyEditor::MyEditor()
{
    pshape = new Shape * [MY_SHAPE_ARRAY_SIZE];
    for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++)
    {
        pshape[i] = nullptr;
    }
    count = 0;
    pCurrentShape = nullptr;
    isDrawing = false;
    xstart = ystart = xend = yend = 0;
    hwndToolBar = NULL;
}

MyEditor::~MyEditor()
{
    for (int i = 0; i < count; i++)
    {
        delete pshape[i];
    }
    delete[] pshape;

    if (pCurrentShape)
    {
        delete pCurrentShape;
    }
}

void MyEditor::Start(Shape* pShape)
{
    if (pCurrentShape)
    {
        delete pCurrentShape;
    }
    pCurrentShape = pShape;
}

void MyEditor::OnLBdown(HWND hWnd)
{
    if (!pCurrentShape) return;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    xstart = xend = pt.x;
    ystart = yend = pt.y;
    isDrawing = true;
}

void MyEditor::OnMouseMove(HWND hWnd)
{
    if (!isDrawing || !pCurrentShape) return;

    HDC hdc = GetDC(hWnd);

    pCurrentShape->Set(xstart, ystart, xend, yend);
    pCurrentShape->ShowRubber(hdc);

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xend = pt.x;
    yend = pt.y;
    pCurrentShape->Set(xstart, ystart, xend, yend);
    pCurrentShape->ShowRubber(hdc);
    ReleaseDC(hWnd, hdc);
}

void MyEditor::OnLBup(HWND hWnd)
{
    if (!isDrawing || !pCurrentShape) return;

    isDrawing = false;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xend = pt.x;
    yend = pt.y;

    if (count < MY_SHAPE_ARRAY_SIZE)
    {
        Shape* pNewShape = pCurrentShape->Duplicate();
        pNewShape->Set(xstart, ystart, xend, yend);
        pshape[count++] = pNewShape;
    }
    InvalidateRect(hWnd, NULL, TRUE);
}

void MyEditor::OnPaint(HWND hWnd, HDC hdc)
{
    for (int i = 0; i < count; i++)
    {
        if (pshape[i])
        {
            pshape[i]->Show(hdc);
        }
    }
}

void MyEditor::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    TBBUTTON tbb[6];
    ZeroMemory(tbb, sizeof(tbb));
    int commands[6] = { IDM_POINT, IDM_LINE, IDM_RECT, IDM_ELLIPSE, IDM_LINEOO, IDM_CUBE };
    for (int i = 0; i < 6; i++)
    {
        tbb[i].iBitmap = i;
        tbb[i].fsState = TBSTATE_ENABLED;
        tbb[i].fsStyle = TBSTYLE_BUTTON;
        tbb[i].idCommand = commands[i];
    }
    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        1, 6, hInst, IDB_TOOLBAR1, tbb, 6,
        24, 24, 24, 24, sizeof(TBBUTTON));
}

void MyEditor::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc);
        GetWindowRect(hwndToolBar, &rw);
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void MyEditor::OnNotify(HWND hWnd, LPARAM lParam)
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
        case IDM_LINEOO:
            lstrcpy(lpttt->szText, L"Лінія з кружечками");
            break;
        case IDM_CUBE:
            lstrcpy(lpttt->szText, L"Куб");
            break;
        }
    }
}