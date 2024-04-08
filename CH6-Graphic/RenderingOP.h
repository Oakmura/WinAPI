#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static int sx, sy, oldx, oldy;
    static BOOL bNowDraw = FALSE;

    switch (msg)
    {
    case WM_LBUTTONDOWN:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        oldx = sx;
        oldy = sy;
        bNowDraw = TRUE;
        return 0;
    case WM_MOUSEMOVE:
        if (bNowDraw)
        {
            hdc = GetDC(hWnd);
            {
                SetROP2(hdc, R2_NOT);
                MoveToEx(hdc, sx, sy, NULL);
                LineTo(hdc, oldx, oldy);
                oldx = LOWORD(lParam);
                oldy = HIWORD(lParam);
                MoveToEx(hdc, sx, sy, NULL);
                LineTo(hdc, oldx, oldy);
            }
            ReleaseDC(hWnd, hdc);    
        }
        return 0;
    case WM_LBUTTONUP:
        bNowDraw = FALSE;
        hdc = GetDC(hWnd);
        {
            MoveToEx(hdc, sx, sy, NULL);
            LineTo(hdc, oldx, oldy);
        }
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}