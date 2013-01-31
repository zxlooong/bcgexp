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
#if !defined(AFX_BCGPMSMLinksBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_)
#define AFX_BCGPMSMLinksBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPMSMLinksBar.h : header file
//

#include "BCGPMSMToolBar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMLinksBar window

class CBCGPMSMLinksBar : public CBCGPMSMToolBar
{
	DECLARE_DYNCREATE(CBCGPMSMLinksBar)
// Construction
public:
	CBCGPMSMLinksBar ();

	virtual ~CBCGPMSMLinksBar ();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSMLinksBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual int GetRowHeight () const
				{
					return 1;
				}

	void SetCurrentCommand (UINT nCommand)
		 {
			m_CurrentCommand = nCommand;
		 }

	UINT GetCurrentCommand () const
		 {
			return m_CurrentCommand;
		 }

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMSMLinksBar)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	UINT m_CurrentCommand;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMLinksBAR_H__69C5AD65_461D_41F0_8419_D27C5CFAF337__INCLUDED_)
