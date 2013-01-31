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
// EditDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "EditDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CEditDialogBar, CBCGPDialogBar, VERSIONABLE_SCHEMA | 1)

/////////////////////////////////////////////////////////////////////////////
// CEditDialogBar

CEditDialogBar::CEditDialogBar()
{
	EnableVisualManagerStyle ();
}

CEditDialogBar::~CEditDialogBar()
{
}


BEGIN_MESSAGE_MAP(CEditDialogBar, CBCGPDialogBar)
	//{{AFX_MSG_MAP(CEditDialogBar)
	ON_WM_SIZE()
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditDialogBar message handlers

void CEditDialogBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDialogBar::OnSize(nType, cx, cy);

	if (cx != 0 || cy != 0)
	{
		Resize(cx, cy);
	}
}

LRESULT CEditDialogBar::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
	if (!CBCGPDialogBar::HandleInitDialog (wParam, lParam))
	{
		return 0L;
	}

	return OnInitDialogBar();
}

BOOL CEditDialogBar::OnInitDialogBar()
{
	CRect rect;
	GetWindowRect (rect);

	m_szWindow = rect.Size ();

	int count = (int)m_ResizeInfo.GetSize ();
	for (int i = 0; i < count; i++)
	{
		XResizeInfo& ri = m_ResizeInfo[i];

		CWnd* pWnd = GetDlgItem (ri.m_id);
		ASSERT_VALID (pWnd);

		pWnd->GetWindowRect (ri.m_rectInit);
		ScreenToClient (ri.m_rectInit);
	}

	return TRUE;
}

void CEditDialogBar::AddResize(UINT nID, XResize resize)
{
	XResizeInfo info (nID, resize);
	m_ResizeInfo.Add (info);
}

void CEditDialogBar::Resize(int cx, int cy)
{
	int count = (int)m_ResizeInfo.GetSize ();

	if (count == 0)
	{
		return;
	}

	HDWP hDwp = ::BeginDeferWindowPos (count);

	for (int i = 0; i < count; i++)
	{
		const XResizeInfo& ri = m_ResizeInfo[i];

		DWORD dwFlags = SWP_NOMOVE;
		if (ri.m_resize == e_ResizeMoveH ||
			ri.m_resize == e_ResizeMoveV ||
			ri.m_resize == e_ResizeMoveHV)
		{
			dwFlags = SWP_NOSIZE;
		}

		CSize szDiff (cx - m_szWindow.cx, cy - m_szWindow.cy);

		CWnd* pWnd = GetDlgItem (ri.m_id);
		ASSERT_VALID (pWnd);

		CRect rect (ri.m_rectInit);
		if (ri.m_resize == e_ResizeMoveH || ri.m_resize == e_ResizeMoveHV)
		{
			rect.OffsetRect (szDiff.cx, 0);
		}

		if (ri.m_resize == e_ResizeMoveV || ri.m_resize == e_ResizeMoveHV)
		{
			rect.OffsetRect (0, szDiff.cy);
		}

		if (ri.m_resize == e_ResizeSizeH || ri.m_resize == e_ResizeSizeHV)
		{
			rect.right += szDiff.cx;
		}

		if (ri.m_resize == e_ResizeSizeV || ri.m_resize == e_ResizeSizeHV)
		{
			rect.bottom += szDiff.cy;
		}

		::DeferWindowPos (hDwp, pWnd->GetSafeHwnd (), HWND_TOP, 
			rect.left, rect.top, rect.Width (), rect.Height (), SWP_NOZORDER | SWP_NOOWNERZORDER | dwFlags);
	}

	::EndDeferWindowPos (hDwp);
}
