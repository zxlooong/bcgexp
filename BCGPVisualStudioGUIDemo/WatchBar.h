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
#if !defined(AFX_WATCHBAR_H__31A1AF6B_7EB0_11D3_95C6_00A0C9289F1B__INCLUDED_)
#define AFX_WATCHBAR_H__31A1AF6B_7EB0_11D3_95C6_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WatchBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWatchBar window

class CWatchBar : public CBCGPDockingControlBar
{
// Construction
public:
	CWatchBar();

// Attributes
protected:
	CFont			m_Font;
	CBCGPListCtrl	m_wndWatch;

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatchBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWatchBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWatchBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WATCHBAR_H__31A1AF6B_7EB0_11D3_95C6_00A0C9289F1B__INCLUDED_)
