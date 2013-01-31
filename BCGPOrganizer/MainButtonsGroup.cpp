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
// MainButtonsGroup.cpp : implementation file
//

#include "stdafx.h"
#include "bcgporganizer.h"
#include "MainButtonsGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FILE_MARGIN			4

IMPLEMENT_DYNCREATE(CMainButtonsGroup, CBCGPRibbonButtonsGroup)

void CMainButtonsGroup::OnAfterChangeRect (CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	int y = m_rect.top + 2;

	for (int i = 0; i < m_arButtons.GetSize (); i++)
	{
		CBCGPBaseRibbonElement* pButton = m_arButtons [i];
		ASSERT_VALID (pButton);

		pButton->SetParentMenu (m_pParentMenu);

		pButton->OnCalcTextSize (pDC);
		CSize sizeButton = pButton->GetSize (pDC);

		CRect rectButton = m_rect;
		rectButton.DeflateRect (1, 0);

		rectButton.top = y;
		rectButton.bottom = y + sizeButton.cy + 2 * FILE_MARGIN;

		pButton->SetRect (rectButton);
		pButton->OnAfterChangeRect (pDC);

		y = rectButton.bottom;
	}
}

CSize CMainButtonsGroup::GetRegularSize (CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	int cy = 4;

	for (int i = 0; i < m_arButtons.GetSize (); i++)
	{
		CBCGPBaseRibbonElement* pButton = m_arButtons [i];
		ASSERT_VALID (pButton);

		pButton->OnCalcTextSize (pDC);
		CSize sizeButton = pButton->GetSize (pDC);

		cy += sizeButton.cy + 2 * FILE_MARGIN;
	}

	const int nDefaultSize = 300;

	return CSize (
		globalData.GetRibbonImageScale () == 1. ? nDefaultSize : (int) (globalData.GetRibbonImageScale () *  nDefaultSize), 
		cy);
}

void CMainButtonsGroup::OnDraw (CDC* pDC)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	if (m_rect.IsRectEmpty ())
	{
		return;
	}

	for (int i = 0; i < m_arButtons.GetSize (); i++)
	{
		CBCGPBaseRibbonElement* pButton = m_arButtons [i];
		ASSERT_VALID (pButton);

		pButton->OnDraw (pDC);
	}
}

BOOL CMainButtonsGroup::OnMenuKey (UINT nUpperChar)
{
	ASSERT_VALID (this);

	for (int i = 0; i < m_arButtons.GetSize (); i++)
	{
		CBCGPRibbonButton* pButton = DYNAMIC_DOWNCAST (
			CBCGPRibbonButton, m_arButtons [i]);

		if (pButton == NULL)
		{
			continue;
		}

		ASSERT_VALID (pButton);

		CString strLabel = pButton->GetText ();

		int iAmpOffset = strLabel.Find (_T('&'));
		if (iAmpOffset >= 0 && iAmpOffset < strLabel.GetLength () - 1)
		{
			TCHAR szChar [2] = { strLabel.GetAt (iAmpOffset + 1), '\0' };
			CharUpper (szChar);

			if ((UINT) (szChar [0]) == nUpperChar && !pButton->IsDisabled ())
			{
				pButton->OnClick (pButton->GetRect ().TopLeft ());
				return TRUE;
			}
		}
	}

	return FALSE;
}
