#pragma once

// MfcCircCtrlCtrl.h : CMfcCircCtrlCtrl ActiveX 控件类的声明。


// CMfcCircCtrlCtrl : 有关实现的信息，请参阅 MfcCircCtrlCtrl.cpp。

class CMfcCircCtrlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMfcCircCtrlCtrl)

// 构造函数
public:
	CMfcCircCtrlCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CMfcCircCtrlCtrl();

	DECLARE_OLECREATE_EX(CMfcCircCtrlCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CMfcCircCtrlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMfcCircCtrlCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CMfcCircCtrlCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		eventidClickOut = 2L,
		eventidClickIn = 1L,
		dispidCircleOffset = 2,
		dispidCircleShaple = 1
	};
protected:
	void OnCircleShapleChanged();
	VARIANT_BOOL m_CircleShaple = TRUE; //TRUE圆 FALSE椭圆
	SHORT GetCircleOffset();
	void SetCircleOffset(SHORT newVal);

private:
	BOOL InBounds(SHORT nOffset);	
	BOOL InCircle(CPoint& pt);

private:
	short m_circleOffset = 0;

protected:

	/*负责在哪里调用激发*/
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

