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
// RecurrenceRuleWeeklyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "RecurrenceRuleWeeklyDlg.h"

#include "BCGPRecurrenceRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleWeeklyDlg dialog


CRecurrenceRuleWeeklyDlg::CRecurrenceRuleWeeklyDlg()
{
	//{{AFX_DATA_INIT(CRecurrenceRuleWeeklyDlg)
	m_Span = 1;
	m_Check1 = FALSE;
	m_Check2 = FALSE;
	m_Check3 = FALSE;
	m_Check4 = FALSE;
	m_Check5 = FALSE;
	m_Check6 = FALSE;
	m_Check7 = FALSE;
	//}}AFX_DATA_INIT
}


void CRecurrenceRuleWeeklyDlg::DoDataExchange(CDataExchange* pDX)
{
	CRecurrenceRuleDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecurrenceRuleWeeklyDlg)
	DDX_Text(pDX, IDC_RW_SPAN, m_Span);
	DDX_Check(pDX, IDC_RW_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_RW_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_RW_CHECK3, m_Check3);
	DDX_Check(pDX, IDC_RW_CHECK4, m_Check4);
	DDX_Check(pDX, IDC_RW_CHECK5, m_Check5);
	DDX_Check(pDX, IDC_RW_CHECK6, m_Check6);
	DDX_Check(pDX, IDC_RW_CHECK7, m_Check7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecurrenceRuleWeeklyDlg, CRecurrenceRuleDlg)
	//{{AFX_MSG_MAP(CRecurrenceRuleWeeklyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleWeeklyDlg message handlers

void CRecurrenceRuleWeeklyDlg::SetRule (CBCGPRecurrenceBaseRule* pRule)
{
	CRecurrenceRuleDlg::SetRule (pRule);

	m_Span = ((CBCGPRecurrenceRuleWeekly*)(pRule))->GetSpan ();
	
	DWORD dwDays = ((CBCGPRecurrenceRuleWeekly*)(pRule))->GetDays ();

	m_Check1 = (dwDays & CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_1) != 0;
	m_Check2 = (dwDays & CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_2) != 0;
	m_Check3 = (dwDays & CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_3) != 0;
	m_Check4 = (dwDays & CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_4) != 0;
	m_Check5 = (dwDays & CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_5) != 0;
	m_Check6 = (dwDays & CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_6) != 0;
	m_Check7 = (dwDays & CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_7) != 0;

	UpdateData (FALSE);
}


BOOL CRecurrenceRuleWeeklyDlg::UpdateRule (const COleDateTime& /*dtStart*/)
{
	BOOL bRes = UpdateData ();

	if (bRes)
	{
		if (m_Span < 1 || m_Span > 1000)
		{
			return FALSE;
		}

		CBCGPRecurrenceRuleWeekly* pRule = (CBCGPRecurrenceRuleWeekly*)GetRule ();

		pRule->SetSpan (m_Span);

		DWORD dwDays = 0;

		if (m_Check1)
		{
			dwDays |= CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_1;
		}
		if (m_Check2)
		{
			dwDays |= CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_2;
		}
		if (m_Check3)
		{
			dwDays |= CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_3;
		}
		if (m_Check4)
		{
			dwDays |= CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_4;
		}
		if (m_Check5)
		{
			dwDays |= CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_5;
		}
		if (m_Check6)
		{
			dwDays |= CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_6;
		}
		if (m_Check7)
		{
			dwDays |= CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_7;
		}

		bRes = dwDays != 0;
		
		if (bRes)
		{
			pRule->SetDays (dwDays);
		}
	}

	return bRes;
}

BOOL CRecurrenceRuleWeeklyDlg::OnInitDialog() 
{
	CRecurrenceRuleDlg::OnInitDialog();

	const UINT nID[7] = {IDC_RW_CHECK1, IDC_RW_CHECK2, IDC_RW_CHECK3, IDC_RW_CHECK4, 
					IDC_RW_CHECK5, IDC_RW_CHECK6, IDC_RW_CHECK7};

	for (int i = 0; i < 7; i++)
	{
		CWnd* pWnd = GetDlgItem (nID[i]);

		if (pWnd != NULL)
		{
			pWnd->SetWindowText (CBCGPPlannerManagerCtrl::GetSystemWeekDayName (i));
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
