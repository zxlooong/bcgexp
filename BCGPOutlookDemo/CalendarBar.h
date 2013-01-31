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
#if !defined(AFX_CALENDARBAR_H__101F55C6_C155_49A9_A302_79601100D2B7__INCLUDED_)
#define AFX_CALENDARBAR_H__101F55C6_C155_49A9_A302_79601100D2B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalendarBar window

class CCalendarBar : public CWnd
{
// Construction
public:
	CCalendarBar();

// Attributes
public:
	CBCGPCalendar		m_wndCalendars;
	int					m_nMyCalendarsY;
	CImageList			m_Images;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarBar)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID = (UINT)-1);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCalendarBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCalendarBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARBAR_H__101F55C6_C155_49A9_A302_79601100D2B7__INCLUDED_)
