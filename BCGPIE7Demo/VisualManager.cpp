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
// VisualManager.cpp: implementation of the CVisualManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "VisualManager.h"

#include "RebarDC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE (CVisualManager, CBCGPWinXPVisualManager)

CVisualManager::CVisualManager()
{
}

CVisualManager::~CVisualManager()
{

}

CSize CVisualManager::GetCaptionButtonExtraBorder () const
{
	CSize size (CBCGPWinXPVisualManager::GetCaptionButtonExtraBorder ());

	if (!IsWinXPThemeAvailible ())
	{
		size = CBCGPVisualManager::GetCaptionButtonExtraBorder ();
	}
	else if (m_hThemeWindow != NULL)
	{
		size.cx = 2;
		size.cy = 1;
	}

	return size;
}

void CVisualManager::OnDrawCaptionButton (CDC* pDC, CBCGPCaptionButton* pButton, 
								BOOL bActive, BOOL bHorz, BOOL bMaximized, BOOL bDisabled,
								int nImageID /*= -1*/)
{
	ASSERT_VALID (pDC);
	ASSERT (pButton != NULL);

	if (!IsWinXPThemeAvailible ())
	{
		CBCGPVisualManager::OnDrawCaptionButton (pDC, pButton, bActive, bHorz, 
								bMaximized, bDisabled, nImageID);
		return;
	}

	if (pButton->IsMiniFrameButton () ||
		(pButton->m_nHit != HTCLOSE_BCG &&
		 pButton->m_nHit != HTMAXBUTTON))
	{
		CBCGPWinXPVisualManager::OnDrawCaptionButton (pDC, pButton, bActive, bHorz, 
								bMaximized, bDisabled, nImageID);
		return;
	}

	BOOL bPushed = pButton->m_bPushed;
	BOOL bFocused = pButton->m_bFocused || pButton->m_bDroppedDown;

	CBCGPToolBarImages* pImages = NULL;
	int image = 0;

	if (pButton->m_nHit == HTCLOSE_BCG)
	{
		pImages = &m_BtnClose;
	}
	else
	{
		pImages = &m_BtnPin;
	}

	if (!bDisabled)
	{
		if (bPushed && bFocused)
		{
			image = 2;
		}
		else if (bFocused)
		{
			image = 1;
		}
	}	

	CRect rect = pButton->GetRect ();

	if (pImages != NULL)
	{
		pImages->DrawEx (pDC, rect, image, 
			CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);
	}
}

COLORREF CVisualManager::OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
			BOOL /*bActive*/, CRect rectCaption, CRect /*rectButtons*/)
{
	ASSERT_VALID (pBar);

	OnFillBarBackground (pDC, pBar, rectCaption, rectCaption);

	if (!IsWinXPThemeAvailible ())
	{
		CPen pen (PS_SOLID, 0, globalData.clrBtnHilite);
		CPen* pPen = (CPen*) pDC->SelectObject (&pen);

		pDC->MoveTo (rectCaption.left, rectCaption.top);
		pDC->LineTo (rectCaption.right, rectCaption.top);

		pDC->SelectObject (pPen);
	}

	return globalData.clrBarText;
}

