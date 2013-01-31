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
// CalendarPlannerView.cpp : implementation file
//

#include "stdafx.h"
#include "../BCGPOrganizer.h"
#include "../BCGPOrganizerDoc.h"
#include "../mainfrm.h"

#include "CalendarPlannerView.h"

#include "../Planner/Appointment.h"
#include "../Planner/GotoDayDialog.h"
#include "../Planner/PrintTypeDlg.h"
#include "../Planner/AppointmentFrame.h"
#include "../Planner/RecurrenceConfirmDlg.h"
#include "../Planner/PlannerClockIcons.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const LPCTSTR s_szFileName = _T("organizer_calendar.dat");
const DWORD c_dwHeader = MAKELONG (MAKEWORD ('B', 'C'), MAKEWORD ('G', 'S'));

/////////////////////////////////////////////////////////////////////////////
// CCalendarPlannerView

IMPLEMENT_DYNCREATE(CCalendarPlannerView, CBCGPPlannerManagerView)

BEGIN_MESSAGE_MAP(CCalendarPlannerView, CBCGPPlannerManagerView)
	//{{AFX_MSG_MAP(CCalendarPlannerView)
	ON_COMMAND(ID_PLANNER_MODE_DAY, OnModeDay)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_DAY, OnUpdateModeDay)
	ON_COMMAND(ID_PLANNER_MODE_MONTH, OnModeMonth)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_MONTH, OnUpdateModeMonth)
	ON_COMMAND(ID_PLANNER_MODE_WEEK, OnModeWeek)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_WEEK, OnUpdateModeWeek)
	ON_COMMAND(ID_PLANNER_MODE_WORKWEEK, OnModeWorkweek)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_WORKWEEK, OnUpdateModeWorkweek)
	ON_COMMAND(ID_PLANNER_TIMELINE_60, OnTimeLine60)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_60, OnUpdateTimeLine60)
	ON_COMMAND(ID_PLANNER_TIMELINE_30, OnTimeLine30)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_30, OnUpdateTimeLine30)
	ON_COMMAND(ID_PLANNER_TIMELINE_20, OnTimeLine20)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_20, OnUpdateTimeLine20)
	ON_COMMAND(ID_PLANNER_TIMELINE_15, OnTimeLine15)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_15, OnUpdateTimeLine15)
	ON_COMMAND(ID_PLANNER_TIMELINE_10, OnTimeLine10)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_10, OnUpdateTimeLine10)
	ON_COMMAND(ID_PLANNER_TIMELINE_6, OnTimeLine6)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_6, OnUpdateTimeLine6)
	ON_COMMAND(ID_PLANNER_TIMELINE_5, OnTimeLine5)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_5, OnUpdateTimeLine5)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMESCALE, OnUpdateTimeScale)
	ON_COMMAND(ID_GOTO_TODAY, OnGotoToday)
	ON_UPDATE_COMMAND_UI(ID_GOTO_TODAY, OnUpdateGotoToday)
	ON_COMMAND(ID_GOTO_THISDAY, OnGotoThisday)
	ON_UPDATE_COMMAND_UI(ID_GOTO_THISDAY, OnUpdateGotoThisday)
	ON_COMMAND(ID_GOTO_DAY, OnGotoDay)
	ON_UPDATE_COMMAND_UI(ID_GOTO_DAY, OnUpdateGotoDay)
	ON_COMMAND(ID_PLANNER_COMPRESS_WEEKEND, OnCompressWeekend)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_COMPRESS_WEEKEND, OnUpdateCompressWeekend)
	ON_COMMAND(ID_PLANNER_DRAW_TIME_FINISH, OnDrawTimeFinish)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_DRAW_TIME_FINISH, OnUpdateDrawTimeFinish)
	ON_COMMAND(ID_PLANNER_DRAW_TIME_AS_ICONS, OnDrawTimeAsIcons)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_DRAW_TIME_AS_ICONS, OnUpdateDrawTimeAsIcons)
	ON_COMMAND(ID_PLANNER_DRAW_APP_GRADIENT, OnDrawAppGradient)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_DRAW_APP_GRADIENT, OnUpdateDrawAppGradient)
	ON_COMMAND(ID_PLANNER_DRAW_APP_ROUNDED, OnDrawAppRounded)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_DRAW_APP_ROUNDED, OnUpdateDrawAppRounded)
	ON_COMMAND(ID_PLANNER_DRAW_APP_DURATION, OnDrawAppDuration)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_DRAW_APP_DURATION, OnUpdateDrawAppDuration)
	ON_COMMAND(ID_PLANNER_SHOWTOOLTIP, OnShowToolTip)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_SHOWTOOLTIP, OnUpdateShowToolTip)
	ON_COMMAND(ID_PLANNER_OPEN_APP, OnPlannerOpenApp)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_OPEN_APP, OnUpdatePlannerOpenApp)
	ON_COMMAND(ID_PLANNER_REMOVE_APP, OnPlannerRemoveApp)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_REMOVE_APP, OnUpdatePlannerRemoveApp)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_PLANNER_NEW, OnPlannerNewAppointment)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_NEW_APPOINTMENT, OnPlannerNewAppointment)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW_APPOINTMENT, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_NEW_EVENT, OnPlannerNewEvent)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW_EVENT, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_NEW_REC_APPOINTMENT, OnPlannerNewRecAppointment)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW_REC_APPOINTMENT, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_NEW_REC_EVENT, OnPlannerNewRecEvent)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW_REC_EVENT, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_DRAW_BACKGROUND, OnDrawBackground)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_DRAW_BACKGROUND, OnUpdateDrawBackground)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CBCGPPlannerManagerView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPPlannerManagerView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_REGISTERED_MESSAGE(BCGM_ON_HIGHLIGHT_RIBBON_LIST_ITEM, OnHighlightRibbonListItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarPlannerView construction/destruction

CCalendarPlannerView::CCalendarPlannerView()
	: m_bFirstTime      (TRUE)
	, m_LastClickedTime ()
	, m_dwVersion       ()
{
}

CCalendarPlannerView::~CCalendarPlannerView()
{
}

BOOL CCalendarPlannerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPPlannerManagerView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarPlannerView printing

void CCalendarPlannerView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CCalendarPlannerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	CRuntimeClass* pPrinterClass = NULL;

	if (!pInfo->m_bPreview)
	{
		CPrintTypeDlg dlg (AfxGetMainWnd ());

		switch (GetType ())
		{
		case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY:
			dlg.SetType (GetViewDuration () == 1 ? 0 : 3);
			break;
		case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK:
			dlg.SetType (1);
			break;
		case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK:
			dlg.SetType (1);
			break;
		case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH:
			dlg.SetType (2);
			break;
		}

		if (dlg.DoModal () != IDOK)
		{
			return FALSE;
		}
		else
		{
			switch (dlg.GetType ())
			{
			case 0:
				pPrinterClass = RUNTIME_CLASS(CBCGPPlannerPrintDay);
				break;
			case 1:
				pPrinterClass = RUNTIME_CLASS(CBCGPPlannerPrintWeek);
				break;
			case 2:
				pPrinterClass = RUNTIME_CLASS(CBCGPPlannerPrintMonth);
				break;
			case 3:
				pPrinterClass = RUNTIME_CLASS(CBCGPPlannerPrintDual);
				break;
			}
		}
	}

	GetManagerCtrl ().OnPreparePrinting (pInfo, pPrinterClass);

	return DoPreparePrinting(pInfo);
}

