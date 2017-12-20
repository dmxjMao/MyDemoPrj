
// MFCDialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCDialog.h"
#include "MFCDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDialogDlg �Ի���
// ���ӿ� {235AEA4B-5536-42AC-A6B9-3B62BCDEC35F}
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


// CMFCDialogDlg ��Ϣ�������

BOOL CMFCDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//#importʹ�ô������
	if (FAILED(m_account.CreateInstance(__uuidof(Account)))) {
		return FALSE;
	}

	//�����Ӷ���
	/*GUID guid;
	HRESULT hr = ::CLSIDFromProgID(L"SourceComp.SourceObj", &guid);
	if (FAILED(hr))
		return FALSE;

	hr = CoCreateInstance(guid, 0, CLSCTX_INPROC_SERVER, IID_IDispatch, (LPVOID*)&m_pDispatch);
	if (FAILED(hr))
		return FALSE;*/

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDialogDlg::OnBnClickedButton1()
{
	if (m_dwCookie)
		return;

	LPCONNECTIONPOINTCONTAINER pConnPtCont = 0;
	if (m_pDispatch && //�Ƿ��ǿ����Ӷ���
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
		//�����Զ����ӿ�
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
