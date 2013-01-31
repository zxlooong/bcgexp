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
// BCGPOrganizer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPOrganizer.h"

#include "MainFrm.h"
#include "BCGPOrganizerDoc.h"
#include "BCGPOrganizerView.h"

#include "RibbonTooltipCtrl.h"
#include "Planner/PlannerTooltipCtrl.h"
#include "Gantt/GanttTooltipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString s_szKeyPlanner (_T("Options\\Planner"));
static CString s_szKeyGantt (_T("Options\\Gantt"));

CPlannerOptions::CPlannerOptions()
	: m_clrBackground        (CLR_DEFAULT)
	, m_Type                 (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_FIRST)
	, m_ShowToolTip          (2)
	, m_DrawFlags            ((DWORD)-1)
	, m_WorkFirstDayOfWeek   (-1)
	, m_WorkHourFirst        ( 9.0)
	, m_WorkHourLast         (18.0)
	, m_DefaultImages        (FALSE)
	, m_DefaultClockIcons    (FALSE)
	, m_DayTimeDelta         (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_FIRST)
	, m_WeekDrawTimeFinish   (TRUE)
	, m_WeekDrawTimeIcons    (FALSE)
	, m_MonthDrawTimeFinish  (TRUE)
	, m_MonthDrawTimeIcons   (FALSE)
	, m_MonthCompressWeekend (TRUE)
	, m_bImagesChanged       (FALSE)
	, m_bClockIconsChanged   (FALSE)
	, m_CalendarGradientFill (FALSE)
	, m_CalendarWeekNumbers  (TRUE)
{
}

void CPlannerOptions::Load ()
{
	m_clrBackground        = (COLORREF) theApp.GetSectionInt (s_szKeyPlanner, _T("BackColor"), (int) m_clrBackground);
	m_Type                 = (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE) theApp.GetSectionInt (s_szKeyPlanner, _T("Type"), (int) m_Type);
	m_ShowToolTip          = (int) theApp.GetSectionInt (s_szKeyPlanner, _T("ShowToolTip"), (int) m_ShowToolTip);
	m_DrawFlags         = (DWORD) theApp.GetSectionInt (s_szKeyPlanner, _T("DrawFlags"), (int) m_DrawFlags);
	m_WorkFirstDayOfWeek   = theApp.GetSectionInt (s_szKeyPlanner + _T("\\Work"), _T("FirstDayOfWeek"), m_WorkFirstDayOfWeek);
	m_WorkHourFirst        = theApp.GetSectionInt (s_szKeyPlanner + _T("\\Work"), _T("HourFirst"), (int) (m_WorkHourFirst * 100.0)) / 100.0;
	m_WorkHourLast         = theApp.GetSectionInt (s_szKeyPlanner + _T("\\Work"), _T("HourLast"), (int) (m_WorkHourLast * 100.0)) / 100.0;
	m_DefaultImages        = (BOOL) theApp.GetSectionInt (s_szKeyPlanner, _T("DefaultImages"), (int) m_DefaultImages);
	m_DefaultClockIcons    = (BOOL) theApp.GetSectionInt (s_szKeyPlanner, _T("DefaultClockIcons"), (int) m_DefaultClockIcons);
	m_DayTimeDelta         = (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Day"), _T("TimeScale"), (int) m_DayTimeDelta);
	m_WeekDrawTimeFinish   = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Week"), _T("DrawTimeFinish"), (int) m_WeekDrawTimeFinish);
	m_WeekDrawTimeIcons    = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Week"), _T("DrawTimeIcons"), (int) m_WeekDrawTimeIcons);
	m_MonthDrawTimeFinish  = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Month"), _T("DrawTimeFinish"), (int) m_MonthDrawTimeFinish);
	m_MonthDrawTimeIcons   = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Month"), _T("DrawTimeIcons"), (int) m_MonthDrawTimeIcons);
	m_MonthCompressWeekend = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Month"), _T("CompressWeekend"), (int) m_MonthCompressWeekend);

	m_CalendarGradientFill = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Calendar"), _T("GradientFill"), (int) m_CalendarGradientFill);
	m_CalendarWeekNumbers  = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Calendar"), _T("WeekNumbers"), (int) m_CalendarWeekNumbers);

	m_bImagesChanged = !m_DefaultImages;
	m_bClockIconsChanged = !m_DefaultClockIcons;
}

void CPlannerOptions::Save ()
{
	theApp.WriteSectionInt (s_szKeyPlanner, _T("BackColor"), (int) m_clrBackground);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("Type"), (int) m_Type);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("ShowToolTip"), (int) m_ShowToolTip);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("DrawFlags"), (int) m_DrawFlags);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Work"), _T("FirstDayOfWeek"), m_WorkFirstDayOfWeek);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Work"), _T("HourFirst"), (int) (m_WorkHourFirst * 100.0));
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Work"), _T("HourLast"), (int) (m_WorkHourLast * 100.0));
	theApp.WriteSectionInt (s_szKeyPlanner, _T("DefaultImages"), (int) m_DefaultImages);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("DefaultClockIcons"), (int) m_DefaultClockIcons);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Day"), _T("TimeScale"), (int) m_DayTimeDelta);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Week"), _T("DrawTimeFinish"), (int) m_WeekDrawTimeFinish);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Week"), _T("DrawTimeIcons"), (int) m_WeekDrawTimeIcons);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Month"), _T("DrawTimeFinish"), (int) m_MonthDrawTimeFinish);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Month"), _T("DrawTimeIcons"), (int) m_MonthDrawTimeIcons);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Month"), _T("CompressWeekend"), (int) m_MonthCompressWeekend);

	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Calendar"), _T("GradientFill"), (int) m_CalendarGradientFill);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Calendar"), _T("WeekNumbers"), (int) m_CalendarWeekNumbers);
}


