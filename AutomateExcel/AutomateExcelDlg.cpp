
// AutomateExcelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutomateExcel.h"
#include "AutomateExcelDlg.h"
#include "afxdialogex.h"


#include "CApplication.h"
#include "CWindows.h"
#include "CWindow0.h"
#include "CFont0.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CChart.h"
#include "CCharts.h"


#include <map>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CApplication app;

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
public:
//	afx_msg void OnClose();

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CLOSE()
ON_WM_SIZE()
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
	//DDX_Control(pDX, IDC_MSCHART2, m_demoChart);
}

BEGIN_MESSAGE_MAP(CAutomateExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDRun, &CAutomateExcelDlg::OnBnClickedRun)
	ON_WM_CLOSE()
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
	//m_demoChart.SetWindowPos(0, rc.left + 1, rc.top + 1, rc.Width() - 2, rc.Height() - 15, SWP_NOZORDER | SWP_NOACTIVATE);

	ShowWindow(SW_MAXIMIZE);
	//GetDlgItem(IDRun)->SetWindowPos(0, rc.right / 2, rc.bottom - 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

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

	//CApplication app;
	//LPDISPATCH p = app.get_Application();
	//BOOL bValid = AfxIsValidAddress(p, sizeof(p));
	//if(0 != p)
	//	return;
	//app.ActivateMicrosoftApp(/*xlMicrosoftWord*/5);

	static std::map<UINT8, float> mapDPI = {
		{96,1.0f},{ 120,1.25f },{ 144,1.5f },{ 192,2.0f }
	};
	int n = GetDeviceCaps(GetDC()->GetSafeHdc(), LOGPIXELSX);
	float fScale = 1.0f;
	auto itScale = mapDPI.find(n);
	if (mapDPI.end() != itScale)
		fScale = itScale->second;

	//ֻ�ܵ�һ��Run
	//if (!app.CreateDispatch(TEXT("Excel.Application"))) {
	//	AfxMessageBox(TEXT("Couldn't start Excel and get Application object."));
	//	return;
	//}

	//�ᴴ�����������
	long nCreator = app.get_Creator();
	if (0x5843454C != nCreator){ 
		if (!app.CreateDispatch(TEXT("Excel.Application"))){
			AfxMessageBox(TEXT("Couldn't start Excel and get Application object."));
			return;
		}
	}

	//����excel������ʽ���ʼǱ���װ��office2016����Ч
	HWND hWnd = (HWND)app.get_Hwnd();
	LONG nStyle = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	//nStyle &= ~(WS_BORDER | WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_SIZEBOX);
	nStyle &= ~(WS_OVERLAPPEDWINDOW);
	::SetWindowLongPtr(hWnd, GWL_STYLE, nStyle);
	//::SetMenu(hWnd, 0);
	//�ڶԻ���������ʾ
	::SetWindowPos(hWnd, GetSafeHwnd(), 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	//����excel�����λ��
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);

	//static int i = 0;
	//CRect rc2[2];
	//rc2[0].SetRect(0, 0, (int)(rc.Width() / 2 * 3 / 4 / fScale),(int)(rc.Height() * 3 / 4 / fScale) - 30);
	//rc2[1].SetRect(rc2[0].right, 0, (int)(rc.Width() * 3 / 4 / fScale), rc2[0].Height());

	//���excelȫ����ʾ�ˣ��Ͳ�������Left������Leftֵ��Ч���ᱨ��
	app.put_DisplayFullScreen(FALSE);
	app.put_Left(rc.left * 3 / 4 / fScale);
	app.put_Top(rc.top * 3 / 4 / fScale);
	app.put_Width(rc.Width() * 3 / 4 / fScale);
	app.put_Height(rc.Height() * 3 / 4 / fScale - 30);
	//i %= 2;
	//app.put_Left(rc2[i].left);
	//app.put_Top(rc2[i].top);
	//app.put_Width(rc2[i].Width());
	//app.put_Height(rc2[i].Height());
	//++i;
	//excel������ƶ�

	//app.get_MenuBars()
	//app.put_AlwaysUseClearType(TRUE);
	//��ʽ������������״̬�����رճ�����ʾ�����桱
	app.put_DisplayFormulaBar(FALSE);
	app.put_DisplayScrollBars(FALSE);
	app.put_DisplayStatusBar(FALSE);
	app.put_DisplayAlerts(FALSE); 
	
	//app.put_ShowMenuFloaties(FALSE);
	//app.put_ShowDevTools(FALSE);
	//app.put_CalculateBeforeSave(FALSE);

	//����ribbon
	//app.ExecuteExcel4Macro(_T("SHOW.TOOLBAR(""Ribbon"", False)"));
	app.ExecuteExcel4Macro(_T("SHOW.TOOLBAR(\"Ribbon\", False)"));

	//CMenuBars menuBars = app.get_MenuBars();
	//long nCnts = menuBars.get_Count();

	//for (long i = 1; i <= nCnts; ++i) {
	//	CMenuBar mb = menuBars.get_Item(COleVariant((short)i));
	//	CString str = mb.get_Caption();
	//	str = _T("");
	//	
	//}
	

	CWorkbooks books;
	CWorkbook book;
	CWorksheets sheets;
	CWorksheet sheet;

	books = app.get_Workbooks();
	book = books.Add(covOptional); //�½�һ��workbook�������´ε��Runʱ���ǡ�������2��

	//Get the first sheet.
	sheets = book.get_Worksheets(); //��ȡworksheets
	sheet = sheets.get_Item(COleVariant((short)1));
	//sheet.Activate();

	//long nCnt = sheets.get_Count();
	//for (long i = 2; i <= nCnt; ++i) {
	//	CWorksheet tmpSheet = sheets.get_Item(COleVariant((short)i));
	//	tmpSheet.put_Visible(FALSE);
	//}

	CWindows wnds; //һ��worksheet��һ������
	wnds = app.get_Windows();
	//long nCnt = wnds.get_Count();
	//long nCreator = wnds.get_Creator();

	CWindow0 wnd;
	wnd = wnds.get_Item(COleVariant((short)1));
	
	//wnd.put_DisplayFormulas(FALSE);
	//wnd.put_DisplayGridlines(FALSE);
	//wnd.put_DisplayHeadings(FALSE);

	//nCnt = 0;

	CRange range;
	CFont0 font;
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
	//range = sheet.get_Range(COleVariant(TEXT("A1")), COleVariant(TEXT("C1")));
	//font = range.get_Font();
	//font.put_Bold(covTrue);
	//range.put_VerticalAlignment(COleVariant((short)-4108));   //xlVAlignCenter = -4108

	//AutoFit columns A:D.
	//range = sheet.get_Range(COleVariant(TEXT("A1")), COleVariant(TEXT("D1")));
	//CRange cols;
	//cols = range.get_EntireColumn();
	//cols.AutoFit();

	//���ͼ��
	CCharts charts;
	CChart chart;
	charts = book.get_Charts();
	chart = charts.Add(covOptional, covOptional, covOptional);
	
	//��ʾ����ͼ
	chart.ApplyCustomType(51, COleVariant());
	range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("C6")));
	COleVariant plotBy((short)2);
	chart.SetSourceData(range, plotBy);
	// chart.ColumnGroups(COleVariant());
	//long nCnt = chart

	app.put_Interactive(FALSE);
	app.put_Cursor(1);
	app.put_Visible(TRUE);
	app.put_UserControl(TRUE);
}




