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
// BCGPOutlookDemoView.h : interface of the CBCGPOutlookDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPOUTLOOKDEMOVIEW_H__3952E28B_16AC_44FB_B047_EF7F8F348697__INCLUDED_)
#define AFX_BCGPOUTLOOKDEMOVIEW_H__3952E28B_16AC_44FB_B047_EF7F8F348697__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPOutlookDemoView : public CBCGPReportView
{
protected: // create from serialization only
	CBCGPOutlookDemoView();
	DECLARE_DYNCREATE(CBCGPOutlookDemoView)

// Attributes
public:
	CBCGPOutlookDemoDoc* GetDocument();

	enum IMPORTANCE
	{
		IMPORTANCE_NORMAL,
		IMPORTANCE_HIGH,
		IMPORTANCE_LOW
	};
	
protected:
	CImageList		m_ImagesHeader;
	CImageList		m_ImagesList;
	CBCGPHeaderCtrl	m_wndHeader;

// Operations
public:

	BOOL AddMail (int nIcon, LPCTSTR strFrom,
		 LPCTSTR strSubject,
		 IMPORTANCE importance = IMPORTANCE_NORMAL,
		 BOOL bHasAttachment = FALSE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPOutlookDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPOutlookDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPOutlookDemoView)
	afx_msg void OnViewPreviewPane();
	afx_msg void OnUpdateViewPreviewPane(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BCGPOutlookDemoView.cpp
inline CBCGPOutlookDemoDoc* CBCGPOutlookDemoView::GetDocument()
   { return (CBCGPOutlookDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPOUTLOOKDEMOVIEW_H__3952E28B_16AC_44FB_B047_EF7F8F348697__INCLUDED_)
