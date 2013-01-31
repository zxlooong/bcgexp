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
#if !defined(AFX_FOLDERSTREE_H__A0EAE6DE_C7A4_11D4_95C8_00A0C9289F1B__INCLUDED_)
#define AFX_FOLDERSTREE_H__A0EAE6DE_C7A4_11D4_95C8_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FoldersTree.h : header file
//

class CWorkspaceObj;

/////////////////////////////////////////////////////////////////////////////
// CFoldersTree window

class CFoldersTree : public CTreeCtrl
{
// Construction
public:
	CFoldersTree(const CObList& lstWorkspaces, CImageList& images);

// Attributes
protected:
	CTreeCtrl		m_wndFolders;
	const CObList&	m_lstWorkspaces;
	CImageList&		m_images;

	CMap<CWorkspaceObj*, CWorkspaceObj*, HTREEITEM, HTREEITEM>	m_Items;

// Operations
public:
	BOOL SelectWorkspace (CWorkspaceObj* pWS);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFoldersTree)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFoldersTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFoldersTree)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERSTREE_H__A0EAE6DE_C7A4_11D4_95C8_00A0C9289F1B__INCLUDED_)
