// AccountExe.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCSampleExe.h"
#include "AccountExe.h"


// CAccountExe

IMPLEMENT_DYNCREATE(CAccountExe, CCmdTarget)


CAccountExe::CAccountExe()
{
	EnableAutomation();
	
	// 为了使应用程序在 OLE 自动化对象处于活动状态时保持
	//	运行，构造函数调用 AfxOleLockApp。
	
	AfxOleLockApp();
}

CAccountExe::~CAccountExe()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	
	AfxOleUnlockApp();
}


void CAccountExe::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CAccountExe, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CAccountExe, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IAccountExe 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {862B69E7-2BC6-4123-8906-E69DEAEF330A}
static const IID IID_IAccountExe =
{ 0x862B69E7, 0x2BC6, 0x4123, { 0x89, 0x6, 0xE6, 0x9D, 0xEA, 0xEF, 0x33, 0xA } };

BEGIN_INTERFACE_MAP(CAccountExe, CCmdTarget)
	INTERFACE_PART(CAccountExe, IID_IAccountExe, Dispatch)
END_INTERFACE_MAP()

// {34494B3D-BD25-4BF3-8C10-4C795B2E1402}
IMPLEMENT_OLECREATE_FLAGS(CAccountExe, "MFCSampleExe.AccountExe", afxRegApartmentThreading, 0x34494b3d, 0xbd25, 0x4bf3, 0x8c, 0x10, 0x4c, 0x79, 0x5b, 0x2e, 0x14, 0x2)


// CAccountExe 消息处理程序
