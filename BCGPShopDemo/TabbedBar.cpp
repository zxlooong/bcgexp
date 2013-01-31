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
// ShopTabbedBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPShopDemo.h"
#include "TabbedBar.h"
#include "ShopToolBase.h"
#include "ShopTabWnd.h"
#include "PaletteMiniFrame.h"
#include "VisualManager.h"


// CTabbedBar

IMPLEMENT_SERIAL(CTabbedBar, CBCGPTabbedControlBar, 1)

//*******************************************************************************
CTabbedBar::CTabbedBar()
{
    CBCGPTabbedControlBar::m_bTabsAlwaysTop = true;
    CBCGPTabbedControlBar::m_pTabWndRTC = RUNTIME_CLASS (CShopTabWnd);
}
//*******************************************************************************
CTabbedBar::~CTabbedBar()
{
}
//*******************************************************************************

BEGIN_MESSAGE_MAP(CTabbedBar, CBCGPTabbedControlBar)
	//{{AFX_MSG_MAP(CTabbedBar)
    ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*******************************************************************************
// CTabbedBar message handlers

int CTabbedBar::OnCreate (LPCREATESTRUCT lpCreateStruct) 
{
	ASSERT_VALID (this);
	if (CBCGPTabbedControlBar::OnCreate (lpCreateStruct) == -1)
		return -1;
    CBCGPTabWnd* pTab = DYNAMIC_DOWNCAST (CBCGPTabWnd, GetUnderlinedWindow ());
    if (pTab)
    {
        pTab->HideSingleTab(FALSE);
    }
    
    m_pMiniFrameRTC = RUNTIME_CLASS (CTabbedMiniFrame);

    RemoveCaptionButtons ();

    return 0;
}
//*******************************************************************************


// CTabbedMiniFrame

IMPLEMENT_SERIAL(CTabbedMiniFrame, CBCGPMultiMiniFrameWnd, 1)

BEGIN_MESSAGE_MAP(CTabbedMiniFrame, CBCGPMultiMiniFrameWnd)
    ON_WM_CREATE()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_SHOWWINDOW()
    ON_WM_DESTROY()
END_MESSAGE_MAP()

//*******************************************************************************
int CTabbedMiniFrame::OnCreate (LPCREATESTRUCT lpCS)
{
    int result = CBCGPMultiMiniFrameWnd::OnCreate (lpCS);
    RemoveAllCaptionButtons ();

    m_wndShadow.Create (this);
    m_wndShadow.SetShadowDimensions (CRect (2, 0, 3, 8), 6);

    return result;
}
//*******************************************************************************
void CTabbedMiniFrame::RecalcCaptionHeight ()
{
    m_nCaptionHeight = 0;
    m_sizeMinSize.cx = 25;
    m_sizeMinSize.cy = m_nCaptionHeight + 15;
}
//*******************************************************************************
void CTabbedMiniFrame::CalcBorderSize (CRect& rectBorderSize) const
{
    rectBorderSize.SetRectEmpty(); // remove any borders
}
//*******************************************************************************
void CTabbedMiniFrame::OnDrawCaptionButtons (CDC* /*pDC*/)
{
	// Do not draw anything
}
//*******************************************************************************
void CTabbedMiniFrame::OnLButtonUp (UINT nFlags, CPoint point)
{
    CPoint ptScreen = point;
    ClientToScreen (&ptScreen);
    if (HitTest (ptScreen, TRUE) == HTCAPTION)
    {
        // TODO: add your code to process caption click
    }
    CBCGPMultiMiniFrameWnd::OnLButtonUp (nFlags, point);
}
//*******************************************************************************
// Disable dock/undock on double-click
void CTabbedMiniFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CWnd::OnLButtonDblClk (nFlags, point);
}
//*******************************************************************************
// Ignore all standard caption buttons and resize area.
BCGNcHitTestType CTabbedMiniFrame::HitTest (CPoint point, BOOL bDetectCaption)
{
    BCGNcHitTestType htInfo = CBCGPMultiMiniFrameWnd::HitTest (point, bDetectCaption);
    switch (htInfo)
    {
    case HTLEFT:
    case HTRIGHT:       case HTTOP:
    case HTTOPLEFT:     case HTTOPRIGHT:
    case HTBOTTOM:      case HTBOTTOMLEFT:
    case HTBOTTOMRIGHT:
        htInfo = HTCAPTION;
    }
    return htInfo;
}
//*******************************************************************************
void CTabbedMiniFrame::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
    m_wndShadow.TrackHostWindow (TRUE);
    CBCGPMultiMiniFrameWnd::OnWindowPosChanged(lpwndpos);
}
//*******************************************************************************
void CTabbedMiniFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
    m_wndShadow.TrackHostWindow (bShow);
	CBCGPMultiMiniFrameWnd::OnShowWindow (bShow, nStatus);
}
//*******************************************************************************
void CTabbedMiniFrame::OnDestroy()
{   
    m_wndShadow.DestroyWindow ();
    CBCGPMultiMiniFrameWnd::OnDestroy ();
}
//*******************************************************************************
