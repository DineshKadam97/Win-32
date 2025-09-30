#include<windows.h>

#include "Window.h"
#include  "AutomationServer.h"

//Global Callback Declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Declaration of Interface Pointers 
IDispatch* pIDispatch = NULL;

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

	//IDispatch client related variables
	//Exported functionalities token names whose DispatchIDs we must obtain to invoke these functionalities
	OLECHAR* szFunctionName1 = L"SumOfTwoIntegers";
	OLECHAR* szFunctionName2 = L"SubtractionOfTwoIntegers";

	DISPID dispid; //variable to store unique dispatch ID of the functionality to be invoked
	
	//varibales to send to the Invoke() functinality
	DISPPARAMS params;
	static VARIANT vArgs[2];

	//varibale to hold the actual return value of Invoke() functionality
	static VARIANT vretval;

	switch (iMsg)
	{
		case WM_CREATE: //CLSCTX_INPROC_SERVER  => com server kontya prakaracha aahe he sangto, class context in process server(jevha dll asto aani aplaych machine var asto tevha as lihitat)
			hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);
			if (FAILED(hr)) //only one CoCreateInstance per DLL
			{
				MessageBox(NULL, TEXT("FAILED TO OBTAIN IDispatch Interface!!"), TEXT("COM ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			MessageBox(NULL, TEXT("SUCCESS!!"), TEXT("COM SUCCESS"), MB_OK);

			//Prepare the parameters to be sent to the invoke functionality
			VariantInit(vArgs);
			vArgs[0].vt = VT_INT;
			vArgs[0].intVal = iNum2;


			vArgs[1].vt = VT_INT;
			vArgs[1].intVal = iNum1;

			params.rgvarg = vArgs;
			params.cArgs = 2;
			params.rgdispidNamedArgs = NULL;
			params.cNamedArgs = 0;

			//prepare the return value variant variable to accept the return value of invoke functionality
			VariantInit(&vretval);

			//Get Dispatch ID of sum of 2 integers functionality
			hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName1, 1, GetUserDefaultLCID(), &dispid);
			if (FAILED(hr))
			{
				MessageBox(NULL, TEXT("FAILURE IN GetIDsOfNames!!"), TEXT("COM FAILURE"), MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			//using the above obtainer unique dispatch id, call Invoke(). To invoke sum of two integers functionality
			hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vretval, NULL, NULL);
			if (FAILED(hr))
			{
				MessageBox(NULL, TEXT("FAILURE TO INVOKE SumoftwoIntegers!!"), TEXT("COM FAILURE"), MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			//
			iSum = vretval.lVal;
			wsprintf(str, TEXT("Sum is %d"), iSum);
			MessageBox(NULL, str, TEXT("ADDITION"), MB_OK);

			hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName2, 1, GetUserDefaultLCID(), &dispid);
			if (FAILED(hr))
			{
				MessageBox(NULL, TEXT("FAILURE IN GetIDsOfNames!!"), TEXT("COM FAILURE"), MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			//using the above obtainer unique dispatch id, call Invoke(). To invoke sum of two integers functionality
			hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &params, &vretval, NULL, NULL);
			if (FAILED(hr))
			{
				MessageBox(NULL, TEXT("FAILURE TO INVOKE SubtractionoftwoIntegers!!"), TEXT("COM FAILURE"), MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			//
			iSub = vretval.lVal;
			wsprintf(str, TEXT("Subtraction is %d"), iSub);
			MessageBox(NULL, str, TEXT("ADDITION"), MB_OK);

			//assach subtract sathi

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
			VariantClear(&vretval);
			VariantClear(vArgs);
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
	if (pIDispatch)
	{
		pIDispatch->Release();
		pIDispatch = NULL;
	}
}

//link.exe Window.obj Window.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
//rc.exe Window.rc