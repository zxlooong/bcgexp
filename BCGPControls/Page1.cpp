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
// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcontrols.h"
#include "Page1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage1 property page

IMPLEMENT_DYNCREATE(CPage1, CBCGPPropertyPage)

CPage1::CPage1() : CBCGPPropertyPage(CPage1::IDD)
{
	//{{AFX_DATA_INIT(CPage1)
	m_bXPButtons = TRUE;
	m_bCheck = TRUE;
	m_strToolTip = _T("ToolTip");
	m_iImage = 2;
	m_iBorderStyle = 0;
	m_iCursor = 0;
	m_bMenuStayPressed = FALSE;
	m_bRightArrow = FALSE;
	m_nImageLocation = 0;
	m_bMenuDefaultClick = FALSE;
	//}}AFX_DATA_INIT
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage1)
	DDX_Control(pDX, IDC_BUTTON_MULTLINE, m_btnMultiLine);
	DDX_Control(pDX, IDC_BORDER, m_wndBorder);
	DDX_Control(pDX, IDC_BORDER_LABEL, m_wndBorderLabel);
	DDX_Control(pDX, IDC_CHECK_BUTTON, m_btnCheck);
	DDX_Control(pDX, IDC_XP_BUTTONS, m_wndXPButtons);
	DDX_Check(pDX, IDC_XP_BUTTONS, m_bXPButtons);
	DDX_Check(pDX, IDC_CHECK_BUTTON, m_bCheck);
	DDX_Control(pDX, IDC_BUTTON, m_Button);
	DDX_Text(pDX, IDC_TOOLTIP, m_strToolTip);
	DDX_CBIndex(pDX, IDC_IMAGE, m_iImage);
	DDX_CBIndex(pDX, IDC_BORDER, m_iBorderStyle);
	DDX_CBIndex(pDX, IDC_CURSOR, m_iCursor);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btnMenu);
	DDX_Check(pDX, IDC_PRESSED_ON_MENU, m_bMenuStayPressed);
	DDX_Check(pDX, IDC_RIGHT_ARROW, m_bRightArrow);
	DDX_CBIndex(pDX, IDC_IMAGE_LOCATION, m_nImageLocation);
	DDX_Check(pDX, IDC_MENU_DEFAULT_CLICK, m_bMenuDefaultClick);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_RADIO1, m_btnRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_btnRadio2);
	DDX_Control(pDX, IDC_RADIO3, m_btnRadio3);
	DDX_Control(pDX, IDC_RADIO4, m_btnRadio4);
}


