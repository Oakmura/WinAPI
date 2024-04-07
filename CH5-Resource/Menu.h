#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_FILE_MENU1:
            MessageBox(hWnd, TEXT("첫번쨰 메뉴를 선택했습니다"), TEXT("Menu Demo"), MB_OK);
            break;
        case ID_FILE_MENU2:
            MessageBox(hWnd, TEXT("두번쨰 메뉴를 선택했습니다"), TEXT("Menu Demo"), MB_OK);
            break;
        case ID_FILE_EXIT:
            DestroyWindow(hWnd);
            break;
        }
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}