void CCalendarPlannerView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	GetManagerCtrl ().OnBeginPrinting (pDC, pInfo);
}

void CCalendarPlannerView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPPlannerManagerView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarPlannerView diagnostics

#ifdef _DEBUG
void CCalendarPlannerView::AssertValid() const
{
	CBCGPPlannerManagerView::AssertValid();
}

void CCalendarPlannerView::Dump(CDumpContext& dc) const
{
	CBCGPPlannerManagerView::Dump(dc);
}

CBCGPOrganizerDoc* CCalendarPlannerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPOrganizerDoc)));
	return (CBCGPOrganizerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCalendarPlannerView message handlers

void CCalendarPlannerView::OnContextMenu(CWnd*, CPoint point)
{
	UINT nID = 0;

	CPoint pt (point);
	ScreenToClient (&pt);

	CBCGPPlannerView::BCGP_PLANNER_HITTEST nHit = HitTest (pt);

	if (nHit >= CBCGPPlannerView::BCGP_PLANNER_HITTEST_APPOINTMENT)
	{
		nID = IDR_PLANNER_APPOINTMENT;
	}
	else if (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_TIMEBAR)
	{
		nID = IDR_PLANNER_TIMEBAR;
	}
	else if (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_CLIENT ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_DAY_CAPTION ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_ICON_UP ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_ICON_DOWN)
	{
		if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY)
		{
			nID = (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_CLIENT ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY)
					? IDR_PLANNER_CLIENT_DAY
					: IDR_PLANNER_TIMEBAR;
		}
		else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK)
		{
			nID = (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_CLIENT ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY)
					? IDR_PLANNER_CLIENT_WORK_WEEK
					: IDR_PLANNER_TIMEBAR;
		}
		else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
		{
			nID = IDR_PLANNER_CLIENT_WEEK;
		}
		else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
		{
			if (nHit != CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER)
			{
				nID = IDR_PLANNER_CLIENT_MONTH;
			}
		}

		m_LastClickedTime = GetDateFromPoint (pt);
	}

	if (nID != 0)
	{
		theApp.ShowPopupMenu (nID, point, this);
	}
}

void CCalendarPlannerView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/) 
{
	CBCGPOrganizerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	GetManagerCtrl ().SetDateInterval (pDoc->GetDate1 (), pDoc->GetDate2 ());

	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetType ();

	if (theApp.m_OptionsPlanner.m_Type != type && !m_bFirstTime)
	{
		theApp.m_OptionsPlanner.m_Type = type;
		theApp.UpdateCalendar (FALSE);
	}
}

void CCalendarPlannerView::OnModeDay() 
{
	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY);
}

void CCalendarPlannerView::OnUpdateModeDay(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == 
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY);
}

void CCalendarPlannerView::OnModeMonth() 
{
	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
}

void CCalendarPlannerView::OnUpdateModeMonth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == 
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
}

void CCalendarPlannerView::OnModeWeek() 
{
	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK);
}

void CCalendarPlannerView::OnUpdateModeWeek(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == 
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK);
}

void CCalendarPlannerView::OnModeWorkweek() 
{
	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
}

void CCalendarPlannerView::OnUpdateModeWorkweek(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
}

void CCalendarPlannerView::OnTimeLine60()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_60);
}

void CCalendarPlannerView::OnUpdateTimeLine60(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_60);
}

void CCalendarPlannerView::OnTimeLine30()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_30);
}

void CCalendarPlannerView::OnUpdateTimeLine30(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_30);
}

void CCalendarPlannerView::OnTimeLine20()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_20);
}

void CCalendarPlannerView::OnUpdateTimeLine20(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_20);
}

void CCalendarPlannerView::OnTimeLine15()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_15);
}

void CCalendarPlannerView::OnUpdateTimeLine15(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_15);
}

void CCalendarPlannerView::OnTimeLine10()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_10);
}

void CCalendarPlannerView::OnUpdateTimeLine10(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_10);
}

void CCalendarPlannerView::OnTimeLine6()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_6);
}

void CCalendarPlannerView::OnUpdateTimeLine6(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_6);
}

void CCalendarPlannerView::OnTimeLine5()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_5);
}

void CCalendarPlannerView::OnUpdateTimeLine5(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_5);
}

void CCalendarPlannerView::OnUpdateTimeScale (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
}

void CCalendarPlannerView::OnGotoToday() 
{
	SetToday ();
}

void CCalendarPlannerView::OnUpdateGotoToday(CCmdUI* pCmdUI) 
{
	COleDateTime d1 (GetManagerCtrl ().GetDate ());
	COleDateTime d2 (COleDateTime::GetCurrentTime ());

	pCmdUI->Enable (
		d1.GetDay () != d2.GetDay () ||
		d1.GetMonth () != d2.GetMonth () ||
		d1.GetYear () != d2.GetYear ());
}

void CCalendarPlannerView::OnGotoThisday() 
{
	COleDateTime day (m_LastClickedTime);

	if (day == COleDateTime ())
	{
		day = GetDate ();
	}

	m_LastClickedTime = COleDateTime ();

	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY);

	CBCGPOrganizerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetDateInterval (day, day);
}

void CCalendarPlannerView::OnUpdateGotoThisday(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK ||
		GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);	
}

