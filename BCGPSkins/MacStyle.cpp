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
// MacStyle.cpp: implementation of the CMacStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPSkins.h"
#include "MacStyle.h"

#include "BCGPGlobalUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMacStyle, CBCGPVisualManagerXP)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMacStyle::CMacStyle()
{
	m_nMenuShadowDepth = 3;

	m_crHilight = ::GetSysColor(COLOR_3DHILIGHT);
	m_crFace    = RGB (231, 231, 231);
	m_crShadow  = ::GetSysColor(COLOR_3DSHADOW);

	m_brOutlook.CreateSolidBrush (RGB(231, 237, 246));
	m_brFace.CreateSolidBrush (m_crFace);
	m_brHighlight.CreateSolidBrush (RGB (133, 133, 133));

	m_penGripper1.CreatePen (PS_SOLID, 1, RGB(117, 117, 117));
	m_penGripper2.CreatePen (PS_SOLID, 1, RGB(214, 214, 214));

	m_ctrlMainBorder.Create (
		CBCGPControlRendererParams (IDB_MAC_MAINBORDER, RGB (255, 0, 255), 
			CRect (0, 0, 35, 23), CRect (17, 0, 17, 17), CRect (17, 0, 17, 17)));
	m_ctrlMainBorderCaption.Create (
		CBCGPControlRendererParams (IDB_MAC_MAINBORDERCAPTION, RGB (255, 0, 255), 
			CRect (0, 0, 35, 26), CRect (17, 8, 17, 3)));

	m_ctrlBtn.Create (
		CBCGPControlRendererParams (IDB_MAC_BTN, CRect (0, 0, 22, 22), CRect (3, 4, 3, 5)));

	m_ctrlStatusBarBack.Create (
		CBCGPControlRendererParams (IDB_MAC_SB_BACK, RGB (255, 0, 255), 
			CRect (0, 0, 35, 23), CRect (5, 2, 5, 4), CRect (2, 2, 2, 1)));

	m_ctrlStatusBarPaneBorder.Create (
		CBCGPControlRendererParams (IDB_MAC_SB_PANE, CRect (0, 0, 30, 20), CRect (6, 6, 6, 6)));

	m_StatusBarSizeBox.SetTransparentColor ((COLORREF)(-1));
    m_StatusBarSizeBox.SetImageSize (CSize (12, 12));
    m_StatusBarSizeBox.Load (IDB_MAC_SB_SIZEGRIP);

	m_ctrlSysBtnBack.Create (
		CBCGPControlRendererParams (IDB_MAC_BTN_SYS_BACK, CRect (0, 0, 14, 15), CRect (2, 2, 2, 2)));

	m_SysBtnMinimize.SetTransparentColor ((COLORREF)(-1));
    m_SysBtnMinimize.SetImageSize (CSize (8, 8));
    m_SysBtnMinimize.Load (IDB_MAC_BTN_SYS_MIN);
	m_SysBtnMaximize.SetTransparentColor ((COLORREF)(-1));
    m_SysBtnMaximize.SetImageSize (CSize (8, 8));
    m_SysBtnMaximize.Load (IDB_MAC_BTN_SYS_MAX);
	m_SysBtnRestore.SetTransparentColor ((COLORREF)(-1));
    m_SysBtnRestore.SetImageSize (CSize (8, 8));
    m_SysBtnRestore.Load (IDB_MAC_BTN_SYS_RESTORE);
	m_SysBtnClose.SetTransparentColor ((COLORREF)(-1));
    m_SysBtnClose.SetImageSize (CSize (8, 8));
    m_SysBtnClose.Load (IDB_MAC_BTN_SYS_CLOSE);

	SetLook2000 (FALSE);
	SetMenuFlatLook (TRUE);
	SetEmbossDisabledImage (FALSE);
	SetShadowHighlightedImage (FALSE);

	m_bActive = TRUE;

	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS);

	if (globalData.GetNonClientMetrics (ncm))
	{
		m_AppCaptionFont.DeleteObject ();
		m_AppCaptionFont.CreateFontIndirect (&ncm.lfCaptionFont);
	}
}

CMacStyle::~CMacStyle()
{
}

