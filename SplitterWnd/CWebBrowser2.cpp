// CWebBrowser2.cpp  : Definition of ActiveX Control wrapper class(es) created by Microsoft Visual C++


#include "stdafx.h"
#include "CWebBrowser2.h"

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser2

IMPLEMENT_DYNCREATE(CWebBrowser2, CWnd)

// CWebBrowser2 properties

// CWebBrowser2 operations


BOOL CWebBrowser2::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bRet = CWnd::PreCreateWindow(cs);
	//cs.style &= ~(WS_HSCROLL | WS_VSCROLL);
	//ModifyStyle(WS_HSCROLL | WS_VSCROLL, 0);
	return bRet;
}
