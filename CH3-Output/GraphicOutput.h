#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            SetPixel(hdc, 10, 10, RGB(255, 0, 0));
            MoveToEx(hdc, 50, 50, NULL);
            LineTo(hdc, 300, 90);
            Rectangle(hdc, 50, 100, 200, 180);
            Ellipse(hdc, 220, 100, 400, 200);
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}