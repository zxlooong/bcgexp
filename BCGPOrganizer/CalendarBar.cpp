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
// CalendarBar.cpp : implementation of the CCalendarBar class
//

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "CalendarBar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarBar

CCalendarBar::CCalendarBar()
{
}

CCalendarBar::~CCalendarBar()
{
}


BOOL CCalendarBar::Create(CWnd* pParentWnd, UINT nID)
{
	return CBCGPCalendar::Create (WS_CHILD | WS_VISIBLE, CRect (0, 0, 0, 0), pParentWnd, nID);
}


BEGIN_MESSAGE_MAP(CCalendarBar, CBCGPCalendar)
	//{{AFX_MSG_MAP(CCalendarBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarBar message handlers

int CCalendarBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPCalendar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	EnableMutipleSelection (TRUE, 35 /* Max sel days */, TRUE);
	EnableWeekNumbers ();

	UpdateCalendar ();
	return 0;
}

void CCalendarBar::UpdateCalendar ()
{
	int nFirstDayOfWeek = theApp.m_OptionsPlanner.m_WorkFirstDayOfWeek == -1
		? CBCGPPlannerManagerCtrl::GetSystemFirstDayOfWeek ()
		: theApp.m_OptionsPlanner.m_WorkFirstDayOfWeek;

	if (nFirstDayOfWeek != GetFirstDayOfWeek ())
	{
		SetFirstDayOfWeek (nFirstDayOfWeek);
	}

	EnableWeekNumbers (theApp.m_OptionsPlanner.m_CalendarWeekNumbers);
	EnableGradientFillCaption (theApp.m_OptionsPlanner.m_CalendarGradientFill);
}
