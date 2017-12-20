// SourceObj.cpp : 实现文件
//

#include "stdafx.h"
#include "SourceComp.h"
#include "SourceObj.h"


// CSourceObj

IMPLEMENT_DYNCREATE(CSourceObj, CCmdTarget)


CSourceObj::CSourceObj()
{
	EnableAutomation();
	EnableConnections();
	
	// 为了使应用程序在 OLE 自动化对象处于活动状态时保持
	//	运行，构造函数调用 AfxOleLockApp。
	
	AfxOleLockApp();
}

CSourceObj::~CSourceObj()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	
	AfxOleUnlockApp();
}


void CSourceObj::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSourceObj, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CSourceObj, CCmdTarget)
	DISP_PROPERTY_EX(CSourceObj, "MyProperty", GetMyProperty, SetMyProperty, VT_I4)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ISourceObj 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {00ACF9CC-E760-4204-92B7-C98A76D5D151}
static const IID IID_ISourceObj =
{ 0xACF9CC, 0xE760, 0x4204, { 0x92, 0xB7, 0xC9, 0x8A, 0x76, 0xD5, 0xD1, 0x51 } };

// 出接口 {235AEA4B-5536-42AC-A6B9-3B62BCDEC35F}
static const GUID IID_IEventSet =
{ 0x235aea4b, 0x5536, 0x42ac,{ 0xa6, 0xb9, 0x3b, 0x62, 0xbc, 0xde, 0xc3, 0x5f } };


BEGIN_INTERFACE_MAP(CSourceObj, CCmdTarget)
	INTERFACE_PART(CSourceObj, IID_ISourceObj, Dispatch)
	INTERFACE_PART(CSourceObj, IID_IConnectionPointContainer, ConnPtContainer)
END_INTERFACE_MAP()

// {040017F7-DE9C-4A16-9A7A-778845B62DB4}
IMPLEMENT_OLECREATE_FLAGS(CSourceObj, "SourceComp.SourceObj", afxRegApartmentThreading, 0x40017f7, 0xde9c, 0x4a16, 0x9a, 0x7a, 0x77, 0x88, 0x45, 0xb6, 0x2d, 0xb4)


//连接点对象加入映射表
BEGIN_CONNECTION_MAP(CSourceObj, CCmdTarget)
	CONNECTION_PART(CSourceObj, IID_IEventSet, EventSetConnPt)
END_CONNECTION_MAP()


REFIID CSourceObj::XEventSetConnPt::GetIID()
{
	return IID_IEventSet;
}


void CSourceObj::FirePropChanged(long nInt)
{
	COleDispatchDriver driver;

	//遍历sink
	POSITION pos = m_xEventSetConnPt.GetStartPosition();
	LPDISPATCH pDispatch;
	while (pos != NULL)
	{
		pDispatch = (LPDISPATCH)m_xEventSetConnPt.GetNextConnection(pos);
		ASSERT(pDispatch != NULL);
		driver.AttachDispatch(pDispatch, FALSE);
		TRY
			//会走到 CMFCDialogDlg::XEventSink::Invoke，再根据dispid
			driver.InvokeHelper(0/*EventID*/, DISPATCH_METHOD, VT_EMPTY, NULL,
			(BYTE *)(VTS_I4), nInt);
		END_TRY
			driver.DetachDispatch();
	}
}


long CSourceObj::GetMyProperty()
{
	return mProperty;
}

void CSourceObj::SetMyProperty(long nNewValue)
{
	mProperty = nNewValue;
	FirePropChanged(mProperty);
}