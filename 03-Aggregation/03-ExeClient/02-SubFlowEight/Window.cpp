#include<windows.h>

#include "Window.h"
#include "AggregationInnerDllServer.h"

//Global Callback Declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Declaration of Interface Pointers 
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;

//Process ch aayushya ithun suru hot
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	TCHAR pszAppName[] = TEXT("DDK_WINDOW");
	HWND hwnd;
	MSG msg;
	HRESULT hr;

	//code
	//Initializing COM engine 
	hr = CoInitialize(NULL); //I am not a ordinary process, I am com client
	if (FAILED(hr)) //SUCCEEDED pan aahe
		MessageBox(NULL, TEXT("COINITIALIZE FAILED COInitialize!!"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR);

	memset((void*)&wndclass, 0, sizeof(WNDCLASSEX));

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(DDK_ICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(DDK_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = pszAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	//Window ch aayushya CreateWindow nantr suru hot, aani WM_DESTROY nantr sampt
	hwnd = CreateWindow(pszAppName,
		TEXT("DDK : My First Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, 
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//aani ithe process ch aayush sampt
	//uninitializing COM engine
	CoUninitialize(); //CoFreeUnusedLibrary() la call det => lpfn2(DllCanUnloadNow) => CoFreeLibrary() => FreeLibarary() => Dll memory madhun jate
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function prototypes
	void SafeInterfaceRelease(void);

	//variable declarations
	HRESULT hr = S_OK;
	int iNum1 = 20, iNum2 = 11;
	int iSum = 0, iSub = 0;
	TCHAR str[255];
	TCHAR str2[255];

	switch (iMsg)
	{
		case WM_CREATE: //CLSCTX_INPROC_SERVER  => com server kontya prakaracha aahe he sangto, class context in process server(jevha dll asto aani aplaych machine var asto tevha as lihitat)
			hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMULTIPLICATION, (void**)&pIMultiplication);
			if (FAILED(hr)) //only one CoCreateInstance per DLL
			{
				MessageBox(NULL, TEXT("COINITIALIZE wmcreate FAILED!!"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iSum);
			wsprintf(str, TEXT("Sum is %d"), iSum);
			MessageBox(NULL, str, TEXT("ADDITION"), MB_OK);

			hr = pIMultiplication->QueryInterface(IID_IDIVISION, (void**)&pIDivision);
			if (FAILED(hr)) //only one CoCreateInstance per DLL
			{
				MessageBox(NULL, TEXT("QueryInterface FAILED TO OBTAIN ISUBTRACT INTERFACE!!"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iSub);
			wsprintf(str2, TEXT("Subtraction is %d"), iSub);
			MessageBox(NULL, str2, TEXT("Subtraction"), MB_OK);
			DestroyWindow(hwnd);
			break;                                     //Message Box chya caption madhey kaay pahije //4th parameter mahiti kara

		case WM_KEYDOWN:   //Keydown zalyanantr kuthli key aahe aani character key asel tar translate message adhi WM_CHAR pathvto aani nantr WM_KEYDOWN yeto! //mhnjech don yetat
			switch(wParam)
			{
				case VK_ESCAPE:
					DestroyWindow(hwnd);
					break;

				default :
					break;
			}
			break;

		case WM_DESTROY:
			SafeInterfaceRelease();
			PostQuitMessage(0);
			break;

		default:
			break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

//user defined function for safely releasing the interface pointers
void SafeInterfaceRelease(void)
{
	//code
	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}

	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
}

//link.exe Window.obj Window.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
//rc.exe Window.rc