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
// BCGPCalendarDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPCalendarDemo.h"

#include "MainFrm.h"
#include "BCGPCalendarDemoDoc.h"
#include "BCGPCalendarDemoView.h"
#include "PlannerTooltipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarOptions

static CString strKey (_T("Options\\"));

CCalendarOptions::CCalendarOptions()
	: m_clrBackground        (CLR_DEFAULT)
	, m_Type                 (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK)
	, m_ShowToolTip          (2)
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
	, m_UseDayInsteadWeek    (FALSE)
	, m_ScrollVisible        (TRUE)
{
}

void CCalendarOptions::Load ()
{
	m_clrBackground        = (COLORREF) theApp.GetSectionInt (strKey, _T("BackColor"), (int) m_clrBackground);
	m_Type                 = (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE) theApp.GetSectionInt (strKey, _T("Type"), (int) m_Type);
	m_ShowToolTip          = (int) theApp.GetSectionInt (strKey, _T("ShowToolTip"), (int) m_ShowToolTip);
	m_WorkFirstDayOfWeek   = theApp.GetSectionInt (strKey + _T("\\Work"), _T("FirstDayOfWeek"), m_WorkFirstDayOfWeek);
	m_WorkHourFirst        = theApp.GetSectionInt (strKey + _T("\\Work"), _T("HourFirst"), (int) (m_WorkHourFirst * 100.0)) / 100.0;
	m_WorkHourLast         = theApp.GetSectionInt (strKey + _T("\\Work"), _T("HourLast"), (int) (m_WorkHourLast * 100.0)) / 100.0;
	m_DefaultImages        = (BOOL) theApp.GetSectionInt (strKey, _T("DefaultImages"), (int) m_DefaultImages);
	m_DefaultClockIcons    = (BOOL) theApp.GetSectionInt (strKey, _T("DefaultClockIcons"), (int) m_DefaultClockIcons);
	m_DayTimeDelta         = (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA) theApp.GetSectionInt (strKey + _T("\\Day"), _T("TimeScale"), (int) m_DayTimeDelta);
	m_WeekDrawTimeFinish   = (BOOL) theApp.GetSectionInt (strKey + _T("\\Week"), _T("DrawTimeFinish"), (int) m_WeekDrawTimeFinish);
	m_WeekDrawTimeIcons    = (BOOL) theApp.GetSectionInt (strKey + _T("\\Week"), _T("DrawTimeIcons"), (int) m_WeekDrawTimeIcons);
	m_MonthDrawTimeFinish  = (BOOL) theApp.GetSectionInt (strKey + _T("\\Month"), _T("DrawTimeFinish"), (int) m_MonthDrawTimeFinish);
	m_MonthDrawTimeIcons   = (BOOL) theApp.GetSectionInt (strKey + _T("\\Month"), _T("DrawTimeIcons"), (int) m_MonthDrawTimeIcons);
	m_MonthCompressWeekend = (BOOL) theApp.GetSectionInt (strKey + _T("\\Month"), _T("CompressWeekend"), (int) m_MonthCompressWeekend);

	m_CalendarGradientFill = (BOOL) theApp.GetSectionInt (strKey + _T("\\Calendar"), _T("GradientFill"), (int) m_CalendarGradientFill);
	m_CalendarWeekNumbers  = (BOOL) theApp.GetSectionInt (strKey + _T("\\Calendar"), _T("WeekNumbers"), (int) m_CalendarWeekNumbers);

	m_UseDayInsteadWeek    = (BOOL) theApp.GetSectionInt (strKey, _T("UseDayInsteadWeek"), (int) m_UseDayInsteadWeek);
	m_ScrollVisible        = (BOOL) theApp.GetSectionInt (strKey, _T("ScrollVisible"), (int) m_ScrollVisible);

	m_bImagesChanged = !m_DefaultImages;
	m_bClockIconsChanged = !m_DefaultClockIcons;
}

