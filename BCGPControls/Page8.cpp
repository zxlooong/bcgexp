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
// Page8.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "bcgpcontrols.h"
#include "Page8.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage8 property page

IMPLEMENT_DYNCREATE(CPage8, CBCGPPropertyPage)

CPage8::CPage8() : CBCGPPropertyPage(CPage8::IDD)
{
	//{{AFX_DATA_INIT(CPage8)
	m_dblValue = 0.0;
	m_bUserCommands = FALSE;
	//}}AFX_DATA_INIT
}

CPage8::~CPage8()
{
}

void CPage8::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage8)
	DDX_Control(pDX, IDC_EDIT, m_wndEdit);
	DDX_Control(pDX, IDC_CALCULATOR, m_wndCalcRect);
	DDX_Text(pDX, IDC_EDIT, m_dblValue);
	DDX_Check(pDX, IDC_USER_COMMANDS, m_bUserCommands);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage8, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CPage8)
	ON_BN_CLICKED(IDC_USER_COMMANDS, OnUserCommands)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage8 message handlers

BOOL CPage8::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();
	
	CRect rectCalc;
	m_wndCalcRect.GetWindowRect (&rectCalc);
	ScreenToClient (rectCalc);

	rectCalc.DeflateRect (1, 1);
	m_wndCalc.CreateControl (this, rectCalc, IDC_CALCULATOR);

	m_wndCalc.SetFocus ();

	m_wndEdit.EnableCalculatorButton ();
	
	return FALSE;
}

void CPage8::OnUserCommands() 
{
	UpdateData ();

	if (m_bUserCommands)
	{
		CStringList lstCommands;

		lstCommands.AddTail (_T("Sin"));
		lstCommands.AddTail (_T("Cos"));
		lstCommands.AddTail (_T("Tan"));
		lstCommands.AddTail (_T("Exp"));
		lstCommands.AddTail (_T("X^3"));
		lstCommands.AddTail (_T("X^2"));
		lstCommands.AddTail (_T("Ln"));
		lstCommands.AddTail (_T("Log"));
		lstCommands.AddTail (_T("1/X"));
		lstCommands.AddTail (_T("Pi"));

		m_wndCalc.SetAdditionalCommands (lstCommands);
		m_wndEdit.EnableCalculatorButton (&lstCommands);
	}
	else
	{
		m_wndCalc.RemoveAdditionalCommands ();
		m_wndEdit.EnableCalculatorButton ();
	}

	m_wndCalc.SetValue (0.);
	m_wndCalc.SetError (FALSE);
}

static void CalculatorUserCommand (CBCGPCalculator* pCalculator, UINT uiCmd)
{
	double dblVal = pCalculator->GetValue ();

	switch (uiCmd)
	{
	case CBCGPCalculator::idCommandUser:	// Sin
		dblVal = sin (dblVal);
		break;

	case CBCGPCalculator::idCommandUser + 1:	// Cos
		dblVal = cos (dblVal);
		break;

	case CBCGPCalculator::idCommandUser + 2:	// Tan
		dblVal = tan (dblVal);
		break;

	case CBCGPCalculator::idCommandUser + 3:	// Exp
		dblVal = exp (dblVal);
		break;

	case CBCGPCalculator::idCommandUser + 4:	// X^3
		dblVal = pow (dblVal, 3);
		break;

	case CBCGPCalculator::idCommandUser + 5:	// X^2
		dblVal = pow (dblVal, 2);
		break;

	case CBCGPCalculator::idCommandUser + 6:	// Ln
		dblVal = log (dblVal);
		break;

	case CBCGPCalculator::idCommandUser + 7:	// Log
		dblVal = log10 (dblVal);
		break;

	case CBCGPCalculator::idCommandUser + 8:	// 1/X
		if (dblVal == 0.)
		{
			pCalculator->SetError ();
			return;
		}
		else
		{
			dblVal = 1. / dblVal;
		}
		break;

	case CBCGPCalculator::idCommandUser + 9:	// Pi
		dblVal = 3.1415926535897932;
		break;
	}

	pCalculator->SetValue (dblVal);
}

void CMyCalc::OnUserCommand (UINT uiCmd)
{
	CalculatorUserCommand (this, uiCmd);
}

void CMyEdit::OnCalculatorUserCommand (CBCGPCalculator* pCalculator, UINT uiCmd)
{
	CalculatorUserCommand (pCalculator, uiCmd);
}
