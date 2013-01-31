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
// AppointmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPCalendarDemo.h"
#include "AppointmentDlg.h"
#include "RecurrenceDlg.h"

#include "BCGPAppointmentDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppointmentDlg dialog


CAppointmentDlg::CAppointmentDlg(CBCGPAppointment& app, 
								 const CBCGPRecurrenceBaseRule* pRule /*=NULL*/,
								 BOOL bEcp /*= FALSE*/,
								 BOOL bNewRecur /*= FALSE*/,
								 BOOL bReadOnly /*= FALSE*/,
								 CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CAppointmentDlg::IDD, pParent)
	, m_Appointment (app)
	, m_Rule        (NULL)
	, m_bEcp        (bEcp)
	, m_bNewRecur   (bNewRecur)
	, m_bReadOnly   (bReadOnly)
	, m_bDeleted    (FALSE)
{
#ifndef _BCGPCALENDAR_STANDALONE
	EnableVisualManagerStyle ();
#endif

	if (pRule != NULL)
	{
		ASSERT_VALID (pRule);
		m_Rule = pRule->CreateCopy ();
	}

	//{{AFX_DATA_INIT(CAppointmentDlg)
	m_strSubject  = m_Appointment.GetDescription ();
	m_strLocation = _T("");
	m_bAllDay     = m_Appointment.IsAllDay ();
	m_bMeeting    = m_Appointment.HasImage (3);
	m_bPrivate    = m_Appointment.HasImage (2);
	m_bPhoneCall  = m_Appointment.HasImage (5);
	m_nLabel      = 0;
	m_nShowTime   = -1;
	m_strMemo = _T("");
	//}}AFX_DATA_INIT
}

CAppointmentDlg::~CAppointmentDlg ()
{
	if (m_Rule != NULL)
	{
		delete m_Rule;
		m_Rule = NULL;
	}
}

void CAppointmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppointmentDlg)
	DDX_Control(pDX, IDC_MEMO, m_EditMemo);
	DDX_Control(pDX, IDC_LOCATION, m_EditLocation);
	DDX_Control(pDX, IDC_DATETIME_START_STATIC, m_stDateTimeStart);
	DDX_Control(pDX, IDC_DATETIME_END_STATIC, m_stDateTimeEnd);
	DDX_Control(pDX, IDC_SHOW_TIME, m_wndShowTime);
	DDX_Control(pDX, IDC_LABEL, m_wndLabel);
	DDX_Control(pDX, IDC_DATE_START, m_DateStart);
	DDX_Control(pDX, IDC_TIME_START, m_TimeStart);
	DDX_Control(pDX, IDC_DATE_END, m_DateEnd);
	DDX_Control(pDX, IDC_TIME_END, m_TimeEnd);
	DDX_Text(pDX, IDC_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_LOCATION, m_strLocation);
	DDX_Check(pDX, IDC_ALLDAY, m_bAllDay);
	DDX_Check(pDX, IDC_MEETING, m_bMeeting);
	DDX_Check(pDX, IDC_PRIVATE, m_bPrivate);
	DDX_Check(pDX, IDC_PHONECALL, m_bPhoneCall);
	DDX_CBIndex(pDX, IDC_LABEL, m_nLabel);
	DDX_CBIndex(pDX, IDC_SHOW_TIME, m_nShowTime);
	DDX_Text(pDX, IDC_MEMO, m_strMemo);
	DDX_Control(pDX, IDC_ALLDAY, m_AllDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppointmentDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CAppointmentDlg)
	ON_BN_CLICKED(IDC_BTN_RECURRENCE, OnBtnRecurrence)
	ON_BN_CLICKED(IDC_ALLDAY, OnBtnAllDay)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppointmentDlg message handlers

void CAppointmentDlg::EnableDateControls (BOOL bEnable)
{
	int nCmd = bEnable ? SW_SHOW : SW_HIDE;

	m_stDateTimeStart.ShowWindow (nCmd);
	m_stDateTimeStart.EnableWindow (bEnable);
	m_DateStart.ShowWindow (nCmd);
	m_DateStart.EnableWindow (bEnable);
	m_TimeStart.ShowWindow (nCmd);
	m_TimeStart.EnableWindow (bEnable);

	m_stDateTimeEnd.ShowWindow (nCmd);
	m_stDateTimeEnd.EnableWindow (bEnable);
	m_DateEnd.ShowWindow (nCmd);
	m_DateEnd.EnableWindow (bEnable);
	m_TimeEnd.ShowWindow (nCmd);
	m_TimeEnd.EnableWindow (bEnable);

	m_AllDay.ShowWindow (nCmd);
	m_AllDay.EnableWindow (bEnable);
}

