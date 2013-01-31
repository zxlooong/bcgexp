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
#if !defined(AFX_RECURRENCERULEWEEKLYDLG_H__A33A1401_5FE3_44D2_9889_CF5CD62E943C__INCLUDED_)
#define AFX_RECURRENCERULEWEEKLYDLG_H__A33A1401_5FE3_44D2_9889_CF5CD62E943C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecurrenceRuleWeeklyDlg.h : header file
//

#include "RecurrenceRuleDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleWeeklyDlg dialog

class CRecurrenceRuleWeeklyDlg : public CRecurrenceRuleDlg
{
// Construction
public:
	CRecurrenceRuleWeeklyDlg();   // standard constructor

	virtual void SetRule (CBCGPRecurrenceBaseRule* pRule);

	virtual BOOL UpdateRule (const COleDateTime& dtStart);

// Dialog Data
	//{{AFX_DATA(CRecurrenceRuleWeeklyDlg)
	enum { IDD = IDD_RECURRENCE_RULE_WEEKLY };
	DWORD	m_Span;
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	BOOL	m_Check4;
	BOOL	m_Check5;
	BOOL	m_Check6;
	BOOL	m_Check7;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecurrenceRuleWeeklyDlg)
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
	//{{AFX_MSG(CRecurrenceRuleWeeklyDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECURRENCERULEWEEKLYDLG_H__A33A1401_5FE3_44D2_9889_CF5CD62E943C__INCLUDED_)
