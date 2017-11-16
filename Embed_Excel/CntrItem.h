
// CntrItem.h : interface of the CEmbed_ExcelCntrItem class
//

#pragma once

class CEmbed_ExcelDoc;
class CEmbed_ExcelView;

class CEmbed_ExcelCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CEmbed_ExcelCntrItem)

// Constructors
public:
	CEmbed_ExcelCntrItem(CEmbed_ExcelDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer

// Attributes
public:
	CEmbed_ExcelDoc* GetDocument()
		{ return reinterpret_cast<CEmbed_ExcelDoc*>(COleClientItem::GetDocument()); }
	CEmbed_ExcelView* GetActiveView()
		{ return reinterpret_cast<CEmbed_ExcelView*>(COleClientItem::GetActiveView()); }

	LPDISPATCH GetIDispatch();

public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();

protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);

// Implementation
public:
	~CEmbed_ExcelCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

