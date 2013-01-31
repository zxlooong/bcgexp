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
// LineWeightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "drawcli.h"
#include "LineWeightDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineWeightDlg dialog


CLineWeightDlg::CLineWeightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineWeightDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineWeightDlg)
	m_penSize = 0;
	//}}AFX_DATA_INIT
}

void CLineWeightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineWeightDlg)
	DDX_Control(pDX, IDC_SPIN1, m_SpinCtrl);
	DDX_Text(pDX, IDC_WEIGHT, m_penSize);
	DDV_MinMaxUInt(pDX, m_penSize, 0, 100);
	//}}AFX_DATA_MAP
}

BOOL CLineWeightDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_SpinCtrl.SetRange(0, 100);
	m_SpinCtrl.SetBase(10);
	m_SpinCtrl.SetPos(max (m_penSize, 0));
	return TRUE;
}

BEGIN_MESSAGE_MAP(CLineWeightDlg, CDialog)
	//{{AFX_MSG_MAP(CLineWeightDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineWeightDlg message handlers
