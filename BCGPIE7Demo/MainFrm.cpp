//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
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
#include "BCGPIE7Demo.h"

#include "MainFrm.h"

#include "BCGPIE7DemoDoc.h"
#include "BCGPIE7DemoView.h"

#include "VisualManager.h"
#include "LinkButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_COMMAND(ID_VIEW_MENUBAR, OnViewMenuBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MENUBAR, OnUpdateViewMenuBar)
	ON_COMMAND(ID_VIEW_LINKSBAR, OnViewLinksBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LINKSBAR, OnUpdateViewLinksBar)
	ON_COMMAND(ID_FILE_NEW_TAB, OnNewTab)
	ON_COMMAND(ID_FILE_NEW_WINDOW, OnNewWindow)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND_RANGE(ID_FAVORITE_FIRST, ID_FAVORITE_LAST, OnFavorite)
	ON_COMMAND_RANGE(ID_HISTORY_FIRST, ID_HISTORY_FIRST + HISTORY_LEN - 1, OnHistory)
	ON_COMMAND(ID_VIEW_FAVORITES_CENTER, OnViewFavorites)
	ON_COMMAND(ID_VIEW_FAVORITES, OnViewFavorites)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FAVORITES, OnUpdateViewFavorites)
	ON_COMMAND(ID_VIEW_HISTORY, OnViewHistory)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HISTORY, OnUpdateViewHistory)
	ON_UPDATE_COMMAND_UI(ID_LINK_1, OnUpdateLink)
	ON_COMMAND(ID_HELP_WEB_TUTORIAL, OnHelpWebTutorial)
	ON_COMMAND(ID_HELP_ONLINE_SUPPORT, OnHelpOnlineSupport)
	ON_COMMAND(ID_HELP_SEND_FEEDBACK, OnHelpSendFeedback)
	ON_COMMAND(ID_FILE_WORK_OFFLINE, OnWorkOffline)
	ON_UPDATE_COMMAND_UI(ID_FILE_WORK_OFFLINE, OnUpdateWorkOffline)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnFullScreen)
	ON_COMMAND(ID_VIEW_USE_LARGEICONS, OnViewUseLargeIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USE_LARGEICONS, OnUpdateViewUseLargeIcons)
	ON_COMMAND(ID_VIEW_ADD_TO_FAVORITES, OnAddFavoritesMenu)
	ON_MESSAGE(WM_MDIACTIVATE, OnMDIActivate)
	ON_MESSAGE(WM_DWMCOMPOSITIONCHANGED, OnDWMCompositionChanged)
	ON_COMMAND(ID_TOOLBAR_LOCKTHETOOLBARS, OnToolbarLockthetoolbars)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_LOCKTHETOOLBARS, OnUpdateToolbarLockthetoolbars)
	ON_COMMAND(IDC_ADDRESS, OnAddress)
	ON_CBN_SELENDOK(IDC_ADDRESS, OnAddress)
	ON_COMMAND(IDC_SEARCH, OnSearch)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_PROGRESS,	// progress bar
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

