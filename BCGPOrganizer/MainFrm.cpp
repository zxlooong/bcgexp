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
#include "BCGPOrganizer.h"
#include "BCGPOrganizerDoc.h"

#include "MainFrm.h"

#include "OptionsPage.h"
#include "ResourcePage.h"

#include "keys.h"

#include "MainButtonsGroup.h"

#pragma warning (disable : 4706)

#ifndef _BCGCBPRO_STATIC_
#ifdef _AFXDLL
#define COMPILE_MULTIMON_STUBS
#endif // _AFXDLL

#endif

#include "multimon.h"

#pragma warning (default : 4706)

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

const int IdStartProgressTimer = 1;
const int IdShowProgressTimer = 2;

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_VIEW_APPLOOK, OnUpdateDummy)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2007_1, ID_VIEW_APPLOOK_2007_4, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2007_1, ID_VIEW_APPLOOK_2007_4, OnUpdateAppLook)
	ON_COMMAND(ID_STATUSBAR_REFRESH, OnRefresh)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_REFRESH, OnUpdateRefresh)
	ON_UPDATE_COMMAND_UI(ID_MAIL_FIND, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_NAMES_AB, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_NAMES_CHECK, OnUpdateDummy)
	ON_REGISTERED_MESSAGE(BCGM_CHANGE_ACTIVE_TAB, OnActivateShortcut)
	ON_REGISTERED_MESSAGE(BCGM_ON_CHANGE_RIBBON_CATEGORY, OnActivateCategory)
	ON_COMMAND(ID_SHORTCUTS_HOME, OnShortcutsHome)
	ON_COMMAND(ID_SHORTCUTS_MAIL, OnShortcutsMail)
	ON_COMMAND(ID_SHORTCUTS_DOWNLOAD, OnShortcutsDownload)
	ON_COMMAND(ID_SHORTCUTS_ABOUT, OnShortcutsAbout)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND_RANGE(ID_ACTIVATE_VIEW_0, ID_ACTIVATE_VIEW_5, OnActivateView)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ACTIVATE_VIEW_0, ID_ACTIVATE_VIEW_5, OnUpdateActivateView)
	ON_COMMAND(ID_STATUSBAR_ZOOM, OnZoom100)
	ON_COMMAND(ID_STATUSBAR_ZOOM_SLIDER, OnZoom)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_REGISTERED_MESSAGE(BCGM_ON_HIGHLIGHT_RIBBON_LIST_ITEM, OnHighlightRibbonListItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nProgressValue = -1;
	m_bInfiniteProgressMode = TRUE;
}

CMainFrame::~CMainFrame()
{
	for (POSITION pos = m_TooltipImages.GetStartPosition (); pos != NULL;)
	{
		CBCGPToolBarImages* pBmp = NULL;
		UINT uiID;

		m_TooltipImages.GetNextAssoc (pos, uiID, pBmp);
		delete pBmp;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	globalData.m_bUseBuiltIn32BitIcons = TRUE;

	OnAppLook (theApp.m_nAppLook + ID_VIEW_APPLOOK_2007_1);

	CBCGPToolBar::AddToolBarForImageCollection (IDR_MAINFRAME, IDB_MAINFRAME_HC);
	CBCGPToolBar::AddToolBarForImageCollection (IDR_PLANNER, IDB_PLANNER_HC);
	CBCGPToolBar::AddToolBarForImageCollection (IDR_GANTT, IDB_GANTT_HC);
	CBCGPToolBar::AddToolBarForImageCollection (IDR_CATEGORY, IDB_CATEGORY_HC);

	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	};

	if (!CreateStatusBar ())
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!CreateOutlookBar ())
	{
		TRACE0("Failed to create shortcuts bar\n");
		return -1;      // fail to create
	}

	if (!m_wndOutputBar.Create (_T("Information"), this, CRect (0, 0, 100, 100),
		TRUE, 
		ID_VIEW_BAR_OUTPUT,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI,
		CBRS_BCGP_REGULAR_TABS,
		CBRS_BCGP_FLOAT | CBRS_BCGP_RESIZE | CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create output bar\n");
		return FALSE;      // fail to create
	}

	m_wndOutputBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutputBar.SetIcon (m_PanelImages.ExtractIcon (0), FALSE);

	EnableDocking (CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);

	DockControlBar (&m_wndOutlookBar);
	DockControlBar(&m_wndOutputBar);
	
	if (!CreateCaptionBar ())
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}

	m_wndRibbonBar.RecalcLayout ();

	//EnableFullScreenMode (ID_VIEW_FULLSCREEN);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
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

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    CBCGPOrganizerDoc* pDoc = DYNAMIC_DOWNCAST(CBCGPOrganizerDoc, pContext->m_pCurrentDoc);

    if(pDoc != NULL)
    {
        pDoc->CreateViews(this, pContext);
    }

    return CBCGPFrameWnd::OnCreateClient(lpcs, pContext);
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

LRESULT CMainFrame::OnActivateShortcut(WPARAM wParam, LPARAM lParam)
{
	if ((LPVOID)lParam == (LPVOID)m_wndOutlookBar.GetUnderlinedWindow () ||
		lParam == 0)
	{
		int nCategory = m_wndOutlookBar.GetUnderlinedWindow ()->GetTabID ((int) wParam) - 1;
		if (nCategory >= 0)
		{
			m_wndRibbonBar.SetActiveCategory (m_pRibbonCategory [nCategory]);
		}
	}

	m_wndOutputBar.UpdateInfo ((int) wParam);
	return 0L;
}

LRESULT CMainFrame::OnActivateCategory(WPARAM /*wParam*/, LPARAM lParam)
{
	if ((LPVOID)lParam == (LPVOID)&m_wndRibbonBar)
	{
		CBCGPRibbonCategory* pCategory = m_wndRibbonBar.GetActiveCategory ();
		ASSERT_VALID (pCategory);

		ActivateCategory (pCategory);
	}

	return 0L;
}

