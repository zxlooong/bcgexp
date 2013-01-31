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
// CntrItem.h : interface of the CBCGPMSOffice2007DemoCntrItem class
//

#if !defined(AFX_CNTRITEM_H__28D2D8C4_FDB7_4AC5_897C_F0564D8931E1__INCLUDED_)
#define AFX_CNTRITEM_H__28D2D8C4_FDB7_4AC5_897C_F0564D8931E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPMSOffice2007DemoDoc;
class CBCGPMSOffice2007DemoView;

class CBCGPMSOffice2007DemoCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CBCGPMSOffice2007DemoCntrItem)

// Constructors
public:
	CBCGPMSOffice2007DemoCntrItem(REOBJECT* preo = NULL, CBCGPMSOffice2007DemoDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CBCGPMSOffice2007DemoDoc* GetDocument()
		{ return (CBCGPMSOffice2007DemoDoc*)CRichEditCntrItem::GetDocument(); }
	CBCGPMSOffice2007DemoView* GetActiveView()
		{ return (CBCGPMSOffice2007DemoView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSOffice2007DemoCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);

// Implementation
public:
	~CBCGPMSOffice2007DemoCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	UINT	m_uiCategoryID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__28D2D8C4_FDB7_4AC5_897C_F0564D8931E1__INCLUDED_)
