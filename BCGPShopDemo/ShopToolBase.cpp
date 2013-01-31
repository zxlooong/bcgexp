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
#include "ShopToolBase.h"
#include "TabbedBar.h"
#include "MainFrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShopToolBase

IMPLEMENT_DYNAMIC(CShopToolBase, CBCGPDockingControlBar)

CShopToolBase::CShopToolBase()
    : m_bCloseHilited (FALSE), m_clrBackground (RGB(237, 237, 237))
{
    m_pMiniFrameRTC = RUNTIME_CLASS (CTabbedMiniFrame);
}

CShopToolBase::~CShopToolBase()
{
}

CBCGPMiniFrameWnd* CShopToolBase::CreateDefaultMiniframe (CRect rectInitial)
{
    m_pMiniFrameRTC = RUNTIME_CLASS (CTabbedMiniFrame);
    return CBCGPDockingControlBar::CreateDefaultMiniframe (rectInitial);
}

void CShopToolBase::SetBackColor(COLORREF color)
{
    m_clrBackground = color;
    Invalidate ();
}


BEGIN_MESSAGE_MAP(CShopToolBase, CBCGPDockingControlBar)
    //{{AFX_MSG_MAP(CShopToolBase)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_NCLBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_NCCALCSIZE()
    ON_WM_NCPAINT()
    ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CShopToolBase::Create(LPCTSTR lpszCaption, 
                           CWnd* pParentWnd, 
                           const RECT& rect, 
                           BOOL bHasGripper, 
                           UINT nID, 
                           DWORD dwStyle, 
                           DWORD dwTabbedStyle,
                           DWORD dwBCGStyle,
                           CCreateContext* pContext)
{
	return CreateEx (0, lpszCaption, pParentWnd, rect, 
					 bHasGripper, nID, dwStyle, dwTabbedStyle, 
					 dwBCGStyle, pContext
                     );
}


BOOL CShopToolBase::Create(LPCTSTR lpszWindowName, 
                           CWnd* pParentWnd,
                           CSize sizeDefault, 
                           BOOL bHasGripper,
                           UINT nID, 
                           DWORD dwStyle, 
                           DWORD dwTabbedStyle, 
                           DWORD dwBCGStyle)
{
	CRect rect (0, 0, sizeDefault.cx, sizeDefault.cy);
	return CreateEx (0, lpszWindowName, pParentWnd, rect, 
                     bHasGripper, nID, dwStyle, dwTabbedStyle, 
                     dwBCGStyle, NULL);
}

BOOL CShopToolBase::CreateEx ( DWORD dwStyleEx, 
						       LPCTSTR lpszCaption, 
						       CWnd* pParentWnd, 
						       const RECT& rect, 
						       BOOL bHasGripper, 
						       UINT nID, 
						       DWORD dwStyle, 
						       DWORD dwTabbedStyle, 
						       DWORD dwBCGStyle,
						       CCreateContext* pContext)
{
    BOOL bResult = CBCGPDockingControlBar::CreateEx (
        dwStyleEx, lpszCaption, pParentWnd, rect, bHasGripper, nID,
        dwStyle, dwTabbedStyle, dwBCGStyle, pContext);

    SetTabbedControlBarRTC (RUNTIME_CLASS (CTabbedBar));

    RemoveCaptionButtons ();
    return bResult;
}

int CShopToolBase::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CBCGPDockingControlBar::OnCreate (lpCreateStruct) == -1)
    {
        return -1;
    }
    if (m_hFont.GetSafeHandle() == NULL)
    {
        m_hFont.CreatePointFont (70, _T("Arial"));
    }
    DoCreate (); // overridable
    SetTimer (1, 50, NULL); // 1/20 sec. timer
    return 0;	
}

void CShopToolBase::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1)
    {
        CPoint ptMouse;
        ::GetCursorPos (&ptMouse);
        DoUpdateOnTimer (ptMouse);

        // Check if mouse is over Tab Close button

        CRect rcWindow;
        GetWindowRect (&rcWindow);
        ptMouse.x -= rcWindow.left;
        ptMouse.y -= rcWindow.top;

        if (m_HeaderLayout.HitTest (ptMouse) == HTCLOSE)
        {
            if (!m_bCloseHilited)
            {
                CWindowDC dc (this);
                m_HeaderLayout.DrawTabCloseButton (&dc, TRUE, FALSE);
                m_bCloseHilited = TRUE;
            }
        }
        else
        {
            if (m_bCloseHilited)
            {
                CWindowDC dc(this);
                m_HeaderLayout.DrawTabCloseButton (&dc, FALSE, FALSE);
                m_bCloseHilited = FALSE;
            }
        }
    }
} 

