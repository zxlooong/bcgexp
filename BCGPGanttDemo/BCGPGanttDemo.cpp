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
// BCGPGanttDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPGanttDemo.h"

#include "MainFrm.h"
#include "BCGPGanttDemoDoc.h"
#include "BCGPGanttDemoView.h"
#include "GanttTooltipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoApp

BEGIN_MESSAGE_MAP(CBCGPGanttDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CBCGPGanttDemoApp)
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
// CBCGPGanttDemoApp construction

CBCGPGanttDemoApp::CBCGPGanttDemoApp()
#ifndef _BCGPGANTT_STANDALONE
	: CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
#endif
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

#ifdef _BCGPGANTT_STANDALONE
int CBCGPGanttDemoApp::GetSectionInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault /*= 0*/)
{
	return GetProfileInt(lpszSection, lpszEntry, nDefault);
}

BOOL CBCGPGanttDemoApp::WriteSectionInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue )
{
	return WriteProfileInt(lpszSection, lpszEntry, nValue);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only CBCGPGanttDemoApp object

CBCGPGanttDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoApp initialization

BOOL CBCGPGanttDemoApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
#ifndef _BCGPGANTT_STANDALONE	
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Examples"));
#else
	SetRegistryKey(_T("BCGSoft\\BCGGantt\\Samples"));
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

#ifndef _BCGPGANTT_STANDALONE
	SetRegistryBase (_T("Settings"));
#endif

#ifndef _BCGPGANTT_STANDALONE
	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();

    CBCGPToolTipParams params;
    params.m_bVislManagerTheme = TRUE;
    globalData.m_nMaxToolTipWidth = 150;

    GetTooltipManager ()->SetTooltipParams (
        0xFFFF,
        RUNTIME_CLASS (CBCGPToolTipCtrl),
        &params);

#endif
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBCGPGanttDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CBCGPGanttDemoView));
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
// CBCGPGanttDemoApp message handlers

int CBCGPGanttDemoApp::ExitInstance() 
{
#ifndef _BCGPGANTT_STANDALONE
	BCGCBProCleanUp();
#endif

	return CWinApp::ExitInstance();
}

#ifdef _BCGPGANTT_STANDALONE

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
#ifndef _BCGPGANTT_STANDALONE
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
#ifdef _BCGPGANTT_STANDALONE
	afx_msg void OnMail();
	afx_msg void OnURL();
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnLink (const CString& str);
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
void CBCGPGanttDemoApp::OnAppAbout()
{
#ifndef _BCGPGANTT_STANDALONE
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
#else
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
#endif
}

#ifndef _BCGPGANTT_STANDALONE

void CBCGPGanttDemoApp::PreLoadState ()
{
	GetContextMenuManager()->AddMenu (_T("Gantt View"), IDR_GANTT_CLIENT);
	GetContextMenuManager()->AddMenu (_T("Gantt Task"), IDR_GANTT_TASK);
}

#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoApp message handlers
