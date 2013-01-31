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
// mainfrm.cpp : implementation of the CMainFrame class

#include "stdafx.h"
#include "drawcli.h"

#include "mainfrm.h"
#include "drawdoc.h"
#include "drawvw.h"

#include "RibbonListButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static int g_nSelectedObjectGroupIndex = 0;
static int g_nMaxLineWeight = 20;

static const CMainFrame::XStyle c_Styles[] =
{
	{RGB ( 64,  64,  64), RGB (  0,   0,   0)},
	{RGB ( 85, 140, 205), RGB ( 61,  97, 140)},
	{RGB (207,  86,  82), RGB (143,  61,  59)},
	{RGB (168, 203,  96), RGB (116, 141,  66)},
	{RGB (145, 113, 184), RGB ( 97,  77, 121)},
	{RGB ( 77, 179, 206), RGB ( 56, 129, 149)},
	{RGB (249, 151,  70), RGB (212, 107,  22)},
	{RGB (  0,   0,   0), (COLORREF)-1},
	{RGB ( 78, 128, 188), (COLORREF)-1},
	{RGB (191,  79,  76), (COLORREF)-1},
	{RGB (154, 186,  88), (COLORREF)-1},
	{RGB (127,  99, 161), (COLORREF)-1},
	{RGB ( 74, 171, 197), (COLORREF)-1},
	{RGB (246, 149,  69), (COLORREF)-1},
	{(COLORREF)-1, RGB (  0,   0,   0)},
	{(COLORREF)-1, RGB ( 78, 128, 188)},
	{(COLORREF)-1, RGB (191,  79,  76)},
	{(COLORREF)-1, RGB (154, 186,  88)},
	{(COLORREF)-1, RGB (127,  99, 161)},
	{(COLORREF)-1, RGB ( 74, 171, 197)},
	{(COLORREF)-1, RGB (246, 149,  69)},
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CBCGPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2007, ID_VIEW_APPLOOK_2007_3, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2007, ID_VIEW_APPLOOK_2007_3, OnUpdateAppLook)
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	ON_COMMAND(ID_MDI_MOVE_TO_NEXT_GROUP, OnMdiMoveToNextGroup)
	ON_COMMAND(ID_MDI_MOVE_TO_PREV_GROUP, OnMdiMoveToPrevGroup)
	ON_COMMAND(ID_MDI_NEW_HORZ_TAB_GROUP, OnMdiNewHorzTabGroup)
	ON_COMMAND(ID_MDI_NEW_VERT_GROUP, OnMdiNewVertGroup)
	ON_COMMAND(ID_MDI_CANCEL, OnMdiCancel)
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_REGISTERED_MESSAGE(BCGM_ON_HIGHLIGHT_RIBBON_LIST_ITEM, OnHighlightRibbonListItem)
	ON_COMMAND(ID_WINDOWS_MENU,OnDummy)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2007);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	OnAppLook (m_nAppLook);

	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}

	if (!CreateStatusBar ())
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//------------------------
	// Enable windows manager:
	//------------------------
	EnableWindowsDialog (ID_WINDOW_MANAGER, _T("&Windows..."), TRUE);

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers and overrides

void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2007:
	case ID_VIEW_APPLOOK_2007_1:
	case ID_VIEW_APPLOOK_2007_2:
	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:
		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2007:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_2007_1:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_2007_2:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
			break;

		case ID_VIEW_APPLOOK_2007_3:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
			break;
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));

		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;
	}

	CBCGPMDITabParams mdiTabParams;

	mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_VS2005;
	mdiTabParams.m_bAutoColor = TRUE;
	mdiTabParams.m_bDocumentMenu = TRUE;
	mdiTabParams.m_bActiveTabCloseButton = TRUE;

	EnableMDITabbedGroups (TRUE, mdiTabParams);

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnWindowManager() 
{
	ShowWindowsDialog ();
}

LRESULT CMainFrame::OnRibbonCustomize (WPARAM /*wp*/, LPARAM /*lp*/)
{
	ShowOptions (0);
	return 1;
}

void CMainFrame::OnToolsOptions()
{
	ShowOptions (0);
}

BOOL CMainFrame::OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop)
{
	CMenu menu;
	VERIFY(menu.LoadMenu (bDrop ? IDR_POPUP_DROP_MDITABS : IDR_POPUP_MDITABS));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	if ((dwAllowedItems & BCGP_MDI_CREATE_HORZ_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_HORZ_TAB_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CREATE_VERT_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_VERT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_NEXT) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_NEXT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_PREV) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_PREV_GROUP, MF_BYCOMMAND);
	}

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->SetAutoDestroy (FALSE);
	pPopupMenu->Create (this, point.x, point.y, pPopup->GetSafeHmenu ());

	return TRUE;
}

void CMainFrame::OnMdiMoveToNextGroup() 
{
	MDITabMoveToNextGroup ();
}

void CMainFrame::OnMdiMoveToPrevGroup() 
{
	MDITabMoveToNextGroup (FALSE);
}

void CMainFrame::OnMdiNewHorzTabGroup() 
{
	MDITabNewGroup (FALSE);
}

void CMainFrame::OnMdiNewVertGroup() 
{
	MDITabNewGroup ();
}

