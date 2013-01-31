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
// LinksBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "LinksBar.h"
#include "LinkButton.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CLinksBar, CBCGPToolBar, 1)

/////////////////////////////////////////////////////////////////////////////
// CLinksBar

CLinksBar::CLinksBar()
{
	EnableLargeIcons (FALSE);
}

CLinksBar::~CLinksBar()
{
}


BEGIN_MESSAGE_MAP(CLinksBar, CBCGPToolBar)
	//{{AFX_MSG_MAP(CLinksBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLinksBar message handlers

int CLinksBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	RestoreOriginalstate ();
	return 0;
}

BOOL CLinksBar::OnSendCommand (const CBCGPToolbarButton* pButton)
{
	CLinkButton* pLinkButton = DYNAMIC_DOWNCAST (CLinkButton, pButton);
	if (pLinkButton == NULL)
	{
		// Defauult processing
		return FALSE;
	}

	CString strURL = pLinkButton->GetURL ();

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, GetParentFrame ());
	ASSERT_VALID(pFrame);
	if (pFrame != NULL)
	{
		pFrame->Navigate (strURL);
	}

	return TRUE;
}

BOOL CLinksBar::RestoreOriginalstate ()
{
	RemoveAllButtons ();

	InsertButton (CLinkButton (_T("Best Company"), _T("http://www.bcgsoft.com")));
	InsertButton (CLinkButton (_T("Best Car"), _T("http://www.skoda-auto.com")));
	InsertButton (CLinkButton (_T("Best Rock-Band"), _T("http://www.planetaquarium.com/eng")));
	InsertButton (CLinkButton (_T("Best City"), _T("http://www.enlight.ru/camera/index_e.htm")));

	EnableCustomizeButton (TRUE, (UINT)-1, _T(""));

	AdjustLayout ();
	Invalidate ();

	return TRUE;
}
