#include<windows.h>

#include "Window.h"

//Global Callback Declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Process ch aayushya ithun suru hot
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR pszAppName[] = TEXT("DDK_WINDOW");
	HWND hwnd;
	MSG msg;

	memset((void*)&wndclass, 0, sizeof(WNDCLASSEX));

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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

	UpdateWindow(hwnd); //Update window is the first time when we recieve WM_PAINT, WM_PAINT is a send messgae, Update window pathavto

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//aani ithe process ch aayush sampt
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//variable declarations
	static RECT rect;
	HDC hdc = NULL; //handle to device context, hyala painter mhnu shakto
	PAINTSTRUCT ps; //chotyatla chota painting unit
	TCHAR str[] = TEXT("Hello World WinDev-2025");

	switch (iMsg)
	{
		case WM_CREATE:      //Message Box madhey kaay text pahije?
			//MessageBox(NULL, TEXT("WM_CREATE ARRIVED"), TEXT("MESSAGE"), MB_OK); //NULL parent window cha handle kaay? ithe by defualt ghe as mhntoy
/*			memset((void*)&rect, 0, sizeof(RECT));
			GetClientRect(hwnd, &rect);*/ //ithe call dilyavar work hot nahi karan, ITHUN CreateWindow kade janar aani rect destroy honar local variable aahe
			                           //centerally text adjust hot nahi karan jevha tayar keli tevhache(JUNEY) rect parameters aahet
			//WM_CREATE ekdach yeto, fakt suruwatila, tyamule ithun GetClientRect la call deu naka!!
			
			break;                                     //Message Box chya caption madhey kaay pahije //4th parameter mahiti kara

		case WM_PAINT: //WM_PAINT madhey fakt painting cha 
			//Zero out the memory of Rect struct variable
			memset((void*)&rect, 0, sizeof(RECT));

			//get the window client area rectangle
			GetClientRect(hwnd, &rect); //mazya client area che dimensions rect madhey bharun de
			
			//zero-out the memory of PAINTSTRUCT variable
			memset((void*)&ps, 0, sizeof(PAINTSTRUCT));

			//Obtain the HDC painter
			hdc = BeginPaint(hwnd, &ps);

			//Set text background to black color
			SetBkColor(hdc, RGB(0, 0, 0)); //By default color 8-bits cha asto, mhnjech 2 raise to 8 256 aani 0 pasun mhnun max 255
			
			//Set Text Color to green
			SetTextColor(hdc, RGB(0, 255, 0));

			//Draw the text in the Window's Client Area
			DrawText(hdc, str, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); //-1 lihun sangto purn string draw karaychiye
			
			if (hdc)
			{
				//Release the HDC painter
				EndPaint(hwnd, &ps);
				hdc = NULL;
			}
			break;

		//case WM_SIZE: //WINDOW resize kelyavar WM_SIZE nantr WM_PAINT yetoch!!!, whenever you reszie a window you receive WM_PAINT
		//	memset((void*)&rect, 0, sizeof(RECT));
		//	GetClientRect(hwnd, &rect); //IDEAL place to call GetClientRect()
		//	break;

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
			PostQuitMessage(0);
			break;

		default:
			break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

//link.exe Window.obj Window.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
//rc.exe Window.rc

//typedef struct tagRECT
//{
//	LONG    left;
//	LONG    top;
//	LONG    right;
//	LONG    bottom;
//} RECT, * PRECT, NEAR* NPRECT, FAR* LPRECT;

//Device Context navach structure graphics card handle kart, aani device context cha opaque pointer det

//typedef struct tagPAINTSTRUCT {
//	HDC         hdc;
//	BOOL        fErase;
//	RECT        rcPaint;
//	BOOL        fRestore;
//	BOOL        fIncUpdate;
//	BYTE        rgbReserved[32];
//} PAINTSTRUCT, * PPAINTSTRUCT, * NPPAINTSTRUCT, * LPPAINTSTRUCT;

//30 June
//