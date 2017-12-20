
// MFCSampleExe.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MFCSampleExe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSampleExeApp

BEGIN_MESSAGE_MAP(CMFCSampleExeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCSampleExeApp ����

CMFCSampleExeApp::CMFCSampleExeApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCSampleExeApp ����

CMFCSampleExeApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x6A6E89E4, 0x7A01, 0x4106, { 0x90, 0x23, 0x1B, 0xEA, 0x8E, 0x34, 0xDD, 0x38 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CMFCSampleExeApp ��ʼ��

BOOL CMFCSampleExeApp::InitInstance()
{
	//CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// �����Զ������ػ�ע��/ע�����ص������С�
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Ӧ�ó������� /Embedding �� /Automation ���������ġ�
	//ʹӦ�ó�����Ϊ�Զ������������С�
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// ͨ�� CoRegisterClassObject() ע���๤����
		COleTemplateServer::RegisterAll();
	}
	// Ӧ�ó������� /Unregserver �� /Unregister ���������ġ�  �Ƴ�
	// ע����е��
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// Ӧ�ó������Զ�����ʽ������������(�� /Register
	// �� /Regserver)�����ġ�  ����ע�����������Ϳ⡣
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CMFCSampleExeApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
