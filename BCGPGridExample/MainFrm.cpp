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
#include "BCGPGridExample.h"

#include "MainFrm.h"

#include "BCGPGridExampleDoc.h"
#include "BCGPGridExampleView.h"

#include "TreeDlg.h"
#include "VirtualGridDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CToolbarLabel : public CBCGPToolbarButton  
{
	DECLARE_SERIAL(CToolbarLabel)

public:
	CToolbarLabel (UINT nID = 0, LPCTSTR lpszText = NULL);

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages, 
						 BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,						
						 BOOL bHighlight = FALSE,						
						 BOOL bDrawBorder = TRUE, 
						 BOOL bGrayDisabledButtons = TRUE);
};

IMPLEMENT_SERIAL(CToolbarLabel, CBCGPToolbarButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CToolbarLabel::CToolbarLabel (UINT nID, LPCTSTR lpszText)
{
	if (lpszText != NULL)	
	{		
		m_strText = lpszText;	
	}	

	m_bText = TRUE;
	m_nID = nID;
	m_iImage = -1;
}

void CToolbarLabel::OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages, 
							  BOOL bHorz, BOOL /*bCustomizeMode*/, BOOL /*bHighlight*/,	
							  BOOL /*bDrawBorder*/,	BOOL /*bGrayDisabledButtons*/)
{
	UINT nStyle = m_nStyle;	
	m_nStyle &= ~TBBS_DISABLED;

	CBCGPToolbarButton::OnDraw (pDC, rect, pImages, bHorz, FALSE,
								FALSE, FALSE, FALSE);

	m_nStyle = nStyle;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_GRID_TREE_DLG, OnGridTreeDlg)
	ON_COMMAND(ID_GRID_VIRTUAL_DLG, OnGridVirtualDlg)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_COMMAND_RANGE(ID_SHORTCUT_1, ID_SHORTCUT_7, OnOutlookBarShortcut)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SHORTCUT_1, ID_SHORTCUT_7, OnUpdateOutlookBarShortcut)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2008, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2008, OnUpdateAppLook)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static LPCTSTR viewTypes [] = 
{
	_T("Basic Grid"),
	_T("Report Control"),
	_T("Cell Types"),
	_T("Custom Colors"),
	_T("Virtual List"),
	_T("Merge Cells"),
	_T("Filtered Grid"),
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2007_1);
	m_nCurrType = theApp.GetInt (_T("ViewTppe"), ID_SHORTCUT_1);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetMenu (NULL);

	OnAppLook (m_nAppLook);

	m_wndToolBar.EnableNavigationButtons (ID_VIEW_BACK, ID_VIEW_FORWARD, 0, 0);

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR256 : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//-----------------------
	// Setup toolbar buttons:
	//-----------------------
	CMenu menuView;
	menuView.LoadMenu (IDR_MENU_VIEW);

	m_wndToolBar.ReplaceButton (ID_TOOLBAR_VIEW, 
		CBCGPToolbarMenuButton ((UINT)-1, menuView.Detach (), -1, _T("&View")));

	CMenu menuGrid;
	menuGrid.LoadMenu (IDR_MENU_GRID);

	m_wndToolBar.ReplaceButton (ID_TOOLBAR_DIALOGS, 
		CBCGPToolbarMenuButton ((UINT)-1, menuGrid.Detach (), -1, _T("&Grid")));

	m_wndToolBar.ReplaceButton (ID_COLOR_LABEL, 
		CToolbarLabel (ID_COLOR_LABEL, _T("Color theme: ")));

	CBCGPToolbarComboBoxButton comboButton (ID_COLOR_THEME_COMBO, 
		CImageHash::GetImageOfCommand (ID_COLOR_THEME_COMBO, FALSE), CBS_DROPDOWNLIST);

	comboButton.AddItem (_T("Light Blue Theme"));
	comboButton.AddItem (_T("Silver Theme"));
	comboButton.AddItem (_T("Green Theme"));
	comboButton.AddItem (_T("Visual Manager Theme"));

	comboButton.SelectItem (theApp.m_Options.m_nColorTheme);

	m_wndToolBar.ReplaceButton (ID_COLOR_THEME_COMBO, comboButton);

	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_FIELD_CHOOSER), NULL, TRUE, TRUE);
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_GROUP_BY_BOX), NULL, TRUE, TRUE);
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_REPORT_PREVIEW), NULL, TRUE, TRUE);
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_MERGE_CELLS), NULL, TRUE, TRUE);
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_UNMERGE_CELLS), NULL, TRUE, TRUE);

	SetHiddenCommands (m_lstHiddenCommands);

	m_wndToolBar.EnableCustomizeButton (TRUE, (UINT)-1, _T("More Items"));

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

	if (!CreateShortcutsBar ())
	{
		TRACE0("Failed to create shortcuts bar\n");
		return -1;      // fail to create
	}

	if (!m_wndCaptionBar.Create (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this,
		ID_VIEW_CAPTIONBAR, -1))
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}

	m_wndCaptionBar.SetFlatBorder ();
	m_wndCaptionBar.SetText (viewTypes [m_nCurrType - ID_SHORTCUT_1]);

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
		TRUE /* Automatic menus scaning */
		);

	pDlgCust->Create ();
}

void CMainFrame::OnOutlookBarShortcut(UINT id)
{
	const int nViewType = id - ID_SHORTCUT_1;

	m_wndCaptionBar.SetText (viewTypes [nViewType]);

    CBCGPGridExampleView* pActiveView = 
		DYNAMIC_DOWNCAST (CBCGPGridExampleView, GetActiveView ());
	if (pActiveView != NULL)
	{
		pActiveView->SetViewType (nViewType);
	}

	m_nCurrType = id;
	theApp.WriteInt (_T("ViewTppe"), m_nCurrType);
}

