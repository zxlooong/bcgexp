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
// Page7.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcontrols.h"
#include "Page7.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage7 property page

IMPLEMENT_DYNCREATE(CPage7, CBCGPPropertyPage)

CPage7::CPage7() : CBCGPPropertyPage(CPage7::IDD)
{
	//{{AFX_DATA_INIT(CPage7)
	m_strSelectedFolder = _T("c:\\");
	//}}AFX_DATA_INIT
}

CPage7::~CPage7()
{
}

void CPage7::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage7)
	DDX_Control(pDX, IDC_LIST1, m_wndShellList);
	DDX_Control(pDX, IDC_TREE1, m_wbdShellTree);
	DDX_Text(pDX, IDC_SELECTED_FOLDER, m_strSelectedFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage7, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CPage7)
	ON_BN_CLICKED(IDC_SELECT_FOLDER, OnSelectFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage7 message handlers

void CPage7::OnSelectFolder() 
{
	if (theApp.GetShellManager ()->BrowseForFolder (
		m_strSelectedFolder, this, m_strSelectedFolder))
	{
		UpdateData (FALSE);
	}
}

BOOL CPage7::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();
	
	m_wbdShellTree.Expand (m_wbdShellTree.GetRootItem (), TVE_EXPAND);
	m_wbdShellTree.SetRelatedList (&m_wndShellList);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