void CCalendarPlannerView::OnGotoDay() 
{
	CGotoDayDialog dlg(GetDate (), GetType (), 
		CBCGPPlannerManagerCtrl::GetFirstDayOfWeek (), this);

	if (dlg.DoModal () == IDOK)
	{
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = dlg.GetType ();
		COleDateTime dt (dlg.GetDate ());

		if (GetType () == type && GetDate () == dt)
		{
			return;
		}

		if (GetType () != type)
		{
			GetManagerCtrl ().SetType (type, FALSE);

			theApp.m_OptionsPlanner.m_Type = type;
			theApp.UpdateCalendar (FALSE);
		}

		GetManagerCtrl ().SetDate (dt, FALSE);
		GetManagerCtrl ().RedrawWindow ();
	}
}

void CCalendarPlannerView::OnUpdateGotoDay(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command handler code here
}

void CCalendarPlannerView::OnCompressWeekend() 
{
	SetCompressWeekend (!IsCompressWeekend ());

	theApp.m_OptionsPlanner.m_MonthCompressWeekend = IsCompressWeekend ();
	theApp.UpdateCalendar (FALSE);
}

void CCalendarPlannerView::OnUpdateCompressWeekend(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
	pCmdUI->SetCheck (IsCompressWeekend ());
}

void CCalendarPlannerView::OnDrawTimeFinish() 
{
	SetDrawTimeFinish (!IsDrawTimeFinish ());
	
	if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
	{
		theApp.m_OptionsPlanner.m_WeekDrawTimeFinish = IsDrawTimeFinish ();
	}
	else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
	{
		theApp.m_OptionsPlanner.m_MonthDrawTimeFinish = IsDrawTimeFinish ();
	}

	theApp.UpdateCalendar (FALSE);
}

void CCalendarPlannerView::OnUpdateDrawTimeFinish(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK ||
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
	pCmdUI->SetCheck (IsDrawTimeFinish ());
}

void CCalendarPlannerView::OnDrawTimeAsIcons() 
{
	SetDrawTimeAsIcons (!IsDrawTimeAsIcons ());

	if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
	{
		theApp.m_OptionsPlanner.m_WeekDrawTimeIcons = IsDrawTimeAsIcons ();
	}
	else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
	{
		theApp.m_OptionsPlanner.m_MonthDrawTimeIcons = IsDrawTimeAsIcons ();
	}

	theApp.UpdateCalendar (FALSE);
}

void CCalendarPlannerView::OnUpdateDrawTimeAsIcons(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK ||
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
	pCmdUI->SetCheck (IsDrawTimeAsIcons ());
}

void CCalendarPlannerView::OnDrawAppGradient()
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();
	DWORD dwFlags = rMan.GetDrawFlags ();

	if ((dwFlags & BCGP_PLANNER_DRAW_APP_GRADIENT_FILL) ==
		BCGP_PLANNER_DRAW_APP_GRADIENT_FILL)
	{
		dwFlags &= ~BCGP_PLANNER_DRAW_APP_GRADIENT_FILL;
	}
	else
	{
		dwFlags |= BCGP_PLANNER_DRAW_APP_GRADIENT_FILL;
	}

	rMan.SetDrawFlags (dwFlags);

	theApp.m_OptionsPlanner.m_DrawFlags = dwFlags;
	theApp.UpdateCalendar (FALSE);
}

void CCalendarPlannerView::OnUpdateDrawAppGradient(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (
		(GetManagerCtrl ().GetDrawFlags () & BCGP_PLANNER_DRAW_APP_GRADIENT_FILL) ==
			BCGP_PLANNER_DRAW_APP_GRADIENT_FILL);
}

void CCalendarPlannerView::OnDrawAppRounded()
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();
	DWORD dwFlags = rMan.GetDrawFlags ();

	if ((dwFlags & BCGP_PLANNER_DRAW_APP_ROUNDED_CORNERS) ==
		BCGP_PLANNER_DRAW_APP_ROUNDED_CORNERS)
	{
		dwFlags &= ~BCGP_PLANNER_DRAW_APP_ROUNDED_CORNERS;
	}
	else
	{
		dwFlags |= BCGP_PLANNER_DRAW_APP_ROUNDED_CORNERS;
	}

	rMan.SetDrawFlags (dwFlags);

	theApp.m_OptionsPlanner.m_DrawFlags = dwFlags;
	theApp.UpdateCalendar (FALSE);
}

void CCalendarPlannerView::OnUpdateDrawAppRounded(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (
		(GetManagerCtrl ().GetDrawFlags () & BCGP_PLANNER_DRAW_APP_ROUNDED_CORNERS) ==
			BCGP_PLANNER_DRAW_APP_ROUNDED_CORNERS);
}

void CCalendarPlannerView::OnDrawAppDuration()
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();
	DWORD dwFlags = rMan.GetDrawFlags ();

	if ((dwFlags & BCGP_PLANNER_DRAW_VIEW_NO_DURATION) ==
		BCGP_PLANNER_DRAW_VIEW_NO_DURATION)
	{
		dwFlags &= ~BCGP_PLANNER_DRAW_APP_DURATION_SHAPE;
		dwFlags &= ~BCGP_PLANNER_DRAW_VIEW_NO_DURATION;
	}
	else
	{
		dwFlags |= BCGP_PLANNER_DRAW_VIEW_NO_DURATION;
		dwFlags |= BCGP_PLANNER_DRAW_APP_DURATION_SHAPE;
	}

	rMan.SetDrawFlags (dwFlags);

	theApp.m_OptionsPlanner.m_DrawFlags = dwFlags;
	theApp.UpdateCalendar (FALSE);
}

void CCalendarPlannerView::OnUpdateDrawAppDuration(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY ||
		GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
	pCmdUI->SetCheck (
		(GetManagerCtrl ().GetDrawFlags () & BCGP_PLANNER_DRAW_VIEW_NO_DURATION) ==
			0);
}

void CCalendarPlannerView::OnShowToolTip() 
{
	GetManagerCtrl ().SetShowToolTip (!GetManagerCtrl ().IsShowToolTip ());
	
	theApp.m_OptionsPlanner.m_ShowToolTip = GetManagerCtrl ().IsShowToolTip ();

	theApp.UpdateCalendar (FALSE);
}

void CCalendarPlannerView::OnUpdateShowToolTip(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (GetManagerCtrl ().IsShowToolTip ());
}

void CCalendarPlannerView::OnPlannerOpenApp() 
{
	if (GetManagerCtrl ().GetSelectedAppointmentsCount () == 1)
	{
		POSITION pos = GetManagerCtrl ().GetFirstSelectedAppointment ();
		CBCGPAppointment* pApp = const_cast<CBCGPAppointment*>(
			GetManagerCtrl ().GetNextSelectedAppointment (pos));

		AddEditAppointment (pApp);
	}
}