BOOL CAppointmentDlg::OnInitDialog() 
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
	m_DateStart.SetState (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | nFlags, nMask);
	m_DateStart.SetDate (m_Appointment.GetStart ());

	m_TimeStart.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
	m_TimeStart.SetDate (m_Appointment.GetStart ());

	m_DateEnd.SetState (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | nFlags, nMask);
	m_DateEnd.SetDate (m_Appointment.GetFinish ());

	m_TimeEnd.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
	m_TimeEnd.SetDate (m_Appointment.GetFinish ());

	if (m_Appointment.IsRecurrence () && !m_Appointment.IsRecurrenceClone ())
	{
		EnableDateControls (FALSE);
	}

	//------------------
	// Fill	label combo:
	//------------------
	m_wndLabel.AddColor (RGB (255, 255, 255), _T("None"));
	m_wndLabel.AddColor (RGB (255, 148, 132), _T("Important"));
	m_wndLabel.AddColor (RGB (132, 156, 231), _T("Business"));
	m_wndLabel.AddColor (RGB (165, 222, 99),  _T("Personal"));
	m_wndLabel.AddColor (RGB (231, 231, 214), _T("Vacation"));
	m_wndLabel.AddColor (RGB (255, 181, 115), _T("Must Attend"));
	m_wndLabel.AddColor (RGB (132, 239, 247), _T("Travel Requied"));
	m_wndLabel.AddColor (RGB (214, 206, 132), _T("Needs Preparation"));
	m_wndLabel.AddColor (RGB (198, 165, 247), _T("Birthday"));
	m_wndLabel.AddColor (RGB (165, 206, 198), _T("Anniversary"));
	m_wndLabel.AddColor (RGB (255, 231, 115), _T("Phone Call"));

	m_nLabel = 0;
	if (m_Appointment.GetBackgroundColor () != CLR_DEFAULT)
	{
		m_nLabel = m_wndLabel.FindColor (m_Appointment.GetBackgroundColor ());
	}

	//----------------------
	// Fill show time color:
	//----------------------
	m_wndShowTime.AddColor (RGB (255, 255, 255), _T("Free"));
	m_wndShowTime.AddColor (RGB (178, 207, 251), _T("Tentative"));
	m_wndShowTime.AddColor (RGB (0, 0, 255),     _T("Busy"));
	m_wndShowTime.AddColor (RGB (128, 0, 128),   _T("Out of office"));

	m_nShowTime = 0;
	if (m_Appointment.GetDurationColor () != CLR_DEFAULT)
	{
		m_nShowTime = m_wndShowTime.FindColor (m_Appointment.GetDurationColor ());
	}

	CBCGPAppointmentDemo* pAppDemo = DYNAMIC_DOWNCAST (CBCGPAppointmentDemo, &m_Appointment);
	if (pAppDemo != NULL)
	{
		m_strLocation = pAppDemo->GetLocation ();
		m_strMemo = pAppDemo->GetMemo ();
	}
	else
	{
		m_EditLocation.EnableWindow (FALSE);
		m_EditMemo.EnableWindow (FALSE);
	}

	if (m_bReadOnly)
	{
		const int nCount = 2;

		UINT nID [nCount] = {IDOK, IDC_BTN_DELETE};

		for (int i = 0; i < nCount; i++)
		{
			CWnd* pWnd = GetDlgItem (nID[i]);

			if (pWnd != NULL && pWnd->GetSafeHwnd () != NULL)
			{
				pWnd->EnableWindow (FALSE);
			}
		}
	}

	UpdateData (FALSE);

	if (!m_Appointment.IsRecurrence () || m_Appointment.IsRecurrenceClone () && 
		m_Appointment.IsAllDay ())
	{
		OnBtnAllDay ();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAppointmentDlg::OnBtnAllDay ()
{
	UpdateData ();

	int nCmd = m_bAllDay ? SW_HIDE : SW_SHOW;

	m_TimeStart.ShowWindow (nCmd);
	m_TimeStart.EnableWindow (!m_bAllDay);
	m_TimeEnd.ShowWindow (nCmd);
	m_TimeEnd.EnableWindow (!m_bAllDay);
}

void CAppointmentDlg::OnBtnDelete ()
{
	m_bDeleted = TRUE;

	CBCGPDialog::OnCancel ();
}

void CAppointmentDlg::OnOK() 
{
	UpdateData ();

	m_Appointment.SetAllDay (m_bAllDay);

	if (!m_Appointment.IsRecurrence () || m_Appointment.IsRecurrenceClone ())
	{
		COleDateTime dtS = m_DateStart.GetDate ();
		COleDateTime dtF = m_DateEnd.GetDate ();

		COleDateTime tmS = m_TimeStart.GetDate ();
		COleDateTime tmF = m_TimeEnd.GetDate ();

		dtS = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
			tmS.GetHour (), tmS.GetMinute (), 0);

		dtF = COleDateTime (dtF.GetYear (), dtF.GetMonth (), dtF.GetDay (),
			tmF.GetHour (), tmF.GetMinute (), 0);

		if (dtS > dtF)
		{
			AfxMessageBox (IDS_APPOINTMENT_1);
			return;
		}

		m_Appointment.SetInterval (dtS, dtF);
	}
	
	m_Appointment.SetDescription (m_strSubject);
	m_Appointment.SetBackgroundColor (m_nLabel == 0 ? CLR_DEFAULT : m_wndLabel.GetColor (m_nLabel));
	m_Appointment.SetDurationColor (m_nShowTime == 0 ? CLR_DEFAULT : m_wndShowTime.GetColor (m_nShowTime));

	m_Appointment.RemoveAllImages ();

	if (m_bPrivate)
	{
		m_Appointment.AddImage (2);
	}

	if (m_bMeeting)
	{
		m_Appointment.AddImage (3);
	}

	if (m_bPhoneCall)
	{
		m_Appointment.AddImage (5);
	}

	CBCGPAppointmentDemo* pAppDemo = DYNAMIC_DOWNCAST (CBCGPAppointmentDemo, &m_Appointment);
	if (pAppDemo != NULL)
	{
		pAppDemo->SetLocation (m_strLocation);
		pAppDemo->SetMemo (m_strMemo);
	}

	CBCGPDialog::OnOK();
}

