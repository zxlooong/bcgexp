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
// Page4.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcontrols.h"
#include "Page4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage4 property page

IMPLEMENT_DYNCREATE(CPage4, CBCGPPropertyPage)

CPage4::CPage4() : CBCGPPropertyPage(CPage4::IDD)
{
	//{{AFX_DATA_INIT(CPage4)
	m_strValue1 = _T("");
	m_strValue2 = _T("");
	m_strValue3 = _T("");
	m_strValue4 = _T("");
	m_strValue5 = _T("");
	//}}AFX_DATA_INIT
}

CPage4::~CPage4()
{
}

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage4)
	DDX_Control(pDX, IDC_MASKEDIT5, m_wndMaskEdit5);
	DDX_Control(pDX, IDC_MASKEDIT4, m_wndMaskEdit4);
	DDX_Control(pDX, IDC_MASKEDIT3, m_wndMaskEdit3);
	DDX_Control(pDX, IDC_MASKEDIT2, m_wndMaskEdit2);
	DDX_Control(pDX, IDC_MASKEDIT1, m_wndMaskEdit1);
	DDX_Text(pDX, IDC_VALUE1, m_strValue1);
	DDX_Text(pDX, IDC_VALUE2, m_strValue2);
	DDX_Text(pDX, IDC_VALUE3, m_strValue3);
	DDX_Text(pDX, IDC_VALUE4, m_strValue4);
	DDX_Text(pDX, IDC_VALUE5, m_strValue5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage4, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CPage4)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage4 message handlers

BOOL CPage4::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();
	
	// Mask 1: phone number
	m_wndMaskEdit1.EnableMask(
		_T(" ddd  ddd dd dd"),	// The mask string
		_T("(___) ___-__-__"),	// Literal, "_" char = character entry
		_T(' '));				// Default char
	m_wndMaskEdit1.SetValidChars(NULL);					// Valid string characters 
	m_wndMaskEdit1.SetWindowText(_T("(123) 123-12-12"));

	// Mask 2: State, Zip Code
	m_wndMaskEdit2.EnableMask(
		_T("       cc       ddddd-dddd"),	// The mask string
		_T("State: __, Zip: _____-____"),	// Literal, "_" char = character entry
		_T(' '));							// Backspace replace char
	m_wndMaskEdit2.SetValidChars(NULL);							// Valid string characters 
	m_wndMaskEdit2.SetWindowText(_T("State: NY, Zip: 12345-6789"));
	// Mask 3: serial code
	m_wndMaskEdit3.EnableMask(
		_T("     AAAA AAAA AAAA AAAA"),	// The mask string
		_T("S/N: ____-____-____-____"),	// Literal, "_" char = character entry
		_T('_'));							// Backspace replace char
	m_wndMaskEdit3.SetValidChars(NULL);							// Valid string characters 
	m_wndMaskEdit3.SetWindowText(_T("S/N: FPR5-5678-1234-8765"));

	// Mask 4: 0xFFFF
	m_wndMaskEdit4.EnableMask(
		_T("  AAAA"),	// The mask string
		_T("0x____"),	// Literal, "_" char = character entry
		_T('_'));		// Backspace replace char
	m_wndMaskEdit4.SetValidChars(_T("1234567890ABCDEFabcdef")); // Valid string characters 
	m_wndMaskEdit4.SetWindowText(_T("0x01AF"));

	// Mask 5: digits only
	m_wndMaskEdit5.DisableMask();					// Don't use the mask
	m_wndMaskEdit5.SetValidChars(_T("1234567890"));	// Valid string characters 
	m_wndMaskEdit5.SetWindowText(_T("1234567890"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage4::OnButtonGet() 
{
	m_wndMaskEdit1.GetWindowText(m_strValue1);
	m_wndMaskEdit2.GetWindowText(m_strValue2);
	m_wndMaskEdit3.GetWindowText(m_strValue3);
	m_wndMaskEdit4.GetWindowText(m_strValue4);
	m_wndMaskEdit5.GetWindowText(m_strValue5);
	UpdateData(FALSE);
}