void CMainFrame::ActivateCategory (CBCGPRibbonCategory* pCategory)
{
	ASSERT_VALID (pCategory);

	if (IsPrintPreview ())
	{
		return;
	}

	CBCGPOrganizerDoc::XMode mode = CBCGPOrganizerDoc::e_ModeUndefined;

	int nShortcut = 0;

	if (pCategory == m_pRibbonCategory[0])
	{
		nShortcut = 0;
		mode = CBCGPOrganizerDoc::e_ModeShortcuts;
	}
	else if (pCategory == m_pRibbonCategory[1])
	{
		nShortcut = 1;
		mode = CBCGPOrganizerDoc::e_ModeMail;
	}
	else if (pCategory == m_pRibbonCategory[2])
	{
		nShortcut = 2;
		mode = CBCGPOrganizerDoc::e_ModeCalendar;
	}
	else if (pCategory == m_pRibbonCategory[3])
	{
		nShortcut = 3;
		mode = CBCGPOrganizerDoc::e_ModeTasks;
	}
	else if (pCategory == m_pRibbonCategory[4])
	{
		nShortcut = 4;
		mode = CBCGPOrganizerDoc::e_ModeMacros;
	}
	else if (pCategory == m_pRibbonCategory[5])
	{
		nShortcut = 5;
		mode = CBCGPOrganizerDoc::e_ModeGantt;
	}

	ASSERT (mode != CBCGPOrganizerDoc::e_ModeUndefined);

	CBCGPOrganizerDoc* pDoc = DYNAMIC_DOWNCAST (CBCGPOrganizerDoc, GetActiveDocument ());
	if (pDoc != NULL)
	{
		pDoc->SetMode (mode);
	}

	int nTab = m_wndOutlookBar.GetUnderlinedWindow ()->GetTabByID (nShortcut + 1);
	if (nTab >= 0)
	{
		m_wndOutlookBar.SetActiveShortcut (nTab);
	}

	OnActivateShortcut (
		(WPARAM)m_wndOutlookBar.GetActiveShortcut (), 
		(LPARAM)&m_wndRibbonBar);

	CBCGPPopupMenu::UpdateAllShadows ();
}

BOOL CMainFrame::CreateOutlookBar ()
{
	const CString strCaption = _T("Shortcuts");
	const int nInitialWidth = 150;

	return m_wndOutlookBar.Create (strCaption, this, 
		CRect (0, 0, nInitialWidth, nInitialWidth), 
		ID_VIEW_BAR_SHORTCUTS, WS_CHILD | WS_VISIBLE | CBRS_LEFT);
}

BOOL CMainFrame::CreateRibbonBar ()
{
	if (!m_wndRibbonBar.Create (this))
	{
		return FALSE;      // fail to create
	}

	//-------------------
	// Load panel images:
	//-------------------
	m_PanelImages.SetImageSize (CSize (16, 16));
	if (!m_PanelImages.Load (IDB_BUTTONS))
	{
		TRACE0("Failed to load panel images\n");
		return FALSE;
	}

	CreateDocumentColors ();

	//-----------------
	// Add main button:
	//-----------------
	AddMainCategory ();

	//----------
	// Add tabs:
	//----------
	m_pRibbonCategory[0] = AddTab_Shortcuts ();
	m_pRibbonCategory[1] = AddTab_Mail ();
	m_pRibbonCategory[2] = AddTab_Calendar ();
	m_pRibbonCategory[3] = AddTab_Tasks ();
	m_pRibbonCategory[4] = AddTab_Macros ();
	m_pRibbonCategory[5] = AddTab_Gantt ();
/*
	//------------------
	// Add context tabs:
	//------------------
	AddContextTab_Picture ();
	AddContextTab_Chart ();
	AddContextTab_Table ();
*/
	//-----------------------------------
	// Add quick access toolbar commands:
	//-----------------------------------
	CList<UINT, UINT> lstQATCmds;

//	lstQATCmds.AddTail (ID_FILE_SAVE);
//	lstQATCmds.AddTail (ID_EDIT_UNDO);
//	lstQATCmds.AddTail (ID_FILE_PRINT_DIRECT);
	lstQATCmds.AddTail (ID_FILE_PRINT_PREVIEW);
	lstQATCmds.AddTail (ID_FILE_PRINT_DIRECT);

	m_wndRibbonBar.SetQuickAccessCommands (lstQATCmds);

	//----------------------------------------
	// Add elements to the right side of tabs:
	//----------------------------------------
	CBCGPRibbonButton* pVisualStyleButton = new CBCGPRibbonButton (ID_VIEW_APPLOOK, _T("Style"), -1, -1);
	pVisualStyleButton->SetMenu (IDR_THEME_MENU, FALSE /* No default command */, TRUE /* Right align */);
	pVisualStyleButton->SetToolTipText (_T("Modify Visual Style"));
	pVisualStyleButton->SetDescription (_T("Choose one of the following looks:\r\nBlue, Black, Silver or Aqua"));
	m_wndRibbonBar.AddToTabs (pVisualStyleButton);

	m_wndRibbonBar.AddToTabs (new CBCGPRibbonButton (ID_APP_ABOUT, _T(""), m_PanelImages.ExtractIcon (0), FALSE, NULL, TRUE));

	m_wndRibbonBar.EnableToolTips (theApp.m_bShowToolTips, theApp.m_bShowToolTipDescr);
	m_wndRibbonBar.EnableKeyTips (theApp.m_bShowKeyTips);

	SetKeys ();

	return TRUE;
}

BOOL CMainFrame::CreateStatusBar ()
{
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;
	}
/*
	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PAGE, _T("Page 1")), _T("Formatted Page Number"));

	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_LINE, _T("Line 1")), _T("Line Number"));

	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_COLUMN, _T("Column 1")), _T("Column"));

	m_wndStatusBar.AddSeparator ();
*/
	HICON hIconRefresh = (HICON) ::LoadImage (
			AfxGetResourceHandle (),
			MAKEINTRESOURCE (IDI_REFRESH),
			IMAGE_ICON,
			::GetSystemMetrics (SM_CXSMICON),
			::GetSystemMetrics (SM_CYSMICON),
			LR_SHARED);

	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_REFRESH, _T("Refresh"), FALSE, hIconRefresh), 
		_T("Refresh"));
/*
	CBCGPRibbonButtonsGroup* pSBGroup = new CBCGPRibbonButtonsGroup;

	CBCGPToolBarImages images1;
	images1.SetImageSize (CSize (14, 14));
	images1.Load (IDB_LAYOUT);

	pSBGroup->SetImages (&images1, NULL, NULL);
	pSBGroup->SetID (ID_GROUP_SHORTCUTS);

	pSBGroup->AddButton (new CBCGPRibbonButton (ID_PRINT_LAYOUT, _T(""), 0));
	pSBGroup->AddButton (new CBCGPRibbonButton (ID_FULL_SCREEN_READING, _T(""), 1));
	pSBGroup->AddButton (new CBCGPRibbonButton (ID_WEB_LAYOUT, _T(""), 2));
	pSBGroup->AddButton (new CBCGPRibbonButton (ID_MASTER_DOCUMENT_TOOLS, _T(""), 3));
	pSBGroup->AddButton (new CBCGPRibbonButton (ID_DRAFT, _T(""), 4));

	m_wndStatusBar.AddExtendedElement (pSBGroup, _T("View Shortcuts"));

	m_wndStatusBar.AddExtendedElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_ZOOM, _T("100%"), FALSE, NULL, _T("1000%")), _T("Zoom"));

	CBCGPRibbonSlider* pSlider = new CBCGPRibbonSlider (ID_STATUSBAR_ZOOM_SLIDER);
	pSlider->SetZoomButtons ();
	pSlider->SetRange (0, 200);
	pSlider->SetPos (100);

	m_wndStatusBar.AddExtendedElement (pSlider, _T("Zoom Slider"));
*/
	m_wndStatusBar.AddExtendedElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_ZOOM, _T("100%"), FALSE, NULL, _T("1000%")), _T("Zoom"));

	CBCGPRibbonSlider* pSlider = new CBCGPRibbonSlider (ID_STATUSBAR_ZOOM_SLIDER);
	pSlider->SetZoomButtons ();
	pSlider->SetPageSize (1);
	pSlider->SetRange (0, 16);
	pSlider->SetPos (8);

	m_wndStatusBar.AddExtendedElement (pSlider, _T("Zoom Slider"));
	m_pZoomSlider = pSlider;

	return TRUE;
}

