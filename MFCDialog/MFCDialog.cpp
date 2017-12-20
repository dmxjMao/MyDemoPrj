
// MFCDialog.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "MFCDialog.h"
#include "MFCDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMFCDialogApp

BEGIN_MESSAGE_MAP(CMFCDialogApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCDialogApp 构造

CMFCDialogApp::CMFCDialogApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMFCDialogApp 对象

CMFCDialogApp theApp;


// CMFCDialogApp 初始化

BOOL CMFCDialogApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxOleInit())
		return FALSE;

	CMFCDialogDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

