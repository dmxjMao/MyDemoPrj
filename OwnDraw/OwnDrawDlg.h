
// OwnDrawDlg.h : header file
//

#pragma once
//#include "UICfg.h" //ui配置
#include "BaseDialog.h"
//#include "afxcmn.h"
//#include "afxwin.h"

/*遗留问题
字体
OnPaint父类输出了文字，子类输出不了文字
*/
class CMyMenu1;//自绘菜单
class CMyButton1;//最小最大化关闭按钮
class CMyCombo1;
class CMyEdit1;
class CMyListCtrl1;

// COwnDrawDlg dialog
class COwnDrawDlg : /*public CDialogEx, */public CBaseDialog
{
// Construction
public:
	COwnDrawDlg(CWnd* pParent = NULL);	// standard constructor
	~COwnDrawDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OWNDRAW_DIALOG };
#endif


// Implementation
protected:
	HICON m_hIcon;
	CFont m_font;
	//CString m_strTitle = _T("天跃智能环境监测系统——登录界面");//标题
	//std::shared_ptr<CMenu> m_pMenuPop1 = 0;
	CMenu* m_pMenuPop1 = 0;
	CMyMenu1* m_pMyMenu1 = 0;

	// Generated message map functions
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//virtual bool ParseCfg(const boost::smatch& cfg);

public:
	afx_msg void OnMenu1M1();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//afx_msg LRESULT OnNcHitTest(CPoint point);
	void OnBnClicked(UINT nID);
protected:
	std::shared_ptr<CMyButton1> m_minBtn = 0;
	std::shared_ptr<CMyButton1> m_maxBtn = 0;
	std::shared_ptr<CMyButton1> m_closeBtn = 0;
	std::shared_ptr<CMyCombo1> m_ctlUserName = 0;
	std::shared_ptr<CMyEdit1> m_ctlPasswd = 0;
	std::shared_ptr<CMyButton1> m_ctlBtn2 = 0;
	std::shared_ptr<CMyListCtrl1> m_ctlList = 0;
public:
	afx_msg void OnBnClickedButton1();

};
