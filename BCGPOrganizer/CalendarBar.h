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
// CalendarBar.h : interface of the CCalendarBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALENDARBAR_H__27BD293B_AB9D_4F66_AEAF_6DD7F7807E05__INCLUDED_)
#define AFX_CALENDARBAR_H__27BD293B_AB9D_4F66_AEAF_6DD7F7807E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalendarBar : public CBCGPCalendar
{
	friend class CMainFrame;

public:
	CCalendarBar();

// Operations
public:
	void UpdateCalendar ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarBar)
	virtual BOOL Create(CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCalendarBar();

// Generated message map functions
protected:
	//{{AFX_MSG(CCalendarBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARBAR_H__27BD293B_AB9D_4F66_AEAF_6DD7F7807E05__INCLUDED_)
