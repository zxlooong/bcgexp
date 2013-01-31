//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// cntritem.h : interface of the CWordPadCntrItem class
//

class CWordPadDoc;
class CWordPadView;

class CWordPadCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CWordPadCntrItem)

// Constructors
public:
	CWordPadCntrItem(REOBJECT* preo = NULL, CWordPadDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CWordPadDoc* GetDocument()
		{ return (CWordPadDoc*)COleClientItem::GetDocument(); }
	CWordPadView* GetActiveView()
		{ return (CWordPadView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordPadCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