const int nStatusInfo = 0;
const int nStatusProgress = 1;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bMainToolbarMenu = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// enable Windows XP look (in other OS Office XP look will be used):
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CVisualManager));

	CBCGPDockManager::SetDockMode (BCGP_DT_STANDARD);

	CBCGPToolBar::m_dblLargeImageRatio = 1.2;

	CBCGPToolBar::SetSizes (CSize (22, 22), CSize (16, 16));
	CBCGPToolBar::SetMenuSizes (CBCGPToolBar::GetMenuButtonSize (), CSize (16, 16));

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	theApp.m_nColorMode = (WORD)dc.GetDeviceCaps (BITSPIXEL);

	//-----------------------
	// Create the addressbar:
	//-----------------------
	CBCGPToolbarComboBoxButton::SetFlatMode (FALSE);
	CBCGPToolbarEditBoxButton::SetFlatMode (FALSE);

	m_wndAddressBar.EnableNavigationButtons (ID_GOTO_BACK, ID_GOTO_FORWARD, ID_GOTO_HISTORY, ID_VIEW_HISTORY, 0);

	if (!m_wndAddressBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndAddressBar.LoadToolBar (IDR_ADDRESS_BAR, 
						theApp.m_nColorMode >= 16 ? IDB_ADDRESS_BAR : 0, 0, 0,
						theApp.m_nColorMode >= 16 ? IDB_ADDRESS_BAR_120 : 0))
	{
		TRACE0("Failed to create addressbar\n");
		return -1;      // fail to create
	}

	m_wndAddressBar.ReplaceButton (IDC_ADDRESS, CBCGPToolbarComboBoxButton (IDC_ADDRESS, -1, CBS_DROPDOWN));
	m_wndAddressBar.SetStretchID (IDC_ADDRESS);

	m_wndAddressBar.ReplaceButton (IDC_SEARCH, CBCGPToolbarEditBoxButton (IDC_SEARCH, -1));

	CMenu menu;
	VERIFY (menu.LoadMenu (IDR_SEARCH_POPUP));

	CMenu* pMenuSearch = menu.GetSubMenu (0);
	VERIFY (pMenuSearch != NULL);
	
	m_wndAddressBar.ReplaceButton (ID_GOTO_SEARCH, 
		CBCGPToolbarMenuButton (ID_GOTO_SEARCH, pMenuSearch->GetSafeHmenu (), 4));

	//--------------------
	// Create the menubar:
	//--------------------
	if (!m_wndMenuBar.CreateEx (this, TBSTYLE_TRANSPARENT))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}
	m_wndMenuBar.SetBarStyle ((m_wndMenuBar.GetBarStyle() & ~(CBRS_GRIPPER | CBRS_BORDER_ANY)) | CBRS_SIZE_DYNAMIC);
	m_wndMenuBar.EnableCustomizeButton (TRUE, (UINT)-1, _T(""));

	//------------------
	// Create links bar:
	//------------------

	if (!m_wndLinksBar.CreateEx (this, TBSTYLE_TRANSPARENT,
		dwDefaultToolbarStyle, CRect(0, 0, 0, 0), AFX_IDW_DIALOGBAR + 1))
	{
		TRACE0("Failed to create linksbar\n");
	}
	CString strLinksLabel;
	strLinksLabel.LoadString (IDS_LINKSBAR_NAME);
	m_wndLinksBar.SetWindowText (strLinksLabel);

	m_wndLinksBar.SetBarStyle (m_wndLinksBar.GetBarStyle() & ~(CBRS_GRIPPER | CBRS_BORDER_ANY));
	m_wndLinksBar.EnableCustomizeButton (TRUE, (UINT)-1, _T(""));

	//--------------
	// Create rebar:
	//--------------
	m_wndReBar.LockBars ();

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndMenuBar, NULL, NULL, 
				RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP | RBBS_BREAK | RBBS_HIDDEN) ||
		!m_wndReBar.AddBar(&m_wndLinksBar, strLinksLabel, NULL,
				RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP | RBBS_BREAK))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.AdjustLayout ();
	m_wndLinksBar.AdjustLayout ();

	//---------------
	// Create tabbar:
	//---------------
	if (!m_wndTabBar.Create (_T(""), this, FALSE, MAKEINTRESOURCE(IDD_TAB_BAR), 
		CBRS_SIZE_DYNAMIC | CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY, AFX_IDW_DIALOGBAR + 2,
		CBRS_BCGP_REGULAR_TABS, 0))
	{
		TRACE0("Failed to create addressbar\n");
		return -1;      // fail to create
	}

	EnableDocking(CBRS_ALIGN_ANY);
	m_wndReBar.EnableDocking (CBRS_TOP);
	m_wndTabBar.EnableDocking (CBRS_TOP);
	DockControlBar (&m_wndReBar);
	DockControlBar (&m_wndTabBar);
	ShowControlBar (&m_wndMenuBar, FALSE, FALSE, FALSE);
	ShowControlBar (&m_wndTabBar, TRUE, FALSE, FALSE);

	//-------------------
	// Create status bar:
	//-------------------
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create statusbar\n");
		return -1;      // fail to create
	}

	//------------------------------
	// First pane - image/animation:
	//------------------------------
	m_wndStatusBar.SetPaneStyle (nStatusInfo, SBPS_STRETCH | SBPS_NOBORDERS);
	m_wndStatusBar.SetPaneWidth (nStatusProgress, 80);

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndLinksBar.SetBarStyle(m_wndLinksBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	//-----------------------
	// Set up Favorites menu:
	//-----------------------
	VERIFY (theApp.m_Favorites.CreateMenu (m_menuFavotites));

	// Load control bar icons:
	CBCGPToolBarImages imagesExplorer;
	imagesExplorer.SetImageSize (CSize (16, 16));
	if (theApp.m_nColorMode >= 16)
	{
		imagesExplorer.SetTransparentColor (RGB (255, 0, 255));
	}
	imagesExplorer.Load 
		(
			theApp.m_nColorMode >= 16
				? IDB_EXPLORER_32
				: theApp.m_nColorMode >= 8 
					? IDB_EXPLORER_256
					: IDB_EXPLORER
		);

	if (!m_wndExplorer.Create (_T("Favorites Center"), this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_FAVORITES_CENTER,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}

	m_wndExplorer.SetIcon (imagesExplorer.ExtractIcon (0), FALSE);

	m_wndExplorer.EnableDocking(CBRS_ALIGN_LEFT);

	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar (&m_wndExplorer);

	// Enable windows manager:
	EnableWindowsDialog (ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	UINT nTicID = 0;
	if (theApp.m_nColorMode >= 16)
	{
		nTicID = IDR_TOOLBAR_IC_32;
	}
	else if (theApp.m_nColorMode >= 8)
	{
		nTicID = IDR_TOOLBAR_IC_256;
	}

	CBCGPToolBar::AddToolBarForImageCollection (
		IDR_TOOLBAR_IC,		// Toolbar (need for map "Command - Image")
		nTicID,	 // "Hot" images
		nTicID,	 // "Cold" images
		nTicID); // Menu images

	EnableFullScreenMode(ID_VIEW_FULLSCREEN);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CMDIFrameWnd::PreCreateWindow(cs))
	{
		return FALSE;
	}	

	cs.style |= FWS_PREFIXTITLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnDrawMenuImage (CDC* pDC,
								const CBCGPToolbarMenuButton* pMenuButton,
								const CRect& rectImage)
{
	if (theApp.m_Favorites.GetSysImages () == NULL)
	{
		return FALSE;
	}

	ASSERT_VALID (pDC);
	ASSERT_VALID (pMenuButton);

	int iIcon = -1;

	if (pMenuButton->m_nID >= ID_FAVORITE_FIRST &&
		pMenuButton->m_nID <= ID_FAVORITE_LAST)
	{
		iIcon = theApp.m_Favorites.GetIDIcon (pMenuButton->m_nID);
	}
	else if (IsFavoritesMenu (pMenuButton))	// Maybe, favorites folder?
	{
		iIcon = theApp.m_Favorites.GetFolderIcon ();
	}

	if (iIcon == -1)
	{
		return FALSE;	// Don't draw it!
	}

	::ImageList_Draw (theApp.m_Favorites.GetSysImages (), iIcon, 
		pDC->GetSafeHdc (), 
		rectImage.left + (rectImage.Width () - theApp.m_Favorites.GetSysImageSize ().cx) / 2, 
		rectImage.top + (rectImage.Height () - theApp.m_Favorites.GetSysImageSize ().cy) / 2, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CMainFrame::IsFavoritesMenu (const CBCGPToolbarMenuButton* pMenuButton)
{
	if (pMenuButton == NULL || pMenuButton->m_nID != (UINT) -1)
	{
		return FALSE;
	}

	ASSERT_VALID (pMenuButton);
	const CObList& lstCommands = pMenuButton->GetCommands ();
	
	for (POSITION pos = lstCommands.GetHeadPosition (); pos != NULL;)
	{
		CBCGPToolbarButton* pCmd = (CBCGPToolbarButton*) lstCommands.GetNext (pos);
		ASSERT_VALID (pCmd);

		if ((pCmd->m_nID >= ID_FAVORITE_FIRST &&
			pCmd->m_nID <= ID_FAVORITE_LAST) ||
			IsFavoritesMenu (DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton, pCmd)))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */
		);

	pDlgCust->Create ();
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

	return 0;
}

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM wp,LPARAM lp)
{
	CBCGPToolBar* pToolBar = DYNAMIC_DOWNCAST (CBCGPToolBar, 
											CWnd::FromHandlePermanent ((HWND) wp));
	m_bMainToolbarMenu = (
		pToolBar != NULL && pToolBar->GetDlgCtrlID () == AFX_IDW_TOOLBAR);

	CPoint point (BCG_GET_X_LPARAM(lp), BCG_GET_Y_LPARAM(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->Create (this, point.x, point.y, pPopup->Detach ());

	return 0;
}

BOOL CMainFrame::OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup)
{
    CBCGPMDIFrameWnd::OnShowPopupMenu (pMenuPopup);

	if (pMenuPopup == NULL)
	{
        return TRUE;
    }

	CBCGPPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	for (int i = 0; i < pMenuBar->GetCount (); i ++)
	{
		CBCGPToolbarButton* pButton = pMenuBar->GetButton (i);
		ASSERT_VALID (pButton);

		if (pButton->m_nID == ID_FAVORITES_DUMMY)
		{
			pMenuBar->ImportFromMenu (m_menuFavotites);
			pMenuPopup->SetMaxWidth (300);

			return TRUE;
		}

		if (pButton->m_nID == ID_VIEW_HISTORY)
		{
			CMenu menuHistory;
			menuHistory.LoadMenu (IDR_HISTORY_POPUP);

			CMenu* subMenu = menuHistory.GetSubMenu (0);
			ASSERT_VALID (subMenu);

			CBCGPIE7DemoView* pView = DYNAMIC_DOWNCAST(CBCGPIE7DemoView, GetActiveHTML ());
			if (pView != NULL)
			{
				CBCGPIE7DemoDoc* pDoc = pView->GetDocument ();
				if (pDoc != NULL)
				{
					_T_HistotyList lst;

					int index = 0;
					POSITION pos = NULL;

					pDoc->GetBackList (lst);
					for (pos = lst.GetHeadPosition (); pos != NULL;)
					{
						CHistoryObj* pObj = lst.GetNext (pos);
						ASSERT (pObj != NULL);

						subMenu->InsertMenu (index, MF_STRING | MF_BYPOSITION, 
							pObj->GetCommand (), pObj->GetTitle ());
						index++;
					}

					pDoc->GetFrwdList (lst);
					for (pos = lst.GetHeadPosition (); pos != NULL;)
					{
						CHistoryObj* pObj = lst.GetNext (pos);
						ASSERT (pObj != NULL);

						subMenu->InsertMenu (index, MF_STRING | MF_BYPOSITION, 
							pObj->GetCommand (), pObj->GetTitle ());
						index++;
					}

					if (index > 0)
					{
						subMenu->InsertMenu (index, MF_SEPARATOR | MF_BYPOSITION, 0, (LPCTSTR)NULL);
					}
				}
			}

			pMenuBar->ImportFromMenu (subMenu->GetSafeHmenu ());
			return TRUE;
		}
	}
	
	return TRUE;
}

void CMainFrame::OnWindowManager() 
{
	ShowWindowsDialog ();
}

CBCGPMDIChildWnd* CMainFrame::CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/)
{
	if (lpcszDocName != NULL && lpcszDocName [0] != '\0')
	{
		CDocument* pDoc = AfxGetApp()->OpenDocumentFile (lpcszDocName);

		if (pDoc != NULL)
		{
			POSITION pos = pDoc->GetFirstViewPosition();

			if (pos != NULL)
			{
				CView* pView = pDoc->GetNextView (pos);
				if (pView == NULL)
				{
					return NULL;
				}

				return DYNAMIC_DOWNCAST (CBCGPMDIChildWnd, pView->GetParent ());
			}   
		}
	}

	return NULL;
}

CHtmlView* CMainFrame::GetActiveHTML() const
{
	CHtmlView* pView = NULL;

	CMDIChildWnd* pFrame = MDIGetActive ();
	if (pFrame != NULL)
	{
		pView = DYNAMIC_DOWNCAST (CHtmlView, pFrame->GetActiveView ());
	}

	return pView;
}

void CMainFrame::OnViewMenuBar() 
{
	ShowControlBar (&m_wndMenuBar, !m_wndMenuBar.IsWindowVisible (), FALSE, TRUE);
	m_wndMenuBar.SetTempVisible (FALSE);
}

void CMainFrame::OnUpdateViewMenuBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndMenuBar.IsWindowVisible () && !m_wndMenuBar.IsTempVisible ());
}


