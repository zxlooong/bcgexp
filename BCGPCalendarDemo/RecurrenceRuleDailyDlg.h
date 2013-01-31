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
#if !defined(AFX_RECURRENCERULEDAILYDLG_H__ECE54683_3164_441D_BF65_97F64CD9259E__INCLUDED_)
#define AFX_RECURRENCERULEDAILYDLG_H__ECE54683_3164_441D_BF65_97F64CD9259E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecurrenceRuleDailyDlg.h : header file
//

#include "RecurrenceRuleDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleDailyDlg dialog

class CRecurrenceRuleDailyDlg : public CRecurrenceRuleDlg
{
// Construction
public:
	CRecurrenceRuleDailyDlg();   // standard constructor

	virtual void SetRule (CBCGPRecurrenceBaseRule* pRule);

	virtual BOOL UpdateRule (const COleDateTime& dtStart);

// Dialog Data
	//{{AFX_DATA(CRecurrenceRuleDailyDlg)
	enum { IDD = IDD_RECURRENCE_RULE_DAILY };
	DWORD	m_Span;
	CBCGPButton m_btnTypeSpan;
	CBCGPButton m_btnTypeWeekDays;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecurrenceRuleDailyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:

	virtual UINT GetID () const
	{
		return IDD;
	}

	// Generated message map functions
	//{{AFX_MSG(CRecurrenceRuleDailyDlg)
	afx_msg void OnChangeSpan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECURRENCERULEDAILYDLG_H__ECE54683_3164_441D_BF65_97F64CD9259E__INCLUDED_)
