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
// ResourcePage.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpmsoffice2007demo.h"
#include "ResourcePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourcePage property page

IMPLEMENT_DYNCREATE(CResourcePage, CBCGPPropertyPage)

CResourcePage::CResourcePage() : CBCGPPropertyPage(CResourcePage::IDD)
{
	//{{AFX_DATA_INIT(CResourcePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CResourcePage::~CResourcePage()
{
}

void CResourcePage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResourcePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResourcePage, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CResourcePage)
	ON_BN_CLICKED(IDC_HOME, OnHome)
	ON_BN_CLICKED(IDC_CONTACT, OnContact)
	ON_BN_CLICKED(IDC_PRODUCT, OnProduct)
	ON_BN_CLICKED(IDC_SUPPORT, OnSupport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourcePage message handlers

void CResourcePage::OnHome() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com"), NULL, NULL, NULL);
}

void CResourcePage::OnContact() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com/contact.htm"), NULL, NULL, NULL);
}

void CResourcePage::OnProduct() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com/bcgcontrolbarpro.htm"), NULL, NULL, NULL);
}

void CResourcePage::OnSupport() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com/support.htm"), NULL, NULL, NULL);
}
