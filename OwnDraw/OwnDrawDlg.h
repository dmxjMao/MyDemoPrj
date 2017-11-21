
// OwnDrawDlg.h : header file
//

#pragma once

class CMyMenu1;//×Ô»æ²Ëµ¥

// COwnDrawDlg dialog
class COwnDrawDlg : public CDialogEx
{
// Construction
public:
	COwnDrawDlg(CWnd* pParent = NULL);	// standard constructor
	~COwnDrawDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OWNDRAW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	//std::shared_ptr<CMenu> m_pMenuPop1 = 0;
	CMenu* m_pMenuPop1 = 0;
	CMyMenu1* m_pMyMenu1 = 0;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMenu1M1();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};
