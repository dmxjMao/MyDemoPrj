
// Embed_ExcelView.h : interface of the CEmbed_ExcelView class
//

#pragma once

class CEmbed_ExcelCntrItem;

class CEmbed_ExcelView : public CView
{
protected: // create from serialization only
	CEmbed_ExcelView();
	DECLARE_DYNCREATE(CEmbed_ExcelView)

// Attributes
public:
	CEmbed_ExcelDoc* GetDocument() const;
	// m_pSelection holds the selection to the current CEmbed_ExcelCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CEmbed_ExcelCntrItem objects.  This selection
	//  mechanism is provided just to help you get started

	// TODO: replace this selection mechanism with one appropriate to your app
	CEmbed_ExcelCntrItem* m_pSelection;

	void EmbedAutomateExcel();

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support

// Implementation
public:
	virtual ~CEmbed_ExcelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Embed_ExcelView.cpp
inline CEmbed_ExcelDoc* CEmbed_ExcelView::GetDocument() const
   { return reinterpret_cast<CEmbed_ExcelDoc*>(m_pDocument); }
#endif

