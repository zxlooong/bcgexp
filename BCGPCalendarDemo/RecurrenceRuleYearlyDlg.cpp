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
// RecurrenceRuleYearlyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcalendardemo.h"
#include "RecurrenceRuleYearlyDlg.h"

#include "BCGPPlannerView.h"
#include "BCGPRecurrenceRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleYearlyDlg dialog


CRecurrenceRuleYearlyDlg::CRecurrenceRuleYearlyDlg()
{
	//{{AFX_DATA_INIT(CRecurrenceRuleYearlyDlg)
	m_dwDay = 0;
	m_nDayMonth = 0;
	m_nDayTypeMonth = 0;
	m_nDayTypeDay = 0;
	m_nDayTypeWeekDay = 0;
	//}}AFX_DATA_INIT
}


void CRecurrenceRuleYearlyDlg::DoDataExchange(CDataExchange* pDX)
{
	CRecurrenceRuleDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecurrenceRuleYearlyDlg)
	DDX_Control(pDX, IDC_RY_DAYTYPE_TYPE, m_cbDayTypeWeekDay);
	DDX_Control(pDX, IDC_RY_DAYTYPE_MONTH, m_cbDayTypeMonth);
	DDX_Control(pDX, IDC_RY_DAY_MONTH, m_cbDayMonth);
	DDX_Control (pDX, IDC_RY_DAY, m_btnTypeDay);
	DDX_Control (pDX, IDC_RY_DAYTYPE, m_btnTypeDayType);
	DDX_Text(pDX, IDC_RY_DAY_DAY, m_dwDay);
	DDX_CBIndex(pDX, IDC_RY_DAY_MONTH, m_nDayMonth);
	DDX_CBIndex(pDX, IDC_RY_DAYTYPE_MONTH, m_nDayTypeMonth);
	DDX_CBIndex(pDX, IDC_RY_DAYTYPE_NUM, m_nDayTypeDay);
	DDX_CBIndex(pDX, IDC_RY_DAYTYPE_TYPE, m_nDayTypeWeekDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecurrenceRuleYearlyDlg, CRecurrenceRuleDlg)
	//{{AFX_MSG_MAP(CRecurrenceRuleYearlyDlg)
	ON_BN_CLICKED(IDC_RY_DAY, OnTypeDay)
	ON_BN_CLICKED(IDC_RY_DAYTYPE, OnTypeDay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleYearlyDlg message handlers

void CRecurrenceRuleYearlyDlg::SetRule (CBCGPRecurrenceBaseRule* pRule)
{
	CRecurrenceRuleDlg::SetRule (pRule);

	CBCGPRecurrenceRuleYearly* pRuleY = (CBCGPRecurrenceRuleYearly*)pRule;
	m_dwDay = pRuleY->GetDay ();
	m_nDayMonth = pRuleY->GetDayMonth () - 1;

	m_nDayTypeDay     = (int)pRuleY->GetDayTypeDay ();
	m_nDayTypeWeekDay = (int)pRuleY->GetDayTypeWeekDay ();
	m_nDayTypeMonth   = pRuleY->GetDayTypeMonth () - 1;

	if (((CBCGPRecurrenceRuleYearly*)(pRule))->GetType () ==
		CBCGPRecurrenceRuleYearly::BCGP_REC_RULE_YEARLY_TYPE_DAY)
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


BOOL CRecurrenceRuleYearlyDlg::UpdateRule (const COleDateTime& dtStart)
{
	BOOL bRes = UpdateData ();

	if (bRes)
	{
		CBCGPRecurrenceRuleYearly* pRule = (CBCGPRecurrenceRuleYearly*)GetRule ();

		if (m_btnTypeDay.GetCheck () == BST_CHECKED)
		{
			if (m_dwDay < 1 || m_dwDay > 31)
			{
				return FALSE;
			}

			if (dtStart != COleDateTime ())
			{
				if ( CBCGPCalendar::GetMaxMonthDay (m_cbDayMonth.GetCurSel () + 1, 
						dtStart.GetYear ()) < (int)m_dwDay)
				{
					return FALSE;
				}
			}

			pRule->SetType (CBCGPRecurrenceRuleYearly::BCGP_REC_RULE_YEARLY_TYPE_DAY);
			pRule->SetDayMonth (m_nDayMonth + 1);
			pRule->SetDay     (m_dwDay);
		}
		else
		{
			pRule->SetType (CBCGPRecurrenceRuleYearly::BCGP_REC_RULE_YEARLY_TYPE_DAYTYPE);
			pRule->SetDayTypeDay ((CBCGPRecurrenceRuleYearly::BCGP_REC_RULE_YEARLY_DAYTYPE_DAY)m_nDayTypeDay);
			pRule->SetDayTypeWeekDay ((CBCGPRecurrenceRuleYearly::BCGP_REC_RULE_YEARLY_DAYTYPE_WEEKDAY)m_nDayTypeWeekDay);
			pRule->SetDayTypeMonth (m_nDayTypeMonth + 1);
		}
	}

	return bRes;
}

BOOL CRecurrenceRuleYearlyDlg::OnInitDialog() 
{
	CRecurrenceRuleDlg::OnInitDialog();
	
	int i;
	for (i = 0; i < 12; i++)
	{
		CString str;

		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_SMONTHNAME1 + i,
			str.GetBuffer (100), 100);
		str.ReleaseBuffer ();

		m_cbDayMonth.AddString (str);
		m_cbDayTypeMonth.AddString (str);
	}

	for (i = 0; i < 7; i++)
	{
		m_cbDayTypeWeekDay.AddString (CBCGPPlannerManagerCtrl::GetSystemWeekDayName (i));
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecurrenceRuleYearlyDlg::OnTypeDay() 
{
	BOOL bDay = m_btnTypeDay.GetCheck () == BST_CHECKED;

	UINT nID[] =
	{
		IDC_RY_DAY_MONTH,
		IDC_RY_DAY_DAY,
		IDC_RY_DAYTYPE_NUM,
		IDC_RY_DAYTYPE_TYPE,
		IDC_RM_STATIC1,
		IDC_RY_DAYTYPE_MONTH,
	};

	for (int i = 0; i < 6; i++)
	{
		CWnd* pWnd = GetDlgItem (nID[i]);
		if (pWnd->GetSafeHwnd ())
		{
			pWnd->EnableWindow (i < 2 ? bDay : !bDay);
		}
	}
}
