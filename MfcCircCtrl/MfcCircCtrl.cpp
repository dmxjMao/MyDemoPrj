// MfcCircCtrl.cpp : CMfcCircCtrlApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "MfcCircCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMfcCircCtrlApp theApp;

const GUID CDECL _tlid = { 0x86FCAD0D, 0xED68, 0x4052, { 0xA1, 0xA8, 0x37, 0x5D, 0x27, 0x38, 0xD2, 0xD3 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CMfcCircCtrlApp::InitInstance - DLL ��ʼ��

BOOL CMfcCircCtrlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  �ڴ��������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CMfcCircCtrlApp::ExitInstance - DLL ��ֹ

int CMfcCircCtrlApp::ExitInstance()
{
	// TODO:  �ڴ��������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - �������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}