void CCalendarPlannerView::OnUpdatePlannerOpenApp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetManagerCtrl ().GetSelectedAppointmentsCount () == 1);
}

void CCalendarPlannerView::OnPlannerRemoveApp() 
{
	if (GetManagerCtrl ().GetSelectedAppointmentsCount () > 0)
	{
		GetManagerCtrl ().RemoveSelectedAppointments ();
	}
}

void CCalendarPlannerView::OnUpdatePlannerRemoveApp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetManagerCtrl ().GetSelectedAppointmentsCount () > 0);
}

void CCalendarPlannerView::OnEditPaste() 
{
	if (GetManagerCtrl ().IsEditPasteEnabled ())
	{
		GetManagerCtrl ().EditPaste (m_LastClickedTime);

		m_LastClickedTime = COleDateTime ();
	}		
}

void CCalendarPlannerView::AddEditAppointment (CBCGPAppointment* pApp, 
												BOOL bAllDay /*= FALSE*/,
												BOOL bNewRecur /*= FALSE*/)
{
	CBCGPAppointment* pAppEdit = pApp;
	CBCGPRecurrenceBaseRule* pOldRule = NULL;

	BOOL bAdd = pAppEdit == NULL;
	BOOL bEcp = FALSE;
	
	COleDateTime dtOld;

	if (bAdd)
	{
		COleDateTime dtS (GetManagerCtrl ().GetSelectionStart ());
		COleDateTime dtF (GetManagerCtrl ().GetSelectionEnd ());

		if (dtF < dtS)
		{
			COleDateTime dt (dtS);
			dtS = dtF;
			dtF = dt;
		}

		if (!bAllDay)
		{
			CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetType ();

			if (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK || 
				type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
			{
				if (dtS.GetDayOfYear () == dtF.GetDayOfYear ())
				{
					dtS = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
						GetManagerCtrl ().GetFirstWorkingHour (), 0, 0);
					dtF = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
						GetManagerCtrl ().GetFirstWorkingHour () + 1, 0, 0);
				}
				else
				{
					bAllDay = TRUE;
				}
			}
			else
			{
				dtF += COleDateTimeSpan (0, 0, 0, 1);
			}
		}

		pAppEdit = new CAppointment (
					dtS, dtF, _T(""),
					CLR_DEFAULT,
					CLR_DEFAULT,
					bAllDay ? CLR_DEFAULT : RGB (0, 0, 255));

		ASSERT_VALID(pAppEdit);

		if (bAllDay)
		{
			pAppEdit->SetAllDay (TRUE);
		}
	}
	else
	{
		bNewRecur = FALSE;

		if (pAppEdit->IsRecurrence ())
		{
			if (pAppEdit->IsRecurrenceClone ())
			{
				CRecurrenceConfirmDlg dlg (pAppEdit->GetDescription (), TRUE, this);

				if (dlg.DoModal () != IDOK)
				{
					return;
				}

				if (!dlg.IsOnlyOccurrence ())
				{
					pAppEdit = GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ());
					ASSERT_VALID(pAppEdit);
				}
			}

			if (pAppEdit->IsRecurrenceClone ())
			{
				pOldRule = GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ())->
					GetRecurrence ()->GetRule ();
				bEcp = !GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ())->
					GetRecurrence ()->IsExceptionsCollectionEmpty ();
			}
			else
			{
				pOldRule = pAppEdit->GetRecurrence ()->GetRule ();
				bEcp = !pAppEdit->GetRecurrence ()->IsExceptionsCollectionEmpty ();
			}

			ASSERT_VALID(pOldRule);
		}

		dtOld = pAppEdit->GetStart ();
	}

	ASSERT_VALID (pAppEdit);

	CAppointmentFrame dlg (*pAppEdit, pOldRule, bEcp, bNewRecur, 
		IsReadOnly (), this);
	if (dlg.DoModal () != IDOK)
	{
		if (bAdd)
		{
			delete pAppEdit;
		}
		else
		{
			if (dlg.IsDeleted ())
			{
				GetManagerCtrl ().RemoveSelectedAppointments ();
			}
		}

		return;
	}

	if (IsReadOnly ())
	{
		return;
	}

	const CBCGPRecurrenceBaseRule* pRule = dlg.GetRule ();

	if (bAdd)
	{
		if (pRule != NULL)
		{	
			pAppEdit->SetRecurrenceRule (pRule);
		}

		GetManagerCtrl ().AddAppointment (pAppEdit, TRUE, TRUE);
	}
	else
	{
		if (pAppEdit->IsRecurrence ())
		{
			if (!pAppEdit->IsRecurrenceClone ())
			{
				if (pRule == NULL)
				{
					// recurrence appointment -> ordinary appointment
					CBCGPAppointment* pApp = pAppEdit->CreateCopy ();

					GetManagerCtrl ().RemoveAppointment (pAppEdit, FALSE, FALSE);
					pAppEdit = pApp;
					GetManagerCtrl ().AddAppointment (pAppEdit, TRUE, TRUE);

					return;
				}
				else if (*pOldRule != *pRule)
				{
					// update rule
					pAppEdit->SetRecurrenceRule (pRule);
					pAppEdit->UpdateRecurrence ();
				}
			}
			else
			{
				if (pRule == NULL)
				{
					// cloned appointment -> ordinary appointment
					CBCGPAppointment* pApp = pAppEdit->CreateCopy ();

					pAppEdit = GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ());
					ASSERT_VALID(pAppEdit);

					GetManagerCtrl ().RemoveAppointment (pAppEdit, FALSE, FALSE);
					pAppEdit = pApp;
					GetManagerCtrl ().AddAppointment (pAppEdit, TRUE, TRUE);

					return;
				}
				else if (*pOldRule != *pRule)
				{
					// cloned appointment -> recurrence appointment
					CBCGPAppointmentPropertyList props;
					pAppEdit->GetProperties (props);

					pAppEdit = GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ());
					ASSERT_VALID(pAppEdit);
					pAppEdit->SetProperties (props);

					pAppEdit->SetRecurrenceRule (pRule);
				}
			}
		}
		else
		{
			if (pRule != NULL)
			{
				// ordinary appointment -> recurrence appointment
				CBCGPAppointment* pApp = pAppEdit->CreateCopy ();

				GetManagerCtrl ().RemoveAppointment (pAppEdit, FALSE, FALSE);

				pAppEdit = pApp;

				pAppEdit->SetRecurrenceRule (pRule);

				GetManagerCtrl ().AddAppointment (pAppEdit, TRUE, TRUE);

				return;
			}
		}

		if(!GetManagerCtrl ().UpdateAppointment (pAppEdit, dtOld, TRUE, FALSE))
		{
			GetManagerCtrl ().QueryAppointments ();
		}

		GetManagerCtrl ().AdjustLayout (TRUE);
	}
}

