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
//

#include "stdafx.h"

#include "wordpad.h"
#include "mainfrm.h"
#include "wordpdoc.h"
#include "wordpvw.h"
#include "strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const int  iMaxUserToolbars		= 10;

const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_COMMAND(ID_HELP, OnHelpFinder)
	ON_WM_DROPFILES()
	ON_WM_FONTCHANGE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_DEVMODECHANGE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_COMMAND(ID_HELP_INDEX, OnHelpFinder)
	ON_COMMAND(ID_VIEW_FULL_SCREEN, OnViewFullScreen)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_CONTEXT_HELP, CBCGPFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, OnHelpFinder)
	ON_MESSAGE(WPM_BARSTATE, OnBarState)
	ON_REGISTERED_MESSAGE(CWordPadApp::m_nOpenMsg, OnOpenMsg)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZETOOLBAR, OnStartCustomize)
	ON_REGISTERED_MESSAGE(BCGM_CREATETOOLBAR, OnToolbarCreateNew)
	ON_REGISTERED_MESSAGE(BCGM_GETDOCUMENTCOLORS, OnGetDocumentColors)
	ON_COMMAND(ID_DUMMY, OnDummy)
	ON_COMMAND(ID_HELP_FIND, OnAskQuestion)
END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_hIconDoc = theApp.LoadIcon(IDI_ICON_DOC);
	m_hIconText = theApp.LoadIcon(IDI_ICON_TEXT);
	m_hIconWrite = theApp.LoadIcon(IDI_ICON_WRITE);
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	WNDCLASS wndcls;

	BOOL bRes = CBCGPFrameWnd::PreCreateWindow(cs);
	HINSTANCE hInst = AfxGetInstanceHandle();

	// see if the class already exists
	if (!::GetClassInfo(hInst, szWordPadClass, &wndcls))
	{
		// get default stuff
		::GetClassInfo(hInst, cs.lpszClass, &wndcls);
		wndcls.style &= ~(CS_HREDRAW|CS_VREDRAW);
		// register a new class
		wndcls.lpszClassName = szWordPadClass;
		wndcls.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
		ASSERT(wndcls.hIcon != NULL);
		if (!AfxRegisterClass(&wndcls))
			AfxThrowResourceException();
	}
	cs.lpszClass = szWordPadClass;
	CRect rect = theApp.m_rectInitialFrame;
	if (rect.Width() > 0 && rect.Height() > 0)
	{
		// make sure window will be visible
		CDisplayIC dc;
		CRect rectDisplay(0, 0, dc.GetDeviceCaps(HORZRES),
			dc.GetDeviceCaps(VERTRES));
		if (rectDisplay.PtInRect(rect.TopLeft()) &&
			rectDisplay.PtInRect(rect.BottomRight()))
		{
			cs.x = rect.left;
			cs.y = rect.top;
			cs.cx = rect.Width();
			cs.cy = rect.Height();
		}
	}
	return bRes;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
	CBCGPToolbarComboBoxButton::SetFlatMode ();
	CBCGPToolbarComboBoxButton::SetCenterVert ();

	CBCGPFontComboBox::m_bDrawUsingFont = TRUE;

	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!CreateMenuBar())
		return -1;

	if (!CreateToolBar())
		return -1;

	if (!CreateFormatBar())
		return -1;

	if (!CreateStatusBar())
		return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	if (!CreateTaskPane())
		return -1;

	if (!CreateRulerBar())
		return -1;

	CBCGPToolBar::AddToolBarForImageCollection (IDR_TOOLBAR_IMAGES);
	CBCGPToolBar::AddToolBarForImageCollection (IDR_BORDER_TYPE);
	
	CBCGPToolBar::EnableQuickCustomization ();

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFormatBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndTaskPane.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndFormatBar);
	DockControlBar(&m_wndTaskPane);

	CWnd* pView = GetDlgItem(AFX_IDW_PANE_FIRST);
	if (pView != NULL)
	{
		pView->SetWindowPos(&wndBottom, 0, 0, 0, 0,
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);
	}

	//----------------------------------------
	// Allow user-defined toolbars operations:
	//----------------------------------------
	InitUserToobars (NULL,
					uiFirstUserToolBarId,
					uiLastUserToolBarId);

	//--------------------
	// Set basic commands:
	//--------------------
	CList<UINT, UINT>	lstBasicCommands;
	lstBasicCommands.AddTail (ID_FILE_NEW);
	lstBasicCommands.AddTail (ID_FILE_OPEN);
	lstBasicCommands.AddTail (ID_FILE_SAVE);
	lstBasicCommands.AddTail (ID_FILE_PRINT);
	lstBasicCommands.AddTail (ID_APP_EXIT);
	lstBasicCommands.AddTail (ID_EDIT_UNDO);
	lstBasicCommands.AddTail (ID_EDIT_CUT);
	lstBasicCommands.AddTail (ID_EDIT_COPY);
	lstBasicCommands.AddTail (ID_EDIT_PASTE);
	lstBasicCommands.AddTail (ID_EDIT_SELECT_ALL);
	lstBasicCommands.AddTail (ID_EDIT_FIND);
	lstBasicCommands.AddTail (ID_EDIT_REPEAT);
	lstBasicCommands.AddTail (ID_EDIT_REPLACE);
	lstBasicCommands.AddTail (ID_OLE_EDIT_PROPERTIES);
	lstBasicCommands.AddTail (ID_VIEW_OPTIONS);
	lstBasicCommands.AddTail (ID_VIEW_CUSTOMIZE);
	lstBasicCommands.AddTail (ID_VIEW_APP_LOOK);
	lstBasicCommands.AddTail (ID_VIEW_FULL_SCREEN);
	lstBasicCommands.AddTail (ID_OLE_INSERT_NEW);
	lstBasicCommands.AddTail (ID_FORMAT_FONT);
	lstBasicCommands.AddTail (ID_INSERT_BULLET);
	lstBasicCommands.AddTail (ID_CHAR_COLOR);
	lstBasicCommands.AddTail (ID_HELP_INDEX);
	lstBasicCommands.AddTail (ID_APP_ABOUT);
	lstBasicCommands.AddTail (ID_PARA_LEFT);
	lstBasicCommands.AddTail (ID_VIEW_TOOLBARS);

	CBCGPToolBar::SetBasicCommands (lstBasicCommands);

	//--------------------------------------------------------------------
	// Enable conttol bar context menu (list of bars + customize command):
	//--------------------------------------------------------------------
	EnableControlBarMenu (	TRUE, ID_VIEW_CUSTOMIZE, 
							_T("Customize..."), ID_VIEW_TOOLBARS,
							FALSE, TRUE);

	EnableFullScreenMode (ID_VIEW_FULL_SCREEN);
	EnableFullScreenMainMenu (FALSE);

	return 0;
}

