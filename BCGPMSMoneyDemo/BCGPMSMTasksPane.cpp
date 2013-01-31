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
// BCGPMSMTasksPane.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpmsmoneydemo.h"
#include "BCGPMSMTasksPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMTasksPane

IMPLEMENT_DYNAMIC(CBCGPMSMTasksPane, CBCGPTasksPane)

CBCGPMSMTasksPane::CBCGPMSMTasksPane()
{
	m_bWrapTasks = TRUE;
	m_bWrapLabels = TRUE;
}

CBCGPMSMTasksPane::~CBCGPMSMTasksPane()
{
}


BEGIN_MESSAGE_MAP(CBCGPMSMTasksPane, CBCGPTasksPane)
	//{{AFX_MSG_MAP(CBCGPMSMTasksPane)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMTasksPane message handlers

int CBCGPMSMTasksPane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPTasksPane::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nGroup = AddGroup (_T(""));

	COleDateTime now = COleDateTime::GetCurrentTime ();
	CString strDate = now.Format (_T("%B %d, %Y"));

	AddLabel (nGroup, strDate, -1, TRUE);

	AddLabel (nGroup, _T(" "));
	AddLabel (nGroup, _T(" "));
	
	AddLabel (nGroup, _T("Common tasks"), -1, TRUE);
	AddSeparator (nGroup);

	AddTask (nGroup, _T("Learn more about BCGControlBar library"), -1, ID_HELP_BCGSOFT);

	return 0;
}
