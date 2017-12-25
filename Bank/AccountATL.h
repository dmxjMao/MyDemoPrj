// AccountATL.h : CAccountATL ������

#pragma once
#include "resource.h"       // ������



#include "Bank_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CAccountATL

class ATL_NO_VTABLE CAccountATL :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAccountATL, &CLSID_AccountATL>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAccountATL, &IID_IAccountATL, &LIBID_BankLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAccountATL()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ACCOUNTATL)


BEGIN_COM_MAP(CAccountATL)
	COM_INTERFACE_ENTRY(IAccountATL)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(Post)(LONG lAccount, BSTR* pbstrResult);
	STDMETHOD(get_AlternateColor)(OLE_COLOR* pVal);
	STDMETHOD(put_AlternateColor)(OLE_COLOR newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(AccountATL), CAccountATL)
