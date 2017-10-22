// MFCDictComp.h : main header file for the MFCDictComp DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCDictCompApp
// See MFCDictComp.cpp for the implementation of this class
//

class CMFCDictCompApp : public CWinApp
{
public:
	CMFCDictCompApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
