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
#if !defined(AFX_PLANNERTOOLTIPCTRL_H__17390368_90CE_4ECB_9815_0DE1D194444D__INCLUDED_)
#define AFX_PLANNERTOOLTIPCTRL_H__17390368_90CE_4ECB_9815_0DE1D194444D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlannerTooltipCtrl.h : header file
//

class CBCGPAppointmentDemo;

/////////////////////////////////////////////////////////////////////////////
// CPlannerTooltipCtrl window

class CPlannerTooltipCtrl : public CBCGPToolTipCtrl
{
	DECLARE_DYNCREATE(CPlannerTooltipCtrl)

// Construction
public:
	CPlannerTooltipCtrl();

// Attributes
protected:
	CBCGPPlannerManagerCtrl*	m_pWndPlanner;
	CBCGPAppointmentDemo*		m_pHotAppointment;
	HICON						m_hIconMeeting;
	HICON						m_hIconPrivate;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlannerTooltipCtrl)
	//}}AFX_VIRTUAL

	virtual void SetDescription (const CString strDesrciption);
	virtual CSize GetIconSize ();
	virtual BOOL OnDrawIcon (CDC* pDC, CRect rectImage);

// Implementation
public:
	virtual ~CPlannerTooltipCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlannerTooltipCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnShow(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLANNERTOOLTIPCTRL_H__17390368_90CE_4ECB_9815_0DE1D194444D__INCLUDED_)
