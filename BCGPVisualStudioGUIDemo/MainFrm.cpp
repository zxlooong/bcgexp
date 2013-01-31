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
#include "BCGPVisualStudioGUIDemo.h"
#include "FindComboBox.h"
#include "OptionsDlg.h"
#include "MainFrm.h"

#include "BCGPTabbedControlBar.h"
#include "BCGPMiniFrameWnd.h"

#include "ChildFrm.h"

#include "UndoBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	ON_COMMAND(ID_HELP_KEYBOARDMAP, OnHelpKeyboardmap)
	ON_COMMAND(ID_FILE_NEW_PROJECT, OnFileNewProject)
	ON_COMMAND(ID_FILE_NEW_BLANK_SOLUTION, OnFileNewBlankSolution)
	ON_COMMAND(ID_FILE_OPEN_SOLUTION, OnFileOpenSolution)
	ON_COMMAND(ID_FILE_CLOSE_SOLUTION, OnFileCloseSolution)
	ON_COMMAND(ID_FILE_SAVE_ALL, OnFileSaveAll)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_TOOLS_CONNECT_TO_DATABASE, OnToolsConnectToDatabase)
	ON_COMMAND(ID_TOOLS_DEBUG_PROCESSES, OnToolsDebugProcesses)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND(ID_HELP_WEB, OnHelpWeb)
	ON_COMMAND(ID_MDI_MOVE_TO_NEXT_GROUP, OnMdiMoveToNextGroup)
	ON_COMMAND(ID_MDI_MOVE_TO_PREV_GROUP, OnMdiMoveToPrevGroup)
	ON_COMMAND(ID_MDI_NEW_HORZ_TAB_GROUP, OnMdiNewHorzTabGroup)
	ON_COMMAND(ID_MDI_NEW_VERT_GROUP, OnMdiNewVertGroup)
	ON_COMMAND(ID_MDI_CANCEL, OnMdiCancel)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_CLASS, OnViewClass)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CLASS, OnUpdateViewClass)
	ON_COMMAND(ID_VIEW_FILE, OnViewFile)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FILE, OnUpdateViewFile)
	ON_COMMAND(ID_VIEW_RESOURCE, OnViewResource)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESOURCE, OnUpdateViewResource)
	ON_COMMAND(ID_VIEW_PROPERTIES, OnViewProperties)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTIES, OnUpdateViewProperties)
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
	ON_COMMAND(ID_VIEW_WATCH, OnViewWatch)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WATCH, OnUpdateViewWatch)
	ON_COMMAND(ID_VIEW_TOOLBOX, OnViewToolbox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBOX, OnUpdateViewToolbox)
	ON_COMMAND(ID_VIEW_DYNAMICHELP, OnViewDynamichelp)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DYNAMICHELP, OnUpdateViewDynamichelp)
	ON_COMMAND(ID_MDI_TABBED_DOCUMENT, OnMdiTabbedDocument)
	ON_UPDATE_COMMAND_UI(ID_MDI_TABBED_DOCUMENT, OnUpdateMdiTabbedDocument)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_ON_GET_TAB_TOOLTIP, OnGetTabToolTip)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_REGISTERED_MESSAGE(BCGM_CREATETOOLBAR, OnToolbarCreateNew)
	ON_COMMAND(ID_TOOLBOX, OnToolBox)
	ON_UPDATE_COMMAND_UI(IDS_CARET_POS, OnUpdateCaretPos)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_CARET_POS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL, 
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	CBCGPPopupMenu::SetForceShadow (TRUE);

	m_bCanCovertControlBarToMDIChild = TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));

	CBCGPToolbarComboBoxButton::SetFlatMode ();

	//--------------------------
	// Load toolbar user images:
	//--------------------------
	if (!m_UserImages.Load (_T(".\\UserImages.bmp")))
	{
		TRACE(_T("Failed to load user images\n"));
		ASSERT (FALSE);
	}
	else
	{
		CBCGPToolBar::SetUserImages (&m_UserImages);
	}

	CBCGPToolBar::EnableQuickCustomization ();

	//-----------------
	// Create menu bar:
	//-----------------
	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	//--------------------------------------------
	// Menu will not take the focus on activation:
	//--------------------------------------------
	CBCGPPopupMenu::SetForceMenuFocus (FALSE);

	//----------------------
	// Create Resource toolbar:
	//----------------------
	if (!m_wndToolbarResource.Create(this,
		WS_CHILD|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		IDR_TOOLBAR_RESOURCE) || 
		!m_wndToolbarResource.LoadToolBar (IDR_TOOLBAR_RESOURCE))
	{
		TRACE0("Failed to create build toolbar\n");
		return FALSE;      // fail to create
	}

	//---------------------
	// Create main toolbar:
	//---------------------
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText (strMainToolbarTitle);

	//----------------------
	// Create Build toolbar:
	//----------------------
	if (!m_wndToolbarBuild.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		ID_VIEW_BUILD_TOOLBAR) ||
		!m_wndToolbarBuild.LoadToolBar (IDR_BUILD))
	{
		TRACE0("Failed to create build toolbar\n");
		return FALSE;      // fail to create
	}

	CString strBuildToolbarTitle;
	strBuildToolbarTitle.LoadString (IDS_BUILD_TOOLBAR);
	m_wndToolbarBuild.SetWindowText (strBuildToolbarTitle);

	//---------------------
	// Create Edit toolbar:
	//---------------------
	if (!m_wndToolbarEdit.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		ID_VIEW_EDIT_TOOLBAR) ||
		!m_wndToolbarEdit.LoadToolBar (IDR_EDIT))
	{
		TRACE0("Failed to create edit toolbar\n");
		return FALSE;      // fail to create
	}

	CString strEditToolbarTitle;
	strEditToolbarTitle.LoadString (IDS_EDIT_TOOLBAR);
	m_wndToolbarEdit.SetWindowText (strEditToolbarTitle);

	//--------------------------------------------------------------
	// Load menu items images (not placed on the standard toolbars):
	//--------------------------------------------------------------
	CBCGPToolBar::AddToolBarForImageCollection (IDR_MENU_IMAGES);

	//-------------------
	// Create status bar:
	//-------------------
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneStyle (0, SBPS_STRETCH);

	//------------------------------
	// Update status bar indicators:
	//------------------------------
	m_wndStatusBar.SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);

	//--------------------------------
	// Create docking control windows:
	//--------------------------------
	if (!CreateDockingBars ())
	{
		return -1;
	}

	m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	m_wndToolbarBuild.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	m_wndToolbarEdit.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolbarBuild.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolbarEdit.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolbarResource.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndResourceView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutputView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDynamicHelpView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPropertiesBar.EnableDocking(CBRS_ALIGN_ANY);
	m_pWndToolBoxBar->EnableDocking(CBRS_ALIGN_ANY);

	m_wndWatchBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	EnableAutoHideBars(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndPropertiesBar);
	DockControlBar(m_pWndToolBoxBar);

	DockControlBar(&m_wndToolbarBuild);
	DockControlBarLeftOf (&m_wndToolbarEdit, &m_wndToolbarBuild);

	DockControlBar(&m_wndClassView);

	CBCGPDockingControlBar* pTabbedBar = NULL; 
	m_wndResourceView.AttachToTabWnd (&m_wndClassView, BCGP_DM_SHOW, TRUE, &pTabbedBar);
	m_wndFileView.AttachToTabWnd (pTabbedBar, BCGP_DM_SHOW, TRUE, &pTabbedBar);
	m_pWndToolBoxBar->AttachToTabWnd (pTabbedBar, BCGP_DM_SHOW, TRUE, &pTabbedBar);

	DockControlBar(&m_wndOutputView);

	m_wndDynamicHelpView.DockToWindow (&m_wndPropertiesBar, CBRS_ALIGN_BOTTOM);
	m_wndWatchBar.DockToWindow (&m_wndOutputView, CBRS_ALIGN_LEFT);

	CRect rectMainToolBar;
	m_wndToolBar.GetWindowRect (&rectMainToolBar);

	//----------------------------------------
	// Allow user-defined toolbars operations:
	//----------------------------------------
	InitUserToobars (NULL,
					uiFirstUserToolBarId,
					uiLastUserToolBarId);

	//------------------------
	// Enable windows manager:
	//------------------------
	EnableWindowsDialog (ID_WINDOW_MANAGER, _T("Windows..."), TRUE);

	//--------------------------------------------------------------------
	// Enable conttol bar context menu (list of bars + customize command):
	//--------------------------------------------------------------------
	EnableControlBarMenu (	TRUE, ID_VIEW_CUSTOMIZE, 
							_T("Customize..."), ID_VIEW_TOOLBARS,
							FALSE, TRUE);

	EnableFullScreenMode (ID_VIEW_FULLSCREEN);

	return 0;
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


