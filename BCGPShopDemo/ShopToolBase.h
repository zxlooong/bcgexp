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

#pragma once

#include "TabHeaderLayout.h"

/////////////////////////////////////////////////////////////////////////////
// CShopToolBase

class CShopToolBase : public CBCGPDockingControlBar
{
    DECLARE_DYNAMIC(CShopToolBase)

protected:
    CTabHeaderLayout m_HeaderLayout;
    BOOL m_bCloseHilited;
    CFont m_hFont;

// Construction
public:
    CShopToolBase();

// Implementation
public:
    virtual ~CShopToolBase();

    COLORREF GetBackColor() const
    {
        return m_clrBackground;
    }

    void SetBackColor(COLORREF color);

// Override
public:
	virtual BOOL Create(
        LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle, 
        DWORD dwTabbedStyle = CBRS_BCGP_REGULAR_TABS,
        DWORD dwBCGStyle = dwDefaultBCGDockingBarStyle,
        CCreateContext* pContext = NULL
        );
    virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CSize sizeDefault, BOOL bHasGripper, UINT nID,
        DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_HIDE_INPLACE, 
		DWORD dwTabbedStyle = CBRS_BCGP_REGULAR_TABS,
		DWORD dwBCGStyle = dwDefaultBCGDockingBarStyle
        );

    virtual BOOL CreateEx(DWORD dwStyleEx, LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, BOOL bHasGripper, UINT nID, DWORD dwStyle,
        DWORD dwTabbedStyle = CBRS_BCGP_REGULAR_TABS,
        DWORD dwBCGStyle = dwDefaultBCGDockingBarStyle,
        CCreateContext* pContext = NULL
        );

    virtual CBCGPMiniFrameWnd* CreateDefaultMiniframe (CRect rectInitial);

    virtual BCGP_DOCK_TYPE GetDockMode () const
    {
        return BCGP_DT_IMMEDIATE;
    }
    virtual int GetCaptionHeight () const;

    virtual void DrawCaption (CDC* pDC, CRect rectCaption);
    virtual int HitTest (CPoint point, BOOL bDetectCaption);

    virtual void OnAfterDock  (CBCGPBaseControlBar* pBar, LPCRECT lpRect, BCGP_DOCK_METHOD dockMethod);
    virtual BOOL OnBeforeFloat (CRect& rectFloat, BCGP_DOCK_METHOD dockMethod);


// Overridables
public:
    virtual UINT OnShowContextMenu();

protected:

    virtual void DoCreate ();
    virtual void DoResize (int cx, int cy);
    virtual BOOL DoMouseDown (UINT nFlags, const CPoint& mousePos);
    virtual BOOL DoMouseMove (UINT nFlags, const CPoint& mousePos);
    virtual BOOL DoMouseUp (UINT nFlags, const CPoint& mousePos);
    virtual void DoUpdateOnTimer (const CPoint& screenMousePos);
    virtual void DoPaint (CDC& dc);


// Generated message map functions
protected:
    //{{AFX_MSG(CShopToolBase)
    afx_msg  int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg void OnNcPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    COLORREF m_clrBackground;
};
