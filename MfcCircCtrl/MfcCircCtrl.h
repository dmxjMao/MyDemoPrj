#pragma once

// MfcCircCtrl.h : MfcCircCtrl.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// CMfcCircCtrlApp : �й�ʵ�ֵ���Ϣ������� MfcCircCtrl.cpp��

class CMfcCircCtrlApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

