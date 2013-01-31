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
// VisualManager.cpp : implementation file
//

#include "stdafx.h"
#include "VisualManager.h"
#include "TabbedBar.h"
#include "ShopToolBase.h"
#include "ContextToolbar.h"
#include "PaletteMiniFrame.h"
#include "resource.h"

#include <BCGPDockBar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CShopVisualManager implementation

IMPLEMENT_DYNCREATE(CShopVisualManager, CBCGPWinXPVisualManager)

CShopVisualManager::CShopVisualManager ()
{
    CBCGPSlider::m_nDefaultWidth = 2;

    CBCGPControlRendererParams crp;
    crp.m_uiBmpResID = IDB_TOOLBUTTONS;
    crp.m_rectImage = CRect (0, 0, 20, 15);
    crp.m_rectSides = CRect (1, 1, 1, 2);
    crp.m_rectCorners = CRect (3, 3, 3, 3);
    crp.m_clrTransparent = 0xFFFFFF;
    m_imgToolButtonFrame.Create (crp);

    crp.m_uiBmpResID = IDB_TABHEADERS;
    crp.m_rectImage = CRect (0, 0, 15, 16);
    crp.m_rectSides = CRect (1, 1, 1, 2);
    crp.m_rectCorners = CRect (4, 4, 4, 2);
    crp.m_clrTransparent = RGB(255, 0, 255); // Magenta pixels are transparent
    m_imgTabHeaders[0].Create (crp, FALSE); // Original for top side
    m_imgTabHeaders[1].Create (crp, TRUE); // flipped vertically - for bottom side

    crp.m_uiBmpResID = IDB_TABCLOSEBTN;
    crp.m_rectImage = CRect (0, 0, 11, 11);
    crp.m_rectSides.SetRectEmpty ();
    crp.m_rectCorners.SetRectEmpty ();
    crp.m_clrTransparent = 0xFFFFFF;
    m_imgTabCloseButton.Create (crp);

    crp.m_uiBmpResID = IDB_TABBEDBAR;
    crp.m_rectImage.SetRect (0, 0, 31, 32);
    crp.m_rectCorners.SetRect (3, 25, 26, 3);
    crp.m_clrTransparent = 0x000000;
    m_imgTabbedBar.Create (crp);
}
//*******************************************************************************
CShopVisualManager::~CShopVisualManager()
{
}
//*******************************************************************************
void CShopVisualManager::OnDrawSeparator (CDC* pDC, CBCGPBaseControlBar* /*pBar*/,
										 CRect rect, BOOL bHorz)
{
	ASSERT_VALID (pDC);

	if (bHorz)
	{
		rect.left += rect.Width () / 2 - 1;
		rect.right = rect.left + 2;
	}
	else
	{
		rect.top += rect.Height () / 2 - 1;
		rect.bottom = rect.top + 2;
	}

	pDC->Draw3dRect (rect, RGB (166, 167, 170), RGB (237, 237, 237));
}
//*******************************************************************************
void CShopVisualManager::OnFillButtonInterior (CDC* pDC,
                           CBCGPToolbarButton* pButton, CRect rect,
                           CBCGPVisualManager::BCGBUTTON_STATE state)
{
    if (pButton == NULL)
    {
        return;
    }
    CBCGPBaseToolBar* pToolBar = DYNAMIC_DOWNCAST (CBCGPBaseToolBar, pButton->GetParentWnd ());
    if (pToolBar->IsKindOf (RUNTIME_CLASS (CBCGPMenuBar)))
    {
        BOOL bChecked = (pButton->m_nStyle & TBBS_CHECKED);
        BOOL bHilited = (state == ButtonsIsHighlighted);
        int index = 0;
        if (bHilited)
        {
            index = 4;
        }
        if (bChecked)
        {
            index = 5;
        }
        m_imgToolButtonFrame.Draw (pDC, rect, index);
    }
    else
    {
        CBCGPWinXPVisualManager::OnFillButtonInterior (pDC, pButton, rect, state);
    }
}
//*******************************************************************************
void CShopVisualManager::OnDrawBarGripper (CDC* pDC, CRect rectGripper, BOOL bHorz,
                                           CBCGPBaseControlBar* /*pBar*/)
{
    if (rectGripper.IsRectEmpty ())
    {
        return;
    }
    
    COLORREF clrDot = RGB (153, 153, 153);
    int h = rectGripper.Height ();
    int w = rectGripper.Width ();
    if (bHorz)
    {               
        if (h >= 6 && w >= 3)
        {
            int x = rectGripper.left + w / 2;
            int margin = min (8, h / 2 - 6);
            for (int i = rectGripper.top + margin; i < rectGripper.bottom - margin; i += 2)
            {
                pDC->SetPixel (x - 1, i, clrDot);
                pDC->SetPixel (x + 1, i, clrDot);
            }
        }
    }
    else
    {
        if (w >= 6 && h >= 3)
        {
            int y = rectGripper.top + h / 2;
            int margin = min (8, w / 2 - 6);
            for (int i = rectGripper.left + margin; i < rectGripper.right - margin; i += 2)
            {
                pDC->SetPixel (i, y - 1, clrDot);
                pDC->SetPixel (i, y + 1, clrDot);
            }
        }
    }
}
//*******************************************************************************
void CShopVisualManager::OnDrawTab (CDC* pDC, CRect rectTab, int iTab,
                                    BOOL bIsActive, const CBCGPBaseTabWnd* pTabWnd)
{
    ASSERT_VALID (pDC);
    const BOOL bBottom = (pTabWnd->GetLocation () == CBCGPTabWnd::LOCATION_BOTTOM);
    const BOOL bIsHighlight = (iTab == pTabWnd->GetHighlightedTab ());

	CRect rectTabImage = rectTab;
	if (bBottom)
	{
		rectTabImage.top = rectTabImage.bottom - 21;
	}
	else
	{
		rectTabImage.bottom = rectTabImage.top + 21;
	}

    int nImage = 0;
    if (bIsHighlight) nImage = 1;
    if (bIsActive) nImage = 2;
    m_imgTabHeaders[bBottom ? 1 : 0].Draw (pDC, rectTabImage, nImage);


    // Render Text

    COLORREF clrText = pTabWnd->GetTabTextColor (iTab);

    COLORREF cltTextOld = (COLORREF)-1;
    if (!bIsActive && clrText != (COLORREF)-1)
    {
        cltTextOld = pDC->SetTextColor (clrText);
    }

    CRect rectClip;
    pTabWnd->GetTabsRect (rectClip);

    CRgn rgn;
    rgn.CreateRectRgnIndirect (rectClip);
    pDC->SelectClipRgn (&rgn);

    OnDrawTabContent (pDC, rectTab, iTab, bIsActive, pTabWnd, (COLORREF)-1);

    if (cltTextOld != (COLORREF)-1)
    {
        pDC->SetTextColor (cltTextOld);
    }

    pDC->SelectClipRgn (NULL);
}
//*******************************************************************************
void CShopVisualManager::OnDrawTabCloseButton (
               CDC* pDC, CRect rect, const CBCGPBaseTabWnd* /*pTabWnd*/, 
               BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled)
{
    int nImage = 0;
    if (bIsHighlighted) nImage = 2;
    if (bIsPressed) nImage = 1;
    if (bIsDisabled) nImage = 0;

    CSize szButton = m_imgTabCloseButton.GetParams ().m_rectImage.Size ();
    rect.left += (rect.Width () - szButton.cx)/ 2;
    rect.top += (rect.Height () - szButton.cy)/ 2;
    rect.right = rect.left + szButton.cx;
    rect.bottom = rect.top + szButton.cy;
    m_imgTabCloseButton.Draw (pDC, rect, nImage);
}
//*******************************************************************************
BOOL CShopVisualManager::OnEraseTabsFrame (CDC* pDC, CRect rect, 
                                           const CBCGPBaseTabWnd* /*pTabWnd*/) 
{	
    ASSERT_VALID (pDC);
    m_imgTabbedBar.Draw (pDC, rect);
    return TRUE;
}
//*******************************************************************************
COLORREF CShopVisualManager::OnFillMiniFrameCaption (CDC* pDC, CRect rectCaption, 
                                         CBCGPMiniFrameWnd* pFrameWnd, BOOL bActive)
{
	if (pFrameWnd->IsKindOf (RUNTIME_CLASS (CPaletteMiniFrame)))
	{
		CBCGPDrawManager dm (*pDC);
		rectCaption.DeflateRect (0, 0, 0, 1);
		dm.DrawRect (rectCaption, 0xCDCDCD, 0xDDDDDD);
		dm.DrawLine (rectCaption.left, rectCaption.bottom, rectCaption.right, rectCaption.bottom, RGB (164, 164, 164));
		rectCaption.DeflateRect (1, 1, 1, 1);
		dm.FillGradient (rectCaption, 0xCDCDCD, 0xE5E5E5, TRUE);

		return bActive ? globalData.clrCaptionText : globalData.clrInactiveCaptionText;
	}
	return CBCGPWinXPVisualManager::OnFillMiniFrameCaption (pDC, rectCaption, pFrameWnd, bActive);
}
//*******************************************************************************
void CShopVisualManager::OnHighlightMenuItem (CDC*pDC, CBCGPToolbarMenuButton* /*pButton*/,
                                              CRect rect, COLORREF& /*clrText*/)
{
    ASSERT_VALID (pDC);

    CPen  whitePen (PS_SOLID, 1, RGB (255, 255, 255));
    CPen* pOldPen = pDC->SelectObject (&whitePen);
    CBrush* pOldBrush = pDC->SelectObject (&globalData.brHilite);
    pDC->Rectangle (rect);
    pDC->SelectObject (pOldBrush);
    pDC->SelectObject (pOldPen);
}
//*******************************************************************************
void CShopVisualManager::OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
                                              CRect rectClient, CRect rectClip,
                                              BOOL bNCArea)
{
    ASSERT_VALID (pBar);
    ASSERT_VALID (pDC);

    if (pBar->IsKindOf (RUNTIME_CLASS (CContextToolbar)))
    {
        CBCGPDrawManager dm (*pDC);
        dm.FillGradient (rectClient, RGB (217, 217, 217), RGB (247, 247, 247), pBar->IsHorizontal ());
        return;
    }

    if (pBar->IsKindOf (RUNTIME_CLASS (CBCGPToolBar)))
    {
        COLORREF clrFill = globalData.clrBarFace;

        if (pBar->IsKindOf (RUNTIME_CLASS (CBCGPMenuBar)) || pBar->IsKindOf (RUNTIME_CLASS (CBCGPPopupMenuBar)))
        {
            clrFill = RGB (222, 222, 222);
        }

        pDC->FillSolidRect (rectClient, clrFill);
        return;
    }

    if (pBar->IsKindOf (RUNTIME_CLASS (CBCGPDockBar)))
    {
        CRect rectFill = rectClient;

        CPen pen (PS_SOLID, 1, 0x333333);
        CPen* pOldPen = pDC->SelectObject (&pen);

        pDC->FillSolidRect (rectFill, 0x646464);
        pDC->MoveTo (rectFill.left, rectFill.top);
        pDC->LineTo (rectFill.left, rectFill.bottom - 1);
        pDC->MoveTo (rectFill.right - 1, rectFill.top);
        pDC->LineTo (rectFill.right - 1, rectFill.bottom - 1);

        CPen pen2 (PS_SOLID, 1, 0x767676);
        pDC->SelectObject (&pen2);

        pDC->MoveTo (rectFill.left + 1, rectFill.top);
        pDC->LineTo (rectFill.left + 1, rectFill.bottom - 1);
        pDC->MoveTo (rectFill.right - 2, rectFill.top);
        pDC->LineTo (rectFill.right - 2, rectFill.bottom - 1);

        pDC->SelectObject (pOldPen);
        return;
    }

    // call default handler
    CBCGPWinXPVisualManager::OnFillBarBackground (pDC, pBar, rectClient, rectClip, bNCArea);
}
//*******************************************************************************
COLORREF CShopVisualManager::OnDrawControlBarCaption (
                CDC* pDC, CBCGPDockingControlBar* pBar, 
                BOOL bActive, CRect rectCaption, CRect rectButtons)
{
    if (pBar->IsKindOf (RUNTIME_CLASS (CShopToolBase)))
    {
        DrawSingleTab (pDC, rectCaption, pBar);
        return 0xDADADA;
    }
    else
    {
        return CBCGPWinXPVisualManager::OnDrawControlBarCaption (
                    pDC, pBar, bActive, rectCaption, rectButtons);
    }

    ASSERT_VALID (pDC);

    CBrush br (bActive ? globalData.clrActiveCaption : globalData.clrInactiveCaption);
    pDC->FillRect (rectCaption, &br);

    // get the text color
    return bActive ? globalData.clrCaptionText : globalData.clrInactiveCaptionText;
}
//*******************************************************************************
void CShopVisualManager::OnDrawSlider (CDC* pDC, CBCGPSlider* /*pSlider*/, CRect rect, BOOL /*bAutoHideMode*/)
{
    ASSERT_VALID (pDC);
    pDC->FillSolidRect (rect, 0x5B5B5B);
    return;
}
//*******************************************************************************
int CShopVisualManager::GetTabAreaHeight() const
{
    return m_imgTabbedBar.GetParams ().m_rectCorners.top;
}
//*******************************************************************************
void CShopVisualManager::DrawSingleTab(CDC* pDC, CRect rectTabArea, CWnd* pContentWnd)
{
    ASSERT_VALID (pDC);
    ASSERT_VALID (pContentWnd);
    rectTabArea.bottom = rectTabArea.top + GetTabAreaHeight () + 2;
    m_imgTabbedBar.Draw (pDC, rectTabArea);

    if (pContentWnd != NULL)
    {
        CString caption;
        pContentWnd->GetWindowText (caption);
        if (!caption.IsEmpty ())
        {
            CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);

            rectTabArea.DeflateRect (3, 3, (m_imgTabbedBar.GetParams ().m_rectCorners.right + 3), 3);
            CSize textSize = pDC->GetTextExtent (caption);
            textSize.cx += 24;
            if (textSize.cx > rectTabArea.Width ())
            {
                textSize.cx = rectTabArea.Width ();
            }

            rectTabArea.right = rectTabArea.left + textSize.cx;

            m_imgTabHeaders[0].Draw (pDC, rectTabArea, 2);

            CRect rectText = rectTabArea;
            rectText.DeflateRect (5, 0, 16, 0);

            pDC->SetTextColor (0x000000);
            pDC->SetBkMode (TRANSPARENT);
            pDC->DrawText (caption, rectText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_LEFT);
            pDC->SelectObject (pOldFont);
        }
    }
}
//*******************************************************************************
void CShopVisualManager::OnUpdateSystemColors ()
{
	CBCGPWinXPVisualManager::OnUpdateSystemColors ();

	globalData.clrBarFace = RGB (237, 237, 237);
	globalData.clrBarShadow = RGB (166, 167, 170);
	globalData.clrBarDkShadow = RGB (140, 135, 133);
	globalData.clrBarLight = RGB (228, 223, 220);
	globalData.clrBarHilite = RGB (237, 237, 237);
	globalData.clrBarText = 0;
	globalData.clrGrayedText = RGB (170, 166, 167);
	globalData.clrWindowText = 0;
	globalData.clrBtnText =  0;   

	globalData.clrHilite = RGB (157, 185, 203);
	globalData.clrTextHilite = RGB (255, 255, 255);

	globalData.brBarFace.DeleteObject ();
	globalData.brBarFace.CreateSolidBrush (globalData.clrBarFace);

	globalData.brHilite.DeleteObject ();
	globalData.brHilite.CreateSolidBrush (globalData.clrHilite);

	globalData.penHilite.DeleteObject ();
	globalData.penHilite.CreatePen (PS_SOLID, 1, globalData.clrHilite);

	globalData.penBarFace.DeleteObject ();
	globalData.penBarFace.CreatePen (PS_SOLID, 1, globalData.clrBarFace);

	globalData.penBarShadow.DeleteObject ();
	globalData.penBarShadow.CreatePen (PS_SOLID, 1, globalData.clrBarShadow);


	SetShadowHighlightedImage (FALSE);
}
//*******************************************************************************
