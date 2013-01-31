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
// RecurrenceConfirmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "RecurrenceConfirmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceConfirmDlg dialog


CRecurrenceConfirmDlg::CRecurrenceConfirmDlg(const CString& strDescription, 
											 BOOL bOpen, CWnd* pParent /*=NULL*/)
	: CBCGPDialog(bOpen ? IDD_APP_REC_OPEN : IDD_APP_REC_DELETE, pParent)
	, m_strDescription (strDescription)
	, m_bOccurrence (TRUE)
{
	EnableVisualManagerStyle ();

	//{{AFX_DATA_INIT(CRecurrenceConfirmDlg)
	//}}AFX_DATA_INIT
}


void CRecurrenceConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecurrenceConfirmDlg)
	DDX_Control(pDX, IDC_APP_REC_ICON, m_stIcon);
	DDX_Control(pDX, IDC_APP_REC_QUEST, m_stQuestion);
	DDX_Control(pDX, IDC_APP_REC_RADIO_OCCURRENCE, m_btnOccurrence);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecurrenceConfirmDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CRecurrenceConfirmDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceConfirmDlg message handlers

BOOL CRecurrenceConfirmDlg::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp ()->LoadStandardIcon (IDI_WARNING);
	if (hIcon != NULL)
	{
		m_stIcon.SetIcon (hIcon);
	}

	CString strFmt;
	m_stQuestion.GetWindowText (strFmt);

	CString strTxt;
	strTxt.Format (strFmt, m_strDescription);

	m_stQuestion.SetWindowText (strTxt);

	m_btnOccurrence.SetCheck (BST_CHECKED);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecurrenceConfirmDlg::OnOK() 
{
	m_bOccurrence = m_btnOccurrence.GetCheck () == BST_CHECKED;
	
	CBCGPDialog::OnOK();
}

