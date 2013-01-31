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

class CShopVisualManager;

/////////////////////////////////////////////////////////////////////////////
// CTabHeaderLayout

class CTabHeaderLayout : public CObject
{
    DECLARE_DYNCREATE (CTabHeaderLayout);
protected:
    CRect m_rcWindow;
    CRect m_rcTab;
    CRect m_rcTabCloseBtn;
    CRect m_rcMenu;
    CRect m_rcCloseBtn;
    int   m_cyCaption;
    bool  m_bShowTab;
public:
    CTabHeaderLayout ();
    virtual ~CTabHeaderLayout ();

    int  GetTabCaptionHeight () const;
    void Paint(CDC* pDC, CWnd* pContentWnd);
    void DrawTabCloseButton (CDC* pDC, BOOL bHighlighted, BOOL bPressed);

    void Update (const CRect& rcWindow, const CString& caption);
    void Reset ();
    int  HitTest (const CPoint& point);

protected:
    CShopVisualManager* GetVisualManager() const;
};