void CMainFrame::OnMdiCancel() 
{
	// TODO: Add your command handler code here
	
}
BOOL CMainFrame::OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup)
{
	BOOL bRes = CBCGPMDIFrameWnd::OnShowPopupMenu (pMenuPopup);

	if (pMenuPopup != NULL && !pMenuPopup->IsCustomizePane())
	{
		AdjustObjectSubmenu (pMenuPopup);
	}

	return bRes;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame helpers
BOOL CMainFrame::CreateRibbonBar ()
{
	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	// Load panel images:
	m_PanelImages.SetImageSize (CSize (16, 16));
	m_PanelImages.Load (IDB_RIBBON_ICONS);

	// Init main button:
	InitMainButton ();

	InitHomeCategory ();
	InitViewCategory ();
	InitTabButtons ();

	AddContextTab_Format ();

	// Init QAT state
	// Add quick access toolbar commands:
	CBCGPRibbonQATDefaultState qatState;

	qatState.AddCommand (ID_FILE_NEW, FALSE);
	qatState.AddCommand (ID_FILE_OPEN, FALSE);
	qatState.AddCommand (ID_FILE_SAVE);
	qatState.AddCommand (ID_FILE_PRINT_DIRECT);
	qatState.AddCommand (ID_FILE_PRINT_PREVIEW, FALSE);
	qatState.AddCommand (ID_EDIT_UNDO);

	// Set the state
	m_wndRibbonBar.SetQuickAccessDefaultState (qatState);

	return TRUE;
}

BOOL CMainFrame::CreateStatusBar ()
{
	if (!m_wndStatusBar.Create(this))
	{
		return FALSE;
	}

	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE_OBJECTCOUNT, _T("Object Count: None"), TRUE), _T("Object Count: None"));

	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE_SELECTEDOBJECTCOUNT, _T("Selected Count: None"), TRUE), _T("Selected Count: None"));

	{
		CBCGPRibbonButtonsGroup* pSBGroup = new CBCGPRibbonButtonsGroup;

		CBCGPToolBarImages images;
		images.SetImageSize (CSize (14, 14));
		if (images.Load (IDB_STATUSBAR_1))
		{
			pSBGroup->SetImages (&images, NULL, NULL);
		}

		pSBGroup->AddButton (new CBCGPRibbonButton (ID_FILE_PRINT_PREVIEW, _T(""), 0));
		pSBGroup->AddButton (new CBCGPRibbonButton (ID_FILE_SUMMARYINFO, _T(""), 1));

		m_wndStatusBar.AddExtendedElement (pSBGroup, _T("View Shortcuts"));
	}

	{
		CBCGPRibbonButtonsGroup* pSBGroup = new CBCGPRibbonButtonsGroup;

		CBCGPToolBarImages images;
		images.SetImageSize (CSize (14, 14));
		if (images.Load (IDB_STATUSBAR_2))
		{
			pSBGroup->SetImages (&images, NULL, NULL);
		}

		pSBGroup->AddButton (new CBCGPRibbonButton (ID_VIEW_GRID, _T (""), 0));
		pSBGroup->AddButton (new CBCGPRibbonButton (ID_VIEW_SHOWOBJECTS, _T (""), 1));

		m_wndStatusBar.AddExtendedElement (pSBGroup, _T("View Shortcuts"));
	}

	return TRUE;
}

void CMainFrame::InitMainButton ()
{
	m_MainButton.SetImage (IDB_RIBBON_MAIN);
	m_MainButton.SetToolTipText (_T("File"));
	m_MainButton.SetText (_T("\nf"));

	m_wndRibbonBar.SetMainButton (&m_MainButton, CSize (45, 45));

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("File"), IDB_RIBBON_FILESMALL, IDB_RIBBON_FILELARGE);
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_NEW, _T("&New"), 0, 0));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_OPEN, _T("&Open..."), 1, 1));
	
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE, _T("&Save"), 2, 2));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("Save &As..."), 3, 3));

	CBCGPRibbonButton* pBtnPrint = new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 4, 4);

	pBtnPrint->AddSubItem (new CBCGPRibbonLabel (_T("Preview and print the document")));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_DIRECT, _T("&Quick Print"), 7, 7, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_PREVIEW, _T("Print Pre&view"), 6, 6, TRUE));

	pBtnPrint->SetKeys (_T("p"), _T("w"));
	pMainPanel->Add (pBtnPrint);

	pMainPanel->AddSeparator ();
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SEND_MAIL, _T("Sen&d..."), 8, 8));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SUMMARYINFO, _T("Summary &Info..."), 9, 9));

	pMainPanel->AddSeparator ();
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_CLOSE, _T("&Close"), 5, 5));

	pMainPanel->AddRecentFilesList (_T("Recent Documents"));
	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_TOOLS_OPTIONS, _T("Opt&ions"), 10));
	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_APP_EXIT, _T("E&xit"), 11));
}

