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

#include "stdafx.h"
#include "VisualManager.h"
#include "TabHeaderLayout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabHeaderLayout implementation

IMPLEMENT_DYNCREATE (CTabHeaderLayout, CObject)

CTabHeaderLayout::CTabHeaderLayout ()
: m_bShowTab(false), m_cyCaption(0)
{
    m_rcWindow.SetRectEmpty ();
    m_rcTab.SetRectEmpty ();
    m_rcTabCloseBtn.SetRectEmpty ();
    m_rcMenu.SetRectEmpty ();
    m_rcCloseBtn.SetRectEmpty ();
}

CTabHeaderLayout::~CTabHeaderLayout ()
{

}

CShopVisualManager* CTabHeaderLayout::GetVisualManager() const
{
    return DYNAMIC_DOWNCAST (CShopVisualManager, CBCGPVisualManager::GetInstance ());
}

int CTabHeaderLayout::GetTabCaptionHeight () const
{
    CShopVisualManager* pVisualManager = GetVisualManager( );
    return pVisualManager != NULL ?
        pVisualManager->m_imgTabbedBar.GetParams ().m_rectCorners.top : 0;
}

void CTabHeaderLayout::Paint(CDC* pDC, CWnd* pContentWnd)
{
    ASSERT_VALID (pDC);
    CShopVisualManager* pVisualManager = GetVisualManager ();
    ASSERT_VALID (pVisualManager);
    if (pVisualManager == NULL) return;

    // paint with menu
    CRect rectTabArea = m_rcWindow;
    rectTabArea.bottom = rectTabArea.top + GetTabCaptionHeight () + 2;
    if (!m_rcMenu.IsRectEmpty ())
    {
        pVisualManager->m_imgTabbedBar.Draw (pDC, rectTabArea, 0); // with menu
    }
    else
    {
        pVisualManager->m_imgTabbedBar.Draw (pDC, rectTabArea, 1); // without menu
    }

    CString caption;
    if (pContentWnd != NULL)
    {
        pContentWnd->GetWindowText (caption);
    }

    if (!m_bShowTab) return;

    // Drawing a tab
    pVisualManager->m_imgTabHeaders[0].Draw (pDC, m_rcTab, 2);

    bool bCloseBtn = !m_rcTabCloseBtn.IsRectEmpty ();
    if (!caption.IsEmpty ())
    {
        CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);

        CRect rcText = m_rcTab;
        rcText.DeflateRect(4, 0, bCloseBtn ? 22 : 4, 0);

        pDC->SetTextColor (globalData.clrWindowText);
        pDC->SetBkMode (TRANSPARENT);
        pDC->DrawText (caption, rcText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_LEFT);
        pDC->SelectObject (pOldFont);
    }

    if (bCloseBtn)
    {
        DrawTabCloseButton (pDC, FALSE, FALSE);
    }

}

void CTabHeaderLayout::DrawTabCloseButton (CDC* pDC, BOOL bHighlighted, BOOL bPressed)
{
    CShopVisualManager* pVisualManager = GetVisualManager ();
    ASSERT_VALID (pVisualManager);
    if (!m_rcTabCloseBtn.IsRectEmpty () && pVisualManager != NULL)
    {
        int nImage = 0;
        if (bPressed) nImage = 1;
        if (bHighlighted) nImage = 2;
        pVisualManager->m_imgTabCloseButton.Draw (pDC, m_rcTabCloseBtn, nImage);
    }
}

void CTabHeaderLayout::Reset ()
{
    m_bShowTab = FALSE;
    m_cyCaption = 0;
    m_rcCloseBtn.SetRectEmpty();
    m_rcMenu.SetRectEmpty();
    m_rcTab.SetRectEmpty();
    m_rcTabCloseBtn.SetRectEmpty();
}

void CTabHeaderLayout::Update (const CRect& rcWindow, const CString& caption)
{
    m_rcWindow = rcWindow;
    Reset ();
    m_bShowTab = !caption.IsEmpty ();
    CShopVisualManager* pVisualManager = GetVisualManager();
    if (pVisualManager == NULL) return;

    m_cyCaption = pVisualManager->m_imgTabbedBar.GetParams().m_rectCorners.top;
    if (m_cyCaption == 0) return;

    if (rcWindow.Width() > 20) // Is there enough space for menu?
    {
        // menu
        m_rcMenu = m_rcWindow;
        m_rcMenu.top += 17;
        m_rcMenu.bottom = m_rcMenu.top + 7;
        m_rcMenu.right -= 2;
        m_rcMenu.left = m_rcMenu.right - 15;
    }

    if (!caption.IsEmpty ())
    {
        // Calculate the maximum space for tab
        m_rcTab = m_rcWindow;
        m_rcTab.top += 3;
        m_rcTab.bottom = m_rcTab.top + m_cyCaption - 4;
        m_rcTab.left += 3;
        if (!m_rcMenu.IsRectEmpty ())
        {
            m_rcTab.right = m_rcMenu.left - 2;
        }
        m_rcTab.right -= 3; //(pVisualManager->m_imgTabbedBar.GetParams ().m_rectCorners.right + 3);

        CDC dcScreen;
        dcScreen.Attach (::GetDC (NULL));
        CFont* pOldFont = dcScreen.SelectObject (&globalData.fontRegular);
        CSize textSize = dcScreen.GetTextExtent (caption);
        dcScreen.SelectObject (pOldFont);
        ::ReleaseDC (NULL, dcScreen.Detach ());

        bool bTabCloseBtn = (textSize.cx > 16);
        CSize szButton = pVisualManager->m_imgTabCloseButton.GetParams ().m_rectImage.Size ();

        textSize.cx += 8; // text margins
        if (bTabCloseBtn) 
            textSize.cx += szButton.cx + 8;
        if (m_rcTab.Width () > textSize.cx)
            m_rcTab.right = m_rcTab.left + textSize.cx;

        if (bTabCloseBtn) // Is there enough space for tab close button?
        {
            m_rcTabCloseBtn = m_rcTab;
            m_rcTabCloseBtn.right -= 4;
            m_rcTabCloseBtn.left = m_rcTabCloseBtn.right - szButton.cx;
            m_rcTabCloseBtn.top += (m_rcTabCloseBtn.Height() - szButton.cy)/ 2;
            m_rcTabCloseBtn.bottom = m_rcTabCloseBtn.top + szButton.cy;
        }

        //rectTabArea.right = rectTabArea.left + textSize.cx;
        //rectTabArea.DeflateRect (3, 3, (m_imgTabbedBar.GetParams ().m_rectCorners.right + 5), 3);

        //m_imgTabHeaders[0].Draw (pDC, rectTabArea, 2);

        //CRect rectText = rectTabArea;
        //rectText.DeflateRect (5, 0, 16, 0);

        //pDC->SetTextColor (0x000000);
        //pDC->SetBkMode (TRANSPARENT);
        //pDC->DrawText (caption, rectText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_LEFT);
        //pDC->SelectObject (pOldFont);
    }

}

int CTabHeaderLayout::HitTest (const CPoint& point)
{
    if (!m_rcWindow.PtInRect(point))
        return HTNOWHERE;
    if (m_rcMenu.PtInRect(point))
        return HTSYSMENU;
    if (m_rcTabCloseBtn.PtInRect(point))
        return HTCLOSE;
    if (point.y < (m_rcWindow.top + m_cyCaption))
        return HTCAPTION;
    return HTCLIENT;
}

