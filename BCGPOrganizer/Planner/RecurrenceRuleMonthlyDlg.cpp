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
// RecurrenceRuleMonthlyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "RecurrenceRuleMonthlyDlg.h"

#include "BCGPRecurrenceRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleMonthlyDlg dialog


CRecurrenceRuleMonthlyDlg::CRecurrenceRuleMonthlyDlg()
{
	//{{AFX_DATA_INIT(CRecurrenceRuleMonthlyDlg)
	m_dwDay = 0;
	m_dwDaySpan = 0;
	m_nDayTypeDay = 0;
	m_nDayTypeWeekDay = 0;
	m_dwDayTypeSpan = 0;
	//}}AFX_DATA_INIT
}


void CRecurrenceRuleMonthlyDlg::DoDataExchange(CDataExchange* pDX)
{
	CRecurrenceRuleDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecurrenceRuleMonthlyDlg)
	DDX_Control(pDX, IDC_RM_DAYTYPE_TYPE, m_cbDayTypeWeekDay);
	DDX_Control (pDX, IDC_RM_DAY, m_btnTypeDay);
	DDX_Control (pDX, IDC_RM_DAYTYPE, m_btnTypeDayType);
	DDX_Text(pDX, IDC_RM_DAY_DAY, m_dwDay);
	DDX_Text(pDX, IDC_RM_DAY_SPAN, m_dwDaySpan);
	DDX_Text(pDX, IDC_RM_DAYTYPE_SPAN, m_dwDayTypeSpan);
	DDX_CBIndex(pDX, IDC_RM_DAYTYPE_TYPE, m_nDayTypeWeekDay);
	DDX_CBIndex(pDX, IDC_RM_DAYTYPE_NUM, m_nDayTypeDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecurrenceRuleMonthlyDlg, CRecurrenceRuleDlg)
	//{{AFX_MSG_MAP(CRecurrenceRuleMonthlyDlg)
	ON_BN_CLICKED(IDC_RM_DAY, OnTypeDay)
	ON_BN_CLICKED(IDC_RM_DAYTYPE, OnTypeDay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleMonthlyDlg message handlers

void CRecurrenceRuleMonthlyDlg::SetRule (CBCGPRecurrenceBaseRule* pRule)
{
	CRecurrenceRuleDlg::SetRule (pRule);

	CBCGPRecurrenceRuleMonthly* pRuleM = (CBCGPRecurrenceRuleMonthly*)pRule;

	m_dwDay           = pRuleM->GetDay ();
	m_dwDaySpan       = pRuleM->GetDaySpan ();

	m_nDayTypeDay     = (int)pRuleM->GetDayTypeDay ();
	m_nDayTypeWeekDay = (int)pRuleM->GetDayTypeWeekDay ();
	m_dwDayTypeSpan   = pRuleM->GetDayTypeSpan ();
	
	if (((CBCGPRecurrenceRuleMonthly*)(pRule))->GetType () ==
		CBCGPRecurrenceRuleMonthly::BCGP_REC_RULE_MONTHLY_TYPE_DAY)
	{
		m_btnTypeDay.SetCheck (BST_CHECKED);
	}
	else
	{
		m_btnTypeDayType.SetCheck (BST_CHECKED);
	}

	UpdateData (FALSE);

	OnTypeDay();
}


BOOL CRecurrenceRuleMonthlyDlg::UpdateRule (const COleDateTime& /*dtStart*/)
{
	BOOL bRes = UpdateData ();

	if (bRes)
	{
		CBCGPRecurrenceRuleMonthly* pRule = (CBCGPRecurrenceRuleMonthly*)GetRule ();

		if (m_btnTypeDay.GetCheck () == BST_CHECKED)
		{
			if (m_dwDay < 1 || m_dwDay > 31)
			{
				return FALSE;
			}

			if (m_dwDaySpan < 1 || m_dwDaySpan > 1000)
			{
				return FALSE;
			}

			if (m_dwDay > 28)
			{
				CString str;

				str.Format (IDS_APPOINTMENT_4, m_dwDay);
				AfxMessageBox (str, MB_ICONWARNING);
			}

			pRule->SetType (CBCGPRecurrenceRuleMonthly::BCGP_REC_RULE_MONTHLY_TYPE_DAY);
			pRule->SetDay     (m_dwDay);
			pRule->SetDaySpan (m_dwDaySpan);
		}
		else
		{
			if (m_dwDayTypeSpan < 1 || m_dwDayTypeSpan > 1000)
			{
				return FALSE;
			}

			pRule->SetType (CBCGPRecurrenceRuleMonthly::BCGP_REC_RULE_MONTHLY_TYPE_DAYTYPE);
			pRule->SetDayTypeDay ((CBCGPRecurrenceRuleMonthly::BCGP_REC_RULE_MONTHLY_DAYTYPE_DAY)m_nDayTypeDay);
			pRule->SetDayTypeWeekDay ((CBCGPRecurrenceRuleMonthly::BCGP_REC_RULE_MONTHLY_DAYTYPE_WEEKDAY)m_nDayTypeWeekDay);
			pRule->SetDayTypeSpan (m_dwDayTypeSpan);
		}
	}

	return bRes;
}

BOOL CRecurrenceRuleMonthlyDlg::OnInitDialog() 
{
	CRecurrenceRuleDlg::OnInitDialog();

	for (int i = 0; i < 7; i++)
	{
		m_cbDayTypeWeekDay.AddString (CBCGPPlannerManagerCtrl::GetSystemWeekDayName (i));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecurrenceRuleMonthlyDlg::OnTypeDay() 
{
	BOOL bDay = m_btnTypeDay.GetCheck () == BST_CHECKED;

	UINT nID[] =
	{
		IDC_RM_DAY_DAY,
		IDC_RM_STATIC1,
		IDC_RM_DAY_SPAN,
		IDC_RM_STATIC2,
		IDC_RM_DAYTYPE_NUM,
		IDC_RM_DAYTYPE_TYPE,
		IDC_RM_STATIC3,
		IDC_RM_DAYTYPE_SPAN,
		IDC_RM_STATIC4
	};

	for (int i = 0; i < 9; i++)
	{
		CWnd* pWnd = GetDlgItem (nID[i]);
		if (pWnd->GetSafeHwnd ())
		{
			pWnd->EnableWindow (i < 4 ? bDay : !bDay);
		}
	}
}
