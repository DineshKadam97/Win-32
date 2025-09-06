#include<windows.h>

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = pszAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);

	//Window ch aayushya CreateWindow la suru hot, aani WM_DESTROY nantr sampt
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
		NULL); //ithun SendMessage through WM_CREATE pathvla jato, conrtol WNdProc madhey tithe WM_CREATE handle karun break houn control
	//punha createWindow kade yeto, ithun pudhe ShowWindow, UpdateWindow houn MessageLoop pashi control jato
	//SendMessages(Software Messages) are synchronous!!!
	//LPCREATESTRUCT type aani tyache members mhnje aadhiche 10 parameters
	//WM_CREATE cha lparam mhnje LPCREATESTRUCT aahe, aapan ha parameter deun apan multiwindow, complex programming karu shakto
	//cbClsExtra, cbWndExtra

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) //Posted Message are asynchronous
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
	TCHAR str[255];
	unsigned int x = 0;
	unsigned int y = 0;

	switch (iMsg)
	{
		case WM_CREATE:      //Message Box madhey kaay text pahije?
			MessageBox(NULL, TEXT("WM_CREATE ARRIVED"), TEXT("MESSAGE"), MB_OK); //NULL parent window cha handle kaay? ithe by defualt ghe as mhntoy, mazya messagebox cha baap desktop aahe
			break;                                     //Message Box chya caption madhey kaay pahije //4th parameter mahiti kara

		case WM_KEYDOWN:   //Keydown zalyanantr kuthli key aahe aani character key asel tar translate message adhi WM_CHAR pathvto aani nantr WM_KEYDOWN yeto! //mhnjech don yetat
			MessageBox(NULL, str, TEXT("MESSAGE KEYDOWN"), MB_OK);
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
			char ch = wParam;
			wsprintf(str, TEXT("Character key pressed is : %c"), ch);
			MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
			break;

		case WM_LBUTTONDOWN:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			wsprintf(str, TEXT("Left Mouse Button Click Co-ordinates are : (%d,%d)"), x, y);
			MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
			break;

		case WM_RBUTTONDOWN:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			wsprintf(str, TEXT("Right Mouse Button Click Co - ordinates are : (%d, %d)"), x, y);
			MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
			break;

		case WM_SIZE: //WM_SIZE window chi size kami jast keli tar ha message yeto, WM_SIZE madhey message box takayla nahi pahije
			//MessageBox(NULL, TEXT("WM_SIZE ARRIVED"), TEXT("MESSAGE"), MB_OK);
			break;

		case WM_DESTROY:
			MessageBox(NULL, TEXT("WM_DESTROY ARRIVED"), TEXT("MESSAGE"), MB_OK);
			//PostQuitMessage(0); //ithe window cha aayushya sampt
			PostMessage(hwnd, WM_QUIT, 0, 0);
			break;

		default:
			break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


//Messages che 2 prakar : Hardware Messages, Software Messages
//All the hardware messages go through Message Looop and there are only 2 software messages go through message loop(WM_QUIT)
//Software Messages have functions and by using which these messages get send. e.g. CreateWindow(WM_CREATE)
//Software message sarti OS directly calls WndProc at that point where software message pathvla gela pahije
//Interrupt is a life saving mechanism
//Hardwware Messages la process whayla vel lagto : Ice Cream khalyavar sardi hone, DispatchMessage (Posting of Message), Posted Messages
//Thakasi To Mahathak : Software Message, Sending of Message(Sent Messages)
//
//tumchya windows la yenara pahila message jo ekdach yeto tyach naav aahe WM_CREATE.To software message aahe
//PostMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) => hardware messages sathi
//WM_CREATE chya aat => SendMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) => software message sathi aani he jata wnd proc la
//CreateWindow atmadhey WM_CREATE => SendMessage through call jato
// 
// 
//GetMessage => TranslateMessage => DispatchMessage => PostMessage(hwnd, WM_QUIT, 0, 0) (Hardware Messages)

//Aaj Paryntacha sagla syllabus VIVA madhey

//24 June
//macros for all non-character keys like ctrl, caps-loc etc, and this is for WM_KEYDOWN message
//aani he macros WPARAM mhnun pathvle jatat fro WM_KEYDOWN
// LBUTTONDOWN cha WPARAM => MACROS, CLICK sobat dusr kahi click kelay ka LPARAM => x and y co-ordinates
// RBUTTONDOWN cha WPARAM => MACROS, CLICK sobat dusr kahi click kelay ka LPARAM => x and y co-ordinates
// WM_SIZE => WPARAM => kashi resize zali
// LPARAM => new widht and height, don ghetle karan don mahiti veglya aahet (e.g. color, wajan)
// 
// ALL ARE WPARAM OF WM_KEYDOWN
//VK_ESCAPE (virtual key code) VK
//VK_NUMPAD0
//VK_NUMPAD2
//VK_ADD(+)
//VK_SUBTRACT(-)
//VK_UP
//VK_DOWN
//VK_RIGHT, VK_LEFT

//19June and 23 June Parat Parat Abhyas
// 
//26 June
//WM_PAINT => DESKTOP/APPLICATION WINDOWS CH REPAINTING hot!!
//8 scenarios in which repainting occurs which means WM_PAINT gets handled by OS or application developer
//6 madhey OS handle karte aplysathi => Jevha Window pahilyanda tayar hote tevha, desktop scrap hoto aani tya area madhey window paint keli jate.
//									 => Jevha System Menu uncovers the window(our window), then repainting of uncovered part is done by the OS.(Re-paint)
//									 => When another window uncovers your window
//									 => When you move your mouse cursor over your window/desktop.(scrap-repaint, scrap-repaint desktop ch aani cursor ch paint)
//									 => When you move Icon over your window.
//									 => When you move your window across the desktop. 
//                                      Mhnjech window halvli ki desktop scrap-repaint hote aani window pan paint hot rahte
// 
// 2 madhey aplyalach karav lagt => Window resize kelyanantr aplyala handle karava lagto, WM_SIZE AND WM_PAINT(MSDN la vacha)
//								 => repainting = Imediate Mode Rendering
// MonitorInfo navach struct 
// COM Automation => Chrome, Edge etc
// COM => Cross-Platform Automation Portability
// Idispatch Interface
// CLIPPING AND CULLING
//Re-triggering of WM_PAINT

//LPCREATESTRUCT 