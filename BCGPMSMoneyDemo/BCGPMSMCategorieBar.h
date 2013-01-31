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
#if !defined(AFX_BCGPMSMCategorieBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_)
#define AFX_BCGPMSMCategorieBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPMSMCategorieBar.h : header file
//

#include "BCGPMSMToolBar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCategorieBar window

class CBCGPMSMCategorieBar : public CBCGPMSMToolBar
{
	DECLARE_DYNCREATE(CBCGPMSMCategorieBar)
// Construction
public:
	CBCGPMSMCategorieBar ();

	virtual ~CBCGPMSMCategorieBar ();

// Attributes
public:

	virtual BOOL RestoreOriginalstate ();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSMCategorieBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual int GetRowHeight () const
				{
					return 1;
				}

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMSMCategorieBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMCategorieBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_)
