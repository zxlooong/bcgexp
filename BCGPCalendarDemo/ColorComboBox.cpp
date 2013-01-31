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
// ColorComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPCalendarDemo.h"
#include "ColorComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nMargin = 3;

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox

CColorComboBox::CColorComboBox()
{
}

CColorComboBox::~CColorComboBox()
{
}


BEGIN_MESSAGE_MAP(CColorComboBox, CBCGPComboBox)
	//{{AFX_MSG_MAP(CColorComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox message handlers

int CColorComboBox::CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/) 
{
	return 0;
}

void CColorComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle (lpDIS->hDC);
	ASSERT_VALID (pDC);

	CRect rect = lpDIS->rcItem;
	int nIndex = lpDIS->itemID;

	COLORREF	clText;
	CBrush*		pBrush = NULL;

	if (lpDIS->itemState & ODS_SELECTED)  
	{
		clText = globalData.clrTextHilite; 
		pBrush = &globalData.brHilite;
	} 
	else 
	{
		pBrush = &globalData.brWindow;
		clText = globalData.clrWindowText;
	} 

	if (lpDIS->itemAction & (ODA_DRAWENTIRE | ODA_SELECT))
	{
		pDC->FillRect (rect, pBrush);
	}

	if (nIndex < 0)
	{
		return;
	}

	CString strLabel;
	GetLBText (nIndex, strLabel);

	CRect rectBox = rect;
	rectBox.DeflateRect (nMargin, nMargin);
	
	if (!strLabel.IsEmpty ())
	{
		rectBox.right = rectBox.left + rectBox.Height ();
	}

	COLORREF color = GetColor (nIndex);

	CBrush br (color);
	pDC->FillRect (rectBox, &br);
	pDC->Draw3dRect (rectBox, globalData.clrWindowText, globalData.clrWindowText);

	if (!strLabel.IsEmpty ())
	{
		CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);

		pDC->SetBkMode (TRANSPARENT);
		pDC->SetTextColor (clText);

		CRect rectText = rect;
		rectText.left = rectBox.right + 2 * nMargin;

		pDC->DrawText (strLabel, rectText, DT_SINGLELINE | DT_VCENTER);

		pDC->SelectObject (pOldFont);
	}
}

void CColorComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS) 
{
	lpMIS->itemHeight = globalData.GetTextHeight () + nMargin * 2;
}

int CColorComboBox::AddColor (COLORREF color, CString strLabel)
{
	int nIndex = AddString (strLabel);
	if (nIndex < 0)
	{
		return nIndex;
	}

	m_Colors.SetAt (nIndex, color);
	return nIndex;
}

int CColorComboBox::FindColor (COLORREF color) const
{
	for (POSITION pos = m_Colors.GetStartPosition (); pos != NULL;)
	{
		int nIndex = -1;
		COLORREF colorCurr = RGB (255, 255, 255);

		m_Colors.GetNextAssoc (pos, nIndex, colorCurr);

		if (colorCurr == color)
		{
			return nIndex;
		}
	}

	return -1;
}
