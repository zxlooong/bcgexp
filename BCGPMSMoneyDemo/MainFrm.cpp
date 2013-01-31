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
#include "BCGPMSMoneyDemo.h"
#include "BCGPMSMoneyDemoDoc.h"
#include "BCGPMSMoneyDemoView.h"

#include "MainFrm.h"

#include "BCGPMSMVisualManager.h"

#include "BCGPMSMLinksBarButton.h"

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
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_UPDATE_COMMAND_UI(ID_GO_ADDRESS_EDIT, OnUpdateGoAddressEdit)
	ON_UPDATE_COMMAND_UI(ID_BACKWARD_1, OnUpdateBackward1)
	ON_UPDATE_COMMAND_UI(ID_BACKWARD_2, OnUpdateBackward2)
	ON_UPDATE_COMMAND_UI(ID_FORWARD_1, OnUpdateForward1)
	ON_UPDATE_COMMAND_UI(ID_FORWARD_2, OnUpdateForward2)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_CUSTOMIZE, OnUpdateCustomize)
	ON_COMMAND_RANGE(ID_CATEGORIE_1, ID_CATEGORIE_8, OnCategorie)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CATEGORIE_1, ID_CATEGORIE_8, OnUpdateCategorie)
	ON_COMMAND_RANGE(ID_LINKS_HOME_1, ID_LINKS_TAXES_5, OnLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LINKS_HOME_1, ID_LINKS_TAXES_5, OnUpdateLinks)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_HELP_BCGSOFT, OnHelpBcgsoft)
	ON_WM_SETTINGCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bMainToolbarMenu = FALSE;
	m_nCategorie       = (UINT)-1;
}