void CCalendarPlannerView::OnDblClkCtrl (UINT /*nFlags*/, CPoint point)
{
	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetType ();
	CBCGPPlannerView::BCGP_PLANNER_HITTEST hit = GetManagerCtrl ().HitTest (point);

	if (hit != CBCGPPlannerView::BCGP_PLANNER_HITTEST_NOWHERE &&
		!((hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
		   hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_WEEKBAR ||
		   hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_WEEK_CAPTION) &&
		 type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH))
	{
		CBCGPAppointment* pApp = GetManagerCtrl ().GetAppointmentFromPoint (point);

		BOOL bAllDay = (((type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
			              type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK) &&
			             (hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
						  hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY)) ||
		                (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK || 
			             type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH));

		AddEditAppointment (pApp, bAllDay);
	}
}

void CCalendarPlannerView::OnKeyDownCtrl(UINT nChar, UINT /*nRepCnt*/, UINT /*nFlags*/) 
{
	if ((VK_F1 <= nChar && nChar <= VK_F12) || IsReadOnly ())
	{
		return;
	}

	if (_istalpha (nChar) || _istdigit (nChar) || nChar == VK_RETURN)
	{
		if (GetManagerCtrl ().GetSelectedAppointmentsCount () == 1)
		{
			POSITION pos = GetManagerCtrl ().GetFirstSelectedAppointment ();
			CBCGPAppointment* pApp = const_cast<CBCGPAppointment*>(
				GetManagerCtrl ().GetNextSelectedAppointment (pos));

			AddEditAppointment (pApp);

			return;
		}

		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetType ();

		BOOL bAllDay = (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK || 
						type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);

		AddEditAppointment (NULL, bAllDay);

		return;
	}
	else if (nChar == VK_DELETE)
	{
		GetManagerCtrl ().RemoveSelectedAppointments ();
	}

	return;
}

void CCalendarPlannerView::OnAppointmentAdded (CBCGPAppointment* /*pApp*/)
{
	CBCGPOrganizerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetModifiedFlag ();
}

UINT CCalendarPlannerView::OnUpdateAppointment (CBCGPAppointment* /*pApp*/)
{
	return 0L;
}

void CCalendarPlannerView::OnAppointmentUpdated (CBCGPAppointment* /*pApp*/)
{
	CBCGPOrganizerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetModifiedFlag ();
}

UINT CCalendarPlannerView::OnRemoveAppointment (CBCGPAppointment* pApp)
{
	CBCGPOrganizerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetModifiedFlag ();

	LRESULT lResult = 0L;

	if (GetManagerCtrl().GetChangeOperation () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_CHANGE_OPERATION_NONE &&
		pApp != NULL && pApp->IsRecurrenceClone ())
	{
		CRecurrenceConfirmDlg dlg (pApp->GetDescription (), FALSE, this);

		if (dlg.DoModal () != IDOK)
		{
			lResult = LRESULT(-1L);
		}
		else
		{
			lResult = dlg.IsOnlyOccurrence () ? 0L : 1L;
		}
	}

	return (UINT)lResult;
}

void CCalendarPlannerView::OnAllAppointmentsRemoved ()
{
	CBCGPOrganizerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetModifiedFlag ();
}

void CCalendarPlannerView::OnInitialUpdate() 
{
	CBCGPPlannerManagerView::OnInitialUpdate();

	if (m_bFirstTime)
	{
		m_bFirstTime = FALSE;

		CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

		CMainFrame* pFrame = DYNAMIC_DOWNCAST (CMainFrame, GetTopLevelFrame ());
		if (pFrame != NULL)
		{
			rMan.SetCalendar (pFrame->GetCalendar ());
		}

		UpdateCalendar (theApp.m_OptionsPlanner, FALSE);
		rMan.SetDate (COleDateTime::GetCurrentTime (), FALSE);

		BOOL bCreateDemo = TRUE;
		if (_taccess(GetDocument ()->GetPath () + s_szFileName, 0) != -1)
		{
			bCreateDemo = !Load (GetDocument ()->GetPath (), TRUE);
		}

		if (bCreateDemo)
		{
			CreateDemo (TRUE);
		}

		rMan.SendMessage (WM_KEYDOWN, VK_HOME, 0);
	}
}

void CCalendarPlannerView::OnPlannerNewAppointment() 
{
	m_LastClickedTime = COleDateTime ();
	AddEditAppointment (NULL, FALSE, FALSE);
}

void CCalendarPlannerView::OnPlannerNewEvent() 
{
	m_LastClickedTime = COleDateTime ();
	AddEditAppointment (NULL, TRUE, FALSE);
}

void CCalendarPlannerView::OnPlannerNewRecAppointment() 
{
	m_LastClickedTime = COleDateTime ();
	AddEditAppointment (NULL, FALSE, TRUE);
}

void CCalendarPlannerView::OnPlannerNewRecEvent() 
{
	m_LastClickedTime = COleDateTime ();
	AddEditAppointment (NULL, TRUE, TRUE);
}

void CCalendarPlannerView::OnUpdatePlannerNew(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (!IsReadOnly ());
}

