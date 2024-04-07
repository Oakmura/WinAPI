#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    SYSTEMTIME st;
    static TCHAR sTime[128];
    static RECT rt = { 100, 100, 400, 120 }; // for minimizing screen flickering

    switch (msg)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 1000, NULL); // timer id = 1, WM_TIMER every 1000 (1 sec), optional callback func
        SetTimer(hWnd, 2, 5000, NULL);
        SendMessage(hWnd, WM_TIMER, 1, 0); // (msg, timer id). send msg to display time right after timer creation
        return 0;
    case WM_TIMER:
        switch (wParam) // wParam for timer id
        {
        case 1:
            GetLocalTime(&st);
            wsprintf(sTime, TEXT("지금 시간은 %d.%d.%d입니다"), st.wHour, st.wMinute, st.wSecond);
            InvalidateRect(hWnd, &rt, TRUE);
            break;
        case 2:
            MessageBeep(0);
            break;
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            TextOut(hdc, 100, 100, sTime, lstrlen(sTime));
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        KillTimer(hWnd, 1); // (HWND, id). good to kill because timer is system resource
        KillTimer(hWnd, 2);
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}