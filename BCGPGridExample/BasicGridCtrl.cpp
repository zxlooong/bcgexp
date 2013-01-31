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
// BasicGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPGridExample.h"
#include "BasicGridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBasicGridCtrl

CBasicGridCtrl::CBasicGridCtrl()
{
}

CBasicGridCtrl::~CBasicGridCtrl()
{
}

BEGIN_MESSAGE_MAP(CBasicGridCtrl, CBCGPGridCtrl)
	//{{AFX_MSG_MAP(CBasicGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBasicGridCtrl message handlers

int CBasicGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	EnableMarkSortedColumn (FALSE);
	EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);

	const int nColumns = 26;
	
	for (int nColumn = 0; nColumn < nColumns; nColumn++)
	{
		CString strColumn;
		strColumn.Format (_T("%c"), _T('A') + nColumn);

		InsertColumn (nColumn, strColumn, 80);
	}

	for (int nRow = 0; nRow < 100; nRow++)
	{
		CBCGPGridRow* pRow = CreateRow (GetColumnCount ());

		for (int i = 0; i < GetColumnCount (); i++)
		{
			pRow->GetItem (i)->SetValue ((long) ((nRow + 1) * (i + 1)));
		}

		AddRow (pRow, FALSE);
	}

	LoadState (_T("BasicGrid"));
	AdjustLayout ();

	return 0;
}

void CBasicGridCtrl::OnDestroy() 
{
	SaveState (_T("BasicGrid"));
	CBCGPGridCtrl::OnDestroy();
}
