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
#if !defined(AFX_OUTLOOKBAR_H__E74449DF_CA8F_4053_95FD_96E55BE59E56__INCLUDED_)
#define AFX_OUTLOOKBAR_H__E74449DF_CA8F_4053_95FD_96E55BE59E56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShortcutsBar.h : header file
//

#include "BCGPOutlookBar.h"
#include "ShortcutsBar.h"
#include "MailBar.h"
#include "CalendarBar.h"
#include "TasksBar.h"
#include "MacrosBar.h"
#include "GanttBar.h"

/////////////////////////////////////////////////////////////////////////////
// COutlookBar view

class COutlookWnd: public CBCGPOutlookWnd
{
	DECLARE_DYNCREATE(COutlookWnd)

// Construction
public:
	COutlookWnd()
	{
	}
	virtual ~COutlookWnd()
	{
	}

public:
	BOOL SetToolbarImageList (HIMAGELIST hImageList);

protected:
	DECLARE_MESSAGE_MAP()
};

class COutlookBar : public CBCGPOutlookBar
{
	friend class CMainFrame;

protected:
	COutlookBar();           // protected constructor used by dynamic creation
	DECLARE_DYNAMIC(COutlookBar)

// Attributes
public:
	int GetActiveShortcut ()
	{
		return GetUnderlinedWindow ()->GetActiveTab ();
	}

	int SetActiveShortcut (int index)
	{
		return GetUnderlinedWindow ()->SetActiveTab (index);
	}


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookBar)
	public:
	virtual BOOL Create(LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle, DWORD dwBCGStyle = CBRS_BCGP_RESIZE, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COutlookBar();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COutlookBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnCalendarSelChanged(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CShortcutsBar			m_wndShortcutsBar;
	CMailBar				m_wndMailBar;
	CCalendarBar			m_wndCalendarBar;
	CTasksBar				m_wndTasksBar;
	CMacrosBar				m_wndMacrosBar;
	CGanttBar				m_wndGanttBar;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKBAR_H__E74449DF_CA8F_4053_95FD_96E55BE59E56__INCLUDED_)
