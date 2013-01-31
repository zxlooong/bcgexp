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

class CPaletteMiniFrame : public CBCGPMiniFrameWnd
{
    DECLARE_SERIAL(CPaletteMiniFrame)
    DECLARE_MESSAGE_MAP()

public:
    CPaletteMiniFrame() : CBCGPMiniFrameWnd() 
    {
        RecalcCaptionHeight ();
    }
    virtual ~CPaletteMiniFrame() {}

public:
    virtual void CalcBorderSize (CRect& rectBorderSize) const
    {
        rectBorderSize.SetRectEmpty ();
    }

    virtual void RecalcCaptionHeight ()
    {
        m_nCaptionHeight = 8 + CBCGPVisualManager::GetInstance ()->GetCaptionButtonExtraBorder ().cy;
        m_sizeMinSize.cx = m_sizeMinSize.cy = m_nCaptionHeight + 15;
    }

    virtual void GetResizeButtonRect(CRect& rect);

    virtual void OnCapture (BOOL bOnOff);

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
    CShadowWnd m_wndShadow;

protected:
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnDestroy();
};
