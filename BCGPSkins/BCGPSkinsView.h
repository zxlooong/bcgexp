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
// BCGPSkinsView.h : interface of the CBCGPSkinsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPSKINSVIEW_H__7BA03F4A_6D75_4D8F_AF37_C29D295B9307__INCLUDED_)
#define AFX_BCGPSKINSVIEW_H__7BA03F4A_6D75_4D8F_AF37_C29D295B9307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPSkinsView : public CScrollView
{
protected: // create from serialization only
	CBCGPSkinsView();
	DECLARE_DYNCREATE(CBCGPSkinsView)

// Attributes
public:
	CBCGPSkinsDoc* GetDocument();

	CBitmap	m_Bmp;
	CSize	m_sizeImage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPSkinsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPSkinsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPSkinsView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BCGPSkinsView.cpp
inline CBCGPSkinsDoc* CBCGPSkinsView::GetDocument()
   { return (CBCGPSkinsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPSKINSVIEW_H__7BA03F4A_6D75_4D8F_AF37_C29D295B9307__INCLUDED_)
