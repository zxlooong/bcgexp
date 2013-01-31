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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BCGPShopDemo.h"
#include "VisualManager.h"

#include "MainFrm.h"
#include "ColorPicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CBCGPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_UPDATE_COMMAND_UI_RANGE(ID_TOOLBUTTON01, ID_TOOLBUTTON_MAX, OnUpdateAlwaysEnabledButtons)
    ON_COMMAND_RANGE(ID_TOOLBUTTON01, ID_TOOLBUTTON_COLORPICKER, OnCheckToolBarButton)
    ON_UPDATE_COMMAND_UI_RANGE(ID_TOOLBAR_1COLUMN, ID_TOOLBAR_5COLUMNS, OnUpdateAlwaysEnabledButtons)
    ON_COMMAND_RANGE(ID_TOOLBAR_1COLUMN, ID_TOOLBAR_5COLUMNS, OnSetToolBarColumns)
    ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_STYLES, ID_VIEW_SWATCHES, OnUpdateViewTabPanels)
    ON_COMMAND_RANGE(ID_VIEW_STYLES, ID_VIEW_SWATCHES, OnViewTabPanels)
    ON_MESSAGE(WM_SETACTIVECOLOR, OnSetActiveColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CBCGPMDIFrameWnd::OnCreate (lpCreateStruct) == -1)
    {
        return -1;
    }

    CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CShopVisualManager));

    //----------------------
    // Create docked panels
    //----------------------
    if (!CreatePanelByID (ID_VIEW_STYLES))
    {
        return FALSE;
    }
    if (!CreatePanelByID (ID_VIEW_COLOR))
    {
        return FALSE;
    }
    if (!CreatePanelByID (ID_VIEW_SWATCHES))
    {
        return FALSE;
    }
    if (!CreatePanelByID (ID_VIEW_INFO))
    {
        return FALSE;
    }
    if (!CreatePanelByID (ID_VIEW_LAYERS))
    {
        return FALSE;
    }

    if (!m_wndToolPalette.CreateEx (this, 
        TBSTYLE_FLAT,
        WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY 
        | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_BORDER_3D, CRect (1, 1, 1, 1), ID_TOOLPALETTE) ||
        !m_wndToolPalette.LoadToolBar (IDR_TOOLBARMAIN, IDR_MAINTOOLBAR, 0, TRUE, 0, 0, IDR_MAINTOOLBARC))
    {
        TRACE0("Failed to create Tool palette\n");
        return FALSE;
    }

    m_wndToolPalette.SetWindowText (_T("Bcg"));
    m_wndToolPalette.EnableDocking (CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
    m_wndToolPalette.SetPermament (TRUE); // cannot be closed
    m_wndToolPalette.SetSizes (CSize (26,21), CSize (23,18));

    CShopToolbarColorPicker btnColorPicker;
    btnColorPicker.SetMiniButtonImages (IDB_COLORPICKER_MINIBTNS);
    btnColorPicker.m_nID = ID_TOOLBUTTON_COLORPICKER;
    m_wndToolPalette.ReplaceButton (ID_TOOLBUTTON_COLORPICKER, btnColorPicker);

    //----------------------
    // Create Select toolbar
    //----------------------

    if (!m_wndToolSelect.Create (this,
        WS_CHILD|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
        CBRS_GRIPPER | CBRS_BORDER_3D,
        IDR_TOOLBARSELECT) ||
        !m_wndToolSelect.LoadToolBar (IDR_TOOLBARSELECT, IDR_SELECTTOOL, 0, FALSE, 0, 0, IDR_SELECTTOOLC))
    {
        TRACE0("Failed to create Select toolbar\n");
        return FALSE;
    }

    m_wndToolPalette.ReplaceButton (ID_TOOLBUTTON02,
        CBCGPDropDownToolbarButton (_T("Select Tool"), &m_wndToolSelect));

    //----------------------
    // Create Lasso toolbar
    //----------------------

    if (!m_wndToolLasso.Create (this,
        WS_CHILD|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
        CBRS_GRIPPER | CBRS_BORDER_3D,
        IDR_TOOLBARLASSO) ||
        !m_wndToolLasso.LoadToolBar (IDR_TOOLBARLASSO, IDR_LASSOTOOL, 0, FALSE, 0, 0, IDR_LASSOTOOLC))
    {
        TRACE0("Failed to create Lasso toolbar\n");
        return FALSE;
    }

    m_wndToolPalette.ReplaceButton (ID_TOOLBUTTON03,
        CBCGPDropDownToolbarButton (_T("Lasso Tool"), &m_wndToolLasso));

    //----------------------
    // Initialize Menu bar
    //----------------------
    if (!m_wndMenuBar.Create (this))
    {
        TRACE0 ("Failed to create menubar\n");
        return -1;      // fail to create
    }

    m_wndMenuBar.SetBarStyle (m_wndMenuBar.GetBarStyle () |
                    CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
    m_wndMenuBar.EnableDocking (CBRS_TOP | CBRS_BOTTOM);

    // Initialize Context toolbar
    m_wndContextToolBar.CreateEx (this, 
        TBSTYLE_FLAT,
        WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY |
        CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC, CRect (1, 1, 1, 1), ID_CONTEXTTOOLBAR);

    m_wndContextToolBar.SetWindowText (_T("Context Toolbar"));
    m_wndContextToolBar.LoadToolBar (IDR_CONTEXTTOOLBAR, IDR_CONTEXTTOOLBAR, 0, TRUE, 0, 0); //locked toolbar
    m_wndContextToolBar.EnableDocking (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
    m_wndContextToolBar.SetPermament (TRUE); // cannot be closed

    // Place a combo box in the Context toolbar
    CBCGPToolbarComboBoxButton comboButton (ID_TOOLBUTTON_COMBO, -1, CBS_DROPDOWNLIST);
	CBCGPToolbarComboBoxButton::SetCenterVert (TRUE);
    comboButton.AddItem (_T("Group"));
    comboButton.AddItem (_T("Layer"));
    comboButton.SelectItem (0);
    m_wndContextToolBar.ReplaceButton (ID_TOOLBUTTON_COMBO, comboButton);

    EnableDocking (CBRS_ALIGN_ANY);
    DockControlBar (&m_wndMenuBar, AFX_IDW_DOCKBAR_TOP);
    DockControlBar (&m_wndContextToolBar, AFX_IDW_DOCKBAR_TOP);
    DockControlBar (&m_wndToolPalette, AFX_IDW_DOCKBAR_LEFT);

    CBCGPDockingControlBar* pDockingBar = NULL;
    DockControlBar (&m_wndPanel1, AFX_IDW_DOCKBAR_RIGHT);
    m_wndPanel5.AttachToTabWnd (&m_wndPanel1, BCGP_DM_SHOW, TRUE, &pDockingBar);
    m_wndPanel3.AttachToTabWnd (&m_wndPanel1, BCGP_DM_SHOW, TRUE, &pDockingBar);
    m_wndPanel4.DockToWindow (pDockingBar, CBRS_ALIGN_BOTTOM);
    m_wndPanel2.AttachToTabWnd (&m_wndPanel4, BCGP_DM_SHOW, TRUE, &pDockingBar);

    //--------------------------------------------------------------------
    // Enable control bar context menu (list of bars + customize command):
    //--------------------------------------------------------------------
    EnableControlBarMenu (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize"), ID_VIEW_DOCKPANELS, FALSE, FALSE);

    OnCheckToolBarButton (ID_TOOLBUTTON01); // Select first tool

    OnSetActiveColor (0, (LPARAM)RGB(15, 200, 255));
    OnSetActiveColor (1, (LPARAM)RGB(200, 15, 255));
    return 0;
}

CShopToolBase* CMainFrame::CreatePanelByID (UINT id)
{
    CShopToolBase* pTool = GetToolPanelByID (id);
    if (!pTool)
    {
        return NULL;
    }
    if (pTool->GetSafeHwnd () != NULL)
    {
        return pTool;
    }

    const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI;
    BOOL bStatus = FALSE;
    CRect rcInit (0, 0, 215, 200);

    switch (id)
    {
    case ID_VIEW_STYLES:
        bStatus = m_wndPanel1.Create (_T("Styles"), this, rcInit, TRUE, ID_DOCKPANEL_1, dwStyle);
        break;
    case ID_VIEW_COLOR:
        bStatus = m_wndPanel2.Create (_T("Color"), this, rcInit, TRUE, ID_DOCKPANEL_2, dwStyle);
        break;
    case ID_VIEW_SWATCHES:
        bStatus = m_wndPanel3.Create (_T("Swatches"), this, rcInit, TRUE, ID_DOCKPANEL_3, dwStyle);
        break;
    case ID_VIEW_INFO:
        bStatus = m_wndPanel4.Create (_T("Info"), this, rcInit, TRUE, ID_DOCKPANEL_4, dwStyle);
        break;
    case ID_VIEW_LAYERS:
        bStatus = m_wndPanel5.Create (_T("Layers"), this, rcInit, TRUE, ID_DOCKPANEL_5, dwStyle);
        break;
    }

    if (!bStatus)
    {
        TRACE0 ("Failed to create Panel.\n");
        return NULL;
    }

    pTool->EnableDocking (CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
    return pTool;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)

{
	if( !CBCGPMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
    if (m_wndToolPalette.GetSafeHwnd () != 0)
    {
        CWnd* pDockBar = m_wndToolPalette.GetParent ();
        if (pDockBar)
        {
            pDockBar->Invalidate ();
        }
    }

    CBCGPMDIFrameWnd::OnSize (nType, cx, cy);
}

void CMainFrame::OnUpdateAlwaysEnabledButtons(CCmdUI* pCmdUI)
{
    pCmdUI->Enable (TRUE); // All buttons in main ToolBar are always enabled
}

CShopToolbarColorPicker* CMainFrame::GetColorPickerToolButton () const
{
    int nPickerBtnIndex = m_wndToolPalette.CommandToIndex (ID_TOOLBUTTON_COLORPICKER);
    if (nPickerBtnIndex >= 0)
    {
        return DYNAMIC_DOWNCAST (
            CShopToolbarColorPicker, 
            m_wndToolPalette.GetButton (nPickerBtnIndex));
    }
    return NULL;
}

void CMainFrame::OnSetToolBarColumns (UINT nID)
{
    int nColumns = nID - ID_TOOLBAR_1COLUMN + 1;
    m_wndToolPalette.SetColumns (nColumns);
    CShopToolbarColorPicker* pPicker = GetColorPickerToolButton ();
    if (pPicker)
    {
        pPicker->SetCompactLayout (nColumns == 1);
    }
}

void CMainFrame::OnCheckToolBarButton (UINT nID)
{
    m_wndToolPalette.CheckButtonID (nID);

    m_wndContextToolBar.ShowButtons (ID_TOOLBUTTON01, ID_TOOLBUTTON28, FALSE, FALSE);
    m_wndContextToolBar.ShowButtons (nID, nID, TRUE, FALSE);

    // Setting up specific tool buttons

    // First hide them
    m_wndContextToolBar.ShowButtons (ID_TOOLBUTTON_COMBO, ID_TOOLBUTTON_COMBO, FALSE, FALSE);
    m_wndContextToolBar.ShowButtons (ID_TOOLBUTTON_SELECTION_OPTIONS, ID_TOOLBUTTON_SELECTION_OPTIONS, FALSE, FALSE);
    m_wndContextToolBar.ShowButtons (ID_TOOLBUTTON_QUICK_SEL_OPTIONS, ID_TOOLBUTTON_QUICK_SEL_OPTIONS, FALSE, FALSE);

    switch (nID)
    {
    case ID_TOOLBUTTON01:
        m_wndContextToolBar.ShowButtons (ID_TOOLBUTTON_COMBO, ID_TOOLBUTTON_COMBO, TRUE, FALSE);
        break;
    case ID_TOOLBUTTON02:
    case ID_TOOLBUTTON03:
    case ID_TOOLBUTTON23:
    case ID_TOOLBUTTON24:
    case ID_TOOLBUTTON25:
    case ID_TOOLBUTTON26:
    case ID_TOOLBUTTON27:
        m_wndContextToolBar.ShowButtons (ID_TOOLBUTTON_SELECTION_OPTIONS, ID_TOOLBUTTON_SELECTION_OPTIONS, TRUE, FALSE);
        break;
    case ID_TOOLBUTTON04:
        m_wndContextToolBar.ShowButtons (ID_TOOLBUTTON_QUICK_SEL_OPTIONS, ID_TOOLBUTTON_QUICK_SEL_OPTIONS, TRUE, FALSE);
        break;
    }

    m_wndContextToolBar.AdjustLayout ();
}

// CMainFrame message handlers

CShopToolBase* CMainFrame::GetToolPanelByID (UINT id)
{
    switch (id)
    {
    case ID_VIEW_STYLES:
        return &m_wndPanel1;
    case ID_VIEW_COLOR:
        return &m_wndPanel2;
    case ID_VIEW_SWATCHES:
        return &m_wndPanel3;
    case ID_VIEW_INFO:
        return &m_wndPanel4;
    case ID_VIEW_LAYERS:
        return &m_wndPanel5;
    }
    return NULL;
}

void CMainFrame::OnUpdateViewTabPanels (CCmdUI *pCmdUI)
{
    CShopToolBase* pTool = GetToolPanelByID (pCmdUI->m_nID);
    if (pTool == NULL)
    {
        TRACE0 ("Wrong panel ID. Check GetToolPanelByID() method.\n");
        ASSERT (FALSE);
        pCmdUI->Enable (FALSE);
        return;
    }
    pCmdUI->Enable ();
    pCmdUI->SetCheck (pTool->GetSafeHwnd () != NULL && pTool->IsVisible ());
 }

void CMainFrame::OnViewTabPanels (UINT nID)
{
    CShopToolBase* pTool = GetToolPanelByID (nID);
    if (pTool)
    {
        if (pTool->GetSafeHwnd () != NULL)
        {
            pTool->ShowControlBar (!pTool->IsVisible (), FALSE, TRUE);
        }
        else
        {
            CShopToolBase* pCreatedTool = CreatePanelByID (nID);
            ASSERT (pTool == pCreatedTool);
            if (pCreatedTool != NULL)
            {
                int d = 200 + 20 * (nID % 10);
                pCreatedTool->FloatControlBar (CRect (d, d, d + 215, d + 200));
            }
        }
    }
}

LRESULT CMainFrame::OnSetActiveColor(WPARAM wParam, LPARAM lParam)
{
    COLORREF color = (COLORREF)lParam;
    CShopToolbarColorPicker* pPicker = GetColorPickerToolButton ();
    if (wParam == 0) // left
    {
        if (pPicker)
        {
            pPicker->SetLeftColor (color);
        }
        //m_wndPanel2.SetLeftColor (color);
    }
    else // right
    {
        if (pPicker)
        {
            pPicker->SetRightColor (color);
        }
        //m_wndPanel2.SetRightColor (color);
    }
    return 0;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid () const
{
    CBCGPMDIFrameWnd::AssertValid ();
}

void CMainFrame::Dump (CDumpContext& dc) const
{
    CBCGPMDIFrameWnd::Dump (dc);
}
#endif //_DEBUG
