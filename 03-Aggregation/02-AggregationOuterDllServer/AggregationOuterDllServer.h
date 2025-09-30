#pragma once
#include<windows.h>
                              //IUnknown is the first interface in COM, akhya COM madhey ekach interface aahe jo IUnknown pasun inherit hot nahi, and that is IUnknown itself
class ISum : public IUnknown //ISum madhey sadhya 4 functions aahet, 3 from IUnknown, //if you are programming in COM, all interfaces are directly or indirectly inherited from IUknown
{
public:
	//ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class ISubtract : public IUnknown //ISubtract = IRajeshPradhan, IUnknown = Agency/Franchaise
{
public:
	//ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

//CLSID of SumSubstract Component //{4A895C5B-964F-41A8-BF6E-7B2C82EB7766}//hi stringized guid aahe

const CLSID CLSID_SumSubtract = { 0x4a895c5b, 0x964f, 0x41a8, 0xbf, 0x6e, 0x7b, 0x2c, 0x82, 0xeb, 0x77, 0x66 };

// IID of ISum Interface  //{FBAA779D-EDDC-4A4A-9993-1A4A0592ECF2}
const IID IID_ISUM = { 0xfbaa779d, 0xeddc, 0x4a4a, 0x99, 0x93, 0x1a, 0x4a, 0x5, 0x92, 0xec, 0xf2 };


//IID of ISubtract Interface / {DE6ADC5C-9591-41C9-8E7D-FBC9A4150A46}
const IID IID_ISubtract = { 0xde6adc5c, 0x9591, 0x41c9, 0x8e, 0x7d, 0xfb, 0xc9, 0xa4, 0x15, 0xa, 0x46 };
