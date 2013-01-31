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
// RibbonTableButton.cpp: implementation of the CRibbonTableButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bcgpmsoffice2007demo.h"
#include "RibbonTableButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CELLS_X	10
#define CELLS_Y	8

IMPLEMENT_DYNCREATE(CRibbonTableButton, CBCGPRibbonPaletteButton)

int	CRibbonTableButton::m_nRows = 0;
int	CRibbonTableButton::m_nColumns = 0;

LPCTSTR lpszDefaultCaption = _T("Insert Table");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRibbonTableButton::CRibbonTableButton(
		UINT	nID,
		LPCTSTR	lpszText,
		int		nSmallImageIndex,
		int		nLargeImageIndex) :
	CBCGPRibbonPaletteButton (nID, lpszText, nSmallImageIndex, nLargeImageIndex,
							CSize (18, 18), 0, FALSE)
{
	AddGroup (lpszDefaultCaption, CELLS_X * CELLS_Y);
	SetIconsInRow (CELLS_X);
}

CRibbonTableButton::~CRibbonTableButton()
{
}

void CRibbonTableButton::OnDrawPaletteIcon (CDC* pDC, CRect rectIcon, 
											int nIconIndex, CBCGPRibbonPaletteIcon* /*pIcon*/,
											COLORREF /*clrText*/)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pDC);

	rectIcon.DeflateRect (2, 2);

	COLORREF color = globalData.clrWindowText;

	if (nIconIndex / CELLS_X + 1 <= m_nRows &&
		(nIconIndex % CELLS_X) + 1 <= m_nColumns)
	{
		COLORREF clrInner = RGB (255, 226, 148);

		pDC->Draw3dRect (rectIcon, clrInner, clrInner);

		color = RGB (239, 72, 16);
		rectIcon.InflateRect (1, 1);
	}

	pDC->Draw3dRect (rectIcon, color, color);
}

void CRibbonTableButton::NotifyHighlightListItem (int nIndex)
{
	ASSERT_VALID (this);

	if (m_pPopupMenu != NULL)
	{
		if (nIndex < 0)
		{
			m_nRows = m_nColumns = 0;
		}
		else
		{
			m_nRows = nIndex / CELLS_X + 1;
			m_nColumns = (nIndex % CELLS_X) + 1;
		}

		CString strCaption = lpszDefaultCaption;
		if (m_nColumns > 0 && m_nRows > 0)
		{
			strCaption.Format (_T("%dx%d Table"), m_nColumns, m_nRows);
		}

		SetGroupName (0, strCaption);

		RedrawIcons ();
	}

	CBCGPRibbonPaletteButton::NotifyHighlightListItem (nIndex);
}

void CRibbonTableButton::OnShowPopupMenu ()
{
	ASSERT_VALID (this);

	m_nRows = m_nColumns = 0;
	SetGroupName (0, lpszDefaultCaption);

	CBCGPRibbonPaletteButton::OnShowPopupMenu ();
}
