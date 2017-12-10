// MyButton1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyButton1.h"


// CMyButton1

IMPLEMENT_DYNAMIC(CMyButton1, CButton)

CMyButton1::CMyButton1()
{
	try {
		//ui��������
		m_regex.assign(
			"(?|"
			"(picture):(.*\\.(ico|png|bmp))"
			")"
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {
		//theApp.WriteLog
	}
	//uiĬ��ֵ
	m_cfg["picture"] = "";
}

CMyButton1::~CMyButton1()
{
}


BEGIN_MESSAGE_MAP(CMyButton1, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyButton1 ��Ϣ�������




void CMyButton1::OnPaint()
{
	CPaintDC dc(this); 
	Graphics gh(dc.GetSafeHdc());

	auto& pic = m_cfg["picture"];
	CA2T szPic(pic.c_str());
	Gdiplus::Image img(szPic);

	int w = theApp.m_nCloseBtnWidth;
	gh.DrawImage(&img, 0, 0, w, w);
}





void CMyButton1::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	__super::PreSubclassWindow();
}


void CMyButton1::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

}
