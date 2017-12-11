// MyEdit1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyEdit1.h"
#include "MyCommonDefine.h"

// CMyEdit1
/*��������
1��eye����˸����ʱ����û��
2�������ʱ�޷���ʧ
*/

IMPLEMENT_DYNAMIC(CMyEdit1, CEdit)

CMyEdit1::CMyEdit1()
{
	try {
		m_regex.assign(
			"(?|"
			"(passwd):([01])" //�Ƿ�������
			")"
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {
		//theApp.WriteLog
	}
	m_cfg["passwd"] = "0";


}

CMyEdit1::~CMyEdit1()
{
}


BEGIN_MESSAGE_MAP(CMyEdit1, CEdit)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_UPDATE, &CMyEdit1::OnEditUpdate)
	//ON_CONTROL_REFLECT(EN_SETFOCUS, &CMyEdit1::OnSetFocus)
	//ON_CONTROL_REFLECT(EN_KILLFOCUS, &CMyEdit1::OnKillFocus)
	//ON_WM_LBUTTONDBLCLK()
	//ON_WM_MOUSEMOVE()
	//ON_WM_MOUSEHOVER()
	//ON_WM_MOUSELEAVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CMyEdit1 ��Ϣ�������



/*���������ػ�
NM_CUSTOMDRAW �������ػ�
*/
void CMyEdit1::OnPaint()
{
	CPaintDC dc(this); 
	//SetCueBanner(_T("��   �룺"));  //��Ҳ�����ػ�

	Graphics gh(dc.GetSafeHdc());
	CRect rc;
	GetClientRect(&rc);

	if ("1" == m_cfg["passwd"]) {
		//TRACE(_T("11\n"));
		//SetPasswordChar(_T('��'));
		Gdiplus::Image img(_T("res\\eye_24px.ico"));
		int w = rc.Height();
		Rect rcEye(rc.right - w, 0, w, w);

		gh.DrawImage(&img, rcEye);
	}

	CString str;
	GetWindowText(str);
	if (str.IsEmpty() && GetFocus() != this) {
		CString cue = _T("��   �룺");

		PointF pf(0.0f, 0.0f);
		SolidBrush br(Color(87, 87, 87));
		gh.DrawString(cue, -1, theApp.m_pFontDefault, pf, &br);
	}
}


void CMyEdit1::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL b = IsInEyeRect(point);
	if ("1" == m_cfg["passwd"] && b) { //����ˡ���ʾ���롱
		static bool bShow = true;
		if (bShow) {
			ModifyStyle(ES_PASSWORD, 0);
			SetPasswordChar(0);
		}
		else {
			ModifyStyle(0, ES_PASSWORD);
			SetPasswordChar(_T('��'));
		}
		bShow = !bShow;
	}

	__super::OnLButtonDown(nFlags, point);
	Invalidate(); //��eye
}

//void CMyEdit1::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	__super::OnLButtonDblClk(nFlags, point);
//	Invalidate();
//}

int CMyEdit1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	Macro_SetFont; //��������

	return 0;
}


void CMyEdit1::PreSubclassWindow()
{
	if ("1" == m_cfg["passwd"]) {
		ModifyStyle(0, ES_PASSWORD);
	}
	//EnableWindowTheme(m_hWnd, L"Edit", L"Explorer", 0);

	__super::PreSubclassWindow();
}


void CMyEdit1::OnEditUpdate()
{
	Invalidate();//�����ͣ���뿪�����㡢ʧ������OnPaint��ֻ�����벻��
}


//void CMyEdit1::OnSetFocus()
//{
//	Invalidate();
//}

//void CMyEdit1::OnKillFocus()
//{
//	HideCaret();
//	Invalidate();
//}



//void CMyEdit1::OnMouseMove(UINT nFlags, CPoint point)
//{
//	//BOOL b = IsInEyeRect(point);  ����˸
//	//if (b) {
//	//	HideCaret();  
//	//	SetCursor(LoadCursor(0, IDC_ARROW));
//	//}
//	if (m_bMouseTrack) {
//		m_bMouseTrack = false;
//		TRACKMOUSEEVENT tme;
//		tme.cbSize = sizeof(TRACKMOUSEEVENT);
//		tme.dwFlags = TME_HOVER | TME_LEAVE;
//		//tme.dwHoverTime = HOVER_DEFAULT;  
//		tme.dwHoverTime = 50;
//		tme.hwndTrack = GetSafeHwnd();
//		TrackMouseEvent(&tme);
//	}
//	
//	__super::OnMouseMove(nFlags, point);
//}


//void CMyEdit1::OnMouseHover(UINT nFlags, CPoint point)
//{
//	BOOL b = IsInEyeRect(point);
//	if (b) {
//		SetCursor(LoadCursor(0, IDC_ARROW));
//	}
//}
//
//
//void CMyEdit1::OnMouseLeave()
//{
//	m_bMouseTrack = true;
//}

BOOL CMyEdit1::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	//OnMouseMove������˸����
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	if (IsInEyeRect(pt)) {
		SetCursor(LoadCursor(0, IDC_ARROW));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CMyEdit1::IsInEyeRect(CPoint point)
{
	CRect rc;
	GetClientRect(&rc);

	CRect rcEye;
	int w = rc.Height();
	rcEye.SetRect(rc.right - w, rc.top, rc.right, rc.bottom);

	BOOL b = rcEye.PtInRect(point);
	return b;
}