
// MFCDialogDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFCDialogDlg �Ի���
class CMFCDialogDlg : public CDialogEx
{
// ����
public:
	CMFCDialogDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDIALOG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//��Ƕsink ֻҪ����һ��COM���󣬴󲿷ֲ���ʵ��
	BEGIN_INTERFACE_PART(EventSink, IDispatch)
		INIT_INTERFACE_PART(CMFCDialogDlg, EventSink)
		STDMETHOD(GetTypeInfoCount)(unsigned int*);
		STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**);
		STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, unsigned int, LCID, DISPID*);
		STDMETHOD(Invoke)(DISPID, REFIID, LCID, unsigned short, DISPPARAMS*,
			VARIANT*, EXCEPINFO*, unsigned int*);
	END_INTERFACE_PART(EventSink)

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	DWORD m_dwCookie = 0;
	LPDISPATCH m_pDispatch = 0;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

private:
	long m_Property;
};
