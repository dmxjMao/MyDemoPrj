
// MFCDialogDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMFCDialogDlg 对话框
class CMFCDialogDlg : public CDialogEx
{
// 构造
public:
	CMFCDialogDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDIALOG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//内嵌sink 只要求是一个COM对象，大部分不用实现
	BEGIN_INTERFACE_PART(EventSink, IDispatch)
		INIT_INTERFACE_PART(CMFCDialogDlg, EventSink)
		STDMETHOD(GetTypeInfoCount)(unsigned int*);
		STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**);
		STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, unsigned int, LCID, DISPID*);
		STDMETHOD(Invoke)(DISPID, REFIID, LCID, unsigned short, DISPPARAMS*,
			VARIANT*, EXCEPINFO*, unsigned int*);
	END_INTERFACE_PART(EventSink)

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
