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
#if !defined(AFX_GANTTBAR_H__E74449DF_CA8F_4053_95FD_96E55BE59E56__INCLUDED_)
#define AFX_GANTTBAR_H__E74449DF_CA8F_4053_95FD_96E55BE59E56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GanttBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGanttBar window

class CGanttBar : public CBCGPCalendar
{
// Construction
public:
	CGanttBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGanttBar)
	virtual BOOL Create(CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

	virtual BOOL OnShowControlBarMenu (CPoint /*point*/)	{	return TRUE;	}

// Implementation
public:
	virtual ~CGanttBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGanttBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GANTTBAR_H__E74449DF_CA8F_4053_95FD_96E55BE59E56__INCLUDED_)
