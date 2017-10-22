// DictionaryObj.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDictComp.h"
#include "DictionaryObj.h"

#define INITGUID
// CDictionaryObj
// {8E75622A-0836-4949-A9DF-C6260CD437A2}
DEFINE_GUID(IID_IDictionary,
	0x8e75622a, 0x836, 0x4949, 0xa9, 0xdf, 0xc6, 0x26, 0xc, 0xd4, 0x37, 0xa2);
// {D561594F-9600-4976-97DD-79276AB15031}
DEFINE_GUID(IID_ISpellCheck,
	0xd561594f, 0x9600, 0x4976, 0x97, 0xdd, 0x79, 0x27, 0x6a, 0xb1, 0x50, 0x31);

//extern "C" const IID IID_IDictionary = {};
//extern "C" const IID IID_ISpellCheck = {};

IMPLEMENT_DYNAMIC(CDictionaryObj, CCmdTarget)

// {D561594F-9600-4976-97DD-79276AB15031}
IMPLEMENT_OLECREATE(CDictionaryObj, "Dictionary.Object" ,
	0xd561594f, 0x9600, 0x4976, 0x97, 0xdd, 0x79, 0x27, 0x6a, 0xb1, 0x50, 0x31);


CDictionaryObj::CDictionaryObj()
{
}

CDictionaryObj::~CDictionaryObj()
{
}


BEGIN_MESSAGE_MAP(CDictionaryObj, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_INTERFACE_MAP(CDictionaryObj, CCmdTarget)
	INTERFACE_PART(CDictionaryObj, IID_IDictionary, Dictionary)
	//INTERFACE_PART(CDictionaryObj, IID_ISpellCheck, SpellCheck)
END_INTERFACE_MAP()


// CDictionaryObj message handlers
