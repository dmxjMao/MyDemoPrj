
// Embed_ExcelView.cpp : implementation of the CEmbed_ExcelView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Embed_Excel.h"
#endif

#include "Embed_ExcelDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "Embed_ExcelView.h"

//#include "excel.h"
//#include "excel.tlh"

#include "CApplication0.h"
#include "CWorkbook0.h"
#include "CWorkbooks0.h"
#include "CWorksheets0.h"
#include "CWorksheet0.h"
#include "CRange0.h"
#include "CWindows.h"
#include "CWindow0.h"


#include "CChart0.h"
#include "CCharts0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

// CEmbed_ExcelView

IMPLEMENT_DYNCREATE(CEmbed_ExcelView, CView)

BEGIN_MESSAGE_MAP(CEmbed_ExcelView, CView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, &CEmbed_ExcelView::OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, &CEmbed_ExcelView::OnCancelEditCntr)
	ON_COMMAND(ID_FILE_PRINT, &CEmbed_ExcelView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEmbed_ExcelView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEmbed_ExcelView construction/destruction

CEmbed_ExcelView::CEmbed_ExcelView()
{
	m_pSelection = NULL;
	// TODO: add construction code here

}

CEmbed_ExcelView::~CEmbed_ExcelView()
{
}

BOOL CEmbed_ExcelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEmbed_ExcelView drawing

void CEmbed_ExcelView::OnDraw(CDC* pDC)
{
	if (!pDC)
		return;

	CEmbed_ExcelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CEmbed_ExcelCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.
	if (m_pSelection != NULL)
	{
		CSize size;
		CRect rect(10, 10, 0, 0);

		//CRect rc;
		//GetClientRect(&rc);
		//rc.SetRect(rc.left, rc.top, rc.right / 2, rc.bottom / 2);
		//size.cx = rc.Width(); size.cy = rc.Height();
		//pDC->LPtoHIMETRIC(&size);
		//m_pSelection->SetExtent(size);
		//size.cx = size.cy = 0;

		if (m_pSelection->GetExtent(&size, m_pSelection->m_nDrawAspect))
		{
			pDC->HIMETRICtoLP(&size);
			rect.right = size.cx + 10;
			rect.bottom = size.cy + 10;
		}
		m_pSelection->Draw(pDC, rect);
	}
}

void CEmbed_ExcelView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}


// CEmbed_ExcelView printing


void CEmbed_ExcelView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEmbed_ExcelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEmbed_ExcelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEmbed_ExcelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CEmbed_ExcelView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CView::OnDestroy();
}



// OLE Client support and commands

BOOL CEmbed_ExcelView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CEmbed_ExcelCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CEmbed_ExcelView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CEmbed_ExcelCntrItem object
	
	EmbedAutomateExcel();
	//COleInsertDialog dlg;
	//if (dlg.DoModal() != IDOK)
	//	return;

	//BeginWaitCursor();

	//CEmbed_ExcelCntrItem* pItem = NULL;
	//TRY
	//{
	//	// Create new item connected to this document
	//	CEmbed_ExcelDoc* pDoc = GetDocument();
	//	ASSERT_VALID(pDoc);
	//	pItem = new CEmbed_ExcelCntrItem(pDoc);
	//	ASSERT_VALID(pItem);

	//	// Initialize the item from the dialog data
	//	if (!dlg.CreateItem(pItem))
	//		AfxThrowMemoryException();  // any exception will do
	//	ASSERT_VALID(pItem);
	//	
 //       if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
	//		pItem->DoVerb(OLEIVERB_SHOW, this);

	//	ASSERT_VALID(pItem);
	//	// As an arbitrary user interface design, this sets the selection
	//	//  to the last item inserted

	//	// TODO: reimplement selection as appropriate for your application
	//	m_pSelection = pItem;   // set selection to last inserted item
	//	pDoc->UpdateAllViews(NULL);
	//}
	//CATCH(CException, e)
	//{
	//	if (pItem != NULL)
	//	{
	//		ASSERT_VALID(pItem);
	//		pItem->Delete();
	//	}
	//	AfxMessageBox(IDP_FAILED_TO_CREATE);
	//}
	//END_CATCH

	//EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation
void CEmbed_ExcelView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place
void CEmbed_ExcelView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CEmbed_ExcelView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

void CEmbed_ExcelView::OnFilePrint()
{
	//By default, we ask the Active document to print itself
	//using IOleCommandTarget. If you don't want this behavior
	//remove the call to COleDocObjectItem::DoDefaultPrinting.
	//If the call fails for some reason, we will try printing
	//the docobject using the IPrint interface.
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL); 
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;
	
	CView::OnFilePrint();

}


void CEmbed_ExcelView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEmbed_ExcelView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEmbed_ExcelView diagnostics

#ifdef _DEBUG
void CEmbed_ExcelView::AssertValid() const
{
	CView::AssertValid();
}

void CEmbed_ExcelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEmbed_ExcelDoc* CEmbed_ExcelView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEmbed_ExcelDoc)));
	return (CEmbed_ExcelDoc*)m_pDocument;
}
#endif //_DEBUG


// CEmbed_ExcelView message handlers


void CEmbed_ExcelView::EmbedAutomateExcel()
{
	//Change the cursor so the user knows something exciting is going
	//on.
	BeginWaitCursor();

	CEmbed_ExcelCntrItem* pItem = NULL;
	TRY
	{
		//创建“站点对象”
		CEmbed_ExcelDoc* pDoc = GetDocument();
		pItem = new CEmbed_ExcelCntrItem(pDoc);

		//创建“ole对象”并关联“站点对象”
		CLSID clsid;
		if (FAILED(::CLSIDFromProgID(L"Excel.sheet",&clsid)))
			AfxThrowMemoryException();

		if (!pItem->CreateNewItem(clsid))
			AfxThrowMemoryException();

		// 现场激活，若不支持激活，则会启动excel
		//pItem->DoVerb(OLEIVERB_SHOW, this);
		//pItem->Close();

		m_pSelection = pItem;   // set selection to last inserted item
		//pDoc->UpdateAllViews(NULL);

		//Query for the dispatch pointer for the embedded object. In
		//this case, this is the Excel worksheet.
		LPDISPATCH lpDisp;
		lpDisp = pItem->GetIDispatch();

		CApplication0 app;
		CWorkbook0 book;
		CWorksheets0 sheets;
		CWorksheet0 sheet;
	
		//不能直接这样，因为sheet页并没有创建窗口，只有new 了对象(LPDISPATCH)
		//sheet.AttachDispatch(lpDisp);
		
		book.AttachDispatch(lpDisp);
		//app = book.get_Application();
		sheets = book.get_Worksheets();
		sheet = sheets.get_Item(COleVariant((short)1));

		CRange0 range;
		range = sheet.get_Range(COleVariant(TEXT("A1")), COleVariant(TEXT("A1")));
		range.put_Value2(COleVariant(TEXT("Average precipation (mm)")));
		range = sheet.get_Range(COleVariant(TEXT("A1")), COleVariant(TEXT("C1")));
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

		//就是因为在sheet里显示了图表，导致ole尺寸变得很小
		//COleVariant	covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		////添加图表
		//CCharts0 charts;
		//CChart0 chart;
		//charts = book.get_Charts();
		//chart = charts.Add(covOptional, covOptional, covOptional);

		////显示柱形图
		//chart.ApplyCustomType(58, COleVariant());
		//range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("C6")));
		//COleVariant plotBy((short)2);
		//chart.SetSourceData(range, plotBy);

		//pItem->Close();
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();

		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}
