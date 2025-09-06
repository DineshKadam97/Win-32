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
	HBRUSH hBrush = NULL;
	static unsigned int iPaintFlag = 0; //default value 0 for black color

	switch (iMsg)
	{
		case WM_CREATE:      //Message Box madhey kaay text pahije			
			break;                                     

		case WM_PAINT: //WM_PAINT madhey fakt painting cha kaam kara
			//Zero out the memory of Rect struct variable
			memset((void*)&rect, 0, sizeof(RECT));

			//get the window client area rectangle
			GetClientRect(hwnd, &rect); //mazya client area che dimensions rect madhey bharun de
			
			//zero-out the memory of PAINTSTRUCT variable
			memset((void*)&ps, 0, sizeof(PAINTSTRUCT));

			//Obtain the HDC painter
			hdc = BeginPaint(hwnd, &ps);

			//Create Brush of desired Color
			switch (iPaintFlag)
			{
				case 1: //R-Red 
					hBrush = CreateSolidBrush(RGB(255, 0, 0));
					break;

				case 2: //G-Green
					hBrush = CreateSolidBrush(RGB(0, 255, 0));
					break;

				case 3: //BLUE
					hBrush = CreateSolidBrush(RGB(0, 0, 255));
					break;

				case 4: //Cyan
					hBrush = CreateSolidBrush(RGB(0, 255, 255));
					break;

				case 5: //MAGENTA
					hBrush = CreateSolidBrush(RGB(255, 0, 255));
					break;

				case 6://Y-Yellow
					hBrush = CreateSolidBrush(RGB(255, 255, 0));
					break;

				case 7://O-orange
					hBrush = CreateSolidBrush(RGB(255, 128, 0));
					break;

				case 8://V-Violet
					hBrush = CreateSolidBrush(RGB(128, 128, 255));
					break;

				case 9: //White
					hBrush = CreateSolidBrush(RGB(255, 255, 255));
					break;

				default:
					hBrush = CreateSolidBrush(RGB(0, 0, 0));
					break;
			}

			//Give the selected brush to the painter
			SelectObject(hdc, hBrush); //kunachya hatat, kaay deu. SelectObject mhje HPEN deu shakta, HFONT. HBRUSH ast tar ekach parameter asta

			//Make the painter color the client area rectangle with selected brush
			FillRect(hdc, &rect, hBrush);
			//Delete the brush
			if (hBrush)
			{
				DeleteObject(hBrush);
				hBrush = NULL;
			}

			if (hdc)
			{
				//Release the HDC painter
				EndPaint(hwnd, &ps);
				hdc = NULL;
			}
			break;

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

		case WM_CHAR:
			switch (wParam)
			{
			   case 'R': //RED
			   case 'r':
				   iPaintFlag = 1;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   case 'G': //GREEN
			   case 'g':
				   iPaintFlag = 2;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   case 'B': //BLUE
			   case 'b':
				   iPaintFlag = 3;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE, InvalidateRect Posts the WM_PAINT
				   break;

			   case 'C': //Cyan
			   case 'c':
				   iPaintFlag = 4;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   case 'M': //MAGENTA
			   case 'm':
				   iPaintFlag = 5;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   case 'Y': //YELLOW
			   case 'y':
				   iPaintFlag = 6;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   case 'O': //ORANGE
			   case 'o':
				   iPaintFlag = 7;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   case 'V': //VIOLET
			   case 'v':
				   iPaintFlag = 8;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   case 'W': //White
			   case 'w':
				   iPaintFlag = 9;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   case 'K': //BLACK
			   case 'k':
				   iPaintFlag = 0;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
				   break;

			   default:
				   iPaintFlag = 0;
				   InvalidateRect(hwnd, NULL, TRUE); //kunacha repaint karu, NULL sagla client area repaint kar, REPAINT kar => TRUE
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

//30 June
//rgbckoywm