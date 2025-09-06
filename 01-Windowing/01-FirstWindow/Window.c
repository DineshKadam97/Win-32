#include<windows.h>

//Global callback function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Entry-point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("DDK_Window");
	HWND hwnd;
	MSG msg;

	//code
	memset((void*)&wndclass, 0, sizeof(WNDCLASSEX));//memory la set kar, wndclass chya address pasun pudh sizeof(WNDCLASSEX) evdhya bytes
	                                                //0 la set kar

	//Initializing Window Class
	wndclass.cbSize = sizeof(WNDCLASSEX); // count of bytes showing the size of the structure, cb mhnje count of bytes(navin aalela member)
	wndclass.style = CS_HREDRAW | CS_VREDRAW; // style of this window class, this is not window style, this is window class style
	                                          //CS => Class Style, ubhi zali/advi zali ki rang redraw zali pahije
	                                         //CS_HREDRAW => Horizontal, CS_VREDRAW => Vertical
	wndclass.cbClsExtra = 0; //hya windows chya prakarabaddal kahi extra mahiti dyaychi aahe ka?(e.g. pushbutton che prakar => ok, cancel etc)
	wndclass.cbWndExtra = 0; //extra information about the this window
	wndclass.hInstance = hInstance; //handle to the current instance of a process, jichya madhey hi window tayar honar aahe

	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //handle(ID) to brush which will be used for window background jo background la rang deto
	                                                            //GetStockObject() is used for getting stock madhla object milav, 
																//Parameter => WHITE_BRUSH milav stock madla object
												//GetStockObject chi return type HBRUSH nahiye, GetStockObject mhnje do down madhun kahitari(kahipan) aanun de
	                                            //GetStockObject gives handle to any GDI object(HGDIOBJ), return type HGDIOBJ hi  aahe, 
												// Brush(HBRUSH), pen(HPEN), font(HFONT) as kahihi deu shakto
	//HICON
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //first parameter => hInstance expect karto, jevha dusrya parameter la jar valid icon file deu shakat asal
	                                                   //tarch pahila hInstance dyaycha, default execuatble cha icon aahe to de as win32 la mhntoy, 
	                                                   //identifier of icon of application, .ico file customised icon
	//HICON												  //return type HICON
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //there are total 3 icons => caotion bar madhey left top la,
	                                                    //explorer madhla
	                                                    //task Bar madhey disto to
	                                                    //hIconSm , sm mhnje small(navin aalela member)
	//HCURSOR
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);   //Return type HCURSOR, jasa icon ch tasch yanch sudha, jo pahije, jasa pahije tasa cursor
													//.cur file, customised cursor, icon sarakhach pahila hInstance pahije pan dusri valid .cur file pahije
												  //IDC_ARROW => Identifier of a cursor, ithe NULL mhnje default vapar asa aahe, mala mahiti nahi OS tu default ghe
	                                              //baryach veles NULL mhje default value consider kar aasa hou shakto
												  // 
	//long pointer to function of window procedure
	wndclass.lpfnWndProc = WndProc;    //MOST IMP member of WNDCLASSEX, WndProc => Window Procedure, CALLBACK function cha address deto aapan OS la kalava mhnun

	//long pointer to zero terminated string
	wndclass.lpszClassName = szAppName; //Window Class la kaay nav denar? Window Class Name

	wndclass.lpszMenuName = NULL; //Menu asel tar MENU cha naav

	//Register the above Window Class
	RegisterClassEx(&wndclass); //return type ATOM => ATOM RegisterClassEx(WNDCLASSEX *);
	                            //ATOM is special type of immutable string, jasa atom immutable asto tas
								//ATOM string ashi tayar hote =>lpszAppName chya naava mag pudh kahi unique chaacters 
								// laun te naav (ti unique string) register hot OS kade

	//Create the Window
	hwnd = CreateWindow(szAppName,//Name of your window class
		TEXT("DDK : My First Window"), //text you want to display in your caption bar
		WS_OVERLAPPEDWINDOW,  //WS => Window Style, Individual Window Style(WS), Overlapped Window
		                      //WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX
		CW_USEDEFAULT,   //CW create window sathiche defualt value vapar, Desktop chya origin pasun kiti dur X
		CW_USEDEFAULT, //desktop origin pasun khali kiti pixel Y cor-ordinate asava
		CW_USEDEFAULT,  //width of the window in pixel
		CW_USEDEFAULT,  //height of the window in pixel
		NULL,          //HWND of parent window, ithe NULL mhnje default value dya, by default Desktop baap hoto, HWND_DESKTOP pan pathvu shakto
		NULL,         //HMENU expect karto, Handle to Menu. Mazyakade nahiye mhnun NULL
		hInstance,    //Hnadle of the current instance of the process
		NULL);       //tula 10 sodun ajun kahi info dyaychi asel tar yat de! 
	                //Explain more about the 11th parameter of the create window

	//create window creates the window only in memory not on screen!!! 
	//create window returns HWND hwnd and we use it to show window
	//showwindow aani updatewindow kelyashivay window screen var disat naste

	//Show the Window
	ShowWindow(hwnd, iCmdShow); //SW_MAXIMIZE SW_MINIMIZE => iCmdShow SW_HIDE SW_NORMAL

	//Update the Window
	UpdateWindow(hwnd); //window la rang UpdateWindow mule milato, Brush gheun bhint rangav he sangan UpdateWindow ch kaam aahe

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0)) //adress of MSG object, 2nd, 3rd, 4th paramter? why NULL, 0, 0
	{
		TranslateMessage(&msg); //Translate Message kuthlya message sathi waparl jaat? aani sop kas kart?
		DispatchMessage(&msg); //Registered wndclass la jaat aani lpfnwndproc la jaun CALLBACK function la call jato
	}                          // MSG members => .hwnd, .msg, WPARAM?, LPARAM?, time, point(x,y)
	                          ///msg cha gola aplya windowchya pungalit dhaklya jaatat aani apli window suck karte
	return((int)msg.wParam); //ata msg madhey WM_QUIT aahe, tyacha wParam 0 aahe mnhnject return 0 which indicates success
}

//Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//variable declarations

	//code
	//switch (iMsg)
	//{
	//	case WM_DESTROY:		//Message Handler : case-break lihine
	//		PostQuitMessage(0); //OS la sangitl jaat, quit message la post kar, WM_QUIT, golyamadhey ha message pathvla jato
	//		                    //aplyach window la!
	//							// Parameter of PostQuitMessage is wParam of WM_QUIT, usually lParam is also 0
	//							//WM_QUIT is the only message for which GetMessage returns 0(false)!!
	//							// GetMessage chi return type BOOL aahe, TRUE or FALSE
	//							//WM_DESTROY NE window jaate(fukl) aani WM_QUIT ne process marte(pind-daan)!!
	//		break;

	//	default:
	//		break;
	//}
	switch (iMsg)
	{
	case WM_CREATE:      //Message Box madhey kaay text pahije?
		MessageBox(NULL, TEXT("WM_CREATE ARRIVED"), TEXT("MESSAGE"), MB_OK); //NULL parent window cha handle kaay? ithe by defualt ghe as mhntoy
		break;                                     //Message Box chya caption madhey kaay pahije //4th parameter mahiti kara

	case WM_DESTROY:
		MessageBox(NULL, TEXT("WM_DESTROY ARRIVED"), TEXT("MESSAGE"), MB_OK);
		PostQuitMessage(0);
		break;
	}


	return(DefWindowProc(hwnd, iMsg, wParam, lParam)); //default window procedure aahe,
												//OS kade pathvle jatat, send all handled and unhandked messages goes to OS only!!
													//minimum ek message pahijech WM_DESTROY cha
													//aapn ekach handle kela pan baki 399 messages OS kade pathvle jatat 
}


//Event driven architecture and Messsage Loop

//19 June 2025
//EHSc => Exception handling and synchronous catch
//Desktop mhnje study table varun aalay => study table var vahya, pustak, crayons, music player, dustbin
// study desk cha top => asa alay desktop!!

//Kuthlihi window dusrya windowchya war naste, desktop chya pan var naste karan te 2D aahe, resolution : 1920*1080 mhnjech 2D aahe!
//Paint Desktop chya var, Notepad Desktop chya var etc etc. as mhnan Sagal Chuk!!
//Notepad desktop cha bhaag aahe, MS-paint desktop cha bhaag aahe!
//icons desktop cha bhaag aahet
//taskbar is a part of the desktop!!

