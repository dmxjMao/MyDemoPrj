
// OwnDrawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "OwnDrawDlg.h"
#include "afxdialogex.h"

#include "MyCommonDefine.h"
#include "CustomMenu.h"//�Ի�˵�
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
		//ui��������
		m_regex.assign(
			"(?|"
			"(fontSize):([0-9]+)|"//�����С	
			"(titleAlign):(left|center|right)|"//�������
			"(btn):([01]{3})"//��С��󻯡��رհ�ť�� 0û��1��
			")"
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {
		//theApp.WriteLog
	}
	//uiĬ��ֵ
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
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, _T("����..."));
		pSysMenu->AppendMenu(MF_STRING, IDM_Help, _T("����"));

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
	//�û���
	if (0 == m_ctlUserName) {
		m_ctlUserName = make_shared<CMyCombo1>();
		m_ctlUserName->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, 
			CRect(0, 0, 0, 0), this, IDC_UserName);
	}
	vector<CString> vecName = { _T("mao"),_T("ljx") ,_T("liangzipeng") ,_T("���Ӿ�") ,
		_T("ֵ��Ա233"),_T("ֵ��Ա��"),_T("ֵ�೤���"),_T("������"),
		_T("ֵ��Ա233"),_T("ֵ��Ա23333333"),_T("û����"),_T("��õ�ֵ��Ա") };
	m_ctlUserName->FillItem(vecName);

	//GetDlgItem(IDC_BUTTON1)->GetFocus();

	//�����
	if (0 == m_ctlPasswd) {
		m_ctlPasswd = make_shared<CMyEdit1>();
		(*m_ctlPasswd) & "passwd:1";

		m_ctlPasswd->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			CRect(0, 0, 0, 0), this, IDC_Passwd);
	}

	//����ɫ+���� ��ť
	if (0 == m_ctlBtn2) {
		m_ctlBtn2 = make_shared<CMyButton1>();
		(*m_ctlBtn2) & "type:2,bkgColor:#657CF2";

		m_ctlBtn2->Create(0, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			CRect(0, 0, 0, 0), this, IDC_Btn2);
		m_ctlBtn2->SetWindowText(_T("����"));
	}

	//�б��

	m_ctlList->SetWindowPos(0, 10, 50, rc.right - 20, rc.bottom - 20, flag);
	m_ctlList->LoadData();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COwnDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	UINT id = nID & 0xFFF0; //����λϵͳʹ��
	if (IDM_ABOUTBOX == id) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (IDM_Help == id) {
		AfxMessageBox(_T("û�˰����㣬лл��"));
	}
	else { //����DefWindowProc
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

	//��С���رհ�ť����Uxtheme���У���Ϊ����Ҫ�������ť������ʹ����������ǻ�
	const auto& btn = m_cfg["btn"];
	bitset<3> bs(btn);
	vector<shared_ptr<CMyButton1>*> vecBtn = { &m_minBtn,&m_maxBtn,&m_closeBtn };
	w = theApp.m_nCloseBtnWidth;
	for (auto i = 0; i < (int)vecBtn.size(); ++i) {
		if (bs[i]) {//���ˣ��رա������С
			x = rc.right - (i + 1) * (w + 1) - theApp.m_nCloseBtnRightGap;
			(*vecBtn[i])->SetWindowPos(0, x, 0, w, w, flag);
		}
	}
	
	y = theApp.m_nTitleHeight + 10;
	m_ctlUserName->SetWindowPos(0, 10, y, 120, 1, flag);

	//�޷�����������ˣ���BaseDialog�п��ԣ�ȥ��__super::OnPaintҲ����
	//PointF pf(250.0f, 50.0f);
	//SolidBrush br(theApp.m_clrTitle);
	//gh.DrawString(_T("nihao"), -1, theApp.m_pFontDefault, pf, &br);

	//����Ͽ��ڵ�edit��3px�ľ���
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
	//point�ǿͻ�����
	//m_muPop1.TrackPopupMenu(TPM_LEFTALIGN, ptScreen.x, ptScreen.y, this); //��Ļ����

	CDialogEx::OnRButtonUp(nFlags, point);
}


void COwnDrawDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//��Ļ����
	//m_pMenuPop1->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	//m_pMyMenu1->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);

	//CMenu add;
	//add.CreatePopupMenu();
	//add.AppendMenu(MF_STRING, ID_POP1_P1, _T("&New Sibling\tINS"));
	//add.AppendMenu(MF_STRING, ID_POP1_P2, _T("New Child\tCtrl+INS"));
	//add.AppendMenu(MF_STRING, ID_POP1_P3, _T("New Root\tShift+INS"));

	//CMenu menu;//�Ҽ��˵�
	//menu.CreatePopupMenu();
	//menu.AppendMenu(MF_POPUP, (UINT)add.GetSafeHmenu(), _T("Add"));//�Ӳ˵�
	//menu.AppendMenu(MF_SEPARATOR);//�ָ���
	//menu.AppendMenu(MF_STRING | MF_CHECKED, ID_POP1_P1, _T("Select All"));

	//menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this); //��Ļ����

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
	SC_CLOSE	�رհ�ť
	SC_MAXIMIZE	��󻯰�ť
	SC_MINIMIZE	��С����ť
	SC_RESTORE	�ָ���ť
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