BOOL CMainFrame::CreateCaptionBar ()
{
	if (!m_wndCaptionBar.Create (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this,
		ID_VIEW_BAR_CAPTION, -1))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;      // fail to create
	}

	m_wndCaptionBar.SetFlatBorder ();
	m_wndCaptionBar.SetText (_T("<Put your caption here>"));
//	m_bmpCaption.LoadBitmap (IDB_CAPTION);
//	m_wndCaptionBar.SetBitmap (m_bmpCaption, RGB (255, 0, 255));

	return TRUE;
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

	static ColorTableEntry colorsCalendar [] =
	{
		{	RGB (156, 191, 139),	_T("")		},
		{	RGB (209, 149, 170),	_T("")		},
		{	RGB (176, 182, 190),	_T("")		},
		{	RGB (140, 191, 192),	_T("")		},
		{	RGB (140, 140, 215),	_T("")		},
		{	RGB (141, 193, 157),	_T("")		},
		{	RGB (211, 150, 150),	_T("")		},
		{	RGB (186, 186, 137),	_T("")		},
		{	RGB (174, 153, 216),	_T("")		},
		{	RGB (195, 176, 141),	_T("")		},
		{	RGB (144, 182, 200),	_T("")		},
		{	RGB (255, 223, 134),	_T("")		},
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

	m_lstCalendarColors.RemoveAll ();
	nNumColours = sizeof (colorsCalendar) / sizeof (ColorTableEntry);

	for (i = 0; i < nNumColours; i++)
	{
		m_lstCalendarColors.AddTail (colorsCalendar [i].color);
		//CBCGPRibbonColorButton::SetColorName (colorsCalendar [i].color, colorsCalendar [i].szName);
	};
}

void CMainFrame::AddMainCategory ()
{
	m_MainButton.SetImage (IDB_MAIN);
	m_MainButton.SetToolTipText (_T("Main Button"));
	m_MainButton.SetDescription (_T("Click here to see everything you can do with your document, including saving, printing or sharing it with others"));
	m_MainButton.SetID (ID_MAIN);

	m_wndRibbonBar.SetMainButton (&m_MainButton, CSize (45, 45));

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("Main Menu"), IDB_FILE_SMALL, IDB_FILE_LARGE);

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_NEW, _T("&New"), 0, 0));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_OPEN, _T("&Open"), 1, 1));

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE, _T("&Save"), 2, 2));

	CBCGPRibbonButton* pBtnSaveAs = new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("Save &As..."), 3, 3);
/*
	pBtnSaveAs->AddSubItem (new CBCGPRibbonLabel (_T("Save a copy of the document")));
	pBtnSaveAs->AddSubItem (new CBCGPRibbonButton (ID_FILE_SAVE_AS_DOCUMENT, _T("&Word Document"), 9, 9, TRUE));
	pBtnSaveAs->AddSubItem (new CBCGPRibbonButton (ID_FILE_SAVE_AS_TEMPLATE, _T("Word &Template"), 10, 10, TRUE));
	pBtnSaveAs->AddSubItem (new CBCGPRibbonButton (ID_FILE_SAVE_AS_DOCUMENT_OLD, _T("Word &97-2003 Document"), 11, 11, TRUE));
	pBtnSaveAs->AddSubItem (new CBCGPRibbonButton (ID_FILE_SAVE_AS_ADDINS, _T("&Find add-ins for other file formats"), 12, 12, TRUE));
	pBtnSaveAs->AddSubItem (new CBCGPRibbonButton (ID_FILE_SAVE_AS_OTHER, _T("&Other Formats"), 3, 3, TRUE));
*/
	pMainPanel->Add (pBtnSaveAs);

	pMainPanel->Add (new CBCGPRibbonSeparator (TRUE));

	CBCGPRibbonButton* pBtnPrint = new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 4, 4);
	pBtnPrint->AddSubItem (new CBCGPRibbonLabel (_T("Preview and print the document")));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 4, 4, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_DIRECT, _T("&Quick Print"), 13, 13, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_PREVIEW, _T("Print Pre&view"), 14, 14, TRUE));
	pMainPanel->Add (pBtnPrint);

	CBCGPRibbonButton* pBtnPrepare = new CBCGPRibbonButton (ID_FILE_PREPARE, _T("Pr&epare"), 5, 5);
	pBtnPrepare->AddSubItem (new CBCGPRibbonLabel (_T("Prepare the document for distribution")));
	pBtnPrepare->AddSubItem (new CBCGPRibbonButton (ID_FILE_PREPARE_PROPERTIES, _T("&Properties"), 15, 15, TRUE));
	pBtnPrepare->AddSubItem (new CBCGPRibbonButton (ID_FILE_PREPARE_INSPECT, _T("&Inspect Document"), 16, 16, TRUE));
	pBtnPrepare->AddSubItem (new CBCGPRibbonButton (ID_FILE_PREPARE_ENCRYPT, _T("&Encrypt Document"), 17, 17, TRUE));
	pBtnPrepare->AddSubItem (new CBCGPRibbonButton (ID_FILE_PREPARE_ADD_SIGNATURE, _T("Add a Digital &Signature"), 18, 18, TRUE));
	pBtnPrepare->AddSubItem (new CBCGPRibbonButton (ID_FILE_PREPARE_MARK_AS_FINAL, _T("Mark as &Final"), 19, 19, TRUE));
	pBtnPrepare->AddSubItem (new CBCGPRibbonButton (ID_FILE_PREPARE_RUN_CHECKER, _T("Run &Compatibility Checker"), 20, 20, TRUE));
	pBtnPrepare->SetDefaultCommand (FALSE);
	pMainPanel->Add (pBtnPrepare);

	CBCGPRibbonButton* pBtnSend = new CBCGPRibbonButton (ID_FILE_SEND, _T("Sen&d"), 6, 6);
	pBtnSend->AddSubItem (new CBCGPRibbonLabel (_T("Send a copy of the document to other people")));
	pBtnSend->AddSubItem (new CBCGPRibbonButton (ID_FILE_SEND_EMAIL, _T("&E-mail"), 21, 21, TRUE));
	pBtnSend->AddSubItem (new CBCGPRibbonButton (ID_FILE_SEND_FAX, _T("Internet Fa&x"), 22, 22, TRUE));
	pBtnSend->SetDefaultCommand (FALSE);
	pMainPanel->Add (pBtnSend);

	CBCGPRibbonButton* pBtnPublish = new CBCGPRibbonButton (ID_FILE_PUBLISH, _T("P&ublish"), 7, 7);
	pBtnPublish->AddSubItem (new CBCGPRibbonLabel (_T("Distribute the document to other people")));
	pBtnPublish->AddSubItem (new CBCGPRibbonButton (ID_FILE_PUBLISH_BLOG, _T("&Blog"), 23, 23, TRUE));
	pBtnPublish->AddSubItem (new CBCGPRibbonButton (ID_FILE_PUBLISH_DOCMANAGE_SERVER, _T("&Document Management Server"), 24, 24, TRUE));
	pBtnPublish->AddSubItem (new CBCGPRibbonButton (ID_FILE_PUBLISH_CREATE_DOCWORKSPACE, _T("&Create Document Workspace"), 25, 25, TRUE));
	pBtnPublish->SetDefaultCommand (FALSE);
	pMainPanel->Add (pBtnPublish);

	pMainPanel->Add (new CBCGPRibbonSeparator (TRUE));

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_CLOSE, _T("&Close"), 8, 8));

	CMainButtonsGroup* pGroup = new CMainButtonsGroup (_T("Shortcuts"));
	pGroup->AddButton (new CBCGPRibbonButton (ID_ACTIVATE_VIEW_0, _T("&1. Home"), 28));
	pGroup->AddButton (new CBCGPRibbonButton (ID_ACTIVATE_VIEW_1, _T("&2. Mail"), 29));
	pGroup->AddButton (new CBCGPRibbonButton (ID_ACTIVATE_VIEW_2, _T("&3. Calendar"), 30));
	pGroup->AddButton (new CBCGPRibbonButton (ID_ACTIVATE_VIEW_3, _T("&4. Tasks"), 31));
	pGroup->AddButton (new CBCGPRibbonButton (ID_ACTIVATE_VIEW_4, _T("&5. Macros"), 32));
	pGroup->AddButton (new CBCGPRibbonButton (ID_ACTIVATE_VIEW_5, _T("&6. Gantt"), 33));
	pMainPanel->AddToRight (pGroup);

	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_TOOLS_OPTIONS, _T("Opt&ions"), 26));
	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_APP_EXIT, _T("E&xit"), 27));
}

