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
#if !defined(AFX_BCGPMSMMENUBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_)
#define AFX_BCGPMSMMENUBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPMSMMenuBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMMenuBar window

class CBCGPMSMMenuBar : public CBCGPMenuBar
{
	DECLARE_DYNCREATE(CBCGPMSMMenuBar)

// Construction
public:
	CBCGPMSMMenuBar();

	virtual ~CBCGPMSMMenuBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSMMenuBar)
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMSMMenuBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMMENUBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_)
