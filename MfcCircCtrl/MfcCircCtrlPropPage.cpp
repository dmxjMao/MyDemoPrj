// MfcCircCtrlPropPage.cpp : CMfcCircCtrlPropPage 属性页类的实现。

#include "stdafx.h"
#include "MfcCircCtrl.h"
#include "MfcCircCtrlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMfcCircCtrlPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CMfcCircCtrlPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CMfcCircCtrlPropPage, "MFCCIRCCTRL.MfcCircCtrlPropPage.1",
	0xa5b7caad, 0xc613, 0x4da4, 0x81, 0x91, 0x18, 0xe, 0x20, 0xab, 0x26, 0xad)

// CMfcCircCtrlPropPage::CMfcCircCtrlPropPageFactory::UpdateRegistry -
// 添加或移除 CMfcCircCtrlPropPage 的系统注册表项

BOOL CMfcCircCtrlPropPage::CMfcCircCtrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MFCCIRCCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CMfcCircCtrlPropPage::CMfcCircCtrlPropPage - 构造函数

CMfcCircCtrlPropPage::CMfcCircCtrlPropPage() :
	COlePropertyPage(IDD, IDS_MFCCIRCCTRL_PPG_CAPTION)
{
}

// CMfcCircCtrlPropPage::DoDataExchange - 在页和属性间移动数据

void CMfcCircCtrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CMfcCircCtrlPropPage 消息处理程序
