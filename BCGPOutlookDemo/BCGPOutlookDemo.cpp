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
// BCGPOutlookDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPOutlookDemo.h"

#include "MainFrm.h"
#include "BCGPOutlookDemoDoc.h"
#include "BCGPOutlookDemoView.h"

#include "AppLookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoApp

BEGIN_MESSAGE_MAP(CBCGPOutlookDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPOutlookDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VIEW_APP_LOOK, OnViewAppLook)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoApp construction

CBCGPOutlookDemoApp::CBCGPOutlookDemoApp() :
	CBCGPWorkspace (TRUE)
{
	m_bLoadSaveFrameBarsOnly = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPOutlookDemoApp object

CBCGPOutlookDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoApp initialization

BOOL CBCGPOutlookDemoApp::InitInstance()
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

	SetActiveFrame (MainFrame);

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();
	InitShellManager();

	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		0xFFFF,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// Enable user-defined tools. If you want allow more than 10 tools,
	// add tools entry to resources (ID_USER_TOOL11, ID_USER_TOOL12,...)
	EnableUserTools (ID_TOOLS_ENTRY, ID_USER_TOOL1, ID_USER_TOOL10);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPOutlookDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPOutlookDemoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	LoadCustomState ();

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Set application general look:
	CAppLookDlg dlg (TRUE);
	dlg.DoModal ();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoApp message handlers

int CBCGPOutlookDemoApp::ExitInstance() 
{
	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

// App command to run the dialog
void CBCGPOutlookDemoApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}

void CBCGPOutlookDemoApp::PreLoadState ()
{

	GetContextMenuManager()->AddMenu (_T("My menu"), IDR_CONTEXT_MENU);

	// TODO: add another context menus here
}

void CBCGPOutlookDemoApp::SetActiveFrame (OUTLOOK_FRAME frame)
{
	CString strOldRegPath = GetRegSectionPath ();

	// Save user tools:
	if (GetUserToolsManager () != NULL)
	{
		GetUserToolsManager ()->SaveState (GetRegSectionPath ());
	}

	switch (frame)
	{
	case MainFrame:
		SetRegistryBase (_T("Main Frame Settings"));
		break;

	case MailFrame:
		SetRegistryBase (_T("Mail Settings"));
		break;

	default:
		ASSERT (FALSE);
	}

	// Load user tools:
	if (GetUserToolsManager () != NULL)
	{
		GetUserToolsManager ()->LoadState (strOldRegPath);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoApp message handlers

void CBCGPOutlookDemoApp::OnViewAppLook() 
{
	CAppLookDlg dlg (FALSE);
	dlg.DoModal ();
}
