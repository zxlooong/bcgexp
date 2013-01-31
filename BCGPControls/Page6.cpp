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
// Page6.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcontrols.h"
#include "Page6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DTPICKER_DATE_TIME			0
#define DTPICKER_DATE				1
#define DTPICKER_TIME				2

#define DTPICKER_TIME_FORMAT_LOCALE	0
#define DTPICKER_TIME_FORMAT_24		1
#define DTPICKER_TIME_FORMAT_12		2

/////////////////////////////////////////////////////////////////////////////
// CPage6 property page

IMPLEMENT_DYNCREATE(CPage6, CBCGPPropertyPage)

CPage6::CPage6() : CBCGPPropertyPage(CPage6::IDD)
{
	//{{AFX_DATA_INIT(CPage6)
	m_bDurationDays = TRUE;
	m_bDurationHours = TRUE;
	m_bDurationSpin = TRUE;
	m_bDateTimeCheckBox = TRUE;
	m_bDateTimeDrop = TRUE;
	m_bDateTimeSpin = TRUE;
	m_bCalendarMultSel = TRUE;
	m_bCalendarShowWeekNumber = TRUE;
	m_nDateTimeParts = DTPICKER_DATE_TIME;
	m_nTimeFormat = DTPICKER_TIME_FORMAT_LOCALE;
	m_bDurationSeconds = FALSE;
	m_bCalendarShowToday = TRUE;
	//}}AFX_DATA_INIT
}

CPage6::~CPage6()
{
}

void CPage6::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage6)
	DDX_Control(pDX, IDC_WEEKSTART, m_weekStart);
	DDX_Control(pDX, IDC_DURATION, m_wndDuration);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_wndDateTimePicker);
	DDX_Control(pDX, IDC_CALENDARLOCATION, m_calendarLocation);
	DDX_Check(pDX, IDC_CHECKDAYS, m_bDurationDays);
	DDX_Check(pDX, IDC_CHECKHOURS, m_bDurationHours);
	DDX_Check(pDX, IDC_CHECKSPIN, m_bDurationSpin);
	DDX_Check(pDX, IDC_CAL_CHKBOX, m_bDateTimeCheckBox);
	DDX_Check(pDX, IDC_CAL_DROPBTN, m_bDateTimeDrop);
	DDX_Check(pDX, IDC_CAL_SPIN, m_bDateTimeSpin);
	DDX_Check(pDX, IDC_CALENDARBAR_MULTY, m_bCalendarMultSel);
	DDX_Check(pDX, IDC_CALENDARBAR_WEEKNOBND, m_bCalendarShowWeekNumber);
	DDX_Radio(pDX, IDC_DATETIME_PARTS, m_nDateTimeParts);
	DDX_Radio(pDX, IDC_TIME_FORMAT, m_nTimeFormat);
	DDX_Check(pDX, IDC_CHECKSECONDS, m_bDurationSeconds);
	DDX_Check(pDX, IDC_CALENDARBAR_TODAY_BUTTON, m_bCalendarShowToday);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage6, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CPage6)
	ON_BN_CLICKED(IDC_CHECKDAYS, SetDurationState)
	ON_BN_CLICKED(IDC_DURATION, OnDuration)
	ON_BN_CLICKED(IDC_CAL_CHKBOX, SetDateTimeState)
	ON_BN_CLICKED(IDC_DATETIMEPICKER1, OnDatetimepicker)
	ON_CBN_SELCHANGE(IDC_WEEKSTART, OnSelchangeWeekstart)
	ON_BN_CLICKED(IDC_DATETIME_PARTS, SetDateTimeState)
	ON_BN_CLICKED(IDC_CHECKHOURS, SetDurationState)
	ON_BN_CLICKED(IDC_CHECKSPIN, SetDurationState)
	ON_BN_CLICKED(IDC_CAL_DROPBTN, SetDateTimeState)
	ON_BN_CLICKED(IDC_CAL_SPIN, SetDateTimeState)
	ON_BN_CLICKED(IDC_CALENDARBAR_MULTY, SetCalendarBarSate)
	ON_BN_CLICKED(IDC_CALENDARBAR_WEEKNOBND, SetCalendarBarSate)
	ON_BN_CLICKED(IDC_DATETIME_PARTS2, SetDateTimeState)
	ON_BN_CLICKED(IDC_DATETIME_PARTS3, SetDateTimeState)
	ON_BN_CLICKED(IDC_TIME_FORMAT, SetDateTimeState)
	ON_BN_CLICKED(IDC_TIME_FORMAT2, SetDateTimeState)
	ON_BN_CLICKED(IDC_TIME_FORMAT3, SetDateTimeState)
	ON_BN_CLICKED(IDC_CHECKSECONDS, SetDurationState)
	ON_BN_CLICKED(IDC_CALENDARBAR_TODAY_BUTTON, SetCalendarBarSate)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_CALENDAR_ON_SELCHANGED, OnCalendarSelectionChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage6 message handlers