void CMainFrame::OnViewLinksBar() 
{
	ShowControlBar (&m_wndLinksBar, !m_wndLinksBar.IsWindowVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewLinksBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndLinksBar.IsWindowVisible ());
}

void CMainFrame::SetAddress(LPCTSTR lpszUrl)
{
	// This is called when the browser has completely loaded the new location,
	// so make sure the text in the address bar is up to date and stop the
	// animation.

	CBCGPToolbarComboBoxButton* pAdress = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndAddressBar.GetButton (m_wndAddressBar.CommandToIndex (IDC_ADDRESS)));

	if (pAdress != NULL)
	{
		ASSERT_VALID (pAdress);
		pAdress->SetText (lpszUrl);
	}
//	m_wndAnimate.Stop();
}

void CMainFrame::StartAnimation()
{
	// Start the animation.  This is called when the browser begins to
	// navigate to a new location

//	m_wndAnimate.Play();
}

void CMainFrame::SetProgress (long nCurr, long nTotal)
{
	m_wndStatusBar.EnablePaneProgressBar (nStatusProgress, nTotal);

	if (nTotal >= 0)
	{
		m_wndStatusBar.SetPaneProgress (nStatusProgress, min (nTotal, max (0, nCurr)));
	}
	else
	{
		m_wndStatusBar.RedrawWindow ();
	}
}