void CCalendarOptions::Save ()
{
	theApp.WriteSectionInt (strKey, _T("BackColor"), (int) m_clrBackground);
	theApp.WriteSectionInt (strKey, _T("Type"), (int) m_Type);
	theApp.WriteSectionInt (strKey, _T("ShowToolTip"), (int) m_ShowToolTip);
	theApp.WriteSectionInt (strKey + _T("\\Work"), _T("FirstDayOfWeek"), m_WorkFirstDayOfWeek);
	theApp.WriteSectionInt (strKey + _T("\\Work"), _T("HourFirst"), (int) (m_WorkHourFirst * 100.0));
	theApp.WriteSectionInt (strKey + _T("\\Work"), _T("HourLast"), (int) (m_WorkHourLast * 100.0));
	theApp.WriteSectionInt (strKey, _T("DefaultImages"), (int) m_DefaultImages);
	theApp.WriteSectionInt (strKey, _T("DefaultClockIcons"), (int) m_DefaultClockIcons);
	theApp.WriteSectionInt (strKey + _T("\\Day"), _T("TimeScale"), (int) m_DayTimeDelta);
	theApp.WriteSectionInt (strKey + _T("\\Week"), _T("DrawTimeFinish"), (int) m_WeekDrawTimeFinish);
	theApp.WriteSectionInt (strKey + _T("\\Week"), _T("DrawTimeIcons"), (int) m_WeekDrawTimeIcons);
	theApp.WriteSectionInt (strKey + _T("\\Month"), _T("DrawTimeFinish"), (int) m_MonthDrawTimeFinish);
	theApp.WriteSectionInt (strKey + _T("\\Month"), _T("DrawTimeIcons"), (int) m_MonthDrawTimeIcons);
	theApp.WriteSectionInt (strKey + _T("\\Month"), _T("CompressWeekend"), (int) m_MonthCompressWeekend);

	theApp.WriteSectionInt (strKey + _T("\\Calendar"), _T("GradientFill"), (int) m_CalendarGradientFill);
	theApp.WriteSectionInt (strKey + _T("\\Calendar"), _T("WeekNumbers"), (int) m_CalendarWeekNumbers);

	theApp.WriteSectionInt (strKey, _T("UseDayInsteadWeek"), (int) m_UseDayInsteadWeek);
	theApp.WriteSectionInt (strKey, _T("ScrollVisible"), (int) m_ScrollVisible);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoApp

BEGIN_MESSAGE_MAP(CBCGPCalendarDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPCalendarDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoApp construction

CBCGPCalendarDemoApp::CBCGPCalendarDemoApp()
#ifndef _BCGPCALENDAR_STANDALONE
	: CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
#endif
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

#ifdef _BCGPCALENDAR_STANDALONE
int CBCGPCalendarDemoApp::GetSectionInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault /*= 0*/)
{
	return GetProfileInt(lpszSection, lpszEntry, nDefault);
}

BOOL CBCGPCalendarDemoApp::WriteSectionInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue )
{
	return WriteProfileInt(lpszSection, lpszEntry, nValue);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPCalendarDemoApp object

CBCGPCalendarDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoApp initialization

BOOL CBCGPCalendarDemoApp::InitInstance()
{
	AfxOleInit ();
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
#ifndef _BCGPCALENDAR_STANDALONE	
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Examples"));
#else
	SetRegistryKey(_T("BCGSoft\\BCGCalendar\\Samples"));
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

#ifndef _BCGPCALENDAR_STANDALONE
	SetRegistryBase (_T("Settings"));
#endif

	m_Options.Load ();

#ifndef _BCGPCALENDAR_STANDALONE
	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager ();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	globalData.m_nMaxToolTipWidth = 150;

	GetTooltipManager ()->SetTooltipParams (
		0xFFFF,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);
	
	if (m_Options.m_ShowToolTip == 2)
	{
		GetTooltipManager ()->SetTooltipParams (
			BCGP_TOOLTIP_TYPE_PLANNER,
			RUNTIME_CLASS (CPlannerTooltipCtrl),
			&params);
	}
#endif

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPCalendarDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPCalendarDemoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//UpdateCalendar ();

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoApp message handlers

int CBCGPCalendarDemoApp::ExitInstance() 
{
	m_Options.Save ();

#ifndef _BCGPCALENDAR_STANDALONE
	BCGCBProCleanUp();
#endif

	return CWinApp::ExitInstance();
}

#ifdef _BCGPCALENDAR_STANDALONE

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
#ifndef _BCGPCALENDAR_STANDALONE
	CBCGPURLLinkButton	m_bntURL;
	CBCGPURLLinkButton	m_btnMail;
#endif
	CString	m_strVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
#ifdef _BCGPCALENDAR_STANDALONE
	afx_msg void OnMail();
	afx_msg void OnURL();
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifdef _BCGPCALENDAR_STANDALONE
	void OnLink (const CString& str);
#endif
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strVersion = _T("");
	//}}AFX_DATA_INIT
	m_strVersion.Format (_T("%d.%d"), _BCGPCALENDAR_VERSION_MAJOR, _BCGPCALENDAR_VERSION_MINOR);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_MAIL, OnMail)
	ON_BN_CLICKED(IDC_URL, OnURL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnMail()
{
	OnLink (_T("mailto:info@bcgsoft.com"));
}

void CAboutDlg::OnURL()
{
	OnLink (_T("http://www.bcgsoft.com"));
}

#endif

// App command to run the dialog
void CBCGPCalendarDemoApp::OnAppAbout()
{
#ifndef _BCGPCALENDAR_STANDALONE
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
#else
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
#endif
}


#ifndef _BCGPCALENDAR_STANDALONE

void CBCGPCalendarDemoApp::PreLoadState ()
{
	GetContextMenuManager()->AddMenu (_T("Planner Appointment"), IDR_PLANNER_APPOINTMENT);

	GetContextMenuManager()->AddMenu (_T("Planner Time Bar"), IDR_PLANNER_TIMEBAR);
	GetContextMenuManager()->AddMenu (_T("Planner Day View"), IDR_PLANNER_CLIENT_DAY);
	GetContextMenuManager()->AddMenu (_T("Planner Work Week View"), IDR_PLANNER_CLIENT_WORK_WEEK);
	GetContextMenuManager()->AddMenu (_T("Planner Week View"), IDR_PLANNER_CLIENT_WEEK);
	GetContextMenuManager()->AddMenu (_T("Planner Month View"), IDR_PLANNER_CLIENT_MONTH);
	GetContextMenuManager()->AddMenu (_T("Planner Multi View"), IDR_PLANNER_CLIENT_MULTI);
}

#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoApp message handlers

void CBCGPCalendarDemoApp::UpdateCalendar (BOOL bUpdateCalendar /*= TRUE*/)
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd ();
	if (pFrame->GetSafeHwnd () == NULL)
	{
		return;
	}

	if (bUpdateCalendar)
	{
		CBCGPCalendarDemoDoc* pDoc = (CBCGPCalendarDemoDoc*) 
			pFrame->GetActiveDocument ();

		if (pDoc != NULL)
		{
			ASSERT_VALID (pDoc);
			pDoc->UpdateCalendar (m_Options);
		}

		pFrame->UpdateCalendar ();
	}
	else
	{
		pFrame->GetPropBar ().Update ();
	}

	//------------------------
	// Set tooltip parameters:
	//------------------------
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	globalData.m_nMaxToolTipWidth = 150;

	GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_PLANNER,
		m_Options.m_ShowToolTip == 2 ?
			RUNTIME_CLASS (CPlannerTooltipCtrl) :
			RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);
}
