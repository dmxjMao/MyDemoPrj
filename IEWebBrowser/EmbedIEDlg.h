#pragma once
#include "explorer.h"


// CEmbedIEDlg dialog

class CEmbedIEDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEmbedIEDlg)

public:
	CEmbedIEDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEmbedIEDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IEWebBrowser };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CExplorer m_ie;
	CString m_htmlPath;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