CGanttOptions::CGanttOptions()
	: m_clrBackground        (CLR_DEFAULT)
	, m_ShowToolTip          (2)
{
}

void CGanttOptions::Load ()
{
	m_clrBackground        = (COLORREF) theApp.GetSectionInt (s_szKeyGantt, _T("BackColor"), (int) m_clrBackground);
	m_ShowToolTip          = (int) theApp.GetSectionInt (s_szKeyGantt, _T("ShowToolTip"), (int) m_ShowToolTip);
}

void CGanttOptions::Save ()
{
	theApp.WriteSectionInt (s_szKeyGantt, _T("BackColor"), (int) m_clrBackground);
	theApp.WriteSectionInt (s_szKeyGantt, _T("ShowToolTip"), (int) m_ShowToolTip);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerApp

BEGIN_MESSAGE_MAP(CBCGPOrganizerApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPOrganizerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerApp construction

CBCGPOrganizerApp::CBCGPOrganizerApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	m_bShowFloaty = TRUE;
	m_nAppLook = ID_VIEW_APPLOOK_2007_1;
	m_bShowToolTips = TRUE;
	m_bShowKeyTips = TRUE;
	m_bShowToolTipDescr = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPOrganizerApp object

CBCGPOrganizerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerApp initialization

BOOL CBCGPOrganizerApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Examples"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings2"));

	m_OptionsPlanner.Load ();
	m_OptionsGantt.Load ();

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	m_bShowFloaty = GetInt (_T("ShowFloaty"), TRUE);
	m_nAppLook = GetInt (_T("ApplicationLook"), 1);
	m_bShowToolTips = GetInt (_T("ShowToolTips"), TRUE);
	m_bShowKeyTips = GetInt (_T("ShowKeyTips"), TRUE);
	m_bShowToolTipDescr = GetInt (_T("ShowToolTipDescription"), TRUE);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	globalData.m_nMaxToolTipWidth = 150;

	theApp.GetTooltipManager ()->SetTooltipParams (
		0xFFFF,
		RUNTIME_CLASS (CRibbonTooltipCtrl),
		&params);
	
	if (m_OptionsPlanner.m_ShowToolTip == 2)
	{
		GetTooltipManager ()->SetTooltipParams (
			BCGP_TOOLTIP_TYPE_PLANNER,
			RUNTIME_CLASS (CPlannerTooltipCtrl),
			&params);
	}

	if (m_OptionsGantt.m_ShowToolTip == 2)
	{
 		GetTooltipManager ()->SetTooltipParams (
 			BCGP_TOOLTIP_TYPE_GANTT,
 			RUNTIME_CLASS (CGanttTooltipCtrl),
 			&params);
	}

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPOrganizerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPOrganizerView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
/*
	CRect rect;
	m_pMainWnd->GetWindowRect (rect);
	m_pMainWnd->SetWindowPos (NULL, -1, -1, rect.Width (), rect.Height (), SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
*/
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerApp message handlers

