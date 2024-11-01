#include<windows.h>

//DLL's Entry-Point Function
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	//Code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}	 

	return(TRUE);
}

//Now define DLLs Functionality 
//Function(s) to be exported
extern "C" int MakeCube(int num)
{
	//Function Prototype
	void CheckNumber(int);
	//Code
	CheckNumber(num);
	return (num * num * num);	
}

//Function(s) for DLL's internal usage	
extern "C" void CheckNumber(int num)
{	
	if (num < 0)
	{
		MessageBox(NULL, TEXT("Number is negative!"), TEXT("Check Number"), MB_OK);
	}
}
