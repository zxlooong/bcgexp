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
#include "BCGPGanttDemo.h"
#include "GanttDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGanttDlg dialog


CGanttDlg::CGanttDlg(CBCGPGanttItem& item, 
								 BOOL bMilestone /*= FALSE*/,
								 BOOL bReadOnly /*= FALSE*/,
								 CWnd* pParent /*=NULL*/)
	: CDialog(CGanttDlg::IDD, pParent)
	, m_Item       (item)
	, m_bMilestone (bMilestone)
	, m_bReadOnly  (bReadOnly)
	, m_bDeleted   (FALSE)
{
	//{{AFX_DATA_INIT(CGanttDlg)
	m_strName = m_Item.GetName ();
	m_strMemo = _T("");
	m_lProgress = (long)(m_Item.GetProgress () * 100.0 + 0.5);
	//}}AFX_DATA_INIT

	m_bCompleted = m_Item.IsCompleted ();
}

CGanttDlg::~CGanttDlg ()
{
}

void CGanttDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGanttDlg)
	DDX_Control(pDX, IDC_MEMO, m_EditMemo);
	DDX_Control(pDX, IDC_DATETIME_START_STATIC, m_stDateTimeStart);
	DDX_Control(pDX, IDC_DATETIME_END_STATIC, m_stDateTimeEnd);
	DDX_Control(pDX, IDC_DATE_START, m_DateStart);
	DDX_Control(pDX, IDC_TIME_START, m_TimeStart);
	DDX_Control(pDX, IDC_DATE_END, m_DateEnd);
	DDX_Control(pDX, IDC_TIME_END, m_TimeEnd);
    DDX_Control(pDX, IDC_COLOR1, m_Color1);
    DDX_Control(pDX, IDC_COLOR2, m_Color2);
	DDX_Control (pDX, IDC_PROGRESS_STATIC, m_stProgress);
	DDX_Control (pDX, IDC_PROGRESS_EDIT, m_Progress);
	DDX_Control (pDX, IDC_PROGRESS_SPIN, m_ProgressSpin);
	DDX_Text (pDX, IDC_PROGRESS_EDIT, m_lProgress);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_MEMO, m_strMemo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGanttDlg, CDialog)
	//{{AFX_MSG_MAP(CGanttDlg)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGanttDlg message handlers

void CGanttDlg::EnableDateControls (BOOL bEnable)
{
	int nCmd = bEnable ? SW_SHOW : SW_HIDE;

	m_stDateTimeEnd.ShowWindow (nCmd);
	m_stDateTimeEnd.EnableWindow (bEnable);
	m_DateEnd.ShowWindow (nCmd);
	m_DateEnd.EnableWindow (bEnable);
	m_TimeEnd.ShowWindow (nCmd);
	m_TimeEnd.EnableWindow (bEnable);

	m_stProgress.ShowWindow (nCmd);
	m_stProgress.EnableWindow (bEnable);
	m_Progress.ShowWindow (nCmd);
	m_Progress.EnableWindow (bEnable);
	m_ProgressSpin.ShowWindow (nCmd);
	m_ProgressSpin.EnableWindow (bEnable);
}

BOOL CGanttDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

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
	m_DateStart.SetDate (m_Item.GetStartTime ());

	m_TimeStart.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
	m_TimeStart.SetDate (m_Item.GetStartTime ());

	m_DateEnd.SetState (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | nFlags, nMask);
	m_DateEnd.SetDate (m_Item.GetFinishTime ());

	m_TimeEnd.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
	m_TimeEnd.SetDate (m_Item.GetFinishTime ());

	if (m_bMilestone)
	{
		EnableDateControls (FALSE);
	}

    //-------------------
    //  Color pickers:

    m_Color1.EnableAutomaticButton (_T("Automatic"), CLR_DEFAULT);
    m_Color1.EnableOtherButton (_T("Other"));
    m_Color1.SetColor (m_Item.GetPrimaryColor () == CLR_DEFAULT ? (COLORREF)-1 : m_Item.GetPrimaryColor ());

    m_Color2.EnableAutomaticButton (_T("Automatic"), CLR_DEFAULT);
    m_Color2.EnableOtherButton (_T("Other"));
    m_Color2.SetColor (m_Item.GetCompleteColor () == CLR_DEFAULT ? (COLORREF)-1 : m_Item.GetCompleteColor ());

/*
	CBCGPAppointmentDemo* pAppDemo = DYNAMIC_DOWNCAST (CBCGPAppointmentDemo, &m_Item);
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
*/
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

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGanttDlg::OnBtnDelete ()
{
	m_bDeleted = TRUE;

	CDialog::OnCancel ();
}

void CGanttDlg::OnOK() 
{
	UpdateData ();
	COleDateTime dtS = m_DateStart.GetDate ();
	COleDateTime tmS = m_TimeStart.GetDate ();

	COleDateTime dtF = dtS;
	COleDateTime tmF = tmS;

	if (!m_bMilestone)
	{
		dtF = m_DateEnd.GetDate ();
		tmF = m_TimeEnd.GetDate ();
	}

	dtS = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
		tmS.GetHour (), tmS.GetMinute (), 0);

	dtF = COleDateTime (dtF.GetYear (), dtF.GetMonth (), dtF.GetDay (),
		tmF.GetHour (), tmF.GetMinute (), 0);

	if (!m_bMilestone)
	{
		if (dtS >= dtF)
		{
			AfxMessageBox (IDS_GANTT_1);
			return;
		}
	}	

	m_Item.SetInterval (dtS, dtF);

	m_Item.SetName (m_strName);

	if (m_bCompleted)
	{
		m_Item.SetCompleted ();
	}
	else if (!m_bMilestone)
	{
		m_Item.SetProgress (m_lProgress / 100.0);
	}

    
    COLORREF clr = m_Color1.GetColor ();
    m_Item.SetPrimaryColor (clr == (COLORREF)-1 ? CLR_DEFAULT : clr);

    clr = m_Color2.GetColor ();
    m_Item.SetCompleteColor (clr == (COLORREF)-1 ? CLR_DEFAULT : clr);

/*
	CAppointment* pAppDemo = DYNAMIC_DOWNCAST (CAppointment, &m_Appointment);
	if (pAppDemo != NULL)
	{
		pAppDemo->SetImportance (m_Importance == e_ImportanceLow
			? CAppointment::e_ImportanceLow
			: m_Importance == e_ImportanceHigh
				? CAppointment::e_ImportanceHigh
				: CAppointment::e_ImportanceNormal);
		pAppDemo->SetPrivate (m_bPrivate);

		pAppDemo->SetLocation (m_wndDialogBar.m_strLocation);

		CString strMemo;
		GetText (strMemo);
		pAppDemo->SetMemo (strMemo);
	}
*/
	CDialog::OnOK();
}

void CGanttDlg::OnCancel()
{
	CDialog::OnCancel ();
}