int CBCGPOrganizerApp::ExitInstance() 
{
	WriteInt (_T("ShowFloaty"), m_bShowFloaty);
	WriteInt (_T("ApplicationLook"), m_nAppLook);
	WriteInt (_T("ShowToolTips"), m_bShowToolTips);
	WriteInt (_T("ShowKeyTips"), m_bShowKeyTips);
	WriteInt (_T("ShowToolTipDescription"), m_bShowToolTipDescr);

	m_OptionsPlanner.Save ();
	m_OptionsGantt.Save ();

	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

void CBCGPOrganizerApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}

void CBCGPOrganizerApp::PreLoadState ()
{
	CBCGPContextMenuManager* pManager = GetContextMenuManager();

	pManager->AddMenu (_T("Output"), IDR_OUTPUT_MENU);
	pManager->AddMenu (_T("Mail"), IDR_MAIL_MENU);
	pManager->AddMenu (_T("Planner Appointment"), IDR_PLANNER_APPOINTMENT);
	pManager->AddMenu (_T("Planner Time Bar"), IDR_PLANNER_TIMEBAR);
	pManager->AddMenu (_T("Planner Day View"), IDR_PLANNER_CLIENT_DAY);
	pManager->AddMenu (_T("Planner Work Week View"), IDR_PLANNER_CLIENT_WORK_WEEK);
	pManager->AddMenu (_T("Planner Week View"), IDR_PLANNER_CLIENT_WEEK);
	pManager->AddMenu (_T("Planner Month View"), IDR_PLANNER_CLIENT_MONTH);
	pManager->AddMenu (_T("Tasks"), IDR_TASKS_MENU);
	pManager->AddMenu (_T("Macros Edit"), IDR_EDIT_MENU);
	pManager->AddMenu (_T("Macros Edit Margin"), IDR_EDIT_POPUP_SELECTIONMARGIN);
	pManager->AddMenu (_T("Gantt View"), IDR_GANTT_CLIENT);
	pManager->AddMenu (_T("Gantt Task"), IDR_GANTT_TASK);
	
	pManager->AddMenu (_T("Edit"), IDR_EDITCTRL_MENU);
	//pManager->AddMenu (_T("Category"), IDR_CATEGORY_MENU);
}

void CBCGPOrganizerApp::UpdateCalendar (BOOL bUpdateCalendar /*= TRUE*/)
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd ();
	ASSERT_VALID (pFrame);

	if (bUpdateCalendar)
	{
		CBCGPOrganizerDoc* pDoc = (CBCGPOrganizerDoc*) 
			pFrame->GetActiveDocument ();

		if (pDoc != NULL)
		{
			ASSERT_VALID (pDoc);
			pDoc->UpdateCalendar (m_OptionsPlanner);
		}

		pFrame->UpdateCalendar ();
	}
	else
	{
		//DR:
		//pFrame->GetPropBar ().Update ();
	}

	//------------------------
	// Set tooltip parameters:
	//------------------------
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	globalData.m_nMaxToolTipWidth = 150;

	GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_PLANNER,
		m_OptionsPlanner.m_ShowToolTip == 2 ?
			RUNTIME_CLASS (CPlannerTooltipCtrl) :
			RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);
}

void CBCGPOrganizerApp::UpdateGantt (BOOL bUpdateGantt /*= TRUE*/)
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd ();
	ASSERT_VALID (pFrame);

	if (bUpdateGantt)
	{
		CBCGPOrganizerDoc* pDoc = (CBCGPOrganizerDoc*) 
			pFrame->GetActiveDocument ();

		if (pDoc != NULL)
		{
			ASSERT_VALID (pDoc);
			pDoc->UpdateGantt (m_OptionsGantt);
		}

		pFrame->UpdateCalendar ();
	}
	else
	{
		//DR:
		//pFrame->GetPropBar ().Update ();
	}

	//------------------------
	// Set tooltip parameters:
	//------------------------
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	globalData.m_nMaxToolTipWidth = 150;

	GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_GANTT,
		m_OptionsGantt.m_ShowToolTip == 2 ?
			RUNTIME_CLASS (CPlannerTooltipCtrl) :
			RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);
}
/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerApp message handlers