CMainFrame::~CMainFrame()
{
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


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle (WS_CAPTION | FWS_ADDTOTITLE, 0);
	ModifyStyleEx (WS_EX_CLIENTEDGE, 0);

	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPMSMVisualManager));
    CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	//---------------------------------
	// Set toolbar and menu image size:
	//---------------------------------
	CBCGPToolbarButton::m_bWrapText = FALSE;
	CBCGPToolBar::SetMenuSizes (CSize (22, 22), CSize (16, 16));

	CBCGPToolbarComboBoxButton::SetFlatMode ();
	CBCGPToolbarComboBoxButton::SetCenterVert ();

	if (!m_wndCaptionBar.Create(this, IDR_MAINFRAME))
	{
		TRACE0("Failed to create captionbar\n");
		return -1;
	}

	if (globalData.fontRegular.GetSafeHandle () != NULL)
	{
		LOGFONT lf;
		ZeroMemory (&lf, sizeof (LOGFONT));
		globalData.fontRegular.GetLogFont (&lf);

		m_wndCaptionBar.SetCaptionFont (lf);
	}

	if (!m_wndMenuBar.Create (this, dwDefaultToolbarStyle))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);

	CClientDC dc (this);
	m_bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 16;

	UINT uiToolbarHotID  = m_bIsHighColor ? IDB_HOTTOOLBAR : 0;
	UINT uiToolbarColdID = m_bIsHighColor ? IDB_COLDTOOLBAR : 0;
	UINT uiToolbarDisID  = m_bIsHighColor ? IDB_DISABLEDTOOLBAR : 0;
	UINT uiToolbarPresID = m_bIsHighColor ? IDB_PRESSEDTOOLBAR : 0;
	UINT uiMenuID        = m_bIsHighColor ? IDB_MENU_IMAGES : IDB_MENU_IMAGES_16;

	if (!m_wndToolBar.CreateEx (this, TBSTYLE_FLAT,
		                        CBRS_SIZE_FIXED | dwDefaultToolbarStyle) ||
		!m_wndToolBar.LoadToolBar (IDR_MAINFRAME, uiToolbarColdID, uiMenuID, 
			FALSE /* Not locked */, uiToolbarDisID, 0, uiToolbarHotID, uiToolbarPresID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.InsertButton 
		(CBCGPToolbarComboBoxButton (ID_GO_ADDRESS_EDIT, 0), 3);

	DockControlBar (&m_wndToolBar);

	if (!m_wndCategorieBar.CreateEx (this, TBSTYLE_FLAT, 
		                      CBRS_SIZE_FIXED | dwDefaultToolbarStyle, 
							  CRect (1, 1, 1, 1), AFX_IDW_TOOLBAR + 3))
	{
		TRACE0("Failed to create categoriebar\n");
		return -1;      // fail to create
	}

	DockControlBar (&m_wndCategorieBar);

	for (long i = 0; i < 8; i++)
	{
		if (!m_wndLinksBars[i].CreateEx (this, TBSTYLE_FLAT, 
								  CBRS_SIZE_FIXED | dwDefaultToolbarStyle, 
								  CRect (1, 1, 1, 1), AFX_IDW_TOOLBAR + 4 + i))
		{
			TRACE0("Failed to create linksbar\n");
			return -1;      // fail to create
		}

		DockControlBar (&m_wndLinksBars[i]);
		ShowControlBar (&m_wndLinksBars[i], FALSE, FALSE, FALSE);
	}

	m_wndLinksBars[0].InsertButton (CBCGPMSMLinksBarButton (_T("My Money"), ID_LINKS_HOME_1));
	m_wndLinksBars[0].InsertButton (CBCGPMSMLinksBarButton (_T("MSN Money News"), ID_LINKS_HOME_2));
	m_wndLinksBars[0].SetCurrentCommand (ID_LINKS_HOME_1);

	m_wndLinksBars[1].InsertButton (CBCGPMSMLinksBarButton (_T("Account List"), ID_LINKS_BANKING_1));
	m_wndLinksBars[1].InsertButton (CBCGPMSMLinksBarButton (_T("Account Tools"), ID_LINKS_BANKING_2));
	m_wndLinksBars[1].InsertButton (CBCGPMSMLinksBarButton (_T("Mortgages && Loans"), ID_LINKS_BANKING_3));
	m_wndLinksBars[1].InsertButton (CBCGPMSMLinksBarButton (_T("Bank Services"), ID_LINKS_BANKING_4));
	m_wndLinksBars[1].InsertButton (CBCGPMSMLinksBarButton (_T("Credit Center"), ID_LINKS_BANKING_5));
	m_wndLinksBars[1].SetCurrentCommand (ID_LINKS_BANKING_1);

	m_wndLinksBars[2].InsertButton (CBCGPMSMLinksBarButton (_T("Bills Summary"), ID_LINKS_BILLS_1));
	m_wndLinksBars[2].InsertButton (CBCGPMSMLinksBarButton (_T("Bill Calendar"), ID_LINKS_BILLS_2));
	m_wndLinksBars[2].InsertButton (CBCGPMSMLinksBarButton (_T("Transfer Money"), ID_LINKS_BILLS_3));
	m_wndLinksBars[2].InsertButton (CBCGPMSMLinksBarButton (_T("MSN Bill Pay Online"), ID_LINKS_BILLS_4));
	m_wndLinksBars[2].InsertButton (CBCGPMSMLinksBarButton (_T("History"), ID_LINKS_BILLS_5));
	m_wndLinksBars[2].SetCurrentCommand (ID_LINKS_BILLS_1);

	m_wndLinksBars[3].InsertButton (CBCGPMSMLinksBarButton (_T("Reports Home"), ID_LINKS_REPORTS_1));
	m_wndLinksBars[3].InsertButton (CBCGPMSMLinksBarButton (_T("Favorite Reports"), ID_LINKS_REPORTS_2));
	m_wndLinksBars[3].InsertButton (CBCGPMSMLinksBarButton (_T("Monthly Reports"), ID_LINKS_REPORTS_3));
	m_wndLinksBars[3].SetCurrentCommand (ID_LINKS_REPORTS_1);

	m_wndLinksBars[4].InsertButton (CBCGPMSMLinksBarButton (_T("Budget Summary"), ID_LINKS_BUDGET_1));
	m_wndLinksBars[4].InsertButton (CBCGPMSMLinksBarButton (_T("Budget vs. Spending"), ID_LINKS_BUDGET_2));
	m_wndLinksBars[4].SetCurrentCommand (ID_LINKS_BUDGET_1);

	m_wndLinksBars[5].InsertButton (CBCGPMSMLinksBarButton (_T("Investing Home"), ID_LINKS_INVESTING_1));
	m_wndLinksBars[5].InsertButton (CBCGPMSMLinksBarButton (_T("Investing Tools"), ID_LINKS_INVESTING_2));
	m_wndLinksBars[5].InsertButton (CBCGPMSMLinksBarButton (_T("Market News"), ID_LINKS_INVESTING_3));
	m_wndLinksBars[5].InsertButton (CBCGPMSMLinksBarButton (_T("Stocks"), ID_LINKS_INVESTING_4));
	m_wndLinksBars[5].InsertButton (CBCGPMSMLinksBarButton (_T("Funds"), ID_LINKS_INVESTING_5));
	m_wndLinksBars[5].InsertButton (CBCGPMSMLinksBarButton (_T("Insight"), ID_LINKS_INVESTING_6));
	m_wndLinksBars[5].InsertButton (CBCGPMSMLinksBarButton (_T("Brokers"), ID_LINKS_INVESTING_7));
	m_wndLinksBars[5].SetCurrentCommand (ID_LINKS_INVESTING_1);

	m_wndLinksBars[6].InsertButton (CBCGPMSMLinksBarButton (_T("Planning Home"), ID_LINKS_PLANNING_1));
	m_wndLinksBars[6].InsertButton (CBCGPMSMLinksBarButton (_T("Planning Tools"), ID_LINKS_PLANNING_2));
	m_wndLinksBars[6].InsertButton (CBCGPMSMLinksBarButton (_T("Retirement"), ID_LINKS_PLANNING_3));
	m_wndLinksBars[6].InsertButton (CBCGPMSMLinksBarButton (_T("Savings"), ID_LINKS_PLANNING_4));
	m_wndLinksBars[6].InsertButton (CBCGPMSMLinksBarButton (_T("Insurance"), ID_LINKS_PLANNING_5));
	m_wndLinksBars[6].InsertButton (CBCGPMSMLinksBarButton (_T("Family && College"), ID_LINKS_PLANNING_6));
	m_wndLinksBars[6].SetCurrentCommand (ID_LINKS_PLANNING_1);

	m_wndLinksBars[7].InsertButton (CBCGPMSMLinksBarButton (_T("Taxes Home"), ID_LINKS_TAXES_1));
	m_wndLinksBars[7].InsertButton (CBCGPMSMLinksBarButton (_T("Tax Tools"), ID_LINKS_TAXES_2));
	m_wndLinksBars[7].InsertButton (CBCGPMSMLinksBarButton (_T("Prepare Online"), ID_LINKS_TAXES_3));
	m_wndLinksBars[7].InsertButton (CBCGPMSMLinksBarButton (_T("Planning"), ID_LINKS_TAXES_4));
	m_wndLinksBars[7].InsertButton (CBCGPMSMLinksBarButton (_T("Products && Services"), ID_LINKS_TAXES_5));
	m_wndLinksBars[7].SetCurrentCommand (ID_LINKS_TAXES_1);

	//-----------------------
	// Set up Favorites menu:
	//-----------------------

	int nCategorie = theApp.GetProfileInt (_T(""), _T("Categorie"), 0);

	OnCategorie (ID_CATEGORIE_1 + nCategorie);

	m_wndTaskPane.Create (_T(""), this, CRect (0, 0, 140, 200), 
		FALSE, IDR_MAINFRAME + 1, 
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT, 0, 0);

	DockControlBar(&m_wndTaskPane);

	return 0;
}


void CMainFrame::OnClose() 
{
	theApp.WriteProfileInt (_T(""), _T("Categorie"), m_nCategorie);
	
	CFrameWnd::OnClose();
}


void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	if (m_wndCaptionBar.GetSafeHwnd () != NULL)
	{
		m_wndCaptionBar.SetParentActive (nState != WA_INACTIVE);
	}
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	SetupMemoryBitmapSize (CSize (cx, cy));

	if (m_wndCaptionBar.GetSafeHwnd () != NULL)
	{
		m_wndCaptionBar.SetParentMaximize (nType == SIZE_MAXIMIZED);
	}

	CFrameWnd::OnSize(nType, cx, cy);
}

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM)
{
	return 0;
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wp, LPARAM)
{
	UINT uiToolBarId = (UINT) wp;
	if (uiToolBarId == IDR_MAINFRAME)
	{
		// Replace "Back" and "Forward" buttons by the menu buttons
		// with the history lists:

		CMenu menuBackward;
		menuBackward.LoadMenu (IDR_BACKWARD_MENU);

		m_wndToolBar.ReplaceButton (ID_GO_BACK, 
			CBCGPToolbarMenuButton (ID_GO_BACK, menuBackward, 
						CImageHash::GetImageOfCommand (ID_GO_BACK), NULL));

		CMenu menuForward;
		menuForward.LoadMenu (IDR_FORWARD_MENU);

		m_wndToolBar.ReplaceButton (ID_GO_FORWARD,
			CBCGPToolbarMenuButton (ID_GO_FORWARD, menuForward, 
						CImageHash::GetImageOfCommand (ID_GO_FORWARD), NULL));
	}

	return 0;
}

