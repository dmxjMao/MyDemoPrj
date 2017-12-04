#pragma once
#include "CWebBrowser2.h"


// CHtmlTestDlg dialog

class CHtmlTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHtmlTestDlg)

public:
	CHtmlTestDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHtmlTestDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CWebBrowser2 m_WebBrowser;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