void CVisualManager::OnUpdateSystemColors ()
{
	CBCGPWinXPVisualManager::OnUpdateSystemColors ();

	m_nMenuBorderSize = IsWinXPThemeAvailible () ? 1 : 2;
	m_bShadowHighlightedImage = FALSE;

	if (!m_BtnPin.IsValid ())
	{
		m_BtnPin.SetImageSize (CSize (17, 16));
		m_BtnPin.LoadStr (_T("IDB_BTN_PIN"));
	}

	if (!m_BtnClose.IsValid ())
	{
		m_BtnClose.SetImageSize (CSize (17, 16));
		m_BtnClose.LoadStr (_T("IDB_BTN_SM_CLOSE"));
	}

	if (!m_BtnAddressBar [0].IsValid ())
	{
		m_BtnAddressBar [0].SetImageSize (CSize (22, 22));
		m_BtnAddressBar [0].LoadStr (_T("IDB_BTN_ADDRESS_BAR"));
	}

	if (!m_BtnAddressBar [1].IsValid ())
	{
		m_BtnAddressBar [1].SetImageSize (CSize (26, 26));
		m_BtnAddressBar [1].LoadStr (_T("IDB_BTN_ADDRESS_BAR_120"));
	}

	if (!m_BtnMenuAddressBar [0].IsValid ())
	{
		m_BtnMenuAddressBar [0].SetImageSize (CSize (35, 22));
		m_BtnMenuAddressBar [0].LoadStr (_T("IDB_BTN_MENU_ADDRESS_BAR"));
	}

	if (!m_BtnMenuAddressBar [1].IsValid ())
	{
		m_BtnMenuAddressBar [1].SetImageSize (CSize (50, 26));
		m_BtnMenuAddressBar [1].LoadStr (_T("IDB_BTN_MENU_ADDRESS_BAR_120"));
	}

	CSize size (CRebarDC::GetInstance().GetSize ());
	if (size.cx != 0 && size.cy != 0)
	{
		CRebarDC::GetInstance().SetSize (size);
	}	
}

void CVisualManager::OnFillButtonInterior (CDC* pDC,
				CBCGPToolbarButton* pButton, CRect rect,
				CBCGPVisualManager::BCGBUTTON_STATE state)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	if (!IsAddressBarButton (pButton))
	{
		CBCGPWinXPVisualManager::OnFillButtonInterior (pDC, pButton, rect, state);
		return;
	}

	int image = 0;
	int nImageIndex = theApp.m_bLargeIcons ? 1 : 0;

	CBCGPToolbarMenuButton* pMenuButton = DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton, pButton);

	if (pMenuButton != NULL)
	{
		if (pMenuButton->IsDroppedDown ())
		{
			image = 2;
		}
		else if (pButton->m_nStyle && TBBS_PRESSED)
		{
			image = 3;
		}
		else if (state == ButtonsIsHighlighted)
		{
			image = 1;
		}

		m_BtnMenuAddressBar [nImageIndex].DrawEx (pDC, rect, image);
		return;
	}

	if (pButton->m_nStyle && TBBS_PRESSED)
	{
		image = 2;
	}
	else if (state == ButtonsIsHighlighted)
	{
		image = 1;
	}

	m_BtnAddressBar [nImageIndex].DrawEx (pDC, rect, image);
}

void CVisualManager::OnDrawButtonBorder (CDC* pDC,
		CBCGPToolbarButton* pButton, CRect rect, BCGBUTTON_STATE state)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	if (IsAddressBarButton (pButton))
	{
		return;
	}

	CBCGPWinXPVisualManager::OnDrawButtonBorder (pDC, pButton, rect, state);
}

void CVisualManager::OnDrawButtonSeparator (CDC* pDC,
		CBCGPToolbarButton* pButton, CRect rect, CBCGPVisualManager::BCGBUTTON_STATE state,
		BOOL bHorz)
{
	ASSERT_VALID (pButton);

	if (IsAddressBarButton (pButton))
	{
		return;
	}

	CBCGPWinXPVisualManager::OnDrawButtonSeparator (pDC, pButton, rect, state, bHorz);
}

void CVisualManager::OnDrawSeparator (CDC* pDC, CBCGPBaseControlBar* pBar, CRect rect, BOOL bIsHoriz)
{
	CBCGPToolBar* pToolBar = DYNAMIC_DOWNCAST(CBCGPToolBar, pBar);

	if (pToolBar != NULL && pToolBar->GetResourceID () == IDR_ADDRESS_BAR)
	{
		return;
	}

	CBCGPWinXPVisualManager::OnDrawSeparator (pDC, pBar, rect, bIsHoriz);
}

BOOL CVisualManager::IsAddressBarButton (CBCGPToolbarButton* pButton)
{
	ASSERT_VALID (pButton);

	CBCGPToolBar* pToolBar = DYNAMIC_DOWNCAST(CBCGPToolBar, pButton->GetParentWnd ());

	if (pToolBar == NULL)
	{
		return FALSE;
	}

	return pToolBar->GetResourceID () == IDR_ADDRESS_BAR;
}

