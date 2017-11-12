
// AutomateExcelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutomateExcel.h"
#include "AutomateExcelDlg.h"
#include "afxdialogex.h"


#include "CApplication.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CChart.h"
#include "CCharts.h"

//#include "mschart2.h"

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


// CAutomateExcelDlg dialog



CAutomateExcelDlg::CAutomateExcelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTOMATEEXCEL_DIALOG, pParent)
	/*, m_demoChart(0)*/
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutomateExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCHART2, m_demoChart);
}

BEGIN_MESSAGE_MAP(CAutomateExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDRun, &CAutomateExcelDlg::OnBnClickedRun)
END_MESSAGE_MAP()


// CAutomateExcelDlg message handlers

BOOL CAutomateExcelDlg::OnInitDialog()
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

	// TODO: Add extra initialization here

	CRect rc;
	GetClientRect(&rc);
	m_demoChart.SetWindowPos(0, rc.left + 1, rc.top + 1, rc.Width() - 2, rc.Height() - 15, SWP_NOZORDER | SWP_NOACTIVATE);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAutomateExcelDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAutomateExcelDlg::OnPaint()
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
HCURSOR CAutomateExcelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void FillSafeArray(OLECHAR FAR* sz, int iRow, int iCol,
	COleSafeArray* sa)
{

	VARIANT v;
	long index[2];

	index[0] = iRow;
	index[1] = iCol;

	VariantInit(&v);
	v.vt = VT_BSTR;
	v.bstrVal = SysAllocString(sz);
	sa->PutElement(index, v.bstrVal);
	SysFreeString(v.bstrVal);
	VariantClear(&v);

}

void CAutomateExcelDlg::OnBnClickedRun()
{
	// Commonly used OLE variants.
	COleVariant
		covTrue((short)TRUE),
		covFalse((short)FALSE),
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	CApplication app;

	// Start Excel and get an Application object.
	if (!app.CreateDispatch(TEXT("Excel.Application")))
	{
		AfxMessageBox(TEXT("Couldn't start Excel and get Application object."));
		return;
	}

	CWorkbooks books;
	CWorkbook book;
	CWorksheets sheets;
	CWorksheet sheet;
	CRange range;
	CFont0 font;

	books = app.get_Workbooks();
	book = books.Add(covOptional);


	//Get the first sheet.
	sheets = book.get_Sheets();
	sheet = sheets.get_Item(COleVariant((short)1));

	range = sheet.get_Range(COleVariant(TEXT("A1")), COleVariant(TEXT("A1")));
	range.put_Value2(COleVariant(TEXT("Average precipation (mm)")));
	range = sheet.get_Range(COleVariant(TEXT("A1")), COleVariant(TEXT("C1")));
	range.Merge(covOptional);//�ϲ�A1-C1�����ֺ����Щ��Ԫ��
	range = sheet.get_Range(COleVariant(TEXT("B2")), COleVariant(TEXT("B2")));
	range.put_Value2(COleVariant(TEXT("Acapulco")));
	range = sheet.get_Range(COleVariant(TEXT("C2")), COleVariant(TEXT("C2")));
	range.put_Value2(COleVariant(TEXT("Amsterdam")));


	//Fill A3:A6 with an array of values (Months).
	COleSafeArray saRet;
	DWORD numElements[] = { 4,1 };   //4x1 element array
	saRet.Create(VT_BSTR, 2, numElements);

	FillSafeArray(L"January", 0, 0, &saRet);
	FillSafeArray(L"April", 1, 0, &saRet);
	FillSafeArray(L"July", 2, 0, &saRet);
	FillSafeArray(L"October", 3, 0, &saRet);

	range = sheet.get_Range(COleVariant(TEXT("A3")), COleVariant(TEXT("A6")));
	range.put_Value2(COleVariant(saRet));
	saRet.Detach();

	//Fill B3:C6 with values
	range = sheet.get_Range(COleVariant(TEXT("B3")), COleVariant(TEXT("B3")));
	range.put_Value2(COleVariant(short(10)));
	range = sheet.get_Range(COleVariant(TEXT("B4")), COleVariant(TEXT("B4")));
	range.put_Value2(COleVariant(short(69)));
	range = sheet.get_Range(COleVariant(TEXT("B5")), COleVariant(TEXT("B5")));
	range.put_Value2(COleVariant(short(5)));
	range = sheet.get_Range(COleVariant(TEXT("B6")), COleVariant(TEXT("B6")));
	range.put_Value2(COleVariant(short(53)));
	range = sheet.get_Range(COleVariant(TEXT("C3")), COleVariant(TEXT("C3")));
	range.put_Value2(COleVariant(short(208)));
	range = sheet.get_Range(COleVariant(TEXT("C4")), COleVariant(TEXT("C4")));
	range.put_Value2(COleVariant(short(76)));
	range = sheet.get_Range(COleVariant(TEXT("C5")), COleVariant(TEXT("C5")));
	range.put_Value2(COleVariant(short(145)));
	range = sheet.get_Range(COleVariant(TEXT("C6")), COleVariant(TEXT("C6")));
	range.put_Value2(COleVariant(short(74)));


	//Format A1:C1 as bold, vertical alignment = center.
	range = sheet.get_Range(COleVariant(TEXT("A1")), COleVariant(TEXT("C1")));
	font = range.get_Font();
	font.put_Bold(covTrue);
	range.put_VerticalAlignment(COleVariant((short)-4108));   //xlVAlignCenter = -4108

	//AutoFit columns A:D.
	range = sheet.get_Range(COleVariant(TEXT("A1")), COleVariant(TEXT("D1")));
	CRange cols;
	cols = range.get_EntireColumn();
	cols.AutoFit();

	//Adding Chart
	CCharts charts;
	CChart chart;
	charts = book.get_Charts();
	chart = charts.Add(covOptional, covOptional, covOptional);

	app.put_Visible(TRUE);
	app.put_UserControl(TRUE);
}
