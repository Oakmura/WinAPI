#pragma once

#include <windows.h>

#include "resource.h"

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBitmap)
{
    HDC memDC;
    HBITMAP oldBitmap;
    int bx, by;
    BITMAP bitmapInfo;

    memDC = CreateCompatibleDC(hdc);
    oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);
    bx = bitmapInfo.bmWidth;
    by = bitmapInfo.bmHeight;

    BitBlt(hdc, x, y, bx, by, memDC, 0, 0, SRCCOPY); // (destDC, xDest, yDest, width, height, srcDC, xSrc, ySrc, rop);

    StretchBlt(hdc, x+bx, y+by, bx*2, by*2, memDC, 0, 0, bx, by, SRCCOPY); // stretches or compresses

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc; // screen DC
    PAINTSTRUCT ps;
    static HBITMAP myBitmap;

    switch (msg)
    {
    case WM_CREATE:
        myBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            DrawBitmap(hdc, 0, 0, myBitmap);
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        DeleteObject(myBitmap);
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}