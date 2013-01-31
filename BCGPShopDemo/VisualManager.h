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


// CShopVisualManager

class CShopVisualManager : public CBCGPWinXPVisualManager
{
	DECLARE_DYNCREATE(CShopVisualManager)

public:
	CShopVisualManager();
	virtual ~CShopVisualManager();

protected:
	virtual void OnUpdateSystemColors ();

	virtual void OnDrawSeparator (CDC* pDC, CBCGPBaseControlBar* pBar,
										 CRect rect, BOOL bHorz);

    virtual void OnFillButtonInterior (CDC* pDC,
        CBCGPToolbarButton* pButton, CRect rect, CBCGPVisualManager::BCGBUTTON_STATE state);

    virtual void OnDrawBarGripper (CDC* pDC,
        CRect rectGripper, BOOL bHorz, CBCGPBaseControlBar* pBar
        );

    virtual BOOL IsToolbarRoundShape (CBCGPToolBar* /*pToolBar*/)
    {
        return FALSE;
    }

    virtual BOOL OnEraseTabsFrame (CDC* pDC, CRect rect, 
        const CBCGPBaseTabWnd* pTabWnd);

    virtual void OnEraseTabsArea (CDC* /*pDC*/, CRect /*rect*/, const CBCGPBaseTabWnd* /*pTabWnd*/) 
    {
        // Suppress erasing
    }


    virtual void OnDrawTab (CDC* pDC, CRect rectTab, int iTab,
        BOOL bIsActive, const CBCGPBaseTabWnd* pTabWnd);
	
    virtual void OnDrawTabCloseButton (CDC* pDC, CRect rect, 
        const CBCGPBaseTabWnd* pTabWnd, 
        BOOL bIsHighlighted,
        BOOL bIsPressed,
        BOOL bIsDisabled);

    virtual void OnHighlightMenuItem (CDC*pDC, CBCGPToolbarMenuButton* pButton,
        CRect rect, COLORREF& clrText);


    virtual void OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
        CRect rectClient, CRect rectClip,
        BOOL bNCArea);

    virtual COLORREF OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
        BOOL bActive, CRect rectCaption, CRect rectButtons);


    virtual COLORREF OnFillMiniFrameCaption (CDC* pDC, CRect rectCaption, 
        CBCGPMiniFrameWnd* pFrameWnd,
        BOOL bActive);

    virtual void OnDrawSlider (CDC* pDC, CBCGPSlider* pSlider, CRect rect, BOOL bAutoHideMode);

public:
    virtual int  GetTabAreaHeight() const;
    virtual void DrawSingleTab(CDC* pDC, CRect rectTabArea, CWnd* pContentWnd);

public:
    CBCGPControlRenderer m_imgToolButtonFrame;

    CBCGPControlRenderer m_imgTabbedBar;
    CBCGPControlRenderer m_imgTabHeaders[2];
    CBCGPControlRenderer m_imgTabCloseButton;

};


