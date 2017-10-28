
// MFCSampleExe.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCSampleExeApp:
// See MFCSampleExe.cpp for the implementation of this class
//

class CMFCSampleExeApp : public CWinApp
{
public:
	CMFCSampleExeApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCSampleExeApp theApp;