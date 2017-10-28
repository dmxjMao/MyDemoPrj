// PointComp.h : main header file for the PointComp DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPointCompApp
// See PointComp.cpp for the implementation of this class
//

class CPointCompApp : public CWinApp
{
public:
	CPointCompApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
