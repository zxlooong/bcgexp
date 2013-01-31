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
// LinkButton.cpp: implementation of the CBCGPMSMCategorieBarButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPMSMCategorieBarButton.h"
#include "BCGPMSMVisualManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const int nTextMargin = 3;
static const int nSeparatorWidth = 8;
static const CString strDummyAmpSeq = _T("\001\001");

IMPLEMENT_SERIAL(CBCGPMSMCategorieBarButton, CBCGPToolbarButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGPMSMCategorieBarButton::CBCGPMSMCategorieBarButton ()
{
	Initialize ();
}

//***************************************************************************************
CBCGPMSMCategorieBarButton::CBCGPMSMCategorieBarButton (LPCTSTR lpszLabel, UINT nID)
{
	m_strText = lpszLabel;
	m_nID     = nID;

	Initialize ();
}

CBCGPMSMCategorieBarButton::~CBCGPMSMCategorieBarButton ()
{

}

void CBCGPMSMCategorieBarButton::Initialize ()
{
	m_bText = TRUE;
}

void CBCGPMSMCategorieBarButton::OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages,
								BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight,
								BOOL bDrawBorder, BOOL /*bGrayDisabledButtons*/)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (this);

	m_bHorz = bHorz;

	//----------------------
	// Fill button interior:
	//----------------------
	FillInterior (pDC, rect, bHighlight);

	BOOL bHot = bHighlight;
	CSize sizeImage = (pImages == NULL) ? CSize (0, 0) : pImages->GetImageSize (TRUE);

	CRect rectInternal = rect;

	CFont* pOldFont = (CFont*)(pDC->SelectObject (&globalData.fontBold)); 

	//--------------------
	// Draw button's text:
	//--------------------
	CBCGPVisualManager::BCGBUTTON_STATE state = CBCGPVisualManager::ButtonsIsRegular;

	if (bHighlight)
	{
		state = CBCGPVisualManager::ButtonsIsHighlighted;
	}
	else if (m_nStyle & (TBBS_PRESSED | TBBS_CHECKED))
	{
		//-----------------------
		// Pressed in or checked:
		//-----------------------
		state = CBCGPVisualManager::ButtonsIsPressed;
	}

	COLORREF clrText = CBCGPVisualManager::GetInstance ()->GetToolbarButtonTextColor (
		this, state);

	pDC->SetTextColor (clrText);
	CString strText = m_strText;
	CRect rectText = rectInternal;
	UINT uiTextFormat = 0;

	rectText.top += 7;
	uiTextFormat = DT_SINGLELINE;

	if (bHorz)
	{
		pDC->DrawText (strText, &rectText, uiTextFormat | DT_CENTER);
	}

	pDC->SelectObject (pOldFont); 

	//--------------------
	// Draw button border:
	//--------------------
	if (!bCustomizeMode && HaveHotBorder () && bDrawBorder)
	{
		if (m_nStyle & (TBBS_PRESSED | TBBS_CHECKED))
		{
			//-----------------------
			// Pressed in or checked:
			//-----------------------
			CBCGPVisualManager::GetInstance ()->OnDrawButtonBorder (pDC,
				this, rect, CBCGPVisualManager::ButtonsIsPressed);
		}
		else if (bHot && !(m_nStyle & TBBS_DISABLED) &&
			!(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
		{
			CBCGPVisualManager::GetInstance ()->OnDrawButtonBorder (pDC,
				this, rect, CBCGPVisualManager::ButtonsIsHighlighted);
		}
	}
}

SIZE CBCGPMSMCategorieBarButton::OnCalculateSize (
								CDC* pDC,
								const CSize& sizeDefault,
								BOOL bHorz)
{
	ASSERT_VALID (pDC);

	CBCGPMSMVisualManager* pManager = DYNAMIC_DOWNCAST (CBCGPMSMVisualManager,
		CBCGPVisualManager::GetInstance ());

	if (pManager == NULL)
	{
		return CBCGPToolbarButton::OnCalculateSize (pDC, sizeDefault, bHorz);
	}

	if(!IsVisible())
	{
		return CSize(0,0);
	}

	CSize size = sizeDefault;

	if ((m_nStyle & TBBS_SEPARATOR) == 0)
	{
		if (!IsDrawImage () || GetImage () < 0)
		{
			CSize sizeExtra = m_bExtraSize ? 
				CBCGPVisualManager::GetInstance ()->GetButtonExtraBorder () : CSize (0, 0);

			if (bHorz)
			{
				size.cx = sizeExtra.cx;
			}
			else
			{
				size.cy = sizeExtra.cy;
			}
		}

		m_sizeText = CSize (0, 0);

		if (!m_strText.IsEmpty () && IsDrawText ())
		{
			CFont* pOldFont = (CFont*)(pDC->SelectObject (&globalData.fontBold)); 

			CRect rectText (0, 0, 
				sizeDefault.cx * 3, sizeDefault.cy);

			UINT uiTextFormat = DT_CENTER | DT_CALCRECT;
			if (m_bWrapText)
			{
				uiTextFormat |= DT_WORDBREAK;
			}

			pDC->DrawText (	m_strText, rectText, uiTextFormat);
			m_sizeText = rectText.Size ();
			m_sizeText.cx += 2 * nTextMargin;

			size.cx = max (size.cx, m_sizeText.cx) + 6 * nTextMargin;
			size.cy = m_sizeText.cy + 11;

			pDC->SelectObject (pOldFont);
		}
	}

	return size;
}
