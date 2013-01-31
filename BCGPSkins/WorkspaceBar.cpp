//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2007 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// WorkspaceBar.cpp : implementation of the CWorkspaceBar class
//

#include "stdafx.h"
#include "BCGPSkins.h"
#include "WorkspaceBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UM_REDRAWNCAREA	(WM_USER + 1)

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar

BEGIN_MESSAGE_MAP(CWorkspaceBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CWorkspaceBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_REDRAWNCAREA, OnRedrawNCArea)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar construction/destruction

CWorkspaceBar::CWorkspaceBar()
{
	// TODO: add one-time construction code here

}

CWorkspaceBar::~CWorkspaceBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CWorkspaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tabs window:
	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_3D, rectDummy, this, 1))
	{
		TRACE0("Failed to create workspace tab window\n");
		return -1;      // fail to create
	}

	m_wndTabs.SetFlatFrame ();

	m_wndTabs.SetImageList (IDB_WORKSPACE, 16, RGB (255, 0, 255));

	m_Images.Create (16, 16, ILC_COLOR8 | ILC_MASK, 0, 0);
	m_Images.SetBkColor (::GetSysColor (COLOR_WINDOW));

	CBitmap bmp;
	VERIFY (bmp.LoadBitmap (IDB_SKINS));

	m_Images.Add (&bmp, RGB (255, 0, 255));

	if (!m_wndSkinsList.Create (
			WS_BORDER | WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_NOCOLUMNHEADER   , rectDummy, 
			&m_wndTabs, 2))
	{
		TRACE0("Failed to create workspace tab window\n");
		return -1;      // fail to create
	}

	m_wndSkinsList.SetImageList (&m_Images, LVSIL_SMALL);

	m_wndSkinsList.InsertColumn (0, _T(""));

	m_wndSkinsList.InsertItem (0, _T("Default"), 0);
	m_wndSkinsList.InsertItem (1, _T("Office XP®"), 1);
	m_wndSkinsList.InsertItem (2, _T("Windows XP®"), 2);
	m_wndSkinsList.InsertItem (3, _T("Office 2003®"), 3);
	m_wndSkinsList.InsertItem (4, _T("Mac ®"), 4);
	m_wndSkinsList.InsertItem (5, _T("Exotic"), 5);
	m_wndSkinsList.InsertItem (6, _T("Background Image"), 6);

	m_wndDummy.Create (_T(""), WS_CHILD | WS_VISIBLE, rectDummy, &m_wndTabs);

	m_wndTabs.AddTab (&m_wndSkinsList, _T("Skins"), 0 /* Image number */);
	m_wndTabs.AddTab (&m_wndDummy, _T("Dummy"), 1 /* Image number */);
	return 0;
}

void CWorkspaceBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// Tab control should cover a whole client area:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	m_wndSkinsList.SetColumnWidth (0, cx - ::GetSystemMetrics (SM_CXVSCROLL));

	PostMessage (UM_REDRAWNCAREA);
}

LRESULT CWorkspaceBar::OnRedrawNCArea(WPARAM, LPARAM)
{
	RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_NOERASE);

//	if (m_pDockBar != NULL)
//	{
//		m_pDockBar->RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_NOERASE);
//	}

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CSkinsList

CSkinsList::CSkinsList()
{
}

CSkinsList::~CSkinsList()
{
}


BEGIN_MESSAGE_MAP(CSkinsList, CListCtrl)
	//{{AFX_MSG_MAP(CSkinsList)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinsList message handlers

void CSkinsList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	theApp.SetSkin (GetNextItem (-1, LVNI_SELECTED));
	*pResult = 0;
}