CBCGPRibbonCategory* CMainFrame::AddTab_Shortcuts ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		c_ViewNames[CBCGPOrganizerDoc::e_ModeShortcuts], IDB_SHORTCUTS_RIBBON_SMALL, IDB_SHORTCUTS_RIBBON_LARGE);
	pCategory->SetKeys (_T("h"));

	CBCGPRibbonPanel* pPanelActions = pCategory->AddPanel (_T("Actions"), m_PanelImages.ExtractIcon (1));
	pPanelActions->Add (new CBCGPRibbonButton (ID_SHORTCUTS_HOME, _T("Home Page"), 0, 0));
	pPanelActions->Add (new CBCGPRibbonButton (ID_SHORTCUTS_MAIL, _T("E-mail"), 1, 1));	
	pPanelActions->Add (new CBCGPRibbonButton (ID_SHORTCUTS_DOWNLOAD, _T("Download Evaluation"), 2, 2));
	pPanelActions->Add (new CBCGPRibbonSeparator ());
	pPanelActions->Add (new CBCGPRibbonButton (ID_SHORTCUTS_ABOUT, _T("About Organizer"), 3, 3));

	return pCategory;
}

CBCGPRibbonCategory* CMainFrame::AddTab_Mail ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		c_ViewNames[CBCGPOrganizerDoc::e_ModeMail], IDB_MAIL_SMALL, IDB_MAIL_LARGE);
	pCategory->SetKeys (_T("m"));

	CBCGPRibbonPanel* pPanelActions = pCategory->AddPanel (_T("Actions"), m_PanelImages.ExtractIcon (2));
	pPanelActions->Add (new CBCGPRibbonButton (ID_MAIL_NEW, _T("New"), 0, 0));
	pPanelActions->Add (new CBCGPRibbonButton (ID_MAIL_REMOVE, _T("Delete"), 1, 1));
	pPanelActions->Add (new CBCGPRibbonButton (ID_MAIL_FIND, _T("Find"), 2, 2));

	CBCGPRibbonPanel* pPanelNames = pCategory->AddPanel (_T("Names"), m_PanelImages.ExtractIcon (3));
	pPanelNames->Add (new CBCGPRibbonButton (ID_MAIL_NAMES_AB, _T("Address Book"), 3, 3));
	pPanelNames->Add (new CBCGPRibbonButton (ID_MAIL_NAMES_CHECK, _T("Check Names"), 4, 4));

	CBCGPRibbonPanel* pPanelView = pCategory->AddPanel (_T("View"), m_PanelImages.ExtractIcon (4));
	pPanelView->Add (new CBCGPRibbonButton (ID_GRID_VIEW_GROUPBOX, _T("Group By Box"), 5, -1));
	pPanelView->Add (new CBCGPRibbonButton (ID_GRID_VIEW_FIELDCHOOSER, _T("Field Chooser"), 6, -1));
	pPanelView->Add (new CBCGPRibbonCheckBox (ID_GRID_VIEW_COLUMN_AUTO_RESIZE, _T("Column Auto-Resize")));

	return pCategory;
}

