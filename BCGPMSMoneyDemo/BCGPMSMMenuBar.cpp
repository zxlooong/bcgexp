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
// BCGPMSMMenuBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSMMenuBar.h"

#include "BCGPMSMVisualManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMMenuBar

IMPLEMENT_DYNCREATE(CBCGPMSMMenuBar, CBCGPMenuBar)

CBCGPMSMMenuBar::CBCGPMSMMenuBar ()
{
}

CBCGPMSMMenuBar::~CBCGPMSMMenuBar ()
{
}

BEGIN_MESSAGE_MAP(CBCGPMSMMenuBar, CBCGPMenuBar)
	//{{AFX_MSG_MAP(CBCGPMSMMenuBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMMenuBar message handlers

int CBCGPMSMMenuBar::OnCreate (LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPMenuBar::OnCreate (lpCreateStruct) == -1)
		return -1;

	SetBarStyle((GetBarStyle () & 
		~(CBRS_GRIPPER | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT))
		| CBRS_SIZE_DYNAMIC);
	SetBorders ();
	
	return 0;
}