//Notepad open kela mnhje, jya bhagamadhey apan open kelelya dimesion evdh desktop fadun tyat notepad fit hoto!!
//aani notepad band kela mhnje desktop punha "repaint" hote!!

//aplyala vatat apan right click notepad, paint, aplya windowvar kartoy, pan he sagle desktop che bhaag aahet mhjech right click "desktop" var hoto.
//right click desktop chya ashya area var hotoy jo area notepad konva paint kinva aplya window ne vyaplay!!
//desktop te co-irdinate OS la pathvto(OS la kaltach, karan OS cha sagle karte) aani mag OS ticha table madhey co-ordinates baghun respective
//window madhey right click kelea event nantr kaay karayachay he tya process madhey baghun output dete


//Create window warun window chi position aani widhth aani height kalate, 
//creatwindow chi return value hwnd(handle to window) aste
//aani OS kade hya hwnds cha table asto, application and their respective hwnd
//OS global HWND table

//tumcha left click, right click, typing he sagl desktop la jaat aani OS tyavar action ghete!!

//jas notepad window notepad process cha chehara, paint ha paint process cha chehara tasa OS cha chehara desktop!!!
//saglya process cha baap OS tasa saglya window cha baap Desktop!!

//videos => jevdha windows cha area tevdha => frame buffer => window chya size evdhe buffer create kele jatat!(size of rendering area)
//back to back buffer swap kele jatat

//Media Player chi wondow => directX surface aahe, window which is ready to recieve directX frame buffer with specified color format, alpha, width depth, stensil
// buffers, 

//z order is maintained illusion wised whos topmost and active in case of overlapping windows

//23 Juune 
//Translate Message pasun pudhe!!
// Digestion ch udaharan, poli, bhat, varan la protien, lipids, fats madhey sop karto
//tas translate message keyboard varchya keys(characters, digits, function keys, esc, symbols, enter, 
// complex keys), caps lock, enter, insert, delete, print, alt etc,
//apan jevha key press karto tevha (WM_KEYDOWN (WM => Window Message) ha message jato.
// Translate message shodth key WM_KEYDOWN gehun baght ki nemki kuthli ki click zali aani tyanusar simplify karun 
// DispatchMessage la Pathvat
// Pass By Pointer cha uttam usage
// Translate Message is the digestion of complex message into simpler message. jas poli, bhat ch lipid, fats, protiens hotat tas
// address pathvto aani translate message tyach address var jaun sop karto
// toch address dispatchMessage la pan address pathvto(&msg)
// All the functions are working unitedly on the same address  
//  
// Deoxygenated Blood in right atrium

//Message Looop is nothing but Message Pump as Message loop pumps messages like heart pumps the blood.
// GetMessage(&msg, NULL, 0, 0) dusra hwnd jiche messaged aplyayla ghyaychet expect aahe pan NULL deto aapan
// NULL ka? ata ekti window aahe nantr child windows zalya tar tyanche messages pan ghyayche aahet,
// Ithe NULL te indicate karto, let this null be default value indicating i want both my and my child window messages!!
// first 0 => sagle message WM_KEYDOWN sagle macros aahe, hi range aahe =, minimum
// second 0 => te maximum, donhi kade 0 mhje default aahet, 
// i dont have any minimum or maximum limit, let all messages come
// WM_LBUTTONDOWN => JEVHA APAN WINDOW CLOSE KARTO TEVHA
// translate message mhnto ha sadha LBUTTONDOWN nahiye, ha close warti click zalay, mag translate message 
//WM_LBUTTONDOWN la WM_DESTROY madhey convert karto!!

//24 June
//WPARAM : Message baddal choti information
//LPARAM : Message baddal moti information
//For every message WPARAM aani LPARAM wegle astat, unique astat, 
//tyamulech yana Message Parameters mhntat, they are unique and different for every message!
//Gahu aani Pani ek kkilo, ek liter, he aahet tyanche tyanche parameters
//LBUTTONDOWN : WPARAM => left mouse button click hot astana keyboard warchi key press zali hoti ka(macros astat MK_RBUTTON), macro sathi kami jaga lagte
//LPARAM : click che co-ordinates(x and y)
//WM_SIZE : 
//LPCREATESTRUCT, along with cbClsExtra cbWndExtra for complex applications
//WM_CREATE cha LPARAM te structure aahe which has 10 Paramters of Create WIndow