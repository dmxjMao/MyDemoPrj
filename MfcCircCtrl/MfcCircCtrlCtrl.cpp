// MfcCircCtrlCtrl.cpp : CMfcCircCtrlCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "MfcCircCtrl.h"
#include "MfcCircCtrlCtrl.h"
#include "MfcCircCtrlPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMfcCircCtrlCtrl, COleControl)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CMfcCircCtrlCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// ����ӳ��

BEGIN_DISPATCH_MAP(CMfcCircCtrlCtrl, COleControl)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_FONT()
	DISP_STOCKPROP_FORECOLOR()
	DISP_PROPERTY_NOTIFY_ID(CMfcCircCtrlCtrl, "CircleShaple", dispidCircleShaple, m_CircleShaple, OnCircleShapleChanged, VT_BOOL)
	DISP_PROPERTY_EX_ID(CMfcCircCtrlCtrl, "CircleOffset", dispidCircleOffset, GetCircleOffset, SetCircleOffset, VT_I2)
END_DISPATCH_MAP()

// �¼�ӳ��

BEGIN_EVENT_MAP(CMfcCircCtrlCtrl, COleControl)
	
	EVENT_CUSTOM_ID("ClickIn", eventidClickIn, ClickIn, VTS_XPOS_PIXELS VTS_YPOS_PIXELS)
	EVENT_CUSTOM_ID("ClickOut", eventidClickOut, ClickOut, VTS_XPOS_PIXELS VTS_YPOS_PIXELS)
END_EVENT_MAP()

// ����ҳ

// TODO: ������Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CMfcCircCtrlCtrl, 1)
	PROPPAGEID(CMfcCircCtrlPropPage::guid)
END_PROPPAGEIDS(CMfcCircCtrlCtrl)

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CMfcCircCtrlCtrl, "MFCCIRCCTRL.MfcCircCtrlCtrl.1",
	0x26a29b83, 0x9263, 0x47b4, 0xb6, 0xee, 0x12, 0x61, 0xbb, 0x10, 0xfa, 0x40)

// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CMfcCircCtrlCtrl, _tlid, _wVerMajor, _wVerMinor)

// �ӿ� ID

const IID IID_DMfcCircCtrl = { 0xAAC8F54A, 0xB68F, 0x49D9, { 0xAD, 0xD7, 0xB, 0x85, 0x91, 0x1C, 0x6D, 0xD5 } };
const IID IID_DMfcCircCtrlEvents = { 0x965D2AA7, 0x4EE0, 0x4D3F, { 0xB7, 0xA, 0xD8, 0x3B, 0xAA, 0x35, 0x4B, 0x0 } };

// �ؼ�������Ϣ

static const DWORD _dwMfcCircCtrlOleMisc =
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMfcCircCtrlCtrl, IDS_MFCCIRCCTRL, _dwMfcCircCtrlOleMisc)

// CMfcCircCtrlCtrl::CMfcCircCtrlCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CMfcCircCtrlCtrl ��ϵͳע�����

BOOL CMfcCircCtrlCtrl::CMfcCircCtrlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

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


// CMfcCircCtrlCtrl::CMfcCircCtrlCtrl - ���캯��

CMfcCircCtrlCtrl::CMfcCircCtrlCtrl()
	: m_circleOffset(0)
{
	InitializeIIDs(&IID_DMfcCircCtrl, &IID_DMfcCircCtrlEvents);
	// TODO:  �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}

// CMfcCircCtrlCtrl::~CMfcCircCtrlCtrl - ��������

CMfcCircCtrlCtrl::~CMfcCircCtrlCtrl()
{
	// TODO:  �ڴ�����ؼ���ʵ�����ݡ�
}

// CMfcCircCtrlCtrl::OnDraw - ��ͼ����

void CMfcCircCtrlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  �����Լ��Ļ�ͼ�����滻����Ĵ��롣
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

	//��ȡ��Բ�İ�Χ����
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

// CMfcCircCtrlCtrl::DoPropExchange - �־���֧��

void CMfcCircCtrlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������

}


// CMfcCircCtrlCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CMfcCircCtrlCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO:  �ڴ��������������ؼ�״̬��
}


// CMfcCircCtrlCtrl ��Ϣ�������


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