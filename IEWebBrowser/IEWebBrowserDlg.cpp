
// IEWebBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IEWebBrowser.h"
#include "IEWebBrowserDlg.h"
#include "afxdialogex.h"

#include "EmbedIEDlg.h"

using std::shared_ptr;
using std::make_shared;
using std::vector;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CIEWebBrowserDlg dialog



CIEWebBrowserDlg::CIEWebBrowserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IEWEBBROWSER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIEWebBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_Explorer, m_ie);
	DDX_Control(pDX, IDC_AddChart, m_addChart);
}

BEGIN_MESSAGE_MAP(CIEWebBrowserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_AddChart, &CIEWebBrowserDlg::OnBnClickedAddchart)
END_MESSAGE_MAP()


// CIEWebBrowserDlg message handlers

BOOL CIEWebBrowserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	CRect rc;
	GetClientRect(&rc);
	CRect rcBtn;
	m_addChart.GetClientRect(&rcBtn);
	m_rcChart.SetRect(rc.left, rc.top, rc.right, rc.bottom - rcBtn.Height() - 1);

	//int x = ::GetSystemMetrics(SM_CXSCREEN);
	//int y = ::GetSystemMetrics(SM_CYSCREEN);
	
	m_addChart.SetWindowPos(0, 0, m_rcChart.bottom + 1, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIEWebBrowserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIEWebBrowserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIEWebBrowserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIEWebBrowserDlg::OnBnClickedAddchart()
{
	auto& spDlg = make_shared<CEmbedIEDlg>();
	spDlg->Create(IDD_IEWebBrowser, this);

	//²¼¾Ö
	//int nDiv = 1;
	//static int cxChart = m_rcChart.Width() / nDiv;
	//static int cyChart = m_rcChart.Height() / nDiv;

	//int nDlgCnt = (int)m_vecChartDlg.size();
	//int x = nDlgCnt % nDiv * cxChart;
	//int y = nDlgCnt / nDiv * cyChart;

	//spDlg->SetWindowPos(0, x, y, cxChart, cyChart, SWP_NOACTIVATE | SWP_NOZORDER);
	spDlg->ShowWindow(SW_NORMAL);

	m_vecChartDlg.push_back(spDlg);
}
