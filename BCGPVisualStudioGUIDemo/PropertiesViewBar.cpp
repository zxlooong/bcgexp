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
// PropertiesViewBar.cpp: implementation of the CPropertiesViewBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "MainFrm.h"
#include "PropertiesViewBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesViewBar::CPropertiesViewBar()
{
}

CPropertiesViewBar::~CPropertiesViewBar()
{
}


BEGIN_MESSAGE_MAP(CPropertiesViewBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CPropertiesViewBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_SORTINGPROP, OnSortingprop)
	ON_UPDATE_COMMAND_UI(ID_SORTINGPROP, OnUpdateSortingprop)
	ON_COMMAND(ID_PROPERIES1, OnProperies1)
	ON_UPDATE_COMMAND_UI(ID_PROPERIES1, OnUpdateProperies1)
	ON_COMMAND(ID_PROPERIES2, OnProperies2)
	ON_UPDATE_COMMAND_UI(ID_PROPERIES2, OnUpdateProperies2)
	ON_COMMAND(ID_EXPAND, OnExpand)
	ON_UPDATE_COMMAND_UI(ID_EXPAND, OnUpdateExpand)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CPropertiesViewBar::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect (rectClient);

	m_wndObjectCombo.GetWindowRect (&rectCombo);

	int cyCmb = rectCombo.Size ().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout (FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos (NULL,
								   rectClient.left, 
								   rectClient.top,
								   rectClient.Width (),
								   200,
								   SWP_NOACTIVATE | SWP_NOZORDER);

	m_wndToolBar.SetWindowPos (NULL,
							   rectClient.left, 
							   rectClient.top + cyCmb, 
							   rectClient.Width (),
							   cyTlb,
							   SWP_NOACTIVATE | SWP_NOZORDER);


	m_wndPropList.SetWindowPos (NULL,
									  rectClient.left, 
									  rectClient.top + cyCmb + cyTlb, 
									  rectClient.Width (),
									  rectClient.Height () - (cyCmb+cyTlb),
									  SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create combo:
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST
		| WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	
	if (!m_wndObjectCombo.Create (dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Properies Combo \n");
		return -1;      // fail to create
	}

	m_wndObjectCombo.AddString (_T("IDD_ABOUTBOX (Dialog)"));
	m_wndObjectCombo.SetFont (CFont::FromHandle ((HFONT) GetStockObject (DEFAULT_GUI_FONT)));
	m_wndObjectCombo.SetCurSel (0);

	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properies Grid \n");
		return -1;      // fail to create
	}

	InitPropList ();

	m_wndToolBar.Create (this, dwDefaultToolbarStyle, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar (IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle ();

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
		
	m_wndToolBar.SetBarStyle (
		m_wndToolBar.GetBarStyle () & 
			~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner (this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame (FALSE);

	AdjustLayout ();
	return 0;
}

void CPropertiesViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout ();
}

void CPropertiesViewBar::OnSortingprop() 
{
	m_wndPropList.SetAlphabeticMode ();
}

void CPropertiesViewBar::OnUpdateSortingprop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndPropList.IsAlphabeticMode ());
}

void CPropertiesViewBar::OnExpand() 
{
	m_wndPropList.SetAlphabeticMode (FALSE);
}

void CPropertiesViewBar::OnUpdateExpand(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (!m_wndPropList.IsAlphabeticMode ());
}

void CPropertiesViewBar::OnProperies1() 
{
	// TODO: Add your command handler code here
	
}

void CPropertiesViewBar::OnUpdateProperies1(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command update UI handler code here
	
}

void CPropertiesViewBar::OnProperies2() 
{
	// TODO: Add your command handler code here
	
}

void CPropertiesViewBar::OnUpdateProperies2(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command update UI handler code here
	
}

void CPropertiesViewBar::InitPropList ()
{
	SetPropListFont ();

	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();

	CBCGPProp* pGroup1 = new CBCGPProp (_T("Appearance"));

	pGroup1->AddSubItem (new CBCGPProp (_T("3D Look"), (_variant_t) false,
		_T("Specifies the dialog's font will be nonbold and controls will have a 3D border")));

	CBCGPProp* pProp = new CBCGPProp (_T("Border"), _T("Dialog Frame"),
		_T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption (_T("None"));
	pProp->AddOption (_T("Thin"));
	pProp->AddOption (_T("Resizable"));
	pProp->AddOption (_T("Dialog Frame"));
	pProp->AllowEdit (FALSE);

	pGroup1->AddSubItem (pProp);
	pGroup1->AddSubItem (new CBCGPProp (_T("Caption"), (_variant_t) _T("About BCGProTest"),
		_T("Specifies the text that will be displayed in the dialog's title bar")));

	m_wndPropList.AddProperty (pGroup1);

	CBCGPProp* pSize = new CBCGPProp (_T("Window Size"), 0, TRUE);

	pProp = new CBCGPProp (_T("Height"), (_variant_t) 250l,
							_T("Specifies the dialog's height"));
	pProp->EnableSpinControl (TRUE, 0, 1000);
	pSize->AddSubItem (pProp);

	pProp = new CBCGPProp (	_T("Width"), (_variant_t) 150l,
							_T("Specifies the dialog's width"));
	pProp->EnableSpinControl ();
	pSize->AddSubItem (pProp);

	m_wndPropList.AddProperty (pSize);

	CBCGPProp* pGroup2 = new CBCGPProp (_T("Font"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle ((HFONT) GetStockObject (DEFAULT_GUI_FONT));
	font->GetLogFont (&lf);

	lstrcpy (lf.lfFaceName, _T("Arial"));

	pGroup2->AddSubItem (new CBCGPFontProp (_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the dialog")));
	pGroup2->AddSubItem (new CBCGPProp (_T("Use System Font"), (_variant_t) true, _T("Specifies that the dialog uses MS Shell Dlg font")));

	m_wndPropList.AddProperty (pGroup2);

	CBCGPProp* pGroup3 = new CBCGPProp (_T("Misc"));
	pProp = new CBCGPProp (_T("(Name)"), _T("IDD_ABOUT_BOX (dialog)"));
	pProp->Enable (FALSE);
	pGroup3->AddSubItem (pProp);

	CBCGPColorProp* pColorProp = new CBCGPColorProp (_T("Window Color"), RGB (210, 192, 254), NULL, _T("Specifies the default dialog color"));
	pColorProp->EnableOtherButton (_T("Other..."));
	pColorProp->EnableAutomaticButton (_T("Default"), ::GetSysColor (COLOR_3DFACE));
	pGroup3->AddSubItem (pColorProp);

	static TCHAR BASED_CODE szFilter[] = _T("Icon Files (*.ico)|*.ico|All Files (*.*)|*.*||");
	pGroup3->AddSubItem (new CBCGPFileProp (_T("Icon"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the dialog icon")));

	pGroup3->AddSubItem (new CBCGPFileProp (_T("Folder"), _T("c:\\")));

	COleDateTime date = COleDateTime::GetCurrentTime ();
	pGroup3->AddSubItem (new CBCGPDateTimeProp (_T("Date"), date,
		_T("Set a date"), 0, CBCGPDateTimeCtrl::DTM_DATE));

	pGroup3->AddSubItem (new CBCGPDateTimeProp (_T("Time"), date,
		_T("Set a time"), 0, CBCGPDateTimeCtrl::DTM_TIME));

	m_wndPropList.AddProperty (pGroup3);

	CBCGPProp* pGroup4 = new CBCGPProp (_T("Hierarchy"));

	CBCGPProp* pGroup41 = new CBCGPProp (_T("First sub-level"));
	pGroup4->AddSubItem (pGroup41);

	CBCGPProp* pGroup411 = new CBCGPProp (_T("Second sub-level"));
	pGroup41->AddSubItem (pGroup411);

	pGroup411->AddSubItem (new CBCGPProp (_T("Item 1"), (_variant_t) _T("Value 1"),
		_T("This is a description")));
	pGroup411->AddSubItem (new CBCGPProp (_T("Item 2"), (_variant_t) _T("Value 2"),
		_T("This is a description")));
	pGroup411->AddSubItem (new CBCGPProp (_T("Item 3"), (_variant_t) _T("Value 3"),
		_T("This is a description")));

	pGroup4->Expand (FALSE);
	m_wndPropList.AddProperty (pGroup4);
}

void CPropertiesViewBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	
	m_wndPropList.SetFocus ();
	
}

void CPropertiesViewBar::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CBCGPDockingControlBar::OnSettingChange(uFlags, lpszSection);
	SetPropListFont ();
}

void CPropertiesViewBar::SetPropListFont ()
{
	::DeleteObject (m_fntPropList.Detach ());

	LOGFONT lf;
	globalData.fontRegular.GetLogFont (&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	globalData.GetNonClientMetrics (info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect (&lf);

	m_wndPropList.SetFont (&m_fntPropList);
}

void CPropertiesViewBar::OnChangeVisualStyle ()
{
	m_wndToolBar.CleanUpLockedImages ();
	m_wndToolBar.LoadBitmap (theApp.m_bHiColorIcons ? 
		IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);
}
