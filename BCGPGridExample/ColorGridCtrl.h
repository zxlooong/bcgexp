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
#if !defined(AFX_COLORGRIDCTRL_H__158297E8_B1EB_4F44_AA8B_7DB752851B6E__INCLUDED_)
#define AFX_COLORGRIDCTRL_H__158297E8_B1EB_4F44_AA8B_7DB752851B6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorGridCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorGridCtrl window

#define COLOR_THEMES	4

class CColorGridCtrl : public CBCGPGridCtrl
{
// Construction
public:
	CColorGridCtrl();

// Attributes
protected:
	BCGP_GRID_COLOR_DATA	m_Themes [COLOR_THEMES];

// Operations
public:
	void UpdateColorTheme ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorGridCtrl)
	//}}AFX_VIRTUAL

	virtual int CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn);
	virtual CString GetGroupName (int nGroupCol, CBCGPGridItem* pItem);

// Implementation
public:
	virtual ~CColorGridCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorGridCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnDrawGridScrollBar(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORGRIDCTRL_H__158297E8_B1EB_4F44_AA8B_7DB752851B6E__INCLUDED_)
