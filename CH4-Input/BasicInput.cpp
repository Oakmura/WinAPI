#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE gInstance;
LPCTSTR lpszClass = TEXT("WinAPI");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR CmdParam, int nCmdShow)
{
    gInstance = hInstance;

    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0; // windows reserved space for internal use
    wndClass.cbWndExtra = 0; // windows reserved space for internal use
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // CreateSolidBrush(RGB(0, 0, 255)). CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0)).
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // use default if NULL
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = WndProc;
    wndClass.lpszClassName = lpszClass;
    wndClass.lpszMenuName = NULL; // menu for all subsequent child windows
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);

    HWND hWnd = CreateWindow(
        lpszClass, // lpszClassName. window class name
        lpszClass, // lpszWindowName. window titlebar name
        WS_OVERLAPPEDWINDOW, // dwstyle. (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // pos and size (x, y, width, height)
        NULL, // parent handle
        (HMENU)NULL, // menu for this window only
        hInstance,
        NULL // CREATESTRUCT*. for multiple windows
    );

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) // gets msg from Queue. returns false on WM_QUIT
    {
        TranslateMessage(&msg); // translates WM_KEYDOWN -> WM_CHAR
        DispatchMessage(&msg); // dispatches msg to WndProc
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static int x = 100;
    static int y = 100;

    switch (msg)
    {
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            x -= 8;
            break;
        case VK_RIGHT:
            x += 8;
            break;
        case VK_UP:
            y -= 8;
            break;
        case VK_DOWN:
            y += 8;
            break;
        }

        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    case WM_PAINT: // when part of window is validated (from obscure or resize)
        hdc = BeginPaint(hWnd, &ps); // valid only within WM_PAINT
        {
            TextOut(hdc, x, y, TEXT("A"), 1);
        }
        EndPaint(hWnd, &ps);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}