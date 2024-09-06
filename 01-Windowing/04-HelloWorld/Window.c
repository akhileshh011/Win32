#include<windows.h>
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
	TCHAR str[] = TEXT("Hello World From WinDev - 2024 ");

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		ZeroMemory((void*)&rect, sizeof(RECT));
		ZeroMemory((void*)&ps,sizeof(PAINTSTRUCT));
		//If written here text is not centralized after resizing window as WM_CREATE message got only once
		//GetClientRect(hwnd, &rect);
		break;
	case WM_PAINT:
		//Get the client area Rectangle of our window (every resize WM_PAINT is getting set again (Repainting after resize so))
		//GetClientRect(hwnd, &rect);

		//Get the Painter hdc to do painting work for our window
		hdc = BeginPaint(hwnd, &ps);
		//Set Background Color of my text only not window. Tell the Painter hdc to set background color of our text to black
		SetBkColor(hdc, RGB(0, 0, 0)); //SetBkColor(hdc, RGB(255, 0, 0)); will set red background to text
		// Tell the painter hdc to set text color to green
		SetTextColor(hdc, RGB(0, 255, 0));
		//Tell the painter hdc 4 things 1. Which text to draw (str), 2. What is the length of the text to draw (-1)(-1 mhanje akkhya string chi length ghe (uses function automatically (use wcslen for length not strlen as it is tchar)) 
		//3. In which client area rectangle should I draw the text (got through GetClientRect line 73) , 4. How should I draw the text.
		DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//Release the painter hdc once the painting work is done 
		EndPaint(hwnd, &ps);
		break;
	case WM_SIZE:
		//Get the client area Rectangle of our window 
		GetClientRect(hwnd, &rect);
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


