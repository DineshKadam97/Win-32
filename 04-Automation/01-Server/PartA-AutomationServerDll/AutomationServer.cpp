//WRT ClassFactoryDllServerWithRegFile.cpp there are total 14 changes in AutomationServer.cpp and they are marked at appropriate locations.

#include<windows.h>
#include<stdio.h> //Chnage 1 :
#include"AutomationServer.h"

//class declarations
class CMyMath : public IMyMath //Change 2 : For the first time co-class is inheritinig from only one single interface
{
private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo; //Change 3 : microsoft cha interface

public:
	//constructor method declarations
	CMyMath(void);

	//destructor method declarations
	~CMyMath(void);

	//IUknown specific method declarations (inherited)(panjoba che functions)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//Change 4(A) : 
	//IDispatch specific method declarations (inherited)(aajoba che functions)
	HRESULT __stdcall GetTypeInfoCount(UINT *);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	//Baapache functions
	//IMyMath Specific method declarations (inherited) 
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	//IMyMath Specific method declarations (inherited) 
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	//Change 4(B) :
	HRESULT InitInstance(void); //type library load karnyach kaam aahe yach
};

//Declaring Type 
class CMyMathClassFactory : public IClassFactory //class factory co-class che object tayar karte! IClassfactory ha COM cha interface aahe
{
private:
	long m_cRef;
public:
	//constructor method ddeclarations
	CMyMathClassFactory(void);

	//destructor method declarations
	~CMyMathClassFactory(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassSubFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);

	HRESULT __stdcall LockServer(BOOL);
};

//global DLL handle
HMODULE ghModule = NULL;

//global variable declarations
long glNumberOfActiveComponents = 0; //number of active components
long glNumberOfServerLocks = 0; //number of locks on this dll

//Change 5 : Declaring type library GUID in cpp global variables.
// {30E5D77D-9DEC-44C9-A4EC-A76E057768CD}
const GUID LIBID_AutomationServer = { 0x30e5d77d, 0x9dec, 0x44c9, 0xa4, 0xec, 0xa7, 0x6e, 0x5, 0x77, 0x68, 0xcd };


//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
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
	}

	return(TRUE);
}

/*************************************************************************************************
// Implementation of Co-Class CMyMath
*************************************************************************************************/

//Implementation of CMyMath's construcctor method
CMyMath::CMyMath(void)
{
	//harcoded initialization to anticipate possible  failure of QueryInterface()
	m_cRef = 1;
	m_pITypeInfo = NULL; //Change 6(A)

	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
}

//Implementation of CMyMath's destrucctor method
CMyMath :: ~CMyMath(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter

	//Change 6(B)
	if (m_pITypeInfo)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
	}
}

//Implementation of CMyMath's iUnknown Methods
HRESULT CMyMath::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IMyMath)
		*ppv = static_cast<IMyMath*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return (S_OK);
}

ULONG CMyMath::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMyMath ::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		//m_pITypeInfo->Release();
		//m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	
	return(m_cRef);
}

// Implementation of IDispatch's methods
//Change 8 : 
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo) //Interface Definition Language(IDL) File
{
	// as we have type library it is 1, else 0
	*pCountTypeInfo = 1; //karan IDispatch la inherit karun yenar ekach interface aahe
	return(S_OK);
}

//Change 9 :                //index of type info //locale chi guid   //info of typeinfo
HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
{
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
		return(DISP_E_BADINDEX);
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);
}

//Change 10 :                  //IID_NULL   //registered names(interface pan register honar, services che naav pan ) 
HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, 
								UINT cNames, //kiti names pathvnar aahes?
								LCID lcid, 
								DISPID* rgDispId) //tokens cha array dila tar ithe pan array
{
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId)); //COM ch helper function
}

//Change 11 : 
HRESULT CMyMath::Invoke(DISPID dispIdMember, //FUNCTIONALITY CHI ID
						REFIID riid, //INTERNAL USE SATHI
						LCID lcid, //INTERNAL USE SATHI
						WORD wFlags, //DISPATCH_METHOD/DISPATCH_PROPERTY
						DISPPARAMS* pDispParams, //WHICH PARAMTERS MUST BE PASSED TO THE FUNCTIONS YOU ARE INVOKING
						VARIANT* pVarResult, //GENERIC RETURN VALUE
						EXCEPINFO* pExcepInfo, //EXCEPTION
						UINT* puArgErr)  //ERROR IF ANY
{
	// variable declarations
	HRESULT hr;
	hr = DispInvoke(this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr);
	return(hr);
}


//Implementation of ISum's Methods
HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int* psum)
{
	*psum = num1 + num2;

	return (S_OK);
}

//Implementation of ISubtract's Methods
HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int* psubtract)
{
	*psubtract = num1 - num2;

	return (S_OK);
}

//Change 12 : 
HRESULT CMyMath::InitInstance(void)
{
	// function declarations
	void ComErrorDescriptionString(HWND, HRESULT);
	// variable declarations
	HRESULT hr = S_OK;
	ITypeLib* pITypeLib = NULL; //type library madhun yeto
	// code
	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer,
			1, 0,// major/minor version numbers
			0x00,// LANG_NEUTRAL
			&pITypeLib); //Type library la load kart
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo); //Typeinfo of guid of interface whos providing service
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			pITypeLib = NULL;
			return(hr);
		}
		pITypeLib->Release();
		pITypeLib = NULL;
	}
	return(S_OK);
}

/*************************************************************************************************
// Implementation of CMyMathClassFactory
*************************************************************************************************/

