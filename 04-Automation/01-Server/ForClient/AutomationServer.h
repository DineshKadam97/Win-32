#pragma once
class IMyMath : public IDispatch //IID_IDISPATCH : 00020400-0000-0000-C000-000000000046
{
public:
	// pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
	// pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of MyMath Component : {4A529D3E-9133-4840-BAB2-22B5E061EB91}
const CLSID CLSID_MyMath = { 0x4a529d3e, 0x9133, 0x4840, 0xba, 0xb2, 0x22, 0xb5, 0xe0, 0x61, 0xeb, 0x91 };


// IID of ISum Interface : {DF4495F1-6880-45B8-B798-6B03642D8D27}
const IID IID_IMyMath = { 0xdf4495f1, 0x6880, 0x45b8, 0xb7, 0x98, 0x6b, 0x3, 0x64, 0x2d, 0x8d, 0x27 };


//Can act as Dual Interface => can work as IDispatch and Class Factory
//Custom Marshelling => 
//Per server ekach dual interface inheriting from IDispatch and thats why typeinfo is 1.