void CMainFrame::OnNewTab()
{
	SendMessage (WM_COMMAND, ID_FILE_NEW);
}

void CMainFrame::OnNewWindow()
{
	TCHAR lpFileName[_MAX_PATH * 2];
	if (::GetModuleFileName (NULL, lpFileName, _MAX_PATH * 2) != 0)
	{
		::WinExec (lpFileName, SW_SHOWNORMAL);
	}
}

void CMainFrame::Navigate(LPCTSTR lpszUrl)
{
	CBCGPIE7DemoView* pView = DYNAMIC_DOWNCAST(CBCGPIE7DemoView, GetActiveHTML());
	if (pView == NULL)
	{
		CBCGPIE7DemoView::m_bGoAddress	= FALSE;
		OnNewTab();
		CBCGPIE7DemoView::m_bGoAddress	= TRUE;
		pView = DYNAMIC_DOWNCAST(CBCGPIE7DemoView, GetActiveHTML());
	}
	ASSERT_VALID(pView);

	pView->NavigateB(lpszUrl, 0, NULL);
}

// This demonstrates how we can use the Navigate2() function to load local files
// including local HTML pages, GIFs, AIFF files, etc.
void CMainFrame::OnFileOpen()
{
	CString str;
	str.LoadString(IDS_HTML_FILETYPES);

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, str);

	if(fileDlg.DoModal() == IDOK)
	{
		Navigate (fileDlg.GetPathName());
	}	
}

