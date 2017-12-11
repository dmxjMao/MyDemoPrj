#pragma once


//设置字体，控件声明m_font
#define Macro_SetFont	\
Graphics gh(GetDC()->GetSafeHdc());	\
LOGFONT lfont;	\
theApp.m_pFontDefault->GetLogFontW(&gh, &lfont);	\
m_font.CreateFontIndirect(&lfont);	\
SetFont(&m_font);

//在线状态
enum emOnline {
	Online = 0,
	Offline = 1,
	emOnlineBuff
};

//设备信息
struct stDeviceInfo {
	CString strCode;
	CString strName;
	CString strIP;
	CString strWebsite;
	UINT8 nOnline;
	CTimeSpan tsWork;
};

//使用系统主题
LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist);
//#FFFFFF转Color
bool Convert2Color(const std::string& color, Color& out);
//CRect转RectF
void Convert2RectF(const CRect& rc, RectF& rcF);
//分隔字符串
void SplitString(std::string& line, char ch, std::vector<std::string>& vec);