BOOL CPage6::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog ();

	UpdateData (FALSE);

	int i = 0;
	
	//-------------------------
	// Create Calendar Control:
	//-------------------------
	CRect rectCalendar;
	m_calendarLocation.GetClientRect (&rectCalendar);
	m_calendarLocation.MapWindowPoints (this, &rectCalendar);

	m_wndCalendarCtrl.Create (WS_CHILD | WS_VISIBLE | WS_BORDER, 
		rectCalendar, this, (UINT)-1);

	m_wndCalendarCtrl.SetSingleMonthMode ();

	COleDateTime today = COleDateTime::GetCurrentTime ();

	//------------------------
	// Set bold (marked) days:
	//------------------------
	static int daysMarked [] = {	1, 8, 10, 15, 25, 28	};
	CArray<DATE, DATE&> arMarkedDates;

	for (i = 0; i < sizeof (daysMarked) / sizeof (int); i++)
	{
		COleDateTime dayBold (today.GetYear (), today.GetMonth (), daysMarked [i], 0, 0, 0);
		arMarkedDates.Add (dayBold.m_dt);
	}

	m_wndCalendarCtrl.MarkDates (arMarkedDates);

	//------------------
	// Set colored days:
	//------------------
	static int daysColor1 [] = {	4, 5, 6	};

	for (i = 0; i < sizeof (daysColor1) / sizeof (int); i++)
	{
		COleDateTime dayColor (today.GetYear (), today.GetMonth (), daysColor1 [i], 0, 0, 0);
		m_wndCalendarCtrl.SetDateColor (dayColor, RGB (255, 0, 0));
	}

	static int daysColor2 [] = {	19, 20, 23	};

	for (i = 0; i < sizeof (daysColor2) / sizeof (int); i++)
	{
		COleDateTime dayColor (today.GetYear (), today.GetMonth (), daysColor2 [i], 0, 0, 0);
		m_wndCalendarCtrl.SetDateColor (dayColor, RGB (0, 0, 255));
	}

	SetCalendarBarSate ();

	//-----------------------------
	// Initialize Date/time picker:
	//-----------------------------
	SetDateTimeState ();
	m_wndDateTimePicker.SizeToContent();

	SetDurationState ();

	//----------------------------
	// Fill "Week Days" combo box:
	//----------------------------
	COleDateTime t = COleDateTime::GetCurrentTime ();
	COleDateTimeSpan sp (t.GetDayOfWeek () - 1, 0, 0, 0);
	t -= sp;

	COleDateTimeSpan oneDay (1, 0, 0, 0);
	for (i = 0; i < 7; i ++)
	{
		m_weekStart.AddString (t.Format (_T("%A")));
		t += oneDay;
	}

	m_weekStart.SetCurSel (m_wndCalendarCtrl.GetFirstDayOfWeek ());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//**************************************************************************************
