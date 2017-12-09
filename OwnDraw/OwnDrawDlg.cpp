
// OwnDrawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "OwnDrawDlg.h"
#include "afxdialogex.h"

#include "CustomMenu.h"//自绘菜单
#include "MyButton1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::make_shared;
using std::vector;
using std::shared_ptr;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COwnDrawDlg dialog



COwnDrawDlg::COwnDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OWNDRAW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//m_pMenuPop1 = make_shared<CMenu>();

	m_pMenuPop1 = new CMenu;
	m_pMyMenu1 = new CMyMenu1;

	m_minBtn = make_shared<CMyButton1>();
	(*m_minBtn) & "picture:res\\min_24px.ico";
	m_maxBtn = make_shared<CMyButton1>();
	(*m_maxBtn) & "picture:res\\max_24px.ico";
	m_closeBtn = make_shared<CMyButton1>();
	(*m_closeBtn) & "picture:res\\close_24px.ico";

	try {
		//ui属性正则
		m_regex.assign(
			"(?|"
			"(fontSize):([0-9]+)|"//字体大小	
			"(titleAlign):(left|center|right)|"//标题对齐
			"(btn):([01]{3})"//最小最大化、关闭按钮： 0没有1有
			")"
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {
		//theApp.WriteLog
	}
	//ui默认值
	m_cfg["fontSize"] = "12";
	m_cfg["titleAlign"] = "left";
	m_cfg["btn"] = "001";
}

COwnDrawDlg::~COwnDrawDlg()
{
	if (m_pMenuPop1) {
		delete m_pMenuPop1; m_pMenuPop1 = 0;
	}
	if (m_pMyMenu1) {
		delete m_pMyMenu1; m_pMyMenu1 = 0;
	}
}

void COwnDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_minBtn, *m_minBtn);
	DDX_Control(pDX, IDC_maxBtn, *m_maxBtn);
	DDX_Control(pDX, IDC_closeBtn, *m_closeBtn);
}

BEGIN_MESSAGE_MAP(COwnDrawDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU1_M1, &COwnDrawDlg::OnMenu1M1)
	ON_WM_RBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// COwnDrawDlg message handlers

