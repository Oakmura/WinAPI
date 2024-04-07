#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;

    switch (msg)
    {
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);
        {
            // should be placed in WM_PAINT to repaint on validated
            TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15); // oneline. does not recognize null-terminate str
        }
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}