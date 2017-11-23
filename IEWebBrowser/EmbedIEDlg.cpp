// EmbedIEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IEWebBrowser.h"
#include "EmbedIEDlg.h"
#include "afxdialogex.h"


// CEmbedIEDlg dialog

IMPLEMENT_DYNAMIC(CEmbedIEDlg, CDialogEx)

CEmbedIEDlg::CEmbedIEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IEWebBrowser, pParent)
{

}

CEmbedIEDlg::~CEmbedIEDlg()
{
}

void CEmbedIEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Explorer, m_ie);
}


BEGIN_MESSAGE_MAP(CEmbedIEDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CEmbedIEDlg message handlers


BOOL CEmbedIEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rc;
	GetParent()->GetClientRect(&rc);

	SetWindowPos(0, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	m_ie.SetWindowPos(0, rc.left, rc.top + 16, rc.Width(), rc.Height() - 16, SWP_NOACTIVATE | SWP_NOZORDER);
	
	//m_ie.put_Width(rc.Width());
	//m_ie.put_Height(rc.Height() - 16);

	//œ‘ æhtml
	m_htmlPath = _T("D:\\MyProject\\VC\\MyDemoPrj\\IEWebBrowser\\EChart\\html\\bar.html");
	m_ie.Navigate(m_htmlPath, 0, 0, 0, 0);
	

	return TRUE; 
}


void CEmbedIEDlg::OnPaint()
{
	CPaintDC dc(this); 
	//Graphics gh(dc.GetSafeHdc());

	//gh.FillRectangle()
	CRect rc;
	GetClientRect(&rc);

	//dc.FillSolidRect(&rc, RGB(255, 255, 0));

	dc.DrawText(_T("CEmbedIEDlg"), &rc, DT_SINGLELINE);
}
