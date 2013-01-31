//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPIE7Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "BCGPIE7DemoDoc.h"
#include "BCGPIE7DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoApp

BEGIN_MESSAGE_MAP(CBCGPIE7DemoApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPIE7DemoApp)
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
// CBCGPIE7DemoApp construction

CBCGPIE7DemoApp::CBCGPIE7DemoApp()
	: CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
	, m_nColorMode   (8)
	, m_bLargeIcons  (FALSE)
	, m_Style        (1)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPIE7DemoApp object

CBCGPIE7DemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoApp initialization

BOOL CBCGPIE7DemoApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	AfxInitRichEdit ();

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

	SetRegistryBase (_T("Settings"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitKeyboardManager();

	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	m_Favorites.Load ();

	m_bLargeIcons = (BOOL)GetProfileInt (_T("Options"), _T("LargeIcons"), (int)m_bLargeIcons);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_BCGPIETYPE,
		RUNTIME_CLASS(CBCGPIE7DemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CBCGPIE7DemoView));
	AddDocTemplate(pDocTemplate);

	m_Style = (globalData.DwmIsCompositionEnabled ()) ? 2 : 1;

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoApp message handlers

int CBCGPIE7DemoApp::ExitInstance() 
{
	BCGCBProCleanUp();

	WriteProfileInt (_T("Options"), _T("LargeIcons"), (int)m_bLargeIcons);

	return CWinApp::ExitInstance();
}

// App command to run the dialog
void CBCGPIE7DemoApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}

void CBCGPIE7DemoApp::PreLoadState ()
{
	if (g_pContextMenuManager == NULL)
	{
		InitContextMenuManager ();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoApp message handlers

BOOL CBCGPIE7DemoApp::SaveAllModified()
{
	if (!CWinApp::SaveAllModified ())
	{
		return FALSE;
	}

	CBCGPMDIFrameWnd* pMainFrame = 
		DYNAMIC_DOWNCAST (CBCGPMDIFrameWnd, m_pMainWnd);
	if (pMainFrame != NULL)
	{
		pMainFrame->SaveMDIState (GetRegSectionPath ());
	}

	return TRUE;
}

