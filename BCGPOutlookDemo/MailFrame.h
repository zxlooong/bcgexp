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
#if !defined(AFX_MAILFRAME_H__0DDCF6EE_6114_4123_9B0F_BF27E2B6F7BE__INCLUDED_)
#define AFX_MAILFRAME_H__0DDCF6EE_6114_4123_9B0F_BF27E2B6F7BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailFrame.h : header file
//

#include "MailBar.h"

/////////////////////////////////////////////////////////////////////////////
// CMailFrame frame

class CMailFrame : public CBCGPFrameWnd
{
	DECLARE_DYNCREATE(CMailFrame)

public:
	CMailFrame(); 
	virtual ~CMailFrame();

// Attributes
protected:  // control bar embedded members
	CBCGPMenuBar	m_wndMenuBar;
	CBCGPToolBar	m_wndToolBar;
	CMailBar		m_wndMailBar;
	CBCGPStatusBar	m_wndStatusBar;

	CWnd*			m_pMainWnd;

	static CObList	m_lstMailFrames;

// Operations
public:
	static void OnChangeLook ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailFrame)
	public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMailFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnViewCustomize();
	afx_msg void OnClose();
	afx_msg void OnMailClose();
	afx_msg void OnEnable( BOOL bEnable );
	//}}AFX_MSG
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILFRAME_H__0DDCF6EE_6114_4123_9B0F_BF27E2B6F7BE__INCLUDED_)
