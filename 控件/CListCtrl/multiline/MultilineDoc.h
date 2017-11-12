// MultilineDoc.h : interface of the CMultilineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTILINEDOC_H__3050964C_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
#define AFX_MULTILINEDOC_H__3050964C_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMultilineDoc : public CDocument
{
protected: // create from serialization only
	CMultilineDoc();
	DECLARE_DYNCREATE(CMultilineDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultilineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultilineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultilineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILINEDOC_H__3050964C_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
