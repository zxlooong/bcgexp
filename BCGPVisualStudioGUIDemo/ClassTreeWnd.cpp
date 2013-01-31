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
// ClassTreeWnd.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "ClassTreeWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassTreeWnd

CClassTreeWnd::CClassTreeWnd()
{
}

CClassTreeWnd::~CClassTreeWnd()
{
}


BEGIN_MESSAGE_MAP(CClassTreeWnd, CTreeCtrl)
	//{{AFX_MSG_MAP(CClassTreeWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassTreeWnd message handlers

BOOL CClassTreeWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT (pNMHDR != NULL);

	if (pNMHDR->code == TTN_SHOW && GetToolTips () != NULL)
	{
		GetToolTips ()->SetWindowPos (&wndTop, -1, -1, -1, -1,
			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}