BEGIN_MESSAGE_MAP(CPage1, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CPage1)
	ON_BN_CLICKED(IDC_XP_BUTTONS, OnXpButtons)
	ON_BN_CLICKED(IDC_SET_TOOLTIP, OnSetTooltip)
	ON_CBN_SELCHANGE(IDC_CURSOR, OnSetCursor)
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
	ON_BN_CLICKED(IDC_RIGHT_ARROW, OnRightArrow)
	ON_BN_CLICKED(IDC_BUTTON_MENU, OnButtonMenu)
	ON_BN_CLICKED(IDC_PRESSED_ON_MENU, OnPressedOnMenu)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ITEM_1, OnItem1)
	ON_COMMAND(ID_ITEM_2, OnItem2)
	ON_COMMAND(ID_DIALOG_ABOUT, OnDialogAbout)
	ON_UPDATE_COMMAND_UI(ID_ITEM_2, OnUpdateItem2)
	ON_CBN_SELCHANGE(IDC_IMAGE, OnResetButton)
	ON_CBN_SELCHANGE(IDC_BORDER, OnResetButton)
	ON_CBN_SELCHANGE(IDC_IMAGE, OnResetButton)
	ON_CBN_SELCHANGE(IDC_BORDER, OnResetButton)
	ON_CBN_SELCHANGE(IDC_IMAGE_LOCATION, OnResetButton)
	ON_BN_CLICKED(IDC_MENU_DEFAULT_CLICK, OnMenuDefaultClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage1 message handlers

void CPage1::OnXpButtons() 
{
	UpdateData ();

	CBCGPButton::EnableWinXPTheme (m_bXPButtons);

	m_wndBorder.EnableWindow (!m_bXPButtons);
	m_wndBorderLabel.EnableWindow (!m_bXPButtons);

	RedrawWindow ();
}

BOOL CPage1::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();
	
	if (!CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
	{
		m_bXPButtons = FALSE;
		m_wndXPButtons.EnableWindow (FALSE);
	}
	else
	{
		m_wndBorder.EnableWindow (FALSE);
		m_wndBorderLabel.EnableWindow (FALSE);
	}

	m_Button.m_bTransparent = TRUE;

	OnResetButton();
	OnSetCursor();
	OnSetTooltip();

	m_menu.LoadMenu (IDR_MENU1);
	m_btnMenu.m_hMenu = m_menu.GetSubMenu (0)->GetSafeHmenu ();
	m_btnMenu.SizeToContent ();
	m_btnMenu.m_bOSMenu = FALSE;

	m_btnCheck.SetImage (globalData.bIsOSAlphaBlendingSupport ? IDB_CHECKNO32 : IDB_CHECKNO);
	m_btnCheck.SetCheckedImage (globalData.bIsOSAlphaBlendingSupport ? IDB_CHECK32 : IDB_CHECK);
	m_btnCheck.SizeToContent ();
	m_btnCheck.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;

	m_btnRadio1.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
	m_btnRadio2.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
	m_btnRadio3.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
	m_btnRadio4.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;

	m_btnRadio1.SetImage (globalData.bIsOSAlphaBlendingSupport ? IDB_RADIO_OFF32 : IDB_RADIO_OFF);
	m_btnRadio2.SetImage (globalData.bIsOSAlphaBlendingSupport ? IDB_RADIO_OFF32 : IDB_RADIO_OFF);
	m_btnRadio3.SetImage (globalData.bIsOSAlphaBlendingSupport ? IDB_RADIO_OFF32 : IDB_RADIO_OFF);
	m_btnRadio4.SetImage (globalData.bIsOSAlphaBlendingSupport ? IDB_RADIO_OFF32 : IDB_RADIO_OFF);

	m_btnRadio1.SetCheckedImage (globalData.bIsOSAlphaBlendingSupport ? IDB_RADIO_ON32 : IDB_RADIO_ON);
	m_btnRadio2.SetCheckedImage (globalData.bIsOSAlphaBlendingSupport ? IDB_RADIO_ON32 : IDB_RADIO_ON);
	m_btnRadio3.SetCheckedImage (globalData.bIsOSAlphaBlendingSupport ? IDB_RADIO_ON32 : IDB_RADIO_ON);
	m_btnRadio4.SetCheckedImage (globalData.bIsOSAlphaBlendingSupport ? IDB_RADIO_ON32 : IDB_RADIO_ON);

	m_btnRadio1.SizeToContent ();
	m_btnRadio2.SizeToContent ();
	m_btnRadio3.SizeToContent ();
	m_btnRadio4.SizeToContent ();

	m_btnRadio1.SetCheck (TRUE);

	m_btnMultiLine.SizeToContent ();

	CBCGPToolBar::AddToolBarForImageCollection (IDR_TOOLBAR_MENU_IMAGES);

	UpdateData (FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPage1::OnResetButton() 
{
	UpdateData ();
	
	switch (m_iBorderStyle)
	{
	case 0:
		m_Button.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		break;

	case 1:
		m_Button.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
		break;

	case 2:
		m_Button.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_3D;
	}

	if (m_iImage == 1)	// Text only
	{
		m_Button.SetImage ((HBITMAP) NULL);
	}
	else
	{
		if (globalData.bIsOSAlphaBlendingSupport)
		{
			m_Button.SetImage (IDB_BTN1_32, IDB_BTN1_HOT_32);
		}
		else
		{
			m_Button.SetImage (IDB_BTN1, IDB_BTN1_HOT);
		}
	}

	if (m_iImage == 0)
	{
		m_Button.SetWindowText (_T(""));
	}
	else
	{
		m_Button.SetWindowText (_T("BCGButton"));
	}

	switch (m_nImageLocation)
	{
	case 0:
		m_Button.m_bRighImage = FALSE;
		m_Button.m_bTopImage = FALSE;
		break;

	case 1:
		m_Button.m_bRighImage = TRUE;
		m_Button.m_bTopImage = FALSE;
		break;

	case 2:
		m_Button.m_bRighImage = FALSE;
		m_Button.m_bTopImage = TRUE;
		break;
	}

	m_Button.SizeToContent ();
	m_Button.Invalidate ();
}

void CPage1::OnSetCursor() 
{
	UpdateData ();

	switch (m_iCursor)
	{
	case 0:
		m_Button.SetMouseCursor (NULL);
		break;

	case 1:
		m_Button.SetMouseCursorHand ();
		break;

	case 2:
		m_Button.SetMouseCursor (AfxGetApp ()->LoadCursor (IDC_CURSOR));
		break;
	}
}

void CPage1::OnButton() 
{
	MessageBox (_T("Button Clicked!"));
}

void CPage1::OnSetTooltip() 
{
	UpdateData ();
	m_Button.SetTooltip (m_strToolTip);
}

void CPage1::OnPressedOnMenu() 
{
	UpdateData ();
	m_btnMenu.m_bStayPressed = m_bMenuStayPressed;
}

void CPage1::OnRightArrow() 
{
	UpdateData ();
	m_btnMenu.m_bRightArrow = m_bRightArrow;
	m_btnMenu.Invalidate ();
}

void CPage1::OnButtonMenu() 
{
	CString strItem;
	
	switch (m_btnMenu.m_nMenuResult)
	{
	case ID_ITEM_1:
		strItem = _T("Item 1");
		break;

	case ID_ITEM_2:
		strItem = _T("Item 2");
		break;

	case ID_ITEM_3:
		strItem = _T("Item 3");
		break;

	case ID_ITEM_4:
		strItem = _T("Item 4");
		break;

	default:
		if (!m_bMenuDefaultClick)
		{
			return;
		}

		strItem = _T("Default Menu Button Action");
		break;
	}

	MessageBox (strItem);
}

void CPage1::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu (IDR_DIALOG_MENU);

	theApp.GetContextMenuManager ()->ShowPopupMenu (
		menu.GetSubMenu (0)->GetSafeHmenu (), point.x, point.y, this,
		TRUE);
}

void CPage1::OnItem1() 
{
	MessageBox (_T("Command 1...."));
}

void CPage1::OnItem2() 
{
	MessageBox (_T("Command 2...."));
}

void CPage1::OnDialogAbout() 
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}

void CPage1::OnUpdateItem2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck ();
}

void CPage1::OnMenuDefaultClick() 
{
	UpdateData ();

	m_btnMenu.m_bDefaultClick = m_bMenuDefaultClick;
	m_btnMenu.RedrawWindow ();
}
