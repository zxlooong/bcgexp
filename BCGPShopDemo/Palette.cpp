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
// MainToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "Palette.h"
#include "PaletteMiniFrame.h"
#include "resource.h"


CToolPalette::CToolPalette()
    : m_nColumns(2)
    , m_nCheckedIndex(-1)
    , m_bAdditionalPixel(false)
    , m_nCaptionHeight(23)
{
    CBCGPControlRendererParams crp;
    crp.m_uiBmpResID = IDB_TOOLBARCAPTION;
    crp.m_rectImage.SetRect (0, 0, 46, 15);
    crp.m_rectCorners.SetRect (5, 10, 5, 4);
    m_imgCaption.Create (crp);
}

CToolPalette::~CToolPalette()
{
}


IMPLEMENT_SERIAL(CToolPalette, CBCGPToolBar, 1)

BEGIN_MESSAGE_MAP(CToolPalette, CBCGPToolBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()


// CToolPalette message handlers
//**********************************************************************************
int CToolPalette::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CBCGPToolBar::OnCreate (lpCreateStruct) == -1)
    {
        return -1;
    }

    m_pMiniFrameRTC = RUNTIME_CLASS (CPaletteMiniFrame);

    LOGFONT lf;
    memset(&lf, 0, sizeof(lf));
    lf.lfCharSet = DEFAULT_CHARSET;
    lstrcpy(lf.lfFaceName, _T("MS Trecbuchet"));
    lf.lfHeight = 120;
    lf.lfWeight = FW_HEAVY;
    lf.lfQuality = ANTIALIASED_QUALITY;
    m_fntTitle.CreatePointFontIndirect(&lf);
    return 0;	
}
//**********************************************************************************
CToolPalette::EDisplayOptions CToolPalette::GetToolbarDisplayOptions() const
{
    int x = 0;

    bool bHorizontal = (GetCurrentAlignment() & CBRS_ORIENT_HORZ) != 0;
    if (!bHorizontal)
    {
        CString title;
        GetWindowText (title);
        if (!title.IsEmpty ())
        {
            x |= eDisplayTitle;
        }

        if (IsDocked ())
        {
            x |= eDisplayBorder;
        }
    }
    return (EDisplayOptions)x;
    
}
//**********************************************************************************
void CToolPalette::OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*)
{
    // Do nothing (suppress parent class behavior).
}
//**********************************************************************************
void CToolPalette::DoPaint(CDC* pDC)
{
    CRect rcClient;
    GetClientRect(rcClient);

    CBCGPMemDC bufferDC(*pDC, rcClient);

    CBCGPToolBar::DoPaint (&bufferDC.GetDC());
    CBCGPDrawManager dm (bufferDC.GetDC());

    bool bHorizontal = (GetCurrentAlignment() & CBRS_ORIENT_HORZ) != 0; // Toolbar layout mode

    EDisplayOptions edo = GetToolbarDisplayOptions();

    if ((edo & eDisplaySizeControl) != 0 && !bHorizontal)
    {
        const int sizeControlHeight = m_imgCaption.GetParams().m_rectImage.Height(); 
        CRect rcSizeControl = rcClient;
        rcSizeControl.bottom = rcSizeControl.top + sizeControlHeight;
        m_imgCaption.Draw(pDC, rcSizeControl, 1); // 1 is the index of border image
        rcClient.top += sizeControlHeight;
    }

    if ((edo & eDisplayTitle) != 0)
    {
        CString title;
        GetWindowText (title);

        CRect rcTitle = rcClient;
        if ((edo & eDisplayBorder) != 0)
        {
            const CRect& rectCorners = m_imgCaption.GetParams().m_rectCorners;
            rcTitle.top += rectCorners.top;
        }
        rcTitle.top += 1;
        rcTitle.bottom = rcTitle.top + m_nCaptionHeight;
        dm.FillGradient2 (rcTitle, RGB(48, 112, 202), RGB(21, 57, 111), 305);
        rcTitle.DeflateRect (1, 2, 1, 2);

        CFont* pOldFont = bufferDC.GetDC().SelectObject(&m_fntTitle);
        bufferDC.GetDC().SetBkMode(TRANSPARENT);
        bufferDC.GetDC().SetTextColor(0xFFFFFF);
        bufferDC.GetDC().DrawText (title, rcTitle,
            DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE | DT_END_ELLIPSIS);
        bufferDC.GetDC().SelectObject (pOldFont);
    }

    if ((edo & eDisplayBorder) != 0)
    {
        m_imgCaption.DrawFrame (&bufferDC.GetDC(), rcClient, 0); // 0 is the index of border image
    }

}

//**********************************************************************************
void CToolPalette::OnFillBackground (CDC* pDC)
{
    CRect rcClip;
    pDC->GetClipBox(&rcClip);
    pDC->FillSolidRect(rcClip, 0xededed);
}
//**********************************************************************************
// Helper struct for CalcButtonLocations method
struct ButtonStripe
{
    int buttonCount; // count of visible buttons in a stripe
    int size; // width for horizontal stripes
    int breadth; // height for horizontal stripe

