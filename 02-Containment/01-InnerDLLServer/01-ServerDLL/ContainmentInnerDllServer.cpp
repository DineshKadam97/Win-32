//Changes in ContainmentInnerDllServer.cpp wrt to ClassFactoryDllServerWithRegFile.cpp are:
/*
	1) Co-Class is Implementing interfaces IMultiplication and IDivision
	2) Co-Class name is CMultiplicationDivision
	3) Class factory name is CMultiplicationDivisionClassFactory
	4) Implementing functionalities MultiplicationOfTwoIntegers() and DivisionOfTwoIntegers()
*/
#define UNICODE
#include<windows.h>
#include"ContainmentInnerDllServer.h"

//class declarations
class CMultiplicationDivision : public IMultiplication, IDivision //// CSubtract => Co Class, Concrete class, Component class, Implementer class (super class => sub class)
{
private:
	long m_cRef;

public:
	//constructor method declarations
	CMultiplicationDivision(void);

	//destructor method declarations
	~CMultiplicationDivision(void);

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
CMultiplicationDivision::CMultiplicationDivision(void)
{
	//harcoded initialization to anticipate possible  failure of QueryInterface()
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
}

//Implementation of CMultiplicationDivision's destrucctor method

CMultiplicationDivision :: ~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter
}

//Implementation of CMultiplicationDivision's iUnknown Methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IMULTIPLICATION)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDIVISION)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return (S_OK);
}

ULONG CMultiplicationDivision::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CMultiplicationDivision::Release(void)
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
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pmultiplication)
{
	*pmultiplication = num1 * num2;

	return (S_OK);
}

//Implementation of ISubtract's Methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pdivision)
{
	*pdivision = num1 / num2;

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
	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	//create the instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision = new CMultiplicationDivision;

	if (pCMultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);

	//get the requested interface
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);

	pCMultiplicationDivision->Release(); // anticipate possible failure of QueryInterface()
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
		return(CLASS_E_CLASSNOTAVAILABLE);

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
