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
// unitspag.cpp : implementation file
//

#include "stdafx.h"
#include "wordpad.h"
#include "unitspag.h"
#include "helpids.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnitsPage dialog

const DWORD CUnitsPage::m_nHelpIDs[] =
{
	IDC_BOX, IDH_COMM_GROUPBOX,
	IDC_UNITS_IN, IDH_WORDPAD_INCHES,
	IDC_UNITS_CM, IDH_WORDPAD_CENTIMETERS,
	IDC_UNITS_PT, IDH_WORDPAD_POINTS,
	IDC_UNITS_PI, IDH_WORDPAD_PICAS,
	IDC_WORDSEL, IDH_WORDPAD_OPTIONS_AUTOWORDSEL,
	0, 0
};

CUnitsPage::CUnitsPage() : CCSPropertyPage(CUnitsPage::IDD)
{
	//{{AFX_DATA_INIT(CUnitsPage)
	m_nUnits = -1;
	m_bWordSel = FALSE;
	//}}AFX_DATA_INIT
}


void CUnitsPage::DoDataExchange(CDataExchange* pDX)
{
	CCSPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnitsPage)
	DDX_Radio(pDX, IDC_UNITS_IN, m_nUnits);
	DDX_Check(pDX, IDC_WORDSEL, m_bWordSel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUnitsPage, CCSPropertyPage)
	//{{AFX_MSG_MAP(CUnitsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUnitsPage message handlers
