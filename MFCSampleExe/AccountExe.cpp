// AccountExe.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCSampleExe.h"
#include "AccountExe.h"


// CAccountExe

IMPLEMENT_DYNCREATE(CAccountExe, CCmdTarget)


CAccountExe::CAccountExe()
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	AfxOleLockApp();
}

CAccountExe::~CAccountExe()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CAccountExe::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CAccountExe, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CAccountExe, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ������� IID_IAccountExe ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {862B69E7-2BC6-4123-8906-E69DEAEF330A}
static const IID IID_IAccountExe =
{ 0x862B69E7, 0x2BC6, 0x4123, { 0x89, 0x6, 0xE6, 0x9D, 0xEA, 0xEF, 0x33, 0xA } };

BEGIN_INTERFACE_MAP(CAccountExe, CCmdTarget)
	INTERFACE_PART(CAccountExe, IID_IAccountExe, Dispatch)
END_INTERFACE_MAP()

// {34494B3D-BD25-4BF3-8C10-4C795B2E1402}
IMPLEMENT_OLECREATE_FLAGS(CAccountExe, "MFCSampleExe.AccountExe", afxRegApartmentThreading, 0x34494b3d, 0xbd25, 0x4bf3, 0x8c, 0x10, 0x4c, 0x79, 0x5b, 0x2e, 0x14, 0x2)


// CAccountExe ��Ϣ�������
