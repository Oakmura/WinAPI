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
    RECT rt = { 400, 500, 400, 300 };
    const TCHAR* str = TEXT("´ÔÀº °¬½À´Ï´Ù. ¾Æ¾Æ »ç¶ûÇÏ´Â ³ªÀÇ ´ÔÀº °¬½À´Ï´Ù. Çª¸¥ »êºûÀ»"
        "±úÄ¡°í ´ÜÇ³³ª¹« ½£À» ÇâÇÏ¿© ³­ ÀÛÀº ±æÀ» °É¾î¼­ Â÷¸¶ ¶³Ä¡°í °¬½À´Ï´Ù."
        "È²±ÝÀÇ ²É°°ÀÌ ±»°í ºû³ª´ø ¿¾ ¸Í¼¼´Â Â÷µðÂù Æ¼²øÀÌ µÇ¾î ÇÑ¼ûÀÇ ¹ÌÇ³¿¡ "
        "³¯¾Æ°¬½À´Ï´Ù.");

    switch (msg)
    {
    case WM_DESTROY: // alt + f4
        PostQuitMessage(0); // generates WM_QUIT msg
        return 0;
    case WM_LBUTTONDOWN:
        // MessageBeep(0);
        hdc = GetDC(hWnd);
        {
            TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15); // oneline. does not recognize null-terminate str
        }
        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_PAINT: // when part of window is validated (from obscure or resize)
        hdc = BeginPaint(hWnd, &ps); // valid only within WM_PAINT
        {
            SetTextAlign(hdc, TA_CENTER); // default is (TOP | LEFT)
            TextOut(hdc, 200, 60, TEXT("Beautiful Korea"), 15); // 15 = strlen
            TextOut(hdc, 200, 80, TEXT("is My"), 5);
            TextOut(hdc, 200, 100, TEXT("Lovely Home Country"), 19);

            SetTextAlign(hdc, TA_UPDATECP); // write + update on CP (current point). ignores x,y param in TextOut
            TextOut(hdc, 300, 60, TEXT("One "), 4); // 15 = strlen
            TextOut(hdc, 300, 80, TEXT("Two "), 4);
            TextOut(hdc, 300, 100, TEXT("Three"), 5);

            DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
        }
        EndPaint(hWnd, &ps);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam); // handles resize, move ...
}