//void CAutomateExcelDlg::InitChart()
//{
//	// ���ñ���
//	m_demoChart.put_TitleText(_T("mschart ʾ�� by thinkry@263.net"));
//	
//	// ����ɫ
//	m_demoChart.get_Backdrop()->GetFill().SetStyle(1);
//	
//	m_demoChart.GetBackdrop().GetFill().GetBrush().GetFillColor().Set(255, 255, 255);
//	
//	// ��ʾͼ��
//	m_demoChart.SetShowLegend(TRUE);
//	
//	m_demoChart.SetColumn(1);
//	
//	m_demoChart.SetColumnLabel((LPCTSTR)"1�Ż�");
//	
//	m_demoChart.SetColumn(2);
//	
//	m_demoChart.SetColumnLabel((LPCTSTR)"2�Ż�");
//	
//	m_demoChart.SetColumn(3);
//	
//	m_demoChart.SetColumnLabel((LPCTSTR)"3�Ż�");
//	
//	// ջģʽ
//	// m_demoChart.SetStacking(TRUE);
//	// Y������
//	VARIANT var;
//	
//	m_demoChart.GetPlot().GetAxis(1, var).GetValueScale().SetAuto(FALSE); // ���Զ���עY ��̶�
//	
//	m_demoChart.GetPlot().GetAxis(1, var).GetValueScale().SetMaximum(100); // Y�����̶�
//	
//	m_demoChart.GetPlot().GetAxis(1, var).GetValueScale().SetMinimum(0); // Y����С�̶�
//	
//	m_demoChart.GetPlot().GetAxis(1, var).GetValueScale().SetMajorDivision(5); // Y���   ��5�ȷ�
//	
//	m_demoChart.GetPlot().GetAxis(1, var).GetValueScale().SetMinorDivision(1); // ÿ�̶�   һ���̶���
//	
//	m_demoChart.GetPlot().GetAxis(1, var).GetAxisTitle().SetText("Сʱ"); // Y������
//	
//	// 3������
//	m_demoChart.SetColumnCount(3);
//	
//	// ��ɫ
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(1).GetPen().GetVtColor().Set(0,		0, 255);
//	
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(2).GetPen().GetVtColor().Set	(255, 0, 0);
//	
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(3).GetPen().GetVtColor().Set(0,		255, 0);
//	
//	// �߿�(�Ե���ͼ��Ч)
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(1).GetPen().SetWidth(50);
//	
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(2).GetPen().SetWidth(100);
//	
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(3).GetPen().SetWidth(2);
//	
//	// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
//	// 0: ����ʾ 1: ��ʾ����״ͼ��
//	// 2: ��ʾ����״ͼ���Ϸ� 3: ��ʾ����״ͼ���м� 4: ��ʾ����״ͼ���·�
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(1).GetDataPoints().GetItem  (-1).GetDataPointLabel().SetLocationType(1);
//	
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(2).GetDataPoints().GetItem  (-1).GetDataPointLabel().SetLocationType(1);
//	
//	m_demoChart.GetPlot().GetSeriesCollection().GetItem(3).GetDataPoints().GetItem  (-1).GetDataPointLabel().SetLocationType(1);
//	
//}