BOOL COwnDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu) {
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, _T("关于..."));
		pSysMenu->AppendMenu(MF_STRING, IDM_Help, _T("帮助"));

	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	//设置对话框样式：None
	ModifyStyle(WS_OVERLAPPEDWINDOW, 0);



	//UINT cyMenu = ::GetSystemMetrics(SM_CYMENU);
	//CRect rc;
	//GetClientRect(&rc);
	//rc.SetRect(rc.left, rc.top, rc.right, rc.bottom + cyMenu);
	//SetWindowPos(0, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

	//CMenu mu;
	//mu.LoadMenu(IDR_MENU1);
	//SetMenu(&mu);

	//m_pMenuPop1->LoadMenu(IDM_Pop1);
	//m_pMenuPop1.reset(m_pMenuPop1->GetSubMenu(0));
	
	//m_pMenuPop1->LoadMenu(IDM_Pop1);
	//m_pMenuPop1 = m_pMenuPop1->GetSubMenu(0);

	//m_pMyMenu1->LoadMenu(IDM_Pop2);
	//m_pMyMenu1 = (CMyMenu1*)m_pMyMenu1->GetSubMenu(0);
	//m_pMyMenu1->ChangeMenuItem(m_pMyMenu1);

	CRect rc;
	GetClientRect(&rc);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COwnDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	UINT id = nID & 0xFFF0; //低四位系统使用
	if (IDM_ABOUTBOX == id) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (IDM_Help == id) {
		AfxMessageBox(_T("没人帮助你，谢谢。"));
	}
	else { //交给DefWindowProc
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COwnDrawDlg::OnPaint()
{
	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // device context for painting

	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	//	// Center icon in client rectangle
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;

	//	// Draw the icon
	//	dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	//{
	//	CDialogEx::OnPaint();
	//}

	CPaintDC dc(this);
	int x, y, w, h;
	x = y = w = h = 0;
	DWORD flag = SWP_NOZORDER | SWP_NOACTIVATE;

	//自绘标题栏
	CRect rc;
	GetClientRect(&rc);
	CRect rcTitle(0, 0, rc.right, theApp.m_nTitleHeight);
	RectF rcGdi(0.0f, 0.0f, rcTitle.right*1.0f, rcTitle.bottom*1.0f);

	Graphics gh(dc.GetSafeHdc());

	SolidBrush br(theApp.m_clrTitle);
	gh.FillRectangle(&br, rcGdi);
	StringFormat strFormat;
	auto& align = m_cfg["titleAlign"];
	strFormat.SetLineAlignment(StringAlignmentCenter);
	if ("center" == align)
		strFormat.SetAlignment(StringAlignmentCenter);
	else if("right" == align)
		strFormat.SetAlignment(StringAlignmentFar);

	SolidBrush brFont(theApp.m_clrFont);
	gh.DrawString(m_strTitle, -1, theApp.m_pFontDefault, rcGdi, &strFormat, &brFont);

	//最小最大关闭按钮，用Uxtheme不行，因为你先要有这个按钮，它是使用主题而不是画
	const auto& btn = m_cfg["btn"];
	std::bitset<3> bs(btn);
	static vector<shared_ptr<CMyButton1>*> vecBtn = {
		&m_minBtn,&m_maxBtn,&m_closeBtn 
	};
	w = theApp.m_nCloseBtnWidth;
	for (auto i = 0; i < (int)vecBtn.size(); ++i) {
		if (bs[i]) {//依此：关闭、最大、最小
			(*vecBtn[i])->ShowWindow(SW_NORMAL);
			x = rc.right - (3 - i) * (w) - theApp.m_nCloseBtnRightGap;
			(*vecBtn[i])->SetWindowPos(0, x, 0, w, w, flag);
		}
	}

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COwnDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COwnDrawDlg::OnMenu1M1()
{
	AfxMessageBox(_T("OnMenu1M1"));
}


void COwnDrawDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	//point是客户坐标
	//m_muPop1.TrackPopupMenu(TPM_LEFTALIGN, ptScreen.x, ptScreen.y, this); //屏幕坐标

	CDialogEx::OnRButtonUp(nFlags, point);
}


void COwnDrawDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//屏幕坐标
	//m_pMenuPop1->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	m_pMyMenu1->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);

	//CMenu add;
	//add.CreatePopupMenu();
	//add.AppendMenu(MF_STRING, ID_POP1_P1, _T("&New Sibling\tINS"));
	//add.AppendMenu(MF_STRING, ID_POP1_P2, _T("New Child\tCtrl+INS"));
	//add.AppendMenu(MF_STRING, ID_POP1_P3, _T("New Root\tShift+INS"));

	//CMenu menu;//右键菜单
	//menu.CreatePopupMenu();
	//menu.AppendMenu(MF_POPUP, (UINT)add.GetSafeHmenu(), _T("Add"));//子菜单
	//menu.AppendMenu(MF_SEPARATOR);//分割线
	//menu.AppendMenu(MF_STRING | MF_CHECKED, ID_POP1_P1, _T("Select All"));

	//menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); //屏幕坐标

}






void COwnDrawDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_pMyMenu1->DrawItem(lpDrawItemStruct);

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void COwnDrawDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	m_pMyMenu1->MeasureItem(lpMeasureItemStruct);

	CDialogEx::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}







LRESULT COwnDrawDlg::OnNcHitTest(CPoint point)
{
	CRect rc;
	GetClientRect(&rc);
	CRect rcTitle(0, 0, rc.right, theApp.m_nTitleHeight);

	UINT nHitTest = __super::OnNcHitTest(point);
	if (HTCLIENT == nHitTest) {
		ScreenToClient(&point);
		BOOL b = rcTitle.PtInRect(point);
		if (b) { //在标题区
			nHitTest = HTCAPTION;
		}
	}
	return nHitTest;

	//return __super::OnNcHitTest(point);
}
