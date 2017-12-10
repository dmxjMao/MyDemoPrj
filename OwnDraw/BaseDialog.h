#pragma once
#include "UICfg.h"

// CBaseDialog 对话框


class CBaseDialog : public CDialogEx, public CUICfg
{
	DECLARE_DYNAMIC(CBaseDialog)

public:
	CBaseDialog(CWnd* pParent = NULL);   // 标准构造函数
	CBaseDialog(UINT nIDTemplate, CWnd *pParent = NULL);
	virtual ~CBaseDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	CString m_strTitle = _T("登录界面");
	CFont m_font;

public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
};
