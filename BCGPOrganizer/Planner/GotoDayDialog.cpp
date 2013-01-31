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
// GotoDayDialog.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "GotoDayDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoDayDialog dialog

CGotoDayDialog::CGotoDayDialog(const COleDateTime& date, 
	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type,
	int nFirstDayOfWeek /*= 0*/, 
	CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CGotoDayDialog::IDD, pParent)
	, m_Date (date)
	, m_Type (type)
	, m_nFirstDayOfWeek(0)
{
	EnableVisualManagerStyle ();

	//{{AFX_DATA_INIT(CGotoDayDialog)
	m_TypeIndex = -1;
	//}}AFX_DATA_INIT

	ASSERT (0 <= nFirstDayOfWeek);
	ASSERT (nFirstDayOfWeek <= 6);

	m_nFirstDayOfWeek = nFirstDayOfWeek;

	switch (m_Type)
	{
	case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY:
		m_TypeIndex = 0;
		break;
	case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK:
		m_TypeIndex = 1;
		break;
	case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK:
		m_TypeIndex = 2;
		break;
	case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH:
		m_TypeIndex = 3;
		break;
	}
}


void CGotoDayDialog::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoDayDialog)
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_DateTimePicker);
	DDX_CBIndex(pDX, IDC_MODE_COMBO, m_TypeIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoDayDialog, CBCGPDialog)
	//{{AFX_MSG_MAP(CGotoDayDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CGotoDayDialog::OnOK ()
{
	if (!UpdateData ())
	{
		return;
	}

	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE nType [4] =
	{
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY,
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK,
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK,
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH
	};

	m_Type = nType [m_TypeIndex];

	m_Date = m_DateTimePicker.GetDate();

	CBCGPDialog::OnOK ();
}

/////////////////////////////////////////////////////////////////////////////
// CGotoDayDialog message handlers

BOOL CGotoDayDialog::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	m_DateTimePicker.SizeToContent();
	
	m_DateTimePicker.SetState (
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE,
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME | 
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);

	m_DateTimePicker.SetFirstDayOfWeek (m_nFirstDayOfWeek);

	m_DateTimePicker.SetDate (m_Date);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
