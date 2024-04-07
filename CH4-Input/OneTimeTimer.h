#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static TCHAR str[128];

    switch (msg)
    {
    case WM_LBUTTONDOWN:
        lstrcpy(str, TEXT("¿ÞÂÊ ¹öÆ°À» ´­·¶½À´Ï´Ù."));
        InvalidateRect(hWnd, NULL, TRUE);
        SetTimer(hWnd, 1, 3000, NULL); // set timer upon events
        return 0;
    case WM_TIMER:
        KillTimer(hWnd, 1); // do something... when time is up
        lstrcpy(str, TEXT(""));
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            TextOut(hdc, 10, 10, str, lstrlen(str));
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}