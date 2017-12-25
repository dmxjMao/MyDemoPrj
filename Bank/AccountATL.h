// AccountATL.h : CAccountATL 的声明

#pragma once
#include "resource.h"       // 主符号



#include "Bank_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
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
