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
// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemoView.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg

IMPLEMENT_DYNAMIC(COptionsDlg, CBCGPPropertySheet)

COptionsDlg::COptionsDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBCGPPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	SetLook (CBCGPPropertySheet::PropSheetLook_Tree, 150 /* Tree control width */);
	SetIconsList (IDB_OPTIONSIMAGES, 16 /* Image width */);

	CBCGPPropSheetCategory* pCat1 = AddTreeCategory (_T("Environment"), 0, 1);

	AddPageToTree (pCat1, &m_Page11, -1, 2);
	AddPageToTree (pCat1, &m_Page12, -1, 2);

	CBCGPPropSheetCategory* pCat2 = AddTreeCategory (_T("Source Control"), 0, 1);

	AddPageToTree (pCat2, &m_Page21, -1, 2);
	AddPageToTree (pCat2, &m_Page22, -1, 2);

	CBCGPPropSheetCategory* pCat3 = AddTreeCategory (_T("Text Editor"), 0, 1);

	AddPageToTree (pCat3, &m_Page31, -1, 2);
	AddPageToTree (pCat3, &m_Page32, -1, 2);
}

COptionsDlg::~COptionsDlg()
{
}


BEGIN_MESSAGE_MAP(COptionsDlg, CBCGPPropertySheet)
	//{{AFX_MSG_MAP(COptionsDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers
