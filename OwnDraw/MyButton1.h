#pragma once
#include "UICfg.h"

// CMyButton1

class CMyButton1 : public CButton, public CUICfg
{
	DECLARE_DYNAMIC(CMyButton1)

public:
	CMyButton1();
	virtual ~CMyButton1();

protected:
	//emBtnType m_nType = emBtnTypeBuff;//∞¥≈•¿‡–Õ
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();

	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


