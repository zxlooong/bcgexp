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
#if !defined(AFX_FOLDERLISTBAR_H__4E2AD667_8C86_4004_83C1_5F1F045A0A03__INCLUDED_)
#define AFX_FOLDERLISTBAR_H__4E2AD667_8C86_4004_83C1_5F1F045A0A03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FolderListBar.h : header file
//

#include "FoldersTree.h"

class CWorkspaceObj;

/////////////////////////////////////////////////////////////////////////////
// CFolderListBar window

class CFolderListBar : public CBCGPDockingControlBar
{
// Construction
public:
	CFolderListBar(const CObList& lstWorkspaces, CImageList& images);

// Attributes
protected:
	CFoldersTree	m_wndFolders;
	BOOL			m_bNotifyFrame;

// Operations
public:
	BOOL SelectWorkspace (CWorkspaceObj* pWS);
	virtual BOOL CanAcceptBar (const CBCGPBaseControlBar* /*pBar*/) const
	{
		return FALSE;
	}
	virtual BOOL DoesAllowDynInsertBefore () const
	{
		return FALSE;
	}
// Overrides 
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderListBar)
	//}}AFX_VIRTUAL

protected:
	virtual void OnEraseWorkArea (CDC* pDC, CRect rectWorkArea);

// Implementation
public:
	virtual ~CFolderListBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFolderListBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg void OnSelectTree(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERLISTBAR_H__4E2AD667_8C86_4004_83C1_5F1F045A0A03__INCLUDED_)