void CAutomateExcelDlg::OnClose()
{
	//ɾ���������ݣ�������ʾ�����桱
	//CWorkbooks books = app.get_Workbooks();
	//CWorkbook book = books.get_Item(COleVariant((short)1));
	//CWorksheets sheets = book.get_Worksheets(); //��ȡworksheets
	//CWorksheet sheet = sheets.get_Item(COleVariant((short)1));
	//sheet.Delete();

	//COleVariant filename(_T("excel_demo"));
	//app.Save(filename);
	RestoreExcelStyle();
	app.Quit();

	CDialogEx::OnClose();
}

void CAutomateExcelDlg::RestoreExcelStyle()
{
	HWND hWnd = (HWND)app.get_Hwnd();
	LONG nStyle = ::GetWindowLongPtr(hWnd, GWL_STYLE);
	nStyle |= WS_OVERLAPPEDWINDOW;
	::SetWindowLongPtr(hWnd, GWL_STYLE, nStyle);

	//app.put_DisplayFullScreen(FALSE);
	//app.put_Left(rc.left * 3 / 4 / fScale);
	//app.put_Top(rc.top * 3 / 4 / fScale);
	//app.put_Width(rc.Width() * 3 / 4 / fScale);
	//app.put_Height(rc.Height() * 3 / 4 / fScale - 30);); 	

	app.ExecuteExcel4Macro(_T("SHOW.TOOLBAR(\"Ribbon\", True)"));

	app.put_DisplayFormulaBar(TRUE);
	app.put_DisplayScrollBars(TRUE);
	app.put_DisplayStatusBar(TRUE);
	//app.put_DisplayAlerts(TRUE);
}	


