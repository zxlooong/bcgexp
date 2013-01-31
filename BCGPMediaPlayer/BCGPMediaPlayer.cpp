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
// BCGPMediaPlayer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"

#include "MainFrm.h"
#include "BCGPMediaPlayerDoc.h"
#include "BCGPMediaPlayerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CVisualManager* GetVisualManager ()
{
	return ((CVisualManager*)CBCGPVisualManager::GetInstance ());
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerApp

BEGIN_MESSAGE_MAP(CBCGPMediaPlayerApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPMediaPlayerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerApp construction

CBCGPMediaPlayerApp::CBCGPMediaPlayerApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPMediaPlayerApp object

CBCGPMediaPlayerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerApp initialization

BOOL CBCGPMediaPlayerApp::InitInstance()
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

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPMediaPlayerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPMediaPlayerView));
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
// CBCGPMediaPlayerApp message handlers

int CBCGPMediaPlayerApp::ExitInstance() 
{
	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

// App command to run the dialog
void CBCGPMediaPlayerApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}


/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerApp message handlers


void CBCGPMediaPlayerApp::OnFileOpen() 
{
	CString strTitle;
	VERIFY(strTitle.LoadString(AFX_IDS_OPENFILE));

	CString strFilter;
	CString strDefault;

	strFilter = _T("Media files (all types)|*.wav;*.mp3;*.avi|Audio file (*.wav,*.mp3)|*.wav;*.mp3|Video file (*.avi)|*.avi|Any file (*.*)|*.*||");

	CFileDialog dlgFile (TRUE, NULL, NULL, 
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, strFilter, AfxGetMainWnd ());

	dlgFile.m_ofn.lpstrTitle  = strTitle;

	if (dlgFile.DoModal() == IDOK)
	{
		OpenDocumentFile (dlgFile.GetPathName ());
	}
}
