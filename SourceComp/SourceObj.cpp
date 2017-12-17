// SourceObj.cpp : ʵ���ļ�
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
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	AfxOleLockApp();
}

CSourceObj::~CSourceObj()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CSourceObj::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSourceObj, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CSourceObj, CCmdTarget)
	DISP_PROPERTY_EX(CSourceObj, "MyProperty", GetMyProperty, SetMyProperty, VT_I4)
END_DISPATCH_MAP()

// ע��: ������� IID_ISourceObj ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {00ACF9CC-E760-4204-92B7-C98A76D5D151}
static const IID IID_ISourceObj =
{ 0xACF9CC, 0xE760, 0x4204, { 0x92, 0xB7, 0xC9, 0x8A, 0x76, 0xD5, 0xD1, 0x51 } };

// ���ӿ� {235AEA4B-5536-42AC-A6B9-3B62BCDEC35F}
static const GUID IID_IEventSet =
{ 0x235aea4b, 0x5536, 0x42ac,{ 0xa6, 0xb9, 0x3b, 0x62, 0xbc, 0xde, 0xc3, 0x5f } };


BEGIN_INTERFACE_MAP(CSourceObj, CCmdTarget)
	INTERFACE_PART(CSourceObj, IID_ISourceObj, Dispatch)
	INTERFACE_PART(CSourceObj, IID_IConnectionPointContainer, ConnPtContainer)
END_INTERFACE_MAP()

// {040017F7-DE9C-4A16-9A7A-778845B62DB4}
IMPLEMENT_OLECREATE_FLAGS(CSourceObj, "SourceComp.SourceObj", afxRegApartmentThreading, 0x40017f7, 0xde9c, 0x4a16, 0x9a, 0x7a, 0x77, 0x88, 0x45, 0xb6, 0x2d, 0xb4)


//���ӵ�������ӳ���
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

	//����sink
	POSITION pos = m_xEventSetConnPt.GetStartPosition();
	LPDISPATCH pDispatch;
	while (pos != NULL)
	{
		pDispatch = (LPDISPATCH)m_xEventSetConnPt.GetNextConnection(pos);
		ASSERT(pDispatch != NULL);
		driver.AttachDispatch(pDispatch, FALSE);
		TRY
			//���ߵ� CMFCDialogDlg::XEventSink::Invoke���ٸ���dispid
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