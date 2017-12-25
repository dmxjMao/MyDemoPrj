// AccountATL.cpp : CAccountATL ��ʵ��

#include "stdafx.h"
#include "AccountATL.h"


// CAccountATL

STDMETHODIMP CAccountATL::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IAccountATL
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CAccountATL::Post(LONG lAccount, BSTR* pbstrResult)
{
	*pbstrResult = ::SysAllocString(L"Hello!This is my first MTS component");

	return S_OK;
}


STDMETHODIMP CAccountATL::get_AlternateColor(OLE_COLOR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CAccountATL::put_AlternateColor(OLE_COLOR newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}
