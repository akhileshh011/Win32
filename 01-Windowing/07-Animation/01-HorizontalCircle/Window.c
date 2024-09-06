 #include<windows.h>
#include "Window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ELLIPSE_SIZE_X 100
#define ELLIPSE_SIZE_Y 100
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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //only has limited system colors https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getstockobject
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ARM_ICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ARM_ICON));
	 
	 //Register the aboove Window class
	RegisterClassEx(&wndclass);

	//Create the window in moemory
	hwnd = CreateWindow(szClassName, TEXT("Akhilesh Mali: First Name"), WS_OVERLAPPEDWINDOW, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	
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
	HBRUSH hBrush = NULL;
	static int leftTopX;
	static int leftTopY;
	static int rightBottomX;
	static int rightBottomY;
	static int xAnimate = 0;
	static BOOL bGoFromLeftToRight = TRUE;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		ZeroMemory((void*)&rect, sizeof(RECT));
		ZeroMemory((void*)&ps,sizeof(PAINTSTRUCT));
		//If written here text is not centralized after resizing window as WM_CREATE message got only once
		//GetClientRect(hwnd, &rect);
		
		//Setting Timer ARM_TIMER
		SetTimer(hwnd, ARM_TIMER, 1, NULL);
		break;
	case WM_PAINT:
		//Get the client area Rectangle of our window (every resize WM_PAINT is getting set again (Repainting after resize so))
		GetClientRect(hwnd, &rect);
		//Get the Painter hdc to do painting work for our window
		hdc = BeginPaint(hwnd, &ps);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		//Give the brush to the painter
		SelectObject(hdc, hBrush);
		leftTopX = 0 + xAnimate;
		leftTopY = (WINDOW_HEIGHT/2) - (ELLIPSE_SIZE_Y / 2);
		rightBottomX = ELLIPSE_SIZE_X + xAnimate;
		rightBottomY = (WINDOW_HEIGHT/2) + (ELLIPSE_SIZE_Y / 2);
		Ellipse(hdc, leftTopX, leftTopY, rightBottomX, rightBottomY);
		//Release the brush
		if (hBrush) // or if (hBrush!=NULL) Safe Releasing
		{
			DeleteObject(hBrush); //hdc chya hatun hBrush kadhun ghena
			hBrush = NULL; //Bhanda Dhuvun theva
		}
		//Release the painter hdc once the painting work is done 
		if (hdc)
		{
			EndPaint(hwnd, &ps);
			hdc = NULL;
		}
		break;
	case WM_TIMER:
		//Kill the timer ARM_TIMER
		KillTimer(hwnd, ARM_TIMER);
		if (bGoFromLeftToRight) {
			xAnimate++;
			if (rightBottomX == WINDOW_WIDTH) {
				bGoFromLeftToRight = FALSE;
			}
		}
		else {
			xAnimate--;
			if (leftTopX == 0) {
				bGoFromLeftToRight = TRUE;
			}
		}
		InvalidateRect(hwnd,NULL,TRUE);
		//Setting Timer ARM_TIMER
		SetTimer(hwnd, ARM_TIMER, 1, NULL);
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


