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
// BCGPVisualStudioGUIDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "BCGPVisualStudioGUIDemoDoc.h"
#include "BCGPVisualStudioGUIDemoView.h"
#include "StartView.h"
#include "BCGPVisualManagerXP.h"
#include "AppLookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp

BEGIN_MESSAGE_MAP(CBCGPVisualStudioGUIDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPVisualStudioGUIDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP_SHOW_START, OnHelpShowStart)
	ON_COMMAND(ID_VIEW_APP_LOOK, OnViewAppLook)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp construction

CBCGPVisualStudioGUIDemoApp::CBCGPVisualStudioGUIDemoApp() :
	CBCGPWorkspace (TRUE)
{
	m_pStartDocTemplate = NULL;
	m_pDocTemplateCpp = NULL;
	m_pDocTemplateWeb = NULL;

	m_bHiColorIcons = FALSE;
}

CBCGPVisualStudioGUIDemoApp::~CBCGPVisualStudioGUIDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPVisualStudioGUIDemoApp object

CBCGPVisualStudioGUIDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp initialization

BOOL CBCGPVisualStudioGUIDemoApp::InitInstance()
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
	InitMouseManager();
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager ();

	EnableUserTools (ID_TOOLS_ENTRY, ID_USER_TOOL1, ID_USER_TOOL10, 
					RUNTIME_CLASS (CBCGPUserTool), IDR_MENU_ARGS, IDR_MENU_DIRS);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplateCpp = new CMultiDocTemplate(
		IDR_BCGDEVTYPE_CPP,
		RUNTIME_CLASS(CBCGPVisualStudioGUIDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CBCGPVisualStudioGUIDemoView));
	AddDocTemplate (m_pDocTemplateCpp);

	m_pDocTemplateWeb = new CMultiDocTemplate(
		IDR_BCGDEVTYPE_WEB,
		RUNTIME_CLASS(CBCGPVisualStudioGUIDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CBCGPVisualStudioGUIDemoView));
	AddDocTemplate (m_pDocTemplateWeb);

	m_pStartDocTemplate = new CMultiDocTemplate(
		IDR_BCGDEVTYPE0,
		RUNTIME_CLASS(CBCGPVisualStudioGUIDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CStartView));
	AddDocTemplate (m_pStartDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;

	EnableLoadWindowPlacement (FALSE);

	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{
		if (!pMainFrame->LoadMDIState (GetRegSectionPath ()))
		{
			m_pStartDocTemplate->OpenDocumentFile (NULL);
		}
	}
	else
	{
		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}

	m_pMainWnd->DragAcceptFiles();

	// The main window has been initialized, so show and update it.
	if (!ReloadWindowPlacement (pMainFrame))
	{
		pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->UpdateWindow();
	}


	CAppLookDlg dlg (TRUE, m_pMainWnd);
	dlg.DoModal ();

	return TRUE;
}

// App command to run the dialog
void CBCGPVisualStudioGUIDemoApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}

/////////////////////////////////////////////////////////////////////////////
// Customization load/save methods

void CBCGPVisualStudioGUIDemoApp::PreLoadState ()
{
	GetMouseManager()->AddView (IDR_BCGDEVTYPE0, _T("My view"), IDR_BCGDEVTYPE0);
	// TODO: add another views and windows were mouse double click
	// customization is required

	GetContextMenuManager()->AddMenu (_T("Edit Context menu"), IDR_CONTEXT_MENU);
	GetContextMenuManager()->AddMenu (_T("Edit Left Bar menu"), IDR_POPUP_SELECTIONMARGIN);
	GetContextMenuManager()->AddMenu (_T("Main Window Area menu"), IDR_POPUP_MAIN_AREA);
	GetContextMenuManager()->AddMenu (_T("Resource"), IDR_POPUP_RESOURCE);
	GetContextMenuManager()->AddMenu (_T("Solution Explorer"), IDR_POPUP_SOLUTION);
}

void CBCGPVisualStudioGUIDemoApp::LoadCustomState ()
{
}

void CBCGPVisualStudioGUIDemoApp::SaveCustomState ()
{
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPVisualStudioGUIDemoApp message handlers

int CBCGPVisualStudioGUIDemoApp::ExitInstance() 
{
	BCGCBProCleanUp ();
	return CWinApp::ExitInstance();
}

void CBCGPVisualStudioGUIDemoApp::OnHelpShowStart() 
{
	ASSERT_VALID (m_pStartDocTemplate);

	POSITION pos = m_pStartDocTemplate->GetFirstDocPosition ();
	if (pos == NULL)
	{
		m_pStartDocTemplate->OpenDocumentFile(NULL);
		return;
	}

	CDocument* pDoc = m_pStartDocTemplate->GetNextDoc (pos);
	ASSERT_VALID (pDoc);

	pos = pDoc->GetFirstViewPosition ();
	ASSERT (pos != NULL);

	CView* pView = pDoc->GetNextView (pos);
	ASSERT_VALID (pView);

	CFrameWnd* pFrame = pView->GetParentFrame ();
	ASSERT_VALID (pFrame);

	CMainFrame* pMainFrame = (CMainFrame*) AfxGetMainWnd ();
	ASSERT_VALID (pMainFrame);

	::SendMessage (pMainFrame->m_hWndMDIClient, WM_MDIACTIVATE,
				(WPARAM) pFrame->GetSafeHwnd (), 0);
}

void CBCGPVisualStudioGUIDemoApp::OnViewAppLook() 
{
	CAppLookDlg dlg (FALSE, m_pMainWnd);
	dlg.DoModal ();
}

BOOL CBCGPVisualStudioGUIDemoApp::SaveAllModified() 
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
