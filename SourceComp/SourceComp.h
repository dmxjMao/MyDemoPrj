// SourceComp.h : SourceComp DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSourceCompApp
// �йش���ʵ�ֵ���Ϣ������� SourceComp.cpp
//

class CSourceCompApp : public CWinApp
{
public:
	CSourceCompApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
