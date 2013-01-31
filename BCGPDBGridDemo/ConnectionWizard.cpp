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
// ConnectionWizard.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpdbgriddemo.h"
#include "ConnectionWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectionWizard

IMPLEMENT_DYNAMIC(CConnectionWizard, CPropertySheet)

CConnectionWizard::CConnectionWizard(CWnd* pParentWnd)
	:CPropertySheet (_T("Connection Wizard"), pParentWnd)
{
	AddPage (&m_pageDataType);
	AddPage (&m_pageDataSource);
	AddPage (&m_pageDataTable);
	AddPage (&m_pageFields);

	SetWizardMode ();
}

CConnectionWizard::~CConnectionWizard()
{
}


BEGIN_MESSAGE_MAP(CConnectionWizard, CPropertySheet)
	//{{AFX_MSG_MAP(CConnectionWizard)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectionWizard message handlers
