
// algorithm.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CalgorithmApp: 
// �йش����ʵ�֣������ algorithm.cpp
//

class CalgorithmApp : public CWinApp
{
public:
	CalgorithmApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CalgorithmApp theApp;