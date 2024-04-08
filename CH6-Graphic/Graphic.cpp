// #include "Pen.h"
// #include "Brush.h"
// #include "TransparentObject.h"
// #include "RenderingOP.h"
// #include "Bitmap.h"
#include "Font.h"

HINSTANCE gInstance;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("WinAPI");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR CmdParam, int nCmdShow)
{
    gInstance = hInstance;

    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0; // windows reserved space for internal use
    wndClass.cbWndExtra = 0; // windows reserved space for internal use
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // system default
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
