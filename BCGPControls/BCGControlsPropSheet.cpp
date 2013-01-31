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
// BCGControlsPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcontrols.h"
#include "BCGControlsPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BCGControlsPropSheet

IMPLEMENT_DYNAMIC(BCGControlsPropSheet, CBCGPPropertySheet)

BCGControlsPropSheet::BCGControlsPropSheet(CWnd* pParentWnd)
	:CBCGPPropertySheet (IDS_CAPTION, pParentWnd)
{
	BOOL b32BitIcons = globalData.bIsOSAlphaBlendingSupport;

	if (globalData.m_nBitsPerPixel == 16)
	{
		// 32-bit icons in 16 bpp display mode
		// are correctly displayed in WinXP only

		OSVERSIONINFO osvi;
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		::GetVersionEx (&osvi);

		b32BitIcons = (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT &&
						(osvi.dwMajorVersion > 5 ||
						(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion >= 1)));
	}

	SetLook (CBCGPPropertySheet::PropSheetLook_OutlookBar);
	SetIconsList (b32BitIcons ? IDB_ICONS32 : IDB_ICONS, 32);

	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page4);
	AddPage(&m_Page5);
	AddPage(&m_Page6);
	AddPage(&m_Page7);
	AddPage(&m_Page8);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BCGControlsPropSheet::~BCGControlsPropSheet()
{
}


BEGIN_MESSAGE_MAP(BCGControlsPropSheet, CBCGPPropertySheet)
	//{{AFX_MSG_MAP(BCGControlsPropSheet)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BCGControlsPropSheet message handlers


BOOL BCGControlsPropSheet::OnInitDialog() 
{
	BOOL bResult = CBCGPPropertySheet::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return bResult;
}

HCURSOR BCGControlsPropSheet::OnQueryDragIcon() 
{
	return (HCURSOR) m_hIcon;
}

void BCGControlsPropSheet::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
	}
	else
	{
		CBCGPPropertySheet::OnSysCommand(nID, lParam);
	}
}