void CMainFrame::UpdateCurrentView (int nViewType)
{
	m_wndCaptionBar.SetText (viewTypes [nViewType]);

	m_nCurrType = ID_SHORTCUT_1 + nViewType;
	theApp.WriteInt (_T("ViewTppe"), m_nCurrType);
}

void CMainFrame::OnUpdateOutlookBarShortcut (CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nCurrType == pCmdUI->m_nID);
}

BOOL CMainFrame::CreateShortcutsBar ()
{
	CBCGPOutlookWnd::EnableAnimation ();

	const int nInitialWidth = 150;
	const CString strCaption = _T("Shortcuts");

	if (!m_wndShortcutsBar.Create (strCaption, this, 
		CRect (0, 0, nInitialWidth, nInitialWidth), 
		ID_VIEW_OUTLOOKBAR, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		TRACE0("Failed to create outlook bar\n");
		return FALSE;      // fail to create
	}

	CBCGPOutlookWnd* pShortcutsBarContainer = DYNAMIC_DOWNCAST (CBCGPOutlookWnd, 
							m_wndShortcutsBar.GetUnderlinedWindow ());
	if (pShortcutsBarContainer == NULL)
	{
		TRACE0("Cannot get outlook bar container\n");
		return FALSE;
	}

	CBCGPToolBarImages images;
	images.SetImageSize (CSize (32, 32));

	BOOL bAlphaBlend = globalData.bIsOSAlphaBlendingSupport;
	images.Load (bAlphaBlend ? IDB_SHORTCUTS32 : IDB_SHORTCUTS);

	m_wndShortcutsPane1.Create (&m_wndShortcutsBar, dwDefaultToolbarStyle, ID_SHORTCUTS_PANE_1);
	m_wndShortcutsPane1.SetOwner (this);
	m_wndShortcutsPane1.EnableTextLabels(1);
	m_wndShortcutsPane1.EnableDocking (CBRS_ALIGN_ANY);
	
	m_wndShortcutsPane1.AddButton (images.ExtractIcon (0), viewTypes[0], ID_SHORTCUT_1, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton (images.ExtractIcon (1), viewTypes[1], ID_SHORTCUT_2, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton (images.ExtractIcon (2), viewTypes[2], ID_SHORTCUT_3, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton (images.ExtractIcon (3), viewTypes[3], ID_SHORTCUT_4, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton (images.ExtractIcon (4), viewTypes[4], ID_SHORTCUT_5, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton (images.ExtractIcon (5), viewTypes[5], ID_SHORTCUT_6, -1, bAlphaBlend);
	m_wndShortcutsPane1.AddButton (images.ExtractIcon (6), viewTypes[6], ID_SHORTCUT_7, -1, bAlphaBlend);
	
	pShortcutsBarContainer->AddTab (&m_wndShortcutsPane1, strCaption, (UINT)-1, FALSE);

	return TRUE;
}

void CMainFrame::OnAppLook(UINT id)
{
	CWaitCursor wait;

	m_nAppLook = id;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		break;

	case ID_VIEW_APPLOOK_VS2008:
		// enable VS 2008 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2008));
		break;

	case ID_VIEW_APPLOOK_2007_1:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case ID_VIEW_APPLOOK_2007_2:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case ID_VIEW_APPLOOK_2007_4:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	RecalcLayout ();

    CBCGPGridExampleView* pActiveView = 
		DYNAMIC_DOWNCAST (CBCGPGridExampleView, GetActiveView ());
	if (pActiveView != NULL)
	{
		pActiveView->OnUpdateVisualManager ();
	}

	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::UpdateGrid ()
{
    CBCGPGridExampleView* pActiveView = 
		DYNAMIC_DOWNCAST (CBCGPGridExampleView, GetActiveView ());
	if (pActiveView != NULL)
	{
		pActiveView->UpdateGrid ();
	}
}

void CMainFrame::OnGridTreeDlg() 
{
	CWaitCursor wait;

	CTreeDlg dlg;
	dlg.DoModal ();	
}

void CMainFrame::OnGridVirtualDlg() 
{
	CWaitCursor wait;

	CVirtualGridDlg dlg;
	dlg.DoModal ();
}

CBCGPToolbarComboBoxButton* CMainFrame::GetColorCombo ()
{
	return DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (ID_COLOR_THEME_COMBO)));
}

void CMainFrame::SetHiddenCommands (CList<UINT, UINT>& lstHiddenCommands)
{
	for (int i = 0; i < m_wndToolBar.GetCount (); i++)
	{
		CBCGPToolbarButton* pButton = m_wndToolBar.GetButton (i);
		ASSERT_VALID (pButton);

		const BOOL bIsVisible = lstHiddenCommands.Find (pButton->m_nID) == NULL;

		pButton->SetVisible (bIsVisible);

		if (!bIsVisible && i > 0)
		{
			CBCGPToolbarButton* pPrevButton = m_wndToolBar.GetButton (i - 1);
			ASSERT_VALID (pPrevButton);

			if (pPrevButton->m_nStyle & TBBS_SEPARATOR)
			{
				pPrevButton->SetVisible (FALSE);
			}
		}
	}

	m_wndToolBar.AdjustLayout ();

	m_lstHiddenCommands.RemoveAll ();
	m_lstHiddenCommands.AddTail ((CList<UINT, UINT>*)&lstHiddenCommands);
}