void CMainFrame::InitHomeCategory ()
{
	CreateDocumentColors ();

	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("&Home"),
		IDB_RIBBON_HOMESMALL,
		IDB_RIBBON_HOMELARGE);

	// Create "Clipboard" panel:
	CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel (
		_T("Clipboard\nzc"), m_PanelImages.ExtractIcon (0));

	CBCGPRibbonButton* pBtnPaste = new CBCGPRibbonButton (ID_EDIT_PASTE, _T("Paste\nv"), 0, 0);
	pPanelClipboard->Add (pBtnPaste);

	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CUT, _T("Cut\nx"), 1));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_COPY, _T("Copy\nc"), 2));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CLEAR, _T("Delete\nt"), 3));

	// Create "Operations" panel
	CBCGPRibbonPanel* pPanelOperations = pCategory->AddPanel (
		_T("Operations\nzo"), m_PanelImages.ExtractIcon (1));

	CBCGPRibbonColorButton* pBtnPaperColor = new CBCGPRibbonColorButton (ID_VIEW_PAPERCOLOR, _T("Paper Color\ng"), TRUE, 13, 1);
	pBtnPaperColor->SetAlwaysLargeImage ();
	pBtnPaperColor->SetDefaultCommand (FALSE);
	pBtnPaperColor->EnableAutomaticButton (_T("&Automatic"), RGB (255, 255, 255));
	pBtnPaperColor->EnableOtherButton (_T("&More Colors..."), _T("More Colors"));
	pBtnPaperColor->SetColumns (10);
	pBtnPaperColor->SetColorBoxSize (CSize (17, 17));
	pBtnPaperColor->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
	pBtnPaperColor->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE);
	pBtnPaperColor->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);

	pPanelOperations->Add (pBtnPaperColor);

	pPanelOperations->Add (new CBCGPRibbonButton (ID_EDIT_SELECT_ALL, _T("Select All\na"), 4));
	pPanelOperations->Add (new CBCGPRibbonButton (ID_OLE_INSERT_NEW, _T("New Object...\no"), 5));
	pPanelOperations->Add (new CBCGPRibbonButton (ID_OLE_EDIT_LINKS, _T ("Links...\ni"), 6));

	// Create "Draw" panel
	CBCGPRibbonPanel* pPanelDraw = pCategory->AddPanel (
		_T("Draw\nzd"), m_PanelImages.ExtractIcon (2));

	pPanelDraw->Add (new CBCGPRibbonButton (ID_DRAW_SELECT, _T ("Select\ns"), 7));
	pPanelDraw->Add (new CBCGPRibbonButton (ID_DRAW_LINE, _T ("Line\nl"), 8));
	pPanelDraw->Add (new CBCGPRibbonButton (ID_DRAW_RECT, _T ("Rectangle\nr"), 9));
	pPanelDraw->Add (new CBCGPRibbonButton (ID_DRAW_ROUNDRECT, _T ("Round Rectangle\nn"), 10));
	pPanelDraw->Add (new CBCGPRibbonButton (ID_DRAW_ELLIPSE, _T ("Ellipse\ne"), 11));
	pPanelDraw->Add (new CBCGPRibbonButton (ID_DRAW_POLYGON, _T ("Polygon\ny"), 12));

	// Create "Arrange" panel
	CBCGPRibbonPanel* pPanelArrange = pCategory->AddPanel (
		_T("Arrange\nzj"), m_PanelImages.ExtractIcon (3));

	pPanelArrange->Add (new CBCGPRibbonButton (ID_OBJECT_MOVETOFRONT, _T ("Move to Front\nmf"), 15, 3));
	pPanelArrange->Add (new CBCGPRibbonButton (ID_OBJECT_MOVEFORWARD, _T ("Move Forward\nmw"), 17, 5));
	pPanelArrange->Add (new CBCGPRibbonButton (ID_OBJECT_MOVEBACK, _T ("Move Backward\nmd"), 18, 6));
	pPanelArrange->Add (new CBCGPRibbonButton (ID_OBJECT_MOVETOBACK, _T ("Move to Back\nmb"), 16, 4));
	
	// Add not-in-ribbon commands
	CBCGPRibbonButton* pUndo = new CBCGPRibbonButton (ID_EDIT_UNDO, _T("Undo"), 20);
	pCategory->AddHidden (pUndo);
}

void CMainFrame::InitViewCategory ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("&View"),
		IDB_RIBBON_VIEWSMALL,
		IDB_RIBBON_VIEWLARGE);

	// Create "Show/Hide" panel:
	CBCGPRibbonPanel* pPanelShow = pCategory->AddPanel (
		_T("Show/Hide\nzs"), 
		m_PanelImages.ExtractIcon (4));

	pPanelShow->Add (new CBCGPRibbonCheckBox (ID_VIEW_GRID, _T ("Grid Lines\ng")));
	pPanelShow->Add (new CBCGPRibbonCheckBox (ID_VIEW_SHOWOBJECTS, _T ("Show Objects\ns")));

	// Create "Window" panel:
	CBCGPRibbonPanel* pPanelWindow = pCategory->AddPanel (
		_T("Window\nzw"), 
		m_PanelImages.ExtractIcon (5));

	pPanelWindow->Add (new CBCGPRibbonButton (ID_WINDOW_NEW, _T("New Window\nn"), 0, 0));

	CBCGPRibbonButton* pBtnWindows = new CBCGPRibbonButton (ID_WINDOWS_MENU, _T("Switch Windows\ns"), 1, 1);
	pBtnWindows->SetMenu (IDR_WINDOWS_MENU, TRUE);
	pBtnWindows->SetDefaultCommand (FALSE);
	pPanelWindow->Add (pBtnWindows);

	// Add the launch button at the bottom of the panel:
	pPanelWindow->EnableLaunchButton (ID_WINDOW_MANAGER, 1, _T("W"));
}

