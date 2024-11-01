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
	HMODULE hDll = NULL;
	typedef int (*MakeCubeFnPtr)(int);
	MakeCubeFnPtr fnPtr = NULL;
	int num = 5;
	int cube = 0;
	TCHAR str[255];
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		//Step 1 : Load the desired DLL explicitly
		hDll = LoadLibrary(TEXT("MyMathTwo.dll"));
		if (hDll == NULL) 
		{
			MessageBox(hwnd, TEXT("LoadLibrary() FAILED"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		//Step 2 : Get address of the desired function from the loaded DLL
		fnPtr = (MakeCubeFnPtr)GetProcAddress(hDll, "MakeCube");
		if (fnPtr == NULL)
		{
			FreeLibrary(hDll);
			hDll = NULL;
			MessageBox(hwnd, TEXT("GetProcAddress() FAILED"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		//Step 3 : Now call the function pointer fnPtr just as if calling MakeCube()
		cube = fnPtr(num); //fnPtr = MakeCube Name of function is itself its address
		//Step 4 : Display Result
		wsprintf(str, TEXT("Cube of %d is %d"), num, cube);
		MessageBox(hwnd, str, TEXT("CUBE"), MB_OK);
		//Step 5 : Free Library
		if (hDll)
		{
			FreeLibrary(hDll);
			hDll = NULL;
		}
		DestroyWindow(hwnd);
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