void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */,
		BCGCUSTOMIZE_MENU_SHADOWS | BCGCUSTOMIZE_TEXT_LABELS | 
		BCGCUSTOMIZE_LOOK_2000 | BCGCUSTOMIZE_MENU_ANIMATIONS);

	pDlgCust->EnableUserDefinedToolbars ();

	//-----------------
	// Setup combboxes:
	//-----------------
	pDlgCust->ReplaceButton (ID_EDIT_FIND, CFindComboButton ());

	CBCGPToolbarComboBoxButton comboButtonConfig (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, 
			CImageHash::GetImageOfCommand (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, FALSE),
			CBS_DROPDOWNLIST);
	comboButtonConfig.AddItem (_T("Win32 Debug"));
	comboButtonConfig.AddItem (_T("Win32 Release"));
	comboButtonConfig.SelectItem (0);

	pDlgCust->ReplaceButton (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, comboButtonConfig);

	//-----------------------------------
	// Add dropdown resources button:
	//-----------------------------------
	pDlgCust->AddButton (_T("Build"), CBCGPDropDownToolbarButton (_T("Add Resource"), &m_wndToolbarResource));

	//-------------------------
	// Setup undo/redo buttons:
	//-------------------------
	pDlgCust->ReplaceButton (ID_EDIT_UNDO, CUndoButton (ID_EDIT_UNDO, _T("&Undo")));
	pDlgCust->ReplaceButton (ID_EDIT_REDO, CUndoButton (ID_EDIT_REDO, _T("&Redo")));

	pDlgCust->Create ();
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM)
{
	UINT uiToolBarId = (UINT) wp;

	switch (uiToolBarId)
	{
	case IDR_MAINFRAME:
		{
			ASSERT (m_wndToolbarResource.GetSafeHwnd () != NULL);

			//-----------------------------------
			// Replace dropdown resources button:
			//-----------------------------------
			m_wndToolBar.ReplaceButton (ID_DUMMY_INSERT_RESOURCE,
					CBCGPDropDownToolbarButton (_T("Add Resource"), &m_wndToolbarResource));

			//--------------------------------------
			// Replace "Find..." button by combobox:
			//--------------------------------------
			m_wndToolBar.ReplaceButton (ID_EDIT_FIND, CFindComboButton ());

			//-------------------------------------
			// Replace "Undo" button by menubutton:
			//-------------------------------------
			m_wndToolBar.ReplaceButton (ID_EDIT_UNDO, CUndoButton (ID_EDIT_UNDO, _T("&Undo")));
			m_wndToolBar.ReplaceButton (ID_EDIT_REDO, CUndoButton (ID_EDIT_REDO, _T("&Redo")));
		}
		break;

	case IDR_BUILD:
		{
			//-----------------------------------------------
			// Replace "Confoguration..." button by combobox:
			//-----------------------------------------------
			CBCGPToolbarComboBoxButton comboButton (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, 
				CImageHash::GetImageOfCommand (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION, FALSE),
				CBS_DROPDOWNLIST);
			comboButton.AddItem (_T("Win32 Debug"));
			comboButton.AddItem (_T("Win32 Release"));
			comboButton.SelectItem (0);

			m_wndToolbarBuild.ReplaceButton (ID_DUMMY_SELECT_ACTIVE_CONFIGURATION,
											comboButton);
		}
		break;
	}

	return 0;
}

