#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rt = { 100, 100, 400, 300 };
    const TCHAR* str = TEXT("님은 갔습니다. 아아 사랑하는 나의 님은 갔습니다. 푸른 산빛을"
        "깨치고 단풍나무 숲을 향하여 난 작은 길을 걸어서 차마 떨치고 갔습니다."
        "황금의 꽃같이 굳고 빛나던 옛 맹세는 차디찬 티끌이 되어 한숨의 미풍에 "
        "날아갔습니다.");

    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK); // -1 means str is null-terminated
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}