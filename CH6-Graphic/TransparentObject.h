#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    int i;
    HPEN oldPen, myPen;
    HBRUSH oldBrush, myBrush;

    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            for (i = 0; i < 250; i += 5) // horizontal stripe pattern for more noticeable result
            {
                MoveToEx(hdc, 0, i, NULL);
                LineTo(hdc, 600, i);
            }

            myBrush = CreateSolidBrush(RGB(0, 255, 0));
            oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

            myPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
            oldPen = (HPEN)SelectObject(hdc, myPen);

            // red pen + green brush
            Ellipse(hdc, 20, 20, 150, 150);

            // red pen + null brush
            SelectObject(hdc, GetStockObject(NULL_PEN));
            Ellipse(hdc, 220, 20, 350, 150);

            // null pen + green brush
            SelectObject(hdc, myBrush);
            SelectObject(hdc, GetStockObject(NULL_PEN));
            Ellipse(hdc, 420, 20, 550, 150);

            DeleteObject(SelectObject(hdc, oldBrush));
            DeleteObject(SelectObject(hdc, oldPen));
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}