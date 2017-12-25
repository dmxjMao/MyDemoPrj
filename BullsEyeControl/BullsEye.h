// BullsEye.h : CBullsEye 的声明
#pragma once
#include "resource.h"       // 主符号
#include <atlctl.h>
#include "BullsEyeControl_i.h"
#include "_IBullsEyeEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;



// CBullsEye
class ATL_NO_VTABLE CBullsEye :
	//COM对象支持
	public CComObjectRootEx<CComSingleThreadModel>,
	//固有属性
	public CStockPropImpl<CBullsEye, IBullsEye>,
	//最小接口实现
	public IOleControlImpl<CBullsEye>,
	public IOleObjectImpl<CBullsEye>,
	public IOleInPlaceActiveObjectImpl<CBullsEye>,
	public IViewObjectExImpl<CBullsEye>,
	public IOleInPlaceObjectWindowlessImpl<CBullsEye>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CBullsEye>,
	public CProxy_IBullsEyeEvents<CBullsEye>,
	public IPersistStorageImpl<CBullsEye>,
	public ISpecifyPropertyPagesImpl<CBullsEye>,
	public IQuickActivateImpl<CBullsEye>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CBullsEye>,
#endif
	public IProvideClassInfo2Impl<&CLSID_BullsEye, &__uuidof(_IBullsEyeEvents), &LIBID_BullsEyeControlLib>,
	//连接点
	public IPropertyNotifySinkCP<CBullsEye>,
	public CComCoClass<CBullsEye, &CLSID_BullsEye>,
	public CComControl<CBullsEye>
{
public:


	CBullsEye()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_BULLSEYE)


BEGIN_COM_MAP(CBullsEye)
	COM_INTERFACE_ENTRY(IBullsEye)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()


BEGIN_PROP_MAP(CBullsEye)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage, VT_UI4)
#endif
	PROP_ENTRY_TYPE("BackStyle", DISPID_BACKSTYLE, CLSID_NULL, VT_I4)
	PROP_ENTRY_TYPE("Enabled", DISPID_ENABLED, CLSID_NULL, VT_BOOL)
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage, VT_UI4)
#endif
	// 示例项
	// PROP_ENTRY_TYPE("属性名", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CBullsEye)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_IBullsEyeEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CBullsEye)
	CHAIN_MSG_MAP(CComControl<CBullsEye>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// 处理程序原型: 
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IBullsEye,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IBullsEye
public:
	HRESULT OnDraw(ATL_DRAWINFO& di);
	void DrawBullsEye(ATL_DRAWINFO& di);

	//固有属性
	OLE_COLOR m_clrBackColor;
	void OnBackColorChanged();
	LONG m_nBackStyle;
	void OnBackStyleChanged();
	BOOL m_bEnabled;
	void OnEnabledChanged();
	OLE_COLOR m_clrForeColor;
	void OnForeColorChanged();

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() { return S_OK; }

	void FinalRelease() {}
	//固有方法
	STDMETHOD(AboutBox)();
	STDMETHOD(DoClick)();
	STDMETHOD(Refresh)();

	//自定义属性
	IDispatch* m_pDispApp = 0;
	STDMETHOD(get_Application)(IDispatch** pVal);
	STDMETHOD(put_Application)(IDispatch* newVal);
	OLE_COLOR m_clrAlternateColor = 0;
	STDMETHOD(get_AlternateColor)(OLE_COLOR* pVal);
	STDMETHOD(put_AlternateColor)(OLE_COLOR newVal);
	VARIANT_BOOL m_bBeep = 0;
	STDMETHOD(get_Beep)(VARIANT_BOOL* pVal);
	STDMETHOD(put_Beep)(VARIANT_BOOL newVal);
	OLE_COLOR m_clrCenterColor = 0;
	//STDMETHOD(get_CenterColor)(OLE_COLOR* pVal);
	//STDMETHOD(put_CenterColor)(OLE_COLOR newVal);
	IMPLEMENT_STOCKPROP(OLE_COLOR, CenterColor, clrCenterColor, DISPID_CenterColor)
	IDispatch* m_pDispParent = 0;
	STDMETHOD(get_Parent)(IDispatch** pVal);
	STDMETHOD(put_Parent)(IDispatch* newVal);
	SHORT m_nRingCount = 0;
	STDMETHOD(get_RingCount)(SHORT* pVal);
	STDMETHOD(put_RingCount)(SHORT newVal);
	LONG m_nRingValue = 0;
	STDMETHOD(get_RingValue)(LONG* pVal);
	STDMETHOD(put_RingValue)(LONG newVal);

private:
	HBRUSH m_centerBrush;
	HPEN m_borderPen;
};

OBJECT_ENTRY_AUTO(__uuidof(BullsEye), CBullsEye)
