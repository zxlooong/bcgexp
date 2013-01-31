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
// MailBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "MailBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailBar

CMailBar::CMailBar()
{
}

CMailBar::~CMailBar()
{
}


BOOL CMailBar::Create(CWnd* pParentWnd, UINT nID)
{
	if (CTreeCtrl::Create (WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
			TVS_LINESATROOT | TVS_HASBUTTONS, CRect (0, 0, 0, 0), pParentWnd, nID))
	{
		CBitmap bmp;
		if (bmp.LoadBitmap (IDB_MAIL_FOLDERS))
		{
			m_ImageList.Create (16, 16, ILC_COLOR32 | ILC_MASK, 10, 1);
			m_ImageList.Add (&bmp, (CBitmap*) NULL);

			SetImageList (&m_ImageList, TVSIL_NORMAL);
			SetImageList (&m_ImageList, TVSIL_STATE);
		}

		HTREEITEM hRoot = InsertItem (_T("Personal Folders"), 0, 0);
		InsertItem (_T("Deleted Items"), 1, 1, hRoot);
		InsertItem (_T("Drafts"), 2, 2, hRoot);
		InsertItem (_T("Inbox"), 3, 3, hRoot);
		InsertItem (_T("Junk E-mail"), 4, 4, hRoot);
		InsertItem (_T("Outbox"), 5, 5, hRoot);
		InsertItem (_T("RSS Feeds"), 6, 6, hRoot);
		InsertItem (_T("Sent Items"), 7, 7, hRoot);
		InsertItem (_T("Search Folders"), 8, 8, hRoot);
		Expand (hRoot, TVE_EXPAND);
/*		
		hRoot = InsertItem (_T("Hotmail"), 10, 10);
		InsertItem (_T("Deleted Items"), 1, 1, hRoot);
		InsertItem (_T("Inbox"), 3, 3, hRoot);
		InsertItem (_T("Junk E-mail"), 4, 4, hRoot);
		InsertItem (_T("Sent Items"), 7, 7, hRoot);
		Expand (hRoot, TVE_EXPAND);
*/		
		return TRUE;
	}

	return FALSE;
}


BEGIN_MESSAGE_MAP(CMailBar, CTreeCtrl)
	//{{AFX_MSG_MAP(CMailBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailBar message handlers