LRESULT CMainFrame::OnHelpCustomizeToolbars(WPARAM /*wp*/, LPARAM lp)
{
//	int iPageNum = (int) wp;

	CBCGPToolbarCustomize* pDlg = (CBCGPToolbarCustomize*) lp;
	ASSERT_VALID (pDlg);

	// TODO: show help about page number iPageNum


	return 0;
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

	if ((dwAllowedItems & BCGP_MDI_CAN_BE_DOCKED) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_TABBED_DOCUMENT, MF_BYCOMMAND);
	}

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->SetAutoDestroy (FALSE);
	pPopupMenu->Create (this, point.x, point.y, pPopup->GetSafeHmenu ());

	return TRUE;
}

void CMainFrame::OnWindowManager() 
{
	ShowWindowsDialog ();
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	if (!CMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	// Add some tools for example....
	CBCGPUserToolsManager* pUserToolsManager = theApp.GetUserToolsManager ();
	if (pUserToolsManager != NULL &&
		pUserToolsManager->GetUserTools ().IsEmpty ())
	{
		CBCGPUserTool* pTool1 = pUserToolsManager->CreateNewTool ();
		pTool1->m_strLabel = _T("Notepad");
		pTool1->SetCommand (_T("notepad.exe"));

		CBCGPUserTool* pTool2 = pUserToolsManager->CreateNewTool ();
		pTool2->m_strLabel = _T("Paint Brush");
		pTool2->SetCommand (_T("mspaint.exe"));

		CBCGPUserTool* pTool3 = pUserToolsManager->CreateNewTool ();
		pTool3->m_strLabel = _T("Windows Explorer");
		pTool3->SetCommand (_T("explorer.exe"));

		CBCGPUserTool* pTool4 = pUserToolsManager->CreateNewTool ();
		pTool4->m_strLabel = _T("BCGSoft On-Line");
		pTool4->SetCommand (_T("http://www.bcgsoft.com"));
	}

	CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bTabCustomTooltips = TRUE;

	EnableMDITabbedGroups (TRUE, mdiTabParams);

	//----------------------------------------------------
	// Enable customization button fore all user toolbars:
	//----------------------------------------------------
	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CBCGPToolBar* pUserToolbar = GetUserBarByIndex (i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
		}
	}


	return TRUE;
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//----------------------------------------------------
	// If control located on toolbar has focus, we should 
	// redirect clipboard commands to this control:
	//----------------------------------------------------
	if (CFindComboButton::HasFocus () &&
		HIWORD (wParam) == 1)	// Command from accelerator
	{
		UINT uiCmd = LOWORD (wParam);
		switch (uiCmd)
		{
		case ID_EDIT_PASTE:
			::SendMessage (::GetFocus (), WM_PASTE, 0, 0);
			return TRUE;

		case ID_EDIT_COPY:
			::SendMessage (::GetFocus (), WM_COPY, 0, 0);
			return TRUE;

		case ID_EDIT_CUT:
			::SendMessage (::GetFocus (), WM_CUT, 0, 0);
			return TRUE;
		}
	}
	
	return CMDIFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::OnHelpKeyboardmap() 
{
	CBCGPKeyMapDlg dlg (this, TRUE /* Enable Print */);
	dlg.DoModal ();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CBCGPMDIFrameWnd::OnToolbarCreateNew (wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CBCGPToolBar* pUserToolbar = (CBCGPToolBar*) lres;
	ASSERT_VALID (pUserToolbar);

	pUserToolbar->EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	return lres;
}

BOOL CMainFrame::CreateDockingBars ()
{
	//------------------
	// Crate class view:
	//------------------
	if (!m_wndClassView.Create (_T("Class View"), this, CRect (0, 0, 200, 200),
		TRUE, 
		ID_VIEW_CLASS,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Class View bar\n");
		return FALSE;      // fail to create
	}

	//----------------------
	// Create resource view:
	//----------------------
	if (!m_wndResourceView.Create (_T("Resource View"), this, CRect (0, 0, 200, 200),
		TRUE, 
		ID_VIEW_RESOURCE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Resource View bar\n");
		return FALSE;      // fail to create
	}

	//------------------
	// Create file view:
	//------------------
	if (!m_wndFileView.Create (_T("Solution Explorer"), this, CRect (0, 0, 200, 200),
		TRUE, 
		ID_VIEW_FILE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Solution Explorer bar\n");
		return FALSE;      // fail to create
	}


	//////////////////////////////////New Output////////////////////////////////////////
	if (!m_wndOutputView.Create (_T("Output"), this, CRect (0, 0, 200, 100),
		TRUE, 
		ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create output bar\n");
		return FALSE;      // fail to create
	}

	if (!m_wndDynamicHelpView.Create (_T("Dynamic Help"), this, CRect (0, 0, 200, 200),
		TRUE, 
		ID_VIEW_DYNAMICHELP,
		WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Dynamic Help Bar\n");
		return FALSE;		// fail to create
	}

	//------------------
	// Create watch bar:
	//------------------
	if (!m_wndWatchBar.Create (_T("Watch"), this, CRect (0, 0, 300, 100),
		TRUE, 
		ID_VIEW_WATCH,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create watch bar\n");
		return FALSE;      // fail to create
	}

	if (!m_wndPropertiesBar.Create (_T("Properties"), this, CRect (0, 0, 300, 200),
		TRUE, 
		ID_VIEW_PROPERTIES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}
	
	m_bIsToolBoxEx = TRUE;

	CToolBoxBarEx* pToolBox = new CToolBoxBarEx;

	if (!pToolBox->Create (_T("ToolBox"), this, CRect (0, 0, 200, 200),
		TRUE, 
		ID_TOOLBOX,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create ToolBox Bar\n");
		return FALSE;		// fail to create
	}
	
	m_pWndToolBoxBar = pToolBox;

	SetDockingBarsIcons (FALSE);

	return TRUE;
}

void CMainFrame::SetDockingBarsIcons (BOOL bHiColorIcons)
{
	HICON hClassViewIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
		MAKEINTRESOURCE (bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndClassView.SetIcon (hClassViewIcon, FALSE);

	HICON hResViewIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (bHiColorIcons ? IDI_RES_VIEW_HC : IDI_RES_VIEW),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndResourceView.SetIcon (hResViewIcon, FALSE);

	
	HICON hFileViewIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndFileView.SetIcon (hFileViewIcon, FALSE);


	HICON hOutputBarIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (bHiColorIcons ? IDI_OUTPUT_BAR_HC : IDI_OUTPUT_BAR),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndOutputView.SetIcon (hOutputBarIcon, FALSE);


	HICON hDynamicHelpIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (bHiColorIcons ? IDI_DYNAMIC_HELP_VIEW_HC : IDI_DYNAMIC_HELP_VIEW),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndDynamicHelpView.SetIcon (hDynamicHelpIcon, FALSE);


	HICON hWatchBarIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (bHiColorIcons ? IDI_WATCH_BAR_HC : IDI_WATCH_BAR),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndWatchBar.SetIcon (hWatchBarIcon, FALSE);

	
	HICON hPropertiesBarIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (bHiColorIcons ? IDI_PROPERTIES_BAR_HC : IDI_PROPERTIES_BAR),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndPropertiesBar.SetIcon (hPropertiesBarIcon, FALSE);

	HICON hToolBoxBarIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (bHiColorIcons ? IDI_TOOLBOX_BAR_HC : IDI_TOOLBOX_BAR),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_pWndToolBoxBar->SetIcon (hToolBoxBarIcon, FALSE);

	UpdateMDITabbedBarsIcons ();
}

void CMainFrame::OnFileNewProject() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileNewBlankSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileOpenSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileCloseSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileSaveAll() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewRefresh() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnToolsConnectToDatabase() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnToolsDebugProcesses() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewFullScreen()
{
	ShowFullScreen ();
}

void CMainFrame::OnToolBox() 
{
	int nPage = -1;
	int nTool = -1;

	if (m_bIsToolBoxEx)
	{
		nTool = ((CToolBoxBarEx*) m_pWndToolBoxBar)->GetLastClickedTool (nPage);
	}
	else
	{
		nPage = ((CToolBoxBar*) m_pWndToolBoxBar)->GetActivePage ();
		nTool = ((CToolBoxBar*) m_pWndToolBoxBar)->GetLastClickedTool (nPage);
	}
		
	const MSG* pMsg = CWnd::GetCurrentMessage();

	if (pMsg->lParam != (LPARAM) m_pWndToolBoxBar->GetSafeHwnd ())
	{
		m_pWndToolBoxBar->ShowControlBar (!m_pWndToolBoxBar->IsVisible (), FALSE, TRUE);
		return;
	}

	CString str;
	str.Format (_T("Toolbox item clicked\nPage = %d, item = %d"), nPage, nTool);
	MessageBox (str);
}

CBCGPToolbarComboBoxButton* CMainFrame::GetFindCombo()
{
	CBCGPToolbarComboBoxButton* pFindCombo = NULL;

	CObList listButtons;
	if (CBCGPToolBar::GetCommandButtons (ID_EDIT_FIND_COMBO, listButtons) > 0)
	{
		for (POSITION posCombo = listButtons.GetHeadPosition (); 
			 pFindCombo == NULL && posCombo != NULL;)
		{
			CBCGPToolbarComboBoxButton* pCombo = 
				DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton, listButtons.GetNext (posCombo));

			if (pCombo != NULL &&
				pCombo->GetEditCtrl ()->GetSafeHwnd () == ::GetFocus ())
			{
				pFindCombo = pCombo;
			}
		}
	}

	return pFindCombo;
}

void CMainFrame::OnToolsOptions() 
{
	COptionsDlg dlgOptions (_T("Options"), this);
	dlgOptions.DoModal ();
}

void CMainFrame::OnChangeLook (BOOL bOneNoteTabs, BOOL bMDITabColors, BOOL bIsVSDotNetLook,
							   BOOL bDockTabColors, BOOL bMDITabsVS2005Look,
							   BOOL bIsToolBoxEx, BOOL bActiveTabCloseButton)
{
	CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bTabCustomTooltips = TRUE;

	if (bMDITabsVS2005Look)
	{
		mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_VS2005;
		mdiTabParams.m_bDocumentMenu = TRUE;
	}
	else if (bOneNoteTabs)
	{
		mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_ONENOTE;
		mdiTabParams.m_bAutoColor = bMDITabColors;
	}

	if (bActiveTabCloseButton)
	{
		mdiTabParams.m_bTabCloseButton = FALSE;
		mdiTabParams.m_bActiveTabCloseButton = TRUE;
	}

	EnableMDITabbedGroups (TRUE, mdiTabParams);

	m_wndPropertiesBar.SetVSDotNetLook (bIsVSDotNetLook);

	m_wndPropertiesBar.OnChangeVisualStyle ();
	m_wndDynamicHelpView.OnChangeVisualStyle ();
	m_wndClassView.OnChangeVisualStyle ();
	m_wndFileView.OnChangeVisualStyle ();
	m_wndResourceView.OnChangeVisualStyle ();

	CBCGPTabbedControlBar::EnableTabAutoColor (bDockTabColors);

	//-----------------------
	// Reload toolbar images:
	//-----------------------
	CBCGPToolBar::ResetAllImages ();

	m_wndToolBar.LoadBitmap (theApp.m_bHiColorIcons ? IDB_MAINFRAME_HC : IDR_MAINFRAME);
	m_wndToolbarResource.LoadBitmap (theApp.m_bHiColorIcons ? IDB_TOOLBAR_RESOURCE_HC : IDR_TOOLBAR_RESOURCE);
	m_wndToolbarBuild.LoadBitmap (theApp.m_bHiColorIcons ? IDB_BUILD_HC : IDR_BUILD);
	m_wndToolbarEdit.LoadBitmap (theApp.m_bHiColorIcons ? IDB_EDIT_HC : IDR_EDIT);

	CBCGPToolBar::AddToolBarForImageCollection (IDR_MENU_IMAGES, 
		theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_HC : 0);

	//------------------
	// Inform all views:
	//------------------
	for (CWnd* pWndChild = m_wndClientArea.GetWindow (GW_CHILD); 
		pWndChild != NULL; pWndChild = pWndChild->GetNextWindow ())
	{
		CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, pWndChild);
		if (pMDIChild != NULL)
		{
			CBCGPVisualStudioGUIDemoView* pView = DYNAMIC_DOWNCAST (
				CBCGPVisualStudioGUIDemoView, pMDIChild->GetActiveView ());
			if (pView != NULL)
			{
				pView->OnChangeVisualStyle ();
			}
		}
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	ASSERT_VALID (pDockManager);

	if (m_bIsToolBoxEx != bIsToolBoxEx)
	{
		BOOL bIsMDITabbed = m_pWndToolBoxBar->IsMDITabbed ();
		BOOL bVisible = m_pWndToolBoxBar->IsVisible ();
		//---------------------
		// Recreate toolbox bar:
		//---------------------
		m_bIsToolBoxEx = bIsToolBoxEx;

		CBCGPDockingControlBar*	pWndNewToolBoxBar = NULL;
		const DWORD dwToolBoxStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI;

		if (m_bIsToolBoxEx)
		{
			CToolBoxBarEx* pToolBox = new CToolBoxBarEx;

			if (!pToolBox->Create (_T("ToolBox"), this, CRect (0, 0, 0, 0), TRUE, ID_TOOLBOX, dwToolBoxStyle))
			{
				TRACE0("Failed to create ToolBox Bar\n");
			}

			pWndNewToolBoxBar = pToolBox;
		}
		else
		{
			CToolBoxBar* pToolBox = new CToolBoxBar;

			if (!pToolBox->Create (_T("ToolBox"), this, CRect (0, 0, 0, 0), TRUE, ID_TOOLBOX, dwToolBoxStyle))
			{
				TRACE0("Failed to create ToolBox Bar\n");
			}

			pWndNewToolBoxBar = pToolBox;
		}

		// replace existing toolbox with the new one
		pDockManager->ReplaceControlBar (m_pWndToolBoxBar, pWndNewToolBoxBar);

		// now we need to safely remove the old toolbox from its parent MDI Child window
		CWnd* pParentMDIChild = NULL;
		if (bIsMDITabbed)
		{
			// obtain the parent of toolbox - it can be either MDiChild if toolbox is visible, or MainFrame 
			// if the tabbed document is hidden
			pParentMDIChild = m_pWndToolBoxBar->GetParent ();
			// remove from the list of hidden bars
			GetDockManager ()->RemoveHiddenMDITabbedBar (m_pWndToolBoxBar);			
			// store pointer to parent only in case it's MDIChild - we'll need to destroy the parent 
			// after the control bar has been destroyed
			if (!pParentMDIChild->IsKindOf (RUNTIME_CLASS (CBCGPMDIChildWnd)))
			{
				pParentMDIChild = NULL;
			}
		}

		// now we can destroy the old toolbox
		m_pWndToolBoxBar->DestroyWindow ();
		delete m_pWndToolBoxBar;

		// and close its parent
		if (pParentMDIChild != NULL)
		{
			//close the old MDIChild
			pParentMDIChild->SendMessage (WM_CLOSE);
		}

		m_pWndToolBoxBar = pWndNewToolBoxBar;

		if (bIsMDITabbed)
		{
			// create new MDIChild by converting the new toolbox bar into tabbed document
			ControlBarToTabbedDocument (m_pWndToolBoxBar);
			if (!bVisible)
			{
				m_pWndToolBoxBar->ShowControlBar (FALSE, FALSE, TRUE);
			}
		}
	}

	SetDockingBarsIcons (theApp.m_bHiColorIcons);

	pDockManager->AdjustBarFrames ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

void CMainFrame::OnHelpWeb() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com"), NULL, NULL, NULL);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CMDIFrameWnd::PreCreateWindow(cs);
}

BOOL CMainFrame::DestroyWindow() 
{
	if (m_pWndToolBoxBar != NULL)
	{
		m_pWndToolBoxBar->DestroyWindow ();
		delete m_pWndToolBoxBar;
	}
	
	return CMDIFrameWnd::DestroyWindow();
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

CBCGPMDIChildWnd* CMainFrame::CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/)
{
	if (lpcszDocName != NULL && lpcszDocName [0] != '\0')
	{
		CDocument* pDoc = NULL;
		if (g_strStartViewName.Compare (lpcszDocName) == 0)
		{
			pDoc = theApp.m_pStartDocTemplate->OpenDocumentFile (NULL);
		}
		else
		{
			pDoc = AfxGetApp()->OpenDocumentFile (lpcszDocName);
		}

		if (pDoc != NULL)
		{
			POSITION pos = pDoc->GetFirstViewPosition();

			if (pos != NULL)
			{
				CView* pView = pDoc->GetNextView (pos);
				return DYNAMIC_DOWNCAST (CBCGPMDIChildWnd, pView->GetParent ());
			}   
		}

	}

	return NULL;
}

void CMainFrame::OnClose() 
{
	SaveMDIState (theApp.GetRegSectionPath ());
	CMDIFrameWnd::OnClose();
}

LRESULT CMainFrame::OnGetTabToolTip(WPARAM /*wp*/, LPARAM lp)
{
	CBCGPTabToolTipInfo* pInfo = (CBCGPTabToolTipInfo*) lp;
	ASSERT (pInfo != NULL);
	ASSERT_VALID (pInfo->m_pTabWnd);

	if (!pInfo->m_pTabWnd->IsMDITab ())
	{
		return 0;
	}

	CFrameWnd* pFrame = DYNAMIC_DOWNCAST (CFrameWnd,
		pInfo->m_pTabWnd->GetTabWnd (pInfo->m_nTabIndex));
	if (pFrame == NULL)
	{
		return 0;
	}

	CDocument* pDoc = pFrame->GetActiveDocument ();
	if (pDoc == NULL)
	{
		return 0;
	}

	pInfo->m_strText = pDoc->GetPathName ();
	return 0;
}

void CMainFrame::OnViewClass() 
{
	m_wndClassView.ShowControlBar (!m_wndClassView.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewClass(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndClassView.IsVisible ());	
}

void CMainFrame::OnViewFile() 
{
	m_wndFileView.ShowControlBar (!m_wndFileView.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewFile(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndFileView.IsVisible ());	
}

void CMainFrame::OnViewResource() 
{
	m_wndResourceView.ShowControlBar (!m_wndResourceView.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewResource(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndResourceView.IsVisible ());
}

void CMainFrame::OnViewProperties() 
{
	m_wndPropertiesBar.ShowControlBar (!m_wndPropertiesBar.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewProperties(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndPropertiesBar.IsVisible ());
}

void CMainFrame::OnViewOutput() 
{
	m_wndOutputView.ShowControlBar (!m_wndOutputView.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndOutputView.IsVisible ());
}

void CMainFrame::OnViewWatch() 
{
	m_wndWatchBar.ShowControlBar (!m_wndWatchBar.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewWatch(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndWatchBar.IsVisible ());
}

void CMainFrame::OnViewToolbox() 
{
	m_pWndToolBoxBar->ShowControlBar (!m_pWndToolBoxBar->IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewToolbox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_pWndToolBoxBar->IsVisible ());
}

void CMainFrame::OnViewDynamichelp() 
{
	m_wndDynamicHelpView.ShowControlBar (!m_wndDynamicHelpView.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewDynamichelp(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndDynamicHelpView.IsVisible ());
}

void CMainFrame::OnMdiTabbedDocument() 
{
	CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, MDIGetActive ());
	if (pMDIChild == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	TabbedDocumentToControlBar (pMDIChild);
}

void CMainFrame::OnUpdateMdiTabbedDocument(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck ();
}

void CMainFrame::OnUpdateCaretPos(CCmdUI* pCmdUI)
{
	pCmdUI->SetText (_T(""));
}

