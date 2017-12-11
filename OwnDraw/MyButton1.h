#pragma once
#include "UICfg.h"

// CMyButton1
/*遗留问题
圆角矩形
*/

class CMyButton1 : public CButton, public CUICfg
{
	DECLARE_DYNAMIC(CMyButton1)

public:
	CMyButton1();
	virtual ~CMyButton1();

protected:
	//emBtnType m_nType = emBtnTypeBuff;//按钮类型
	DECLARE_MESSAGE_MAP()
	bool m_bMouseTrack = true;//是否跟踪hover事件
	bool m_bHover = false;//是否悬停状态

public:
	afx_msg void OnPaint();

	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();

};