CBCGPRibbonCategory* CMainFrame::AddTab_Calendar ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		c_ViewNames[CBCGPOrganizerDoc::e_ModeCalendar], IDB_PLANNER_SMALL, IDB_PLANNER_LARGE);
	pCategory->SetKeys (_T("c"));

	CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel (_T("Clipboard"), m_PanelImages.ExtractIcon (5));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_PASTE, _T("Paste"), 0, 0));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CUT, _T("Cut"), 1, -1));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_COPY, _T("Copy"), 2, -1));

	CBCGPRibbonPanel* pPanelActions = pCategory->AddPanel (_T("Actions"), m_PanelImages.ExtractIcon (6));
	CBCGPRibbonButton* pBtnNew = new CBCGPRibbonButton (ID_PLANNER_NEW, _T("New"), 3, 1);
	pBtnNew->SetMenu (IDR_PLANNER_NEW, TRUE);
	pPanelActions->Add (pBtnNew);
	pPanelActions->Add (new CBCGPRibbonButton (ID_PLANNER_OPEN_APP, _T("Open"), 4, 2));
	pPanelActions->Add (new CBCGPRibbonButton (ID_PLANNER_REMOVE_APP, _T("Delete"), 5, 3));
	CBCGPRibbonButton* pBtnGoto = new CBCGPRibbonButton (0, _T("Go To\ng"), 6, 4);
	pBtnGoto->SetMenu (IDR_PLANNER_GOTO);
	pPanelActions->Add (pBtnGoto);

	CBCGPRibbonPanel* pPanelMode = pCategory->AddPanel (_T("Mode"), m_PanelImages.ExtractIcon (7));
	pPanelMode->Add (new CBCGPRibbonButton (ID_PLANNER_MODE_DAY, _T("Day"), 7, 5));
	pPanelMode->Add (new CBCGPRibbonButton (ID_PLANNER_MODE_WORKWEEK, _T("Work Week"), 8, 6));
	pPanelMode->Add (new CBCGPRibbonButton (ID_PLANNER_MODE_WEEK, _T("Week"), 9, 7));
	pPanelMode->Add (new CBCGPRibbonButton (ID_PLANNER_MODE_MONTH, _T("Month"), 10, 8));

	CBCGPRibbonPanel* pPanelView = pCategory->AddPanel (_T("View"), m_PanelImages.ExtractIcon (8));
	CBCGPRibbonButton* pBtnScale = new CBCGPRibbonButton (ID_PLANNER_TIMESCALE, _T("Time Scale"), 11, 9);
	pBtnScale->SetMenu (IDR_PLANNER_TIMESCALE, FALSE);
	pPanelView->Add (pBtnScale);
	pPanelView->Add (new CBCGPRibbonCheckBox (ID_PLANNER_DRAW_TIME_AS_ICONS, _T("Draw time as icons")));
	pPanelView->Add (new CBCGPRibbonCheckBox (ID_PLANNER_DRAW_TIME_FINISH, _T("Show end time")));
	pPanelView->Add (new CBCGPRibbonCheckBox (ID_PLANNER_COMPRESS_WEEKEND, _T("Compress weekend")));
	pPanelView->Add (new CBCGPRibbonSeparator ());

	CBCGPRibbonColorButton* pColor = new CBCGPRibbonColorButton (ID_PLANNER_DRAW_BACKGROUND, 
		_T("Background\nsb"), TRUE, 12, 10, 
		theApp.m_OptionsPlanner.m_clrBackground == CLR_DEFAULT
			? (COLORREF)-1
			: theApp.m_OptionsPlanner.m_clrBackground);
	pColor->SetDefaultCommand (FALSE);
	pColor->SetAlwaysLargeImage ();
	pColor->EnableAutomaticButton (_T("Default"), RGB (255, 255, 255));
	pColor->SetColumns (6);
	pColor->AddColorsGroup (_T("Calendar Colors"), m_lstCalendarColors);
	pPanelView->Add (pColor);

	m_pCalendarColors = pColor;

	pPanelView->Add (new CBCGPRibbonButton (ID_PLANNER_DRAW_APP_GRADIENT, _T(""), 13, -1));
	pPanelView->Add (new CBCGPRibbonButton (ID_PLANNER_DRAW_APP_ROUNDED, _T(""), 14, -1));
	pPanelView->Add (new CBCGPRibbonButton (ID_PLANNER_DRAW_APP_DURATION, _T(""), 15, -1));

	CBCGPRibbonButton* pElement = 
		DYNAMIC_DOWNCAST(CBCGPRibbonButton, pPanelActions->FindByID (ID_PLANNER_NEW_APPOINTMENT));
	if (pElement != NULL)
	{
		pElement->SetImageIndex (16, FALSE);
	}
	pElement = DYNAMIC_DOWNCAST(CBCGPRibbonButton, pPanelActions->FindByID (ID_PLANNER_NEW_REC_APPOINTMENT));
	if (pElement != NULL)
	{
		pElement->SetImageIndex (17, FALSE);
	}
	pElement = DYNAMIC_DOWNCAST(CBCGPRibbonButton, pPanelActions->FindByID (ID_GOTO_TODAY));
	if (pElement != NULL)
	{
		pElement->SetImageIndex (18, FALSE);
	}

	return pCategory;
}

CBCGPRibbonCategory* CMainFrame::AddTab_Tasks ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		c_ViewNames[CBCGPOrganizerDoc::e_ModeTasks], IDB_TASKS_SMALL, IDB_TASKS_LARGE);
	pCategory->SetKeys (_T("t"));

	CBCGPRibbonPanel* pPanelActions = pCategory->AddPanel (_T("Actions"), m_PanelImages.ExtractIcon (9));
	pPanelActions->Add (new CBCGPRibbonButton (ID_TASKS_NEW, _T("New"), 0, 0));
	pPanelActions->Add (new CBCGPRibbonButton (ID_TASKS_OPEN, _T("Open"), 1, 1));
	pPanelActions->Add (new CBCGPRibbonButton (ID_TASKS_REMOVE, _T("Delete"), 2, 2));

	CBCGPRibbonPanel* pPanelManage = pCategory->AddPanel (_T("Manage"), m_PanelImages.ExtractIcon (10));
	pPanelManage->Add (new CBCGPRibbonButton (ID_TASKS_MARK_COMPLETE, _T("Mark Complete"), 3, 3));

	CBCGPRibbonPanel* pPanelView = pCategory->AddPanel (_T("View"), m_PanelImages.ExtractIcon (4));
	pPanelView->Add (new CBCGPRibbonButton (ID_GRID_VIEW_GROUPBOX, _T("Group By Box"), 4, -1));
	pPanelView->Add (new CBCGPRibbonButton (ID_GRID_VIEW_FIELDCHOOSER, _T("Field Chooser"), 5, -1));
	pPanelView->Add (new CBCGPRibbonCheckBox (ID_GRID_VIEW_COLUMN_AUTO_RESIZE, _T("Column Auto-Resize")));

	return pCategory;
}

