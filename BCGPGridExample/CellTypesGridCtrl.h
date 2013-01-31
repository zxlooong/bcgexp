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
#if !defined(AFX_CELLTYPESGRIDCTRL_H__DE20F851_94F5_4F2E_A302_97581036E602__INCLUDED_)
#define AFX_CELLTYPESGRIDCTRL_H__DE20F851_94F5_4F2E_A302_97581036E602__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CellTypesGridCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCellTypesGridCtrl window

class CProgressItem;

class CCellTypesGridCtrl : public CBCGPGridCtrl
{
// Construction
public:
	CCellTypesGridCtrl();

// Attributes
public:

// Operations
public:
	CBCGPGridRow* CreateNewRow ();
	void AddEmptyRow ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCellTypesGridCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCellTypesGridCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCellTypesGridCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	afx_msg void OnAnimateProgress();
	DECLARE_MESSAGE_MAP()

	virtual void SetRowHeight ()
	{
		CBCGPGridCtrl::SetRowHeight ();
		m_nRowHeight += 2;
	}

	CProgressItem*	m_pProgressItem;
	BOOL			m_bProgressIsOn;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELLTYPESGRIDCTRL_H__DE20F851_94F5_4F2E_A302_97581036E602__INCLUDED_)
