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
// MMStyleExampleView.h : interface of the CMMStyleExampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMSTYLEEXAMPLEVIEW_H__2B4A9A0C_0017_40BA_9788_802E09CE9F1D__INCLUDED_)
#define AFX_MMSTYLEEXAMPLEVIEW_H__2B4A9A0C_0017_40BA_9788_802E09CE9F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMMStyleExampleView : public CView
{
protected: // create from serialization only
	CMMStyleExampleView();
	DECLARE_DYNCREATE(CMMStyleExampleView)

// Attributes
public:
	CMMStyleExampleDoc* GetDocument();

protected:
	CString	m_strProgress;
	CFont	m_fntSong;
	CFont	m_fntProgress;
	CRect	m_rectProgress;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMStyleExampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMMStyleExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void PrintText (CDC* pDC, CString str, int x, int y, CFont& font);
	void PrepareProgressText ();

// Generated message map functions
protected:
	//{{AFX_MSG(CMMStyleExampleView)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MMStyleExampleView.cpp
inline CMMStyleExampleDoc* CMMStyleExampleView::GetDocument()
   { return (CMMStyleExampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MMSTYLEEXAMPLEVIEW_H__2B4A9A0C_0017_40BA_9788_802E09CE9F1D__INCLUDED_)
