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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSplitterWndView

IMPLEMENT_DYNCREATE(CSplitterWndView, CView)

BEGIN_MESSAGE_MAP(CSplitterWndView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSplitterWndView construction/destruction

CSplitterWndView::CSplitterWndView()
{
	// TODO: add construction code here

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