void CMacStyle::OnDrawBarGripper (CDC* pDC, CRect rectGripper, BOOL bHorz,
									   CBCGPBaseControlBar* /*pBar*/)
{
	if (bHorz)
	{
		rectGripper.DeflateRect (0, 4);
		rectGripper.left += rectGripper.Width () - 6;
		rectGripper.right = rectGripper.left + 6;
		//rectGripper.OffsetRect (1, 0);

		for (int i = 0; i < 3; i++)
		{
			CPen* pOldPen = pDC->SelectObject (&m_penGripper1);

			pDC->MoveTo (rectGripper.left, rectGripper.top);
			pDC->LineTo (rectGripper.left, rectGripper.bottom);

			pDC->SelectObject (pOldPen);
			pOldPen = pDC->SelectObject (&m_penGripper2);

			pDC->MoveTo (rectGripper.left + 1, rectGripper.top);
			pDC->LineTo (rectGripper.left + 1, rectGripper.bottom);

			pDC->SelectObject (pOldPen);

			rectGripper.OffsetRect (2, 0);
		}
	}
	else
	{
		rectGripper.DeflateRect (4, 0);
	}
}
//****************************************************************************************
void CMacStyle::OnDrawMenuBorder (CDC* pDC, CBCGPPopupMenu* /*pMenu*/, CRect rect)
{
	pDC->Draw3dRect (rect, m_clrMenuBorder, m_clrMenuBorder);
	rect.DeflateRect (1, 1);
	pDC->Draw3dRect (rect, m_clrMenuLight, m_clrMenuLight);
}
//****************************************************************************************
void CMacStyle::OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL /*bNCArea*/)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pBar);

	if (rectClip.IsRectEmpty ())
	{
		rectClip = rectClient;
	}

	if (DYNAMIC_DOWNCAST(CBCGPPopupMenuBar, pBar) != NULL)
	{
		pDC->FillRect (rectClip, &m_brMenuLight);
		return;
	}
	else if (pBar->IsKindOf (RUNTIME_CLASS (CBCGPStatusBar)))
    {
		CSize szSysBorder (GetSystemBorders ());

		CRect rect (rectClient);
		CRect rectExt (0, 0, 0, 0);

		//CRect rectBorders = m_ctrlStatusBarBack.GetParams ().m_rectSides;

		rect.InflateRect (szSysBorder.cx, 0, szSysBorder.cx, szSysBorder.cy);
		m_ctrlStatusBarBack.Draw (pDC, rect, m_bActive ? 0 : 1);

        return;
    }
	else if (pBar->IsKindOf (RUNTIME_CLASS (CBCGPOutlookBarPane)))
	{
		pDC->FillRect (rectClip, &m_brOutlook);
		return;
	}
	else if (DYNAMIC_DOWNCAST(CBCGPToolBar, pBar) != NULL)
	{
		CRect rectFill = rectClient;
/*
		if (!pBar->IsFloating ())
		{
			CRect rectMainFrame;
			pBar->GetTopLevelFrame ()->GetWindowRect (rectMainFrame);

			pBar->ScreenToClient (&rectMainFrame);
			rectFill = rectMainFrame;

			if (bNCArea)
			{
				CRect rectWindow;
				pBar->GetWindowRect (rectWindow);

				pBar->ScreenToClient (rectWindow);

				CRect rectClientActual;
				pBar->GetClientRect (rectClientActual);

				rectFill.left += rectClientActual.left - rectWindow.left;
				rectFill.top += rectClientActual.top - rectWindow.top;
				rectFill.right += 10;
			}
		}
*/
		CBCGPDrawManager dm(*pDC);
		dm.FillGradient (rectFill, RGB(149, 149, 149), RGB(197, 197, 197), TRUE);
		return;
	}

	pDC->FillRect (rectClip, &m_brFace);
}
//**************************************************************************************
void CMacStyle::OnDrawSeparator (CDC* pDC, CBCGPBaseControlBar* pBar,
										 CRect rect, BOOL bHorz)
{
	if (pBar->IsKindOf (RUNTIME_CLASS (CBCGPPopupMenuBar)) != NULL)
	{
		CBCGPVisualManagerXP::OnDrawSeparator (pDC, pBar, rect, bHorz);
		return;
	}
/*
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
		rectSeparator.left = CBCGPToolBar::GetMenuImageSize ().cx + 2 * (IMAGE_MARGIN + 2);
	}

	pDC->Draw3dRect (rectSeparator, ::GetSysColor (COLOR_3DSHADOW),
									::GetSysColor (COLOR_3DSHADOW));
*/
}
//**************************************************************************************
void CMacStyle::OnFillButtonInterior (CDC* pDC,
	CBCGPToolbarButton* pButton, CRect rect, CBCGPVisualManagerXP::BCGBUTTON_STATE state)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	if (DYNAMIC_DOWNCAST(CBCGPMenuBar, pButton->GetParentWnd ()) != NULL)
	{
		if (state != ButtonsIsRegular)
		{
			pDC->FillRect (rect, &m_brHighlight);
		}

		return;
	}
	else if (DYNAMIC_DOWNCAST(CBCGPPopupMenuBar, pButton->GetParentWnd ()) == NULL)
	{
		int index = 0;

		if ((pButton->m_nStyle & TBBS_DISABLED) == TBBS_DISABLED)
		{
			index = 3;
		}
		else
		{
			if ((pButton->m_nStyle & TBBS_PRESSED) == TBBS_PRESSED)
			{
				index = 2;
			}
			else if (state == ButtonsIsHighlighted)
			{
				index = 1;
			}
		}

		m_ctrlBtn.Draw (pDC, rect, index);

		return;
	}

	CBCGPVisualManagerXP::OnFillButtonInterior (pDC, pButton, rect, state);
}
//**************************************************************************************
void CMacStyle::OnDrawButtonBorder (CDC* pDC,
		CBCGPToolbarButton* pButton, CRect rect, BCGBUTTON_STATE state)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);
	
	if (pButton->IsKindOf (RUNTIME_CLASS (CBCGPToolbarMenuButton)) &&
		DYNAMIC_DOWNCAST(CBCGPPopupMenuBar, pButton->GetParentWnd ()) != NULL)
	{
		CBCGPVisualManagerXP::OnDrawButtonBorder (pDC, pButton, rect, state);
	}
}
//**************************************************************************************
void CMacStyle::OnDrawCaptionButton (CDC* /*pDC*/, CBCGPCaptionButton* /*pButton*/,  BOOL /*bActive*/,
									 BOOL /*bHorz*/, BOOL /*bMaximized*/, BOOL /*bDisabled*/)
{
}
//***************************************************************************************
void CMacStyle::OnEraseTabsArea (CDC* pDC, CRect rect, const CBCGPBaseTabWnd* /*pTabWnd*/)
{
	ASSERT_VALID (pDC);
	pDC->FillRect (rect, &m_brFace);
}
//****************************************************************************************
COLORREF CMacStyle::OnDrawControlBarCaption (CDC* /*pDC*/, CBCGPDockingControlBar* /*pBar*/, 
	BOOL /*bActive*/, CRect /*rectCaption*/, CRect /*rectButtons*/)
{
	return RGB (0, 0, 0);
}
//**************************************************************************************
COLORREF CMacStyle::GetToolbarButtonTextColor (	CBCGPToolbarButton* pButton,
												CBCGPVisualManagerXP::BCGBUTTON_STATE state)
{
	ASSERT_VALID (pButton);

	COLORREF clr = 
		(pButton->m_nStyle & TBBS_DISABLED) == TBBS_DISABLED
			? RGB (100, 100, 100)
			: RGB (0, 0, 0);

	if (pButton->IsKindOf (RUNTIME_CLASS (CBCGPOutlookButton)))
	{
		clr = RGB (0, 0, 0);
	}
	else if (DYNAMIC_DOWNCAST(CBCGPMenuBar, pButton->GetParentWnd ()) != NULL)
	{
		clr = (state != ButtonsIsRegular || pButton->IsDroppedDown ())
				? RGB (255, 255, 255)
				: RGB (0, 0, 0);
	}
	
	return clr;
}
//*********************************************************************************
void CMacStyle::OnFillOutlookPageButton (CDC* pDC, const CRect& rect,
										BOOL bIsHighlighted, BOOL bIsPressed,
										COLORREF& clrText)
{
	COLORREF clr1 = RGB (139, 139, 139);
	COLORREF clr2 = RGB (233, 233, 233);

	if (bIsPressed)
	{
		COLORREF clr = clr1;
		clr1 = clr2;
		clr2 = clr;
	}
	else if (bIsHighlighted)
	{
		clr1 = RGB (153, 153, 153);
		clr2 = RGB (255, 255, 255);
	}

	CBCGPDrawManager dm (*pDC);
	dm.FillGradient (rect, clr1, clr2, TRUE);

	clrText = RGB (32, 32, 32);
}
//*********************************************************************************
void CMacStyle::OnDrawOutlookPageButtonBorder (CDC* pDC, CRect& rectBtn, BOOL /*bIsHighlighted*/, BOOL /*bIsPressed*/)
{
	COLORREF clr = RGB (65, 65, 65);
	pDC->Draw3dRect (rectBtn, clr, clr);
}
//*****************************************************************************
void CMacStyle::OnDrawStatusBarPaneBorder (CDC* pDC, CBCGPStatusBar* /*pBar*/,
					CRect rectPane, UINT /*uiID*/, UINT nStyle)
{
	if ((nStyle & SBPS_STRETCH) == 0)
	{
		rectPane.left--;
		if (rectPane.Width () < 
			(m_ctrlStatusBarPaneBorder.GetParams ().m_rectCorners.left + 
			 m_ctrlStatusBarPaneBorder.GetParams ().m_rectCorners.right - 2))
		{
			rectPane.right = rectPane.left + 
				m_ctrlStatusBarPaneBorder.GetParams ().m_rectCorners.left + 
			    m_ctrlStatusBarPaneBorder.GetParams ().m_rectCorners.right - 2;
		}
		m_ctrlStatusBarPaneBorder.Draw (pDC, rectPane, 0);
	}
}
//*****************************************************************************
void CMacStyle::OnDrawStatusBarSizeBox (CDC* pDC, CBCGPStatusBar* /*pStatBar*/,
			CRect rectSizeBox)
{
    m_StatusBarSizeBox.DrawEx (pDC, rectSizeBox, 0, CBCGPToolBarImages::ImageAlignHorzRight, CBCGPToolBarImages::ImageAlignVertBottom);
}
//*****************************************************************************
void CMacStyle::DrawNcBtn (CDC* pDC, const CRect& rect, UINT nButton, 
										BCGBUTTON_STATE state, 
										BOOL bActive)
{
	ASSERT_VALID (pDC);

	CBCGPToolBarImages* pImage = NULL;

	if (nButton == SC_CLOSE)
	{
		pImage = &m_SysBtnClose;
	}
	else if (nButton == SC_MINIMIZE)
	{
		pImage = &m_SysBtnMinimize;
	}
	else if (nButton == SC_MAXIMIZE)
	{
		pImage = &m_SysBtnMaximize;
	}
	else if (nButton == SC_RESTORE)
	{
		pImage = &m_SysBtnRestore;
	}
	else
	{
		return;
	}

	CBCGPToolBarImages::ImageAlignHorz horz = CBCGPToolBarImages::ImageAlignHorzCenter;
	CBCGPToolBarImages::ImageAlignVert vert = CBCGPToolBarImages::ImageAlignVertCenter;

	CRect rtBtnImage (CPoint (0, 0), pImage->GetImageSize ());

	if (!bActive)
	{
		rtBtnImage.OffsetRect (0, pImage->GetImageSize ().cy);
	}

	int index = 0;
	if (!bActive)
	{
		index = 3;
	}
	else if (state != ButtonsIsRegular)
	{
		if (state == ButtonsIsPressed)
		{
			index = 2;
		}
		else
		{
			index = 1;
		}
	}

	m_ctrlSysBtnBack.Draw (pDC, rect, index);

	pImage->DrawEx (pDC, rect, 0, horz, vert, rtBtnImage);
}
//*****************************************************************************
void CMacStyle::DrawNcText (CDC* pDC, CRect& rect, 
							const CString& strTitle, 
							BOOL bActive, BOOL bIsRTL, BOOL bTextCenter)
{
	if (strTitle.IsEmpty () || rect.right <= rect.left)
	{
		return;
	}

	ASSERT_VALID (pDC);

	int nOldMode = pDC->SetBkMode (TRANSPARENT);
	COLORREF clrOldText = pDC->GetTextColor ();

	DWORD dwTextStyle = DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER |
		(bIsRTL ? DT_RTLREADING | DT_RIGHT : 0);

	COLORREF clrText = bActive 
		? RGB (  0,   0,   0)
		: RGB (136, 136, 136);

	int widthFull = rect.Width ();
	int width = pDC->GetTextExtent (strTitle).cx;

	if (bTextCenter && width < widthFull)
	{
		rect.left += (widthFull - width) / 2;
	}

	rect.right = min (rect.left + width, rect.right);

	if (rect.right > rect.left)
	{
		pDC->SetTextColor (clrText);
		pDC->DrawText (strTitle, rect, dwTextStyle);
	}

	pDC->SetBkMode    (nOldMode);
	pDC->SetTextColor (clrOldText);
}
//*****************************************************************************
void CMacStyle::DrawNcCaption (CDC* pDC, CRect rectCaption, 
											   DWORD dwStyle, DWORD dwStyleEx,
											   const CString& strTitle,
											   HICON hIcon, BOOL bActive, 
											   BOOL bTextCenter,
											   const CObList& lstSysButtons)
{
	const BOOL bIsRTL           = (dwStyleEx & WS_EX_LAYOUTRTL) == WS_EX_LAYOUTRTL;
	const int nSysCaptionHeight = ::GetSystemMetrics (SM_CYCAPTION);
	CSize szSysBorder (GetSystemBorders ());

    CDC memDC;
    memDC.CreateCompatibleDC (pDC);
    CBitmap memBmp;
    memBmp.CreateCompatibleBitmap (pDC, rectCaption.Width (), rectCaption.Height ());
    memDC.SelectObject (&memBmp);
	memDC.BitBlt (0, 0, rectCaption.Width (), rectCaption.Height (), pDC, 0, 0, SRCCOPY);

	m_ctrlMainBorderCaption.Draw (&memDC, rectCaption, bActive ? 0 : 1);

	CRect rect (rectCaption);
	rect.DeflateRect (szSysBorder.cx, 0, szSysBorder.cx, 0);

	// Draw icon:
	if (hIcon != NULL)
	{
		CSize szIcon (::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON));

		CRect rectIcon (rect.TopLeft (), CSize (nSysCaptionHeight, rect.Height ()));

		long x = rect.left + max (0, (rectIcon.Width ()  - szIcon.cx) / 2);
		long y = rect.top  + max (0, (rectIcon.Height () - szIcon.cy) / 2);

		::DrawIconEx (memDC.GetSafeHdc (), x, y, hIcon, szIcon.cx, szIcon.cy,
			0, NULL, DI_NORMAL);

		rect.left += rectIcon.Width ();
	}

	// Draw system buttons:
	int xButtonsRight = rect.right;

	for (POSITION pos = lstSysButtons.GetHeadPosition (); pos != NULL;)
	{
		CBCGPFrameCaptionButton* pButton = (CBCGPFrameCaptionButton*)
			lstSysButtons.GetNext (pos);
		ASSERT_VALID (pButton);

		BCGBUTTON_STATE state = ButtonsIsRegular;

		if (pButton->m_bPushed && pButton->m_bFocused)
		{
			state = ButtonsIsPressed;
		}
		else if (pButton->m_bFocused)
		{
			state = ButtonsIsHighlighted;
		}

		UINT uiHit = pButton->GetHit ();
		UINT nButton = 0;

		switch (uiHit)
		{
		case HTCLOSE_BCG:
			nButton = SC_CLOSE;
			break;

		case HTMAXBUTTON_BCG:
			nButton = 
				(dwStyle & WS_MAXIMIZE) == WS_MAXIMIZE ? SC_RESTORE : SC_MAXIMIZE;
			break;

		case HTMINBUTTON_BCG:
			nButton = 
				(dwStyle & WS_MINIMIZE) == WS_MINIMIZE ? SC_RESTORE : SC_MINIMIZE;
			break;
		}

		DrawNcBtn (&memDC, pButton->GetRect (), nButton, state, bActive);

		xButtonsRight = min (xButtonsRight, pButton->GetRect ().left);
	}

	// Draw text:
	if (!strTitle.IsEmpty () && rect.left < rect.right)
	{
		CFont* pOldFont = (CFont*)memDC.SelectObject (&m_AppCaptionFont);

		CRect rectText = rect;
		rectText.right = xButtonsRight - 1;

		DrawNcText (&memDC, rectText, strTitle, bActive, bIsRTL, bTextCenter);

		memDC.SelectObject (pOldFont);
	}

    pDC->BitBlt (rectCaption.left, rectCaption.top, rectCaption.Width (), rectCaption.Height (),
        &memDC, 0, 0, SRCCOPY);
}
//*****************************************************************************
BOOL CMacStyle::OnNcActivate (CWnd* pWnd, BOOL bActive)
{
	HWND hWnd = pWnd->GetSafeHwnd ();

	ASSERT_VALID (pWnd);

	if (hWnd == NULL)
	{
		return FALSE;
	}

	// stay active if WF_STAYACTIVE bit is on
	if (pWnd->m_nFlags & WF_STAYACTIVE)
	{
		bActive = TRUE;
	}

	// but do not stay active if the window is disabled
	if (!pWnd->IsWindowEnabled())
	{
		bActive = FALSE;
	}

	m_bActive = bActive;
	pWnd->SendMessage (WM_NCPAINT, 0, 0);

	return TRUE;
}
//*****************************************************************************
BOOL CMacStyle::OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw)
{
	ASSERT_VALID (pWnd);

	if (pWnd->GetSafeHwnd () == NULL)
	{
		return FALSE;
	}

	CWindowDC dc (pWnd);

	if (dc.GetSafeHdc () != NULL)
	{
		CRgn rgn;
		if (!rectRedraw.IsRectEmpty ())
		{
			rgn.CreateRectRgnIndirect (rectRedraw);
			dc.SelectClipRgn (&rgn);
		}

		CRect rtWindow;
		pWnd->GetWindowRect (rtWindow);
		pWnd->ScreenToClient (rtWindow);

		CRect rtClient;
		pWnd->GetClientRect (rtClient);

		rtClient.OffsetRect (-rtWindow.TopLeft ());
		dc.ExcludeClipRect (rtClient);

		rtWindow.OffsetRect (-rtWindow.TopLeft ());

		CRect rectCaption (rtWindow);
		CSize szSysBorder (GetSystemBorders ());

		rectCaption.bottom = rectCaption.top + szSysBorder.cy;

		const int nSysCaptionHeight = ::GetSystemMetrics (SM_CYCAPTION);
		rectCaption.bottom += nSysCaptionHeight;

		const DWORD dwStyle   = pWnd->GetStyle ();
		const DWORD dwStyleEx = pWnd->GetExStyle ();

		HICON hIcon = globalUtils.GetWndIcon (pWnd);

		CString strTitle;
		pWnd->GetWindowText (strTitle);

		DrawNcCaption (&dc, rectCaption, dwStyle, dwStyleEx, 
						strTitle, hIcon, m_bActive, TRUE,
						lstSysButtons);

		rtWindow.top = rectCaption.bottom;

		dc.ExcludeClipRect (rectCaption);
		m_ctrlMainBorder.DrawFrame (&dc, rtWindow, m_bActive ? 0 : 1);

		//-------------------------------
		// Find status bar extended area:
		//-------------------------------
		CBCGPStatusBar* pStatusBar = DYNAMIC_DOWNCAST (
			CBCGPStatusBar, pWnd->GetDescendantWindow (AFX_IDW_STATUS_BAR, TRUE));

		if (pStatusBar->GetSafeHwnd () != NULL && pStatusBar->IsWindowVisible ())
		{
			CRect rectStatus;
			pStatusBar->GetClientRect (rectStatus);

			int nHeight = rectStatus.Height ();
			rectStatus.bottom = rtWindow.bottom;
			rectStatus.top    = rectStatus.bottom - nHeight - szSysBorder.cy;
			rectStatus.left   = rtWindow.left;
			rectStatus.right  = rtWindow.right;

			m_ctrlStatusBarBack.Draw (&dc, rectStatus, m_bActive ? 0 : 1);
		}

		dc.SelectClipRgn (NULL);
		return TRUE;
	}

	return CBCGPVisualManagerXP::OnNcPaint (pWnd, lstSysButtons, rectRedraw);
}
//*****************************************************************************
BOOL CMacStyle::OnSetWindowRegion (CWnd* pWnd, CSize sizeWindow)
{
	ASSERT_VALID (pWnd);

	if (pWnd->GetSafeHwnd () == NULL)
	{
		return FALSE;
	}

    CSize sz (0, 0);

	BOOL bMainWnd = pWnd == AfxGetMainWnd ();

	if (bMainWnd)
	{
		if ((pWnd->GetStyle () & WS_MAXIMIZE) == WS_MAXIMIZE)
		{
			pWnd->SetWindowRgn (NULL, TRUE);
			return TRUE;
		}

		sz  = CSize (9, 9);

		bMainWnd = TRUE;
	}

	if (sz != CSize (0, 0))
	{
        CRgn rgn;
		BOOL bCreated = FALSE;

		bCreated = rgn.CreateRoundRectRgn (0, 0, sizeWindow.cx + 1, sizeWindow.cy + 1, sz.cx, sz.cy);

		if (bCreated)
		{
			pWnd->SetWindowRgn ((HRGN)rgn.Detach (), TRUE);
			return TRUE;
		}
	}

	return FALSE;
}

CSize CMacStyle::GetSystemBorders () const
{
	return CSize (::GetSystemMetrics (SM_CYSIZEFRAME), 
			    ::GetSystemMetrics (SM_CXSIZEFRAME));
}

CSize CMacStyle::GetNcBtnSize (BOOL /*bSmall*/) const
{
	return CSize (m_ctrlSysBtnBack.GetParams ().m_rectImage.Size ());
}