void CMainFrame::InitTabButtons ()
{
	// Add "Style" button to the right of tabs:
	CBCGPRibbonButton* pStyleButton = new CBCGPRibbonButton ((UINT) -1, _T("Style\ns"));
	pStyleButton->SetMenu (IDR_THEME_MENU, TRUE /* Right align */);

	m_wndRibbonBar.AddToTabs (pStyleButton);

	// Add "About" button to the right of tabs:
	m_wndRibbonBar.AddToTabs (new CBCGPRibbonButton (ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (6)));

}

void CMainFrame::AddContextTab_Format ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddContextCategory (_T("Format"),
		_T("Drawing tools"), ID_FORMAT_CONTEXT_TAB, BCGPCategoryColor_Orange,
		IDB_RIBBON_FORMATSMALL, IDB_RIBBON_FORMATLARGE);
	pCategory->SetKeys (_T("jd"));

	// Create "Styles" panel
	CBCGPRibbonPanel* pPanelStyles = pCategory->AddPanel (
		_T("Styles\nzs"), m_PanelImages.ExtractIcon (8));

	CBCGPRibbonPaletteButton* pBtnStyles = new CBCGPRibbonPaletteButton (ID_OBJECT_STYLES, _T("Styles\nk"), 0, 0, IDB_STYLES, 40);
	pBtnStyles->SetIconsInRow (7);
	pBtnStyles->EnableMenuResize (TRUE, TRUE);
	pPanelStyles->Add (pBtnStyles);

	CBCGPRibbonColorButton* pBtnFillColor = new CBCGPRibbonColorButton (ID_OBJECT_FILLCOLOR, _T("Fill Color\nsf"), FALSE, 1, -1);
	pBtnFillColor->SetDefaultCommand (FALSE);
	pBtnFillColor->EnableAutomaticButton (_T("&Automatic"), RGB (128, 128, 128));
	pBtnFillColor->EnableOtherButton (_T("&More Fill Colors..."), _T("More Fill Colors"));
	pBtnFillColor->SetColumns (10);
	pBtnFillColor->SetColorBoxSize (CSize (17, 17));
	pBtnFillColor->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
	pBtnFillColor->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE);
	pBtnFillColor->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);
	pBtnFillColor->AddSubItem (new CBCGPRibbonButton (ID_OBJECT_NOFILL, _T("&No Fill\nn"), 2));
	pBtnFillColor->SetColor ((COLORREF)-1);
	pPanelStyles->Add (pBtnFillColor);

	CBCGPRibbonColorButton* pBtnLineColor = new CBCGPRibbonColorButton (ID_OBJECT_LINECOLOR, _T("Line Color\nso"), FALSE, 3, -1);
	pBtnLineColor->SetDefaultCommand (FALSE);
	pBtnLineColor->EnableAutomaticButton (_T("&Automatic"), RGB (0, 0, 0));
	pBtnLineColor->EnableOtherButton (_T("&More Line Colors..."), _T("More Line Colors"));
	pBtnLineColor->SetColumns (10);
	pBtnLineColor->SetColorBoxSize (CSize (17, 17));
	pBtnLineColor->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
	pBtnLineColor->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE);
	pBtnLineColor->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);
	pBtnLineColor->AddSubItem (new CBCGPRibbonButton (ID_OBJECT_NOLINE, _T("&No Line\nn"), 2));
	pBtnLineColor->SetColor ((COLORREF)-1);
	pPanelStyles->Add (pBtnLineColor);

	CStringArray sa;
	sa.Add (_T("1 pt"));
	sa.Add (_T("2 pt"));
	sa.Add (_T("3 pt"));
	sa.Add (_T("4 pt"));
	sa.Add (_T("5 pt"));
	sa.Add (_T("6 pt"));
	sa.Add (_T("7 pt"));
	CRibbonListButton* pBtnLineWeight = new CRibbonListButton (ID_OBJECT_LINEWEIGHT, _T ("Line Weight\nsw"), 4, -1, IDB_LINEWEIGHT, 96, sa);
	pBtnLineWeight->AddSubItem (
		new CBCGPRibbonButton (ID_OBJECT_LINEWEIGHT_MORE, _T("More &Lines..."), 5, -1));
	pBtnLineWeight->EnableMenuResize (TRUE, TRUE);	// Vertical only
	pPanelStyles->Add (pBtnLineWeight);

	pPanelStyles->EnableLaunchButton (ID_OBJECT_PROPERTIES, 6, _T("fa"));

	// Create "Arrange" panel
	CBCGPRibbonPanel* pPanelArrange = pCategory->AddPanel (
		_T("Arrange\nzj"), m_PanelImages.ExtractIcon (3));

	pPanelArrange->Add (new CBCGPRibbonButton (ID_OBJECT_MOVETOFRONT, _T ("Move to Front\nmf"), 7, 1));
	pPanelArrange->Add (new CBCGPRibbonButton (ID_OBJECT_MOVEFORWARD, _T ("Move Forward\nmw"), 9, 3));
	pPanelArrange->Add (new CBCGPRibbonButton (ID_OBJECT_MOVEBACK, _T ("Move Backward\nmd"), 10, 4));
	pPanelArrange->Add (new CBCGPRibbonButton (ID_OBJECT_MOVETOBACK, _T ("Move to Back\nmb"), 8, 2));
}

