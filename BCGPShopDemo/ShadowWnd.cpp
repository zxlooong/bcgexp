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
#include "ShadowWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CShadowWnd

IMPLEMENT_DYNAMIC(CShadowWnd, CWnd)

BEGIN_MESSAGE_MAP(CShadowWnd, CWnd)
	//{{AFX_MSG_MAP(CShadowWnd)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*******************************************************************************
CShadowWnd::CShadowWnd ()
    :  m_cAlpha (64), m_rcSides (2, 2, 2, 5), m_uRadius (4), m_pHostWindow (NULL),
       m_clrShadowInner (0x000000), m_clrShadowOuter (0xA0A0A0),
       m_bAlphaSupported (FALSE)
{
}
//*******************************************************************************
CShadowWnd::~CShadowWnd ()
{
}
//*******************************************************************************
void CShadowWnd::SetShadowColor (COLORREF clrInner, COLORREF clrOuter, BYTE alpha)
{
    m_clrShadowInner = clrInner;
    m_clrShadowOuter = clrOuter;
    m_cAlpha = alpha;
    Invalidate ();
}
//*******************************************************************************
void CShadowWnd::SetShadowDimensions (const RECT& rcSides, UINT uCornerRadius)
{
    m_rcSides.CopyRect (&rcSides);
    m_uRadius = uCornerRadius;
    Invalidate ();
}
//*******************************************************************************
BOOL CShadowWnd::Create (CWnd* pHostWindow)
{
    m_pHostWindow = pHostWindow;
    if (pHostWindow == NULL)
    {
        return FALSE;
    }
    ASSERT_VALID (pHostWindow);
    
    CRect rcHostWindow;
    pHostWindow->GetWindowRect (&rcHostWindow);
    rcHostWindow.InflateRect (&m_rcSides);

    CWnd* pHostOwner = pHostWindow->GetWindow (GW_OWNER);

    if (!CWnd::CreateEx (WS_EX_TRANSPARENT, 
        globalData.RegisterWindowClass (_T("BCGPShadowWnd")), NULL,
        WS_POPUP | WS_VISIBLE, rcHostWindow, pHostOwner, 0, NULL))
    {
        return FALSE;
    }

    return TRUE;
}
//*******************************************************************************
BOOL CShadowWnd::PreCreateWindow (CREATESTRUCT& cs)
{
    cs.dwExStyle = WS_EX_TRANSPARENT | WS_EX_LAYERED;
    cs.style = WS_POPUP | WS_VISIBLE;
    return CWnd::PreCreateWindow (cs);
}
//*******************************************************************************
int CShadowWnd::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
    m_bAlphaSupported = globalData.IsWindowsLayerSupportAvailable () && globalData.m_nBitsPerPixel > 8;
    if (m_bAlphaSupported)
    {
        lpCreateStruct->dwExStyle |= WS_EX_LAYERED;
        globalData.SetLayeredAttrib (m_hWnd, RGB (255, 255, 255), m_cAlpha, LWA_ALPHA | LWA_COLORKEY);
    }
    else
    {
        lpCreateStruct->style &= (~WS_VISIBLE);
    }
    return CWnd::OnCreate (lpCreateStruct);
}
//*******************************************************************************
BOOL CShadowWnd::OnEraseBkgnd (CDC*)
{
    return TRUE;
}
//*******************************************************************************
void CShadowWnd::OnPaint ()
{
    if (!m_bAlphaSupported)
    {
        return;
    }

    CPaintDC paintDc (this); // device context for painting
    CBCGPMemDC memDC (paintDc, this);
    CDC& dc = memDC.GetDC ();
    COLORREF gray1 = m_clrShadowOuter, gray2 = m_clrShadowInner;
    COLORREF clTransparent = RGB (255, 255, 255);

    CRect rcShadow;
    GetClientRect (&rcShadow);

    // Paint background white (white is transparent)
    dc.FillSolidRect (rcShadow, clTransparent);

    int cShadowSize = max (m_rcSides.left, max (m_rcSides.top, max (m_rcSides.right, m_rcSides.bottom)));

    CPoint ptRound (m_uRadius * 2, m_uRadius * 2);
    CBrush brWhite (clTransparent);
    CBrush* pOldBrush = dc.SelectObject (&brWhite);
    CPen* pOldPen = dc.GetCurrentPen ();
    for (int i = 0; i < cShadowSize; ++i)
    {
        BYTE r = (BYTE)(GetRValue (gray1) + (GetRValue (gray2) - GetRValue (gray1)) * i / cShadowSize);
        BYTE g = (BYTE)(GetGValue (gray1) + (GetGValue (gray2) - GetGValue (gray1)) * i / cShadowSize);
        BYTE b = (BYTE)(GetBValue (gray1) + (GetBValue (gray2) - GetBValue (gray1)) * i / cShadowSize);
        CPen pen (PS_SOLID, 2, RGB (r, g, b));
        dc.SelectObject (&pen);
        if (rcShadow.IsRectEmpty ())
        {
            break;
        }

        if (ptRound.x * ptRound.y > 0)
        {
            dc.RoundRect (&rcShadow, ptRound);
        }
        else
        {
            dc.Rectangle (&rcShadow);
        }

        rcShadow.DeflateRect (1, 1, 1, 1);
    }

    dc.SelectObject (pOldPen);
    dc.SelectObject (pOldBrush);

    if (m_pHostWindow->GetSafeHwnd () != NULL )
    {
        CRect rcHost;
        m_pHostWindow->GetWindowRect (&rcHost);

        CRgn rgnHost;
        rgnHost.CreateRectRgn (0, 0, 0, 0);
        int rgnType = m_pHostWindow->GetWindowRgn (rgnHost);
        if (rgnType != RGN_ERROR)
        {
            rgnHost.OffsetRgn (-rcHost.left + m_rcSides.left, -rcHost.top + m_rcSides.top);
            dc.SelectClipRgn (&rgnHost);

            CRect rcClip;
            dc.GetClipBox (&rcClip);

            dc.FillSolidRect (rcClip, clTransparent);
            rgnHost.DeleteObject ();
        }
        else
        {
            rcHost.OffsetRect (-rcHost.left + m_rcSides.left, -rcHost.top + m_rcSides.top);
            dc.FillSolidRect (rcHost, clTransparent);
        }
    }
}
//*******************************************************************************
void CShadowWnd::TrackHostWindow (BOOL bEnableShadow)
{
    if (!m_bAlphaSupported || !bEnableShadow || m_pHostWindow == NULL || !m_pHostWindow->IsWindowVisible ())
    {
        ShowWindow (SW_HIDE);
    }
    else
    {
        CRect rcHostWindow;
        m_pHostWindow->GetWindowRect (&rcHostWindow);
        rcHostWindow.InflateRect (&m_rcSides);
        SetWindowPos (m_pHostWindow,
            rcHostWindow.left, rcHostWindow.top, rcHostWindow. Width(), rcHostWindow.Height (),
            SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_SHOWWINDOW);
    }
}
//*******************************************************************************