BOOL CMainFrame::CreateMenuBar()
{
	//----------------------------------------------
	// Create menu bar (replaces the standard menu):
	//----------------------------------------------
	if (!m_wndMenuBar.Create (this/*, WS_CHILD | WS_VISIBLE | CBRS_TOP, uiMenuBarId*/))
	{
		TRACE0("Failed to create menubar\n");
		return FALSE;
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_BORDER_3D);

	m_wndMenuBar.EnableHelpCombobox (ID_HELP_FIND, _T("Type a question for help"));

	CString str;
	str.LoadString(IDS_TITLE_MENUBAR);
	m_wndMenuBar.SetWindowText(str);
	return TRUE;
}

BOOL CMainFrame::CreateToolBar()
{
	if (!m_wndToolBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC |
			CBRS_GRIPPER | CBRS_BORDER_3D)||
			!m_wndToolBar.LoadToolBar (IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;      // fail to create
	}

	CString str;
	str.LoadString(IDS_TITLE_TOOLBAR);
	m_wndToolBar.SetWindowText(str);

	m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	return TRUE;
}

BOOL CMainFrame::CreateFormatBar()
{
	if (!m_wndFormatBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		ID_VIEW_FORMATBAR) ||
		!m_wndFormatBar.LoadToolBar (IDR_FORMATBAR))
	{
		TRACE0("Failed to create FormatBar\n");
		return FALSE;      // fail to create
	}

	CString str;
	str.LoadString(IDS_TITLE_FORMATBAR);
	m_wndFormatBar.SetWindowText(str);

	m_wndFormatBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	return TRUE;
}