void CShopToolBase::OnSize(UINT nType, int cx, int cy) 
{
    CBCGPDockingControlBar::OnSize (nType, cx, cy);

    if (CanAdjustLayout ())
    {
        DoResize (cx, cy); // overridable
    }

    CString sCaption;
    GetWindowText (sCaption);
    CRect rcWindow;
    GetWindowRect (&rcWindow);
    rcWindow.OffsetRect (-rcWindow.left, -rcWindow.top);
    m_HeaderLayout.Update (rcWindow, sCaption);

    CWnd* pParent = GetParent ();
    if (pParent != NULL && pParent->IsKindOf (RUNTIME_CLASS (CBCGPTabWnd)))
    {
        m_HeaderLayout.Reset ();
    }
    Invalidate ();
}

void CShopToolBase::OnAfterDock  (CBCGPBaseControlBar* pBar, LPCRECT lpRect, BCGP_DOCK_METHOD dockMethod)
{
    CRect rcClient;
    GetClientRect (&rcClient);
    OnSize (SIZE_RESTORED, rcClient.Width (), rcClient.Height ());
    CBCGPDockingControlBar::OnAfterDock (pBar, lpRect, dockMethod);
}

BOOL CShopToolBase::OnBeforeFloat (CRect& rectFloat, BCGP_DOCK_METHOD dockMethod)
{
    CRect rcClient;
    GetClientRect (&rcClient);
    OnSize (SIZE_RESTORED, rcClient.Width (), rcClient.Height ());
    return CBCGPDockingControlBar::OnBeforeFloat (rectFloat, dockMethod);
}

void CShopToolBase::DoCreate ()
{
}
void CShopToolBase::DoResize (int, int)
{
}
BOOL CShopToolBase::DoMouseDown (UINT, const CPoint&)
{
    return FALSE; // not processed
}
BOOL CShopToolBase::DoMouseMove (UINT, const CPoint&)
{
    return FALSE; // not processed
}
BOOL CShopToolBase::DoMouseUp (UINT, const CPoint&)
{
    return FALSE; // not processed
}
void CShopToolBase::DoUpdateOnTimer (const CPoint&)
{
}


// Default painting
void CShopToolBase::DoPaint(CDC& dc)
{
    CRect rcDraw;
    GetClientRect (rcDraw);
    dc.FillSolidRect (rcDraw, m_clrBackground);
}

void CShopToolBase::OnPaint() 
{
    CPaintDC dc (this); // device context for painting
    CFont* pOldFont = dc.SelectObject (&m_hFont);
    DoPaint (dc); // overridable
    dc.SelectObject (pOldFont);
}

void CShopToolBase::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (DoMouseDown (nFlags, point))
    {
        return;
    }
    CBCGPDockingControlBar::OnLButtonDown (nFlags, point);
}
void CShopToolBase::OnMouseMove(UINT nFlags, CPoint point)
{
    if (DoMouseMove (nFlags, point))
    {
        return;
    }
    CBCGPDockingControlBar::OnMouseMove (nFlags, point);
}
void CShopToolBase::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (DoMouseUp (nFlags, point))
    {
        return;
    }
    CBCGPDockingControlBar::OnLButtonUp (nFlags, point);
}

int CShopToolBase::GetCaptionHeight () const
{
    CBCGPTabWnd* pTab = DYNAMIC_DOWNCAST (CBCGPTabWnd, GetParent ());
    if (pTab == NULL)
    {
        return m_HeaderLayout.GetTabCaptionHeight ();
    }
    return 0;
}

void CShopToolBase::DrawCaption (CDC* pDC, CRect /*rectCaption*/)
{
    m_HeaderLayout.Paint (pDC, this);
}

int CShopToolBase::HitTest (CPoint point, BOOL bDetectCaption)
{
    CRect rcWindow;
    GetWindowRect (&rcWindow);
    point.Offset(-rcWindow.left, -rcWindow.top);

    int ht = m_HeaderLayout.HitTest (point);
    if (ht == HTCAPTION && !bDetectCaption)
        ht = HTCLIENT;
    return ht;

    ASSERT_VALID (this);
    CRect rectWnd;
    GetWindowRect (&rectWnd);

    if (!rectWnd.PtInRect (point))
    {
        return HTNOWHERE;
    }

    CRect rectClient;
    GetClientRect (&rectClient);
    ClientToScreen (&rectClient);

    if (rectClient.PtInRect (point))
    {
        return HTCLIENT;
    }

    return bDetectCaption ? HTCAPTION : HTCLIENT;
}


