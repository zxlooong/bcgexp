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
// MyVisualManager.cpp: implementation of the CXPVisualManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyVisualManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXPVisualManager::CXPVisualManager()
{
	m_bMenuFlatLook = TRUE;
	m_bShadowHighlightedImage = TRUE;

	OnUpdateSystemColors ();
}
//****************************************************************************************
CXPVisualManager::~CXPVisualManager()
{
}
//****************************************************************************************
void CXPVisualManager::OnUpdateSystemColors ()
{
	m_brBarBkgnd.DeleteObject ();
	m_brMenuLight.DeleteObject ();
	m_brHighlight.DeleteObject ();

	CWindowDC dc (NULL);

	if (dc.GetDeviceCaps (BITSPIXEL) > 8)
	{
		COLORREF clrWindow = ::GetSysColor (COLOR_WINDOW);

		m_clrMenuLight = CBCGDrawManager::PixelAlpha (
			clrWindow, .976, .973, .969);
							
		COLORREF clrFace = ::GetSysColor (COLOR_3DFACE);
		m_clrBarBkgnd = CBCGDrawManager::PixelAlpha (RGB (
			(3 * GetRValue (clrFace) + GetRValue (clrWindow)) / 4,
			(3 * GetGValue (clrFace) + GetGValue (clrWindow)) / 4,
			(3 * GetBValue (clrFace) + GetBValue (clrWindow)) / 4),
			98);

		COLORREF clrHL = ::GetSysColor (COLOR_HIGHLIGHT);
		m_clrHighlight = CBCGDrawManager::PixelAlpha (RGB (
			(GetRValue (clrHL) + 2 * GetRValue (m_clrMenuLight)) / 3,
			(GetGValue (clrHL) + 2 * GetGValue (m_clrMenuLight)) / 3,
			(GetBValue (clrHL) + 2 * GetBValue (m_clrMenuLight)) / 3), 
			114);

		m_clrHighlightDn = CBCGDrawManager::PixelAlpha (
			m_clrHighlight, .87, .87, .87);

		m_clrHighlightChecked = CBCGDrawManager::PixelAlpha (
			m_clrHighlight, 1.02, 1.02, 1.02);
	}
	else
	{
		m_clrMenuLight = ::GetSysColor (COLOR_WINDOW);
		m_clrBarBkgnd = ::GetSysColor (COLOR_3DFACE);
		m_clrHighlight = ::GetSysColor (COLOR_HIGHLIGHT);
		m_clrHighlightDn = ::GetSysColor (COLOR_HIGHLIGHT);
		m_clrHighlightChecked = ::GetSysColor (COLOR_3DFACE);
	}

	m_brBarBkgnd.CreateSolidBrush (m_clrBarBkgnd);
	m_brMenuLight.CreateSolidBrush (m_clrMenuLight);
	m_brHighlight.CreateSolidBrush (m_clrHighlight);
	m_brHighlightDn.CreateSolidBrush (m_clrHighlightDn);
	m_brHighlightChecked.CreateSolidBrush (m_clrHighlightChecked);
}
//***************************************************************************************
void CXPVisualManager::OnDrawBarGripper (CDC* pDC, CRect rectGripper, BOOL bHorz,
									   CControlBar* pBar)
{
	if (m_brGripperHorz.GetSafeHandle () == NULL)
	{
		WORD horzHatchBits [8] = { 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00 };

		CBitmap bmpGripperHorz;
		bmpGripperHorz.CreateBitmap (8, 8, 1, 1, horzHatchBits);

		m_brGripperHorz.CreatePatternBrush (&bmpGripperHorz);

		WORD vertHatchBits[8] = { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };

		CBitmap bmpGripperVert;
		bmpGripperVert.CreateBitmap (8, 8, 1, 1, vertHatchBits);

		m_brGripperVert.CreatePatternBrush (&bmpGripperVert);
	}

	BOOL bSideBar = pBar->IsKindOf (RUNTIME_CLASS (CBCGSizingControlBar));
	BOOL bMenuBar = pBar->IsKindOf (RUNTIME_CLASS (CBCGMenuBar));

	CRect rectFill = rectGripper;

	if (!bSideBar)
	{
		if (bHorz)
		{
			rectFill.DeflateRect (rectFill.Width () / 2 + 2, 6);
		}
		else
		{
			rectFill.DeflateRect (6, rectFill.Height () / 2 + 2);
		}
	}
	else
	{
		if (bHorz)
		{
			rectFill.DeflateRect (4, 0);
		}
		else
		{
			rectFill.DeflateRect (0, 4);
		}

		bHorz = !bHorz;
	}

	COLORREF clrTextOld = pDC->SetTextColor (::GetSysColor (COLOR_3DSHADOW));
	COLORREF clrBkOld = pDC->SetBkColor (bSideBar || bMenuBar ? 
		::GetSysColor (COLOR_3DFACE) : m_clrBarBkgnd);

	pDC->FillRect (rectFill, bHorz ? &m_brGripperHorz : &m_brGripperVert);

	if (bSideBar)
	{
		//------------------
		// Draw bar caption:
		//------------------
		int nOldBkMode = pDC->SetBkMode (OPAQUE);
		pDC->SetTextColor (::GetSysColor (COLOR_BTNTEXT));

		const CFont& font = CBCGMenuBar::GetMenuFont (bHorz);

		CFont* pOldFont = pDC->SelectObject ((CFont*) &font);

		CString strCaption;
		pBar->GetWindowText (strCaption);
		strCaption = _T(" ") + strCaption + _T(" ");

		CRect rectText = rectGripper;
		UINT uiTextFormat = 0;

		TEXTMETRIC tm;
		pDC->GetTextMetrics (&tm);

		CPoint ptTextOffset (0, 0);
		if (bHorz)
		{
			ptTextOffset.y = (rectGripper.Height () - tm.tmHeight - 1) / 2;
		}
		else
		{
			ptTextOffset.x = (rectGripper.Width () - tm.tmHeight + 1) / 2;
		}

		if (bHorz)
		{
			rectText.top += ptTextOffset.y;
			pDC->DrawText (strCaption, &rectText, uiTextFormat);
		}
		else
		{
			rectText.left = rectText.right - ptTextOffset.x;
			rectText.top = rectGripper.top + ptTextOffset.y;
			rectText.bottom = rectGripper.top + 3 * ptTextOffset.y;

			uiTextFormat |= DT_NOCLIP;

			pDC->DrawText (strCaption, &rectText, uiTextFormat);
		}

		pDC->SelectObject(pOldFont);
		pDC->SetBkMode(nOldBkMode);
	}

	pDC->SetTextColor (clrTextOld);
	pDC->SetBkColor (clrBkOld);
}
//****************************************************************************************
void CXPVisualManager::OnDrawMenuBorder (CDC* pDC, CBCGPopupMenu* pMenu, CRect rect)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pMenu);

	COLORREF clrDark = ::GetSysColor (COLOR_3DDKSHADOW);
	pDC->Draw3dRect (rect, clrDark, clrDark);
	rect.DeflateRect (1, 1);
	pDC->Draw3dRect (rect, m_clrMenuLight, m_clrMenuLight);

	CRect rectLeft (1, 1, 2, rect.bottom - 1);
	pDC->FillRect (rectLeft, &m_brBarBkgnd);

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
				pDC->FillRect (rectConnect, &m_brBarBkgnd);
			}
		}
	}
}
//****************************************************************************************
void CXPVisualManager::OnDrawBarBorder (CDC* /*pDC*/, CControlBar* /*pBar*/, CRect& /*rect*/)
{
	// Don't draw borders
}
//****************************************************************************************
void CXPVisualManager::OnFillBarBackground (CDC* pDC, CControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL bNCArea)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pBar);

	if (rectClip.IsRectEmpty ())
	{
		rectClip = rectClient;
	}

	CRuntimeClass* pBarClass = pBar->GetRuntimeClass ();

	if (pBarClass == NULL || pBarClass->IsDerivedFrom (RUNTIME_CLASS (CBCGMenuBar)))
	{
		CBCGVisualManager::OnFillBarBackground (pDC, pBar, rectClient, rectClip);
		return;
	}

	if (pBarClass->IsDerivedFrom (RUNTIME_CLASS (CBCGPopupMenuBar)))
	{
		pDC->FillRect (rectClip, &m_brMenuLight);

		if (!pBarClass->IsDerivedFrom(RUNTIME_CLASS(CBCGColorBar)))
		{
			CRect rectImages = rectClient;
			rectImages.right = rectImages.left + CBCGToolBar::GetMenuImageSize ().cx + 2 * IMAGE_MARGIN + 2;

			pDC->FillRect (rectImages, &m_brBarBkgnd);
		}

		return;
	}

	if (pBarClass->IsDerivedFrom (RUNTIME_CLASS (CBCGToolBar)))
	{
		pDC->FillRect (rectClip, &m_brBarBkgnd);
		return;
	}

	CBCGVisualManager::OnFillBarBackground (pDC, pBar, rectClient, rectClip);
}
//**************************************************************************************
void CXPVisualManager::OnDrawSeparator (CDC* pDC, CControlBar* pBar,
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

	pDC->Draw3dRect (rectSeparator, ::GetSysColor (COLOR_3DSHADOW),
									::GetSysColor (COLOR_3DSHADOW));
}
//**************************************************************************************
void CXPVisualManager::OnDrawButtonBorder (CDC* pDC,
		CBCGToolbarButton* pButton, CRect rect, BCGBUTTON_STATE state)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	CBCGToolbarMenuButton* pMenuButton = 
		DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);
	BOOL bIsMenuButton = pMenuButton != NULL;

	BOOL bIsPopupMenu = bIsMenuButton &&
		pMenuButton->GetParentWnd ()->IsKindOf (RUNTIME_CLASS (CBCGPopupMenuBar));

	COLORREF clrDark = ::GetSysColor (COLOR_3DDKSHADOW);
	COLORREF clrShadow = ::GetSysColor (COLOR_3DSHADOW);

	if (!bIsPopupMenu || state != ButtonsIsHighlighted)
	{
		rect.right--;
		rect.bottom--;
	}

	if (bIsMenuButton && !bIsPopupMenu && state == ButtonsIsPressed)
	{
		CBCGToolBar* pParentBar = DYNAMIC_DOWNCAST (CBCGToolBar, pMenuButton->GetParentWnd ());
		BOOL bIsVertical =	pParentBar != NULL &&
							(pParentBar->m_dwStyle & CBRS_ORIENT_HORZ) == 0;

		if (bIsVertical)
		{
			rect.right += 4;
		}
		else
		{
			rect.bottom += 4;
		}
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

		// By Sven Ritter:
		if (!bIsPopupMenu && bIsMenuButton)
		{
			pDC->Draw3dRect (rect, clrDark, clrDark);
		}
		else
		{
			pDC->Draw3dRect (rect, clrShadow, clrShadow);
		}
	}
}
//*****************************************************************************************
void CXPVisualManager::OnFillButtonInterior (CDC* pDC,
	CBCGToolbarButton* pButton, CRect rect, CBCGVisualManager::BCGBUTTON_STATE state)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	BOOL bIsMenuButton = pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarMenuButton));
	BOOL bIsPopupMenu = bIsMenuButton &&
		((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()->IsKindOf (
		RUNTIME_CLASS (CBCGPopupMenuBar));

	if (!bIsPopupMenu || state != ButtonsIsHighlighted)
	{
		rect.right --;
		rect.bottom --;
	}

	CBrush* pBrush = ((pButton->m_nStyle & TBBS_PRESSED) && !bIsPopupMenu) ? 
		&m_brHighlightDn : &m_brHighlight;

	if (bIsMenuButton && !bIsPopupMenu && state == ButtonsIsPressed)
	{
		rect.bottom += 4;
	}

	if (pButton->m_nStyle & TBBS_CHECKED)
	{
		pBrush = (state == ButtonsIsHighlighted) ? 
				&m_brHighlightDn : &m_brHighlightChecked;
	}

	switch (state)
	{
	case ButtonsIsPressed:
		if (bIsPopupMenu)
		{
			break;
		}

	case ButtonsIsHighlighted:
		rect.DeflateRect (1, 1);
		pDC->FillRect (rect, pBrush);
	}
}
//************************************************************************************
void CXPVisualManager::OnHighlightMenuItem (CDC* pDC, CBCGToolbarMenuButton* pButton,
											CRect rect, COLORREF& clrText)
{
	ASSERT_VALID (pDC);

	pDC->FillRect (rect, &m_brHighlight);

	COLORREF clrDark = ::GetSysColor (COLOR_3DSHADOW);
	pDC->Draw3dRect (rect, clrDark, clrDark);

	BOOL bIsMenuButton = pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarMenuButton));
	BOOL bIsPopupMenu = bIsMenuButton &&
		((CBCGToolbarMenuButton*) pButton)->GetParentWnd ()->IsKindOf (
			RUNTIME_CLASS (CBCGPopupMenuBar));

	if (bIsPopupMenu && rect.left > 1 &&
		!(pButton->m_nStyle & TBBS_CHECKED))
	{
		CRect rectConnect = rect;

		rectConnect.right = rect.left + 1;
		rectConnect.left = CBCGToolBar::GetMenuImageSize ().cx + 2 * IMAGE_MARGIN - 1;

		pDC->Draw3dRect (rectConnect, clrDark, clrDark);
		rectConnect.DeflateRect (0, 1);
		pDC->FillRect (rectConnect, &m_brHighlight);
	}

	// Now, we should define a menu text color...
	if (GetRValue (m_clrHighlight) > 128 &&
		GetGValue (m_clrHighlight) > 128 &&
		GetBValue (m_clrHighlight) > 128)
	{
		clrText = RGB (0, 0, 0);
	}
	else
	{
		clrText = RGB (255, 255, 255);
	}
}
//***********************************************************************************
void CXPVisualManager::OnDrawTab (CDC* pDC, CRect rectTab,
						int iTab, BOOL bIsActive, const CBCGTabWnd* pTabWnd)
{
	// By David Wulff, Battleaxe Software Limited

	#define TEXT_MARGIN				4
	#define IMAGE_MARGIN			4

	ASSERT_VALID (pTabWnd);
	ASSERT_VALID (pDC);

	if (pTabWnd->IsFlatTab ())
	{
		CBCGVisualManager::OnDrawTab (pDC, rectTab, iTab, bIsActive, pTabWnd);
		return;
	}

	CPen penLight (PS_SOLID, 1, ::GetSysColor (COLOR_3DHILIGHT));
	CPen penDkGray (PS_SOLID, 1, ::GetSysColor (COLOR_3DDKSHADOW));

	CPen* pOldPen = pDC->SelectObject (&penLight);
	ASSERT(pOldPen != NULL);
	
	if (iTab != pTabWnd->GetActiveTab () - 1)
	{
		pDC->MoveTo (rectTab.right, rectTab.top + 3);
		pDC->LineTo (rectTab.right, rectTab.bottom - 3);
	}

	if (bIsActive)
	{
		if (pTabWnd->GetLocation () == CBCGTabWnd::LOCATION_BOTTOM)
		{
			CRect rectFace = rectTab;
			rectFace.top -= pTabWnd->IsFlatFrame () ? 1 : 2;
			rectFace.bottom -= 2;
			
			::FillRect (pDC->GetSafeHdc (), rectFace, ::GetSysColorBrush (COLOR_BTNFACE));
			
			pDC->SelectObject (&penDkGray);
			
			pDC->MoveTo(rectTab.left, rectFace.top);
			pDC->LineTo(rectTab.left, rectTab.bottom - 3);
			pDC->LineTo(rectTab.left + 2, rectTab.bottom - 1);
			pDC->LineTo(rectTab.right - 2, rectTab.bottom - 1);
			pDC->LineTo(rectTab.right, rectTab.bottom - 3);
			pDC->LineTo(rectTab.right, rectFace.top);
		}
		else
		{
			CRect rectFace = rectTab;
			rectFace.bottom += 1;
			rectFace.left += 1;
			
			::FillRect (pDC->GetSafeHdc (), rectFace, ::GetSysColorBrush (COLOR_BTNFACE));
			
			pDC->SelectObject (&penLight);
			
			pDC->MoveTo(rectTab.left, rectTab.bottom);
			pDC->LineTo(rectTab.left, rectTab.top + 1);
			pDC->LineTo(rectTab.left + 2, rectTab.top - 1);
			
			pDC->SelectObject (&penDkGray);
			
			pDC->LineTo(rectTab.right - 2, rectTab.top - 1);
			pDC->LineTo(rectTab.right, rectTab.top + 1);
			pDC->LineTo(rectTab.right, rectTab.bottom);
			
			pDC->SelectObject (&penLight);
			pDC->MoveTo(rectTab.left + 1, rectTab.top);
			pDC->LineTo(rectTab.right - 2, rectTab.top);
		}
	}

	CSize sizeImage = pTabWnd->GetImageSize ();
	UINT uiIcon = pTabWnd->GetTabIcon (iTab);
	if (uiIcon == (UINT)-1)
	{
		sizeImage.cx = 0;
	}

	if (sizeImage.cx + IMAGE_MARGIN <= rectTab.Width ())
	{
		const CImageList* pImageList = pTabWnd->GetImageList ();
		if (pImageList != NULL && uiIcon != (UINT)-1)
		{
			//----------------------
			// Draw the tab's image:
			//----------------------
			CRect rectImage = rectTab;

			if (bIsActive && pTabWnd->GetLocation () == CBCGTabWnd::LOCATION_BOTTOM)
				rectImage.top += ((rectTab.Height () - sizeImage.cy) / 2) - 1;
			else
				rectImage.top += (rectTab.Height () - sizeImage.cy) / 2;
			
			rectImage.bottom = rectImage.top + sizeImage.cy;

			rectImage.left += IMAGE_MARGIN;
			rectImage.right = rectImage.left + sizeImage.cx;

			ASSERT_VALID (pImageList);
			((CImageList*) pImageList)->Draw (pDC, uiIcon, rectImage.TopLeft (), ILD_TRANSPARENT);
		}

		//------------------------------
		// Finally, draw the tab's text:
		//------------------------------
		CRect rcText = rectTab;
		rcText.left += sizeImage.cx + 2 * TEXT_MARGIN;
		rcText.bottom -= (bIsActive) ? 2 : 0;
		
		if (bIsActive)
		{
			pDC->SetTextColor (::GetSysColor (COLOR_BTNTEXT));
		}
		else
		{
			pDC->SetTextColor (::GetSysColor (COLOR_3DHILIGHT));
		}

		CString strText;
		pTabWnd->GetTabLabel (iTab, strText);

		pDC->DrawText (strText, rcText, 
					DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);
	}

	pDC->SelectObject (pOldPen);
}
//***********************************************************************************
void CXPVisualManager::OnEraseTabsArea (CDC* pDC, CRect rect, 
										 const CBCGTabWnd* pTabWnd)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pTabWnd);

	if (pTabWnd->IsFlatTab ())
	{
		CBCGVisualManager::OnEraseTabsArea (pDC, rect, pTabWnd);
		return;
	}

	::FillRect (pDC->GetSafeHdc (), rect, ::GetSysColorBrush (COLOR_3DSHADOW));
	
	if (pTabWnd->GetLocation () == CBCGTabWnd::LOCATION_BOTTOM)
	{
		CPen penLight (PS_SOLID, 1, ::GetSysColor (COLOR_3DHILIGHT));
		CPen* pOldPen = pDC->SelectObject (&penLight);

		pDC->MoveTo (rect.left, rect.bottom - 1);
		pDC->LineTo (rect.right, rect.bottom - 1);

		pDC->SelectObject (pOldPen);
	}
}
//**************************************************************************************
void CXPVisualManager::OnDrawCaptionButton (CDC* pDC, CBCGSCBButton* pButton, 
											BOOL bHorz, BOOL bMaximized, BOOL bDisabled)
{
	ASSERT_VALID (pDC);
	ASSERT (pButton != NULL);

	if (!bDisabled || pButton->m_nHit == HTCLOSE_BCG)
	{
		if ((pButton->m_bFocused || pButton->m_bPushed))
		{
			pDC->FillRect (pButton->GetRect (), &m_brHighlight);
		}
	}

	CBCGVisualManager::OnDrawCaptionButton (pDC, pButton, bHorz, bMaximized, bDisabled);
}
