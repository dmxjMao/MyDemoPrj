// MyButton1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyButton1.h"
#include "MyCommonDefine.h"

// CMyButton1

IMPLEMENT_DYNAMIC(CMyButton1, CButton)

CMyButton1::CMyButton1()
{
	try {
		/*��ť���ͣ�
		1 ͼƬ��2 ����ɫ+���֣�
		*/
		m_regex.assign(
			"(?|"
			"(type):([0-9]{1})|"
			"(shape):(rect|roundRect)|"//��״
			"(picture):(.*\\.(ico|png|bmp))|"//ͼƬ
			"(bkgColor):#([0-9a-zA-Z]+)"//����ɫ
			")"
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {
		//theApp.WriteLog
	}
	//uiĬ��ֵ
	m_cfg["type"] = "1";
	m_cfg["shape"] = "rect";
	m_cfg["picture"] = "";
	m_cfg["bkgColor"] = "FFFFFF";
}

CMyButton1::~CMyButton1()
{
}


BEGIN_MESSAGE_MAP(CMyButton1, CButton)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CMyButton1 ��Ϣ�������




void CMyButton1::OnPaint()
{
	CPaintDC dc(this); 
	Graphics gh(dc.GetSafeHdc());
	CRect rc;
	GetClientRect(&rc);

	const int type = stoi(m_cfg["type"]);
	switch (type)
	{
	case 1: {//ͼƬ
		auto& pic = m_cfg["picture"];
		CA2T szPic(pic.c_str());
		Gdiplus::Image img(szPic);

		int w = theApp.m_nCloseBtnWidth;
		gh.DrawImage(&img, 0, 0, w, w);
		if (m_bHover) {
			Pen pen(Color::AntiqueWhite, 2.0f);
			gh.DrawRectangle(&pen, 0, 0, w, w);
		}
		break;
	}
		
	case 2: {//����ɫ+����
		
		Color clr;
		Convert2Color(m_cfg["bkgColor"], clr);
		SolidBrush br(clr);
		Rect rcGdi(rc.left, rc.top, rc.Width(), rc.Height());
		
		if (m_bHover) {
			br.SetColor(Color(218, 162, 162));
		}
		gh.FillRectangle(&br, rcGdi);

		StringFormat strFormat;
		strFormat.SetLineAlignment(StringAlignmentCenter);
		strFormat.SetAlignment(StringAlignmentCenter);

		RectF rcGdiF;
		Convert2RectF(rc, rcGdiF);
		SolidBrush brFont(theApp.m_clrFont);
		CString str;
		GetWindowText(str);
		gh.DrawString(str, -1, theApp.m_pFontDefault, rcGdiF, &strFormat, &brFont);

		break;
	}
	}

}



void CMyButton1::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	__super::PreSubclassWindow();
}

//BS_OWNERDRAW�Ի����������
void CMyButton1::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

}


void CMyButton1::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bMouseTrack) {
		m_bMouseTrack = false;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		//tme.dwHoverTime = HOVER_DEFAULT;  
		tme.dwHoverTime = 50;
		tme.hwndTrack = GetSafeHwnd();
		TrackMouseEvent(&tme);
	}
	
	__super::OnMouseMove(nFlags, point);
}


void CMyButton1::OnMouseHover(UINT nFlags, CPoint point)
{
	m_bHover = true;
	Invalidate();
}


void CMyButton1::OnMouseLeave()
{
	m_bHover = false;
	m_bMouseTrack = true;
	Invalidate();
}
