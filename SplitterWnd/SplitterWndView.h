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

// SplitterWndView.h : interface of the CSplitterWndView class
//

#pragma once

class CWebBrowser2;

class CSplitterWndView : public CView
{
protected: // create from serialization only
	CSplitterWndView();
	DECLARE_DYNCREATE(CSplitterWndView)

// Attributes
public:
	CSplitterWndDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	std::shared_ptr<CWebBrowser2> m_ie;
	HANDLE m_hIE;
	CComDispatchDriver m_spJScript;
	//����html�ĵ�����
	//void SetHtmlDocmSize(int, int);
	void SetChartData1();
	afx_msg void OnDocumentComplete(LPDISPATCH lpDisp, VARIANT FAR* URL);

// Implementation
public:
	virtual ~CSplitterWndView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_EVENTSINK_MAP()

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAddChart();
	afx_msg void OnHtmldlg();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in SplitterWndView.cpp
inline CSplitterWndDoc* CSplitterWndView::GetDocument() const
   { return reinterpret_cast<CSplitterWndDoc*>(m_pDocument); }
#endif

