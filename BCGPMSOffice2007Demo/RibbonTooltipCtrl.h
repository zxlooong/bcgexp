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
#if !defined(AFX_RIBBONTOOLTIPCTRL_H__93FA8008_02A7_4511_BFB5_EF3DBB61F2C1__INCLUDED_)
#define AFX_RIBBONTOOLTIPCTRL_H__93FA8008_02A7_4511_BFB5_EF3DBB61F2C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RibbonTooltipCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRibbonTooltipCtrl window

class CRibbonTooltipCtrl : public CBCGPToolTipCtrl
{
	DECLARE_DYNCREATE(CRibbonTooltipCtrl)

// Construction
public:
	CRibbonTooltipCtrl();

// Attributes
protected:
	CBCGPRibbonPanelMenuBar*	m_pParentMenuBar;
	CBCGPRibbonBar*				m_pParentRibbon;
	UINT						m_nID;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonTooltipCtrl)
	//}}AFX_VIRTUAL

	virtual CSize GetIconSize ();
	virtual BOOL OnDrawIcon (CDC* pDC, CRect rectImage);

// Implementation
public:
	virtual ~CRibbonTooltipCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRibbonTooltipCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnShow(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONTOOLTIPCTRL_H__93FA8008_02A7_4511_BFB5_EF3DBB61F2C1__INCLUDED_)
