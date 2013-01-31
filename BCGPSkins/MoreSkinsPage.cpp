//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2007 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MoreSkinsPage.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpskins.h"
#include "MoreSkinsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_MORE_SKINS	10

const int nMargin = 10;

/////////////////////////////////////////////////////////////////////////////
// CMoreSkinsPage

CMoreSkinsPage::CMoreSkinsPage()
{
	m_sizeButton = CSize (0, 0);
}

CMoreSkinsPage::~CMoreSkinsPage()
{
}


BEGIN_MESSAGE_MAP(CMoreSkinsPage, CWnd)
	//{{AFX_MSG_MAP(CMoreSkinsPage)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMoreSkinsPage message handlers

BOOL CMoreSkinsPage::Create(const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
	return CWnd::Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, rect, pParentWnd, nID, NULL);
}

BOOL CMoreSkinsPage::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

void CMoreSkinsPage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rectClient;
	GetClientRect (rectClient);

	dc.FillSolidRect (rectClient, ::GetSysColor (COLOR_WINDOW));

	const CString strLabel = _T("Click \"More Skins\" button to load more skins from your collection/Internet");

	CRect rectText = rectClient;
	rectText.DeflateRect (nMargin, nMargin);

	rectText.top += 2 * nMargin + m_sizeButton.cy;

	CFont* pOldFont = dc.SelectObject (&globalData.fontRegular);
	dc.SetBkMode (TRANSPARENT);

	dc.DrawText (strLabel, rectText, DT_LEFT | DT_WORDBREAK);

	dc.SelectObject (pOldFont);
}

int CMoreSkinsPage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy (0, 0, 0, 0);
	m_btnMoreSkins.Create (_T("More Skins..."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		rectDummy, this, IDC_MORE_SKINS);

	m_btnMoreSkins.SetFont (&globalData.fontRegular);
	m_sizeButton = m_btnMoreSkins.SizeToContent ();

	return 0;
}

void CMoreSkinsPage::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	m_btnMoreSkins.SetWindowPos (NULL, nMargin, nMargin, -1, -1,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

BOOL CMoreSkinsPage::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == IDC_MORE_SKINS)
	{
		if (theApp.GetSkinManager ()->ShowSelectSkinDlg ())
		{
			theApp.SetSkin (0);
		}
	}
	
	return CWnd::OnCommand(wParam, lParam);
}
