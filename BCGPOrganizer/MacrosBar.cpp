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
// MacrosBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "MacrosBar.h"

#include "BCGPOrganizerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMacrosBar

CMacrosBar::CMacrosBar()
{
}

CMacrosBar::~CMacrosBar()
{
}

BOOL CMacrosBar::Create(CWnd* pParentWnd, UINT nID)
{
	if (CTreeCtrl::Create (WS_CHILD | WS_VISIBLE |
		TVS_FULLROWSELECT | TVS_SHOWSELALWAYS, CRect (0, 0, 0, 0), pParentWnd, nID))
	{
		CBitmap bmp;
		if (bmp.LoadBitmap (IDB_MACROS_FOLDERS))
		{
			m_ImageList.Create (16, 16, ILC_COLOR32 | ILC_MASK, 10, 1);
			m_ImageList.Add (&bmp, (CBitmap*) NULL);

			SetImageList (&m_ImageList, TVSIL_NORMAL);
			SetImageList (&m_ImageList, TVSIL_STATE);
		}

		HTREEITEM hItem = NULL;
		hItem = InsertItem (_T("Accessibility"), 2, 2);
		SetItemData (hItem, IDR_EDITOR_MACROS_1);
		SelectItem (hItem);
		hItem = InsertItem (_T("AddDirAsSlnFolder"), 2, 2);
		SetItemData (hItem, IDR_EDITOR_MACROS_2);
		hItem = InsertItem (_T("DevStudio6Editor"), 2, 2);
		SetItemData (hItem, IDR_EDITOR_MACROS_3);
		hItem = InsertItem (_T("EnvironmentEvents"), 2, 2);
		SetItemData (hItem, IDR_EDITOR_MACROS_4);
		hItem = InsertItem (_T("MakeAddin"), 2, 2);
		SetItemData (hItem, IDR_EDITOR_MACROS_5);
		hItem = InsertItem (_T("Utilities"), 2, 2);
		SetItemData (hItem, IDR_EDITOR_MACROS_6);
		hItem = InsertItem (_T("VSDebugger"), 2, 2);
		SetItemData (hItem, IDR_EDITOR_MACROS_7);
		hItem = InsertItem (_T("VSEditor"), 2, 2);
		SetItemData (hItem, IDR_EDITOR_MACROS_8);

		return TRUE;
	}

	return FALSE;
}


BEGIN_MESSAGE_MAP(CMacrosBar, CTreeCtrl)
	//{{AFX_MSG_MAP(CMacrosBar)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacrosBar message handlers

void CMacrosBar::OnDblclk(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem != NULL)
	{
		CBCGPFrameWnd* pFrameWnd = (CBCGPFrameWnd*)GetTopLevelFrame ();
		ASSERT_VALID (pFrameWnd);

		CBCGPOrganizerDoc* pDoc = 
			DYNAMIC_DOWNCAST(CBCGPOrganizerDoc, pFrameWnd->GetActiveDocument ());

		if (pDoc != NULL)
		{
			pDoc->LoadMacros ((UINT)GetItemData (hItem), GetItemText (hItem));
		}
	}
	
	*pResult = 0;
}

void CMacrosBar::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnDblclk(pNMHDR, pResult);
}
