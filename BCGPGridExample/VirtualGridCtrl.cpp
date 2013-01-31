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
// VirtualGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPGridExample.h"
#include "VirtualGridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static BOOL CALLBACK GridCallback (BCGPGRID_DISPINFO* pdi, LPARAM lp)
{
	ASSERT (pdi != NULL);

	CVirtualGridCtrl* pGridCtrl = (CVirtualGridCtrl*) lp;

    int nRow = pdi->item.nRow;	// Row of an item
	int nCol = pdi->item.nCol;	// Column of an item

	pdi->item.varValue = (LPCTSTR) pGridCtrl->GetItemValue (nRow, nCol);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVirtualGridCtrl

CVirtualGridCtrl::CVirtualGridCtrl()
{
}

CVirtualGridCtrl::~CVirtualGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CVirtualGridCtrl, CBCGPGridCtrl)
	//{{AFX_MSG_MAP(CVirtualGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVirtualGridCtrl message handlers

int CVirtualGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	const int nColumns = 5;
	
	for (int nColumn = 0; nColumn < nColumns; nColumn++)
	{
		CString strColumn;
		strColumn.Format (_T("%c"), _T('A') + nColumn);

		InsertColumn (nColumn, strColumn, 150);
	}

	EnableVirtualMode (GridCallback, (LPARAM) this);
	SetVirtualRows (10000000);	// 10 milions

	SetSingleSel (FALSE);
	EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);

	SetEditFirstClick (FALSE);
	
	LoadState (_T("VirtualGrid"));
	AdjustLayout ();

	return 0;
}

void CVirtualGridCtrl::OnDestroy() 
{
	SaveState (_T("VirtualGrid"));
	CBCGPGridCtrl::OnDestroy();
}

void CVirtualGridCtrl::OnItemChanged (CBCGPGridItem* pItem, int nRow, int nColumn)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pItem);

	CBCGPGridRow* pRow = pItem->GetParentRow ();
	if (pRow == NULL)
	{
		return;
	}

	ASSERT_VALID (pRow);

	CString strKey;
	strKey.Format (_T("%d#%d"), nRow, nColumn);

	m_mapChangedItems.SetAt (strKey, (LPCTSTR) (_bstr_t) pItem->GetValue ());
}

CString CVirtualGridCtrl::GetItemValue (int nRow, int nColumn) const
{
	CString strKey;
	strKey.Format (_T("%d#%d"), nRow, nColumn);
	
	CString str;
	if (!m_mapChangedItems.Lookup (strKey, str))
	{
		str.Format(_T("Item %d, %d"), nRow, nColumn);
	}

	return str;
}
