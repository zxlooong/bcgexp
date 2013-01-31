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
// BCGPVisualManagerOffice10.cpp: implementation of the CBCGPVisualManagerOffice10 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGBarRes.h"
#include "BCGLocalRes.h"

#include "BCGPVisualManagerOffice10.h"

#include "BCGDrawManager.h"
#include "BCGPopupMenu.h"
#include "BCGToolbar.h"
#include "BCGToolbarMenuButton.h"
#include "BCGSizingControlBar.h"

#include "ColorPopup.h"
#include "BCGColorBar.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifndef COLOR_GRADIENTACTIVECAPTION
#define COLOR_GRADIENTACTIVECAPTION     27
#define COLOR_GRADIENTINACTIVECAPTION   28
#define SPI_GETGRADIENTCAPTIONS         0x1008
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGPVisualManagerOffice10::CBCGPVisualManagerOffice10()
{
	CWindowDC dc (NULL);

	if (dc.GetDeviceCaps (BITSPIXEL) > 8)
	{
		COLORREF clrWindow = ::GetSysColor (COLOR_WINDOW);

		m_clrLight = CBCGDrawManager::PixelAlpha (
			clrWindow, .976, .973, .969);
							
		COLORREF clrFace = ::GetSysColor (COLOR_3DFACE);
		m_clrPlum = CBCGDrawManager::PixelAlpha (RGB (
			(3 * GetRValue (clrFace) + GetRValue (clrWindow)) / 4,
			(3 * GetGValue (clrFace) + GetGValue (clrWindow)) / 4,
			(3 * GetBValue (clrFace) + GetBValue (clrWindow)) / 4),
			98);

		COLORREF clrHL = ::GetSysColor (COLOR_HIGHLIGHT);
		m_clrSteel = CBCGDrawManager::PixelAlpha (RGB (
			(GetRValue (clrHL) + 2 * GetRValue (m_clrLight)) / 3,
			(GetGValue (clrHL) + 2 * GetGValue (m_clrLight)) / 3,
			(GetBValue (clrHL) + 2 * GetBValue (m_clrLight)) / 3), 
			112);
	}
	else
	{
		m_clrLight = ::GetSysColor (COLOR_WINDOW);
		m_clrPlum = ::GetSysColor (COLOR_3DFACE);
		m_clrSteel = ::GetSysColor (COLOR_WINDOW);
	}

	m_brPlum.CreateSolidBrush (m_clrPlum);
	m_brLight.CreateSolidBrush (m_clrLight);
	m_brSteel.CreateSolidBrush (m_clrSteel);
}
//****************************************************************************************
CBCGPVisualManagerOffice10::~CBCGPVisualManagerOffice10()
{
}
//****************************************************************************************
void CBCGPVisualManagerOffice10::OnDrawBarGripper (CDC* pDC, CRect rectGripper, BOOL bHorz,
									   CControlBar* pBar)
{
	if (m_brGripperHorz.GetSafeHandle () == NULL)
	{
		CBCGLocalResource localRes;

		CBitmap bmpGripperHorz;
		bmpGripperHorz.LoadBitmap (IDB_BCGBARRES_VM_GRIPPER_HORZ);

		m_brGripperHorz.CreatePatternBrush (&bmpGripperHorz);

		CBitmap bmpGripperVert;
		bmpGripperVert.LoadBitmap (IDB_BCGBARRES_VM_GRIPPER_VERT);

		m_brGripperVert.CreatePatternBrush (&bmpGripperVert);
	}

	BOOL bSideBar = pBar->IsKindOf (RUNTIME_CLASS (CBCGSizingControlBar));

	if (!bSideBar)
	{
		if (bHorz)
		{
			rectGripper.DeflateRect (rectGripper.Width () / 2 + 2, 6);
		}
		else
		{
			rectGripper.DeflateRect (6, rectGripper.Height () / 2 + 2);
		}
	}
	else
	{
		rectGripper.DeflateRect (2, 2);
	}

	COLORREF clrTextOld = pDC->SetTextColor (globalData.clrBtnShadow);
	COLORREF clrBkOld = pDC->SetBkColor (bSideBar ? RGB (0, 204, 204) : m_clrPlum);

	if (bSideBar)
	{
		COLORREF clrCptnRight = globalData.clrBtnFace;
		COLORREF clrCptn = GetSysColor(COLOR_INACTIVECAPTION);

		BOOL bSysGradient = FALSE;
		::SystemParametersInfo (SPI_GETGRADIENTCAPTIONS, 0, &bSysGradient, 0);

		if (bSysGradient)
		{
			// get second gradient color (the right end)
			clrCptnRight = GetSysColor(COLOR_GRADIENTINACTIVECAPTION);
		}

		CBCGDrawManager dm (*pDC);
		dm.FillGradient (rectGripper, clrCptn, clrCptnRight, bHorz);

		CRect rectText = rectGripper;

		COLORREF clrTextOld = pDC->SetTextColor (::GetSysColor (COLOR_INACTIVECAPTIONTEXT));
		CFont* pOldFont = (CFont*) pDC->SelectStockObject (DEFAULT_GUI_FONT);
		pDC->SetBkMode (TRANSPARENT);

		// Draw caption:
		CString strCaption;
		pBar->GetWindowText (strCaption);

		rectText.DeflateRect (5, 0);
		pDC->DrawText (strCaption, rectText, DT_VCENTER | DT_SINGLELINE);

		pDC->SetTextColor (clrTextOld);
		pDC->SelectObject (pOldFont);
	}
	else
	{
		pDC->FillRect (rectGripper, bHorz ? &m_brGripperHorz : &m_brGripperVert);
	}

	pDC->SetTextColor (clrTextOld);
	pDC->SetBkColor (clrBkOld);
}
//****************************************************************************************
void CBCGPVisualManagerOffice10::OnDrawMenuBorder (CDC* pDC, CBCGPopupMenu* pMenu, CRect rect)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pMenu);