void CCalendarPlannerView::CreateDemo (BOOL bRedraw /*= TRUE*/)
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	COleDateTime dt (COleDateTime::GetCurrentTime ());
	dt = COleDateTime (dt.GetYear (), dt.GetMonth (), dt.GetDay (), 0, 0, 0);
	dt = CBCGPPlannerView::GetFirstWeekDay (dt, 2);//rMan.GetFirstDayOfWeek ());

	CAppointment* pApp = NULL;

	//--------------------------------------------------
	// Create multi day appointment: 
	//--------------------------------------------------
	pApp = new CAppointment
			(
				dt + COleDateTimeSpan (1,  9, 0, 0),
				dt + COleDateTimeSpan (3, 18, 0, 0),
				_T("Multi day"),
				CLR_DEFAULT,
				CLR_DEFAULT,
				c_ShowasColors[2]
			);
	pApp->AddImage (3);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	//--------------------------------------------------
	// Create all day appointment: 
	//--------------------------------------------------
	pApp = new CAppointment
			(
				dt + COleDateTimeSpan (2, 0, 0, 0),
				dt + COleDateTimeSpan (2, 0, 0, 0),
				_T("All day"),
				CLR_DEFAULT,
				CLR_DEFAULT,
				c_ShowasColors[2]
			);
	pApp->SetImportance (CAppointment::e_ImportanceLow);
	pApp->AddImage (3);
	pApp->SetAllDay (TRUE);

	rMan.AddAppointment (pApp, FALSE, FALSE);

	//--------------------------------------------------
	// Create recurring appointment: every week, on 
	// Monday, Wednesday and Friday, 9:00 AM -  9:15 AM
	//--------------------------------------------------
	pApp = new CAppointment
			(
				dt,
				dt,
				_T("Meeting"),
				c_CategoryColors[4],
				CLR_DEFAULT,
				c_ShowasColors[2]
			);
	pApp->AddImage (3);

	{
		CBCGPRecurrenceRuleWeekly* pRule = DYNAMIC_DOWNCAST(CBCGPRecurrenceRuleWeekly, 
			CBCGPPlannerManagerCtrl::CreateRule (BCGP_PLANNER_RULE_WEEKLY));
		pRule->SetDateStart (dt);
		pRule->SetTimeInterval (COleDateTimeSpan (0, 9, 0, 0), COleDateTimeSpan (0, 9, 15, 0));
		pRule->SetDays (CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_1 | 
			CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_3 |
			CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_5);

		pApp->SetRecurrenceRule (pRule);
		delete pRule;
	}

	rMan.AddAppointment (pApp, FALSE, FALSE);

	//--------------------------------------------------------
	// Create recurring appointment: every weekday, 2 weeks
	// 6:0 PM-8:00 PM:
	//--------------------------------------------------------
	pApp = new CAppointment
				(
					dt,
					dt,
					_T("Training"),
					CLR_DEFAULT,
					CLR_DEFAULT,
					c_ShowasColors[3]
				);

	{
		CBCGPRecurrenceRuleDaily* pRule = DYNAMIC_DOWNCAST(CBCGPRecurrenceRuleDaily, 
			CBCGPPlannerManagerCtrl::CreateRule (BCGP_PLANNER_RULE_DAILY));
		pRule->SetDateStart (dt);
		pRule->SetTimeInterval (COleDateTimeSpan (0, 18, 0, 0), COleDateTimeSpan (0, 20, 0, 0));
		pRule->SetType (CBCGPRecurrenceRuleDaily::BCGP_REC_RULE_DAILY_TYPE_WEEKDAYS);

		pRule->SetLimitType (CBCGPRecurrenceRuleDaily::BCGP_RECURRENCE_RULE_LIMIT_COUNT);
		pRule->SetLimitCount (10);

		pApp->SetRecurrenceRule (pRule);
		delete pRule;
	}

	rMan.AddAppointment (pApp, FALSE, FALSE);

	//-----------------------------------------------------
	// Create single appointment: 1-st day of week, 8:15 AM:
	//-----------------------------------------------------
	dt += COleDateTimeSpan (1, 0, 0, 0);

	pApp = new CAppointment
			(
				dt + COleDateTimeSpan (0,  8, 15, 0),
				dt + COleDateTimeSpan (0,  8, 15, 0),
				_T("Phone call"),
				c_CategoryColors[5],
				CLR_DEFAULT,
				c_ShowasColors[3]
			);
	pApp->SetImportance (CAppointment::e_ImportanceHigh);
	pApp->SetPrivate ();
	pApp->AddImage (5);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	dt += COleDateTimeSpan (1, 0, 0, 0);
	
	//-----------------------------------------------------
	// Create single appointment: 2-nd day of week, 9:30 AM:
	//-----------------------------------------------------
	rMan.AddAppointment
		(
			new CAppointment
			(
				dt + COleDateTimeSpan (0,  9, 30, 0),
				dt + COleDateTimeSpan (0, 12,  0, 0),
				_T("Briefing"),
				c_CategoryColors[0],
				CLR_DEFAULT,
				c_ShowasColors[2]
			),
			FALSE, FALSE
		);

	dt += COleDateTimeSpan (1, 0, 0, 0);

	//-----------------------------------------------------
	// Create single appointment: 3-d day of week, 2:00 PM:
	//-----------------------------------------------------
	pApp = new CAppointment
			(
				dt + COleDateTimeSpan (0, 14, 30, 0),
				dt + COleDateTimeSpan (0, 15,  0, 0),
				_T("Meeting (friends)"),
				c_CategoryColors[1],
				CLR_DEFAULT,
				c_ShowasColors[3]
			);
	pApp->SetPrivate ();
	pApp->AddImage (3);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	dt += COleDateTimeSpan (1, 0, 0, 0);

	//-----------------------------------------------------
	// Create single appointment: 4-th day of week, 3:30 PM:
	//-----------------------------------------------------
	pApp = new CAppointment
			(
				dt + COleDateTimeSpan (0, 15, 30, 0),
				dt + COleDateTimeSpan (0, 17,  0, 0),
				_T("Business lunch"),
				c_CategoryColors[2],
				CLR_DEFAULT,
				c_ShowasColors[2]
			);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	dt += COleDateTimeSpan (2, 0, 0, 0);

	//-----------------------------------------------------
	// Create single appointment: 6 day of week, 2:00 PM:
	//-----------------------------------------------------
	pApp = new CAppointment
			(
				dt + COleDateTimeSpan (0, 14,  0, 0),
				dt + COleDateTimeSpan (0, 18,  0, 0),
				_T("John's birthday"),
				c_CategoryColors[3],
				CLR_DEFAULT,
				c_ShowasColors[3]
			);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	rMan.QueryAppointments ();
	rMan.AdjustLayout (bRedraw);
	rMan.UpdateCalendarsState ();

	GetDocument ()->SetModifiedFlag (FALSE);
}

int CCalendarPlannerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPPlannerManagerView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	if (theApp.m_OptionsPlanner.m_WorkFirstDayOfWeek != -1)
	{
		rMan.SetFirstDayOfWeek (theApp.m_OptionsPlanner.m_WorkFirstDayOfWeek);
	}

	rMan.SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);

	return 0;
}

void CCalendarPlannerView::OnDateChanged ()
{
	UpdateCaptionText ();
}

void CCalendarPlannerView::OnTypeChanged (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE /*oldType*/,
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE /*newType*/)
{
	theApp.m_OptionsPlanner.m_Type = GetType ();
	theApp.UpdateCalendar (FALSE);
	theApp.UpdateCalendar ();

	OnDateChanged ();
}

