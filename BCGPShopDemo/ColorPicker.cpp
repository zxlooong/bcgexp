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
#include "ColorPicker.h"
#include "MainFrm.h"
#include <BCGPToolBar.h>
#include <BCGPColorDialog.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////
// CShopToolbarColorPicker

IMPLEMENT_SERIAL(CShopToolbarColorPicker, CBCGPToolbarButton, 1)

//*******************************************************************************
void CShopToolbarColorPicker::Serialize (CArchive& ar)
{
    CBCGPToolbarButton::Serialize (ar);

    if (ar.IsLoading ())
    {
        ar >> m_clrLeft;
        ar >> m_clrRight;
    }
    else
    {
        ar << m_clrLeft;
        ar << m_clrRight;
    }
}
//*******************************************************************************
void CShopToolbarColorPicker::CopyFrom (const CBCGPToolbarButton& src)
{
    CBCGPToolbarButton::CopyFrom (src);
    const CShopToolbarColorPicker* source = DYNAMIC_DOWNCAST (CShopToolbarColorPicker,&src);
    m_clrLeft = source->m_clrLeft;
    m_clrRight = source->m_clrRight;
    m_imgMinibuttons = source->m_imgMinibuttons;
}
//*******************************************************************************
CShopToolbarColorPicker::CShopToolbarColorPicker ()
    : m_bCompactLayout (FALSE)
{
    ResetColors ();
}
//*******************************************************************************
void CShopToolbarColorPicker::ResetColors ()
{
    SetLeftColor (0x000000); // Black
    SetRightColor (0xFFFFFF); // White
}
//*******************************************************************************
void CShopToolbarColorPicker::SetLeftColor (COLORREF color)
{
    if (m_clrLeft != color)
    {
        m_clrLeft = color;
        if (m_pWndParent)
        {
            m_pWndParent->Invalidate ();
        }
        CWnd* pMainWnd = AfxGetMainWnd ();
        if (pMainWnd != NULL)
        {
            pMainWnd->PostMessage (WM_SETACTIVECOLOR, (WPARAM)0, (LPARAM)m_clrLeft);
        }
    }
}
//*******************************************************************************
void CShopToolbarColorPicker::SetRightColor (COLORREF color)
{
    if (m_clrRight != color)
    {
        m_clrRight = color;
        if (m_pWndParent)
        {
            m_pWndParent->Invalidate ();
        }
        CWnd* pMainWnd = AfxGetMainWnd ();
        if (pMainWnd != NULL)
        {
            pMainWnd->PostMessage (WM_SETACTIVECOLOR, (WPARAM)1, (LPARAM)m_clrRight);
        }
    }
}
//*******************************************************************************
void CShopToolbarColorPicker::SwapColors ()
{
    COLORREF t = m_clrRight;
    m_clrRight = m_clrLeft;
    m_clrLeft = t;
    if (m_pWndParent)
    {
        m_pWndParent->Invalidate ();
    }
    CWnd* pMainWnd = AfxGetMainWnd ();
    if (pMainWnd != NULL)
    {
        pMainWnd->PostMessage (WM_SETACTIVECOLOR, (WPARAM)0, (LPARAM)m_clrLeft);
        pMainWnd->PostMessage (WM_SETACTIVECOLOR, (WPARAM)1, (LPARAM)m_clrRight);
    }
}
//*******************************************************************************
void CShopToolbarColorPicker::SetCompactLayout(BOOL bCompact)
{
    if (m_bCompactLayout != bCompact)
    {
        m_bCompactLayout = bCompact;
        CBCGPToolBar* pToolBar = DYNAMIC_DOWNCAST(CBCGPToolBar, m_pWndParent);
        if (pToolBar)
        {
            pToolBar->AdjustLayout ();
        }
    }
}
//*******************************************************************************
void CShopToolbarColorPicker::SetMiniButtonImages (UINT uiResourceID)
{
    m_imgMinibuttons.LoadBitmap (uiResourceID);
    ASSERT (m_imgMinibuttons.GetSize() == CSize (22, 11));
    if (m_pWndParent)
    {
        m_pWndParent->Invalidate ();
    }
}
//*******************************************************************************
SIZE CShopToolbarColorPicker::OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz)
{
    if (!IsVisible ())
    {
        return CBCGPToolbarButton::OnCalculateSize (pDC, sizeDefault, bHorz);
    }

    SIZE sz;
    if (m_bCompactLayout)
    {
        m_rcArea[eLeftColorArea  ].SetRect ( 1, 15, 23, 37);
        m_rcArea[eRightColorArea ].SetRect (11, 25, 33, 47);
        m_rcArea[eResetButtonArea].SetRect ( 3,  1, 14, 12);
        m_rcArea[eSwapButtonArea ].SetRect (19,  1, 30, 12);
        sz.cx = 34;
        sz.cy = 48;
    }
    else
    {
        m_rcArea[eLeftColorArea  ].SetRect ( 3,  3, 31, 31);
        m_rcArea[eRightColorArea ].SetRect (16, 15, 45, 44);
        m_rcArea[eResetButtonArea].SetRect ( 2, 35, 13, 46);
        m_rcArea[eSwapButtonArea ].SetRect (33,  2, 44, 13);
        sz.cx = 47;
        sz.cy = 47;
    }
    return sz;
}
//*******************************************************************************
void CShopToolbarColorPicker::OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages*, BOOL, BOOL, BOOL, BOOL, BOOL)
{
    if (m_imgMinibuttons.IsValid ())
    {
        m_imgMinibuttons.DrawPart (
            *pDC,
            m_rcArea[eResetButtonArea].left + rect.left,
            m_rcArea[eResetButtonArea].top + rect.top,
            0, 0,
            m_rcArea[eResetButtonArea].Width(),
            m_rcArea[eResetButtonArea].Height() );

        m_imgMinibuttons.DrawPart (
            *pDC,
            m_rcArea[eSwapButtonArea].left + rect.left,
            m_rcArea[eSwapButtonArea].top + rect.top,
            11, 0,
            m_rcArea[eSwapButtonArea].Width(),
            m_rcArea[eSwapButtonArea].Height() );
    }

    CPen whitePen (PS_SOLID, 1, 0xFFFFFF);
    CBrush rBrush (m_clrRight);
    CBrush lBrush (m_clrLeft);

    CRect rcPicker = m_rcArea[eRightColorArea];
    rcPicker.OffsetRect (rect.TopLeft ());
    pDC->FillSolidRect (rcPicker, 0xC0C0C0);
    rcPicker.DeflateRect (1, 1, 1, 1);
    CPen* oldPen = pDC->SelectObject (&whitePen);
    CBrush* oldBrush = pDC->SelectObject (&rBrush);
    pDC->Rectangle (rcPicker);

    rcPicker = m_rcArea[eLeftColorArea];
    rcPicker.OffsetRect (rect.TopLeft ());
    pDC->FillSolidRect (rcPicker, 0xC0C0C0);
    rcPicker.DeflateRect (1, 1, 1, 1);
    pDC->SelectObject (&lBrush);
    pDC->Rectangle (rcPicker);

    pDC->SelectObject (oldBrush);
    pDC->SelectObject (oldPen);
}
//*******************************************************************************
BOOL CShopToolbarColorPicker::OnClick (CWnd* /*pWnd*/, BOOL /*bDelay*/)
{
    CRect rcLeft = m_rcArea[eLeftColorArea];
    rcLeft.DeflateRect (2, 2, 2, 2);
    CRect rcRight = m_rcArea[eRightColorArea];
    rcRight.DeflateRect (2, 2, 2, 2);

    CPoint ptClick;
    ::GetCursorPos (&ptClick);

    ASSERT (m_pWndParent != NULL);

    m_pWndParent->ScreenToClient (&ptClick);

    ptClick.Offset (-m_rect.left, -m_rect.top);

    if (rcLeft.PtInRect (ptClick))
    {
        CBCGPColorDialog dlg (m_clrLeft);
        if (dlg.DoModal ())
        {
            SetLeftColor (dlg.GetColor ());
            return TRUE;
        }
        return FALSE;
    }
    if (rcRight.PtInRect (ptClick))
    {
        CBCGPColorDialog dlg (m_clrRight);
        if (dlg.DoModal ())
        {
            SetRightColor (dlg.GetColor ());
            return TRUE;
        }
        return FALSE;
    }
    if (m_rcArea[eResetButtonArea].PtInRect (ptClick))
    {
        ResetColors ();
        return TRUE;
    }
    if (m_rcArea[eSwapButtonArea].PtInRect (ptClick))
    {
        SwapColors ();
        return TRUE;
    }
    return TRUE;
}
//*******************************************************************************