//Implementation of CSumSubtarctfactory's Constructor Mehtod
CMyMathClassFactory::CMyMathClassFactory(void)
{
	m_cRef = 1; //hardcoded inititalization to anticipate possible failure of QueryInterface()
}

//Implementation Of CMyMathClassFactory's Destructor Method
CMyMathClassFactory :: ~CMyMathClassFactory(void)
{
	//no code
}

//Implementation of CMyMathClassFactory's OClassFactory's IUnknown's Methods
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return(S_OK);
}

ULONG CMyMathClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return(m_cRef);
}

ULONG CMyMathClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);

		return(0);
	}

	return(m_cRef);
}

//Implementation Of CMyMathfactory's iClassFactory's methods
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declarations
	CMyMath* pCMyMath = NULL;
	HRESULT hr = S_OK;

	//code
	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	//create the instance of component i.e. of CMyMath class
	pCMyMath = new CMyMath;

	if (pCMyMath == NULL)
		return(E_OUTOFMEMORY);

	// call automation related init method
	pCMyMath->InitInstance();

	//get the requested interface
	hr = pCMyMath->QueryInterface(riid, ppv);

	pCMyMath->Release(); // anticipate possible failure of QueryInterface()
	return(hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);
}

//Implementing two procedural exportable functions DllGetClassObject and DllCanUnloadNow

//Implementation Of Exported Functions From This Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//variable declarations
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr = S_OK;

	//code
	if (rclsid != CLSID_MyMath)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create class factory. From procedure oriented to object oriented programming!
	pCMyMathClassFactory = new CMyMathClassFactory;

	if (pCMyMathClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release(); //anticipate possible failure of QueryInterface();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE); //error nahi, success value aahe, e.g. toss heads/tails
}

//hwnd/hresult chya errors in string format milnyasathi he function use karto
void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	// variable declarations
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr); //microsoft windows relared errors
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0,
		NULL) != 0)
	{
		//swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		wsprintf(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		wsprintf(str, TEXT("[Could not find a description for error # %#x.]\n"),hr);
	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}

//// Registers DLL with COM into system registry
//STDAPI DllRegisterServer()
//{
//	HKEY hCLSIDKey = NULL, hInProcSvrKey = NULL;
//	LONG lRet;
//	TCHAR szModulePath[MAX_PATH];
//	TCHAR szClassDescription[] = TEXT("Automation COM class");
//	TCHAR szThreadingModel[] = TEXT("Apartment");
//	__try
//	{
//		// Create a key under CLSID for our COM server.
//		// 32bit server on 32bit OS -> HKEY_CLASSES_ROOT\CLSID\{71169462-E879-4B9B-
//		// ACFF-FB718082D292}
//		// 32bit server on 64bit OS ->
//		// HKEY_CLASSES_ROOT\Wow6432Node\CLSID\{71169462-E879-4B9B-ACFF-
//		// FB718082D292}
//		// 64bit server on 32bit OS -> Invalid
//		// 64bit server on 64bit OS -> HKEY_CLASSES_ROOT\CLSID\{71169462-E879-4B9B-
//		// ACFF-FB718082D292}
//		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{4A529D3E-9133-4840-BAB2-22B5E061EB91}"),
//			0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE |
//			KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);
//		if (ERROR_SUCCESS != lRet)
//			return HRESULT_FROM_WIN32(lRet);
//		// The default value of the key is a human-readable description of the
//		//co class
//
//		lRet = RegSetValueEx(hCLSIDKey, NULL, 0, REG_SZ, (const BYTE*)szClassDescription,
//			sizeof(szClassDescription));
//		if (ERROR_SUCCESS != lRet)
//			return HRESULT_FROM_WIN32(lRet);
//		// Create the InProcServer32 key, which holds info about our coclass.
//		lRet = RegCreateKeyEx(hCLSIDKey, TEXT("InProcServer32"), 0, NULL,
//			REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hInProcSvrKey, NULL);
//		if (ERROR_SUCCESS != lRet)
//			return HRESULT_FROM_WIN32(lRet);
//		// The default value of the InProcServer32 key holds the full path to our DLL.
//		GetModuleFileName(ghModule, szModulePath, MAX_PATH);
//		lRet = RegSetValueEx(hInProcSvrKey, NULL, 0, REG_SZ, (const BYTE*)szModulePath,
//			sizeof(TCHAR) * (lstrlen(szModulePath) + 1));
//		if (ERROR_SUCCESS != lRet)
//			return HRESULT_FROM_WIN32(lRet);
//		// The ThreadingModel value tells COM how it should handle threads in our DLL.
//		lRet = RegSetValueEx(hInProcSvrKey, TEXT("ThreadingModel"), 0,
//			REG_SZ, (const BYTE*)szThreadingModel, sizeof(szThreadingModel));
//		if (ERROR_SUCCESS != lRet)
//			return HRESULT_FROM_WIN32(lRet);
//	}
//	__finally
//	{
//		if (NULL != hCLSIDKey)
//			RegCloseKey(hCLSIDKey);
//		if (NULL != hInProcSvrKey)
//			RegCloseKey(hInProcSvrKey);
//	}
//	return S_OK;
//}
//
//// Unregisters DLL from system registry
//STDAPI DllUnregisterServer()
//{
//	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{4A529D3E-9133-4840-BAB2-22B5E061EB91}\\InProcServer32"));
//		RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{4A529D3E-9133-4840-BAB2-22B5E061EB91}"));
//	return S_OK;
//}
