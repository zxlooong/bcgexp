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
// ShopTabWnd.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPShopDemo.h"
#include "ShopTabWnd.h"
#include "ShopToolBase.h"

// CShopTabWnd

IMPLEMENT_DYNCREATE (CShopTabWnd, CBCGPTabWnd)

//*******************************************************************************
CShopTabWnd::CShopTabWnd ()
    : m_nTabMenuSpace (25), m_bDisableDrawing (FALSE)
{
    m_bDrawFrame = FALSE;
	m_bFlat = TRUE;
}
//*******************************************************************************
CShopTabWnd::~CShopTabWnd ()
{
}
//*******************************************************************************
BEGIN_MESSAGE_MAP(CShopTabWnd, CBCGPTabWnd)
	//{{AFX_MSG_MAP(CShopTabWnd)
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//*******************************************************************************
void CShopTabWnd::RecalcLayout ()
{
    m_bDisableDrawing = TRUE;
    CBCGPTabWnd::RecalcLayout ();
    m_bDisableDrawing = FALSE;

    m_rectTabsArea.DeflateRect (2, 1, m_nTabMenuSpace, -1);

    int minTabWidth = 0;
    for (int i = 0; i < m_iTabsNum; i++)
    {
        CBCGPTabInfo* pTab = (CBCGPTabInfo*) m_arTabs [i];
        ASSERT_VALID (pTab);
        int width = pTab->GetRect ().Width ();
        if (minTabWidth == 0 || width < minTabWidth) minTabWidth = width;
    }
    m_bActiveTabCloseButton = (minTabWidth > 30);

    AdjustWndScroll ();
    AdjustTabs ();
    AdjustTabsScroll ();
    CRect rcUpdateArea;
    GetClientRect (&rcUpdateArea);

    if (m_location != LOCATION_BOTTOM)
    {
        rcUpdateArea.bottom = m_rectWndArea.bottom;
    }
    else
    {
        rcUpdateArea.top = m_rectWndArea.top;
    }

    InvalidateRect (rcUpdateArea);
    UpdateWindow ();
}
//*******************************************************************************
void CShopTabWnd::AdjustTabs ()
{
    if (!m_bDisableDrawing)
    {
        CBCGPTabWnd::AdjustTabs ();
    }
}
//*******************************************************************************
BOOL CShopTabWnd::IsPtInMenuArea (const CPoint& point) const
{
    if (m_location != LOCATION_TOP)
        return FALSE;
    CRect rcTabMenu;
    GetClientRect (rcTabMenu);
    rcTabMenu.top += 17;
    rcTabMenu.bottom = rcTabMenu.top + 7;
    rcTabMenu.right -= 2;
    rcTabMenu.left = rcTabMenu.right - 15;
    return rcTabMenu.PtInRect (point);
}

//*******************************************************************************
// CShopTabWnd message handlers
//*******************************************************************************

int CShopTabWnd::OnCreate (LPCREATESTRUCT lpCreateStruct) 
{
    ASSERT_VALID (this);
    if (CBCGPTabWnd::OnCreate (lpCreateStruct) == -1)
    {
        return -1;
    }

    EnableActiveTabCloseButton (TRUE);

    return 0;
}
//*******************************************************************************
void CShopTabWnd::OnLButtonDown (UINT nFlags, CPoint point)
{
    if (IsPtInMenuArea (point))
    {
        return;
    }
    if (GetTabFromPoint (point) < 0)
    {
        CBCGPTabbedControlBar* pParent = DYNAMIC_DOWNCAST(CBCGPTabbedControlBar, GetParent ());
        if (pParent)
        {
            pParent->SendMessage(WM_LBUTTONDOWN, (WPARAM)nFlags, MAKELPARAM (point.x, point.y));
            return;
        }
    }
    CBCGPTabWnd::OnLButtonDown(nFlags, point);
}
//*******************************************************************************
void CShopTabWnd::OnLButtonUp (UINT nFlags, CPoint point)
{
    if (IsPtInMenuArea (point))
    {
        CShopToolBase* pTool = DYNAMIC_DOWNCAST (CShopToolBase, GetActiveWnd ());
        if (pTool != NULL)
        {
            pTool->OnShowContextMenu ();
        }
        return;
    }
    CBCGPTabWnd::OnLButtonUp (nFlags, point);
}
//*******************************************************************************
void CShopTabWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    BOOL bTabCloseButtonPressed = m_bTabCloseButtonPressed;
    CBCGPTabWnd::OnMouseMove(nFlags, point);
    if (m_bTabCloseButtonHighlighted && (bTabCloseButtonPressed != m_bTabCloseButtonPressed))
    {
        m_bTabCloseButtonPressed = FALSE;
    }
}
//*******************************************************************************
void CShopTabWnd::OnLButtonDblClk (UINT nFlags, CPoint point)
{
    CWnd::OnLButtonDblClk (nFlags, point); // suppress CBCGPTabWnd double-click behavior
}
//*******************************************************************************

