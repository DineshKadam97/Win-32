#pragma once
#include<windows.h>
                              //IUnknown is the first interface in COM, akhya COM madhey ekach interface aahe jo IUnknown pasun inherit hot nahi, and that is IUnknown itself
class IMultiplication : public IUnknown //ISum madhey sadhya 4 functions aahet, 3 from IUnknown, //if you are programming in COM, all interfaces are directly or indirectly inherited from IUknown
{
public:
	//ISum specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class IDivision : public IUnknown //ISubtract = IRajeshPradhan, IUnknown = Agency/Franchaise
{
public:
	//ISubtract specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

//CLSID of SumSubstract Component //  {4B691AF0-C63A-4339-964E-844AFBE816A7}//hi stringized guid aahe

const CLSID CLSID_MultiplicationDivision = { 0x4b691af0, 0xc63a, 0x4339, 0x96, 0x4e, 0x84, 0x4a, 0xfb, 0xe8, 0x16, 0xa7 };



// IID of ISum Interface {253809F9-0BCC-4EBB-88F2-AF517775E6F8}
const IID IID_IMULTIPLICATION = { 0x253809f9, 0xbcc, 0x4ebb, 0x88, 0xf2, 0xaf, 0x51, 0x77, 0x75, 0xe6, 0xf8 };

//  {1D95EE1B-52CA-4173-B8F9-C84F2503BF56}
const IID IID_IDIVISION = { 0x1d95ee1b, 0x52ca, 0x4173, 0xb8, 0xf9, 0xc8, 0x4f, 0x25, 0x3, 0xbf, 0x56 };

//Miscelleneous Questions
//PRIVATE word in def file?
//QueryInterface, AddRef and Release() konakdun aale? ISum ki ISubtract? Adjuster thunk(followed by microsoft) left to right jo pahila aahe tyacha IUnknown gheto
//why is m_cRef long type, reference counting vaparnar aahe
//Why InterlockedIncrement ++ kart tar sadha ++ ka nahi vaprla?
// why separate return 0 and return m_cRef
// pUnkOuter what is this??
// why BOOL false and waht happens if true CoLoadLibrary, false asel tar saglyat shevti call hoto, CoUnitilize nantr, true asel tar ek thread satat call karto
// CogetClass cha 3ra parameter is COSERVERINFO
// m_cref hardcoded 1 la ka initialize karaych
// Array of semantically related functions. Interface is nothing but an array of pure virtual functions
// Adjuster Thunk
// == structure IUknown la kelay, using operator overloading
// BOOL operator == (const GUID& guid1, const GUID& guid2)
// {
//    return IsEqualGuids(guid1, guid2);
// }
// long type of m_cRef, glNumberofActiveComponents, glNumberOfServerLocks karan InterLockedIncrement/ InterLockedDecrement cha parameter type long aahe
// InterLockedIncrement/ InterLockedDecrement thread safe functions aahet mhnun ++/-- peksha safe aahet
// across co class object if you want that object, Lock Server la call deun glNumberOfServerLocks yanchi value increase/decrease karu shakto
//cpp file lihun aanane