    ButtonStripe ()
        : buttonCount(0), size(0), breadth(0)
    {}
};

CSize CToolPalette::CalcButtonLocations(int nColumns, bool bCalcOnly)
{
    if (nColumns < 1)
    {
        nColumns = 1;
    }
    bool bHorizontal = (GetCurrentAlignment () & CBRS_ORIENT_HORZ) != 0; // Toolbar layout mode

    CRect rectClient;
    GetClientRect (rectClient);

    EDisplayOptions edo = GetToolbarDisplayOptions ();
    if ((edo & eDisplayTitle) != 0)
    {
        if (!bHorizontal)
        {
            rectClient.top += m_nCaptionHeight + 4;
        }
    }
    int xBorders = 0;
    int yBorders = 0;
    if ((edo & eDisplayBorder) != 0)
    {
        const CRect& rectCorners = m_imgCaption.GetParams ().m_rectCorners;
        rectClient.left += rectCorners.left + 3;
        rectClient.top += rectCorners.top;
        xBorders = rectCorners.left + rectCorners.right;
        yBorders = rectCorners.top + rectCorners.bottom;
    }
    else
    {
        rectClient.left += 1;
    }
    if ((edo & eDisplaySizeControl) != 0 && bHorizontal)
    {
        const int sizeControlHeight = m_imgCaption.GetParams ().m_rectImage.Height ();
        yBorders += sizeControlHeight;
        rectClient.top += sizeControlHeight;
    }

    // Consider border area

    CPoint xyPos = rectClient.TopLeft (); // Current position
    bool bPrevSeparator = true; // Indicates that previous button was a separator.
                                // Initial 'true' value prevents separator to appear first.
    CClientDC dc (this);
    CSize szButtonDefault (GetColumnWidth (), GetRowHeight ()); // Default button size to pass to button's OnCalculateSize method
    int nMaxSize = nColumns * (bHorizontal ? szButtonDefault.cy : szButtonDefault.cx) * 11 / 10; // (11/10) adds +10% space here
        // The toolbar height (for horizontal layout) or width (for vertical) of toolbar.

    CList<ButtonStripe, const ButtonStripe&> listStripes;

    ButtonStripe stripe; // Current stripe
    CBCGPToolbarButton* pButton = NULL; // Current button
    for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
    {
        pButton = (CBCGPToolbarButton*)m_Buttons.GetNext (pos);
        if (pButton == NULL)
        {
            break;
        }

        if (!pButton->IsVisible ())
        {
            continue;
        }

        bool bSep = (pButton->m_nStyle & TBBS_SEPARATOR) != 0;
        if (bSep && bPrevSeparator)
        {
            continue;
        }

        //  Layout algorithm:
        // -------------------
        // if (separator) AddPreviousStripe, AddSeparatorStripe, BeginNewStripe
        // else {
        //      AddButton
        //      if (stripe.breadth > default_stripe_breadth)
        //          AddPreviousStripe, BeginNewStripe, AddButton
        // }


        CSize szButton = pButton->OnCalculateSize (&dc, szButtonDefault, bHorizontal);
        if (bHorizontal)
        {

        }
        else // vertical layout
        {
            if (bSep)
            {
                if (stripe.buttonCount > 0)
                {
                    listStripes.AddTail (stripe);
                }
                stripe.buttonCount = 1;
                stripe.breadth = 0; // separator length is set automatically
                stripe.size = szButton.cy; // cx for horz.
                listStripes.AddTail (stripe);
                stripe = ButtonStripe ();
            }
            else if (szButton.cx > nMaxSize) // this button is larger than current toolbar width
            {
                if (stripe.buttonCount > 0)
                {
                    listStripes.AddTail (stripe);
                }
                stripe.buttonCount = 1;
                stripe.breadth = szButton.cx; // cy for horz.
                stripe.size = szButton.cy; // cx for horz.
                listStripes.AddTail (stripe); // stripe with a single large button
                stripe = ButtonStripe ();
            }
            else // usual button
            {
                if (stripe.breadth + szButton.cx <= nMaxSize)
                {
                    stripe.breadth += szButton.cx;
                    stripe.buttonCount ++;
                    if (szButton.cy > stripe.size)
                        stripe.size = szButton.cy;
                }
                else
                {
                    if (stripe.buttonCount > 0)
                    {
                        listStripes.AddTail (stripe);
                    }
                    stripe.buttonCount = 1;
                    stripe.breadth = szButton.cx; // cy for horz.
                    stripe.size = szButton.cy; // cx for horz.
                }
            }
        }
        bPrevSeparator = bSep;
    }
    if (stripe.buttonCount > 0)
    {
        listStripes.AddTail (stripe);
    }
    if (listStripes.IsEmpty ())
    {
        return CSize (0, 0);
    }
    if (listStripes.GetTail ().breadth == 0) // last item is separator
    {
        listStripes.RemoveTail ();
    }

    // Now calculate total size
    int totalLength = m_nCaptionHeight + 4;
    int maxBreadth = nMaxSize;
    POSITION posStripes = listStripes.GetHeadPosition ();
    while (posStripes != NULL)
    {
        stripe = listStripes.GetNext (posStripes);
        ASSERT (stripe.buttonCount > 0);
        totalLength += stripe.size;
        if (stripe.breadth > maxBreadth)
        {
            maxBreadth = stripe.breadth;
        }
    }

    if (!bCalcOnly)
    {
        CPoint ptButtonPos = rectClient.TopLeft ();

        posStripes = listStripes.GetHeadPosition ();
        stripe = ButtonStripe();

        for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
        {
            pButton = (CBCGPToolbarButton*)m_Buttons.GetNext (pos);
            if (pButton == NULL)
            {
                break;
            }

            if (!pButton->IsVisible ())
            {
                continue;
            }

            bool bSep = (pButton->m_nStyle & TBBS_SEPARATOR) != 0;
            if (bSep && bPrevSeparator)
            {
                continue;
            }

            CSize szButton = pButton->OnCalculateSize (&dc, szButtonDefault, bHorizontal);
            CRect rcButton (0, 0, 0, 0);

            if (stripe.buttonCount == 0) // this member is decremented below
            {
                ptButtonPos.y += stripe.size;
                if (posStripes == NULL)
                {
                    break;
                }
                stripe = listStripes.GetNext (posStripes);
                ptButtonPos.x = rectClient.left + (maxBreadth - stripe.breadth) / 2; // center-alignment
            }

            if (bSep)
            {
                ASSERT (stripe.breadth == 0);
                ASSERT (stripe.buttonCount == 1);
                rcButton.left = rectClient.left;
                rcButton.top = ptButtonPos.y;
                rcButton.right = rcButton.left + maxBreadth;
                rcButton.bottom = rcButton.top + szButton.cy;
            }
            else
            {
                rcButton.left = ptButtonPos.x;
                rcButton.top = ptButtonPos.y + (stripe.size - szButton.cy) / 2; // center-alignment
                rcButton.right = rcButton.left + szButton.cx;
                rcButton.bottom = rcButton.top + szButton.cy;
                ptButtonPos.x += szButton.cx;
            }
            pButton->SetRect (rcButton);
            stripe.buttonCount --;
        }
    }

    if (m_bAdditionalPixel)
    {
        ++maxBreadth;
    }

    return bHorizontal ? 
        CSize (totalLength + xBorders, maxBreadth + yBorders) :
        CSize (maxBreadth + xBorders, totalLength + yBorders);
}

