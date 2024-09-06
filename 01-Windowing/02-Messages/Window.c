#include<windows.h>

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	 
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
	TCHAR str[255];
	wchar_t ch;
	unsigned int x, y;
	//code
	switch (iMsg)
	{
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
	case WM_CREATE:
		wsprintf(str, TEXT("WM_CREATE Message Received")); // Wide char string printf
		MessageBox(NULL, str , TEXT("MESSAGE"), MB_OKCANCEL); //MB_ABORTRETRYIGNORE MB_YESNOCANCEL MB_RETRYCANCEL
		break;
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		ch = wParam; //Get which key pressed like getch()
		wsprintf(str, TEXT("WM_CHAR Message Received for character %c"),ch);
		MessageBox(NULL, str , TEXT("MESSAGE"), MB_OK); 
		break;
	case WM_LBUTTONDOWN:
		x = LOWORD(LParam);
		y = HIWORD(LParam);
		wsprintf(str, TEXT("Left Mouse Button Click at :(%d,%d)"),x,y);
		MessageBox(NULL, str , TEXT("MESSAGE"), MB_ICONEXCLAMATION);   //MB_CANCELTRYCONTINUE
		break;
	case WM_RBUTTONDOWN:
		x = LOWORD(LParam);
		y = HIWORD(LParam);
		wsprintf(str, TEXT("Right Mouse Button Click at :(%d,%d)"), x, y);
		MessageBox(NULL, str , TEXT("MESSAGE"), MB_YESNO);
		break;
	case WM_DESTROY:
		wsprintf(str, TEXT("The End"));
		MessageBox(NULL, str, TEXT("Message"), MB_HELP);
		PostQuitMessage(0);
		break;
	
	default:
		break;
	}

	//Calling default Window Procedure
	return(DefWindowProc(hwnd, iMsg, wParam, LParam));

}


