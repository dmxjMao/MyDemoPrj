
// MFCDialog.cpp : ����Ӧ�ó��������Ϊ��
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


// CMFCDialogApp ����

CMFCDialogApp::CMFCDialogApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCDialogApp ����

CMFCDialogApp theApp;


// CMFCDialogApp ��ʼ��

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

