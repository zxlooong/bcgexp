//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPMediaPlayerView.h : interface of the CBCGPMediaPlayerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPMEDIAPLAYERVIEW_H__DE07C091_EFB0_4E77_8BF5_E7E27964E8EC__INCLUDED_)
#define AFX_BCGPMEDIAPLAYERVIEW_H__DE07C091_EFB0_4E77_8BF5_E7E27964E8EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBCGPMediaPlayerView : public CView
{
protected: // create from serialization only
	CBCGPMediaPlayerView();
	DECLARE_DYNCREATE(CBCGPMediaPlayerView)

// Attributes
public:
	CBCGPMediaPlayerDoc* GetDocument();
	CMCIControl& GetMCIControl ();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMediaPlayerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPMediaPlayerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMediaPlayerView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNcPaint ();
	//}}AFX_MSG
	afx_msg LRESULT OnMCIMode (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMCISize (WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void PrintText (CDC* pDC, const CString& str, int x, int y, CFont& font);

private:
	UINT_PTR	m_Timer;
	CFont		m_fntSong;
	CFont		m_fntProgress;
	CRect		m_rectProgress;
	CString		m_strProgress;
};

#ifndef _DEBUG  // debug version in BCGPMediaPlayerView.cpp
inline CBCGPMediaPlayerDoc* CBCGPMediaPlayerView::GetDocument()
   { return (CBCGPMediaPlayerDoc*)m_pDocument; }

inline CMCIControl& CBCGPMediaPlayerView::GetMCIControl()
   { return GetDocument ()->GetMCIControl (); }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMEDIAPLAYERVIEW_H__DE07C091_EFB0_4E77_8BF5_E7E27964E8EC__INCLUDED_)
