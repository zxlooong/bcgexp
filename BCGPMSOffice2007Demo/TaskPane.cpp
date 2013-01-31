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
// TaskPane.cpp : implementation of the CTaskPane class
//

#include "stdafx.h"
#include "BCGPMSOffice2007Demo.h"
#include "TaskPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskPane

BEGIN_MESSAGE_MAP(CTaskPane, CBCGPTasksPane)
	//{{AFX_MSG_MAP(CTaskPane)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskPane construction/destruction

CTaskPane::CTaskPane()
{
}

CTaskPane::~CTaskPane()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTaskPane message handlers

int CTaskPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	SetWindowText (_T("Clipboard"));

	if (CBCGPTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create tasks pane windows.
	// TODO: create your own tasks panes here:

	return 0;
}
