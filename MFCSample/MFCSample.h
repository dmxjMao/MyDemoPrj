// MFCSample.h : MFCSample DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCSampleApp
// �йش���ʵ�ֵ���Ϣ������� MFCSample.cpp
//

class CMFCSampleApp : public CWinApp
{
public:
	CMFCSampleApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
