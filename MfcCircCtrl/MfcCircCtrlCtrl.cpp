// MfcCircCtrlCtrl.cpp : CMfcCircCtrlCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "MfcCircCtrl.h"
#include "MfcCircCtrlCtrl.h"
#include "MfcCircCtrlPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMfcCircCtrlCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CMfcCircCtrlCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CMfcCircCtrlCtrl, COleControl)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_FONT()
	DISP_STOCKPROP_FORECOLOR()
	DISP_PROPERTY_NOTIFY_ID(CMfcCircCtrlCtrl, "CircleShaple", dispidCircleShaple, m_CircleShaple, OnCircleShapleChanged, VT_BOOL)
	DISP_PROPERTY_EX_ID(CMfcCircCtrlCtrl, "CircleOffset", dispidCircleOffset, GetCircleOffset, SetCircleOffset, VT_I2)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CMfcCircCtrlCtrl, COleControl)
	
	EVENT_CUSTOM_ID("ClickIn", eventidClickIn, ClickIn, VTS_XPOS_PIXELS VTS_YPOS_PIXELS)
	EVENT_CUSTOM_ID("ClickOut", eventidClickOut, ClickOut, VTS_XPOS_PIXELS VTS_YPOS_PIXELS)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CMfcCircCtrlCtrl, 1)
	PROPPAGEID(CMfcCircCtrlPropPage::guid)
END_PROPPAGEIDS(CMfcCircCtrlCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CMfcCircCtrlCtrl, "MFCCIRCCTRL.MfcCircCtrlCtrl.1",
	0x26a29b83, 0x9263, 0x47b4, 0xb6, 0xee, 0x12, 0x61, 0xbb, 0x10, 0xfa, 0x40)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CMfcCircCtrlCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DMfcCircCtrl = { 0xAAC8F54A, 0xB68F, 0x49D9, { 0xAD, 0xD7, 0xB, 0x85, 0x91, 0x1C, 0x6D, 0xD5 } };
const IID IID_DMfcCircCtrlEvents = { 0x965D2AA7, 0x4EE0, 0x4D3F, { 0xB7, 0xA, 0xD8, 0x3B, 0xAA, 0x35, 0x4B, 0x0 } };

// 控件类型信息

static const DWORD _dwMfcCircCtrlOleMisc =
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMfcCircCtrlCtrl, IDS_MFCCIRCCTRL, _dwMfcCircCtrlOleMisc)

// CMfcCircCtrlCtrl::CMfcCircCtrlCtrlFactory::UpdateRegistry -
// 添加或移除 CMfcCircCtrlCtrl 的系统注册表项

BOOL CMfcCircCtrlCtrl::CMfcCircCtrlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MFCCIRCCTRL,
			IDB_MFCCIRCCTRL,
			afxRegApartmentThreading,
			_dwMfcCircCtrlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CMfcCircCtrlCtrl::CMfcCircCtrlCtrl - 构造函数

CMfcCircCtrlCtrl::CMfcCircCtrlCtrl()
	: m_circleOffset(0)
{
	InitializeIIDs(&IID_DMfcCircCtrl, &IID_DMfcCircCtrlEvents);
	// TODO:  在此初始化控件的实例数据。
}

// CMfcCircCtrlCtrl::~CMfcCircCtrlCtrl - 析构函数

CMfcCircCtrlCtrl::~CMfcCircCtrlCtrl()
{
	// TODO:  在此清理控件的实例数据。
}

// CMfcCircCtrlCtrl::OnDraw - 绘图函数

void CMfcCircCtrlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);

	CBrush* pOldBrush;
	CBrush bkBrush(TranslateColor(GetBackColor()));
	CPen* pOldPen;
	CRect rc = rcBounds;
	CFont* pOldFont;
	TEXTMETRIC tm;
	const CString& strCaption = InternalGetText();

	pdc->SetTextColor(TranslateColor(GetForeColor()));
	pdc->SetBkMode(TRANSPARENT);
	pdc->FillRect(&rcBounds, &bkBrush);

	//获取椭圆的包围矩形
	//GetDrawRect(&rc);

	pOldBrush = pdc->SelectObject(&bkBrush);
	pOldPen = (CPen*)pdc->SelectStockObject(BLACK_PEN);
	pdc->Ellipse(rc);

	pOldFont = SelectStockFont(pdc);
	GetStockTextMetrics(&tm);
	pdc->SetTextAlign(TA_CENTER | TA_TOP);
	pdc->ExtTextOut((rc.left + rc.right) / 2, (rc.top + rc.bottom - tm.tmHeight) / 2, 
		ETO_CLIPPED, rc, strCaption, strCaption.GetLength(), 0);

	pdc->SelectObject(pOldBrush);
	pdc->SelectObject(pOldPen);
	pdc->SelectObject(pOldFont);
}

// CMfcCircCtrlCtrl::DoPropExchange - 持久性支持

void CMfcCircCtrlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。

}


// CMfcCircCtrlCtrl::OnResetState - 将控件重置为默认状态

void CMfcCircCtrlCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CMfcCircCtrlCtrl 消息处理程序


void CMfcCircCtrlCtrl::OnCircleShapleChanged()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	InvalidateControl();

	SetModifiedFlag();
	if (m_CircleShaple) {
		SetCircleOffset(0);
	}
}


SHORT CMfcCircCtrlCtrl::GetCircleOffset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_circleOffset;
}


void CMfcCircCtrlCtrl::SetCircleOffset(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_circleOffset != newVal && m_CircleShaple && InBounds(newVal)) {
		m_circleOffset = newVal;
		SetModifiedFlag();
		InvalidateControl();
	}	
}

BOOL CMfcCircCtrlCtrl::InBounds(SHORT nOffset)
{
	CRect rc;
	int diameter;
	int length;
	int cx, cy;
	GetControlSize(&cx, &cy);
	if (cx > cy) {
		length = cx;
		diameter = cy;
	}
	else {
		length = cy;
		diameter = cx;
	}
	if (nOffset < 0)
		nOffset = -nOffset;

	return (diameter / 2 + nOffset) <= (length / 2);
}


void CMfcCircCtrlCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (InCircle(point)) {
		ClickIn(point.x, point.y);
	}
	else {
		ClickOut(point.x, point.y);
	}

	COleControl::OnLButtonDown(nFlags, point);
}


BOOL CMfcCircCtrlCtrl::InCircle(CPoint& pt)
{
	CRect rc;
	GetClientRect(&rc);
	return rc.PtInRect(pt);
}