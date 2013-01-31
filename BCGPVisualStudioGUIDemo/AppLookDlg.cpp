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
// AppLookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "AppLookDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg dialog


CAppLookDlg::CAppLookDlg(BOOL bStartup, CWnd* pParent /*=NULL*/)
	: CDialog(CAppLookDlg::IDD, pParent),
	m_bStartup (bStartup)
{
	//{{AFX_DATA_INIT(CAppLookDlg)
	m_bShowAtStartup = FALSE;
	m_bOneNoteTabs = TRUE;
	m_bDockTabColors = FALSE;
	m_bRoundedTabs = FALSE;
	m_bCustomTooltips = TRUE;
	m_nAppLook = 6;
	m_nStyle = 0;
	m_bActiveTabCloseButton = FALSE;
	//}}AFX_DATA_INIT

	m_nAppLook = theApp.GetInt (_T("AppLook"), 6);
	m_nStyle = theApp.GetInt (_T("AppStyle"), 0);;
	m_bShowAtStartup = theApp.GetInt (_T("ShowAppLookAtStartup"), TRUE);
	m_bOneNoteTabs = theApp.GetInt (_T("OneNoteTabs"), TRUE);
	m_bDockTabColors = theApp.GetInt (_T("DockTabColors"), FALSE);
	m_bRoundedTabs = theApp.GetInt (_T("RoundedTabs"), FALSE);
	m_bCustomTooltips = theApp.GetInt (_T("CustomTooltips"), TRUE);
	m_bActiveTabCloseButton = theApp.GetInt (_T("ActiveTabCloseButton"), FALSE);
}


void CAppLookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppLookDlg)
	DDX_Control(pDX, IDC_STYLE, m_wndStyle);
	DDX_Control(pDX, IDC_ROUNDED_TABS, m_wndRoundedTabs);
	DDX_Control(pDX, IDC_DOCK_TAB_COLORS, m_wndDockTabColors);
	DDX_Control(pDX, IDC_ONENOTE_TABS, m_wndOneNoteTabs);
	DDX_Control(pDX, IDOK, m_wndOK);
	DDX_Control(pDX, IDCANCEL, m_wndCancel);
	DDX_Check(pDX, IDC_SHOW_AT_STARTUP, m_bShowAtStartup);
	DDX_Check(pDX, IDC_ONENOTE_TABS, m_bOneNoteTabs);
	DDX_Check(pDX, IDC_DOCK_TAB_COLORS, m_bDockTabColors);
	DDX_Check(pDX, IDC_ROUNDED_TABS, m_bRoundedTabs);
	DDX_Check(pDX, IDC_CUSTOM_TOOLTIPS, m_bCustomTooltips);
	DDX_CBIndex(pDX, IDC_APP_LOOK, m_nAppLook);
	DDX_CBIndex(pDX, IDC_STYLE, m_nStyle);
	DDX_Check(pDX, IDC_ACTIVETAB_CLOSE_BUTTON, m_bActiveTabCloseButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppLookDlg, CDialog)
	//{{AFX_MSG_MAP(CAppLookDlg)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_CBN_SELENDOK(IDC_APP_LOOK, OnAppLook)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg message handlers

BOOL CAppLookDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData (FALSE);

	OnAppLook ();

	if (m_bStartup)
	{
		SetLook ();

		if (!m_bShowAtStartup)
		{
			EndDialog (IDCANCEL);
			return TRUE;
		}

		CRect rectBtn;

		// Hide "Cancel" button:
		m_wndCancel.GetWindowRect (rectBtn);
		ScreenToClient (rectBtn);

		m_wndOK.MoveWindow (rectBtn);

		m_wndCancel.EnableWindow (FALSE);
		m_wndCancel.ShowWindow (SW_HIDE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAppLookDlg::OnOK() 
{
	SetLook ();
	CDialog::OnOK();
}

void CAppLookDlg::SetLook ()
{
	CWaitCursor wait;

	UpdateData ();

	CMainFrame* pMainFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
	if (pMainFrame != NULL)
	{
		pMainFrame->LockWindowUpdate ();
	}

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case 0:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case 1:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case 2:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		break;

	case 3:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));

		if (m_bRoundedTabs)
		{
			CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D_ROUNDED;
		}

		CBCGPVisualManagerVS2005::m_bRoundedAutohideButtons = m_bRoundedTabs;
		break;

	case 4:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		break;

	case 5:
		switch (m_nStyle)
		{
		case 0:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
			break;

		case 1:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
			break;

		case 2:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
			break;

		case 3:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
			break;
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case 6:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2008));
		break;
	}

	theApp.WriteInt (_T("AppLook"), m_nAppLook);
	theApp.WriteInt (_T("ShowAppLookAtStartup"), m_bShowAtStartup);
	theApp.WriteInt (_T("OneNoteTabs"), m_bOneNoteTabs);
	theApp.WriteInt (_T("DockTabColors"), m_bDockTabColors);
	theApp.WriteInt (_T("RoundedTabs"), m_bRoundedTabs);
	theApp.WriteInt (_T("CustomTooltips"), m_bCustomTooltips);
	theApp.WriteInt (_T("AppStyle"), m_nStyle);
	theApp.WriteInt (_T("ActiveTabCloseButton"), m_bActiveTabCloseButton);

	switch (m_nAppLook)
	{
	case 2:	// Office 2003
	case 3:	// VS 2005
	case 4:	// Windows XP
	case 5:	// Office 2007
	case 6:	// VS 2008
		{
			CWindowDC dc (NULL);
			theApp.m_bHiColorIcons = dc.GetDeviceCaps (BITSPIXEL) >= 16;

			if (globalData.bIsWindows9x && dc.GetDeviceCaps (BITSPIXEL) == 16)
			{
				theApp.m_bHiColorIcons = FALSE;
			}

			CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		}
		break;

	default:
		theApp.m_bHiColorIcons = FALSE;
	}

	CBCGPTabbedControlBar::ResetTabs ();

	if (m_bCustomTooltips)
	{
		CBCGPToolTipParams params;
		params.m_bVislManagerTheme = TRUE;

		theApp.GetTooltipManager ()->SetTooltipParams (
			BCGP_TOOLTIP_TYPE_ALL,
			RUNTIME_CLASS (CBCGPToolTipCtrl),
			&params);
	}
	else
	{
		theApp.GetTooltipManager ()->SetTooltipParams (
			BCGP_TOOLTIP_TYPE_ALL,
			NULL,
			NULL);
	}

	if (pMainFrame != NULL)
	{
		pMainFrame->OnChangeLook (
					m_bOneNoteTabs/* OneNote tabs */,
					m_bOneNoteTabs /* MDI tab colors*/,
					m_nAppLook != 0 /* VS.NET look */,
					m_bDockTabColors /* Dock tab colors*/,
					m_nAppLook == 3 || m_nAppLook == 6	/* VS.NET 2005 MDI tabs */,
					m_nAppLook == 4 || m_nAppLook == 2 || m_nAppLook == 3 || m_nAppLook == 5 || m_nAppLook == 6	/* Extended toolbox */,
					m_bActiveTabCloseButton);

		pMainFrame->UnlockWindowUpdate ();
		pMainFrame->RedrawWindow ();
	}
}

void CAppLookDlg::OnApply() 
{
	SetLook ();

	if (!m_bStartup)
	{
		m_wndCancel.SetWindowText (_T("Close"));
	}
}

void CAppLookDlg::OnAppLook() 
{
	UpdateData ();

	m_wndRoundedTabs.EnableWindow (m_nAppLook == 3);
	m_wndStyle.EnableWindow (m_nAppLook == 5);
}
