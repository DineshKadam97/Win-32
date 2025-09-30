//Changes in AggregationInnerDllServer.cpp are with respect to ContainmentInnerDllServer.cpp are:
//There are total 12 changes that are marked at appropriate places

#define UNICODE
#include<windows.h>
#include"AggregationInnerDllServer.h"

// Change 1 : Declaring our own IUnknown named INoAggregationIUnknown
interface INoAggregationIUnknown // new
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0; 
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

//class declarations
//Change 2 : Now Aggregation inner Co-class( CMultiplicationDivision) will first inherit from INoAggregationIUnknown and then IMultiplication, IDivision
class CMultiplicationDivision : public INoAggregationIUnknown, IMultiplication, IDivision //// CSubtract => Co Class, Concrete class, Component class, Implementer class (super class => sub class)
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownOuter; //Change 3 : In Aggregation inner's Co-class private member data, declare IUnknown* to store IUnknown of Aggregation outer component.

public:
	//Chnage 4(A) : For the first time constructor of aggregation inner co-class is gonna be parameterised and the parameter is IUnknown*
	//constructor method declarations
	CMultiplicationDivision(IUnknown* ); 

	//destructor method declarations
	~CMultiplicationDivision(void);

	//Change 4(B) : Declaring the INoAggregationIUnknown(our own IUnknown) functions first.
	//INoAggregationIUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);

	//IUknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum Specific method declarations (inherited) 
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	//ISubtract Specific method declarations (inherited) 
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiPlicationDivisionClassFactory : public IClassFactory //class factory co-class che object tayar karte! IClassfactory ha COM cha interface aahe
{
private:
	long m_cRef;
public:
	//constructor method ddeclarations
	CMultiPlicationDivisionClassFactory(void);

	//destructor method declarations
	~CMultiPlicationDivisionClassFactory(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassSubFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);

	HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0; //number of active components
long glNumberOfServerLocks = 0; //number of locks on this dll

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
// Implementation of Co-Class CMultiplicationDivision
*************************************************************************************************/

//Implementation of CMultiplicationDivision's construcctor method
CMultiplicationDivision::CMultiplicationDivision(IUnknown* pIUnknownOuter)
{
	//harcoded initialization to anticipate possible  failure of QueryInterface()
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
	MessageBox(NULL, TEXT("INNER MEIN CMultiplicationDivision SUCCESS!!"), TEXT("INNER ERROR"), MB_ICONERROR);

	//Change 5 : Assigning aggregation outer's IUnknown pointer to inner's IUnknown* pIUnknownOuter which is private member variable.
	if (pIUnknownOuter != NULL)
	{
		m_pIUnknownOuter = pIUnknownOuter;
		MessageBox(NULL, TEXT("INNER MEIN pIUnknownOuter SUCCESS!!"), TEXT("INNER ERROR"), MB_ICONERROR);
	}
	else
	{
		m_pIUnknownOuter = reinterpret_cast<IUnknown*>(static_cast<INoAggregationIUnknown*>(this));
		MessageBox(NULL, TEXT("INNER MEIN INoAggregationIUnknown SUCCESS!!"), TEXT("INNER ERROR"), MB_ICONERROR);
	}
}

//Implementation of CMultiplicationDivision's destrucctor method

CMultiplicationDivision :: ~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter
}

//Implementation of CMultiplicationDivision's iUnknown Methods
//Change 6 : 
HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<INoAggregationIUnknown*>(this);
		MessageBox(NULL, TEXT("INNER MEIN QueryInterface_NoAggregation SUCCESS!!"), TEXT("INNER ERROR"), MB_ICONERROR);
	}
	else if (riid == IID_IMULTIPLICATION)
	{
		*ppv = static_cast<IMultiplication*>(this);
		MessageBox(NULL, TEXT("INNER MEIN IID_IMULTIPLICATION SUCCESS!!"), TEXT("INNER ERROR"), MB_ICONERROR);
	}
	else if (riid == IID_IDIVISION)
	{
		*ppv = static_cast<IDivision*>(this);
		MessageBox(NULL, TEXT("INNER MEIN IID_IDIVISION SUCCESS!!"), TEXT("INNER ERROR"), MB_ICONERROR);
	}
	else
	{
		*ppv = NULL;
		MessageBox(NULL, TEXT("INNER MEIN QueryInterface_NoAggregation ERROR!!"), TEXT("INNER ERROR"), MB_ICONERROR);
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef(); // call AddRef_NoAggregation la call jato, "method coloring" mule AddRef() chya jagi AddRef_NoAggregation
	                                             //AddRef_NoAggregation() la call jato, karan donhi AddRef() aani AddRef_NoAggregation() 
												 //sarkhech function aahet 

	return (S_OK);
}