void CMainFrame::AdjustObjectSubmenu (CBCGPPopupMenu* pMenuPopup)
{
	ASSERT (pMenuPopup != NULL);

	if (pMenuPopup->GetParentPopupMenu () != NULL)
	{
		return;
	}

	CBCGPPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT (pMenuBar != NULL);

	int iIndex = pMenuBar->CommandToIndex (ID_OLE_VERB_FIRST);
	if (iIndex < 0)
	{
		return;
	}

	CFrameWnd* pFrame = GetActiveFrame ();

	if (pFrame == NULL)
	{
		return;
	}

	CDrawDoc* pDoc = (CDrawDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID (pDoc);

	// check for single selection
	COleClientItem* pItem = pDoc->GetPrimarySelectedItem(pFrame->GetActiveView());
	if (pItem == NULL || pItem->GetType() == OT_STATIC)
	{
		// no selection, or is 'static' item
		return;
	}

	// only include Convert... if there is a handler for ID_OLE_EDIT_CONVERT
	UINT nConvertID = ID_OLE_EDIT_CONVERT;
	AFX_CMDHANDLERINFO info;
	if (!pDoc->OnCmdMsg(ID_OLE_EDIT_CONVERT, CN_COMMAND, NULL, &info))
		nConvertID = 0;

	HMENU hMenu = pMenuBar->ExportToMenu ();
	ASSERT(hMenu != NULL);

	// update the menu
	AfxOleSetEditMenu(pItem,
		CMenu::FromHandle (hMenu), iIndex,
		ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, nConvertID);

	pMenuBar->ImportFromMenu (hMenu);
	::DestroyMenu (hMenu);
}

void CMainFrame::ShowOptions (int nPage)
{
	// Create "Customize" page:
	CBCGPRibbonCustomizePage pageCustomize (&m_wndRibbonBar);

	// Add "popular" items:
	CList<UINT, UINT> lstPopular;

	lstPopular.AddTail (ID_FILE_NEW);
	lstPopular.AddTail (ID_FILE_OPEN);
	lstPopular.AddTail (ID_FILE_SAVE);
	lstPopular.AddTail (ID_FILE_PRINT_PREVIEW);
	lstPopular.AddTail (ID_FILE_PRINT_DIRECT);
	lstPopular.AddTail (ID_EDIT_UNDO);

	pageCustomize.AddCustomCategory (_T("Popular Commands"), lstPopular);

	// Add hidden commands:
	CList<UINT,UINT> lstHidden;
	m_wndRibbonBar.GetItemIDsList (lstHidden, TRUE);

	pageCustomize.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);

	// Add all commands:
	CList<UINT,UINT> lstAll;
	m_wndRibbonBar.GetItemIDsList (lstAll);

	pageCustomize.AddCustomCategory (_T("All Commands"), lstAll);

	// Create property sheet:
	CBCGPPropertySheet propSheet (_T("Options"), this, nPage);
	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	propSheet.SetLook (CBCGPPropertySheet::PropSheetLook_List, 124 /* List width */);

	propSheet.AddPage (&pageCustomize);

	if (propSheet.DoModal() != IDOK)
	{
		return;
	}
}

void CMainFrame::UpdateUI (CDrawView* pCurrView)
{
	// Update Status Bar

	int nCount = 0;
	int nSelected = 0;

	if (pCurrView != NULL)
	{
		CDrawDoc* pCurrDoc = pCurrView->GetDocument ();
		nCount = (int) pCurrDoc->GetObjects ()->GetCount ();
		nSelected = (int) pCurrView->m_selection.GetCount ();
	}

	UpdateStatusBarCountPane (ID_STATUSBAR_PANE_OBJECTCOUNT, _T ("Object Count"), nCount);
	UpdateStatusBarCountPane (ID_STATUSBAR_PANE_SELECTEDOBJECTCOUNT, _T ("Selected Count"), nSelected);

	m_wndStatusBar.Invalidate ();
	m_wndStatusBar.UpdateWindow ();
}

void CMainFrame::UpdateContextTab (CDrawView* pCurrView)
{
	bool bEnable = pCurrView != NULL && pCurrView->m_selection.GetCount () > 0;

	SetRibbonContextCategory (bEnable ? ID_FORMAT_CONTEXT_TAB : 0);

	if (bEnable)
	{
		UpdateContextTabFromObject (pCurrView->m_selection);
	}
}

void CMainFrame::UpdateStatusBarCountPane (int nID, CString strText, int nCount)
{
	CBCGPBaseRibbonElement* pPane = m_wndStatusBar.FindByID (nID);
	if (pPane != NULL)
	{
		if (nCount == 0)
		{
			strText += _T (": None");
		}
		else
		{
			CString strFormatted;
			strFormatted.Format (_T (": %d"), nCount);

			strText += strFormatted;
		}
		pPane->SetText (strText);
	}

}

