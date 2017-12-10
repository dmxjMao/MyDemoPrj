
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
	//gdi+��ʼ��
	ULONG_PTR m_gdiplusToken;
	GdiplusStartupInput m_gdiplusStartupInput;

public://���򼶳�Ա
	const UINT8 m_nTitleHeight = 25;//�������߶�
	const Color m_clrTitle = Color(72, 105, 245);//��������ɫ
	const Color m_clrFont = Color(Color::AntiqueWhite);//������ɫ
	//const TCHAR* m_fontDefault = _T("����");//FontFamily��Font����operator=����ȫ��Ҳ����
	Gdiplus::Font* m_pFontDefault;//Ĭ������
	const UINT8 m_nCloseBtnRightGap = 0;//�رհ�ť�ұ߾�
	const UINT8 m_nCloseBtnWidth = 18;//�رհ�ť���
	const UINT8 m_nCloseBtnHoverWidth = 20;//����������
};

extern COwnDrawApp theApp;
//���򼶱�������֧��operator=
//extern const FontFamily g_fFamilyDefault;
//extern const Gdiplus::Font g_fontDefault;