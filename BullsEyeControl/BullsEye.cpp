// BullsEye.cpp : CBullsEye ��ʵ��
#include "stdafx.h"
#include "BullsEye.h"


// CBullsEye


STDMETHODIMP CBullsEye::AboutBox()
{
	

	return S_OK;
}


STDMETHODIMP CBullsEye::DoClick()
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::Refresh()
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}

void CBullsEye::OnBackStyleChanged()
{
	ATLTRACE(_T("OnBackStyleChanged\n"));
}

void CBullsEye::OnEnabledChanged()
{
	ATLTRACE(_T("OnEnabledChanged\n"));
}

void CBullsEye::OnBackColorChanged()
{
	ATLTRACE(_T("OnBackColorChanged\n"));
}

void CBullsEye::OnForeColorChanged()
{
	ATLTRACE(_T("OnForeColorChanged\n"));
}

STDMETHODIMP CBullsEye::get_Application(IDispatch** pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::put_Application(IDispatch* newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::get_AlternateColor(OLE_COLOR* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::put_AlternateColor(OLE_COLOR newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::get_Beep(VARIANT_BOOL* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::put_Beep(VARIANT_BOOL newVal)
{
	// TODO: �ڴ����ʵ�ִ���

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
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::put_Parent(IDispatch* newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::get_RingCount(SHORT* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::put_RingCount(SHORT newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::get_RingValue(LONG* pVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


STDMETHODIMP CBullsEye::put_RingValue(LONG newVal)
{
	// TODO: �ڴ����ʵ�ִ���

	return S_OK;
}


HRESULT CBullsEye::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(LPRECT)di.prcBounds;
	HDC hdc = di.hdcDraw;

	//������Ҫ�Ļ�ˢ

	//BackStyle��͸��ʱ����䱳��ɫ
	if (OPAQUE == m_nBackStyle) {
		::FillRect(hdc, &rc, m_centerBrush);
	}

	//P612
	DrawBullsEye(di);

	/*RECT& rc = *(RECT*)di.prcBounds;
	// ��������������Ϊ di.prcBounds ָ���ľ���
	HRGN hRgnOld = NULL;
	if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
		hRgnOld = NULL;
	bool bSelectOldRgn = false;

	HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

	if (hRgnNew != NULL)
	{
		bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
	}

	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	SetTextAlign(di.hdcDraw, TA_CENTER | TA_BASELINE);
	LPCTSTR pszText = _T("BullsEye");
#ifndef _WIN32_WCE
	TextOut(di.hdcDraw,
		(rc.left + rc.right) / 2,
		(rc.top + rc.bottom) / 2,
		pszText,
		lstrlen(pszText));
#else
	ExtTextOut(di.hdcDraw,
		(rc.left + rc.right) / 2,
		(rc.top + rc.bottom) / 2,
		ETO_OPAQUE,
		NULL,
		pszText,
		ATL::lstrlen(pszText),
		NULL);
#endif

	if (bSelectOldRgn)
		SelectClipRgn(di.hdcDraw, hRgnOld);

	DeleteObject(hRgnNew);*/

	return S_OK;
}

void CBullsEye::DrawBullsEye(ATL_DRAWINFO& di)
{
	HDC hdc = di.hdcDraw;
	//������ˢ

	//���㻷�Ŀ��
	short sRingCount;
	HRESULT hr = get_RingCount(&sRingCount);
	ATLASSERT(SUCCEEDED(hr));

	static const int LOGWIDTH = 1000;
	int ringWidth = LOGWIDTH / (sRingCount * 2 - 1);

	//�ñ߽续�ʻ��ƻ��߽�
	HPEN hOldPen = (HPEN)SelectObject(hdc, m_borderPen);
	HBRUSH hOldBrush = 0;

	for (short i = sRingCount-1; i >=0; --i) {
		//����

		
	}
}