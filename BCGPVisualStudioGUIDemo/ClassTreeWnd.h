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
#if !defined(AFX_CLASSTREEWND_H__0517A828_D18F_11D3_A727_009027900694__INCLUDED_)
#define AFX_CLASSTREEWND_H__0517A828_D18F_11D3_A727_009027900694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassTreeWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClassTreeWnd window

class CClassTreeWnd : public CTreeCtrl
{
// Construction
public:
	CClassTreeWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassTreeWnd)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClassTreeWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClassTreeWnd)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSTREEWND_H__0517A828_D18F_11D3_A727_009027900694__INCLUDED_)