void CShopToolBase::OnNcLButtonDown (UINT nFlags, CPoint point)
{
    CRect rcWindow;
    GetWindowRect (&rcWindow);
    point.x -= rcWindow.left;
    point.y -= rcWindow.top;
    
    int cHit = m_HeaderLayout.HitTest (point);

    if (cHit == HTCAPTION || cHit == HTCLIENT)
    {
        CBCGPMiniFrameWnd* pParentMiniFrame = DYNAMIC_DOWNCAST (CBCGPMiniFrameWnd, GetParent ());
        if (pParentMiniFrame != NULL)
            pParentMiniFrame->SendMessage (WM_NCLBUTTONDOWN, nFlags, MAKELPARAM (point.x, point.y));
    }
    else if (cHit != HTCLOSE)
    {
        CBCGPDockingControlBar::OnNcLButtonDown (nFlags, point);
    }
}

void CShopToolBase::OnNcLButtonUp(UINT /*nFlags*/, CPoint point)
{
    CRect rcWindow;
    GetWindowRect (&rcWindow);
    point.x -= rcWindow.left;
    point.y -= rcWindow.top;

    int cHit = m_HeaderLayout.HitTest (point);

    if (cHit == HTCLOSE)
    {
        OnPressCloseButton ();
        return;
    }

    if (cHit == HTSYSMENU)
    {
        OnShowContextMenu ();
    }
}

UINT CShopToolBase::OnShowContextMenu ()
{
    POINT point;
    ::GetCursorPos (&point);

    CMenu menu;
    menu.CreatePopupMenu ();
    menu.AppendMenu (MF_STRING, ID_TOOLBUTTON_MAX, _T("&Place context menu items here"));
    menu.AppendMenu (MF_SEPARATOR, 0, (LPCTSTR)NULL);
    menu.AppendMenu (MF_STRING, ID_TOOLBUTTON_MAX, _T("Item &1"));
    menu.AppendMenu (MF_STRING, ID_TOOLBUTTON_MAX, _T("Item &2"));
    menu.AppendMenu (MF_STRING, ID_TOOLBUTTON_MAX, _T("Item &3"));

    CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
    pPopupMenu->Create (this, point.x, point.y, menu.Detach ());
    return 0;
}

void CShopToolBase::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CWnd::OnLButtonDblClk(nFlags, point); // suppress double-click behavior (auto-dock)
}

void CShopToolBase::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
    ASSERT_VALID (this);
    CBCGPControlBar::OnNcCalcSize(bCalcValidRects, lpncsp);

    int cyCaption = GetCaptionHeight ();
    if (cyCaption > 0)
    {
        CRect rcClient = lpncsp->rgrc[0];
        rcClient.DeflateRect (0, cyCaption - 1, 0, 0);
        lpncsp->rgrc[0] = rcClient;
    }
}

void CShopToolBase::OnNcPaint() 
{
    if (m_bMultiThreaded)
    {
        g_cs.Lock ();
    }

    ASSERT_VALID (this);

    // get window DC that is clipped to the non-client area
    CWindowDC dcPaint (this);

    CRect rectUpd;
    GetUpdateRect (rectUpd);

    CRect rcClient, rcBar;
    GetClientRect (rcClient);
    ClientToScreen (rcClient);
    GetWindowRect (rcBar);

    rcClient.OffsetRect (-rcBar.TopLeft ());
    rcBar.OffsetRect (-rcBar.TopLeft ());

    dcPaint.ExcludeClipRect (rcClient);

    if (!rcBar.IsRectEmpty ())
    {
        // erase parts not drawn
        dcPaint.IntersectClipRect (rcBar);
        CBCGPMemDC memDC (dcPaint, rcBar);
        memDC.GetDC ().FillSolidRect (rcBar, globalData.clrBarFace);

        m_HeaderLayout.Paint (&memDC.GetDC (), this);
    }
    
    if (m_bMultiThreaded)
    {
        g_cs.Unlock ();
    }
}

void CShopToolBase::OnClose() 
{
	OnPressCloseButton ();
}
