#pragma once
#include "UICfg.h"

// CMyEdit1

class CMyEdit1 : public CEdit, public CUICfg
{
	DECLARE_DYNAMIC(CMyEdit1)

public:
	CMyEdit1();
	virtual ~CMyEdit1();

protected:
	DECLARE_MESSAGE_MAP()
	CFont m_font;
	//Rect m_rcEye;//显示密码按钮区域
	//bool m_bMouseTrack = true;

public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void PreSubclassWindow();
	afx_msg void OnEditUpdate();
	//afx_msg void OnSetFocus();
	//afx_msg void OnKillFocus();
	//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	//afx_msg void OnMouseLeave();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);


private:
	BOOL IsInEyeRect(CPoint point);//是否在eye区域
};


