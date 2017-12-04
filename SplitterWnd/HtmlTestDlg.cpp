// HtmlTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SplitterWnd.h"
#include "HtmlTestDlg.h"
#include "afxdialogex.h"

#include <MsHTML.h>
// CHtmlTestDlg dialog

IMPLEMENT_DYNAMIC(CHtmlTestDlg, CDialogEx)

CHtmlTestDlg::CHtmlTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CHtmlTestDlg::~CHtmlTestDlg()
{
}

void CHtmlTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_WebBrowser);
}


BEGIN_MESSAGE_MAP(CHtmlTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CHtmlTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHtmlTestDlg message handlers


BOOL CHtmlTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rc;
	GetClientRect(&rc);

	m_WebBrowser.SetWindowPos(0, rc.left, rc.top, rc.Width(), rc.Height() - 60, SWP_NOZORDER);

	CString str(_T("D:\\MyProject\\VC\\MyDemoPrj\\Debug\\echart\\test.html"));
	m_WebBrowser.Navigate(str, 0, 0, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CHtmlTestDlg::OnBnClickedButton1()
{
	CComQIPtr<IHTMLDocument2> spDoc = m_WebBrowser.get_Document();
	CComDispatchDriver spScript;
	spDoc->get_Script(&spScript);

	CComVariant var1 = 10, var2 = 20, varRet;
	spScript.Invoke2(L"Add", &var1, &var2, &varRet);

}