CBCGPRibbonCategory* CMainFrame::AddTab_Macros ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		c_ViewNames[CBCGPOrganizerDoc::e_ModeMacros], IDB_MACROS_SMALL, IDB_MACROS_LARGE);
	pCategory->SetKeys (_T("r"));

	CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel (_T("Clipboard"), m_PanelImages.ExtractIcon (5));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_PASTE, _T("Paste"), 0, 0));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CUT, _T("Cut"), 1, -1));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_COPY, _T("Copy"), 2, -1));

	CBCGPRibbonFontComboBox::m_bDrawUsingFont = TRUE;
	CBCGPRibbonPanel* pPanelFont = pCategory->AddPanel (_T("Font"), m_PanelImages.ExtractIcon (12));
	CBCGPRibbonButtonsGroup* pFontGroup = new CBCGPRibbonButtonsGroup;

	CBCGPRibbonFontComboBox* pFontCombo = new CBCGPRibbonFontComboBox (ID_FONT_FONT);
	pFontCombo->SelectItem (_T("Courier New"));
	pFontGroup->AddButton (pFontCombo);

	CBCGPRibbonComboBox* pFontSizeCombo = new CBCGPRibbonComboBox (ID_FONT_SIZE, TRUE, 20);
	pFontSizeCombo->AddItem (_T("8"));
	pFontSizeCombo->AddItem (_T("9"));
	pFontSizeCombo->AddItem (_T("10"));
	pFontSizeCombo->AddItem (_T("11"));
	pFontSizeCombo->AddItem (_T("12"));
	pFontSizeCombo->AddItem (_T("14"));
	pFontSizeCombo->AddItem (_T("16"));
	pFontSizeCombo->AddItem (_T("18"));
	pFontSizeCombo->AddItem (_T("20"));
	pFontSizeCombo->AddItem (_T("22"));
	pFontSizeCombo->AddItem (_T("24"));
	pFontSizeCombo->AddItem (_T("26"));
	pFontSizeCombo->AddItem (_T("28"));
	pFontSizeCombo->AddItem (_T("36"));
	pFontSizeCombo->AddItem (_T("48"));
	pFontSizeCombo->AddItem (_T("72"));
	pFontSizeCombo->SelectItem (5);
	pFontGroup->AddButton (pFontSizeCombo);

	pPanelFont->Add (pFontGroup);

	pPanelFont->AddToolBar (IDR_MACROS_FONT);
	pPanelFont->SetElementMenu (ID_FONT_QUALITY, IDR_FONT_QUALITY);
	pPanelFont->EnableLaunchButton (ID_FONT_BOX);

	CBCGPRibbonPanel* pPanelBM = pCategory->AddPanel (_T("Bookmarks"), m_PanelImages.ExtractIcon (13));
	pPanelBM->Add (new CBCGPRibbonButton (ID_EDIT_TOGGLEBOOKMARK, _T("Toogle Bookmark"), 3, 1));
	pPanelBM->Add (new CBCGPRibbonButton (ID_EDIT_NEXTBOOKMARK, _T("Next Bookmark"), 4, -1));
	pPanelBM->Add (new CBCGPRibbonButton (ID_EDIT_PREVIOUSBOOKMARK, _T("Previous Bookmark"), 5, -1));
	pPanelBM->Add (new CBCGPRibbonButton (ID_EDIT_CLEAR_ALLBOOKMARKS, _T("Clear All Bookmarks"), 6, -1));

	CBCGPRibbonPanel* pPanelView = pCategory->AddPanel (_T("View"), m_PanelImages.ExtractIcon (14));
	pPanelView->Add (new CBCGPRibbonCheckBox (ID_EDIT_ENABLEOUTLINING, _T("Enable Outlining")));
	pPanelView->Add (new CBCGPRibbonCheckBox (ID_EDIT_AUTOOUTLINING, _T("Automating Outlining")));
	pPanelView->Add (new CBCGPRibbonCheckBox (ID_EDIT_LINENUMBERS, _T("Line Numbers")));

	CBCGPRibbonPanel* pPanelEditing = pCategory->AddPanel (_T("Editing"), m_PanelImages.ExtractIcon (15));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_FIND, _T("Find"), 7, 2));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_REPLACE, _T("Replace"), 8, -1));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_SELECT_ALL, _T("Select All"), 9, -1));
	pPanelEditing->Add (new CBCGPRibbonButton (ID_EDIT_GOTO_LINE, _T("Go To..\ng"), 10, -1));

	return pCategory;
}

CBCGPRibbonCategory* CMainFrame::AddTab_Gantt ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		c_ViewNames[CBCGPOrganizerDoc::e_ModeGantt], IDB_GANTT_SMALL, IDB_GANTT_LARGE);
	pCategory->SetKeys (_T("g"));

	CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel (_T("Clipboard"), m_PanelImages.ExtractIcon (5));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_PASTE, _T("Paste"), 0, 0));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CUT, _T("Cut"), 1, -1));
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_COPY, _T("Copy"), 2, -1));

	CBCGPRibbonPanel* pPanelActions = pCategory->AddPanel (_T("Actions"), m_PanelImages.ExtractIcon (16));
	CBCGPRibbonButton* pBtnNew = new CBCGPRibbonButton (ID_GANTT_NEW, _T("New"), 3, 1);
	pBtnNew->SetMenu (IDR_GANTT_NEW, TRUE);
	pPanelActions->Add (pBtnNew);	
	pPanelActions->Add (new CBCGPRibbonButton (ID_GANTT_OPEN_TASK, _T("Open"), 4, 2));
	pPanelActions->Add (new CBCGPRibbonButton (ID_GANTT_REMOVE_TASK, _T("Delete"), 5, 3));
	CBCGPRibbonButton* pBtnGoto = new CBCGPRibbonButton (0, _T("Go To\ng"), 7, 5);
	pBtnGoto->SetMenu (IDR_GANTT_GOTO);
	pPanelActions->Add (pBtnGoto);

	CBCGPRibbonPanel* pPanelManage = pCategory->AddPanel (_T("Manage"), m_PanelImages.ExtractIcon (17));
	pPanelManage->Add (new CBCGPRibbonButton (ID_GANTT_LINK, _T("Link Tasks"), 11, -1));
	pPanelManage->Add (new CBCGPRibbonButton (ID_GANTT_UNLINK, _T("Unlink Tasks"), 12, -1));
	pPanelManage->Add (new CBCGPRibbonButton (ID_GANTT_MARK_COMPLETE, _T("Mark Complete"), 6, -1));//4));

	CBCGPRibbonPanel* pPanelView = pCategory->AddPanel (_T("View"), m_PanelImages.ExtractIcon (18));

	CBCGPRibbonColorButton* pColor = new CBCGPRibbonColorButton (ID_GANTT_DRAW_BACKGROUND, 
		_T("Background\nsb"), TRUE, 8, 6, 
		theApp.m_OptionsGantt.m_clrBackground == CLR_DEFAULT
			? (COLORREF)-1
			: theApp.m_OptionsGantt.m_clrBackground);
	pColor->SetDefaultCommand (FALSE);
	pColor->SetAlwaysLargeImage ();
	pColor->EnableAutomaticButton (_T("Default"), RGB (255, 255, 255));
	pColor->SetColumns (6);
	pColor->AddColorsGroup (_T("Gantt Colors"), m_lstCalendarColors);
	pPanelView->Add (pColor);

	m_pGanttColors = pColor;

	CBCGPRibbonButton* pElement = 
		DYNAMIC_DOWNCAST(CBCGPRibbonButton, pPanelActions->FindByID (ID_GANTT_NEW_TASK));
	if (pElement != NULL)
	{
		pElement->SetImageIndex (9, FALSE);
	}
	pElement = DYNAMIC_DOWNCAST(CBCGPRibbonButton, pPanelActions->FindByID (ID_GOTO_TODAY));
	if (pElement != NULL)
	{
		pElement->SetImageIndex (10, FALSE);
	}

	return pCategory;
}

