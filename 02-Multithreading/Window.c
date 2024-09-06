#include<windows.h>
#include "Window.h"

//Global Callback Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //Can have different names WindowProc etc but as lpfnWndProc 
//Global Thread Functions Declaration
DWORD WINAPI ThreadProcOne(LPVOID); 
DWORD WINAPI ThreadProcTwo(LPVOID);

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
	wndclass.lpfnWndProc = WndProc; //Registering
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
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcOne, //Here we register our thread functions name
			(LPVOID)hwnd,
			0,
			NULL
		);
		hThread2 = CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcTwo,
			(LPVOID)hwnd,
			0,
			NULL
		);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Message Box Thread"), TEXT("Message"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY:
		//Destruction order should opposite to the creation order 
		if (hThread2) {
			CloseHandle(hThread2);
			hThread2 = NULL;
		}
		if (hThread1) {
			CloseHandle(hThread1);
			hThread1 = NULL;
		}
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	//Calling default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, LParam));

}

//Defining ThreadProcOne
DWORD WINAPI ThreadProcOne(LPVOID param)
{
	//Variable Declarations
	HDC hdc = NULL; 
	ULONG i = 0L; //static chi garaj nahi as thread ekda suru jhala ki it will not end till it function ends
	TCHAR str[255];

	//Code
	hdc = GetDC((HWND)param); //Painter la Bolva
	SetBkColor(hdc,RGB(0, 0, 0));
	SetTextColor(hdc,RGB(0, 255, 0));
	for (i = 0;i <= ULONG_MAX;i++)
	{
		wsprintf(str, TEXT("Incrementing: %lu"), i);
		TextOut(hdc,5,5,str,wcslen(str)); // More flexible than DrawText
	}
	if (hdc)
	{
		ReleaseDC((HWND)param, hdc); // painter parat pathva
		hdc = NULL; //Bhanda Dhuvun Theva
	}
	return (0);
}

//Defining ThreadProcOne
DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	//Variable Declarations
	HDC hdc = NULL;
	ULONG i = 0L; //static chi garaj nahi as thread ekda suru jhala ki it will not end till it function ends
	TCHAR str[255];

	//Code
	hdc = GetDC((HWND)param); //Painter la Bolva
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 0, 0));
	for (i = ULONG_MAX;i >= 0;i--)
	{
		wsprintf(str, TEXT("Decrementing: %lu"), i);
		TextOut(hdc, 5, 20, str, wcslen(str)); // More flexible than DrawText
	}
	if (hdc)
	{
		ReleaseDC((HWND)param, hdc); // painter parat pathva
		hdc = NULL; //Bhanda Dhuvun Theva
	}
	return (0);
}
