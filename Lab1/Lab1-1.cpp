#include "Lab1-1.h"
#include "resource.h"

static WCHAR* g_outText_MOD1;
static int g_maxLen_MOD1;

static INT_PTR CALLBACK Work1DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            GetDlgItemTextW(hDlg, IDC_EDIT1_MOD1, g_outText_MOD1, g_maxLen_MOD1);
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

int Func_MOD1(HWND hWnd, WCHAR* outText, int maxLen) {
    g_outText_MOD1 = outText;
    g_maxLen_MOD1 = maxLen;
    HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
    return (int)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_MOD1), hWnd, Work1DlgProc);
}