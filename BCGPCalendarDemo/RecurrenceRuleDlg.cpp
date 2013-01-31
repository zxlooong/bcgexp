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
// RecurrenceRuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcalendardemo.h"
#include "RecurrenceRuleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleDlg dialog

IMPLEMENT_DYNAMIC(CRecurrenceRuleDlg, CBCGPDialog);

CRecurrenceRuleDlg::CRecurrenceRuleDlg()
	: m_Rule (NULL)
{
#ifndef _BCGPCALENDAR_STANDALONE
	EnableVisualManagerStyle ();
#endif

	//{{AFX_DATA_INIT(CRecurrenceRuleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CRecurrenceRuleDlg::Create(CWnd* pParentWnd)
{
	return CBCGPDialog::Create (GetID (), pParentWnd);
}

void CRecurrenceRuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecurrenceRuleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecurrenceRuleDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CRecurrenceRuleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleDlg message handlers
