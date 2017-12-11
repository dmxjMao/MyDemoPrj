// MyButton1.cpp : 实现文件
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
		/*按钮类型：
		1 图片；2 背景色+文字；
		*/
		m_regex.assign(
			"(?|"
			"(type):([0-9]{1})|"
			"(shape):(rect|roundRect)|"//形状
			"(picture):(.*\\.(ico|png|bmp))|"//图片
			"(bkgColor):#([0-9a-zA-Z]+)"//背景色
			")"
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {
		//theApp.WriteLog
	}
	//ui默认值
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



// CMyButton1 消息处理程序




void CMyButton1::OnPaint()
{
	CPaintDC dc(this); 
	Graphics gh(dc.GetSafeHdc());
	CRect rc;
	GetClientRect(&rc);

	const int type = stoi(m_cfg["type"]);
	switch (type)
	{
	case 1: {//图片
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
		
	case 2: {//背景色+文字
		
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

//BS_OWNERDRAW自绘风格必须重载
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
