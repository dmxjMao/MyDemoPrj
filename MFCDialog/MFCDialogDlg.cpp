
// MFCDialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCDialog.h"
#include "MFCDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDialogDlg 对话框
// 出接口 {235AEA4B-5536-42AC-A6B9-3B62BCDEC35F}
static const GUID IID_IEventSet =
{ 0x235aea4b, 0x5536, 0x42ac,{ 0xa6, 0xb9, 0x3b, 0x62, 0xbc, 0xde, 0xc3, 0x5f } };



CMFCDialogDlg::CMFCDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCDIALOG_DIALOG, pParent)
	, m_Property(0)
	, m_nBalance(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT1, m_Property);
	DDX_Text(pDX, IDC_EDIT2, m_nBalance);
}

BEGIN_MESSAGE_MAP(CMFCDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDialogDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCDialogDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCDialogDlg::OnBnClickedButton3)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCDialogDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCDialogDlg 消息处理程序

BOOL CMFCDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//#import使用代码组件
	if (FAILED(m_account.CreateInstance(__uuidof(Account)))) {
		return FALSE;
	}

	//可连接对象
	/*GUID guid;
	HRESULT hr = ::CLSIDFromProgID(L"SourceComp.SourceObj", &guid);
	if (FAILED(hr))
		return FALSE;

	hr = CoCreateInstance(guid, 0, CLSCTX_INPROC_SERVER, IID_IDispatch, (LPVOID*)&m_pDispatch);
	if (FAILED(hr))
		return FALSE;*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDialogDlg::OnBnClickedButton1()
{
	if (m_dwCookie)
		return;

	LPCONNECTIONPOINTCONTAINER pConnPtCont = 0;
	if (m_pDispatch && //是否是可连接对象
		SUCCEEDED(m_pDispatch->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pConnPtCont)))
	{
		LPCONNECTIONPOINT pConnPt = 0;

		if (SUCCEEDED(pConnPtCont->FindConnectionPoint(IID_IEventSet, &pConnPt)))
		{
			pConnPt->Advise(&m_xEventSink, &m_dwCookie);
			pConnPt->Release();
		}
	}

	pConnPtCont->Release();
}





STDMETHODIMP_(ULONG) CMFCDialogDlg::XEventSink::AddRef()
{
	return 1;
}

STDMETHODIMP_(ULONG) CMFCDialogDlg::XEventSink::Release()
{
	return 0;
}

STDMETHODIMP CMFCDialogDlg::XEventSink::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CMFCDialogDlg, EventSink)

		if (IsEqualIID(iid, IID_IUnknown) ||
			IsEqualIID(iid, IID_IDispatch) ||
			IsEqualIID(iid, IID_IEventSet))
		{
			*ppvObj = this;
			AddRef();
			return S_OK;
		}
		else
		{
			return E_NOINTERFACE;
		}
}

STDMETHODIMP CMFCDialogDlg::XEventSink::GetTypeInfoCount(
	unsigned int*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMFCDialogDlg::XEventSink::GetTypeInfo(
	unsigned int, LCID, ITypeInfo**)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMFCDialogDlg::XEventSink::GetIDsOfNames(
	REFIID, LPOLESTR*, unsigned int, LCID, DISPID*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMFCDialogDlg::XEventSink::Invoke(
	DISPID dispid, REFIID, LCID, unsigned short wFlags,
	DISPPARAMS* pDispParams, VARIANT* pvarResult,
	EXCEPINFO* pExcepInfo, unsigned int* puArgError)
{
	if (dispid == 0) {
		AfxMessageBox(_T("The Property has been changed!"));
	}
	else {
		AfxMessageBox(_T("I don't known the event!"));
	}
	return S_OK;
}

void CMFCDialogDlg::OnBnClickedButton2()
{
	if (0 == m_dwCookie)
		return;

	LPCONNECTIONPOINTCONTAINER pConnPtCont;

	if ((m_pDispatch != NULL) &&
		SUCCEEDED(m_pDispatch->QueryInterface(IID_IConnectionPointContainer,
		(LPVOID*)&pConnPtCont)))
	{
		ASSERT(pConnPtCont != NULL);
		LPCONNECTIONPOINT pConnPt = NULL;

		if (SUCCEEDED(pConnPtCont->FindConnectionPoint(IID_IEventSet, &pConnPt)))
		{
			ASSERT(pConnPt != NULL);
			pConnPt->Unadvise(m_dwCookie);
			pConnPt->Release();
			m_dwCookie = 0;
		}

		pConnPtCont->Release();
	}
}


void CMFCDialogDlg::OnBnClickedButton3()
{
	if (!UpdateData(TRUE))
	{
		TRACE0("UpdateData failed during dialog termination.\n");
		// the UpdateData routine will set focus to correct item
		return;
	}

	COleDispatchDriver driver;
	driver.AttachDispatch(m_pDispatch, FALSE);
	TRY
		//调用自动化接口
		driver.SetProperty(0x1, VT_I4, m_Property);
	END_TRY
		
	driver.DetachDispatch();
}


void CMFCDialogDlg::OnClose()
{
	m_account.Release();

	CDialogEx::OnClose();
}


void CMFCDialogDlg::OnBnClickedButton4()
{
	UpdateData();

	CString str;
	BSTR bstr = str.AllocSysString();

	HRESULT hr = m_account->Post(m_nBalance);
	AfxMessageBox(bstr);
	::SysFreeString(bstr);
}
