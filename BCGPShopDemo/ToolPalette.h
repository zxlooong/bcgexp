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
#include "ShopToolBase.h"


// CToolPalette

class CToolPalette : public CBCGPToolBar
{
	DECLARE_DYNAMIC(CToolPalette)

protected:
    const int m_nCaptionHeight; // for vertical layout
    int m_nColumns;
    int m_nCheckedIndex;
    bool m_bAdditionalPixel; // layout fix
    CFont m_fntTitle;
    CBCGPControlRenderer m_imgCaption;
public:
	CToolPalette();
	virtual ~CToolPalette();

// Operations
public:
    void SetColumns (int nColumns);
    int GetColumns() const
    {
        return m_nColumns;
    }
    void CheckButtonID(UINT uCommandID);
    UINT GetCheckedButtonID() const;

    virtual void SetButtonStyle(int nIndex, UINT nStyle);

protected:

    enum EDisplayOptions
    {
        eDisplayTitle = 0x0001,
        eDisplayBorder = 0x0002,
        eDisplaySizeControl = 0x0004
    };

    virtual EDisplayOptions GetToolbarDisplayOptions() const;

    // Returns the size of ToolBar. Called by AdjustLocations() and CalcSize().
    virtual CSize CalcButtonLocations(int nColumns, bool bCalcOnly);

    virtual CSize CalcSize (BOOL bVertDock);
    virtual void AdjustLocations ();
    virtual void DoPaint (CDC* pDC);
    virtual void OnFillBackground (CDC* pDC);

    virtual CBCGPMiniFrameWnd* CreateDefaultMiniframe (CRect rectInitial);

    virtual BOOL AllowShowOnList () const		
    {	
        return FALSE;	// Don't show in the tool bars list
    }
    virtual DWORD GetCurrentAlignment () const;

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);

    DECLARE_MESSAGE_MAP()
};

