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
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__C67CBA98_5A1B_4126_9210_E00943F6E4DE__INCLUDED_)
#define AFX_MAINFRM_H__C67CBA98_5A1B_4126_9210_E00943F6E4DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CFrameWnd CBCGPFrameWnd

#include "PropertyBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPMenuBar		m_wndMenuBar;
	CBCGPStatusBar		m_wndStatusBar;
	CBCGPToolBar		m_wndToolBar;
	CBCGPToolBar		m_wndGanttToolBar;

	//CCalendarBar	m_wndCalendarBar;

	UINT	m_nAppLook;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg void OnViewGanttBar();
	afx_msg void OnUpdateViewGanttBar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);

	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C67CBA98_5A1B_4126_9210_E00943F6E4DE__INCLUDED_)
