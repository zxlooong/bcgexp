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
// RecurrenceRuleDailyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcalendardemo.h"
#include "RecurrenceRuleDailyDlg.h"

#include "BCGPRecurrenceRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleDailyDlg dialog


CRecurrenceRuleDailyDlg::CRecurrenceRuleDailyDlg()
{
	//{{AFX_DATA_INIT(CRecurrenceRuleDailyDlg)
	m_Span = 1;
	//}}AFX_DATA_INIT
}


void CRecurrenceRuleDailyDlg::DoDataExchange(CDataExchange* pDX)
{
	CRecurrenceRuleDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecurrenceRuleDailyDlg)
	DDX_Text(pDX, IDC_RD_SPAN, m_Span);
	DDX_Control(pDX, IDC_RD_TYPE_SPAN, m_btnTypeSpan);
	DDX_Control(pDX, IDC_RD_TYPE_WEEKDAYS, m_btnTypeWeekDays);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecurrenceRuleDailyDlg, CRecurrenceRuleDlg)
	//{{AFX_MSG_MAP(CRecurrenceRuleDailyDlg)
	ON_EN_CHANGE(IDC_RD_SPAN, OnChangeSpan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleDailyDlg message handlers

void CRecurrenceRuleDailyDlg::SetRule (CBCGPRecurrenceBaseRule* pRule)
{
	CRecurrenceRuleDlg::SetRule (pRule);

	m_Span = ((CBCGPRecurrenceRuleDaily*)(pRule))->GetSpan ();
	
	if (((CBCGPRecurrenceRuleDaily*)(pRule))->GetType () ==
		CBCGPRecurrenceRuleDaily::BCGP_REC_RULE_DAILY_TYPE_WEEKDAYS)
	{
		m_btnTypeWeekDays.SetCheck (BST_CHECKED);
	}
	else
	{
		m_btnTypeSpan.SetCheck (BST_CHECKED);
	}

	UpdateData (FALSE);
}


BOOL CRecurrenceRuleDailyDlg::UpdateRule (const COleDateTime& /*dtStart*/)
{
	BOOL bRes = UpdateData ();

	if (bRes)
	{
		if (m_Span < 1 || m_Span > 1000)
		{
			return FALSE;
		}

		CBCGPRecurrenceRuleDaily* pRule = (CBCGPRecurrenceRuleDaily*)GetRule ();

		pRule->SetSpan (m_Span);
		pRule->SetType (
			m_btnTypeWeekDays.GetCheck () == BST_CHECKED
			? CBCGPRecurrenceRuleDaily::BCGP_REC_RULE_DAILY_TYPE_WEEKDAYS
			: CBCGPRecurrenceRuleDaily::BCGP_REC_RULE_DAILY_TYPE_SPAN);
	}

	return bRes;
}

void CRecurrenceRuleDailyDlg::OnChangeSpan() 
{
	if (m_btnTypeSpan.GetCheck () != BST_CHECKED)
	{
		m_btnTypeSpan.SetCheck (BST_CHECKED);
		m_btnTypeWeekDays.SetCheck (BST_UNCHECKED);
	}
}