//**********************************************************************************
DWORD CToolPalette::GetCurrentAlignment () const
{
    return CBRS_ORIENT_VERT;
}
//**********************************************************************************
void CToolPalette::OnSize(UINT nType, int cx, int cy) 
{
    CBCGPBaseToolBar::OnSize (nType, cx, cy);

    if (IsCustomizeMode () && !m_bLocked)
    {
        OnCancelMode ();
    }
 
    if (!m_bInUpdateShadow)
    {
        AdjustLocations ();
    }
}
//**********************************************************************************
CSize CToolPalette::CalcSize (BOOL /*bVertDock*/)
{
    return CalcButtonLocations (m_nColumns, true);
}
//**********************************************************************************
void CToolPalette::AdjustLocations ()
{
    CalcButtonLocations (m_nColumns, false);
    UpdateTooltips ();
    return;
}
//**********************************************************************************
void CToolPalette::SetColumns (int nColumns)
{
    if (m_nColumns == nColumns || nColumns < 1)
    {
        return;
    }

    m_nColumns = nColumns;
    if (GetSafeHwnd () != NULL && GetParentFrame () != NULL)
    {
        m_bAdditionalPixel = !m_bAdditionalPixel;
        GetParentFrame ()->RecalcLayout ();
    }
    GetParent ()->Invalidate (); // removes artifacts on a docking bar
}
//**********************************************************************************
void CToolPalette::CheckButtonID(UINT uCommandID)
{
    int index = CommandToIndex (uCommandID);
    if (index >= 0)
    {
        CBCGPToolbarButton* pButton = GetButton (index);
        ASSERT_VALID (pButton);
        m_nCheckedIndex = index;
        Invalidate ();
    }
}
//**********************************************************************************
UINT CToolPalette::GetCheckedButtonID () const
{   
    return GetItemID (m_nCheckedIndex);
}
//**********************************************************************************
void CToolPalette::SetButtonStyle (int nIndex, UINT nStyle)
{
    CBCGPToolBar::SetButtonStyle (nIndex,
        m_nCheckedIndex == nIndex ? 
            nStyle | TBBS_CHECKED :
            nStyle & (~TBBS_CHECKED)
        );
}
//**********************************************************************************