void CCalendarPlannerView::SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA delta)
{
	theApp.m_OptionsPlanner.m_DayTimeDelta = delta;
	theApp.UpdateCalendar (FALSE);
	theApp.UpdateCalendar ();
}

void CCalendarPlannerView::UpdateCalendar (const CPlannerOptions& options, BOOL bRedraw /*= TRUE*/)
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	rMan.SetRedraw (FALSE);

	if (options.m_Type != GetType ())
	{
		rMan.SetType (options.m_Type, FALSE);
		OnNotifyDateChanged (0, 0);
	}
	rMan.SetBackgroundColor (options.m_clrBackground);

	DWORD drawFlags = options.m_DrawFlags;
	if (drawFlags == (DWORD)-1)
	{
		drawFlags = CBCGPVisualManager::GetInstance ()->GetPlannerDrawFlags ();
	}

	if (drawFlags != rMan.GetDrawFlags ())
	{
		rMan.SetDrawFlags (drawFlags);
	}

	int nFirstDayOfWeek = options.m_WorkFirstDayOfWeek == -1
		? CBCGPPlannerManagerCtrl::GetSystemFirstDayOfWeek ()
		: options.m_WorkFirstDayOfWeek;

	if (nFirstDayOfWeek != rMan.GetFirstDayOfWeek ())
	{
		rMan.SetFirstDayOfWeek (nFirstDayOfWeek);
		OnNotifyDateChanged (0, 0);
	}

	rMan.SetWorkingHourMinuteInterval (options.m_WorkHourFirst, options.m_WorkHourLast, FALSE);

	if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY ||
		GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK)
	{
		rMan.SetTimeDelta (options.m_DayTimeDelta, FALSE);
	}
	else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
	{
		rMan.SetDrawTimeFinish (options.m_WeekDrawTimeFinish);
		rMan.SetDrawTimeAsIcons (options.m_WeekDrawTimeIcons);
	}
	else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
	{
		rMan.SetDrawTimeFinish (options.m_MonthDrawTimeFinish);
		rMan.SetDrawTimeAsIcons (options.m_MonthDrawTimeIcons);
		rMan.SetCompressWeekend (options.m_MonthCompressWeekend);
	}

	CWindowDC dc (NULL);
	int nBitsPerPixel = dc.GetDeviceCaps (BITSPIXEL);

	if (options.m_bImagesChanged)
	{
		(const_cast<CPlannerOptions&>(options)).m_bImagesChanged = FALSE;

		if (nBitsPerPixel > 8)
		{
			if (options.m_DefaultImages)
			{
				rMan.SetImages ((UINT)0, 16);
			}
			else
			{
				rMan.SetImages (IDB_PLANNER_ICONS, 16, (COLORREF)-1);
			}
		}
	}

	if (options.m_bClockIconsChanged)
	{
		(const_cast<CPlannerOptions&>(options)).m_bClockIconsChanged = FALSE;

		if (nBitsPerPixel > 8)
		{
			rMan.SetClockIconsRTC (options.m_DefaultClockIcons 
				? (CRuntimeClass*) NULL 
				: RUNTIME_CLASS(CPlannerClockIcons));
		}
	}

	rMan.SetRedraw (TRUE);

	if (bRedraw)
	{
		rMan.RedrawWindow ();
	}
	
	if (options.m_ShowToolTip != rMan.IsShowToolTip ())
	{
		rMan.SetShowToolTip (options.m_ShowToolTip);
	}
}

