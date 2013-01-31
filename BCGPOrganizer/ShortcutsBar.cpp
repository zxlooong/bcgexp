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
// ShortcutsBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "ShortcutsBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutsBar

CShortcutsBar::CShortcutsBar()
{
}

CShortcutsBar::~CShortcutsBar()
{
}

BOOL CShortcutsBar::Create(CWnd* pParentWnd, UINT nID)
{
	return CBCGPTasksPane::Create (_T("Home"), pParentWnd, 
		CRect (0, 0, 0, 0), FALSE, nID, WS_CHILD | WS_VISIBLE);
}


BEGIN_MESSAGE_MAP(CShortcutsBar, CBCGPTasksPane)
	//{{AFX_MSG_MAP(CShortcutsBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutsBar message handlers

int CShortcutsBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nGroup1 = AddGroup (0, _T("What can you do:"));

	AddTask (nGroup1, _T("Create a new appointment..."), -1, ID_PLANNER_NEW_APPOINTMENT);
	AddTask (nGroup1, _T("Edit Macro..."), -1, ID_DUMMY);
	AddTask (nGroup1, _T("Check you E-mail"), -1, ID_STATUSBAR_REFRESH);
	
	int nGroup2 = AddGroup (0, _T("Choose color scheme:"));

	AddTask (nGroup2, _T("Office 2007 (blue)"), -1, ID_VIEW_APPLOOK_2007_2);
	AddTask (nGroup2, _T("Office 2007 (black)"), -1, ID_VIEW_APPLOOK_2007_3);
	AddTask (nGroup2, _T("Office 2007 (silver)"), -1, ID_VIEW_APPLOOK_2007_4);
	AddTask (nGroup2, _T("Office 2007 (aqua)"), -1, ID_VIEW_APPLOOK_2007_1);
	
	return 0;
}
