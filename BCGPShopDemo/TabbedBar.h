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

#include "ShadowWnd.h"

// CTabbedBar

class CTabbedBar : public CBCGPTabbedControlBar
{
    DECLARE_SERIAL(CTabbedBar)

public:
    CTabbedBar();
    virtual ~CTabbedBar();

// Override
public:
    virtual int GetCaptionHeight () const
    {
        return 0;
    }

    virtual void DrawCaption (CDC* /*pDC*/, CRect /*rectCaption*/)
    {
    }

    virtual BCGP_DOCK_TYPE GetDockMode () const
    {
        return BCGP_DT_IMMEDIATE;
    }

protected:

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()
};



class CTabbedMiniFrame : public CBCGPMultiMiniFrameWnd
{
    DECLARE_SERIAL(CTabbedMiniFrame)
    DECLARE_MESSAGE_MAP()

protected:
    CShadowWnd m_wndShadow;

public:
    CTabbedMiniFrame() : CBCGPMultiMiniFrameWnd() 
    {
        RecalcCaptionHeight ();
    }
    virtual ~CTabbedMiniFrame() {}

public:
    virtual void RecalcCaptionHeight ();

    virtual void CalcBorderSize (CRect& rectBorderSize) const;


    virtual void OnCapture (BOOL bOnOff)
    {
        if (globalData.IsWindowsLayerSupportAvailable () && 
            globalData.m_nBitsPerPixel > 8)
        {
            if (bOnOff) // begin drag
            {
                ModifyStyleEx (0, WS_EX_LAYERED);
                globalData.SetLayeredAttrib (GetSafeHwnd (), 0, 127, LWA_ALPHA);
            }
            else // end drag
            {
                globalData.SetLayeredAttrib (GetSafeHwnd (), 0, 255, LWA_ALPHA);
                ModifyStyleEx (WS_EX_LAYERED, 0); //remove WS_EX_LAYERED style
            }
        }
        CBCGPMiniFrameWnd::OnCapture (bOnOff);
    }

    virtual CString GetCaptionText ()
    {
        return CString(); //never draw caption text
    }

    virtual void OnDrawCaptionButtons (CDC* pDC);
    virtual BCGNcHitTestType HitTest (CPoint point, BOOL bDetectCaption);

    virtual BCGP_DOCK_TYPE GetDockMode () const
    {
        return BCGP_DT_IMMEDIATE;
    }


protected:
    CBCGPControlRenderer m_imgCaptionButton;

    CBCGPBaseTabWnd* GetTabWnd() const
    {
        CBCGPBaseTabWnd* pTabWnd = DYNAMIC_DOWNCAST (CBCGPBaseTabWnd,
            CWnd::FromHandlePermanent (m_hEmbeddedBar));
        return pTabWnd;
    }

    virtual BOOL CanBeAttached () const 
    {
        BOOL result = CBCGPMiniFrameWnd::CanBeAttached();
        return result;
    }

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnDestroy();
};
