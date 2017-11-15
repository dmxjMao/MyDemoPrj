
// CntrItem.cpp : implementation of the CEmbed_ExcelCntrItem class
//

#include "stdafx.h"
#include "Embed_Excel.h"

#include "Embed_ExcelDoc.h"
#include "Embed_ExcelView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEmbed_ExcelCntrItem implementation

IMPLEMENT_SERIAL(CEmbed_ExcelCntrItem, COleClientItem, 0)

CEmbed_ExcelCntrItem::CEmbed_ExcelCntrItem(CEmbed_ExcelDoc* pContainer)
	: COleClientItem(pContainer)
{
	// TODO: add one-time construction code here
}

CEmbed_ExcelCntrItem::~CEmbed_ExcelCntrItem()
{
	// TODO: add cleanup code here
}

void CEmbed_ExcelCntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleClientItem::OnChange(nCode, dwParam);

	// When an item is being edited (either in-place or fully open)
	//  it sends OnChange notifications for changes in the state of the
	//  item or visual appearance of its content.

	// TODO: invalidate the item by calling UpdateAllViews
	//  (with hints appropriate to your application)

	GetDocument()->UpdateAllViews(NULL);
		// for now just update ALL views/no hints
}

BOOL CEmbed_ExcelCntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// During in-place activation CEmbed_ExcelCntrItem::OnChangeItemPosition
	//  is called by the server to change the position of the in-place
	//  window.  Usually, this is a result of the data in the server
	//  document changing such that the extent has changed or as a result
	//  of in-place resizing.
	//
	// The default here is to call the base class, which will call
	//  COleClientItem::SetItemRects to move the item
	//  to the new position.

	if (!COleClientItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: update any cache you may have of the item's rectangle/extent

	return TRUE;
}

BOOL CEmbed_ExcelCntrItem::OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow)
{
	CFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CFrameWndEx, pFrameWnd);

	if (pMainFrame != NULL)
	{
		ASSERT_VALID(pMainFrame);
		return pMainFrame->OnShowPanes(bShow);
	}

	return FALSE;
}

void CEmbed_ExcelCntrItem::OnGetItemPosition(CRect& rPosition)
{
	ASSERT_VALID(this);

	// During in-place activation, CEmbed_ExcelCntrItem::OnGetItemPosition
	//  will be called to determine the location of this item.  Usually, this 
	//  rectangle would reflect the current position of the item relative to the 
	//  view used for activation.  You can obtain the view by calling 
	//  CEmbed_ExcelCntrItem::GetActiveView.

	// TODO: return correct rectangle (in pixels) in rPosition

	CSize size;
	rPosition.SetRectEmpty();
	if (GetExtent(&size, m_nDrawAspect))
	{
		CEmbed_ExcelView* pView = GetActiveView();
		ASSERT_VALID(pView);
		if (!pView)
			return;
		CDC *pDC = pView->GetDC();
		ASSERT(pDC);
		if (!pDC)
			return;
		pDC->HIMETRICtoLP(&size);
		rPosition.SetRect(10, 10, size.cx + 10, size.cy + 10);
	}
	else
		rPosition.SetRect(10, 10, 210, 210);
}

void CEmbed_ExcelCntrItem::OnActivate()
{
    // Allow only one inplace activate item per frame
    CEmbed_ExcelView* pView = GetActiveView();
    ASSERT_VALID(pView);
	if (!pView)
		return;
    COleClientItem* pItem = GetDocument()->GetInPlaceActiveItem(pView);
    if (pItem != NULL && pItem != this)
        pItem->Close();
    
    COleClientItem::OnActivate();
}

void CEmbed_ExcelCntrItem::OnDeactivateUI(BOOL bUndoable)
{
	COleClientItem::OnDeactivateUI(bUndoable);

    DWORD dwMisc = 0;
    m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
    if (dwMisc & OLEMISC_INSIDEOUT)
        DoVerb(OLEIVERB_HIDE, NULL);
}

void CEmbed_ExcelCntrItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// Call base class first to read in COleClientItem data.
	// Since this sets up the m_pDocument pointer returned from
	//  CEmbed_ExcelCntrItem::GetDocument, it is a good idea to call
	//  the base class Serialize first.
	COleClientItem::Serialize(ar);

	// now store/retrieve data specific to CEmbed_ExcelCntrItem
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CEmbed_ExcelCntrItem diagnostics

#ifdef _DEBUG
void CEmbed_ExcelCntrItem::AssertValid() const
{
	COleClientItem::AssertValid();
}

void CEmbed_ExcelCntrItem::Dump(CDumpContext& dc) const
{
	COleClientItem::Dump(dc);
}
#endif


LPDISPATCH CEmbed_ExcelCntrItem::GetIDispatch()
{
	//The this and m_lpObject pointers must be valid for this function
	//to work correctly. The m_lpObject is the IUnknown pointer to
	// this object.
	ASSERT_VALID(this);

	ASSERT(m_lpObject != NULL);

	LPUNKNOWN lpUnk = m_lpObject;

	//The embedded application must be running in order for the rest
	//of the function to work.
	Run();

	//QI for the IOleLink interface of m_lpObject.
	LPOLELINK lpOleLink = NULL;
	if (m_lpObject->QueryInterface(IID_IOleLink,
		(LPVOID FAR*)&lpOleLink) == NOERROR)
	{
		ASSERT(lpOleLink != NULL);
		lpUnk = NULL;

		//Retrieve the IUnknown interface to the linked application.
		if (lpOleLink->GetBoundSource(&lpUnk) != NOERROR)
		{
			TRACE0("Warning: Link is not connected!\n");
			lpOleLink->Release();
			return NULL;
		}
		ASSERT(lpUnk != NULL);
	}

	//QI for the IDispatch interface of the linked application.
	LPDISPATCH lpDispatch = NULL;
	if (lpUnk->QueryInterface(IID_IDispatch, (LPVOID FAR*)&lpDispatch)
		!= NOERROR)
	{
		TRACE0("Warning: does not support IDispatch!\n");
		return NULL;
	}

	//After assuring ourselves it is valid, return the IDispatch
	//interface to the caller.
	ASSERT(lpDispatch != NULL);
	return lpDispatch;
}