void CMainFrame::UpdateContextTabFromObject (CDrawObjList& list)
{
	int count = (int) list.GetCount ();
	if (count == 0)
	{
		return;
	}

	COLORREF clrFill = (COLORREF)-1;
	COLORREF clrLine = (COLORREF)-1;
	int nLineWeight  = -1;
	if (count == 1)
	{
		CDrawObj* pObj = list.GetHead ();
		if (pObj->CanChangeFillColor () && pObj->IsEnableFill ())
		{
			clrFill = pObj->GetFillColor ();
		}
		if (pObj->CanChangeLineColor () && pObj->IsEnableLine ())
		{
			clrLine = pObj->GetLineColor ();
		}
		if (pObj->CanChangeLineWeight () && pObj->IsEnableLine ())
		{
			nLineWeight = pObj->GetLineWeight () - 1;
		}
	}

	{
		CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> arButtons;
		m_wndRibbonBar.GetElementsByID (ID_OBJECT_FILLCOLOR, arButtons);

		if (arButtons.GetSize () > 0)
		{
			for (int i = 0; i < arButtons.GetSize (); i++)
			{
				CBCGPRibbonColorButton* pButton = DYNAMIC_DOWNCAST
					(
						CBCGPRibbonColorButton,
						arButtons[i]
					);
				pButton->SetColor (clrFill);
			}
		}	
	}

	{
		CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> arButtons;
		m_wndRibbonBar.GetElementsByID (ID_OBJECT_LINECOLOR, arButtons);

		if (arButtons.GetSize () > 0)
		{
			for (int i = 0; i < arButtons.GetSize (); i++)
			{
				CBCGPRibbonColorButton* pButton = DYNAMIC_DOWNCAST
					(
						CBCGPRibbonColorButton,
						arButtons[i]
					);
				pButton->SetColor (clrLine);
			}
		}	
	}

	{
		CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> arButtons;
		m_wndRibbonBar.GetElementsByID (ID_OBJECT_LINEWEIGHT, arButtons);

		if (arButtons.GetSize () > 0)
		{
			for (int i = 0; i < arButtons.GetSize (); i++)
			{
				CRibbonListButton* pButton = DYNAMIC_DOWNCAST
					(
						CRibbonListButton,
						arButtons[i]
					);
				pButton->SelectItem (nLineWeight);
			}
		}	
	}

	m_wndRibbonBar.RedrawWindow ();
}