BOOL CMainFrame::OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup)
{
	CBCGPFrameWnd::OnShowPopupMenu (pMenuPopup);

	if (pMenuPopup == NULL)
	{
		return TRUE;
	}

	CBCGPPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	CBCGPToolbarMenuButton* pParentButton = pMenuPopup->GetParentButton ();
	if (pParentButton == NULL)
	{
		return TRUE;
	}

	switch (pParentButton->m_nID)
	{
	case ID_GO_BACK:
	case ID_GO_FORWARD:
		{
			if (CBCGPToolBar::IsCustomizeMode ())
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CMainFrame::OnUpdateGoAddressEdit(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnCategorie(UINT nID)
{
	if (m_nCategorie != -1)
	{
		ShowControlBar (&m_wndLinksBars[m_nCategorie], FALSE, TRUE, FALSE);
	}

	m_nCategorie = nID - ID_CATEGORIE_1;

	ShowControlBar (&m_wndLinksBars[m_nCategorie], TRUE, FALSE, FALSE);
}

void CMainFrame::OnUpdateCategorie(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (pCmdUI->m_nID == (m_nCategorie + ID_CATEGORIE_1));
}

CBCGPMSMLinksBar* CMainFrame::GetLinksBar (UINT nID)
{
	CBCGPMSMLinksBar* pBar = NULL;

	if(ID_LINKS_HOME_1 <= nID && nID <= ID_LINKS_HOME_2)
	{
		pBar = &m_wndLinksBars [0];
	}
	else if(ID_LINKS_BANKING_1 <= nID && nID <= ID_LINKS_BANKING_5)
	{
		pBar = &m_wndLinksBars [1];
	}
	else if(ID_LINKS_BILLS_1 <= nID && nID <= ID_LINKS_BILLS_5)
	{
		pBar = &m_wndLinksBars [2];
	}
	else if(ID_LINKS_REPORTS_1 <= nID && nID <= ID_LINKS_REPORTS_3)
	{
		pBar = &m_wndLinksBars [3];
	}
	else if(ID_LINKS_BUDGET_1 <= nID && nID <= ID_LINKS_BUDGET_2)
	{
		pBar = &m_wndLinksBars [4];
	}
	else if(ID_LINKS_INVESTING_1 <= nID && nID <= ID_LINKS_INVESTING_7)
	{
		pBar = &m_wndLinksBars [5];
	}
	else if(ID_LINKS_PLANNING_1 <= nID && nID <= ID_LINKS_PLANNING_6)
	{
		pBar = &m_wndLinksBars [6];
	}
	else if(ID_LINKS_TAXES_1 <= nID && nID <= ID_LINKS_TAXES_5)
	{
		pBar = &m_wndLinksBars [7];
	}
	else
	{
		ASSERT (FALSE);
	}

	return pBar;
}

void CMainFrame::OnLinks(UINT nID)
{
	CBCGPMSMLinksBar* pBar = GetLinksBar (nID);

	if (pBar != NULL)
	{
		pBar->SetCurrentCommand (nID);
	}
}

void CMainFrame::OnUpdateLinks(CCmdUI* pCmdUI) 
{
	CBCGPMSMLinksBar* pBar = GetLinksBar (pCmdUI->m_nID);

	if (pBar != NULL)
	{
		pCmdUI->SetCheck (pCmdUI->m_nID == pBar->GetCurrentCommand ());
	}

	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateBackward1(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateBackward2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateForward1(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateForward2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnUpdateCustomize(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CFrameWnd::OnGetMinMaxInfo(lpMMI);

	if(m_wndCategorieBar.GetSafeHwnd () != NULL)
	{
		CRect rtRect (CPoint (0, 0), m_wndCategorieBar.CalcSize (FALSE));

		rtRect.bottom = 200;

		CalcWindowRect (rtRect, CWnd::adjustBorder);

		lpMMI->ptMinTrackSize.x = rtRect.Width ();
		lpMMI->ptMinTrackSize.y = rtRect.Height ();
	}
}

void CMainFrame::OnHelpBcgsoft() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com"), NULL, NULL, NULL);
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CFrameWnd::OnSettingChange(uFlags, lpszSection);

	if (m_wndCaptionBar.GetSafeHwnd () != NULL && 
		globalData.fontRegular.GetSafeHandle () != NULL)
	{
		LOGFONT lf;
		ZeroMemory (&lf, sizeof (LOGFONT));
		globalData.fontRegular.GetLogFont (&lf);

		m_wndCaptionBar.SetCaptionFont (lf);
	}

	CRect rt;
	GetClientRect (rt);

	SetupMemoryBitmapSize (rt.Size ());
}

void CMainFrame::SetupMemoryBitmapSize (const CSize& sz)
{
	CBCGPMSMVisualManager* pManager = DYNAMIC_DOWNCAST (CBCGPMSMVisualManager,
		CBCGPVisualManager::GetInstance ());

	if (pManager != NULL)
	{
		CRect rtRes (0, 0, sz.cx, 0);

		CRect rt;

		CBCGPControlBar* bars[4] = 
			{&m_wndCaptionBar, &m_wndMenuBar, &m_wndToolBar, &m_wndCategorieBar};

		for (long i = 0; i < 4; i++)
		{
			CBCGPControlBar* pBar = bars [i];

			if (pBar != NULL && pBar->GetSafeHwnd () != NULL)
			{
				pBar->GetWindowRect (rt);
				rtRes.bottom += rt.Height ();
			}
		}

		CDC* pDC = GetDC ();

		pManager->SetupMemoryBitmapSize (pDC, rtRes.Size ());

		ReleaseDC (pDC);
	}
}
