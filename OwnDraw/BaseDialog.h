#pragma once
#include "UICfg.h"

// CBaseDialog �Ի���


class CBaseDialog : public CDialogEx, public CUICfg
{
	DECLARE_DYNAMIC(CBaseDialog)

public:
	CBaseDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CBaseDialog(UINT nIDTemplate, CWnd *pParent = NULL);
	virtual ~CBaseDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
	CString m_strTitle = _T("��¼����");
	CFont m_font;

public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
};
