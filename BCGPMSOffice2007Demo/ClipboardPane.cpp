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
// ClipboardPane.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpmsoffice2007demo.h"
#include "ClipboardPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int xMargin = 10;
static const int yMargin = 10;

/////////////////////////////////////////////////////////////////////////////
// CClipboardPane

IMPLEMENT_DYNAMIC(CClipboardPane, CBCGPDialogBar)

CClipboardPane::CClipboardPane()
{
	EnableVisualManagerStyle ();

	//{{AFX_DATA_INIT(CClipboardPane)
	//}}AFX_DATA_INIT

	m_mButtonsFullWidth = 0;
}

CClipboardPane::~CClipboardPane()
{
}

void CClipboardPane::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipboardPane)
	DDX_Control(pDX, IDC_LABEL, m_wndLabel);
	DDX_Control(pDX, IDC_ITEMS, m_wndItems);
	DDX_Control(pDX, IDC_OPTION1, m_btnOption1);
	DDX_Control(pDX, IDC_OPTION2, m_btnOption2);
	DDX_Control(pDX, IDC_PASTE_ALL, m_btnPasteAll);
	DDX_Control(pDX, IDC_CLEAR_ALL, m_btnClearAll);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipboardPane, CBCGPDialogBar)
	//{{AFX_MSG_MAP(CClipboardPane)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipboardPane message handlers


void CClipboardPane::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDialogBar::OnSize(nType, cx, cy);
	AdjustControls ();	
}

LRESULT CClipboardPane::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = CBCGPDialogBar::HandleInitDialog(wParam, lParam);

	m_btnPasteAll.SetImage (IDB_PASTE_ALL);
	CSize sizePasteAll = m_btnPasteAll.SizeToContent ();

	m_btnClearAll.SetImage (IDB_CLEAR_ALL);
	CSize sizeClearAll = m_btnClearAll.SizeToContent ();

	m_btnOption1.SetCheck (1);

	m_mButtonsFullWidth = sizePasteAll.cx + sizeClearAll.cx + xMargin;

	// Add some summy items to list:
	m_wndItems.AddString (_T("Clipboard Item 1"));
	m_wndItems.AddString (_T("Clipboard Item 2"));
	m_wndItems.AddString (_T("Clipboard Item 3"));
	m_wndItems.AddString (_T("Clipboard Item 4"));
	m_wndItems.AddString (_T("Clipboard Item 5"));

	m_wndItems.SetCurSel (0);

	return lRes;
}

void CClipboardPane::AdjustControls ()
{
	if (m_wndItems.GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	const int cx = rectClient.Width ();
	const int cy = rectClient.Height ();

	if (cx < m_mButtonsFullWidth + 2 * xMargin)
	{
		// Hide buttons text
		CString str1;
		m_btnPasteAll.GetWindowText (str1);

		CString str2;
		m_btnClearAll.GetWindowText (str2);

		if (!str1.IsEmpty () && !str1.IsEmpty ())
		{
			m_btnPasteAll.SetWindowText (_T(""));
			m_btnPasteAll.SetTooltip (str1);

			m_btnClearAll.SetWindowText (_T(""));
			m_btnClearAll.SetTooltip (str2);
		}
	}
	else
	{
		// Show buttons text
		CString str1;
		m_btnPasteAll.GetTooltip (str1);

		CString str2;
		m_btnClearAll.GetTooltip (str2);

		if (!str1.IsEmpty () && !str1.IsEmpty ())
		{
			m_btnPasteAll.SetWindowText (str1);
			m_btnPasteAll.SetTooltip (_T(""));

			m_btnClearAll.SetWindowText (str2);
			m_btnClearAll.SetTooltip (_T(""));
		}
	}

	m_btnPasteAll.SizeToContent ();
	m_btnClearAll.SizeToContent ();

	CRect rectBtn1;
	m_btnPasteAll.GetWindowRect (rectBtn1);
	ScreenToClient (&rectBtn1);

	m_btnPasteAll.SetWindowPos (NULL, xMargin, rectBtn1.top, -1, -1, 
		SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_btnClearAll.SetWindowPos (NULL, xMargin + rectBtn1.Width () + xMargin, rectBtn1.top, -1, -1,
			SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);

	m_btnPasteAll.RedrawWindow ();
	m_btnPasteAll.RedrawWindow ();

	CRect rectLabel;
	m_wndLabel.GetWindowRect (rectLabel);
	ScreenToClient (rectLabel);

	m_wndLabel.SetWindowPos (NULL, xMargin, rectLabel.top, -1, -1, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);

	CRect rectList;
	m_wndItems.GetWindowRect (rectList);
	ScreenToClient (rectList);

	CRect rectCheck1;
	m_btnOption1.GetWindowRect (rectCheck1);
	ScreenToClient (rectCheck1);

	CRect rectCheck2;
	m_btnOption2.GetWindowRect (rectCheck2);
	ScreenToClient (rectCheck2);

	int nOptionsHeight = rectCheck2.bottom - rectCheck1.top + yMargin;
	int nListHeight = max (2 * yMargin, cy - rectList.top - nOptionsHeight);

	m_wndItems.SetWindowPos (NULL, -1, -1, cx - 2 * rectList.left, nListHeight,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndItems.RedrawWindow ();

	int yOptions = rectList.top + nListHeight + yMargin / 2;

	m_btnOption1.SetWindowPos (NULL, xMargin, yOptions, -1, -1, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_btnOption2.SetWindowPos (NULL, xMargin, yOptions + rectCheck1.Height () + yMargin / 2, -1, -1, SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);

	m_btnOption1.RedrawWindow ();
	m_btnOption2.RedrawWindow ();
}

