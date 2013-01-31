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
// BCGPMSMoneyDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPMSMoneyDemo.h"

#include "MainFrm.h"
#include "BCGPMSMoneyDemoDoc.h"
#include "BCGPMSMoneyDemoView.h"

#include "BCGPMSMDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoApp

BEGIN_MESSAGE_MAP(CBCGPMSMoneyDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPMSMoneyDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoApp construction

CBCGPMSMoneyDemoApp::CBCGPMSMoneyDemoApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPMSMoneyDemoApp object

CBCGPMSMoneyDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoApp initialization

BOOL CBCGPMSMoneyDemoApp::InitInstance()
{
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

	SetRegistryBase (_T("Settings"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present

	// Initialize favorites:

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPMSMoneyDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPMSMoneyDemoView));
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
// CBCGPMSMoneyDemoApp message handlers

int CBCGPMSMoneyDemoApp::ExitInstance() 
{
	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

// App command to run the dialog
void CBCGPMSMoneyDemoApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}


/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoApp message handlers