BOOL CMainFrame::CreateTaskPane ()
{
	CRect rectDummy(0, 0, 200, 400);
	if (!m_wndTaskPane.Create(_T("Tasks Pane"), this, rectDummy, TRUE, ID_VIEW_TASK_PANE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_BCGP_CLOSE | CBRS_BCGP_FLOAT))
	{
		TRACE0("Failed to create task pane\n");
		return FALSE;      // fail to create
	}

	m_wndTaskPane.EnableDocking (CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
	DockControlBar(&m_wndTaskPane);

	return TRUE;
}

BOOL CMainFrame::CreateRulerBar()
{
	if (!m_wndRulerBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_HIDE_INPLACE, ID_VIEW_RULER))
	{
		TRACE0("Failed to create ruler\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}

BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Operations

HICON CMainFrame::GetIcon(int nDocType)
{
	switch (nDocType)
	{
		case RD_WINWORD6:
		case RD_WORDPAD:
		case RD_EMBEDDED:
		case RD_RICHTEXT:
			return m_hIconDoc;
		case RD_TEXT:
		case RD_OEMTEXT:
			return m_hIconText;
		case RD_WRITE:
			return m_hIconWrite;
	}
	return m_hIconDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFontChange()
{
	m_wndFormatBar.SendMessage(CWordPadApp::m_nPrinterChangedMsg);
}

void CMainFrame::OnDevModeChange(LPTSTR lpDeviceName)
{
	theApp.NotifyPrinterChanged();
	CBCGPFrameWnd::OnDevModeChange(lpDeviceName); //sends message to descendants
}

void CMainFrame::OnSysColorChange()
{
	CBCGPFrameWnd::OnSysColorChange();
	OnChangeLook ();
}

void CMainFrame::ActivateFrame(int nCmdShow)
{
	CBCGPFrameWnd::ActivateFrame(nCmdShow);
	// make sure and display the toolbar, ruler, etc while loading a document.
	OnIdleUpdateCmdUI(0, 0);
	UpdateWindow();
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFrameWnd::OnSize(nType, cx, cy);
	theApp.m_bMaximized = (nType == SIZE_MAXIMIZED);
	if (nType == SIZE_RESTORED)
		GetWindowRect(theApp.m_rectInitialFrame);
}

LRESULT CMainFrame::OnBarState(WPARAM wParam, LPARAM lParam)
{
	if (lParam == -1)
		return 0L;
	ASSERT(lParam != RD_EMBEDDED);
	if (wParam != 0)
	{
		if (IsTextType((int) lParam))
		{
			// in text mode hide the ruler and format bar so that it is the default
			CBCGPBaseControlBar* pBar = GetControlBar(ID_VIEW_FORMATBAR);
			if (pBar != NULL)
				pBar->ShowControlBar(FALSE, FALSE, FALSE);
			pBar = GetControlBar(ID_VIEW_RULER);
			if (pBar != NULL)
				pBar->ShowControlBar(FALSE, FALSE, FALSE);
		}
		HICON hIcon = GetIcon((int)lParam);
		SendMessage(WM_SETICON, TRUE, (LPARAM)hIcon);

	}
	return 0L;
}

void CMainFrame::OnMove(int x, int y)
{
	CBCGPFrameWnd::OnMove(x, y);
	WINDOWPLACEMENT wp;
	wp.length = sizeof(wp);
	GetWindowPlacement(&wp);
	theApp.m_rectInitialFrame = wp.rcNormalPosition;
	CView* pView = GetActiveView();
	if (pView != NULL)
		pView->SendMessage(WM_MOVE);
}

LRESULT CMainFrame::OnOpenMsg(WPARAM, LPARAM lParam)
{
	TCHAR szAtomName[256];
	szAtomName[0] = NULL;
	GlobalGetAtomName((ATOM)lParam, szAtomName, 256);
	CWordPadDoc* pDoc = (CWordPadDoc*)GetActiveDocument();
	if (szAtomName[0] != NULL && pDoc != NULL)
	{
		if (lstrcmpi(szAtomName, pDoc->GetPathName()) == 0)
			return TRUE;
	}
	return FALSE;
}

void CMainFrame::OnHelpFinder()
{
	theApp.WinHelp(0, HELP_FINDER);
}

void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFileName[_MAX_PATH];
	::DragQueryFile(hDropInfo, 0, szFileName, _MAX_PATH);
	::DragFinish(hDropInfo);
	theApp.OpenDocumentFile(szFileName);
}

BOOL CMainFrame::OnQueryNewPalette()
{
	CView* pView = GetActiveView();
	if (pView != NULL)
		return (BOOL) pView->SendMessage(WM_QUERYNEWPALETTE);
	return FALSE;
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	CView* pView = GetActiveView();
	if (pView != NULL)
		pView->SendMessage(WM_PALETTECHANGED, (WPARAM)pFocusWnd->GetSafeHwnd());
}

void CMainFrame::OnViewCustomize() 
{
	CWordPadView* pView = DYNAMIC_DOWNCAST (CWordPadView, GetActiveView());
	if (pView != NULL && pView->GetInPlaceActiveItem () != NULL)
	{
		return;
	}

	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */,
		BCGCUSTOMIZE_MENU_SHADOWS | BCGCUSTOMIZE_TEXT_LABELS | 
		BCGCUSTOMIZE_LOOK_2000 | BCGCUSTOMIZE_MENU_ANIMATIONS);

	pDlgCust->AddToolBar (_T("Format"), IDR_FORMATBAR);

	CBCGPToolbarFontCombo* pFontButton = m_wndFormatBar.CreateFontComboButton ();
	pDlgCust->ReplaceButton (IDC_FONTNAME, *pFontButton);
	delete pFontButton;

	CBCGPToolbarFontSizeCombo comboButtonFontSize (IDC_FONTSIZE, 
		CImageHash::GetImageOfCommand (IDC_FONTSIZE, FALSE),
		WS_TABSTOP|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|CBS_DROPDOWN,
		10*m_wndFormatBar.m_szBaseUnits.cx + 10);
	pDlgCust->ReplaceButton (IDC_FONTSIZE, comboButtonFontSize);

	CBCGPColorMenuButton* pColorButton = m_wndFormatBar.CreateColorButton ();
	pDlgCust->ReplaceButton (ID_CHAR_COLOR, *pColorButton);
	delete pColorButton;

	CBCGPToolbarMenuButton* pBorderTypeButton = m_wndFormatBar.CreateBorderTypeButton ();
	pDlgCust->ReplaceButton (ID_BORDER_1, *pBorderTypeButton);
	delete pBorderTypeButton;

	pDlgCust->EnableUserDefinedToolbars ();
	pDlgCust->Create ();
}

BOOL CMainFrame::OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup)
{
	BOOL bRes = CBCGPFrameWnd::OnShowPopupMenu (pMenuPopup);

	if (pMenuPopup != NULL && !pMenuPopup->IsCustomizePane())
	{
		AdjustObjectSubmenu (pMenuPopup);
		AdjustColorsMenu (pMenuPopup, ID_CHAR_COLOR);
	}

	return bRes;
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

	int iIndex = pMenuBar->CommandToIndex (ID_OLE_VERB_POPUP);
	if (iIndex < 0)
	{
		return;
	}

	CWordPadDoc* pDoc = (CWordPadDoc*)GetActiveDocument();
	ASSERT_VALID (pDoc);

	// check for single selection
	COleClientItem* pItem = pDoc->GetPrimarySelectedItem(GetActiveView());
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

void CMainFrame::AdjustColorsMenu (CBCGPPopupMenu* pMenuPopup, UINT uiID)
{
	CBCGPPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT (pMenuBar != NULL);

	int iIndex = pMenuBar->CommandToIndex (uiID);
	if (iIndex < 0)
	{
		return;
	}

	if (DYNAMIC_DOWNCAST (CBCGPColorMenuButton, pMenuBar->GetButton (iIndex)) != NULL)
	{
		return;
	}

	CBCGPColorMenuButton* pColorButton = m_wndFormatBar.CreateColorButton ();
	pMenuBar->ReplaceButton (ID_CHAR_COLOR, *pColorButton, TRUE);
	delete pColorButton;
}
//**********************************************************************************
LRESULT CMainFrame::OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp)
{
	int iPageNum = (int) wp;

	CBCGPToolbarCustomize* pDlg = (CBCGPToolbarCustomize*) lp;
	ASSERT_VALID (pDlg);

	// Test!
	CString str;
	str.Format (_T("Help about page number %d"), iPageNum);

	MessageBox (str);

	return 0;
}
//***************************************************************************************
LRESULT CMainFrame::OnStartCustomize(WPARAM, LPARAM)
{
	CWordPadView* pView = DYNAMIC_DOWNCAST (CWordPadView, GetActiveView());
	if (pView == NULL)
	{
		return 0;
	}

	pView->GetRichEditCtrl().SetSel (-1, 0);
	return 0;
}
//***************************************************************************************
LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CBCGPFrameWnd::OnToolbarCreateNew (wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CBCGPToolBar* pUserToolbar = (CBCGPToolBar*) lres;
	ASSERT_VALID (pUserToolbar);

	pUserToolbar->EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	pUserToolbar->AdjustLayout ();
	return lres;
}
//*******************************************************************************
BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//----------------------------------------------------
	// If Font/Size combobox has focus, we should redirect 
	// clipboard commands to its editbox:
	//----------------------------------------------------
	if (HIWORD (wParam) == 1)	// Command from accelerator
	{
		if (CBCGPToolbarComboBoxButton::GetByCmd (IDC_FONTNAME, TRUE) != NULL ||
			CBCGPToolbarComboBoxButton::GetByCmd (IDC_FONTSIZE, TRUE) != NULL)
		{
			// Either font combox or size combo are focused
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
	}

	return CBCGPFrameWnd::OnCommand(wParam, lParam);
}
//*************************************************************************************
LRESULT CMainFrame::OnGetDocumentColors(WPARAM, LPARAM lp)
{
	CList<COLORREF,COLORREF>* pLstDocColors =
		(CList<COLORREF,COLORREF>*) lp;
	ASSERT_VALID (pLstDocColors);

	CWordPadView* pView = DYNAMIC_DOWNCAST (CWordPadView, GetActiveView());
	if (pView != NULL)
	{
		pView->GetDocumentColors (*pLstDocColors);
	}

	return 0;
}
//*************************************************************************************
BOOL CMainFrame::OnTearOffMenu (CBCGPPopupMenu* /*pMenuPopup*/, CBCGPControlBar* pBar)
{
	CBCGPColorBar* pColorBar = DYNAMIC_DOWNCAST (CBCGPColorBar, pBar);
	if (pColorBar != NULL)
	{
		CWordPadView* pView = DYNAMIC_DOWNCAST (CWordPadView, GetActiveView());
		if (pView != NULL)
		{
			CList<COLORREF,COLORREF> lstDocColors;
			pView->GetDocumentColors (lstDocColors);

			pColorBar->SetDocumentColors (_T("Document's Colors"), lstDocColors);
		}
	}

	return TRUE;
}
//**************************************************************************************
BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	if (!CBCGPFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

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

void CMainFrame::OnChangeLook ()
{
	BOOL bIsLook2003 = CBCGPVisualManager::GetInstance ()->IsKindOf (
		RUNTIME_CLASS (CBCGPVisualManager2003));

	m_wndRulerBar.CreateGDIObjects ();
	m_wndRulerBar.RedrawWindow ();

	CWindowDC dc (NULL);
	int nBitsPerPixel = dc.GetDeviceCaps (BITSPIXEL);

	m_wndTaskPane.UpdateIcons ();
	m_wndTaskPane.EnableNavigationToolbar (bIsLook2003,
		theApp.m_bHiColorIcons && nBitsPerPixel > 16 ? IDB_TASKSPANE_TOOLBAR : 0, CSize (16, 16));
	m_wndTaskPane.RecalcLayout (FALSE);

	//-----------------------
	// Reload toolbar images:
	//-----------------------
	CBCGPToolBar::ResetAllImages ();

	m_wndToolBar.LoadBitmap (
		theApp.m_bHiColorIcons && nBitsPerPixel > 16 ? IDB_MAINFRAME_HC : IDR_MAINFRAME);

	m_wndFormatBar.LoadBitmap (IDR_FORMATBAR);

	CBCGPToolBar::AddToolBarForImageCollection (IDR_TOOLBAR_IMAGES, 
		theApp.m_bHiColorIcons && nBitsPerPixel > 16 ? IDR_TOOLBAR_IMAGES_HC : 0);

	CBCGPToolBar::AddToolBarForImageCollection (IDR_BORDER_TYPE, IDR_BORDER_TYPE);

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

void CMainFrame::OnDummy()
{
	AfxMessageBox (ID_DUMMY);
}

void CMainFrame::OnViewFullScreen() 
{
	ShowFullScreen ();
}

void CMainFrame::OnAskQuestion()
{
	CBCGPToolbarComboBoxButton* pHelpCombo = m_wndMenuBar.GetHelpCombobox ();
	if (pHelpCombo == NULL)
	{
		return;
	}

	CString strQuestion = pHelpCombo->GetText ();
	strQuestion.TrimLeft ();
	strQuestion.TrimRight ();

	if (strQuestion.IsEmpty ())
	{
		return;
	}

	pHelpCombo->AddItem (strQuestion);

	CString str;
	str.Format (_T("The question is: %s"), strQuestion);

	MessageBox (str);

	SetFocus ();
}
