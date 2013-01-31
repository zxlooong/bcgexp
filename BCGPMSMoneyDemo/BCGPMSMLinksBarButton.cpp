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
// LinkButton.cpp: implementation of the CBCGPMSMLinksBarButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPMSMLinksBarButton.h"
#include "BCGPMSMVisualManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const int nTextMargin = 3;

IMPLEMENT_SERIAL(CBCGPMSMLinksBarButton, CBCGPToolbarButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGPMSMLinksBarButton::CBCGPMSMLinksBarButton ()
{
	Initialize ();
}

//***************************************************************************************
CBCGPMSMLinksBarButton::CBCGPMSMLinksBarButton (LPCTSTR lpszLabel, UINT nID)
{
	m_strText = lpszLabel;
	m_nID     = nID;

	Initialize ();
}
//***************************************************************************************
CBCGPMSMLinksBarButton::~CBCGPMSMLinksBarButton ()
{

}
//***************************************************************************************
void CBCGPMSMLinksBarButton::Initialize ()
{
	m_bText = TRUE;
}

void CBCGPMSMLinksBarButton::OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages,
								BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight,
								BOOL bDrawBorder, BOOL /*bGrayDisabledButtons*/)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (this);

	m_bHorz = bHorz;

	//----------------------
	// Fill button interior:
	//----------------------
	BOOL bChecked = (m_nStyle & TBBS_CHECKED) != 0;

	if (bChecked)
	{
		m_nStyle &= ~TBBS_CHECKED;
	}

	FillInterior (pDC, rect, bHighlight);

	if (bChecked)
	{
		m_nStyle |= TBBS_CHECKED;
	}

	BOOL bHot = bHighlight;
	CSize sizeImage = (pImages == NULL) ? CSize (0, 0) : pImages->GetImageSize (TRUE);

	CRect rectInternal = rect;

	//--------------------
	// Draw button's text:
	//--------------------
	CBCGPVisualManager::BCGBUTTON_STATE state = CBCGPVisualManager::ButtonsIsRegular;

	CFont* pOldFont = NULL;

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

	if (m_nStyle & TBBS_CHECKED)
	{
		pOldFont = (CFont*)(pDC->SelectObject (&globalData.fontBold)); 
	}
	else
	{
		pOldFont = (CFont*)(pDC->SelectObject (&globalData.fontRegular)); 
	}

	COLORREF clrText = CBCGPVisualManager::GetInstance ()->GetToolbarButtonTextColor (
		this, state);

	pDC->SetTextColor (clrText);
	CString strText = m_strText;
	CRect rectText = rectInternal;
	UINT uiTextFormat = 0;

	uiTextFormat = DT_SINGLELINE;

	if (bHorz)
	{
		pDC->DrawText (strText, &rectText, uiTextFormat | DT_VCENTER | DT_CENTER | DT_END_ELLIPSIS);
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
			if ((m_nStyle & TBBS_PRESSED) || bHighlight)
			{
				CBCGPVisualManager::GetInstance ()->OnDrawButtonBorder (pDC,
					this, rect, CBCGPVisualManager::ButtonsIsPressed);
			}
		}
		else if (bHot && !(m_nStyle & TBBS_DISABLED) &&
			!(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
		{
			CBCGPVisualManager::GetInstance ()->OnDrawButtonBorder (pDC,
				this, rect, CBCGPVisualManager::ButtonsIsHighlighted);
		}
	}
}


SIZE CBCGPMSMLinksBarButton::OnCalculateSize (
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

			size.cx = max (size.cx, m_sizeText.cx);
			size.cy = m_sizeText.cy + 4 * nTextMargin;

			pDC->SelectObject (pOldFont);
		}
	}

	return size;
}