void CPage6::SetDurationState()
{
	UpdateData ();

	UINT showFlags = 0;

	if (m_bDurationDays)
	{
		showFlags |= CBCGPDurationCtrl::DRTN_DAYS;
	}

	if (m_bDurationHours)
	{
		showFlags |= CBCGPDurationCtrl::DRTN_HOURS_MINS;
	}

	if (m_bDurationSeconds)
	{
		showFlags |= CBCGPDurationCtrl::DRTN_SECONDS;
	}

	if (m_bDurationSpin)
	{
		showFlags |= CBCGPDurationCtrl::DRTN_SPIN;
	}

	const UINT showMask = 
		CBCGPDurationCtrl::DRTN_DAYS | 
		CBCGPDurationCtrl::DRTN_HOURS_MINS | 
		CBCGPDurationCtrl::DRTN_SECONDS | 
		CBCGPDurationCtrl::DRTN_SPIN;

	m_wndDuration.SetState (showFlags, showMask);

	OnDuration ();
}
//***************************************************************************************
void CPage6::OnDuration() 
{
}
//***************************************************************************************
void CPage6::SetDateTimeState() 
{
	UpdateData();

	UINT stateFlags = 0;

	if (m_bDateTimeSpin)
	{
		stateFlags |= CBCGPDateTimeCtrl::DTM_SPIN;
	}

	if (m_bDateTimeDrop)
	{
		stateFlags |= CBCGPDateTimeCtrl::DTM_DROPCALENDAR;
	}

	if (m_bDateTimeCheckBox)
	{
		stateFlags |= CBCGPDateTimeCtrl::DTM_CHECKBOX;
	}

	switch (m_nDateTimeParts)
	{
	case DTPICKER_DATE_TIME:
		stateFlags |= (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME);
		break;

	case DTPICKER_DATE:
		stateFlags |= CBCGPDateTimeCtrl::DTM_DATE;
		break;

	case DTPICKER_TIME:
		stateFlags |= CBCGPDateTimeCtrl::DTM_TIME;
		break;
	}

	switch (m_nTimeFormat)
	{
	case DTPICKER_TIME_FORMAT_LOCALE:
		stateFlags |= CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;
		break;

	case DTPICKER_TIME_FORMAT_24:
		stateFlags |= CBCGPDateTimeCtrl::DTM_TIME24H;
		break;
	}

	const UINT stateMask = 
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME | 
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;

	m_wndDateTimePicker.SetState (stateFlags, stateMask);
	OnDatetimepicker();
}
//***************************************************************************************
void CPage6::OnDatetimepicker() 
{
	COleDateTime dt = m_wndDateTimePicker.GetDate();
	//m_strDateTime = dt.Format(_T("%#x %X"));
	UpdateData(FALSE);
}
//***************************************************************************************
LRESULT CPage6::OnCalendarSelectionChanged(WPARAM /*wParam*/, LPARAM lParam) 
{
	if ((HWND) lParam == m_wndCalendarCtrl.GetSafeHwnd ())
	{
		CList<DATE, DATE&> lstSelDays;
		m_wndCalendarCtrl.GetSelectedDates (lstSelDays);
		
		CString str;
		str.Format(_T("Selected %d day(s)"), lstSelDays.GetCount ());
	}

	return 0;
}
//****************************************************************************************
void CPage6::SetCalendarBarSate() 
{
	UpdateData();

	m_wndCalendarCtrl.EnableMutipleSelection (m_bCalendarMultSel);
	m_wndCalendarCtrl.EnableTodayButton (m_bCalendarShowToday);
	m_wndCalendarCtrl.EnableWeekNumbers (m_bCalendarShowWeekNumber);
}
//**************************************************************************************
void CPage6::OnSelchangeWeekstart() 
{
	int nDay = m_weekStart.GetCurSel ();

	m_wndCalendarCtrl.SetFirstDayOfWeek (nDay);
    m_wndDateTimePicker.SetFirstDayOfWeek (nDay);
}
