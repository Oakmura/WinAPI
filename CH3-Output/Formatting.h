#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static TCHAR str[256];

    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            SetTextAlign(hdc, TA_CENTER); // default is (TOP | LEFT)
            TextOut(hdc, 200, 60, TEXT("Beautiful Korea"), 15); // 15 = strlen
            TextOut(hdc, 200, 80, TEXT("is My"), 5);
            TextOut(hdc, 200, 100, TEXT("Lovely Home Country"), 19);

            TextOut(hdc, 400, 400, str, lstrlen(str));

            SetTextAlign(hdc, TA_UPDATECP); // write + update on CP (current point). ignores x,y param in TextOut
            TextOut(hdc, 300, 60, TEXT("One "), 4); // 15 = strlen
            TextOut(hdc, 300, 80, TEXT("Two "), 4);
            TextOut(hdc, 300, 100, TEXT("Three"), 5);
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}