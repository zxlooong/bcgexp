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
// PrintTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "PrintTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintTypeDlg dialog


CPrintTypeDlg::CPrintTypeDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CPrintTypeDlg::IDD, pParent)
	, m_Type (0)
{
	EnableVisualManagerStyle ();

	//{{AFX_DATA_INIT(CPrintTypeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrintTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintTypeDlg)
	DDX_Control (pDX, IDC_PRNTYPE_RADIO1, m_Radio1);
	DDX_Control (pDX, IDC_PRNTYPE_RADIO2, m_Radio2);
	DDX_Control (pDX, IDC_PRNTYPE_RADIO3, m_Radio3);
	DDX_Control (pDX, IDC_PRNTYPE_RADIO4, m_Radio4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintTypeDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CPrintTypeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintTypeDlg message handlers

void CPrintTypeDlg::SetType (int type)
{
	ASSERT(0 <= type);
	ASSERT(type <= 3);

	m_Type = type;
}

BOOL CPrintTypeDlg::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	if (m_Type == 1)
	{
		m_Radio2.SetCheck (BST_CHECKED);
	}
	else if (m_Type == 2)
	{
		m_Radio3.SetCheck (BST_CHECKED);
	}
	else if (m_Type == 3)
	{
		m_Radio4.SetCheck (BST_CHECKED);
	}
	else
	{
		m_Radio1.SetCheck (BST_CHECKED);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrintTypeDlg::OnOK() 
{
	if (m_Radio1.GetCheck () == BST_CHECKED)
	{
		m_Type = 0;
	}
	else if (m_Radio2.GetCheck () == BST_CHECKED)
	{
		m_Type = 1;
	}
	else if (m_Radio3.GetCheck () == BST_CHECKED)
	{
		m_Type = 2;
	}
	else if (m_Radio4.GetCheck () == BST_CHECKED)
	{
		m_Type = 3;
	}

	
	CBCGPDialog::OnOK();
}
