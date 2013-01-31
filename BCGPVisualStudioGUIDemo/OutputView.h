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
// OutputView.h: interface for the COutputViewBar class.
//


/////////////////////////////////////////////////////////////////////////////
// COutputList window

class COutputList : public CListBox
{
// Construction
public:
	COutputList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputList)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnOutputGotoError();
	afx_msg void OnViewOutput();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#if !defined(AFX_OUTPUTVIEW_H__F9C28949_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_)
#define AFX_OUTPUTVIEW_H__F9C28949_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COutputViewBar : public CBCGPDockingControlBar  
{
// Construction
public:
	COutputViewBar();

// Attributes
protected:

	CFont		m_Font;
	COutputList	m_wndOutput;

protected:
	void FillDebugWindow ();
	void FillBuildWindow ();
	void AdjusrHorzScroll (CListBox& wndListBox);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputViewBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_OUTPUTVIEW_H__F9C28949_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_)
