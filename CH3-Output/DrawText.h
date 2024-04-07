#pragma once

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rt = { 100, 100, 400, 300 };
    const TCHAR* str = TEXT("���� �����ϴ�. �ƾ� ����ϴ� ���� ���� �����ϴ�. Ǫ�� �����"
        "��ġ�� ��ǳ���� ���� ���Ͽ� �� ���� ���� �ɾ ���� ��ġ�� �����ϴ�."
        "Ȳ���� �ɰ��� ���� ������ �� �ͼ��� ������ Ƽ���� �Ǿ� �Ѽ��� ��ǳ�� "
        "���ư����ϴ�.");

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