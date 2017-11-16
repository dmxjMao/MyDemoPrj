
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
		CRect rect(10, 10, 210, 210);
		
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
		//Get the document associated with this view, and be sure it's
		//valid.
		CEmbed_ExcelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//Create a new item associated with this document, and be sure
	//it's valid.
	pItem = new CEmbed_ExcelCntrItem(pDoc);
	ASSERT_VALID(pItem);

	// Get Class ID for Excel sheet.
	// This is used in creation.
	CLSID clsid;
	if (FAILED(::CLSIDFromProgID(L"Excel.sheet",&clsid)))
		//Any exception will do. We just need to break out of the
		//TRY statement.
		AfxThrowMemoryException();

	// Create the Excel embedded item.
	if (!pItem->CreateNewItem(clsid))
		//Any exception will do. We just need to break out of the
		//TRY statement.
		AfxThrowMemoryException();

	//Make sure the new CContainerItem is valid.
	ASSERT_VALID(pItem);

	// Launch the server to edit the item.
	pItem->DoVerb(OLEIVERB_SHOW, this);
	pItem->Close();

	

	// As an arbitrary user interface design, this sets the
	// selection to the last item inserted.
	m_pSelection = pItem;   // set selection to last inserted item
	pDoc->UpdateAllViews(NULL);

	//Query for the dispatch pointer for the embedded object. In
	//this case, this is the Excel worksheet.
	LPDISPATCH lpDisp;
	lpDisp = pItem->GetIDispatch();


	
	//Add text in cell A1 of the embedded Excel sheet
	
	//_Workbook wb;
	//Worksheets wsSet;
	//_Worksheet ws;
	//Range range;
	//_Application app;

	//set _Workbook wb to use lpDisp, the IDispatch* of the
	//actual workbook.
	//wb.AttachDispatch(lpDisp);
	//app = wb.GetApplication();

	//Then get the worksheet's application.

	CApplication0 app;
	CWorkbook0 book;
	CWorksheets0 sheets;
	CWorksheet0 sheet;
	
	book.AttachDispatch(lpDisp);
	app = book.get_Application();

	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));

	CRange0 range;
	range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("A1")));
	range.put_Value2(COleVariant(_T("Hello, World!")));


	app.ExecuteExcel4Macro(_T("SHOW.TOOLBAR(\"Ribbon\", False)"));
	app.put_DisplayScrollBars(FALSE);
	app.put_DisplayStatusBar(FALSE);
	app.put_DisplayFormulaBar(FALSE);
	//app.put_DisplayAlerts(FALSE);

	CWindows wnds; //一个worksheet算一个窗口
	wnds = app.get_Windows();

	CWindow0 wnd;
	wnd = wnds.get_Item(COleVariant((short)1));

	//wnd.put_DisplayFormulas(FALSE);
	wnd.put_DisplayGridlines(FALSE);
	wnd.put_DisplayHeadings(FALSE);

	//Then get the first worksheet in the workbook
	//wsSet = wb.GetWorksheets();
	
	//ws = wsSet.GetItem(COleVariant((short)1));

	//From there, get a Range object corresponding to cell A1.
	

	//Fill A1 with the string "Hello, World!"
	

	//NOTE: If you are automating Excel 2002, the Range.SetValue method has an 
	//additional optional parameter specifying the data type.  Because the 
	//parameter is optional, existing code will still work correctly, but new 
	//code should use the new convention.  The call for Excel2002 should look 
	//like the following:

	//range.SetValue( C<?xm-insertion_mark_start author="v-thomr" time="20070326T121607-0600"?>O<?xm-insertion_mark_end?><?xm-deletion_mark author="v-thomr" time="20070326T121606-0600" data="o"?>leVariant( (long)DISP_E_PARAMNOTFOUND, VT_ERROR ), 
	//                COleVariant("Hello, World!"));
	}

		//Here, we need to do clean up if something went wrong.
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

		//Set the cursor back to normal so the user knows exciting stuff
		//is no longer happening.
		EndWaitCursor();
}
