#pragma once

// MfcCircCtrlCtrl.h : CMfcCircCtrlCtrl ActiveX �ؼ����������


// CMfcCircCtrlCtrl : �й�ʵ�ֵ���Ϣ������� MfcCircCtrlCtrl.cpp��

class CMfcCircCtrlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMfcCircCtrlCtrl)

// ���캯��
public:
	CMfcCircCtrlCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CMfcCircCtrlCtrl();

	DECLARE_OLECREATE_EX(CMfcCircCtrlCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CMfcCircCtrlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMfcCircCtrlCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CMfcCircCtrlCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		eventidClickOut = 2L,
		eventidClickIn = 1L,
		dispidCircleOffset = 2,
		dispidCircleShaple = 1
	};
protected:
	void OnCircleShapleChanged();
	VARIANT_BOOL m_CircleShaple = TRUE; //TRUEԲ FALSE��Բ
	SHORT GetCircleOffset();
	void SetCircleOffset(SHORT newVal);

private:
	BOOL InBounds(SHORT nOffset);	
	BOOL InCircle(CPoint& pt);

private:
	short m_circleOffset = 0;

protected:

	/*������������ü���*/
	void ClickIn(OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
	{
		FireEvent(eventidClickIn, EVENT_PARAM(VTS_XPOS_PIXELS VTS_YPOS_PIXELS), x, y);
	}

	void ClickOut(OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
	{
		FireEvent(eventidClickOut, EVENT_PARAM(VTS_XPOS_PIXELS VTS_YPOS_PIXELS), x, y);
	}
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

