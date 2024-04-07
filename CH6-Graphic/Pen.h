#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HPEN oldPen, myPen;

    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            myPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
            oldPen = (HPEN)SelectObject(hdc, myPen);

            // default stock object used. black boundary (pen) + inner white (brush)
            Rectangle(hdc, 50, 50, 300, 200);

            SelectObject(hdc, oldPen); // make sure to set it back
            DeleteObject(myPen);
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}