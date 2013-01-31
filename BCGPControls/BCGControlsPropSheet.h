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
#if !defined(AFX_BCGCONTROLSPROPSHEET_H__41041213_B1CD_4358_B140_6638E3699820__INCLUDED_)
#define AFX_BCGCONTROLSPROPSHEET_H__41041213_B1CD_4358_B140_6638E3699820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGControlsPropSheet.h : header file
//

#include "Page1.h"
#include "Page2.h"
#include "Page3.h"
#include "Page4.h"
#include "Page5.h"
#include "Page6.h"
#include "Page7.h"
#include "Page8.h"

/////////////////////////////////////////////////////////////////////////////
// BCGControlsPropSheet

class BCGControlsPropSheet : public CBCGPPropertySheet
{
	DECLARE_DYNAMIC(BCGControlsPropSheet)

// Construction
public:
	BCGControlsPropSheet(CWnd* pParentWnd = NULL);

// Attributes
public:
	CPage1	m_Page1;
	CPage2	m_Page2;
	CPage3	m_Page3;
	CPage4	m_Page4;
	CPage5	m_Page5;
	CPage6  m_Page6;
	CPage7  m_Page7;
	CPage8  m_Page8;

	HICON	m_hIcon;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BCGControlsPropSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~BCGControlsPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(BCGControlsPropSheet)
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGCONTROLSPROPSHEET_H__41041213_B1CD_4358_B140_6638E3699820__INCLUDED_)
