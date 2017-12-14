
// OwnDrawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "OwnDrawDlg.h"
#include "afxdialogex.h"

#include "MyCommonDefine.h"
#include "CustomMenu.h"//自绘菜单
#include "MyButton1.h"
#include "MyCombo1.h"
#include "MyEdit1.h"
#include "MyListCtrl1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::make_shared;
using std::vector;
using std::shared_ptr;
using std::bitset;
using std::string;

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
	: /*CDialogEx*/CBaseDialog(IDD_OWNDRAW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//m_pMenuPop1 = make_shared<CMenu>();

	m_pMenuPop1 = new CMenu;
	m_pMyMenu1 = new CMyMenu1;
	
	m_ctlList = make_shared<CMyListCtrl1>();

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

	DDX_Control(pDX, IDC_LIST1, *m_ctlList);
}

BEGIN_MESSAGE_MAP(COwnDrawDlg, /*CDialogEx*/CBaseDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU1_M1, &COwnDrawDlg::OnMenu1M1)
	ON_WM_RBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_COMMAND_RANGE(IDC_minBtn, IDC_closeBtn, &COwnDrawDlg::OnBnClicked)
	ON_BN_CLICKED(IDC_BUTTON1, &COwnDrawDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// COwnDrawDlg message handlers

BOOL COwnDrawDlg::OnInitDialog()
{
	//CDialogEx::OnInitDialog();
	__super::OnInitDialog();

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

	//Graphics gh(GetDC()->GetSafeHdc());

	CRect rc;
	GetClientRect(&rc);
	DWORD flag = SWP_NOZORDER | SWP_NOACTIVATE;

	const auto& btn = m_cfg["btn"];
	bitset<3> bs(btn);
	vector<shared_ptr<CMyButton1>*> vecBtn = { &m_minBtn,&m_maxBtn,&m_closeBtn };
	vector<const char*> vecRes = { "picture:res\\close_24px.ico",
		"picture:res\\max_24px.ico" ,"picture:res\\min_24px.ico" };
	vector<int> vecCtrlID = { IDC_closeBtn, IDC_maxBtn, IDC_minBtn };
	for (int i = 0; i < (int)vecBtn.size(); ++i) {
		if (bs[i]) {
			auto& sp = *vecBtn[i];
			if (0 == sp) {
				sp = make_shared<CMyButton1>();
				sp->Create(0, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, vecCtrlID[i]);
			}
				
			(*sp) & vecRes[i];
		}
	}
	//用户名
	if (0 == m_ctlUserName) {
		m_ctlUserName = make_shared<CMyCombo1>();
		m_ctlUserName->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
			CRect(0, 0, 0, 0), this, IDC_UserName);
	}
	vector<CString> vecName = { _T("mao"),_T("ljx") ,_T("liangzipeng") ,_T("果子卷") ,
		_T("值班员233"),_T("值班员甲"),_T("值班长杨好"),_T("主任奕"),
		_T("值班员233"),_T("值班员23333333"),_T("没事了"),_T("最好的值班员") };
	m_ctlUserName->FillItem(vecName);

	//GetDlgItem(IDC_BUTTON1)->GetFocus();

	//密码框
	if (0 == m_ctlPasswd) {
		m_ctlPasswd = make_shared<CMyEdit1>();
		(*m_ctlPasswd) & "passwd:1";

		m_ctlPasswd->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			CRect(0, 0, 0, 0), this, IDC_Passwd);
	}

	//背景色+文字 按钮
	if (0 == m_ctlBtn2) {
		m_ctlBtn2 = make_shared<CMyButton1>();
		(*m_ctlBtn2) & "type:2,bkgColor:#657CF2";

		m_ctlBtn2->Create(0, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			CRect(0, 0, 0, 0), this, IDC_Btn2);
		m_ctlBtn2->SetWindowText(_T("点我"));
	}

	//列表框

	m_ctlList->SetWindowPos(0, 10, 50, rc.right - 20, rc.bottom - 20, flag);
	m_ctlList->LoadData();

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

	__super::OnPaint();

	CPaintDC dc(this);
	//CPaintDC dc((CBaseDialog*)this);
	Graphics gh(dc.GetSafeHdc());
	//HDC hdc = GetParent()->GetDC()->GetSafeHdc();
	//Graphics gh(hdc);

	int x, y, w, h;
	x = y = w = h = 0;
	DWORD flag = SWP_NOZORDER | SWP_NOACTIVATE;

	CRect rc;
	GetClientRect(&rc);

	//最小最大关闭按钮，用Uxtheme不行，因为你先要有这个按钮，它是使用主题而不是画
	const auto& btn = m_cfg["btn"];
	bitset<3> bs(btn);
	vector<shared_ptr<CMyButton1>*> vecBtn = { &m_minBtn,&m_maxBtn,&m_closeBtn };
	w = theApp.m_nCloseBtnWidth;
	for (auto i = 0; i < (int)vecBtn.size(); ++i) {
		if (bs[i]) {//依此：关闭、最大、最小
			x = rc.right - (i + 1) * (w + 1) - theApp.m_nCloseBtnRightGap;
			(*vecBtn[i])->SetWindowPos(0, x, 0, w, w, flag);
		}
	}
	
	y = theApp.m_nTitleHeight + 10;
	m_ctlUserName->SetWindowPos(0, 10, y, 120, 1, flag);

	//无法再输出文字了，在BaseDialog中可以，去掉__super::OnPaint也可以
	//PointF pf(250.0f, 50.0f);
	//SolidBrush br(theApp.m_clrTitle);
	//gh.DrawString(_T("nihao"), -1, theApp.m_pFontDefault, pf, &br);

	//与组合框内的edit有3px的距离
	y += 30;
	m_ctlPasswd->SetWindowPos(0, 13, y, 120, 20, flag);

	y += 30;
	m_ctlBtn2->SetWindowPos(0, 10, y, 40, 20, flag);

	y += 30;
	m_ctlList->SetWindowPos(0, 10, y, rc.Width() - 20, 300, flag);
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
	//m_pMyMenu1->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);

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







void COwnDrawDlg::OnBnClicked(UINT nID)
{
	/*
	SC_CLOSE	关闭按钮
	SC_MAXIMIZE	最大化按钮
	SC_MINIMIZE	最小化按钮
	SC_RESTORE	恢复按钮
	*/
	if (IDC_maxBtn == nID) {
		static bool bRestore = false;
		PostMessage(WM_SYSCOMMAND, bRestore ? SC_RESTORE : SC_MAXIMIZE);
		bRestore = !bRestore;
		Invalidate();
	}
	if(IDC_minBtn == nID)
		PostMessage(WM_SYSCOMMAND, SC_MINIMIZE);
	if (IDC_closeBtn == nID)
		PostMessage(WM_SYSCOMMAND, SC_CLOSE);
}

void COwnDrawDlg::OnBnClickedButton1()
{
	
}
