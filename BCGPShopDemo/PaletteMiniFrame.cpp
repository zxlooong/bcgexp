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
#include "PaletteMiniFrame.h"
#include "Palette.h"
#include "resource.h"
#include "ColorPicker.h"

// MiniFrame

IMPLEMENT_SERIAL(CPaletteMiniFrame, CBCGPMiniFrameWnd, 1)

BEGIN_MESSAGE_MAP(CPaletteMiniFrame, CBCGPMiniFrameWnd)
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_SHOWWINDOW()
    ON_WM_DESTROY()
END_MESSAGE_MAP()

int CPaletteMiniFrame::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
    CBCGPControlRendererParams crp;
    crp.m_uiBmpResID = IDB_MINIFRAMERESIZE;
    crp.m_rectImage.SetRect (0, 0, 7, 6);
    crp.m_clrTransparent = 0xFFFFFF; // White
    m_imgCaptionButton.Create(crp);

    m_wndShadow.Create (this);

    return CBCGPMiniFrameWnd::OnCreate (lpCreateStruct);
}

void CPaletteMiniFrame::OnCapture (BOOL bOnOff)
{
    if (globalData.IsWindowsLayerSupportAvailable () && globalData.m_nBitsPerPixel > 8)
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

void CPaletteMiniFrame::GetResizeButtonRect (CRect& rect)
{
    rect = m_imgCaptionButton.GetParams ().m_rectImage;
    rect.OffsetRect (3, 2);
}

void CPaletteMiniFrame::OnDrawCaptionButtons (CDC* pDC)
{
    CRect rectWindow;
    GetWindowRect (rectWindow);
    ScreenToClient (rectWindow);

    CRect rcBtn;
    GetResizeButtonRect (rcBtn);
    m_imgCaptionButton.Draw (pDC, rcBtn);
}

void CPaletteMiniFrame::OnLButtonDown (UINT nFlags, CPoint point)
{
    CBCGPMiniFrameWnd::OnLButtonDown (nFlags, point);
}

void CPaletteMiniFrame::OnLButtonUp (UINT nFlags, CPoint point)
{
    CPoint ptScreen = point;
    ClientToScreen (&ptScreen);
    if (HitTest (ptScreen, TRUE) == HTCAPTION)
    {
        CRect rcResizeBtn;
        GetResizeButtonRect (rcResizeBtn);

        CRect rcWindow;
        GetWindowRect (rcWindow);
        ScreenToClient (rcWindow);
        rcResizeBtn.OffsetRect (rcWindow.left, rcWindow.top);

        if (rcResizeBtn.PtInRect (point))
        {
            CToolPalette* pBar = DYNAMIC_DOWNCAST (CToolPalette, CWnd::FromHandlePermanent (m_hEmbeddedBar));
            if (pBar)
            {
                int nColumns = pBar->GetColumns () + 1;
                if (nColumns > 3)
                {
                    nColumns = 1;
                }
                pBar->SetColumns (nColumns);
                int nPickerBtnIndex = pBar->CommandToIndex (ID_TOOLBUTTON_COLORPICKER);
                if (nPickerBtnIndex >= 0)
                {
                    CShopToolbarColorPicker* pPicker = DYNAMIC_DOWNCAST (CShopToolbarColorPicker, pBar->GetButton (nPickerBtnIndex));
                    if (pPicker != NULL)
                    {
                        pPicker->SetCompactLayout (nColumns == 1);
                    }
                }
            }
        }
    }
    CBCGPMiniFrameWnd::OnLButtonUp (nFlags, point);
}

// Disable dock/undock on double-click
void CPaletteMiniFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CWnd::OnLButtonDblClk (nFlags, point);
}

// Ignore all standard caption buttons and resize area.
BCGNcHitTestType CPaletteMiniFrame::HitTest (CPoint point, BOOL bDetectCaption)
{
    BCGNcHitTestType htInfo = CBCGPMiniFrameWnd::HitTest (point, bDetectCaption);

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

void CPaletteMiniFrame::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
    m_wndShadow.TrackHostWindow (TRUE);
    CBCGPMiniFrameWnd::OnWindowPosChanged(lpwndpos);
}

void CPaletteMiniFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
    m_wndShadow.TrackHostWindow (bShow);
    CBCGPMiniFrameWnd::OnShowWindow (bShow, nStatus);
}

void CPaletteMiniFrame::OnDestroy()
{   
    m_wndShadow.DestroyWindow ();
    CBCGPMiniFrameWnd::OnDestroy ();
}
