#include<windows.h>
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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //only has limited system colors https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getstockobject
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ARM_ICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(ARM_ICON));
	 
	 //Register the aboove Window class
	RegisterClassEx(&wndclass);

	//Create the window in moemory
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
	HBRUSH hBrush = NULL;

	static int iPaintFlag = 0; // It should retain its value across WM_CHAR and WM_PAINT

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		ZeroMemory((void*)&rect, sizeof(RECT));
		ZeroMemory((void*)&ps,sizeof(PAINTSTRUCT));
		//If written here text is not centralized after resizing window as WM_CREATE message got only once
		//GetClientRect(hwnd, &rect);
		
		//Begin Playing the Music
		PlaySound(MAKEINTRESOURCE(ARM_MUSIC), GetModuleHandle(NULL), SND_ASYNC | SND_LOOP | SND_RESOURCE);
		//Setting Timer ARM_TIMER
		SetTimer(hwnd, ARM_TIMER, 1000, NULL);
		break;
	case WM_PAINT:
		//Get the client area Rectangle of our window (every resize WM_PAINT is getting set again (Repainting after resize so))
		GetClientRect(hwnd, &rect);

		//Get the Painter hdc to do painting work for our window
		hdc = BeginPaint(hwnd, &ps);
		switch (iPaintFlag)
		{
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(0, 0,0));
			break;
		default:
			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			break;
		}
		//Create Grey Colored Brush
		
		//Give the brush to the painter
		SelectObject(hdc, hBrush);
		//Fill our client area of our rectangle with the color of our selected brush
		FillRect(hdc, &rect, hBrush);
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
		iPaintFlag++;
		InvalidateRect(hwnd,NULL,TRUE);
		if(iPaintFlag>MAX_NUMBER_OF_COLORS)
		{
			iPaintFlag = 0;
		}
		//Setting Timer ARM_TIMER
		SetTimer(hwnd, ARM_TIMER, 1000, NULL);
		break;
	case WM_DESTROY:
		PlaySound(NULL, 0, 0);
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	//Calling default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, LParam));

}


