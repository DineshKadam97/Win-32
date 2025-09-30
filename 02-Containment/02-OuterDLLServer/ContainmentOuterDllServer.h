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

//CLSID of SumSubstract Component // {F6322A1F-21D9-44C3-A510-58DB4370059A}//hi stringized guid aahe

const CLSID CLSID_SumSubtract = { 0xf6322a1f, 0x21d9, 0x44c3, 0xa5, 0x10, 0x58, 0xdb, 0x43, 0x70, 0x5, 0x9a };


// IID of ISum Interface  // {743078AA-787A-4A3D-8722-971F0D32F58D}
const IID IID_ISUM = { 0x743078aa, 0x787a, 0x4a3d, 0x87, 0x22, 0x97, 0x1f, 0xd, 0x32, 0xf5, 0x8d };


//IID of ISubtract Interface / {3671889B-EADA-4000-8B58-D97405D901B1}
const IID IID_ISubtract = { 0x3671889b, 0xeada, 0x4000, 0x8b, 0x58, 0xd9, 0x74, 0x5, 0xd9, 0x1, 0xb1 };

