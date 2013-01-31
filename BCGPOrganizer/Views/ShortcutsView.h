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
#if !defined(AFX_SHORTCUTSVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_)
#define AFX_SHORTCUTSVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShortcutsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShortcutsView view

class CShortcutsView : public CView
{
protected: // create from serialization only
	CShortcutsView();
	DECLARE_DYNCREATE(CShortcutsView)

// Attributes
public:
	CBCGPOrganizerDoc* GetDocument();

	CBCGPHotSpotImageCtrl	m_Image;
	BOOL					m_bIsFirstTime;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutsView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShortcutsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CShortcutsView)
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnClickHotSpot();
	DECLARE_MESSAGE_MAP()

	void SetBitmap ();

private:
	void UpdateCaptionText ();
};

#ifndef _DEBUG  // debug version in ShortcutsView.cpp
inline CBCGPOrganizerDoc* CShortcutsView::GetDocument()
   { return (CBCGPOrganizerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTSVIEW_H__76AA4A51_90F5_4F11_9404_EC70573E2CCA__INCLUDED_)
