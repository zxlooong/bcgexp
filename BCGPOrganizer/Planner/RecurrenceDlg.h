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
#if !defined(AFX_RECURRENCEDLG_H__291BCE7E_24A5_43F0_988F_688597792316__INCLUDED_)
#define AFX_RECURRENCEDLG_H__291BCE7E_24A5_43F0_988F_688597792316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecurrenceDlg.h : header file
//

#include "BCGPRecurrenceRule.h"
#include "RecurrenceRuleDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceDlg dialog

class CBCGPDateTimeCtrl2 : public CBCGPDateTimeCtrl
{
public:
	DATE GetDate () const
	{
		return m_Date;
	}
};

class CRecurrenceDlg : public CBCGPDialog
{
// Construction
public:
	CRecurrenceDlg(const CBCGPRecurrenceBaseRule* pRule, BOOL bHasRule,
				   BOOL bEcp, CWnd* pParent = NULL);   // standard constructor
	virtual ~CRecurrenceDlg();

// Dialog Data
	//{{AFX_DATA(CRecurrenceDlg)
	enum { IDD = IDD_APP_RECURRENCE };
	CBCGPDateTimeCtrl2	m_TimeStart;
	CBCGPDateTimeCtrl2	m_TimeEnd;
	CBCGPDateTimeCtrl	m_DateStart;
	CBCGPDateTimeCtrl	m_LimitDate;
	CBCGPDurationCtrl	m_Duration;
	DWORD				m_LimitCount;
	CBCGPButton			m_btnRuleDaily;
	CBCGPButton			m_btnRuleWeekly;
	CBCGPButton			m_btnRuleMonthly;
	CBCGPButton			m_btnRuleYearly;
	CBCGPButton			m_btnRemove;
	CBCGPButton			m_btnLimitNone;
	CBCGPButton			m_btnLimitCount;
	CBCGPButton			m_btnLimitDate;
	//}}AFX_DATA

	const CBCGPRecurrenceBaseRule* GetRule () const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecurrenceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void ChangeRule (DWORD index);

	// Generated message map functions
	//{{AFX_MSG(CRecurrenceDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRemove();
	afx_msg void OnRuleDaily();
	afx_msg void OnRuleWeekly();
	afx_msg void OnRuleMonthly();
	afx_msg void OnRuleYearly();
	afx_msg void OnLimitNone();
	afx_msg void OnLimitCount();
	afx_msg void OnLimitDate();
	afx_msg void OnTimeChangedS();
	afx_msg void OnTimeChangedE();
	afx_msg void OnDurationChanged();
	afx_msg void OnChangeCount();
	afx_msg void OnDateEndChanged();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CArray<CBCGPRecurrenceBaseRule*, CBCGPRecurrenceBaseRule*> m_Rules;
	CBCGPRecurrenceRuleRegistrator::XBCGPRecurrenceRuleIDArray m_RulesID;
	DWORD m_ID;

	CArray<CRecurrenceRuleDlg*, CRecurrenceRuleDlg*> m_RulesDlg;
	CRecurrenceRuleDlg* m_Dialog;

	BOOL	m_bHasRule;
	BOOL	m_bEcp;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECURRENCEDLG_H__291BCE7E_24A5_43F0_988F_688597792316__INCLUDED_)