void CAppointmentDlg::OnCancel()
{
	CBCGPDialog::OnCancel ();
}

void CAppointmentDlg::OnBtnRecurrence() 
{
	CBCGPRecurrenceBaseRule* pRule = m_Rule;

	if (pRule == NULL)
	{
		pRule = CBCGPPlannerManagerCtrl::CreateRule (BCGP_PLANNER_RULE_DAILY);
		pRule->SetDateStart (m_Appointment.GetStart ());
		
		COleDateTimeSpan span (m_Appointment.GetStart () - pRule->GetDateStart ());
		pRule->SetTimeInterval (span, span + m_Appointment.GetDuration ());
	}

	CRecurrenceDlg dlg(pRule, m_Rule != NULL, m_bEcp, this);

	if (dlg.DoModal () == IDOK)
	{
		m_bEcp = FALSE;
		
		const CBCGPRecurrenceBaseRule* pRuleNew = dlg.GetRule ();

		if (pRuleNew == NULL)
		{
			if (m_Rule != NULL)
			{
				delete m_Rule;
				m_Rule = NULL;

				EnableDateControls (TRUE);

				if (m_Appointment.IsAllDay ())
				{
					OnBtnAllDay ();
				}
			}
		}
		else
		{
			if (m_Rule == NULL || m_Appointment.IsRecurrenceClone ())
			{
				delete pRule;
				EnableDateControls (FALSE);
			}
			else
			{
				delete m_Rule;
			}

			m_Rule = CBCGPPlannerManagerCtrl::CreateRule (pRuleNew->GetID ());


			CBCGPAppointmentPropertyList props;
			pRuleNew->GetProperties (props);
			m_Rule->SetProperties (props);
		}
	}
	else
	{
		if (m_Rule == NULL)
		{
			delete pRule;
		}
	}
}

void CAppointmentDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CBCGPDialog::OnShowWindow(bShow, nStatus);
	
	if (m_bNewRecur)
	{
		PostMessage (WM_COMMAND, MAKEWPARAM (IDC_BTN_RECURRENCE, BN_CLICKED), 
			(LPARAM)m_Recurrence.GetSafeHwnd ());
	}
}
