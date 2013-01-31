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
// BCGPSkins.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPSkins.h"

#include "MainFrm.h"
#include "BCGPSkinsDoc.h"
#include "BCGPSkinsView.h"
#include "MacStyle.h"
#include "FunnyStyle.h"
#include "ImageStyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsApp

BEGIN_MESSAGE_MAP(CBCGPSkinsApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPSkinsApp)
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
// CBCGPSkinsApp construction

CBCGPSkinsApp::CBCGPSkinsApp()
{
	m_uiCurrSkin = ID_LOOK_2000;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPSkinsApp object

CBCGPSkinsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsApp initialization

BOOL CBCGPSkinsApp::InitInstance()
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
		RUNTIME_CLASS(CBCGPSkinsDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPSkinsView));
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

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsApp message handlers

int CBCGPSkinsApp::ExitInstance() 
{
	// Save image parameters for future run:
	WriteString (_T("ImagePath"), CImageStyle::m_strImagePath);
	WriteInt (_T("InternalImageBright"), CImageStyle::m_bIsInternalImage);
	WriteInt (_T("ImageBright"), CImageStyle::m_nHighlight);
	WriteInt (_T("TextColor"), CImageStyle::m_clrText);

	WriteInt (_T("SelectedSkin"), m_uiCurrSkin);

	CBCGPVisualManager::SetDefaultManager (NULL);

	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

void CBCGPSkinsApp::PreLoadState ()
{
	CImageStyle::m_strImagePath = GetString (_T("ImagePath"), _T(""));
	CImageStyle::m_bIsInternalImage = GetInt (_T("InternalImageBright"), TRUE);
	CImageStyle::m_nHighlight = GetInt (_T("ImageBright"), 100);
	CImageStyle::m_clrText = GetInt (_T("TextColor"), globalData.clrBtnText);

	SetSkin (GetInt (_T("SelectedSkin"), ID_LOOK_2000));
}

void CBCGPSkinsApp::SetSkin (UINT nSkin)
{
	m_uiCurrSkin = nSkin;

	if (m_uiCurrSkin == 0)
	{
		// Skin loaded from DLL ("More skins" tab)
		return;
	}

	switch (nSkin)
	{
	case ID_LOOK_2000:
		CBCGPVisualManager::SetDefaultManager (NULL);
		CBCGPVisualManager::GetInstance ()->SetLook2000 ();
		break;

	case ID_LOOK_XP:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_LOOK_WIN_XP:
		if (!CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
		{
			AfxMessageBox (_T("This skin can be viewed under Windows(r) XP themes only. Because your system doesn't support Windows (r) XP theme, you'll see an Office XP look"));
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_LOOK_2003:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		break;

	case ID_LOOK_VS2005:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		break;

	case ID_LOOK_VS2008:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2008));
		break;

	case ID_LOOK_2007_1:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case ID_LOOK_2007_2:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case ID_LOOK_2007_3:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case ID_LOOK_2007_4:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case ID_LOOK_MAC:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CMacStyle));
		break;

	case ID_LOOK_EXOTIC:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CFunnyStyle));
		break;

	case ID_LOOK_IMAGE:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CImageStyle));
		break;
	}

	CBCGPVisualManager::GetInstance ()->RedrawAll ();
}

// App command to run the dialog
void CBCGPSkinsApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}