void CMainFrame::OnFavorite(UINT nID)
{
	Navigate (theApp.m_Favorites.GetURLofID (nID));
	SetFocus ();
}

void CMainFrame::OnHistory(UINT nID)
{
	CBCGPIE7DemoView* pView = DYNAMIC_DOWNCAST(CBCGPIE7DemoView, GetActiveHTML ());
	if (pView != NULL)
	{
		CBCGPIE7DemoDoc* pDoc = pView->GetDocument();
		ASSERT_VALID(pDoc);

		CHistoryObj* pObj = pDoc->Go (nID);
		ASSERT (pObj != NULL);

		Navigate (pObj->GetURL ());
	}
}

void CMainFrame::OnViewFavorites ()
{
	if (!m_wndExplorer.IsWindowVisible ())
	{
		ShowControlBar (&m_wndExplorer, TRUE, FALSE, TRUE);
	}

	if (!m_wndExplorer.IsFavorites ())
	{
		m_wndExplorer.SendMessage (WM_COMMAND, ID_VIEW_FAVORITES);
	}
}

void CMainFrame::OnUpdateViewFavorites (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (m_wndExplorer.IsWindowVisible () && m_wndExplorer.IsFavorites ());
}

void CMainFrame::OnViewHistory ()
{
	if (!m_wndExplorer.IsWindowVisible ())
	{
		ShowControlBar (&m_wndExplorer, TRUE, FALSE, TRUE);
	}

	if (m_wndExplorer.IsFavorites ())
	{
		m_wndExplorer.SendMessage (WM_COMMAND, ID_VIEW_HISTORY);
	}
}

