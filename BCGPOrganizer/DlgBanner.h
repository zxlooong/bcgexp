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
#if !defined(AFX_DLGBANNER_H__6FCA6B15_C3B0_48D1_93F6_A229F47C1F00__INCLUDED_)
#define AFX_DLGBANNER_H__6FCA6B15_C3B0_48D1_93F6_A229F47C1F00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBanner.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBanner window

class CDlgBanner : public CBCGPStatic
{
// Construction
public:
	CDlgBanner();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBanner)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgBanner();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgBanner)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBANNER_H__6FCA6B15_C3B0_48D1_93F6_A229F47C1F00__INCLUDED_)
