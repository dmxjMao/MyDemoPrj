#pragma once
#include "UICfg.h"

// CMyCombo1

class CMyCombo1 : public /*CComboBoxEx*/CComboBox, public CUICfg
{
	DECLARE_DYNAMIC(CMyCombo1)

public:
	CMyCombo1();
	virtual ~CMyCombo1();
	//填充item，实际参数是map<用户信息>
	void FillItem(const std::vector<CString>&);

protected:
	DECLARE_MESSAGE_MAP()
	BOOL m_bAutoComplete = TRUE;
	CFont m_font;
public:
	afx_msg void OnPaint();
	afx_msg void OnEditUpdate(); //自动补全
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