void CMainFrame::OnAppLook(UINT id)
{
	theApp.m_nAppLook = id - ID_VIEW_APPLOOK_2007_1;

	switch (theApp.m_nAppLook)
	{
	case 0:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
		break;
		
	case 1:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
		break;

	case 2:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
		break;

	case 3:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
		break;
	}

	if (!m_wndOutlookBar.IsMode2003 ())
	{
		m_wndOutlookBar.SetMode2003 (TRUE);
	}

	CBCGPVisualManager::SetDefaultManager ( RUNTIME_CLASS (CBCGPVisualManager2007));

	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	CRect rectWindow;
	GetWindowRect (rectWindow);

	SetWindowPos(&wndTop, 0, 0, rectWindow.Width (), rectWindow.Height (), 
		SWP_NOMOVE | SWP_NOZORDER);

	RecalcLayout ();

	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (theApp.m_nAppLook == (pCmdUI->m_nID - ID_VIEW_APPLOOK_2007_1));
}

CBCGPToolBarImages* CMainFrame::GetTooltipImage (UINT uiID)
{
	if (!theApp.m_bShowToolTipDescr)
	{
		return NULL;
	}

	UINT uiResID = 0;

	switch (uiID)
	{
	case ID_MAIN:
		uiResID = IDB_TOOLTIP_MAIN;
		break;

	case ID_FONT_BOX:
		uiResID = IDB_TOOLTIP_FONT;
		break;
	}

	if (uiResID == 0)
	{
		return NULL;
	}

	CBCGPToolBarImages* pBmp = NULL;

	if (!m_TooltipImages.Lookup (uiID, pBmp))
	{
		pBmp = new CBCGPToolBarImages;
		pBmp->Load (uiResID);
		pBmp->SetSingleImage ();

		m_TooltipImages.SetAt (uiID, pBmp);
	}

	return pBmp;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	if (!CBCGPFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	if (theApp.GetProfileInt (_T("Document"), _T("Mode"), CBCGPOrganizerDoc::e_ModeUndefined) ==
		CBCGPOrganizerDoc::e_ModeUndefined)
	{
		m_wndOutlookBar.SetActiveShortcut (0);
	}

	if (m_wndRibbonBar.GetHideFlags () == 0)
	{
		m_wndRibbonBar.SetActiveCategory (m_pRibbonCategory[m_wndOutlookBar.GetActiveShortcut ()]);
	}

	CBCGPDockManager* pDockManager = GetDockManager ();

	if (pDockManager != NULL)
	{
		CWnd* pDockSite = pDockManager->GetDockSite ();

		if (pDockSite != NULL)
		{
			CRect rectWnd;
			pDockManager->GetDockSite ()->SetRedraw (FALSE);
			pDockManager->GetDockSite ()->GetWindowRect (rectWnd);
			pDockManager->GetDockSite ()->SetWindowPos (NULL, -1, -1, 
				rectWnd.Width () + 1, rectWnd.Height () + 1, 
				SWP_NOZORDER |  SWP_NOMOVE | SWP_NOACTIVATE);
			pDockManager->GetDockSite ()->SetWindowPos (NULL, -1, -1, 
				rectWnd.Width (), rectWnd.Height (), 
				SWP_NOZORDER |  SWP_NOMOVE  | SWP_NOACTIVATE);
			pDockManager->GetDockSite ()->SetRedraw (TRUE);
			pDockManager->GetDockSite ()->RedrawWindow (NULL, NULL, 
				RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
		}
	}

	// Force resize:
	CRect rectWindow;
	GetWindowRect (rectWindow);

	rectWindow.right++;
	MoveWindow (rectWindow);

	// Show progress bar after the short delay:
	SetTimer (IdStartProgressTimer, 500, NULL);

	m_wndOutputBar.UpdateInfo (m_wndOutlookBar.GetActiveShortcut ());

	m_wndOutlookBar.RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_ERASE | RDW_FRAME | RDW_INVALIDATE);

	return TRUE;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent) 
{
	if (nIDEvent == IdStartProgressTimer)
	{
		ShowProgress ();
		KillTimer (IdStartProgressTimer);
	}

	if (nIDEvent == IdShowProgressTimer)
	{
		m_nProgressValue++;

		if (m_nProgressValue > 100)
		{
			ShowProgress (FALSE);

			if (!m_bInfiniteProgressMode)
			{
				// Show "new mail" popup window:
				CBCGPPopupWindow* pPopup = new CBCGPPopupWindow;

				pPopup->SetAnimationType (CBCGPPopupMenu::FADE);
				pPopup->SetAnimationSpeed (30);
				pPopup->SetTransparency (200);
				pPopup->SetSmallCaption (TRUE);
				pPopup->SetAutoCloseTime (3000);

				CBCGPPopupWndParams params;
				
				params.m_strText = _T("Sender: John Smith\r\nHello, I'm sending you the requsted information. Please follow the link below to open the document");
				params.m_strURL = _T("Click here to open");
				params.m_hIcon = theApp.LoadIcon (IDR_MAINFRAME);

				params.m_nURLCmdID = 101;

				pPopup->Create (this, params);
			}
		}
		else
		{
			CBCGPRibbonProgressBar* pProgress = DYNAMIC_DOWNCAST (
				CBCGPRibbonProgressBar,
				m_wndStatusBar.FindElement (ID_STATUSBAR_PROGRESS));
			ASSERT_VALID (pProgress);

			pProgress->SetPos (m_nProgressValue, TRUE);
		}
	}
}

void CMainFrame::ShowProgress (BOOL bShow)
{
	if (bShow)
	{
		int cxFree = m_wndStatusBar.GetSpace ();
		if (cxFree < 20)
		{
			// Not enough space for progress bar
			return;
		}

		int cxProgress = min (cxFree, 150);

		CBCGPRibbonProgressBar* pProgressBar = 
			new CBCGPRibbonProgressBar (ID_STATUSBAR_PROGRESS, cxProgress);

		pProgressBar->SetInfiniteMode (m_bInfiniteProgressMode);

		m_wndStatusBar.AddDynamicElement (pProgressBar);

		m_nProgressValue = 0;

		SetTimer (IdShowProgressTimer, 10, NULL);
	}
	else
	{
		KillTimer (IdShowProgressTimer);
		m_wndStatusBar.RemoveElement (ID_STATUSBAR_PROGRESS);
		m_nProgressValue = -1;
	}

	m_wndStatusBar.RecalcLayout ();
	m_wndStatusBar.RedrawWindow ();

	CBCGPPopupMenu::UpdateAllShadows ();
}

void CMainFrame::OnRefresh()
{
	m_bInfiniteProgressMode = FALSE;
	ShowProgress ();
}

void CMainFrame::OnUpdateRefresh(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (m_nProgressValue < 0);
}

void CMainFrame::SetDateInterval (const COleDateTime& date1, const COleDateTime& date2)
{
	CBCGPOrganizerDoc* pDoc = (CBCGPOrganizerDoc*) GetActiveDocument ();
	if (pDoc != NULL)
	{
		ASSERT_VALID (pDoc);
		pDoc->SetDateInterval (date1, date2);
	}
}

void CMainFrame::SetCaptionText (const CString& strText)
{
	BOOL bWasEmptyText = m_wndCaptionBar.GetText ().IsEmpty ();

	m_wndCaptionBar.SetText (strText);

	if (strText.IsEmpty () || bWasEmptyText)
	{
		m_wndCaptionBar.RedrawWindow ();
	}	
}

void CMainFrame::OnUpdateDummy (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CMainFrame::OnShortcutsHome ()
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com"), NULL, NULL, NULL);
}

void CMainFrame::OnShortcutsMail ()
{
	::ShellExecute (NULL, NULL, _T("mailto:info@bcgsoft.com"), NULL, NULL, NULL);
}

void CMainFrame::OnShortcutsDownload ()
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com/download.htm"), NULL, NULL, NULL);
}

