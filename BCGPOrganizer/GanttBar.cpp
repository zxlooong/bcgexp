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
// GanttBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "GanttBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGanttBar

CGanttBar::CGanttBar()
{
}

CGanttBar::~CGanttBar()
{
}

BOOL CGanttBar::Create(CWnd* pParentWnd, UINT nID)
{
	return CBCGPCalendar::Create (WS_CHILD | WS_VISIBLE, CRect (0, 0, 0, 0), pParentWnd, nID);
}


BEGIN_MESSAGE_MAP(CGanttBar, CBCGPCalendar)
	//{{AFX_MSG_MAP(CGanttBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGanttBar message handlers

int CGanttBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPCalendar::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableMutipleSelection (FALSE, 35 /* Max sel days */, TRUE);
	EnableWeekNumbers ();

	return 0;
}
