#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static int x, y;
    static BOOL bNowDraw = FALSE;

    switch (msg)
    {
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        bNowDraw = true;
        return 0;
    case WM_LBUTTONUP:
        bNowDraw = FALSE;
        return 0;
    case WM_MOUSEMOVE:
        if (bNowDraw == TRUE)
        {
            hdc = GetDC(hWnd);
            {
                MoveToEx(hdc, x, y, NULL);
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                LineTo(hdc, x, y);
            }
            ReleaseDC(hWnd, hdc);
        }
        return 0;
    case WM_LBUTTONDBLCLK:
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}