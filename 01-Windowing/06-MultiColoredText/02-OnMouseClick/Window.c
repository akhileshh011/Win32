#include <windows.h>
#include "Window.h"

//Global Callback Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Entry-point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpszCmdLine, int iCmdShow)
{
    //variable declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szClassName[] = TEXT("MyWindow_ARM"); //TEXT() is a macro 

    //code 
    ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));

    //Initializing Window Class
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.lpszClassName = szClassName;
    wndclass.lpszMenuName = NULL;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.hInstance = hInstance;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ARM_ICON));
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ARM_ICON));

    //Register the above Window class
    RegisterClassEx(&wndclass);

    //Create the window in memory
    hwnd = CreateWindow(szClassName, TEXT("Akhilesh Mali: First Name"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    //Show the window on the desktop
    ShowWindow(hwnd, iCmdShow);

    //Update / Paint the window on the desktop
    UpdateWindow(hwnd);

    //Message Loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return((int)msg.wParam);
}

//Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM LParam)
{
    //Variable Declarations
    HDC hdc = NULL;
    static PAINTSTRUCT ps;
    static RECT rect; //static to use across cases
    TCHAR str[] = TEXT("Hello World From WinDev - 2024 ");
    HBRUSH hBrushRect = NULL; // Red brush for rectangles
    HBRUSH hBrushEllipse = NULL; // Blue brush for ellipses

    static iPaintFlag = 0;
    //code
    switch (iMsg)
    {
    case WM_CREATE:
        ZeroMemory((void*)&rect, sizeof(RECT));
        ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
        break;
    case WM_PAINT:
        // Get the client area Rectangle of our window 
        GetClientRect(hwnd, &rect);

        //Get the Painter hdc to do painting work for our window
        hdc = BeginPaint(hwnd, &ps);

        // Set background color of my text only, not window.
        SetBkColor(hdc, RGB(0, 0, 0)); // Black background for text

        // Create brushes and pens for coloring shapes
        //HBRUSH hBrushRect = CreateSolidBrush(RGB(255, 0, 0)); // Red brush for rectangles
        //HBRUSH hBrushEllipse = CreateSolidBrush(RGB(0, 0, 255)); // Blue brush for ellipses
        switch (iPaintFlag)
        {
        case 1:
            hBrushRect = CreateSolidBrush(RGB(255, 0, 0));
            hBrushEllipse = CreateSolidBrush(RGB(255, 0, 0));
            SetTextColor(hdc, RGB(255, 0, 0)); // Red text color
            break;
        case 2:
            hBrushRect = CreateSolidBrush(RGB(0, 255, 0));
            hBrushEllipse = CreateSolidBrush(RGB(0, 255, 0));
            SetTextColor(hdc, RGB(0, 255, 0)); // Green text color
            break;
        case 3:
            hBrushRect = CreateSolidBrush(RGB(0, 0, 255));
            hBrushEllipse = CreateSolidBrush(RGB(0, 0, 255));
            SetTextColor(hdc, RGB(0, 0, 255)); // Blue text color
            break;
        case 4:
            hBrushRect = CreateSolidBrush(RGB(0, 255, 255));
            hBrushEllipse = CreateSolidBrush(RGB(0, 255, 255));
            SetTextColor(hdc, RGB(0, 255, 255)); // Cyan text color
            break;
        case 5:
            hBrushRect = CreateSolidBrush(RGB(255, 0, 255));
            hBrushEllipse = CreateSolidBrush(RGB(255, 0, 255));
            SetTextColor(hdc, RGB(255, 0, 255)); // Magenta text color
            break;
        case 6:
            hBrushRect = CreateSolidBrush(RGB(255, 255, 0));
            hBrushEllipse = CreateSolidBrush(RGB(255, 255, 0));
            SetTextColor(hdc, RGB(255, 255, 0)); // Yellow text color
            break;
        case 7:
            hBrushRect = CreateSolidBrush(RGB(0, 0, 0));
            hBrushEllipse = CreateSolidBrush(RGB(0, 0, 0));
            SetTextColor(hdc, RGB(0, 0, 0)); // Black text color
            break;
        default:
            hBrushRect = CreateSolidBrush(RGB(128, 128, 128));
            hBrushEllipse = CreateSolidBrush(RGB(128, 128, 128));
            SetTextColor(hdc, RGB(128, 128, 128)); // Grey text color
            break;
        }

        // Set brush and draw the rectangles
        SelectObject(hdc, hBrushRect);
        Rectangle(hdc, 38, 29, 92, 83);
        Rectangle(hdc, 1496, 760, 1442, 706);

        // Set brush and draw the ellipses
        SelectObject(hdc, hBrushEllipse);
        Ellipse(hdc, 1496, 29, 1442, 83);
        Ellipse(hdc, 38, 760, 92, 706);

        // Draw the text
        DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // Clean up brushes
        if (hBrushRect) {
            DeleteObject(hBrushRect);

        }
        if (hBrushEllipse) {
            DeleteObject(hBrushEllipse);
        }
        if (hdc)
        {
            EndPaint(hwnd, &ps);
            hdc = NULL;
        }
        // Release the painter hdc once the painting work is done
        EndPaint(hwnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        iPaintFlag++;
        InvalidateRect(hwnd, NULL, TRUE);
        if (iPaintFlag > MAX_NUMBER_OF_COLORS)
        {
            iPaintFlag = 0;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    //Calling default Window Procedure
    return(DefWindowProc(hwnd, iMsg, wParam, LParam));
}
