//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2007 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// WorkspaceBar.h : interface of the CWorkspaceBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKSPACEBAR_H__93A2C1F8_0E01_4973_B559_FF1EE49B584B__INCLUDED_)
#define AFX_WORKSPACEBAR_H__93A2C1F8_0E01_4973_B559_FF1EE49B584B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSkinsList window

class CSkinsList : public CListCtrl
{
// Construction
public:
	CSkinsList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinsList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinsList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinsList)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CWorkspaceBar : public CBCGPDockingControlBar
{
public:
	CWorkspaceBar();

// Attributes
protected:
	CBCGPTabWnd	m_wndTabs;
	CSkinsList	m_wndSkinsList;
	CStatic		m_wndDummy;
	CImageList	m_Images;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkspaceBar();

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnRedrawNCArea(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEBAR_H__93A2C1F8_0E01_4973_B559_FF1EE49B584B__INCLUDED_)
