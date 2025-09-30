/*
	With respect to ContainmentOuterDllServer.cpp there are 6 chnages in AggregationOuterDllServer.cpp, 
	these changes are marked through out the code.
*/
#define UNICODE
#include<windows.h>
#include"AggregationOuterDllServer.h"
#include"AggregationInnerDllServer.h" 

//class declarations
//Change 1 : Unlike containment's outer co-class, aggregation co-class inherit and implement only its own interfaces ISum and ISubtract, 
//			 it wont inherit and implement IMultiplication and IMultiplication
class CSumSubtract : public ISum, ISubtract//// CSubtract => Co Class, Concrete class, Component class, Implementer class (super class => sub class)
{
private:
	long m_cRef;
	//Change 2 : Declaring to store the IUnknown of inner component
	IUnknown* m_pIUnknownInner;

public:
	//constructor method declarations
	CSumSubtract(void);

	//destructor method declarations
	~CSumSubtract(void);

	//IUknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum Specific method declarations (inherited) 
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	//ISubtract Specific method declarations (inherited) 
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	HRESULT __stdcall InitializeInnerComponent(void);
};

class CSumSubtractClassFactory : public IClassFactory //class factory co-class che object tayar karte! IClassfactory ha COM cha interface aahe
{
private:
	long m_cRef;
public:
	//constructor method ddeclarations
	CSumSubtractClassFactory(void);

	//destructor method declarations
	~CSumSubtractClassFactory(void);

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
// Implementation of Co-Class CSumSubtract
*************************************************************************************************/

//Implementation of CSumSubtract's construcctor method
CSumSubtract::CSumSubtract(void)
{
	m_pIUnknownInner = NULL;
	//harcoded initialization to anticipate possible  failure of QueryInterface()
	m_cRef = 1;

	//Change 3 : Initializing m_pIUknownInner to NULL
	//m_pIUnknownInner = NULL;

	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
}

//Implementation of CSumSubtract's destrucctor method

CSumSubtract :: ~CSumSubtract(void)
{

	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter

	//Change 4 : Write a release block for m_PiUknownInner in outer co-class destructor

	if (m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

//Implementation of CSumSubtract's iUnknown Methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISUM)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	//Change 5 :
	else if (riid == IID_IMULTIPLICATION)
		return(m_pIUnknownInner->QueryInterface(riid, 
			ppv)); //m_pIUnknownInner madhey INoAggregationIUnknown aahe mhnun QueryInterface_NoAggregation la call jato, method coloring
	else if (riid == IID_IDIVISION)
		return(m_pIUnknownInner->QueryInterface(riid,
			ppv));
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return (S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	
	return(m_cRef);
}

//Implementation of ISum's Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* psum)
{
	*psum = num1 + num2;

	return (S_OK);
}

//Implementation of ISubtract's Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* psum)
{
	*psum = num1 - num2;

	return (S_OK);
}

// Change 7 : Define InitializeInnerComponent() which will call CoCreateInstance() for inner dll
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	//variable declarations
	HRESULT hr = S_OK;

	//Change 6 : 
	hr = CoCreateInstance(CLSID_MultiplicationDivision,
		reinterpret_cast<IUnknown*>(this),
		CLSCTX_INPROC_SERVER,
		IID_IUnknown,
		(void**)&m_pIUnknownInner);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("CoCreateInstance failed to obtain inner IMultiplicationn Interface"), TEXT("OUTER COM ERROR"), MB_ICONERROR);
		return (E_FAIL);
	}
		
	return hr;
}

/*************************************************************************************************
// Implementation of CSumSubtractClassFactory
*************************************************************************************************/

//Implementation of CSumSubtarctfactory's Constructor Mehtod
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1; //hardcoded inititalization to anticipate possible failure of QueryInterface()
}

//Implementation Of CSumSubtractClassFactory's Destructor Method
CSumSubtractClassFactory :: ~CSumSubtractClassFactory(void)
{
	//no code
}

//Implementation of CSumSubtractClassFactory's OClassFactory's IUnknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);

	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);

		return(0);
	}

	return(m_cRef);
}

//Implementation Of CSumSubtractfactory's iClassFactory's methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr = S_OK;

	//code
	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	//create the instance of component i.e. of CSumSubtract class
	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);

	//Change 8 : Call Co-Class's user defined InitializeInnerComponent function to load inner dll
	hr = pCSumSubtract->InitializeInnerComponent();

	if (FAILED(hr))
		MessageBox(NULL, TEXT("FAILED INITIALIZE COMPONENT"), TEXT("OUTER COM ERROR"), MB_ICONERROR | MB_OK);

	//get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);

	pCSumSubtract->Release(); // anticipate possible failure of QueryInterface()
	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr = S_OK;

	//code
	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create class factory. From procedure oriented to object oriented programming!
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release(); //anticipate possible failure of QueryInterface();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE); //error nahi, success value aahe, e.g. toss heads/tails
}