// *************************************
	if (pMenu->IsKindOf(RUNTIME_CLASS(CColorPopup)))
	{
		CBCGVisualManager::OnDrawMenuBorder(pDC, pMenu, rect);
		return;
	}
// *************************************

	pDC->Draw3dRect (rect, globalData.clrBtnDkShadow, globalData.clrBtnDkShadow);
	rect.DeflateRect (1, 1);
	pDC->Draw3dRect (rect, m_clrLight, m_clrLight);

	CRect rectLeft (1, 1, 2, rect.bottom - 1);
	pDC->FillRect (rectLeft, &m_brPlum);

	CBCGToolbarMenuButton* pParentMenuBtn = pMenu->GetParentButton ();
	if (pParentMenuBtn != NULL && pMenu->GetParentPopupMenu () == NULL)
	{
		CWnd* pBar = pParentMenuBtn->GetParentWnd ();
		if (pBar != NULL)
		{
			CRect rectBar;
			pBar->GetClientRect (rectBar);
			pBar->ClientToScreen (rectBar);

			CRect rectMenu;
			pMenu->GetWindowRect (rectMenu);

			if (rectMenu.top >= rectBar.top + pParentMenuBtn->Rect ().bottom - 2)
			{
				CRect rectConnect (1, 0, pParentMenuBtn->Rect ().Width () - 1, 1);
				pDC->FillRect (rectConnect, &m_brPlum);
			}
		}
	}
}
//****************************************************************************************
void CBCGPVisualManagerOffice10::OnDrawBarBorder (CDC* /*pDC*/, CControlBar* /*pBar*/, CRect& /*rect*/)
{
	// Don't draw borders
}
//****************************************************************************************
void CBCGPVisualManagerOffice10::OnFillBarBackground (CDC* pDC, CControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL /*bNCArea*/)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pBar);

	if (rectClip.IsRectEmpty ())
	{
		rectClip = rectClient;
	}

	CRuntimeClass* pBarClass = pBar->GetRuntimeClass ();

	if (pBarClass == NULL || pBarClass->IsDerivedFrom (RUNTIME_CLASS (CBCGMenuBar)) || 
// *************************************
		pBarClass->IsDerivedFrom(RUNTIME_CLASS(CBCGColorBar)))
