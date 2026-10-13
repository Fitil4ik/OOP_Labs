#include "Lab1-2.h"
#include "resource.h"

static int* g_outValue_MOD2;
static int g_currentPos_MOD2 = 1;

static INT_PTR CALLBACK Work2DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {
        HWND hScroll = GetDlgItem(hDlg, IDC_SCROLLBAR_MOD2);
        SetScrollRange(hScroll, SB_CTL, 1, 100, TRUE);
        SetScrollPos(hScroll, SB_CTL, 1, TRUE);
        SetDlgItemInt(hDlg, IDC_STATIC_MOD2, 1, FALSE);
        g_currentPos_MOD2 = 1;
        return (INT_PTR)TRUE;
    }
    case WM_HSCROLL: {
        HWND hScroll = (HWND)lParam;
        int pos = GetScrollPos(hScroll, SB_CTL);
        switch (LOWORD(wParam)) {
        case SB_LINELEFT: pos -= 1; break;
        case SB_LINERIGHT: pos += 1; break;
        case SB_PAGELEFT: pos -= 10; break;
        case SB_PAGERIGHT: pos += 10; break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK: pos = HIWORD(wParam); break;
        }
        if (pos < 1) pos = 1;
        if (pos > 100) pos = 100;

        SetScrollPos(hScroll, SB_CTL, pos, TRUE);
        SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos, FALSE);
        g_currentPos_MOD2 = pos;
        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            *g_outValue_MOD2 = g_currentPos_MOD2;
            EndDialog(hDlg, 1);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int Func_MOD2(HWND hWnd, int* outValue) {
    g_outValue_MOD2 = outValue;
    HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
    return (int)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_MOD2), hWnd, Work2DlgProc);
}