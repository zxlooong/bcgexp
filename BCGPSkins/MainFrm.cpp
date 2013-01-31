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
#include "BCGPSkins.h"
#include "BackgndImageDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LOOK_2000, ID_LOOK_VS2008, OnUpdateLook)
	ON_COMMAND_RANGE(ID_LOOK_2000, ID_LOOK_VS2008, OnLook)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBCGPToolBar::EnableQuickCustomization ();

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR256 : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!CreateOutlookBar ())
	{
		TRACE0("Failed to create workspace bar\n");
		return -1;      // fail to create
	}

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText (strMainToolbarTitle);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndBarOutlook.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndBarOutlook);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	WNDCLASS wndcls;

	if (GetClassInfo (AfxGetInstanceHandle (), cs.lpszClass, &wndcls))
	{
		HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_MAINFRAME), RT_GROUP_ICON);
		HICON hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));

		// register a very similar WNDCLASS but without CS_HREDRAW and CS_VREDRAW styles:
		cs.lpszClass = AfxRegisterWndClass (CS_DBLCLKS, wndcls.hCursor, wndcls.hbrBackground, hIcon);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */);

	pDlgCust->Create ();
}

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM lp)
{
	CPoint point (BCG_GET_X_LPARAM(lp), BCG_GET_Y_LPARAM(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->Create (this, point.x, point.y, pPopup->Detach ());

	return 0;
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM /*wp*/,LPARAM)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	//
	// UINT uiToolBarId = (UINT) wp;
	// if (uiToolBarId == IDR_MAINFRAME)
	// {
	//		do something with m_wndToolBar
	// }

	CBCGPToolBar::SetSizes (CSize (24, 22), CSize (16, 15));
	return 0;
}

BOOL CMainFrame::OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup)
{
	//---------------------------------------------------------
	// Replace ID_VIEW_TOOLBARS menu item to the toolbars list:
	//---------------------------------------------------------
    CFrameWnd::OnShowPopupMenu (pMenuPopup);

    if (pMenuPopup != NULL &&
		pMenuPopup->GetMenuBar ()->CommandToIndex (ID_VIEW_TOOLBARS) >= 0)
    {
		if (CBCGPToolBar::IsCustomizeMode ())
		{
			//----------------------------------------------------
			// Don't show toolbars list in the cuztomization mode!
			//----------------------------------------------------
			return FALSE;
		}

		pMenuPopup->RemoveAllItems ();

		CMenu menu;
		VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pMenuPopup->GetMenuBar ()->ImportFromMenu (*pPopup, TRUE);
    }

	return TRUE;
}

void CMainFrame::OnViewWorkspace() 
{
	ShowControlBar (&m_wndBarOutlook,
					!(m_wndBarOutlook.GetStyle () & WS_VISIBLE),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndBarOutlook.GetStyle () & WS_VISIBLE);
}

