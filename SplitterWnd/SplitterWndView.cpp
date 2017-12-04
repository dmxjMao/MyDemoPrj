// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// SplitterWndView.cpp : implementation of the CSplitterWndView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SplitterWnd.h"
#endif

#include "SplitterWndDoc.h"
#include "SplitterWndView.h"

#include "MsHTML.h"
#include "CWebBrowser2.h"

#include "HtmlTestDlg.h"

#include <fstream>
#include <json\json.h>
#pragma comment(lib, "lib_json")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_IE 100 //ie
#define IDT_EChart 1

// CSplitterWndView

IMPLEMENT_DYNCREATE(CSplitterWndView, CView)

BEGIN_MESSAGE_MAP(CSplitterWndView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_AddChart, &CSplitterWndView::OnAddChart)
	ON_COMMAND(ID_HtmlDlg, &CSplitterWndView::OnHtmldlg)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CSplitterWndView, CView)
	ON_EVENT(CSplitterWndView, IDC_IE, 259/*DocumentComplete*/,
		OnDocumentComplete, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()

// CSplitterWndView construction/destruction

CSplitterWndView::CSplitterWndView()
{
	m_ie = make_shared<CWebBrowser2>();
	m_hIE = ::CreateEvent(0, TRUE, FALSE, 0);
}

CSplitterWndView::~CSplitterWndView()
{
}

BOOL CSplitterWndView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSplitterWndView drawing

void CSplitterWndView::OnDraw(CDC* /*pDC*/)
{
	CSplitterWndDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CSplitterWndView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSplitterWndView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSplitterWndView diagnostics

#ifdef _DEBUG
void CSplitterWndView::AssertValid() const
{
	CView::AssertValid();
}

void CSplitterWndView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSplitterWndDoc* CSplitterWndView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitterWndDoc)));
	return (CSplitterWndDoc*)m_pDocument;
}
#endif //_DEBUG


// CSplitterWndView message handlers


void CSplitterWndView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(&rc);

	HWND hIE = m_ie->GetSafeHwnd();
	if (hIE) {
		m_ie->SetWindowPos(0, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
		//������ҳ��С
		//SetHtmlDocmSize(rc.Width(), rc.Height());
	}

}




void CSplitterWndView::OnAddChart()
{
	
	CRect rc;
	GetClientRect(&rc);

	if (0 == m_ie->GetSafeHwnd()) {
		if (!m_ie->Create(0, WS_CHILD | WS_VISIBLE, rc, this, IDC_IE)) {
			AfxMessageBox(_T("����ie���ʧ�ܣ�"));
			return;
		}
	}
	//ModifyStyle(WS_HSCROLL | WS_VSCROLL, 0);

	CString str(_T("E:\\maoyinan\\prj\\MyDemoPrj\\SplitterWnd\\echart\\myEChart.html"));


	m_ie->Navigate(str, 0, 0, 0, 0);

}


void CSplitterWndView::OnHtmldlg()
{
	CHtmlTestDlg dlg;
	dlg.DoModal();
}



void CSplitterWndView::OnDocumentComplete(LPDISPATCH lpDisp,
	VARIANT FAR* URL)
{
	IUnknown*  pUnk;
	LPDISPATCH lpWBDisp;
	HRESULT    hr;

	pUnk = m_ie->GetControlUnknown();
	ASSERT(pUnk);

	hr = pUnk->QueryInterface(IID_IDispatch, (void**)&lpWBDisp);
	ASSERT(SUCCEEDED(hr));

	if (lpDisp == lpWBDisp)
	{
		// Top-level Window object, so document has been loaded  
		TRACE("Web document is finished downloading/n");

		CComQIPtr<IHTMLDocument2> spDoc = m_ie->get_Document();
		if (NULL == spDoc) {
			return;
		}

		if (m_spJScript)
			m_spJScript.Release();

		hr = spDoc->get_Script(&m_spJScript);
		if (FAILED(hr)) {
			TRACE(_T("spDoc->get_Script(&m_spJScript)  failed!"));
		}

		//�����ĵ���ʼ��С
		//CRect rc;
		//GetClientRect(&rc);
		//SetHtmlDocmSize(rc.Width(), rc.Height());
		
		//���ñ���
		CComVariant var(_T("�ܺõ�"));
		m_spJScript.Invoke1(_T("SetTitle"), &var);

		//����ͼ������
		SetChartData1();
		SetTimer(IDT_EChart, 1000, 0);
		::SetEvent(m_hIE);//�����¼�
	}
	
	lpWBDisp->Release();


	//CComVariant var(_T("hello,html! 30sˢ�� ����è���С�"));
	//// ���ñ���
	//hr = m_spJScript.Invoke1(_T("SetSubTitle"), &var);
}


//����html�ĵ����
//void CSplitterWndView::SetHtmlDocmSize(int w, int h)
//{
//	CComVariant wVar(w), hVar(h);
//	m_spJScript.Invoke2(_T("Layout"), &wVar, &hVar);
//
//	//��Ӧwindows.onsize�¼�
//	TRACE(_T("SetFrameSize:%d,%d"), w, h);
//}

void CSplitterWndView::SetChartData1()
{
	
	/* 
	��������:
	 {
		data: [5, 20, 36, 10, 10, 20]
     }
	*/
	vector<int> vec = { 50, 200, 36, 10, 10, 20 };
	vector<int> vec2 = { 100, 20, 36, 10, 10, 20 };
	static int i = 0;

	Json::Value data;
	if (i % 2) {
		for (auto& n : vec)
			data.append(n);
	}
	else {
		for (auto& n : vec2)
			data.append(n);
	}
	++i;

	Json::Value obj;
	obj["data"] = data;

	//string out1 = obj.toStyledString();
	//ofstream ofs("E:\\maoyinan\\a.txt");
	//ofs << out1;
	//ofs.close();

	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "";
	string out = Json::writeString(builder, obj);

	CComVariant var(out.c_str());
	HRESULT hr = m_spJScript.Invoke1(_T("SetData1"), &var);
}

void CSplitterWndView::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case IDT_EChart:
		SetChartData1();
		break;
	default:
		break;
	}

	CView::OnTimer(nIDEvent);
}
