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
// BCGPMSMCategoriesBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSMoneyDemo.h"
#include "BCGPMSMCategorieBar.h"
#include "BCGPMSMCategorieBarButton.h"

#include "BCGPMSMVisualManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCategorieBar

IMPLEMENT_DYNCREATE(CBCGPMSMCategorieBar, CBCGPMSMToolBar)

CBCGPMSMCategorieBar::CBCGPMSMCategorieBar ()
{
}

CBCGPMSMCategorieBar::~CBCGPMSMCategorieBar ()
{
}

BEGIN_MESSAGE_MAP(CBCGPMSMCategorieBar, CBCGPMSMToolBar)
	//{{AFX_MSG_MAP(CBCGPMSMCategorieBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCategorieBar message handlers

int CBCGPMSMCategorieBar::OnCreate (LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPMSMToolBar::OnCreate (lpCreateStruct) == -1)
		return -1;
	
	RestoreOriginalstate ();

	return 0;
}

BOOL CBCGPMSMCategorieBar::RestoreOriginalstate ()
{
	RemoveAllButtons ();

	InsertButton (CBCGPMSMCategorieBarButton (_T("Home")     , ID_CATEGORIE_1));
	InsertButton (CBCGPMSMCategorieBarButton (_T("Banking")  , ID_CATEGORIE_2));
	InsertButton (CBCGPMSMCategorieBarButton (_T("Bills")    , ID_CATEGORIE_3));
	InsertButton (CBCGPMSMCategorieBarButton (_T("Reports")  , ID_CATEGORIE_4));
	InsertButton (CBCGPMSMCategorieBarButton (_T("Budget")   , ID_CATEGORIE_5));
	InsertButton (CBCGPMSMCategorieBarButton (_T("Investing"), ID_CATEGORIE_6));
	InsertButton (CBCGPMSMCategorieBarButton (_T("Planning") , ID_CATEGORIE_7));
	InsertButton (CBCGPMSMCategorieBarButton (_T("Taxes")    , ID_CATEGORIE_8));

//	EnableCustomizeButton (TRUE, -1, _T(""));

	AdjustLayout ();
	Invalidate ();

	return TRUE;
}
