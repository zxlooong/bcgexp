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
// VirtualGridDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPGridExample.h"
#include "VirtualGridDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static BOOL CALLBACK GridCallback (BCGPGRID_DISPINFO* pdi, LPARAM)
{
	ASSERT (pdi != NULL);

    int nRow = pdi->item.nRow;	// Row of an item
	int nCol = pdi->item.nCol;	// Column of an item

	if (nCol == 0)
	{
		pdi->item.varValue = (long) nRow;
	}
	else
	{
		pdi->item.varValue = (long) rand ();
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVirtualGridDlg dialog


CVirtualGridDlg::CVirtualGridDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVirtualGridDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVirtualGridDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVirtualGridDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVirtualGridDlg)
	DDX_Control(pDX, IDC_GRID_RECT, m_wndGridLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVirtualGridDlg, CDialog)
	//{{AFX_MSG_MAP(CVirtualGridDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtualGridDlg message handlers

BOOL CVirtualGridDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rectGrid;
	m_wndGridLocation.GetClientRect (&rectGrid);
	m_wndGridLocation.MapWindowPoints (this, &rectGrid);

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
	m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);

	m_wndGrid.SetReadOnly ();
	
	m_wndGrid.InsertColumn (0, _T("A"), 70);
	m_wndGrid.InsertColumn (1, _T("B"), 50);
	m_wndGrid.InsertColumn (2, _T("C"), 50);
	m_wndGrid.InsertColumn (3, _T("D"), 50);
	m_wndGrid.InsertColumn (4, _T("E"), 50);

	srand ((unsigned) time (NULL));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVirtualGridDlg::OnAdd() 
{
	CWaitCursor wait;

	m_wndGrid.RemoveAll ();
	m_wndGrid.EnableVirtualMode (GridCallback);
	m_wndGrid.SetVirtualRows (100000000);
	m_wndGrid.AdjustLayout ();	
}
