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
// MergeGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MergeGridItem.h"
#include "MergeGridCtrl.h"

#include "BCGPGridExample.h"
#include "resource.h"       // main symbols
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMergeGridCtrl

IMPLEMENT_DYNCREATE(CMergeGridCtrl, CBCGPGridCtrl)

CMergeGridCtrl::CMergeGridCtrl()
{
	m_bProtectRangeChart = FALSE;
}

CMergeGridCtrl::~CMergeGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CMergeGridCtrl, CBCGPGridCtrl)
	//{{AFX_MSG_MAP(CMergeGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Methods:

CBCGPGridItem* CMergeGridCtrl::CreateItem (int nRow, int nColumn)
{
	if (m_rangeChart.IsInRange (nRow, nColumn))
	{
		return new CMergeGridItem (&m_ImageChart, 0);
	}

	return CBCGPGridCtrl::CreateItem (nRow, nColumn);
}
//*****************************************************************************
int CMergeGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	//--------------------------
	// Set grid general options:
	//--------------------------
	EnableMarkSortedColumn (TRUE, FALSE);
	EnableHeader (TRUE, 0);
	//SetSelectionBorder (FALSE);

	//-----------------------------------
	// Load images for some merges cells:
	//-----------------------------------
	m_ImageChart.Load (IDB_GRIDMERGE_CHART);
	m_ImageChart.SetSingleImage ();
	m_rangeChart.Set (1, 9, 3, 18);

	//-------------
	// Add columns:
	//-------------
	const int nColumns = 5;
	
	for (int nColumn = 0; nColumn < nColumns; nColumn++)
	{
		CString strColumn;
		strColumn.Format (_T("%c"), _T('A') + nColumn);

		InsertColumn (nColumn, strColumn, 85);
	}

	//-----------------
	// Add simple data:
	//-----------------
	for (int nRow = 0; nRow < 49; nRow++)
	{
		CBCGPGridRow* pRow = CBCGPGridCtrl::CreateRow (GetColumnCount ());

		for (int i = 0; i < GetColumnCount (); i++)
		{
			CString strText;
			strText.Format (_T("%d"), ((nRow + 1) * (i + 1)));
			pRow->GetItem (i)->SetValue ((LPCTSTR)strText);
		}

		AddRow (pRow, FALSE);
	}

	//-------------
	// Merge cells:
	//-------------
	CBCGPGridRange rangeA (0, 0, 1, 1);
	MergeRange (rangeA, FALSE);
	CBCGPGridRange rangeB (1, 3, 2, 4);
	MergeRange (rangeB, FALSE);
	CBCGPGridRange rangeC (2, 6, 3, 7);
	MergeRange (rangeC, FALSE);
	CBCGPGridRange rangeColumn1 (0, 22, 0, 27);
	MergeRange (rangeColumn1, FALSE);
	CBCGPGridRange rangeLine1 (1, 22, 2, 22);
	MergeRange (rangeLine1, FALSE);
	CBCGPGridRange rangeLine2 (1, 23, 2, 23);
	MergeRange (rangeLine2, FALSE);
	CBCGPGridRange rangeLine3 (1, 24, 2, 24);
	MergeRange (rangeLine3, FALSE);
	CBCGPGridRange rangeLine4 (1, 25, 2, 25);
	MergeRange (rangeLine4, FALSE);
	CBCGPGridRange rangeLine5 (1, 26, 2, 26);
	MergeRange (rangeLine5, FALSE);
	CBCGPGridRange rangeLine6 (1, 27, 2, 27);
	MergeRange (rangeLine6, FALSE);
	CBCGPGridRange rangeColumn2 (3, 22, 4, 27);
	MergeRange (rangeColumn2, FALSE);

	MergeRange (m_rangeChart, FALSE);
	m_bProtectRangeChart = TRUE;

	LoadState (_T("MergeGrid"));

	//---------------------
	// Select 4 grid cells:
	//---------------------
	SetCurSel (CBCGPGridItemID (3, 1));
	SetCurSel (CBCGPGridItemID (5, 2), SM_CONTINUE_SEL_GROUP | SM_SINGLE_ITEM);

	AdjustLayout ();

	return 0;
}
//********************************************************************************
BOOL CMergeGridCtrl::ReplaceItem (CBCGPGridItemID id, CBCGPGridItem *pNewItem)
{
	ASSERT_VALID (this);
	
	CBCGPGridRow* pRow = GetRow (id.m_nRow);
	if (pRow != NULL)
	{
		ASSERT_VALID (pRow);
		return pRow->ReplaceItem (id.m_nColumn, pNewItem, FALSE, FALSE);
	}

	return FALSE;
}
//********************************************************************************
void CMergeGridCtrl::OnDestroy() 
{
	SaveState (_T("MergeGrid"));

	CBCGPGridCtrl::OnDestroy();
}
//********************************************************************************
BOOL CMergeGridCtrl::CanMergeRange (const CBCGPGridRange& range, BOOL bMerge)
{
	int nTop = min (range.m_nTop, range.m_nBottom);
	int nBottom = max (range.m_nTop, range.m_nBottom);
	int nLeft = min (range.m_nLeft, range.m_nRight);
	int nRight = max (range.m_nLeft, range.m_nRight);

	// if range intersects with m_rangeChart
	if (m_bProtectRangeChart &&
		m_rangeChart.m_nTop <= nBottom && m_rangeChart.m_nBottom >= nTop &&
		m_rangeChart.m_nLeft <= nRight && m_rangeChart.m_nRight >= nLeft)
	{
		return FALSE; // not allow merging
	}

	return CBCGPGridCtrl::CanMergeRange (range, bMerge);
}
