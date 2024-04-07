#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static RECT rt;

    switch (msg)
    {
    case WM_CREATE:
        // GetClientRect(hWnd, &rt); should be placed to accoodate window resize
        return 0;
    case WM_SIZE:
        GetClientRect(hWnd, &rt);
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            SetTextAlign(hdc, TA_CENTER);
            TextOut(hdc, rt.right / 2, rt.bottom / 2, TEXT("Center String"), 13);
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}