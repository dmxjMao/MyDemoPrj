
// MFCSampleExe.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCSampleExeApp: 
// �йش����ʵ�֣������ MFCSampleExe.cpp
//

class CMFCSampleExeApp : public CWinApp
{
public:
	CMFCSampleExeApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCSampleExeApp theApp;