void CMainFrame::OnUpdateViewHistory (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (m_wndExplorer.IsWindowVisible () && !m_wndExplorer.IsFavorites ());
}

void CMainFrame::OnUpdateLink(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

// these all go to specific web pages, just like Internet Explorer's help menu
void CMainFrame::OnHelpWebTutorial()
{
	CString str;
	str.LoadString(IDS_HELP_WEB_TUTORIAL);
	Navigate (str);
}

void CMainFrame::OnHelpOnlineSupport()
{
	CString str;
	str.LoadString(IDS_HELP_ONLINE_SUPPORT);
	Navigate (str);
}

void CMainFrame::OnHelpSendFeedback()
{
	CString str;
	str.LoadString(IDS_HELP_SEND_FEEDBACK);
	Navigate (str);
}

void CMainFrame::OnWorkOffline()
{
	CBCGPIE7DemoView::m_bWorkOffline = !CBCGPIE7DemoView::m_bWorkOffline;

	POSITION posTemplate = theApp.m_pDocManager->GetFirstDocTemplatePosition ();
	while (posTemplate != NULL)
	{
		CDocTemplate* pTemplate = theApp.m_pDocManager->GetNextDocTemplate (posTemplate);
		if (pTemplate != NULL)
		{
			POSITION posDocument = pTemplate->GetFirstDocPosition ();
			while (posDocument != NULL)
			{
				CDocument* pDocument = 	pTemplate->GetNextDoc (posDocument);
				if (pDocument != NULL)
				{
					POSITION posView = pDocument->GetFirstViewPosition ();
					while (posView != NULL)
					{
						CHtmlView* pView = DYNAMIC_DOWNCAST(CHtmlView, pDocument->GetNextView (posView));
						if (pView != NULL)
						{
							pView->SetOffline (CBCGPIE7DemoView::m_bWorkOffline);
						}
					}
				}
			}
		}
	}
}

void CMainFrame::OnUpdateWorkOffline(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (CBCGPIE7DemoView::m_bWorkOffline);
}

void CMainFrame::OnFullScreen()
{
	ShowFullScreen();

	if (!IsFullScreen ())
	{
		AdjustClientArea ();
	}
}

void CMainFrame::OnViewUseLargeIcons()
{
	theApp.m_bLargeIcons = !theApp.m_bLargeIcons;

	CBCGPToolBar::SetLargeIcons (theApp.m_bLargeIcons);

	RecalcLayout ();
	m_wndTabBar.Resize (TRUE);

	RedrawWindow (NULL);
}

void CMainFrame::OnUpdateViewUseLargeIcons(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
	pCmdUI->SetCheck (theApp.m_bLargeIcons);
}

void CMainFrame::OnAddFavoritesMenu()
{
	m_wndTabBar.ShowFavoritesMenu();
}

LRESULT CMainFrame::OnMDIActivate (WPARAM wParam, LPARAM lPAram)
{
	m_wndClientArea.SendMessage (WM_MDIACTIVATE, wParam, lPAram);

	CHtmlView* pView = GetActiveHTML ();
	if (pView != NULL)
	{
		SetAddress (pView->GetLocationURL ());
	}

	return 0L;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CRebarDC::GetInstance ().SetSize (CSize (cx, 200));

	CMDIFrameWnd::OnSize(nType, cx, cy);
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	BOOL isFullScreen = IsFullScreen();

	if (!isFullScreen)
	{
		if (pMsg->message == WM_SYSKEYUP)
		{
			BOOL  isCtrlPressed =  (0x8000 & GetKeyState(VK_CONTROL)) != 0;
			BOOL  isShiftPressed = (0x8000 & GetKeyState(VK_SHIFT)) != 0;

			if (pMsg->wParam == VK_MENU || 
				(pMsg->wParam == VK_F10 && !isCtrlPressed && !isShiftPressed))
			{
				if (m_wndMenuBar.IsTempVisible ())
				{
					OnViewMenuBar();
				}
				else if (!m_wndMenuBar.IsWindowVisible ())
				{
					OnViewMenuBar();
					m_wndMenuBar.SetFocus ();
					m_wndMenuBar.SetTempVisible (TRUE);
					return TRUE;
				}
			}
		}
	}	

	BOOL bRes = CMDIFrameWnd::PreTranslateMessage(pMsg);

	if (isFullScreen)
	{
		if (pMsg->message == WM_KEYDOWN &&
			pMsg->wParam == VK_ESCAPE && !IsFullScreen())
		{
			AdjustClientArea ();
		}
	}	

	return bRes;
}

LRESULT CMainFrame::OnDWMCompositionChanged(WPARAM,LPARAM)
{
	const BOOL bIsAero = globalData.DwmIsCompositionEnabled ();

	theApp.m_Style = bIsAero ? 2 : 1;

	m_wndTabBar.EnableAero (bIsAero);

	return Default ();
}

void CMainFrame::OnToolbarLockthetoolbars()
{
	m_wndReBar.LockBars (!m_wndReBar.IsLocked ());
}

void CMainFrame::OnUpdateToolbarLockthetoolbars(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (m_wndReBar.IsLocked ());
}

BOOL CMainFrame::GetToolbarButtonToolTipText (CBCGPToolbarButton* pButton, CString& strTTText)
{
	CLinkButton* pLinkBtn = NULL;

	ASSERT_VALID (pButton);

	if (pButton->m_nID == ID_LINK_1 &&
		(pLinkBtn = DYNAMIC_DOWNCAST (CLinkButton, pButton)) != NULL)
	{
		strTTText = pLinkBtn->GetURL ();
		return TRUE;
	}

	return FALSE;	// Default tooltip text
}

BOOL CMainFrame::OnMenuButtonToolHitTest (CBCGPToolbarButton* pButton, TOOLINFO* pTI)
{
	ASSERT_VALID (pButton);
	
	if (pButton->m_nID < ID_FAVORITE_FIRST ||
		pButton->m_nID > ID_FAVORITE_LAST)
	{
		return FALSE;
	}

	ASSERT (pTI != NULL);

	CString strText = theApp.m_Favorites.GetURLofID (pButton->m_nID);

	pTI->lpszText = (LPTSTR) ::calloc ((strText.GetLength () + 1), sizeof (TCHAR));
	lstrcpy (pTI->lpszText, strText);

	return TRUE;
}

void CMainFrame::OnAddress()
{
	CBCGPToolbarComboBoxButton* pAdress = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndAddressBar.GetButton (m_wndAddressBar.CommandToIndex (IDC_ADDRESS)));

	if (pAdress == NULL)
	{
		return;
	}

	ASSERT_VALID (pAdress);

	CString strAddress = pAdress->GetText ();

	Navigate (strAddress);

	if (pAdress->FindItem (strAddress) < 0)
	{
		pAdress->AddItem (strAddress);
	}
}

void CMainFrame::OnSearch ()
{
}
