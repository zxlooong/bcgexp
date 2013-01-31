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
#if !defined(AFX_OUTPUTBAR_H__708257AC_7B83_11D3_A74B_0090274409AC__INCLUDED_)
#define AFX_OUTPUTBAR_H__708257AC_7B83_11D3_A74B_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
class COutputBar : public CBCGPDockingControlBar  
{
// Construction
public:
	COutputBar();

// Attributes
protected:
	CString	m_strText;

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputBar();

	void UpdateInfo (int nType);

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputBar)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTBAR_H__708257AC_7B83_11D3_A74B_0090274409AC__INCLUDED_)
