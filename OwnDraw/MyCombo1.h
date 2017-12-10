#pragma once
#include "UICfg.h"

// CMyCombo1

class CMyCombo1 : public CComboBoxEx, public CUICfg
{
	DECLARE_DYNAMIC(CMyCombo1)

public:
	CMyCombo1();
	virtual ~CMyCombo1();
	//填充item，实际参数是map<用户信息>
	void FillItem(const std::vector<CString>&);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual void PreSubclassWindow();
};


