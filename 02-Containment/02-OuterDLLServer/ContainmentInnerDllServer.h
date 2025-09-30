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

//CLSID of SumSubstract Component // {DA0BD6D5-AEA7-49C7-9738-2368607D0539} //hi stringized guid aahe

const CLSID CLSID_MultiplicationDivision = { 0xda0bd6d5, 0xaea7, 0x49c7, 0x97, 0x38, 0x23, 0x68, 0x60, 0x7d, 0x5, 0x39 };


// IID of ISum Interface{437176B4-3E55-4E7F-BC2D-700835B85D88}
const IID IID_IMULTIPLICATION = { 0x437176b4, 0x3e55, 0x4e7f, 0xbc, 0x2d, 0x70, 0x8, 0x35, 0xb8, 0x5d, 0x88};

// {202896E4-B537-4308-B6B6-B72516B29614}
const IID IID_IDIVISION = { 0x202896e4, 0xb537, 0x4308, 0xb6, 0xb6, 0xb7, 0x25, 0x16, 0xb2, 0x96, 0x14 };



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
