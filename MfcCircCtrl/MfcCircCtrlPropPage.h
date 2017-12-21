#pragma once

// MfcCircCtrlPropPage.h : CMfcCircCtrlPropPage 属性页类的声明。


// CMfcCircCtrlPropPage : 有关实现的信息，请参阅 MfcCircCtrlPropPage.cpp。

class CMfcCircCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMfcCircCtrlPropPage)
	DECLARE_OLECREATE_EX(CMfcCircCtrlPropPage)

// 构造函数
public:
	CMfcCircCtrlPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_MFCCIRCCTRL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