BOOL CMainFrame::CreateOutlookBar ()
{
	if (!m_wndBarOutlook.Create (_T("Shortcuts"), this, CRect (0, 0, 100, 100), 
		ID_VIEW_WORKSPACE, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE;		// fail to create
	}

	CBCGPOutlookWnd* pOutlookBar = (CBCGPOutlookWnd*) 
										m_wndBarOutlook.GetUnderlinedWindow ();

	if (pOutlookBar == NULL)
	{
		ASSERT (FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit (TRUE);

	const UINT uiPage1ID = 1;
	const UINT uiPage2ID = 2;

	DWORD dwPaneStyle = dwDefaultToolbarStyle | CBRS_FLOAT_MULTI;

	// can float, can autohide, can resize, CAN NOT CLOSE
	DWORD dwBCGStyle = CBRS_BCGP_FLOAT | CBRS_BCGP_AUTOHIDE | CBRS_BCGP_RESIZE;

	m_wndOutlookPane1.Create (&m_wndBarOutlook, dwPaneStyle, uiPage1ID, dwBCGStyle);
	m_wndOutlookPane1.SetOwner (this);
	m_wndOutlookPane1.EnableTextLabels ();
	m_wndOutlookPane1.EnableDocking (CBRS_ALIGN_ANY);

	m_wndOutlookPane2.Create (&m_wndBarOutlook, dwPaneStyle, uiPage2ID, dwBCGStyle);
	m_wndOutlookPane2.SetOwner (this);
	m_wndOutlookPane2.EnableTextLabels ();
	m_wndOutlookPane2.EnableDocking (CBRS_ALIGN_ANY);

	CImageList images;

	CBitmap bmp;
	if (!bmp.LoadBitmap (IDB_SKINS))
	{
		TRACE(_T("Can't load bitmap: %x\n"), IDB_SKINS);
		return FALSE;
	}

	BITMAP bmpObj;
	bmp.GetBitmap (&bmpObj);

	UINT nFlags = ILC_MASK;

	switch (bmpObj.bmBitsPixel)
	{
	case 4:
	default:
		nFlags |= ILC_COLOR4;
		break;

	case 8:
		nFlags |= ILC_COLOR8;
		break;

	case 16:
		nFlags |= ILC_COLOR16;
		break;

	case 24:
		nFlags |= ILC_COLOR24;
		break;

	case 32:
		nFlags |= ILC_COLOR32;
		break;
	}

	images.Create (32, bmpObj.bmHeight, nFlags, 0, 0);
	images.Add (&bmp, RGB (255, 0, 255));

	m_wndOutlookPane1.AddButton (images.ExtractIcon (0), _T("Office 2000®"), ID_LOOK_2000);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (1), _T("Office XP®"), ID_LOOK_XP);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (2), _T("Windows XP®"), ID_LOOK_WIN_XP);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (3), _T("Office 2003®"), ID_LOOK_2003);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (7), _T("VS 2005®"), ID_LOOK_VS2005);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (8), _T("Office 2007 Luna Blue"), ID_LOOK_2007_1);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (10), _T("Office 2007® Obsidian Black"), ID_LOOK_2007_2);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (9), _T("Office 2007® Aqua"), ID_LOOK_2007_3);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (11), _T("Office 2007® Silver"), ID_LOOK_2007_4);
	m_wndOutlookPane1.AddButton (images.ExtractIcon (7), _T("VS 2008®"), ID_LOOK_VS2008);

	m_wndOutlookPane2.AddButton (images.ExtractIcon (4), _T("Mac ®"), ID_LOOK_MAC);
	m_wndOutlookPane2.AddButton (images.ExtractIcon (5), _T("Background Image"), ID_LOOK_IMAGE);
	m_wndOutlookPane2.AddButton (images.ExtractIcon (6), _T("Exotic"), ID_LOOK_EXOTIC);

	pOutlookBar->AddTab (&m_wndOutlookPane1, "Default");
	m_wndOutlookPane1.EnableDocking (CBRS_ALIGN_ANY);
	m_wndOutlookPane1.SetDefaultState ();

	CBCGPDockingCBWrapper* pWrapper = 
		DYNAMIC_DOWNCAST (CBCGPDockingCBWrapper, 
							pOutlookBar->GetTabWnd (0));
	ASSERT_VALID (pWrapper);
	pWrapper->SetTabbedControlBarRTC (RUNTIME_CLASS (CBCGPOutlookBar));

	pOutlookBar->AddTab (&m_wndOutlookPane2, "User Skins");
	m_wndOutlookPane2.EnableDocking (CBRS_ALIGN_ANY);
	m_wndOutlookPane2.SetDefaultState ();

	pWrapper = DYNAMIC_DOWNCAST (CBCGPDockingCBWrapper, 
							pOutlookBar->GetTabWnd (1));
	ASSERT_VALID (pWrapper);
	pWrapper->SetTabbedControlBarRTC (RUNTIME_CLASS (CBCGPOutlookBar));

	m_wndOutlookPane1.EnableTextLabels (TRUE);

	m_wndBarOutlook.SetBarStyle(m_wndBarOutlook.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	return TRUE;
}

void CMainFrame::OnUpdateLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (theApp.m_uiCurrSkin == pCmdUI->m_nID);
}

void CMainFrame::OnLook(UINT nCommandID)
{
	if (nCommandID == ID_LOOK_IMAGE)
	{
		// Choose background image:
		CBackgndImageDlg dlg;
		if (dlg.DoModal () != IDOK)
		{
			return;
		}
	}

	theApp.SetSkin (nCommandID);
	RecalcLayout ();
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	if (!CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	m_wndOutlookPane1.RestoreOriginalstate ();
	m_wndOutlookPane2.RestoreOriginalstate ();

	return TRUE;
}
