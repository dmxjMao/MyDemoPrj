#pragma once

// MfcCircCtrlPropPage.h : CMfcCircCtrlPropPage ����ҳ���������


// CMfcCircCtrlPropPage : �й�ʵ�ֵ���Ϣ������� MfcCircCtrlPropPage.cpp��

class CMfcCircCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMfcCircCtrlPropPage)
	DECLARE_OLECREATE_EX(CMfcCircCtrlPropPage)

// ���캯��
public:
	CMfcCircCtrlPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MFCCIRCCTRL };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

