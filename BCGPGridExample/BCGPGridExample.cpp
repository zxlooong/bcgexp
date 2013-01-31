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
// BCGPGridExample.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPGridExample.h"

#include "MainFrm.h"
#include "BCGPGridExampleDoc.h"
#include "BCGPGridExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGridOptions::CGridOptions()
{
	m_bFieldChooser = TRUE;
	m_bGroupByBox = TRUE;
	m_bReportPreview = TRUE;
	m_nColorTheme = 0;
}

void CGridOptions::Load ()
{
	m_bFieldChooser = theApp.GetInt (_T("FieldChooser"), TRUE);
	m_bGroupByBox = theApp.GetInt (_T("GroupByBox"), TRUE);
	m_bReportPreview = theApp.GetInt (_T("ReportPreview"), TRUE);
	m_nColorTheme = theApp.GetInt (_T("ColorTheme"), 0);
}

void CGridOptions::Save ()
{
	theApp.WriteInt (_T("FieldChooser"), m_bFieldChooser);
	theApp.WriteInt (_T("GroupByBox"), m_bGroupByBox);
	theApp.WriteInt (_T("ReportPreview"), m_bReportPreview);
	theApp.WriteInt (_T("ColorTheme"), m_nColorTheme);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleApp

BEGIN_MESSAGE_MAP(CBCGPGridExampleApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPGridExampleApp)
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
// CBCGPGridExampleApp construction

CBCGPGridExampleApp::CBCGPGridExampleApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPGridExampleApp object

CBCGPGridExampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleApp initialization

BOOL CBCGPGridExampleApp::InitInstance()
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

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings10"));

	m_Options.Load ();

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		0xFFFF,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPGridExampleDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPGridExampleView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleApp message handlers

int CBCGPGridExampleApp::ExitInstance() 
{
	m_Options.Save ();
	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

// App command to run the dialog
void CBCGPGridExampleApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}


void CBCGPGridExampleApp::PreLoadState ()
{

	GetContextMenuManager()->AddMenu (_T("My menu"), IDR_CONTEXT_MENU);

	// TODO: add another context menus here
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleApp message handlers

void CBCGPGridExampleApp::UpdateGrid ()
{
	((CMainFrame*) AfxGetMainWnd ())->UpdateGrid ();
}

