//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MenuBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "MenuBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuBar

CMenuBar::CMenuBar()
	: m_bTempVisible (FALSE)
	, m_bSaveState   (FALSE)
{
}

CMenuBar::~CMenuBar()
{
}


BEGIN_MESSAGE_MAP(CMenuBar, CBCGPMenuBar)
	//{{AFX_MSG_MAP(CMenuBar)
	ON_WM_KILLFOCUS()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMenuBar message handlers

void CMenuBar::CloseTemp ()
{
	if (m_bTempVisible && !m_bTracked)
	{
		ShowControlBar (FALSE, FALSE, FALSE);
		m_bTempVisible = FALSE;
	}
}

void CMenuBar::OnKillFocus(CWnd* pNewWnd) 
{
	CBCGPMenuBar::OnKillFocus(pNewWnd);

	CloseTemp ();
}

void CMenuBar::OnCancelMode() 
{
	CBCGPMenuBar::OnCancelMode();
	
	CloseTemp ();
}

BOOL CMenuBar::IsVisible () const
{
	BOOL bVisible = CBCGPMenuBar::IsVisible ();

	if (m_bSaveState && m_bTempVisible)
	{
		bVisible = FALSE;
	}

	return bVisible;
}

BOOL CMenuBar::SaveState (LPCTSTR lpszProfileName/* = NULL*/, int nIndex/* = -1*/, UINT uiID/* = (UINT) -1*/)
{
	m_bSaveState = TRUE;

	return CBCGPMenuBar::SaveState (lpszProfileName, nIndex, uiID);
}
