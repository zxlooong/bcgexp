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
// BCGPMSOffice2007Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPMSOffice2007Demo.h"

#include "MainFrm.h"
#include "BCGPMSOffice2007DemoDoc.h"
#include "BCGPMSOffice2007DemoView.h"
#include "RibbonTooltipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoApp

BEGIN_MESSAGE_MAP(CBCGPMSOffice2007DemoApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPMSOffice2007DemoApp)
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
// CBCGPMSOffice2007DemoApp construction

CBCGPMSOffice2007DemoApp::CBCGPMSOffice2007DemoApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	m_bShowFloaty = TRUE;
	m_bShowDevTab = FALSE;
	m_nAppLook = ID_VIEW_APPLOOK_2007_1;
	m_bShowToolTips = TRUE;
	m_bShowKeyTips = TRUE;
	m_bShowToolTipDescr = TRUE;

	// Init custom theme colors:
	m_lstCustomColors.AddTail (RGB (210, 240, 179));
	m_lstCustomColors.AddTail (RGB (151, 192, 234));
	m_lstCustomColors.AddTail (RGB (203, 160, 224));
	m_lstCustomColors.AddTail (RGB (223, 159, 191));
	m_lstCustomColors.AddTail (RGB (243, 224, 185));
	m_lstCustomColors.AddTail (RGB (190, 178, 240));
	m_lstCustomColors.AddTail (RGB (232, 232, 216));
	m_lstCustomColors.AddTail (RGB (247, 218, 214));
	m_lstCustomColors.AddTail (RGB (189, 231, 224));
	m_lstCustomColors.AddTail (RGB (214, 234, 218));

	m_clrCustomDef = RGB (193, 223, 192);
	m_clrCustom = (COLORREF)-1;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPMSOffice2007DemoApp object

CBCGPMSOffice2007DemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoApp initialization

BOOL CBCGPMSOffice2007DemoApp::InitInstance()
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

	SetRegistryBase (_T("Settings"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

	// Load options:
	m_bShowFloaty = GetInt (_T("ShowFloaty"), TRUE);
	m_bShowDevTab = GetInt (_T("ShowDevTab"), FALSE);
	m_nAppLook = GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2007_1);
	
	if (m_nAppLook < ID_VIEW_APPLOOK_2007_1)
	{
		m_nAppLook = ID_VIEW_APPLOOK_2007_1;
	}

	m_bShowToolTips = GetInt (_T("ShowToolTips"), TRUE);
	m_bShowKeyTips = GetInt (_T("ShowKeyTips"), TRUE);
	m_bShowToolTipDescr = GetInt (_T("bShowToolTipDescr"), TRUE);
	m_bIsRTL = GetInt (_T("IsRTL"), FALSE);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		0xFFFF,
		RUNTIME_CLASS (CRibbonTooltipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPMSOffice2007DemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPMSOffice2007DemoView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	GetContextMenuManager()->AddMenu (_T("Context menu"), IDR_CONTEXT_MENU);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);

	CRect rect;
	m_pMainWnd->GetWindowRect (rect);

	m_pMainWnd->SetWindowPos (NULL, -1, -1, rect.Width (), rect.Height (), SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoApp message handlers

int CBCGPMSOffice2007DemoApp::ExitInstance() 
{
	// Save options:
	WriteInt (_T("ShowFloaty"), m_bShowFloaty);
	WriteInt (_T("ShowDevTab"), m_bShowDevTab);
	WriteInt (_T("ApplicationLook"), m_nAppLook);
	WriteInt (_T("ShowToolTips"), m_bShowToolTips);
	WriteInt (_T("ShowKeyTips"), m_bShowKeyTips);
	WriteInt (_T("bShowToolTipDescr"), m_bShowToolTipDescr);
	WriteInt (_T("IsRTL"), m_bIsRTL);

	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

// App command to run the dialog
void CBCGPMSOffice2007DemoApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}


/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoApp message handlers

