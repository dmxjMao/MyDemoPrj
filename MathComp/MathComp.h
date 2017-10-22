// MathComp.h : main header file for the MathComp DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMathCompApp
// See MathComp.cpp for the implementation of this class
//

class CMathCompApp : public CWinApp
{
public:
	CMathCompApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
