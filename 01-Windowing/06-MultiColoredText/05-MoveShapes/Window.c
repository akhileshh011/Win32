#include <windows.h>
#include<mmsystem.h> // Including this file for PlaySound() API 

#include "Window.h"
//Import Library (Instead of writing its name in link.exe command)
#pragma comment(lib,"winmm.lib") //winmm.lib is library of PlaySound()

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
    static HBRUSH hBrushRect = NULL; // Red brush for rectangles
    static HBRUSH hBrushEllipse = NULL; // Blue brush for ellipses
    static int iRect1Left = 38;
    static int iRect1Top = 29;
    static int iRect1Right = 92;
    static int iRect1Bottom = 83;
    static int iRect2Left = 1496;
    static int iRect2Top = 760;
    static int iRect2Right = 1442;
    static int iRect2Bottom = 706;
    static int iEllipse1Left = 1496;
    static int iEllipse1Top = 29;
    static int iEllipse1Right = 1442;
    static int iEllipse1Bottom = 83;
    static int iEllipse2Left = 38;
    static int iEllipse2Top = 760;
    static int iEllipse2Right = 92;
    static int iEllipse2Bottom = 706;

    static int iPaintFlag = 0;

    // Movement direction flags
    static BOOL movingRightRect1 = TRUE; // Direction for first rectangle
    static BOOL movingRightRect2 = TRUE; // Direction for second rectangle
    static BOOL movingRightEllipse1 = TRUE; // Direction for first ellipse
    static BOOL movingRightEllipse2 = TRUE; // Direction for second ellipse

    switch (iMsg)
    {
    case WM_CREATE:
        ZeroMemory((void*)&rect, sizeof(RECT));
        ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
        //Begin Playing the Music
        PlaySound(MAKEINTRESOURCE(ARM_MUSIC), GetModuleHandle(NULL), SND_ASYNC | SND_LOOP | SND_RESOURCE);

        //Setting Timer ARM_TIMER
        SetTimer(hwnd, ARM_TIMER, 1000, NULL);
        break;
    case WM_PAINT:
        // Get the client area Rectangle of our window 
        GetClientRect(hwnd, &rect);

        //Get the Painter hdc to do painting work for our window
        hdc = BeginPaint(hwnd, &ps);

        // Set background color of my text only, not window.
        SetBkColor(hdc, RGB(0, 0, 0)); // Black background for text

        // Create brushes and pens for coloring shapes
        switch (iPaintFlag)
        {
        case 1:
            hBrushRect = CreateSolidBrush(RGB(255, 0, 0));
            hBrushEllipse = CreateSolidBrush(RGB(0, 255, 255));
            SetTextColor(hdc, RGB(255, 0, 0)); // Red text color
            break;
        case 2:
            hBrushRect = CreateSolidBrush(RGB(0, 255, 0));
            hBrushEllipse = CreateSolidBrush(RGB(255, 0, 255));
            SetTextColor(hdc, RGB(0, 255, 0)); // Green text color
            break;
        case 3:
            hBrushRect = CreateSolidBrush(RGB(0, 0, 255));
            hBrushEllipse = CreateSolidBrush(RGB(255, 255, 0));
            SetTextColor(hdc, RGB(0, 0, 255)); // Blue text color
            break;
        case 4:
            hBrushRect = CreateSolidBrush(RGB(0, 255, 255));
            hBrushEllipse = CreateSolidBrush(RGB(255, 0, 0));
            SetTextColor(hdc, RGB(0, 255, 255)); // Cyan text color
            break;
        case 5:
            hBrushRect = CreateSolidBrush(RGB(255, 0, 255));
            hBrushEllipse = CreateSolidBrush(RGB(0, 255, 0));
            SetTextColor(hdc, RGB(255, 0, 255)); // Magenta text color
            break;
        case 6:
            hBrushRect = CreateSolidBrush(RGB(255, 255, 0));
            hBrushEllipse = CreateSolidBrush(RGB(0, 0, 255));
            SetTextColor(hdc, RGB(255, 255, 0)); // Yellow text color
            break;
        case 7:
            hBrushRect = CreateSolidBrush(RGB(0, 0, 0));
            hBrushEllipse = CreateSolidBrush(RGB(255, 255, 255));
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
        Rectangle(hdc, iRect1Left, iRect1Top, iRect1Right, iRect1Bottom);
        Rectangle(hdc, iRect2Left, iRect2Top, iRect2Right, iRect2Bottom);

        // Set brush and draw the ellipses
        SelectObject(hdc, hBrushEllipse);
        Ellipse(hdc, iEllipse1Left, iEllipse1Top, iEllipse1Right, iEllipse1Bottom);
        Ellipse(hdc, iEllipse2Left, iEllipse2Top, iEllipse2Right, iEllipse2Bottom);

        // Draw the text
        DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        // Clean up brushes
        if (hBrushRect) {
            DeleteObject(hBrushRect);
        }
        if (hBrushEllipse) {
            DeleteObject(hBrushEllipse);
        }

        // Release the painter hdc once the painting work is done
        EndPaint(hwnd, &ps);
        break;
    case WM_TIMER:
        // Update the rectangle position
        if (movingRightRect1)
        {
            if (iRect1Right >= rect.right) // If rectangle reaches right edge
            {
                movingRightRect1 = FALSE; // Change direction to left
            }
            else
            {
                iRect1Left+=100;
                iRect1Right+=100;
            }
        }
        else
        {
            if (iRect1Left <= 0) // If rectangle reaches left edge
            {
                movingRightRect1 = TRUE; // Change direction to right
            }
            else
            {
                iRect1Left-=100;
                iRect1Right-=100;
            }
        }

        if (movingRightRect2)
        {
            if (iRect2Right >= rect.right) // If rectangle reaches right edge
            {
                movingRightRect2 = FALSE; // Change direction to left
            }
            else
            {
                iRect2Left += 100;
                iRect2Right += 100;
            }
        }
        else
        {
            if (iRect2Left <= 0) // If rectangle reaches left edge
            {
                movingRightRect2 = TRUE; // Change direction to right
            }
            else
            {
                iRect2Left -= 100;
                iRect2Right -= 100;
            }
        }

        // Update the ellipses' positions
        if (movingRightEllipse1)
        {
            if (iEllipse1Right >= rect.right) // If ellipse reaches right edge
            {
                movingRightEllipse1 = FALSE; // Change direction to left
            }
            else
            {
                iEllipse1Left+=100;
                iEllipse1Right+=100;
            }
        }
        else
        {
            if (iEllipse1Left <= 0) // If ellipse reaches left edge
            {
                movingRightEllipse1 = TRUE; // Change direction to right
            }
            else
            {
                iEllipse1Left-=100;
                iEllipse1Right-=100;
            }
        }

        if (movingRightEllipse2)
        {
            if (iEllipse2Right >= rect.right) // If ellipse reaches right edge
            {
                movingRightEllipse2 = FALSE; // Change direction to left
            }
            else
            {
                iEllipse2Left+=100;
                iEllipse2Right+=100;
            }
        }
        else
        {
            if (iEllipse2Left <= 0) // If ellipse reaches left edge
            {
                movingRightEllipse2 = TRUE; // Change direction to right
            }
            else
            {
                iEllipse2Left-=100;
                iEllipse2Right-=100;
            }
        }
        
        // Invalidate the window to trigger a repaint
        InvalidateRect(hwnd, NULL, TRUE);

        // Kill and restart the timer
        KillTimer(hwnd, ARM_TIMER);
        SetTimer(hwnd, ARM_TIMER, 1000, NULL);

        // Update the paint flag
        iPaintFlag++;
        if (iPaintFlag > 7)
        {
            iPaintFlag = 0;
        }
        break;
    case WM_DESTROY:
        PlaySound(NULL, 0, 0);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, iMsg, wParam, LParam);
    }

    return 0;
}

