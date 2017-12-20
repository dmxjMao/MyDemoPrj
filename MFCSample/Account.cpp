// Account.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCSample.h"
#include "Account.h"


// CAccount

IMPLEMENT_DYNCREATE(CAccount, CCmdTarget)


CAccount::CAccount()
	: m_nBalance(0)
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	AfxOleLockApp();
}

CAccount::~CAccount()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CAccount::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CAccount, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CAccount, CCmdTarget)
	DISP_PROPERTY_EX(CAccount, "Balance", GetBalance, SetBalance, VT_I4)
	DISP_FUNCTION(CAccount, "Post", Post2, VT_I4, VTS_I4/* VTS_PBSTR*/)
END_DISPATCH_MAP()

// ע��: ������� IID_IAccount ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {CC6316FE-8AFE-46D9-8005-42EC04C460FA}
static const IID IID_IAccount =
{ 0xCC6316FE, 0x8AFE, 0x46D9, { 0x80, 0x5, 0x42, 0xEC, 0x4, 0xC4, 0x60, 0xFA } };

BEGIN_INTERFACE_MAP(CAccount, CCmdTarget)
	INTERFACE_PART(CAccount, IID_IAccount, Dispatch)
END_INTERFACE_MAP()

// {E0E30A65-2E23-4879-85A4-4B0FB1EF5919}
IMPLEMENT_OLECREATE_FLAGS(CAccount, "MFCSample.Account", afxRegApartmentThreading, 0xe0e30a65, 0x2e23, 0x4879, 0x85, 0xa4, 0x4b, 0xf, 0xb1, 0xef, 0x59, 0x19)


// CAccount ��Ϣ�������


//long CAccount::GetBalance();
//void CAccount::SetBalance(long);

HRESULT CAccount::Post2(long lAmount/*, LPBSTR pResult*/)
{
	TCHAR szBuffer[512] = { 0 };
	if (m_nBalance + lAmount < 0) {
		_stprintf_s(szBuffer, 512,
			_T("Error Balance(%ld) can't be overdrawn by %ld"),
			m_nBalance, lAmount);
	}
	else {
		m_nBalance += lAmount;
		_stprintf_s(szBuffer, 512,
			_T("����(%s)��%ld���,����ʣ�ࣺ%ld"),
			lAmount ? _T("����") : _T("����"), lAmount, m_nBalance);
	}
	//*pResult = T2BSTR(szBuffer);
	return S_OK;
}
