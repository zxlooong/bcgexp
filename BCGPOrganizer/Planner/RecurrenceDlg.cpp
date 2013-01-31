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
// RecurrenceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "RecurrenceDlg.h"

#include "RecurrenceRuleDailyDlg.h"
#include "RecurrenceRuleWeeklyDlg.h"
#include "RecurrenceRuleMonthlyDlg.h"
#include "RecurrenceRuleYearlyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceDlg dialog


CRecurrenceDlg::CRecurrenceDlg(const CBCGPRecurrenceBaseRule* pRule, 
							   BOOL bHasRule,
							   BOOL bEcp,
							   CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CRecurrenceDlg::IDD, pParent)
	, m_Dialog (NULL)
	, m_bHasRule (bHasRule)
	, m_bEcp (bEcp)
{
	EnableVisualManagerStyle ();

	ASSERT_VALID (pRule);

	CBCGPPlannerManagerCtrl::GetRulesID (m_RulesID);

	m_ID = 0;

	COleDateTime dtStart (pRule->GetDateStart ());

	for (int i = 0; i < m_RulesID.GetSize (); i++)
	{
		DWORD ID = m_RulesID[i];

		if (pRule != NULL && ID == pRule->GetID ())
		{
			m_ID = pRule->GetID ();
			m_Rules.SetAtGrow (ID, pRule->CreateCopy ());
		}
		else
		{
			CBCGPRecurrenceBaseRule* pR = CBCGPPlannerManagerCtrl::CreateRule (ID);
			pR->SetDateStart (dtStart);

			if (ID == BCGP_PLANNER_RULE_WEEKLY)
			{
				int nWD = dtStart.GetDayOfWeek () - 1;

				((CBCGPRecurrenceRuleWeekly*)(pR))->SetDays 
					(
						1 << ((nWD == 0 ? 7 : nWD) - 1)
					);
			}
			else if (ID == BCGP_PLANNER_RULE_MONTHLY)
			{
				((CBCGPRecurrenceRuleMonthly*)(pR))->SetDay (dtStart.GetDay ());

				int nWD = dtStart.GetDayOfWeek () - 1;
				((CBCGPRecurrenceRuleMonthly*)(pR))->SetDayTypeWeekDay 
					(
						(CBCGPRecurrenceRuleMonthly::BCGP_REC_RULE_MONTHLY_DAYTYPE_WEEKDAY)
							((nWD == 0 ? 7 : nWD) - 1 + 
							 (int)CBCGPRecurrenceRuleMonthly::BCGP_REC_RULE_MONTHLY_DAYTYPE_WEEKDAY_1)
					);
			}
			else if (ID == BCGP_PLANNER_RULE_YEARLY)
			{
				((CBCGPRecurrenceRuleYearly*)(pR))->SetDay (dtStart.GetDay ());
				((CBCGPRecurrenceRuleYearly*)(pR))->SetDayMonth (dtStart.GetMonth ());

				int nWD = dtStart.GetDayOfWeek () - 1;
				((CBCGPRecurrenceRuleYearly*)(pR))->SetDayTypeWeekDay 
					(
						(CBCGPRecurrenceRuleYearly::BCGP_REC_RULE_YEARLY_DAYTYPE_WEEKDAY)
							((nWD == 0 ? 7 : nWD) - 1 + 
							 (int)CBCGPRecurrenceRuleYearly::BCGP_REC_RULE_YEARLY_DAYTYPE_WEEKDAY_1)
					);
				((CBCGPRecurrenceRuleYearly*)(pR))->SetDayTypeMonth (dtStart.GetMonth ());
			}

			m_Rules.SetAtGrow (ID, pR);
		}
	}

	//{{AFX_DATA_INIT(CRecurrenceDlg)
	m_LimitCount = 10;
	//}}AFX_DATA_INIT

	if (pRule->GetLimitType () == CBCGPRecurrenceBaseRule::BCGP_RECURRENCE_RULE_LIMIT_COUNT)
	{
		m_LimitCount = pRule->GetLimitCount ();
	}
}

CRecurrenceDlg::~CRecurrenceDlg ()
{
	int i = 0;

	for (i = 0; i < m_RulesID.GetSize (); i++)
	{
		DWORD ID = m_RulesID[i];

		if (m_Rules[ID] != NULL)
		{
			delete m_Rules[ID];
		}
	}

	for (i = 0; i < m_RulesDlg.GetSize (); i++)
	{
		if (m_RulesDlg[i] != NULL)
		{
			delete m_RulesDlg[i];
		}
	}
}

void CRecurrenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecurrenceDlg)
	DDX_Control(pDX, IDC_TIME_START, m_TimeStart);
	DDX_Control(pDX, IDC_TIME_END, m_TimeEnd);
	DDX_Control(pDX, IDC_DATE_START, m_DateStart);
	DDX_Control(pDX, IDC_DATE_END, m_LimitDate);
	DDX_Control(pDX, IDC_DURATION, m_Duration);
	DDX_Text(pDX, IDC_COUNT, m_LimitCount);
	DDV_MinMaxDWord(pDX, m_LimitCount, 1, 999);
	DDX_Control(pDX, IDC_RULE_DAILY, m_btnRuleDaily);
	DDX_Control(pDX, IDC_RULE_WEEKLY, m_btnRuleWeekly);
	DDX_Control(pDX, IDC_RULE_MONTHLY, m_btnRuleMonthly);
	DDX_Control(pDX, IDC_RULE_YEARLY, m_btnRuleYearly);
	DDX_Control(pDX, IDC_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_LIMIT_NONE, m_btnLimitNone);
	DDX_Control(pDX, IDC_LIMIT_COUNT, m_btnLimitCount);
	DDX_Control(pDX, IDC_LIMIT_DATE, m_btnLimitDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecurrenceDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CRecurrenceDlg)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_RULE_DAILY, OnRuleDaily)
	ON_BN_CLICKED(IDC_RULE_WEEKLY, OnRuleWeekly)
	ON_BN_CLICKED(IDC_RULE_MONTHLY, OnRuleMonthly)
	ON_BN_CLICKED(IDC_RULE_YEARLY, OnRuleYearly)
	ON_BN_CLICKED(IDC_LIMIT_NONE, OnLimitNone)
	ON_BN_CLICKED(IDC_LIMIT_COUNT, OnLimitCount)
	ON_BN_CLICKED(IDC_LIMIT_DATE, OnLimitDate)
	ON_BN_CLICKED(IDC_TIME_START, OnTimeChangedS)
	ON_BN_CLICKED(IDC_TIME_END, OnTimeChangedE)
	ON_BN_CLICKED(IDC_DURATION, OnDurationChanged)
	ON_EN_CHANGE(IDC_COUNT, OnChangeCount)
	ON_BN_CLICKED(IDC_DATE_END, OnDateEndChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceDlg message handlers

BOOL CRecurrenceDlg::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	UINT nMask = 
		CBCGPDateTimeCtrl::DTM_SPIN         |
		CBCGPDateTimeCtrl::DTM_DATE         |
		CBCGPDateTimeCtrl::DTM_TIME         |
		CBCGPDateTimeCtrl::DTM_CHECKBOX     |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_CHECKED;

	UINT nFlags = CBCGPDateTimeCtrl::DTM_CHECKED | CBCGPDateTimeCtrl::DTM_SPIN;
	//-------------------
	// Setup date fields:
	//-------------------
	CBCGPRecurrenceBaseRule* pRule = m_Rules[m_ID];

	COleDateTime dtStart (pRule->GetDateStart ());

	m_DateStart.SetState (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | nFlags, nMask);
	m_DateStart.SetDate (dtStart);

	m_TimeStart.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
	m_TimeStart.SetDate (dtStart + pRule->GetTimeStart ());

	m_TimeEnd.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
	m_TimeEnd.SetDate (dtStart + pRule->GetTimeFinish ());

	m_LimitDate.SetState (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | nFlags, nMask);
	if (pRule->GetLimitType () == CBCGPRecurrenceBaseRule::BCGP_RECURRENCE_RULE_LIMIT_DATE)
	{
		m_LimitDate.SetDate (pRule->GetLimitDate ());
	}
	else
	{
		m_LimitDate.SetDate (COleDateTime (dtStart.GetYear () + 1, dtStart.GetMonth (),
			dtStart.GetDay (), 0, 0, 0));
	}

	m_Duration.SetState (CBCGPDurationCtrl::DRTN_DAYS | 
		                 CBCGPDurationCtrl::DRTN_HOURS_MINS | 
						 CBCGPDurationCtrl::DRTN_SPIN, 
						 CBCGPDurationCtrl::DRTN_DAYS | 
						 CBCGPDurationCtrl::DRTN_HOURS_MINS | 
						 CBCGPDurationCtrl::DRTN_SPIN | 
						 CBCGPDurationCtrl::DRTN_SECONDS);
	m_Duration.SetDuration (m_TimeEnd.GetDate () - m_TimeStart.GetDate ());

	m_RulesDlg.Add (new CRecurrenceRuleDailyDlg);
	m_RulesDlg.Add (new CRecurrenceRuleWeeklyDlg);
	m_RulesDlg.Add (new CRecurrenceRuleMonthlyDlg);
	m_RulesDlg.Add (new CRecurrenceRuleYearlyDlg);

	CRect rt;
	CWnd* pWnd = GetDlgItem (IDC_POS_STATIC);
	ASSERT_VALID(pWnd);

	pWnd->GetWindowRect (rt);
	ScreenToClient (rt);

	for (int i = 0; i < m_RulesDlg.GetSize (); i++)
	{
		m_RulesDlg[i]->Create (this);
		m_RulesDlg[i]->SetWindowPos(&wndTop, rt.left, rt.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	if (pRule->GetLimitType () == CBCGPRecurrenceBaseRule::BCGP_RECURRENCE_RULE_LIMIT_COUNT)
	{
		m_btnLimitCount.SetCheck (BST_CHECKED);
	}
	else if (pRule->GetLimitType () == CBCGPRecurrenceBaseRule::BCGP_RECURRENCE_RULE_LIMIT_DATE)
	{
		m_btnLimitDate.SetCheck (BST_CHECKED);
	}
	else
	{
		m_btnLimitNone.SetCheck (BST_CHECKED);
	}

	if (!m_bHasRule)
	{
		m_btnRemove.EnableWindow (FALSE);
	}

	if (m_ID == BCGP_PLANNER_RULE_DAILY)
	{
		OnRuleDaily ();
	}
	else if (m_ID == BCGP_PLANNER_RULE_WEEKLY)
	{
		OnRuleWeekly ();
	}
	else if (m_ID == BCGP_PLANNER_RULE_MONTHLY)
	{
		OnRuleMonthly ();
	}
	else if (m_ID == BCGP_PLANNER_RULE_YEARLY)
	{
		OnRuleYearly ();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecurrenceDlg::OnOK() 
{
	if (!UpdateData ())
	{
		return;
	}

	if (m_bEcp)
	{
		if (AfxMessageBox (IDS_APPOINTMENT_5, MB_ICONWARNING | MB_OKCANCEL) == IDCANCEL)
		{
			return;
		}
	}

	COleDateTime dtStart (m_DateStart.GetDate ());
	dtStart = COleDateTime(dtStart.GetYear (), dtStart.GetMonth (), dtStart.GetDay (), 
		0, 0, 0);

	COleDateTime dt (m_TimeStart.GetDate ());
	COleDateTimeSpan sp1 (0, dt.GetHour (), dt.GetMinute (), 0);
	COleDateTimeSpan sp2 (sp1 + m_Duration.GetDuration ());

	if (sp2 < sp1)
	{
		AfxMessageBox (IDS_APPOINTMENT_1, MB_ICONWARNING);
		return;
	}

	if (m_Dialog != NULL)
	{
		if (!m_Dialog->UpdateRule (m_DateStart.GetDate ()) ||
			(m_btnLimitDate.GetCheck () == BST_CHECKED && 
			 m_LimitDate.GetDate () < m_DateStart.GetDate ()))
		{
			AfxMessageBox (IDS_APPOINTMENT_3, MB_ICONWARNING);
			return;
		}
	}

	CBCGPRecurrenceBaseRule* pRule = m_Rules[m_ID];

	if (m_btnLimitCount.GetCheck () == BST_CHECKED)
	{
		pRule->SetLimitType (CBCGPRecurrenceBaseRule::BCGP_RECURRENCE_RULE_LIMIT_COUNT);
		pRule->SetLimitCount (m_LimitCount);
	}
	else if (m_btnLimitDate.GetCheck () == BST_CHECKED)
	{
		pRule->SetLimitType (CBCGPRecurrenceBaseRule::BCGP_RECURRENCE_RULE_LIMIT_DATE);
		pRule->SetLimitDate (m_LimitDate.GetDate ());
	}
	else
	{
		pRule->SetLimitType (CBCGPRecurrenceBaseRule::BCGP_RECURRENCE_RULE_LIMIT_NONE);
	}

	pRule->SetDateStart (dtStart);
	pRule->SetTimeInterval (sp1, sp2);
	
	pRule->CorrectStart ();

	CBCGPDialog::OnOK();
}

void CRecurrenceDlg::OnRemove() 
{
	delete m_Rules[m_ID];
	m_Rules[m_ID] = NULL;

	CBCGPDialog::OnOK();
}

void CRecurrenceDlg::ChangeRule (DWORD index)
{
	m_ID = m_RulesID[index];

	CBCGPRecurrenceBaseRule* pRule = m_Rules[m_ID];

	if (m_Dialog != NULL)
	{
		m_Dialog->UpdateRule (COleDateTime ());
		m_Dialog->ShowWindow (SW_HIDE);
	}

	m_Dialog = m_RulesDlg[index];

	if (m_Dialog != NULL)
	{
		m_Dialog->ShowWindow (SW_SHOW);
		m_Dialog->SetRule (pRule);
	}
}

void CRecurrenceDlg::OnRuleDaily() 
{
	m_btnRuleDaily.SetCheck (BST_CHECKED);

	m_btnRuleWeekly.SetCheck (BST_UNCHECKED);
	m_btnRuleMonthly.SetCheck (BST_UNCHECKED);
	m_btnRuleYearly.SetCheck (BST_UNCHECKED);

	ChangeRule (0);
}

void CRecurrenceDlg::OnRuleWeekly() 
{
	m_btnRuleWeekly.SetCheck (BST_CHECKED);

	m_btnRuleDaily.SetCheck (BST_UNCHECKED);
	m_btnRuleMonthly.SetCheck (BST_UNCHECKED);
	m_btnRuleYearly.SetCheck (BST_UNCHECKED);

	ChangeRule (1);
}

void CRecurrenceDlg::OnRuleMonthly() 
{
	m_btnRuleMonthly.SetCheck (BST_CHECKED);

	m_btnRuleDaily.SetCheck (BST_UNCHECKED);
	m_btnRuleWeekly.SetCheck (BST_UNCHECKED);
	m_btnRuleYearly.SetCheck (BST_UNCHECKED);

	ChangeRule (2);
}

void CRecurrenceDlg::OnRuleYearly() 
{
	m_btnRuleYearly.SetCheck (BST_CHECKED);

	m_btnRuleDaily.SetCheck (BST_UNCHECKED);
	m_btnRuleWeekly.SetCheck (BST_UNCHECKED);
	m_btnRuleMonthly.SetCheck (BST_UNCHECKED);

	ChangeRule (3);
}

const CBCGPRecurrenceBaseRule* CRecurrenceDlg::GetRule () const
{
	ASSERT (m_ID > 0);
	return m_Rules[m_ID];
}

void CRecurrenceDlg::OnLimitNone()
{
	m_LimitCount = 10;

	COleDateTime dtStart (m_DateStart.GetDate ());

	m_LimitDate.SetDate (COleDateTime (dtStart.GetYear () + 1, dtStart.GetMonth (),
		dtStart.GetDay (), 0, 0, 0));

	UpdateData (FALSE);
}

void CRecurrenceDlg::OnLimitCount()
{
	COleDateTime dtStart (m_DateStart.GetDate ());
	
	m_LimitDate.SetDate (COleDateTime (dtStart.GetYear () + 1, dtStart.GetMonth (),
		dtStart.GetDay (), 0, 0, 0));
}

void CRecurrenceDlg::OnLimitDate()
{
	m_LimitCount = 10;

	UpdateData (FALSE);
}

void CRecurrenceDlg::OnTimeChangedS()
{
	m_TimeEnd.SetDate (m_TimeStart.GetDate () + m_Duration.GetDuration ());
}

void CRecurrenceDlg::OnTimeChangedE()
{
	if (m_TimeEnd.GetDate () < m_TimeStart.GetDate ())
	{
		m_TimeEnd.SetDate (m_TimeStart.GetDate ());
	}

	m_Duration.SetDuration (m_TimeEnd.GetDate () - m_TimeStart.GetDate ());
}

void CRecurrenceDlg::OnDurationChanged()
{
	OnTimeChangedS ();
}

void CRecurrenceDlg::OnChangeCount() 
{
	if (m_btnLimitCount.GetCheck () != BST_CHECKED)
	{
		m_btnLimitCount.SetCheck (BST_CHECKED);
		m_btnLimitNone.SetCheck (BST_UNCHECKED);
		m_btnLimitDate.SetCheck (BST_UNCHECKED);

		OnLimitCount ();
	}
}

void CRecurrenceDlg::OnDateEndChanged() 
{
	if (m_btnLimitDate.GetCheck () != BST_CHECKED)
	{
		m_btnLimitDate.SetCheck (BST_CHECKED);
		m_btnLimitNone.SetCheck (BST_UNCHECKED);
		m_btnLimitCount.SetCheck (BST_UNCHECKED);

		OnLimitDate ();
	}
}
