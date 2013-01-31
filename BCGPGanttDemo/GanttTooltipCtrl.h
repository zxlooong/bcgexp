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
#if !defined(AFX_GANTTTOOLTIPCTRL_H__17390368_90CE_4ECB_9815_0DE1D194444D__INCLUDED_)
#define AFX_GANTTTOOLTIPCTRL_H__17390368_90CE_4ECB_9815_0DE1D194444D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GanttTooltipCtrl.h : header file
//

class CBCGPAppointmentDemo;

/////////////////////////////////////////////////////////////////////////////
// CGanttTooltipCtrl window

class CGanttTooltipCtrl : public CBCGPToolTipCtrl
{
	DECLARE_DYNCREATE(CGanttTooltipCtrl)

// Construction
public:
	CGanttTooltipCtrl();

// Attributes
protected:
	CBCGPGanttChart*			m_pWndGantt;
	CBCGPGanttItem*				m_pHotItem;
	HICON						m_hIconComplete;
	HICON						m_hIconMilestone;
	HICON						m_hIconMilestoneC;

	CBCGPGanttItem*				GetHotItem ();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGanttTooltipCtrl)
	//}}AFX_VIRTUAL

	virtual CSize GetIconSize ();
	virtual CString GetLabel ();

	virtual BOOL OnDrawIcon (CDC* pDC, CRect rectImage);

	virtual void SetDescription (const CString strDesrciption);

// Implementation
public:
	virtual ~CGanttTooltipCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGanttTooltipCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnShow(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GANTTTOOLTIPCTRL_H__17390368_90CE_4ECB_9815_0DE1D194444D__INCLUDED_)
