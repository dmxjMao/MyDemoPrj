#pragma once
#include "UICfg.h"

// CMyButton1
/*��������
Բ�Ǿ���
*/

class CMyButton1 : public CButton, public CUICfg
{
	DECLARE_DYNAMIC(CMyButton1)

public:
	CMyButton1();
	virtual ~CMyButton1();

protected:
	//emBtnType m_nType = emBtnTypeBuff;//��ť����
	DECLARE_MESSAGE_MAP()
	bool m_bMouseTrack = true;//�Ƿ����hover�¼�
	bool m_bHover = false;//�Ƿ���ͣ״̬

public:
	afx_msg void OnPaint();

	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();

};