//Change 7 : 
ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

//Change 8 : 
ULONG CMultiplicationDivision::Release_NoAggregation(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	
	return(m_cRef);
}

//Change 9 : 
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	return (m_pIUnknownOuter->QueryInterface(riid, ppv));
}

//Change 10 : 
ULONG CMultiplicationDivision::AddRef(void)
{
	return (m_pIUnknownOuter->AddRef());
}

//Change 11 : 
ULONG CMultiplicationDivision::Release(void)
{
	return (m_pIUnknownOuter->Release());
}

//Implementation of ISum's Methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* psum)
{
	*psum = num1 * num2;

	return (S_OK);
}

//Implementation of ISubtract's Methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* psum)
{
	*psum = num1 / num2;

	return (S_OK);
}

/*************************************************************************************************
// Implementation of CMultiPlicationDivisionClassFactory
*************************************************************************************************/

//Implementation of CMultiPlicationDivisionClassFactory's Constructor Mehtod
CMultiPlicationDivisionClassFactory::CMultiPlicationDivisionClassFactory(void)
{
	m_cRef = 1; //hardcoded inititalization to anticipate possible failure of QueryInterface()
}

//Implementation Of CMultiPlicationDivisionClassFactory's Destructor Method
CMultiPlicationDivisionClassFactory :: ~CMultiPlicationDivisionClassFactory(void)
{
	//no code
}

//Implementation of CMultiPlicationDivisionClassFactory's OClassFactory's IUnknown's Methods
HRESULT CMultiPlicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CMultiPlicationDivisionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return(m_cRef);
}

ULONG CMultiPlicationDivisionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);

		return(0);
	}

	return(m_cRef);
}

//Implementation Of CMultiPlicationDivisionClassFactory's iClassFactory's methods
HRESULT CMultiPlicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declarations
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr = S_OK;

	//code
	//Change 12(A) : If pUnkOuter is not NULL which means it is valid pointer, then riid must be IID_IUnknown
	if (pUnkOuter != NULL && riid != IID_IUnknown)
	{
		//MessageBox(NULL, TEXT("INNER MEIN pUnkOuter ERROR!!"), TEXT("INNER ERROR"), MB_ICONERROR);
		return (CLASS_E_NOAGGREGATION);
	}

	//create the instance of component i.e. of CMultiplicationDivision class
	//Change 12(B) : Passing parameter while creating an object
	pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);

	if (pCMultiplicationDivision == NULL)
	{
		//MessageBox(NULL, TEXT("INNER MEIN pCMultiplicationDivision ERROR!!"), TEXT("INNER ERROR"), MB_ICONERROR);
		return(E_OUTOFMEMORY);
	}

	//Change 12(C) : 
	// get the requested interface
	hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv); //m_pIUnknownInner madhey => INoAggregationIUnknown jato
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("pCMultiplicationDivision HR FAILED"), TEXT("INNER ERRROR"), MB_ICONERROR);
	}
	// anticipate possible failure of QueryInterface()
	pCMultiplicationDivision->Release_NoAggregation();
	return(hr);
}

HRESULT CMultiPlicationDivisionClassFactory::LockServer(BOOL fLock)
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
	CMultiPlicationDivisionClassFactory* pCMultiPlicationDivisionClassFactory = NULL;
	HRESULT hr = S_OK;

	//code
	if (rclsid != CLSID_MultiplicationDivision)
	{
		MessageBox(NULL, TEXT("INNER MEIN pCMultiplicationDivision ERROR!!"), TEXT("INNER ERROR"), MB_ICONERROR);
		return(CLASS_E_CLASSNOTAVAILABLE);
	}

	//create class factory. From procedure oriented to object oriented programming!
	pCMultiPlicationDivisionClassFactory = new CMultiPlicationDivisionClassFactory;

	if (pCMultiPlicationDivisionClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCMultiPlicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiPlicationDivisionClassFactory->Release(); //anticipate possible failure of QueryInterface();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE); //error nahi, success value aahe, e.g. toss heads/tails
}
