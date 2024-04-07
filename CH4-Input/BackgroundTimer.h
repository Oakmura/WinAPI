#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    int i;

    switch (msg)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 1000, NULL); // timer id = 1, WM_TIMER every 1000 (1 sec), optional callback func
        SetTimer(hWnd, 2, 5000, NULL);
        SendMessage(hWnd, WM_TIMER, 1, 0); // (msg, timer id). send msg to display time right after timer creation
        return 0;
    case WM_TIMER:
        hdc = GetDC(hWnd);
        {
            for (i = 0; i < 1000; ++i)
            {
                SetPixel(hdc, rand() % 500, rand() % 400, RGB(rand() % 256, rand() % 256, rand() % 256));
            }
        }
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);
        {
            Ellipse(hdc, LOWORD(lParam) - 10, HIWORD(lParam) - 10, LOWORD(lParam) + 10, HIWORD(lParam) + 10);
        }
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_DESTROY: // alt + f4
        KillTimer(hWnd, 1); // (HWND, id). good to kill because timer is system resource
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}