void CMainFrame::CreateDocumentColors ()
{
	typedef struct 
	{
		COLORREF	color;
		TCHAR*		szName;
	} 
	ColorTableEntry;

	int i = 0;
	int nNumColours = 0;

	static ColorTableEntry colorsMain [] = 
	{
		{	RGB (255, 255, 255),	_T("White, Background 1")	},
		{	RGB (0, 0, 0),			_T("Black, Text 1")			},
		{	RGB (238, 236, 225),	_T("Tan, Background 2")		},
		{	RGB (31, 73, 125),		_T("Dark Blue, Text 2")		},
		{	RGB (79, 129, 189),		_T("Blue, Accent 1")		},
		{	RGB (192, 80, 77),		_T("Red, Accent 2")			},
		{	RGB (155, 187, 89),		_T("Olive Green, Accent 3")	},
		{	RGB (128, 100, 162),	_T("Purple, Accent 4")		},
		{	RGB (75, 172, 198),		_T("Aqua, Accent 5")		},
		{	RGB (245, 150, 70),		_T("Orange, Accent 6")		}
	};

	static ColorTableEntry colorsAdditional [] = 
	{
		{	RGB (242, 242, 242),	_T("White, Background 1, Darker 5%")	},
		{	RGB (127, 127, 127),	_T("Black, Text 1, Lighter 50%")		},
		{	RGB (214, 212, 202),	_T("Tan, Background 2, Darker 10%")		},
		{	RGB (210, 218, 229),	_T("Dark Blue, Text 2, Lighter 80%")	},
		{	RGB (217, 228, 240),	_T("Blue, Accent 1, Lighter 80%")		},
		{	RGB (244, 219, 218),	_T("Red, Accent 2, Lighter 80%")		},
		{	RGB (234, 241, 221),	_T("Olive Green, Accent 3, Lighter 80%")},
		{	RGB (229, 223, 235),	_T("Purple, Accent 4, Lighter 80%")		},
		{	RGB (216, 237, 242),	_T("Aqua, Accent 5, Lighter 80%")		},
		{	RGB (255, 234, 218),	_T("Orange, Accent 6, Lighter 80%")		},

		{	RGB (215, 215, 215),	_T("White, Background 1, Darker 15%")	},
		{	RGB (89, 89, 89),		_T("Black, Text 1, Lighter 35%")		},
		{	RGB (177, 176, 167),	_T("Tan, Background 2, Darker 25%")		},
		{	RGB (161, 180, 201),	_T("Dark Blue, Text 2, Lighter 60%")	},
		{	RGB (179, 202, 226),	_T("Blue, Accent 1, Lighter 60%")		},
		{	RGB (233, 184, 182),	_T("Red, Accent 2, Lighter 60%")		},
		{	RGB (213, 226, 188),	_T("Olive Green, Accent 3, Lighter 60%")},
		{	RGB (203, 191, 215),	_T("Purple, Accent 4, Lighter 60%")		},
		{	RGB (176, 220, 231),	_T("Aqua, Accent 5, Lighter 60%")		},
		{	RGB (255, 212, 181),	_T("Orange, Accent 6, Lighter 60%")		},

		{	RGB (190, 190, 190),	_T("White, Background 1, Darker 25%")	},
		{	RGB (65, 65, 65),		_T("Black, Text 1, Lighter 25%")		},
		{	RGB (118, 117, 112),	_T("Tan, Background 2, Darker 35%")		},
		{	RGB (115, 143, 175),	_T("Dark Blue, Text 2, Lighter 40%")	},
		{	RGB (143, 177, 213),	_T("Blue, Accent 1, Lighter 40%")		},
		{	RGB (222, 149, 147),	_T("Red, Accent 2, Lighter 40%")		},
		{	RGB (192, 213, 155),	_T("Olive Green, Accent 3, Lighter 40%")},
		{	RGB (177, 160, 197),	_T("Purple, Accent 4, Lighter 40%")		},
		{	RGB (137, 203, 218),	_T("Aqua, Accent 5, Lighter 40%")		},
		{	RGB (255, 191, 145),	_T("Orange, Accent 6, Lighter 40%")		},

		{	RGB (163, 163, 163),	_T("White, Background 1, Darker 35%")	},
		{	RGB (42, 42, 42),		_T("Black, Text 1, Lighter 15%")		},
		{	RGB (61, 61, 59),		_T("Tan, Background 2, Darker 50%")		},
		{	RGB (20, 57, 92),		_T("Dark Blue, Text 2, Darker 25%")		},
		{	RGB (54, 96, 139),		_T("Blue, Accent 1, Darker 25%")		},
		{	RGB (149, 63, 60),		_T("Red, Accent 2, Darker 25%")			},
		{	RGB (114, 139, 71),		_T("Olive Green, Accent 3, Darker 25%")	},
		{	RGB (97, 76, 119),		_T("Purple, Accent 4, Darker 25%")		},
		{	RGB (41, 128, 146),		_T("Aqua, Accent 5, Darker 25%")		},
		{	RGB (190, 112, 59),		_T("Orange, Accent 6, Darker 25%")		},

		{	RGB (126, 126, 126),	_T("White, Background 1, Darker 50%")	},
		{	RGB (20, 20, 20),		_T("Black, Text 1, Lighter 5%")			},
		{	RGB (29, 29, 28),		_T("Tan, Background 2, Darker 90%")		},
		{	RGB (17, 40, 64),		_T("Dark Blue, Text 2, Darker 50%")		},
		{	RGB (38, 66, 94),		_T("Blue, Accent 1, Darker 50%")		},
		{	RGB (100, 44, 43),		_T("Red, Accent 2, Darker 50%")			},
		{	RGB (77, 93, 49),		_T("Olive Green, Accent 3, Darker 50%")	},
		{	RGB (67, 53, 81),		_T("Purple, Accent 4, Darker 50%")		},
		{	RGB (31, 86, 99),		_T("Aqua, Accent 5, Darker 50%")		},
		{	RGB (126, 77, 42),		_T("Orange, Accent 6, Darker 50%")		},
	};

	static ColorTableEntry colorsStandard [] = 
	{
		{	RGB (200, 15, 18),		_T("Dark Red")		},
		{	RGB (255, 20, 24),		_T("Red")			},
		{	RGB (255, 191, 40),		_T("Orange")		},
		{	RGB (255, 255, 49),		_T("Yellow")		},
		{	RGB (138, 207, 87),		_T("Light Green")	},
		{	RGB (0, 175, 84),		_T("Green")			},
		{	RGB (0, 174, 238),		_T("Light Blue")	},
		{	RGB (0, 111, 189),		_T("Blue")			},
		{	RGB (0, 36, 95),		_T("Black")			},
		{	RGB (114, 50, 157),		_T("Purple")		},
	};

	m_lstMainColors.RemoveAll ();
	nNumColours = sizeof (colorsMain) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstMainColors.AddTail (colorsMain [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsMain [i].color, colorsMain [i].szName);
	};

	m_lstAdditionalColors.RemoveAll ();
	nNumColours = sizeof (colorsAdditional) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstAdditionalColors.AddTail (colorsAdditional [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsAdditional [i].color, colorsAdditional [i].szName);
	};

	m_lstStandardColors.RemoveAll ();
	nNumColours = sizeof (colorsStandard) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstStandardColors.AddTail (colorsStandard [i].color);
		CBCGPRibbonColorButton::SetColorName (colorsStandard [i].color, colorsStandard [i].szName);
	};
}