// *************************************
	{
		CBCGVisualManager::OnFillBarBackground (pDC, pBar, rectClient, rectClip);
		return;
	}

	if (pBarClass->IsDerivedFrom (RUNTIME_CLASS (CBCGPopupMenuBar)))
	{
		pDC->FillRect (rectClip, &m_brLight);

		CRect rectImages = rectClient;
		rectImages.right = rectImages.left + CBCGToolBar::GetMenuImageSize ().cx + 2 * IMAGE_MARGIN + 2;

		pDC->FillRect (rectImages, &m_brPlum);
		return;
	}

	if (pBarClass->IsDerivedFrom (RUNTIME_CLASS (CBCGToolBar)))
	{
		pDC->FillRect (rectClip, &m_brPlum);
		return;
	}

	CBCGVisualManager::OnFillBarBackground (pDC, pBar, rectClient, rectClip);
}
//**************************************************************************************
void CBCGPVisualManagerOffice10::OnDrawSeparator (CDC* pDC, CControlBar* pBar,
										 CRect rect, BOOL bHorz)
{
	CRect rectSeparator = rect;

	if (bHorz)
	{
		rectSeparator.left += rectSeparator.Width () / 2 - 1;
		rectSeparator.right = rectSeparator.left + 1;
	}
	else
	{
		rectSeparator.top += rectSeparator.Height () / 2 - 1;
		rectSeparator.bottom = rectSeparator.top + 1;

		if (pBar->IsKindOf (RUNTIME_CLASS (CBCGPopupMenuBar)))
		{
			rectSeparator.left = CBCGToolBar::GetMenuImageSize ().cx + 2 * (IMAGE_MARGIN + 2);
		}
	}

	pDC->Draw3dRect (rectSeparator, globalData.clrBtnShadow, globalData.clrBtnShadow);
}
//**************************************************************************************
void CBCGPVisualManagerOffice10::OnDrawButtonBorder (CDC* pDC,
		CBCGToolbarButton* pButton, CRect rect, BCGBUTTON_STATE state)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

// *************************************
	if (pButton->IsKindOf(RUNTIME_CLASS(CColorButton)))
	{
		CBCGVisualManager::OnDrawButtonBorder(pDC, pButton, rect, state);
		return;
	}
// *************************************

	BOOL bIsMenuButton = pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarMenuButton));