BOOL CCalendarPlannerView::Load(const CString& strPath, BOOL bStartUp)
{
	CDocument* pDoc = GetDocument ();
	ASSERT_VALID(pDoc);

	CString strFileName = strPath + s_szFileName;

	CFileException fe;
	CFile* pFile = pDoc->GetFile(strFileName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		pDoc->ReportSaveLoadException(strFileName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}

	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_pDocument  = pDoc;
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;

		if (pFile->GetLength() != 0)
		{
			DWORD dwHeader = 0;
			loadArchive >> dwHeader;

			if (dwHeader != c_dwHeader)
			{
				if (!bStartUp)
				{
					AfxThrowArchiveException(CArchiveException::badSchema);
				}
				return FALSE;
			}

			loadArchive >> m_dwVersion;

			Serialize (loadArchive);     // load me
		}

		loadArchive.Close();
		pDoc->ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		pDoc->ReleaseFile(pFile, TRUE);

		TRY
		{
			pDoc->ReportSaveLoadException(strFileName, e,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		}
		END_TRY
		do { e->Delete(); } while (0);
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

BOOL CCalendarPlannerView::Save(const CString& strPath)
{
	CDocument* pDoc = GetDocument ();
	ASSERT_VALID(pDoc);

	CString strFileName = strPath + s_szFileName;

	CFileException fe;
	CFile* pFile = NULL;
	pFile = pDoc->GetFile(strFileName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);

	if (pFile == NULL)
	{
		pDoc->ReportSaveLoadException(strFileName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return FALSE;
	}

	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_pDocument  = pDoc;
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;

		saveArchive << c_dwHeader;
		saveArchive << m_dwVersion;

		Serialize (saveArchive);

		saveArchive.Close();
		pDoc->ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		pDoc->ReleaseFile(pFile, TRUE);

		TRY
		{
			pDoc->ReportSaveLoadException(strFileName, e,
				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		}
		END_TRY
		do { e->Delete(); } while (0);

		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

void CCalendarPlannerView::UpdateCaptionText ()
{
	CBCGPOrganizerDoc* pDoc = GetDocument ();
	if (pDoc == NULL || pDoc->GetMode () != CBCGPOrganizerDoc::e_ModeCalendar)
	{
		return;
	}

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());

	if (pFrame != NULL)
	{
		COleDateTime dtStart (GetManagerCtrl ().GetDateStart ());
		COleDateTime dtEnd (GetManagerCtrl ().GetDateEnd ());

		CString strText;

		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetManagerCtrl ().GetType ();

		if (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
			type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
			type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
		{
			SYSTEMTIME st;
			CString str;

			if ((dtEnd - dtStart).GetDays () != 0)
			{
				if (dtEnd.GetYear () != dtStart.GetYear ())
				{
					dtStart.GetAsSystemTime (st);
					::GetDateFormat
						(
							LOCALE_USER_DEFAULT,
							0,
							&st,
							_T("d MMMM yyyy"),
							str.GetBuffer (100),
							100
						);
					str.ReleaseBuffer ();

					strText = str + _T(" - ");

					dtEnd.GetAsSystemTime (st);
					::GetDateFormat
						(
							LOCALE_USER_DEFAULT,
							0,
							&st,
							_T("d MMMM yyyy"),
							str.GetBuffer (100),
							100
						);
					str.ReleaseBuffer ();

					strText += str;
				}
				else
				{
					dtStart.GetAsSystemTime (st);
					::GetDateFormat
						(
							LOCALE_USER_DEFAULT,
							0,
							&st,
							_T("d MMMM"),
							str.GetBuffer (100),
							100
						);
					str.ReleaseBuffer ();

					strText = str + _T(" - ");

					dtEnd.GetAsSystemTime (st);
					::GetDateFormat
						(
							LOCALE_USER_DEFAULT,
							0,
							&st,
							_T("d MMMM"),
							str.GetBuffer (100),
							100
						);
					str.ReleaseBuffer ();

					strText += str;
				}
			}
			else
			{		
				dtStart.GetAsSystemTime (st);
				::GetDateFormat
					(
						LOCALE_USER_DEFAULT,
						0,
						&st,
						_T("d MMMM yyyy"),
						str.GetBuffer (100),
						100
					);
				str.ReleaseBuffer ();

				strText = str;
			}
		}
		else if (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
		{
			SYSTEMTIME st;
			CString str;
			
			if ((dtStart + COleDateTimeSpan (7, 0, 0, 0)).GetMonth () != 
				dtStart.GetMonth ())
			{
				dtStart += COleDateTimeSpan (7, 0, 0, 0);
			}

			if ((dtEnd - COleDateTimeSpan (7, 0, 0, 0)).GetMonth () != 
				 dtEnd.GetMonth ())
			{
				dtEnd -= COleDateTimeSpan (7, 0, 0, 0);
			}

			dtStart.GetAsSystemTime (st);
			::GetDateFormat
				(
					LOCALE_USER_DEFAULT,
					0,
					&st,
					_T("MMMM yyyy"),
					str.GetBuffer (100),
					100
				);
			str.ReleaseBuffer ();

			strText = str;

			if (dtStart.GetMonth () != dtEnd.GetMonth ())
			{
				dtEnd.GetAsSystemTime (st);
				::GetDateFormat
					(
						LOCALE_USER_DEFAULT,
						0,
						&st,
						_T("MMMM yyyy"),
						str.GetBuffer (100),
						100
					);
				str.ReleaseBuffer ();

				strText += _T(" - ");
				strText += str;
			}
		}

		pFrame->SetCaptionText (strText);
	}
}

void CCalendarPlannerView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CBCGPPlannerManagerView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		UpdateCaptionText ();
	}
}

void CCalendarPlannerView::Serialize(CArchive& ar)
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();
	BOOL bMulti = rMan.IsMultiResourceStorage ();
	DWORD dwCount = 0;

	if (ar.IsStoring ())
	{
		ar << bMulti;

		if (bMulti)
		{
			CBCGPAppointmentBaseMultiStorage* pStorage = 
				DYNAMIC_DOWNCAST(CBCGPAppointmentBaseMultiStorage, rMan.GetStorage ());

			CBCGPAppointmentMultiStorage::XResourceIDArray id;
			pStorage->GetResourceIDs (id);

			dwCount = (DWORD) id.GetSize ();

			ar << dwCount;

			for (DWORD i = 0; i < dwCount; i++)
			{
				ar << id[i];

				CBCGPAppointmentBaseResourceInfo* pInfo = 
					(CBCGPAppointmentBaseResourceInfo*)pStorage->GetResourceInfo (id[i]);

				pInfo->Serialize (ar);
			}
		}	
	}
	else
	{
		ar >> bMulti;
		
		if (bMulti)
		{
			return;
		}

		rMan.ClearAppointmentSelection (FALSE);
		rMan.ClearQuery ();

		rMan.SetUseMultiResourceDefault (bMulti);
		rMan.SetStorageRTC ();

		if (bMulti)
		{
			CBCGPAppointmentBaseMultiStorage* pStorage = 
				DYNAMIC_DOWNCAST(CBCGPAppointmentBaseMultiStorage, rMan.GetStorage ());

			if (pStorage != NULL)
			{
				ar >> dwCount;

				if (dwCount == 0)
				{
					ASSERT (FALSE);
					return;
				}

				for (DWORD i = 0; i < dwCount; i++)
				{
					UINT nResourceID = 0;

					ar >> nResourceID;

					CAppointmentResourceInfo* pInfo = new CAppointmentResourceInfo;

					pInfo->Serialize (ar);

					if (rMan.AddResourceRTC (nResourceID, NULL, pInfo, TRUE, FALSE))
					{
						if (i == 0)
						{
							pStorage->SetCurrentResourceID (nResourceID);
						}
					}
				}

				rMan.SetCurrentResourceID (pStorage->GetCurrentResourceID (), FALSE);
			}
		}
		else
		{
			if (rMan.GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI)
			{
				rMan.SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY, FALSE);
			}
		}
	}

	//CompleteResourceCombo ();

	rMan.SerializeRaw (ar);
}

void CCalendarPlannerView::OnDrawBackground()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST (CMainFrame, GetTopLevelFrame ());
	if (pFrame != NULL)
	{
		COLORREF clr = pFrame->GetCalendarBackground ();
		GetManagerCtrl ().SetBackgroundColor (clr);
		theApp.m_OptionsPlanner.m_clrBackground = clr;
	}
}

void CCalendarPlannerView::OnUpdateDrawBackground(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

class XBCGPRibbonColorButton: public CBCGPRibbonColorButton
{
	friend class CCalendarPlannerView;
};

LRESULT CCalendarPlannerView::OnHighlightRibbonListItem (WPARAM wp, LPARAM lp)
{
	int nIndex = (int) wp;

	CBCGPBaseRibbonElement* pElem = (CBCGPBaseRibbonElement*) lp;
	ASSERT_VALID (pElem);

	const UINT uiCommand = pElem->GetID ();

	if (uiCommand == ID_PLANNER_DRAW_BACKGROUND)
	{
		COLORREF clr = theApp.m_OptionsPlanner.m_clrBackground;

		if (nIndex != -1)
		{
			XBCGPRibbonColorButton* pColor = 
				(XBCGPRibbonColorButton*)DYNAMIC_DOWNCAST(CBCGPRibbonColorButton, pElem);
			if (pColor != NULL)
			{
				clr = pColor->GetColorByIndex (nIndex);
			}
		}

		GetManagerCtrl ().SetBackgroundColor (clr);
	}

	return 0L;
}