COLORREF CMainFrame::GetColorFromColorButton (int nButtonID)
{
	CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> arButtons;

	m_wndRibbonBar.GetElementsByID (nButtonID, arButtons);

	if (arButtons.GetSize () == 0)
	{
		return (COLORREF) -1;
	}

	CBCGPRibbonColorButton* pColorButton = (CBCGPRibbonColorButton*)arButtons.GetAt (0);

	COLORREF clr = pColorButton->GetColor ();
	if (clr == (COLORREF)-1)
	{
		clr = pColorButton->GetAutomaticColor ();
	}

	return clr;
}

int CMainFrame::GetWeightFromLineWeight (int nButtonID)
{
	CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> arButtons;

	m_wndRibbonBar.GetElementsByID (nButtonID, arButtons);

	if (arButtons.GetSize () == 0)
	{
		return -1;
	}

	int weight = -1;
	CBCGPRibbonPaletteButton* pBtn = DYNAMIC_DOWNCAST (CBCGPRibbonPaletteButton, arButtons.GetAt (0));
	if (pBtn != NULL && pBtn->GetSelectedItem () != -1)
	{
		weight = pBtn->GetSelectedItem () + 1;
	}

	return weight;
}

BOOL CMainFrame::GetStyleFromStyles (XStyle& style)
{
	CArray<CBCGPBaseRibbonElement*, CBCGPBaseRibbonElement*> arButtons;

	m_wndRibbonBar.GetElementsByID (ID_OBJECT_STYLES, arButtons);

	if (arButtons.GetSize () == 0)
	{
		return FALSE;
	}

	BOOL bRes = FALSE;

	CBCGPRibbonPaletteButton* pBtn = DYNAMIC_DOWNCAST (CBCGPRibbonPaletteButton, arButtons.GetAt (0));
	if (pBtn != NULL && pBtn->GetSelectedItem () != -1)
	{
		style = c_Styles[pBtn->GetSelectedItem ()];
		bRes = TRUE;
	}

	return bRes;
}

void CMainFrame::OnDummy()
{
}

LRESULT CMainFrame::OnHighlightRibbonListItem (WPARAM wp, LPARAM lp)
{
	int nIndex = (int) wp;

	CBCGPBaseRibbonElement* pElem = (CBCGPBaseRibbonElement*) lp;
	ASSERT_VALID (pElem);

	const UINT uiCommand = pElem->GetID ();
	
	CFrameWnd* pFrame = GetActiveFrame ();
	if (pFrame == NULL)
	{
		return 0;
	}

	CDrawDoc* pDoc = (CDrawDoc*)pFrame->GetActiveDocument();
	if (pDoc == NULL)
	{
		return 0;
	}

	ASSERT_VALID (pDoc);

	CDrawView* pView = DYNAMIC_DOWNCAST (CDrawView, pFrame->GetActiveView());
	if (pView == NULL)
	{
		return 0;
	}

	if (uiCommand != ID_VIEW_PAPERCOLOR)
	{
		if (nIndex != -1)
		{
			pView->StorePreviewState ();
		}
		else
		{
			pView->RestorePreviewState ();
		}
	}

	switch (uiCommand)
	{
	case ID_VIEW_PAPERCOLOR:
	case ID_OBJECT_FILLCOLOR:
	case ID_OBJECT_LINECOLOR:
		{
			COLORREF color = ((CBCGPRibbonColorButton*) pElem)->GetHighlightedColor ();

			if (uiCommand == ID_VIEW_PAPERCOLOR)
			{
				pDoc->SetPreviewColor (color);
			}
			else if (nIndex != -1)
			{
				if (uiCommand == ID_OBJECT_FILLCOLOR)
				{
					pView->PreviewFillColor (color);
				}
				else
				{
					pView->PreviewLineColor (color);
				}
			}	

			CBCGPPopupMenu::UpdateAllShadows ();
		}
		break;

	case ID_OBJECT_LINEWEIGHT:
		if (nIndex != -1)
		{
			pView->PreviewLineWeight (nIndex + 1);
			CBCGPPopupMenu::UpdateAllShadows ();
		}	
		break;

	case ID_OBJECT_STYLES:
		if (nIndex != -1)
		{
			pView->PreviewStyle (c_Styles[nIndex].clrFill, c_Styles[nIndex].clrLine);
			CBCGPPopupMenu::UpdateAllShadows ();
		}	
		break;
	}

	return 0;
}

void CMainFrame::SetRibbonContextCategory (UINT uiCategoryID)
{
	if (uiCategoryID != 0)
	{
		CBCGPRibbonCategory* pActivaTab = m_wndRibbonBar.GetActiveCategory ();
		if (pActivaTab != NULL && pActivaTab->GetContextID () == uiCategoryID)
		{
			return;
		}
	}

	BOOL bRecalc = m_wndRibbonBar.HideAllContextCategories ();

	if (uiCategoryID != 0)
	{
		m_wndRibbonBar.ShowContextCategories (uiCategoryID);
		bRecalc = TRUE;
	}

	if (bRecalc)
	{
		m_wndRibbonBar.RecalcLayout ();
		m_wndRibbonBar.RedrawWindow ();

		SendMessage (WM_NCPAINT, 0, 0);
	}
}

void CMainFrame::ActivateRibbonContextCategory (UINT uiCategoryID)
{
	if (m_wndRibbonBar.GetHideFlags () == 0)
	{
		m_wndRibbonBar.ActivateContextCategory (uiCategoryID);
	}
}
