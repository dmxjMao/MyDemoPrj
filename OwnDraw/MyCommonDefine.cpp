
#include "stdafx.h"
#include "MyCommonDefine.h"


using std::string;
using std::vector;

/*
OpenThemeData  LPCWSTR pszClassList 分号分割的类，Parts and States中的Class列
大部分控件的 subApp = L"Explorer"
*/
LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist)
{
	LRESULT lResult = S_FALSE;

	HRESULT(__stdcall *pSetWindowTheme)(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);
	HANDLE(__stdcall *pOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
	HRESULT(__stdcall *pCloseThemeData)(HANDLE hTheme);

	HMODULE hinstDll = ::LoadLibrary(_T("UxTheme.dll"));
	if (hinstDll) {
		(FARPROC&)pOpenThemeData = ::GetProcAddress(hinstDll, "OpenThemeData");
		(FARPROC&)pCloseThemeData = ::GetProcAddress(hinstDll, "CloseThemeData");
		(FARPROC&)pSetWindowTheme = ::GetProcAddress(hinstDll, "SetWindowTheme");
		
		if (pSetWindowTheme && pOpenThemeData && pCloseThemeData) {
			HANDLE theme = pOpenThemeData(hwnd, classList);
			if (theme) {
				VERIFY(pCloseThemeData(theme) == S_OK);
				lResult = pSetWindowTheme(hwnd, subApp, idlist);
			}
		}
		::FreeLibrary(hinstDll);
	}
	return lResult;
}


bool Convert2Color(const string& color, Color& out)
{
	//char szColor[16] = { 0 };
	DWORD r, g, b;
	sscanf_s(color.c_str(), "%2X%2X%2X", &r, &g, &b);
	COLORREF rgb = RGB(r, g, b);
	out.SetFromCOLORREF(rgb);

	return true;
}

//CRect转RectF
void Convert2RectF(const CRect& rc, RectF& rcF)
{
	rcF.X = rc.left * 1.0f;
	rcF.Y = rc.top * 1.0f;
	rcF.Width = rc.Width() * 1.0f;
	rcF.Height = rc.Height() * 1.0f;
}

//分隔字符串
void SplitString(string& line, char ch, vector<string>& vec)
{
	vec.clear();
	line += ch;

	size_t pos(0), prev(0);
	pos = line.find_first_of(ch, prev);
	while (pos != string::npos) {
		string& str = line.substr(prev, pos - prev);
		vec.push_back(str);
		prev = pos + 1;
		pos = line.find_first_of(ch, prev);
	}
	line.erase(line.size(), 1);
}