/*	BOOL bIsPopupMenu = bIsMenuButton &&
		((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()->IsKindOf (
			RUNTIME_CLASS (CBCGPopupMenuBar));*/
	BOOL bIsPopupMenu = bIsMenuButton && (NULL != ((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()) &&
		((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()->IsKindOf (
		RUNTIME_CLASS (CBCGPopupMenuBar));

	if (!bIsPopupMenu || state != ButtonsIsHighlighted)
	{
		rect.right--;
		rect.bottom--;
	}

	if (bIsMenuButton && !bIsPopupMenu && state == ButtonsIsPressed)
	{
		rect.bottom += 4;
	}

	switch (state)
	{
	case ButtonsIsPressed:
	case ButtonsIsHighlighted:
		if (!bIsPopupMenu &&
			(state != ButtonsIsPressed || bIsMenuButton))
		{
			CBCGDrawManager dm (*pDC);
			rect.bottom ++;

			dm.DrawShadow (rect, 1);
			rect.bottom --;
		}

		if (bIsPopupMenu && (pButton->m_nStyle & TBBS_CHECKED))
		{
			rect.bottom ++;
		}

// *************************************
		if (!bIsPopupMenu && bIsMenuButton)
			pDC->Draw3dRect (rect, globalData.clrBtnDkShadow, globalData.clrBtnDkShadow);

		else
			pDC->Draw3dRect (rect, globalData.clrBtnShadow, globalData.clrBtnShadow);
// *************************************
	}
}
//*****************************************************************************************
void CBCGPVisualManagerOffice10::OnFillButtonInterior (CDC* pDC,
	CBCGToolbarButton* pButton, CRect rect, CBCGVisualManager::BCGBUTTON_STATE state)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

// *************************************
	if (pButton->IsKindOf(RUNTIME_CLASS(CColorButton)))
	{
		CBCGVisualManager::OnFillButtonInterior(pDC, pButton, rect, state);
		return;
	}
// *************************************

	BOOL bIsMenuButton = pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarMenuButton));
/*	BOOL bIsPopupMenu = bIsMenuButton &&
		((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()->IsKindOf (
		RUNTIME_CLASS (CBCGPopupMenuBar));*/
	BOOL bIsPopupMenu = bIsMenuButton && (NULL != ((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()) &&
		((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()->IsKindOf (
		RUNTIME_CLASS (CBCGPopupMenuBar));

	if (!bIsPopupMenu || state != ButtonsIsHighlighted)
	{
		rect.right --;
		rect.bottom --;
	}

	CBrush* pBrush = &m_brSteel;

	if (bIsMenuButton && !bIsPopupMenu && state == ButtonsIsPressed)
	{
		rect.bottom += 4;
	}

	if (bIsMenuButton && !bIsPopupMenu && 
		((CBCGToolbarMenuButton*) pButton)->IsDroppedDown ())
	{
		pBrush = &m_brPlum;
	}

	if (pButton->m_nStyle & TBBS_CHECKED)
	{
		pBrush = (state == ButtonsIsHighlighted) ? &m_brLight : &m_brSteel;
	}

	switch (state)
	{
	case ButtonsIsPressed:
	case ButtonsIsHighlighted:
		rect.DeflateRect (1, 1);
		pDC->FillRect (rect, pBrush);
	}
}
//************************************************************************************
void CBCGPVisualManagerOffice10::OnHighlightMenuItem (CDC* pDC, CBCGToolbarMenuButton* pButton,
											CRect rect, COLORREF& clrText)
{
	ASSERT_VALID (pDC);

// *************************************
	if (pButton->IsKindOf(RUNTIME_CLASS(CColorButton)))
	{
		CBCGVisualManager::OnHighlightMenuItem(pDC, pButton, rect, clrText);
		return;
	}
// *************************************

	pDC->FillRect (rect, &m_brSteel);
	pDC->Draw3dRect (rect, globalData.clrBtnShadow, globalData.clrBtnShadow);

	BOOL bIsMenuButton = pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarMenuButton));
/*	BOOL bIsPopupMenu = bIsMenuButton &&
		((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()->IsKindOf (
			RUNTIME_CLASS (CBCGPopupMenuBar));*/
	BOOL bIsPopupMenu = bIsMenuButton && (NULL != ((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()) &&
		((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()->IsKindOf (
		RUNTIME_CLASS (CBCGPopupMenuBar));

	if (bIsPopupMenu && rect.left > 1 &&
		!(pButton->m_nStyle & TBBS_CHECKED))
	{
		CRect rectConnect = rect;

		rectConnect.right = rect.left + 1;
		rectConnect.left = CBCGToolBar::GetMenuImageSize ().cx + 2 * IMAGE_MARGIN - 1;

		pDC->Draw3dRect (rectConnect, globalData.clrBtnShadow, globalData.clrBtnShadow);
		rectConnect.DeflateRect (0, 1);
		pDC->FillRect (rectConnect, &m_brSteel);
	}

	// Now, we should define a menu text color...
	if (GetRValue (m_clrSteel) > 128 &&
		GetGValue (m_clrSteel) > 128 &&
		GetBValue (m_clrSteel) > 128)
	{
		clrText = RGB (0, 0, 0);
	}
	else
	{
		clrText = RGB (255, 255, 255);
	}
}
