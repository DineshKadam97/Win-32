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

//CLSID of SumSubstract Component {77EB179B-5968-40F3-9117-1F6D36456C52} //hi stringized guid aahe

const CLSID CLSID_SumSubtract = { 0x77eb179b, 0x5968, 0x40f3, 0x91, 0x17, 0x1f, 0x6d, 0x36, 0x45, 0x6c, 0x52 };

// IID of ISum Interface {D321082A-CBAB-4B68-A22D-F182076E1C9F}
const IID IID_ISUM = { 0xd321082a, 0xcbab, 0x4b68, 0xa2, 0x2d, 0xf1, 0x82, 0x7, 0x6e, 0x1c, 0x9f };

//IID of ISubtract Interface {A39F45D2-E331-486A-9C50-4760A90C3880}
const IID IID_ISubtract = { 0xa39f45d2, 0xe331, 0x486a, 0x9c, 0x50, 0x47, 0x60, 0xa9, 0xc, 0x38, 0x80 };

//Miscelleneous Questions
//PRIVATE word in def file?
//QueryInterface, AddRef and Release() konakdun aale? ISum ki ISubtract?
//why is m_cRef long type, reference counting vaparnar aahe
//Why InterlockedIncrement ++ kart tar sadha ++ ka nahi vaprla?
// why separate eturn 0 and return m_cRef
// pUnkOuter what is this??
// what is the third parameter of CoGetClassObject?
// why are we comparing the struct IID_IUnknown 
//cpp file lihun aanane
//LCID => locale ID , IID, CATID, CLSID
