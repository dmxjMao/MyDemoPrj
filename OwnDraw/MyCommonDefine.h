#pragma once


//�������壬�ؼ�����m_font
#define Macro_SetFont	\
Graphics gh(GetDC()->GetSafeHdc());	\
LOGFONT lfont;	\
theApp.m_pFontDefault->GetLogFontW(&gh, &lfont);	\
m_font.CreateFontIndirect(&lfont);	\
SetFont(&m_font);

//����״̬
enum emOnline {
	Online = 0,
	Offline = 1,
	emOnlineBuff
};

//�豸��Ϣ
struct stDeviceInfo {
	CString strCode;
	CString strName;
	CString strIP;
	CString strWebsite;
	UINT8 nOnline;
	CTimeSpan tsWork;
};

//ʹ��ϵͳ����
LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist);
//#FFFFFFתColor
bool Convert2Color(const std::string& color, Color& out);
//CRectתRectF
void Convert2RectF(const CRect& rc, RectF& rcF);
//�ָ��ַ���
void SplitString(std::string& line, char ch, std::vector<std::string>& vec);