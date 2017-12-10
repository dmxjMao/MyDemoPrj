// BaseDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "BaseDialog.h"
#include "afxdialogex.h"

using std::make_shared;
using std::shared_ptr;

// CBaseDialog 对话框

IMPLEMENT_DYNAMIC(CBaseDialog, CDialogEx)

CBaseDialog::CBaseDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASEDIALOG, pParent)
{

}

CBaseDialog::CBaseDialog(UINT nIDTemplate, CWnd *pParent)
	: CDialogEx(nIDTemplate, pParent)
{

}

CBaseDialog::~CBaseDialog()
{
}

void CBaseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBaseDialog, CDialogEx)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBaseDialog 消息处理程序


BOOL CBaseDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//设置对话框样式：None
	ModifyStyle(WS_OVERLAPPEDWINDOW, 0);

	return TRUE;  
}



LRESULT CBaseDialog::OnNcHitTest(CPoint point)
{
	CRect rc;
	GetClientRect(&rc);
	CRect rcTitle(0, 0, rc.right, theApp.m_nTitleHeight);

	UINT nHitTest = __super::OnNcHitTest(point);
	if (HTCLIENT == nHitTest) {
		ScreenToClient(&point);
		BOOL b = rcTitle.PtInRect(point);
		if (b && !IsZoomed()) { //在标题区&不是最大化
			nHitTest = HTCAPTION;
			//Invalidate();
		}
	}
	return nHitTest;

	//return __super::OnNcHitTest(point);
}

void CBaseDialog::OnPaint()
{
	CPaintDC dc(this); 
	Graphics gh(dc.GetSafeHdc());

	int x, y, w, h;
	x = y = w = h = 0;
	DWORD flag = SWP_NOZORDER | SWP_NOACTIVATE;

	//自绘标题栏
	CRect rc;
	GetClientRect(&rc);
	CRect rcTitle(0, 0, rc.right, theApp.m_nTitleHeight);
	RectF rcGdi(0.0f, 0.0f, rcTitle.right*1.0f, rcTitle.bottom*1.0f);

	SolidBrush br(theApp.m_clrTitle);
	gh.FillRectangle(&br, rcGdi);
	StringFormat strFormat;
	auto& align = m_cfg["titleAlign"];
	strFormat.SetLineAlignment(StringAlignmentCenter);
	if ("center" == align)
		strFormat.SetAlignment(StringAlignmentCenter);
	else if ("right" == align)
		strFormat.SetAlignment(StringAlignmentFar);

	SolidBrush brFont(theApp.m_clrFont);
	gh.DrawString(m_strTitle, -1, theApp.m_pFontDefault, rcGdi, &strFormat, &brFont);


}
