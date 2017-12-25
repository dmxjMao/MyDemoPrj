// BullsEye.cpp : CBullsEye 的实现
#include "stdafx.h"
#include "BullsEye.h"


// CBullsEye


STDMETHODIMP CBullsEye::AboutBox()
{
	

	return S_OK;
}


STDMETHODIMP CBullsEye::DoClick()
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::Refresh()
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::get_Application(IDispatch** pVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::put_Application(IDispatch* newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::get_AlternateColor(OLE_COLOR* pVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::put_AlternateColor(OLE_COLOR newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::get_Beep(VARIANT_BOOL* pVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::put_Beep(VARIANT_BOOL newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


//STDMETHODIMP CBullsEye::get_CenterColor(OLE_COLOR* pVal)
//{
//	if (!pVal) return E_POINTER;
//	*pVal = m_clrCenterColor;
//
//	return S_OK;
//}
//
//
//STDMETHODIMP CBullsEye::put_CenterColor(OLE_COLOR newVal)
//{
//	if (newVal == m_clrCenterColor) return S_OK;
//
//
//	return S_OK;
//}


STDMETHODIMP CBullsEye::get_Parent(IDispatch** pVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::put_Parent(IDispatch* newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::get_RingCount(SHORT* pVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::put_RingCount(SHORT newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::get_RingValue(LONG* pVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}


STDMETHODIMP CBullsEye::put_RingValue(LONG newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}
