
// IEWebBrowserDlg.h : header file
//

#pragma once
#include "explorer.h"
#include "afxwin.h"

class CEmbedIEDlg;//图表

// CIEWebBrowserDlg dialog
class CIEWebBrowserDlg : public CDialogEx
{
// Construction
public:
	CIEWebBrowserDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IEWEBBROWSER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CRect m_rcChart;//图表区域
	std::vector<std::shared_ptr<CEmbedIEDlg>> m_vecChartDlg;//图表对话框

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
//	CExplorer m_ie;
	CButton m_addChart;
public:
	afx_msg void OnBnClickedAddchart();
};
