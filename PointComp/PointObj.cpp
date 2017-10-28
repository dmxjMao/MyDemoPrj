// PointObj.cpp : implementation file
//

#include "stdafx.h"
#include "PointComp.h"
#include "PointObj.h"


// CPointObj

IMPLEMENT_DYNAMIC(CPointObj, CCmdTarget)


CPointObj::CPointObj()
	: x(0)
{
	EnableAutomation();
}

CPointObj::~CPointObj()
{
}


void CPointObj::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CPointObj, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CPointObj, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IPointObj to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {1716B8DF-6E8B-4567-A0C5-50FA64C6E8D2}
static const IID IID_IPointObj =
{ 0x1716B8DF, 0x6E8B, 0x4567, { 0xA0, 0xC5, 0x50, 0xFA, 0x64, 0xC6, 0xE8, 0xD2 } };

BEGIN_INTERFACE_MAP(CPointObj, CCmdTarget)
	INTERFACE_PART(CPointObj, IID_IPointObj, Dispatch)
END_INTERFACE_MAP()


// CPointObj message handlers



void CPointObj::MoveTo(long xDest, long yDest)
{
}
