
// OwnDraw.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COwnDrawApp:
// See OwnDraw.cpp for the implementation of this class
//

class COwnDrawApp : public CWinApp
{
public:
	COwnDrawApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

private:
	//gdi+初始化
	ULONG_PTR m_gdiplusToken;
	GdiplusStartupInput m_gdiplusStartupInput;

public://程序级成员
	const UINT8 m_nTitleHeight = 25;//标题栏高度
	const Color m_clrTitle = Color(72, 105, 245);//标题栏颜色
	const Color m_clrFont = Color(Color::AntiqueWhite);//文字颜色
	//const TCHAR* m_fontDefault = _T("宋体");//FontFamily和Font不能operator=，作全局也不行
	Gdiplus::Font* m_pFontDefault;//默认字体
	const UINT8 m_nCloseBtnRightGap = 0;//关闭按钮右边距
	const UINT8 m_nCloseBtnWidth = 18;//关闭按钮宽度
	const UINT8 m_nCloseBtnHoverWidth = 20;//鼠标悬浮宽度
};

extern COwnDrawApp theApp;
//程序级变量，不支持operator=
//extern const FontFamily g_fFamilyDefault;
//extern const Gdiplus::Font g_fontDefault;