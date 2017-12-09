// MyButton1.cpp : 实现文件
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyButton1.h"


// CMyButton1

IMPLEMENT_DYNAMIC(CMyButton1, CButton)

CMyButton1::CMyButton1()
{
	try {
		//ui属性正则
		m_regex.assign(
			"(?|"
			"(picture):(.*\\.(ico|png|bmp))"
			")"
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {
		//theApp.WriteLog
	}
	//ui默认值
	m_cfg["picture"] = "";
}

CMyButton1::~CMyButton1()
{
}


BEGIN_MESSAGE_MAP(CMyButton1, CButton)
END_MESSAGE_MAP()



// CMyButton1 消息处理程序


