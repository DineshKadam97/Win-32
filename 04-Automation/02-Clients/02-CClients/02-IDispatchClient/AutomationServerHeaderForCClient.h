#pragma once

//Undefine any interface if already present, because we are going to define new interface now
#undef INTERFACE 

//Define IMyMath Interface
#define INTERFACE IMyMath
DECLARE_INTERFACE_(IMyMath, IDispatch)
{
	//Declaring pure virtual methods of grandparent interface IUnknown
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, AddRelease)(THIS) PURE;

	// Declaring pure virtual methods of parent interface IDispatch
	STDMETHOD(GetTypeInfoCount)(THIS_ UINT*) PURE;
	STDMETHOD(GetTypeInfo)(THIS_ UINT, LCID, ITypeInfo**) PURE;
	STDMETHOD(GetIDsOfNames)(THIS_ REFIID, LPOLESTR*, UINT, LCID, DISPID*) PURE;
	STDMETHOD(Invoke)(THIS_ DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*) PURE;

	//Declaring pure virtual methods of child interface IMyMath
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
	STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

// CLSID of MyMath Component : {4A529D3E-9133-4840-BAB2-22B5E061EB91}
const CLSID CLSID_MyMath = { 0x4a529d3e, 0x9133, 0x4840, 0xba, 0xb2, 0x22, 0xb5, 0xe0, 0x61, 0xeb, 0x91 };


// IID of ISum Interface : {DF4495F1-6880-45B8-B798-6B03642D8D27}
const IID IID_IMyMath = { 0xdf4495f1, 0x6880, 0x45b8, 0xb7, 0x98, 0x6b, 0x3, 0x64, 0x2d, 0x8d, 0x27 };

