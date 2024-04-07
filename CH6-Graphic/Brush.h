#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH oldBrush, myBrush;

    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        {
            // stock object
            {
                myBrush = (HBRUSH)GetStockObject(GRAY_BRUSH); // no need to destroy stock object
                oldBrush = (HBRUSH)SelectObject(hdc, myBrush); // returns previously used HGDIOBJ

                // default stock object used. black boundary (pen) + inner white (brush)
                Rectangle(hdc, 50, 50, 300, 200);

                SelectObject(hdc, oldBrush); // make sure to set it back to oldbrush
            }

            // my brush
            {
                myBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 255));
                oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
                Rectangle(hdc, 400, 400, 300, 200);
                SelectObject(hdc, oldBrush);
                DeleteObject(myBrush);
            }
        }
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}