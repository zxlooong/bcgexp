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
#if !defined(AFX_TASKPANE_H__7744B2C4_AF42_4747_A5F9_531A4CF8DC2F__INCLUDED_)
#define AFX_TASKPANE_H__7744B2C4_AF42_4747_A5F9_531A4CF8DC2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaskPane.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTaskPane window

class CTaskPane : public CBCGPTasksPane
{
// Construction
public:
	CTaskPane();

// Attributes
protected:
	int	m_nDocumentsGroup;
	CFont		m_Font;
	CTreeCtrl	m_wndTree;
	CEdit		m_wndEdit;

// Operations
public:
	void UpdateMRUFilesList ();
	void UpdateIcons ();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskPane)
	//}}AFX_VIRTUAL

protected:
	BOOL CreateTreeWindow();

// Implementation
public:
	virtual ~CTaskPane();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTaskPane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKPANE_H__7744B2C4_AF42_4747_A5F9_531A4CF8DC2F__INCLUDED_)
