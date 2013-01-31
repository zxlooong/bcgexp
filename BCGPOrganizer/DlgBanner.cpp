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
// DlgBanner.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "DlgBanner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBanner

CDlgBanner::CDlgBanner()
{
}

CDlgBanner::~CDlgBanner()
{
}


BEGIN_MESSAGE_MAP(CDlgBanner, CBCGPStatic)
	//{{AFX_MSG_MAP(CDlgBanner)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBanner message handlers

void CDlgBanner::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect (rect);

	CFont* pOldFont = dc.SelectObject (&globalData.fontBold);
	ASSERT (pOldFont != NULL);

	dc.SetTextColor (CBCGPVisualManager::GetInstance ()->OnDrawMenuLabel (&dc, rect));
	dc.SetBkMode (TRANSPARENT);

	rect.DeflateRect (5, 0);

	CString strText;
	GetWindowText (strText);

	dc.DrawText (strText, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER);

	dc.SelectObject (pOldFont);
}
