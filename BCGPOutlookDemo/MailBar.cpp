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
#include "BCGPOutlookDemo.h"
#include "MailBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailBar dialog


CMailBar::CMailBar()
{
	//{{AFX_DATA_INIT(CMailBar)
	//}}AFX_DATA_INIT
}


void CMailBar::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMailBar)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMailBar, CBCGPDialogBar)
	//{{AFX_MSG_MAP(CMailBar)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailBar message handlers

void CMailBar::AdjustWidth (int cx, UINT uiCtrlID)
{
	const int nMargin = 10;

	CWnd* pWnd = GetDlgItem (uiCtrlID);
	if (pWnd == NULL)
	{
		return;
	}

	CRect rect;
	pWnd->GetWindowRect (rect);
	ScreenToClient (rect);

	rect.right = cx - nMargin;

	pWnd->SetWindowPos (NULL, -1, -1, rect.Width (), rect.Height (),
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CMailBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDialogBar::OnSize(nType, cx, cy);

	AdjustWidth (cx, IDC_MAIL_TO_NAME);
	AdjustWidth (cx, IDC_MAIL_CC_NAME);
	AdjustWidth (cx, IDC_MAIL_SUBJECT_NAME);

}

BOOL CMailBar::OnEraseBkgnd(CDC* pDC) 
{
	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPVisualManager::GetInstance()->OnFillBarBackground (pDC,
		this, rectClient, rectClient);

	return TRUE;
}

HBRUSH CMailBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	#define MAX_CLASS_NAME	255
	#define STATIC_CLASS	_T("Static")
	#define BUTTON_CLASS	_T("Button")

	if (nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN)
	{
		TCHAR lpszClassName [MAX_CLASS_NAME + 1];

		::GetClassName (pWnd->GetSafeHwnd (), lpszClassName, MAX_CLASS_NAME);
		CString strClass = lpszClassName;

		if (strClass == STATIC_CLASS || strClass == BUTTON_CLASS)
		{
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH) ::GetStockObject (HOLLOW_BRUSH);
		}
	}

	return CBCGPDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);
}
