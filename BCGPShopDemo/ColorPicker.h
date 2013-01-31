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
#include <BCGPToolbarButton.h>
#include "SharedBitmap.h"

class CShopToolbarColorPicker : public CBCGPToolbarButton  
{
    DECLARE_SERIAL(CShopToolbarColorPicker)

public:
    CShopToolbarColorPicker ();
    CShopToolbarColorPicker (UINT uiID);

protected:
    virtual void Serialize (CArchive& ar);
    virtual void CopyFrom (const CBCGPToolbarButton& src);

    virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
    virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages,
        BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight,
        BOOL bDrawBorder, BOOL bGrayDisabledButtons
        );
    virtual BOOL OnClick (CWnd* pWnd, BOOL bDelay);

    void OnChangeParentWnd (CWnd* pWndParent)
    {
        CBCGPToolbarButton::OnChangeParentWnd (pWndParent);
    }

public:
    COLORREF GetLeftColor() const
    {
        return m_clrLeft;
    }

    COLORREF GetRightColor() const
    {
        return m_clrLeft;
    }

    void SetLeftColor (COLORREF color);
    void SetRightColor (COLORREF color);
    void SwapColors ();
    void ResetColors ();

    void SetMiniButtonImages(UINT uiResourceID);
    void SetCompactLayout(BOOL bCompact);

protected:
    COLORREF m_clrLeft;
    COLORREF m_clrRight;
    CSharedBitmap m_imgMinibuttons;
    BOOL m_bCompactLayout;
    CRect m_rcArea[4];

    enum
    {
        eLeftColorArea,
        eRightColorArea,
        eSwapButtonArea,
        eResetButtonArea
    };

};