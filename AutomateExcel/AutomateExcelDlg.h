
// AutomateExcelDlg.h : header file
//

#pragma once
//#include "mschart2.h"


// CAutomateExcelDlg dialog
class CAutomateExcelDlg : public CDialogEx
{
// Construction
public:
	CAutomateExcelDlg(CWnd* pParent = NULL);	// standard constructor

	//void InitChart();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOMATEEXCEL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	//excel
	void RestoreExcelStyle();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRun();
	//CMschart2 m_demoChart;
	afx_msg void OnClose();
};
