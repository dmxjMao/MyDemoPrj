// Account.cpp : 实现文件
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
	
	// 为了使应用程序在 OLE 自动化对象处于活动状态时保持
	//	运行，构造函数调用 AfxOleLockApp。
	
	AfxOleLockApp();
}

CAccount::~CAccount()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	
	AfxOleUnlockApp();
}


void CAccount::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CAccount, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CAccount, CCmdTarget)
	DISP_PROPERTY_EX(CAccount, "Balance", GetBalance, SetBalance, VT_I4)
	DISP_FUNCTION(CAccount, "Post", Post2, VT_I4, VTS_I4/* VTS_PBSTR*/)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IAccount 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {CC6316FE-8AFE-46D9-8005-42EC04C460FA}
static const IID IID_IAccount =
{ 0xCC6316FE, 0x8AFE, 0x46D9, { 0x80, 0x5, 0x42, 0xEC, 0x4, 0xC4, 0x60, 0xFA } };

BEGIN_INTERFACE_MAP(CAccount, CCmdTarget)
	INTERFACE_PART(CAccount, IID_IAccount, Dispatch)
END_INTERFACE_MAP()

// {E0E30A65-2E23-4879-85A4-4B0FB1EF5919}
IMPLEMENT_OLECREATE_FLAGS(CAccount, "MFCSample.Account", afxRegApartmentThreading, 0xe0e30a65, 0x2e23, 0x4879, 0x85, 0xa4, 0x4b, 0xf, 0xb1, 0xef, 0x59, 0x19)


// CAccount 消息处理程序


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
			_T("您刚(%s)了%ld金币,现在剩余：%ld"),
			lAmount ? _T("存入") : _T("消费"), lAmount, m_nBalance);
	}
	//*pResult = T2BSTR(szBuffer);
	return S_OK;
}
