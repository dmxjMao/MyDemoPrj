// MfcCircCtrlPropPage.cpp : CMfcCircCtrlPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "MfcCircCtrl.h"
#include "MfcCircCtrlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMfcCircCtrlPropPage, COlePropertyPage)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CMfcCircCtrlPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CMfcCircCtrlPropPage, "MFCCIRCCTRL.MfcCircCtrlPropPage.1",
	0xa5b7caad, 0xc613, 0x4da4, 0x81, 0x91, 0x18, 0xe, 0x20, 0xab, 0x26, 0xad)

// CMfcCircCtrlPropPage::CMfcCircCtrlPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CMfcCircCtrlPropPage ��ϵͳע�����

BOOL CMfcCircCtrlPropPage::CMfcCircCtrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MFCCIRCCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CMfcCircCtrlPropPage::CMfcCircCtrlPropPage - ���캯��

CMfcCircCtrlPropPage::CMfcCircCtrlPropPage() :
	COlePropertyPage(IDD, IDS_MFCCIRCCTRL_PPG_CAPTION)
{
}

// CMfcCircCtrlPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CMfcCircCtrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CMfcCircCtrlPropPage ��Ϣ�������
