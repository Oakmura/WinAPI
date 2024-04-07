#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        if (MessageBox(hWnd, TEXT("Body"), TEXT("Caption"), MB_YESNO) == IDYES)
        {
            // ���� ���
        }
        else
        {
            // ���� ����
            MessageBeep(0); // 0 is MB_OK
        }
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}