void CMainFrame::OnShortcutsAbout ()
{
	SendMessage (WM_COMMAND, ID_APP_ABOUT, 0);
}

void CMainFrame::SetActiveView (int nView)
{
	CBCGPRibbonCategory* pCategory = m_pRibbonCategory[nView];

	if (m_wndRibbonBar.GetHideFlags () == 0)
	{
		m_wndRibbonBar.SetActiveCategory (pCategory);
	}
	else
	{
		ActivateCategory (pCategory);
	}
}

void CMainFrame::OnToolsOptions ()
{
	ShowOptions (0);
}

LRESULT CMainFrame::OnRibbonCustomize (WPARAM /*wp*/, LPARAM /*lp*/)
{
	ShowOptions (1);
	return 1;
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
	lstPopular.AddTail (ID_FILE_SEND_EMAIL);

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

	// Create "Options" and "Resources" pages:
	COptionsPage pageOptions;
	CResourcePage pageRes;

	// Create property sheet:
	COptionsPropSheet propSheet (this, nPage);
	propSheet.EnablePageHeader (max (60, globalData.GetTextHeight () * 3));

	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	propSheet.SetLook (CBCGPPropertySheet::PropSheetLook_List, 124);

	propSheet.AddPage (&pageOptions);
	propSheet.AddPage (&pageCustomize);
	propSheet.AddPage (&pageRes);

	if (propSheet.DoModal() != IDOK)
	{
		return;
	}

	// Change application theme and tooltips:
	OnAppLook (theApp.m_nAppLook + ID_VIEW_APPLOOK_2007_1);

	m_wndRibbonBar.EnableToolTips (theApp.m_bShowToolTips, theApp.m_bShowToolTipDescr);
	m_wndRibbonBar.EnableKeyTips (theApp.m_bShowKeyTips);
}

void CMainFrame::SetKeys ()
{
	m_MainButton.SetKeys (_T("f"));

	const BCGPKey* arKeys[] = {stdKeys, mainKeys};

	for (int k = 0; k < sizeof (arKeys) / sizeof (BCGPKey*); k++)
	{
		const BCGPKey* keys = arKeys[k];

		for (int i = 0; keys [i].uiCmd != 0; i++)
		{
			CString str = keys [i].lpszKey;

			int nAmpIndex = str.Find (_T('&'));

			if (nAmpIndex >= 0)
			{
				CString str1 = str.Left (nAmpIndex);
				CString str2 = str.Mid (nAmpIndex + 1);

				m_wndRibbonBar.SetElementKeys (keys [i].uiCmd, str1, str2);
			}
			else
			{
				m_wndRibbonBar.SetElementKeys (keys [i].uiCmd, str);
			}
		}
	}
}

void CMainFrame::OnActivateView (UINT nID)
{
	SetActiveView (nID - ID_ACTIVATE_VIEW_0);
}

void CMainFrame::OnUpdateActivateView (CCmdUI* pCmdUI)
{
	CBCGPOrganizerDoc* pDoc = DYNAMIC_DOWNCAST (CBCGPOrganizerDoc, GetActiveDocument ());
	if (pDoc != NULL)
	{
		pCmdUI->Enable ((UINT)pDoc->GetMode () != pCmdUI->m_nID - ID_ACTIVATE_VIEW_0);
	}	
}

COLORREF CMainFrame::GetCalendarBackground () const
{
	COLORREF clr = CLR_DEFAULT;

	if (m_pCalendarColors != NULL)
	{
		clr = m_pCalendarColors->GetColor ();
		if (clr == RGB (255, 255, 255) ||
			clr == (COLORREF)-1)
		{
			clr = CLR_DEFAULT;
		}
	}

	return clr;
}

COLORREF CMainFrame::GetGanttBackground () const
{
	COLORREF clr = CLR_DEFAULT;

	if (m_pGanttColors != NULL)
	{
		clr = m_pGanttColors->GetColor ();
		if (clr == RGB (255, 255, 255) ||
			clr == (COLORREF)-1)
		{
			clr = CLR_DEFAULT;
		}
	}

	return clr;
}

LRESULT CMainFrame::OnHighlightRibbonListItem (WPARAM wp, LPARAM lp)
{
	LRESULT lRes = 0L;

	CBCGPOrganizerDoc* pDoc = DYNAMIC_DOWNCAST (CBCGPOrganizerDoc, GetActiveDocument ());
	if (pDoc != NULL)
	{
		CView* pView = pDoc->GetView (pDoc->GetMode ());
		if (pView != NULL)
		{
			lRes = pView->SendMessage (BCGM_ON_HIGHLIGHT_RIBBON_LIST_ITEM, wp, lp);
		}
	}

	return lRes;
}

void CMainFrame::OnZoom100 ()
{
	CBCGPOrganizerDoc* pDoc = DYNAMIC_DOWNCAST (CBCGPOrganizerDoc, GetActiveDocument ());
	if (pDoc != NULL)
	{
		if (m_pZoomSlider->GetPos () != 8)
		{
			m_pZoomSlider->SetPos (8);
			OnZoom ();
		}	
	}
}

void CMainFrame::OnZoom ()
{
	CBCGPOrganizerDoc* pDoc = DYNAMIC_DOWNCAST (CBCGPOrganizerDoc, GetActiveDocument ());
	if (pDoc != NULL)
	{
		pDoc->UpdateZoom (m_pZoomSlider->GetPos ());
	}
}
