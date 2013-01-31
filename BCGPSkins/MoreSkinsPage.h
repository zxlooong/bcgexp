//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2007 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
#if !defined(AFX_MORESKINSPAGE_H__A1CEEA22_C4EA_460C_A115_38C5AAE8D472__INCLUDED_)
#define AFX_MORESKINSPAGE_H__A1CEEA22_C4EA_460C_A115_38C5AAE8D472__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoreSkinsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoreSkinsPage window

class CMoreSkinsPage : public CWnd
{
// Construction
public:
	CMoreSkinsPage();

// Attributes
public:
	CBCGPButton	m_btnMoreSkins;
	CSize		m_sizeButton;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoreSkinsPage)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMoreSkinsPage();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMoreSkinsPage)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MORESKINSPAGE_H__A1CEEA22_C4EA_460C_A115_38C5AAE8D472__INCLUDED_)
