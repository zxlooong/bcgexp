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
// BCGPShopDemoView.h : interface of the CBCGPShopDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPSHOPDEMOVIEW_H__E7442BF6_1493_44FC_85FD_DF85979C9156__INCLUDED_)
#define AFX_BCGPSHOPDEMOVIEW_H__E7442BF6_1493_44FC_85FD_DF85979C9156__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPShopDemoView : public CScrollView
{
protected: // create from serialization only
	CBCGPShopDemoView();
	DECLARE_DYNCREATE(CBCGPShopDemoView)

// Attributes
public:
	CBCGPShopDemoDoc* GetDocument();

// Operations
public:

    BOOL MapScreenPoint (CPoint& ptInOut);
    COLORREF GetPixelColor (const CPoint& ptView) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPShopDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPShopDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CRect  GetPageRect ();

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPShopDemoView)
    afx_msg int OnCreate(LPCREATESTRUCT lpcs);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    const int m_nHorizontalViewMargin;
    const int m_nVerticalViewMargin;
};

#ifndef _DEBUG  // debug version in BCGPShopDemoView.cpp
inline CBCGPShopDemoDoc* CBCGPShopDemoView::GetDocument()
   { return (CBCGPShopDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPSHOPDEMOVIEW_H__E7442BF6_1493_44FC_85FD_DF85979C9156__INCLUDED_)
