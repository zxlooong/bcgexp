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
// BCGPCalendarDemo.h : main header file for the BCGPCALENDARDEMO application
//

#if !defined(AFX_BCGPCALENDARDEMO_H__1452945C_B3C2_47E6_A389_E78834A43252__INCLUDED_)
#define AFX_BCGPCALENDARDEMO_H__1452945C_B3C2_47E6_A389_E78834A43252__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoApp:
// See BCGPCalendarDemo.cpp for the implementation of this class
//
class CCalendarOptions
{
public:
	CCalendarOptions();

	COLORREF			m_clrBackground;
	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE
						m_Type;
	int					m_ShowToolTip;	// 0 - don't show, 1 - standard, 2 - advanced
	BOOL				m_DefaultImages;
	BOOL				m_DefaultClockIcons;
	int					m_WorkFirstDayOfWeek;
	double				m_WorkHourFirst;
	double				m_WorkHourLast;
	CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA
						m_DayTimeDelta;
	BOOL				m_WeekDrawTimeFinish;
	BOOL				m_WeekDrawTimeIcons;
	BOOL				m_MonthDrawTimeFinish;
	BOOL				m_MonthDrawTimeIcons;
	BOOL				m_MonthCompressWeekend;

	BOOL				m_CalendarGradientFill;
	BOOL				m_CalendarWeekNumbers;	

	BOOL				m_UseDayInsteadWeek;
	BOOL				m_ScrollVisible;

	BOOL				m_bImagesChanged;
	BOOL				m_bClockIconsChanged;

	void Load ();
	void Save ();
};

class CBCGPCalendarDemoApp : public CWinApp
#ifndef _BCGPCALENDAR_STANDALONE
							,public CBCGPWorkspace
#endif
{
public:
	CBCGPCalendarDemoApp();

#ifndef _BCGPCALENDAR_STANDALONE
	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
#else
	int GetSectionInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault = 0);
	BOOL WriteSectionInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
#endif

	void UpdateCalendar (BOOL bUpdateCalendar = TRUE);

	CCalendarOptions	m_Options;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPCalendarDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPCalendarDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CBCGPCalendarDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCALENDARDEMO_H__1452945C_B3C2_47E6_A389_E78834A43252__INCLUDED_)
