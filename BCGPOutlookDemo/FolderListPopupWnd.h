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
#if !defined(AFX_FOLDERLISTPOPUPWND_H__A0EAE6D5_C7A4_11D4_95C8_00A0C9289F1B__INCLUDED_)
#define AFX_FOLDERLISTPOPUPWND_H__A0EAE6D5_C7A4_11D4_95C8_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FolderListPopupWnd.h : header file
//

#include "FoldersTree.h"

class CWorkspaceObj;

/////////////////////////////////////////////////////////////////////////////
// CFolderListPopupWnd window

class CFolderListPopupWnd : public CWnd
{
// Construction
public:
	CFolderListPopupWnd(const CObList& lstWorkspaces, CImageList& images,
						CWorkspaceObj* pSelWorkSpace);

// Attributes
protected:
	static CString	m_strClassName;
	CFoldersTree	m_wndFolders;
	CWorkspaceObj*	m_pSelWorkSpace;

	CBCGPButton		m_btnPin;

	CRect			m_rectCaption;
	CString			m_strCaption;

	BOOL			m_bNotify;

// Operations
public:
	void CloseMe (BOOL bKeep = FALSE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderListPopupWnd)
	public:
	virtual BOOL Create(const RECT& rect);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFolderListPopupWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFolderListPopupWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCancelMode();
	afx_msg void OnNcDestroy();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
#if _MSC_VER >= 1300
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
#else
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
#endif
	afx_msg void OnSelectTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeepVisible();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERLISTPOPUPWND_H__A0EAE6D5_C7A4_11D4_95C8_00A0C9289F1B__INCLUDED_)
