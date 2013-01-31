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
#if !defined(AFX_TASKSBAR_H__E53E1BD7_AB29_4DBB_8615_17E2A0AED2AE__INCLUDED_)
#define AFX_TASKSBAR_H__E53E1BD7_AB29_4DBB_8615_17E2A0AED2AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TasksBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTasksBar window

class CTasksBar : public CBCGPTasksPane
{
// Construction
public:
	CTasksBar();

// Attributes
protected:
	CFont	m_Font;

	CBCGPEdit	m_wndEdit;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTasksBar)
	virtual BOOL Create(CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

	virtual BOOL OnShowControlBarMenu (CPoint /*point*/)	{	return TRUE;	}

// Implementation
public:
	virtual ~CTasksBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTasksBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKSBAR_H__E53E1BD7_AB29_4DBB_8615_17E2A0AED2AE__INCLUDED_)
