#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc; // screen DC
    PAINTSTRUCT ps;
    HFONT oldFont, myFont;
    HBRUSH oldBrush, myBrush;
    const TCHAR* str = TEXT("ÆùÆ® Test 1234");
    LOGFONT lf;

    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            myBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
            oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
            Rectangle(hdc, 50, 50, 400, 200);
            SelectObject(hdc, oldBrush);

            // myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("±Ã¼­"));
            // below is equivalent 
            {
                lf.lfHeight = 30; // 0 if default
                lf.lfWidth = 0; // 0 if preserve aspect ratio to lfHeight
                lf.lfEscapement = 0; // rotation for entire str
                lf.lfOrientation = 0; // rotation for one char
                lf.lfWeight = FW_NORMAL; // font thickness
                lf.lfItalic = FALSE;
                lf.lfUnderline = FALSE;
                lf.lfStrikeOut = FALSE;
                lf.lfCharSet = HANGEUL_CHARSET; // ANSI_CHARSET for english
                lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
                lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
                lf.lfQuality = DEFAULT_QUALITY;
                lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
                lstrcpy(lf.lfFaceName, TEXT("±Ã¼­")); // Times New Roman
                myFont = CreateFontIndirect(&lf);
            }
            oldFont = (HFONT)SelectObject(hdc, myFont);

            SetTextColor(hdc, RGB(255, 0, 0));
            SetBkColor(hdc, RGB(255, 255, 0));
            TextOut(hdc, 100, 100, str, lstrlen(str));

            SetBkMode(hdc, TRANSPARENT);
            TextOut(hdc, 100, 150, str, lstrlen(str));

            SelectObject(hdc, oldFont);
            DeleteObject(myBrush);
            DeleteObject(myFont);
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}