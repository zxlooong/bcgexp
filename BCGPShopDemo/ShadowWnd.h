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

class CShadowWnd : public CWnd
{
    DECLARE_DYNAMIC (CShadowWnd);
protected:
    BYTE  m_cAlpha;
    CRect m_rcSides;
    UINT  m_uRadius;
    CWnd* m_pHostWindow;
    COLORREF m_clrShadowInner;
    COLORREF m_clrShadowOuter;
    BOOL  m_bAlphaSupported;
public:
    CShadowWnd ();
    virtual ~CShadowWnd ();

    BOOL Create (CWnd* pHostWindow);

    void TrackHostWindow (BOOL bEnableShadow);

    void SetShadowColor (COLORREF clrInner, COLORREF clrOuter, BYTE alpha = 64);
    void SetShadowDimensions (const RECT& rcSides, UINT uCornerRadius = 0);

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    //{{AFX_MSG(CShadowWnd)
    afx_msg  int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()


};