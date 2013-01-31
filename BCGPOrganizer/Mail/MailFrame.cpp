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
// MailFrame.cpp : implementation file
//

#include "stdafx.h"
#include "../bcgporganizer.h"
#include "MailFrame.h"

#include "../MainButtonsGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CMailDialogBar1, CEditDialogBar, VERSIONABLE_SCHEMA | 1)

CMailDialogBar1::CMailDialogBar1 ()
{
}

CMailDialogBar1::~CMailDialogBar1 ()
{
}

BEGIN_MESSAGE_MAP(CMailDialogBar1, CEditDialogBar)
END_MESSAGE_MAP()

void CMailDialogBar1::DoDataExchange(CDataExchange* pDX)
{
	CEditDialogBar::DoDataExchange (pDX);

	DDX_Text(pDX, IDC_MAIL_EDIT_FROM, m_strFrom);
	DDX_Text(pDX, IDC_MAIL_EDIT_TO, m_strTo);
	DDX_Text(pDX, IDC_MAIL_EDIT_CC, m_strCc);
	DDX_Text(pDX, IDC_MAIL_EDIT_SUBJECT, m_strSubject);
}

BOOL CMailDialogBar1::OnInitDialogBar()
{
	AddResize (IDC_MAIL_EDIT_FROM, CEditDialogBar::e_ResizeSizeH);
	AddResize (IDC_MAIL_EDIT_TO, CEditDialogBar::e_ResizeSizeH);
	AddResize (IDC_MAIL_EDIT_CC, CEditDialogBar::e_ResizeSizeH);
	AddResize (IDC_MAIL_EDIT_SUBJECT, CEditDialogBar::e_ResizeSizeH);

	return CEditDialogBar::OnInitDialogBar();
}


IMPLEMENT_SERIAL(CMailDialogBar2, CEditDialogBar, VERSIONABLE_SCHEMA | 1)

CMailDialogBar2::CMailDialogBar2 ()
{
}

CMailDialogBar2::~CMailDialogBar2 ()
{
}

BEGIN_MESSAGE_MAP(CMailDialogBar2, CEditDialogBar)
END_MESSAGE_MAP()

void CMailDialogBar2::DoDataExchange(CDataExchange* pDX)
{
	CEditDialogBar::DoDataExchange (pDX);

	DDX_Text(pDX, IDC_MAIL_EDIT_TO, m_strTo);
	DDX_Text(pDX, IDC_MAIL_EDIT_CC, m_strCc);
	DDX_Text(pDX, IDC_MAIL_EDIT_SUBJECT, m_strSubject);

	DDX_Control (pDX, ID_MAIL_EDIT_SEND, m_Send);
}

BOOL CMailDialogBar2::OnInitDialogBar()
{
	AddResize (IDC_MAIL_EDIT_TO, CEditDialogBar::e_ResizeSizeH);
	AddResize (IDC_MAIL_EDIT_CC, CEditDialogBar::e_ResizeSizeH);
	AddResize (IDC_MAIL_EDIT_SUBJECT, CEditDialogBar::e_ResizeSizeH);

	if (CEditDialogBar::OnInitDialogBar())
	{
		m_Send.m_bTopImage = TRUE;
		m_Send.SetImage (IDB_MAIL_SEND, 0, 0);

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMailFrame

IMPLEMENT_DYNAMIC(CMailFrame, CEditFrameDialog)

CMailFrame::CMailFrame(CBCGPGridRow& mail, 
					   BOOL bReadOnly /*= FALSE*/,
					   CWnd* pParent /*=NULL*/)
	: CEditFrameDialog(IDR_MAILFRAME, pParent)
	, m_Mail            (mail)
	, m_bReadOnly       (bReadOnly)
	, m_bDeleted        (FALSE)
	, m_bAttachment     (FALSE)
	, m_bPrivate        (FALSE)
	, m_Importance      (e_ImportanceNormal)
	, m_Format          (e_FormatHTML)
{
	if (m_bReadOnly)
	{
		m_wndDialogBar1.m_strFrom    = m_Mail.GetItem (3)->FormatItem ();
		m_wndDialogBar1.m_strTo      = m_Mail.GetItem (5)->FormatItem ();
		m_wndDialogBar1.m_strCc      = _T("");
		m_wndDialogBar1.m_strSubject = m_Mail.GetItem (4)->FormatItem ();
	}
	else
	{
		m_wndDialogBar2.m_strTo      = m_Mail.GetItem (5)->FormatItem ();
		m_wndDialogBar2.m_strCc      = _T("");
		m_wndDialogBar2.m_strSubject = m_Mail.GetItem (4)->FormatItem ();
	}

	long nImage = (long)m_Mail.GetItem (0)->GetValue ();
	if (nImage == 2)
	{
		m_Importance = e_ImportanceHigh;
	}
	else if (nImage == 3)
	{
		m_Importance = e_ImportanceLow;
	}
}

CMailFrame::~CMailFrame()
{
}

void CMailFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if ((GetStyle() & FWS_ADDTOTITLE) == 0)
		return;     // leave it alone!

	CString strTitle (_T("Message"));
	if (m_Format == e_FormatPlain)
	{
		strTitle += _T(" (Plain Text)");
	}
	else if (m_Format == e_FormatHTML)
	{
		strTitle += _T(" (HTML)");
	}
	else
	{
		strTitle += _T(" (Rich Text)");
	}

	SetTitle (strTitle);

	if (bAddToTitle)
	{
		CString strSubject (m_Mail.GetItem (4)->FormatItem ());
		UpdateFrameTitleForDocument (strSubject.IsEmpty () ?
			_T("Untitled") : strSubject);
	}
	else
	{
		UpdateFrameTitleForDocument(NULL);
	}
}

BEGIN_MESSAGE_MAP(CMailFrame, CEditFrameDialog)
	//{{AFX_MSG_MAP(CMailFrame)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_MAIL_EDIT_SEND, OnSaveClose)
	ON_COMMAND(ID_MAIL_EDIT_SAVE_CLOSE, OnSaveClose)
	ON_COMMAND(ID_MAIL_EDIT_DELETE, OnDelete)
	ON_COMMAND(ID_MAIL_EDIT_PRIVATE, OnPrivate)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_PRIVATE, OnUpdatePrivate)
	ON_COMMAND(ID_MAIL_EDIT_IMPORTANCE_LOW, OnImportanceLow)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_IMPORTANCE_LOW, OnUpdateImportanceLow)
	ON_COMMAND(ID_MAIL_EDIT_IMPORTANCE_HIGH, OnImportanceHigh)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_IMPORTANCE_HIGH, OnUpdateImportanceHigh)
	ON_COMMAND(ID_MAIL_EDIT_FORMAT_PLAIN, OnFormatPlain)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_FORMAT_PLAIN, OnUpdateFormatPlain)
	ON_COMMAND(ID_MAIL_EDIT_FORMAT_HTML, OnFormatHTML)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_FORMAT_HTML, OnUpdateFormatHTML)
	ON_COMMAND(ID_MAIL_EDIT_FORMAT_RTF, OnFormatRTF)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_FORMAT_RTF, OnUpdateFormatRTF)

	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_REPLY, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_REPLY_ALL, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_FORWARD, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_MOVE, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_ACTIONS, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_MARK_AS_UNREAD, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_LABEL, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_FOLLOW, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_NAMES_AB, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_NAMES_CHECK, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_ATTACH_FILE, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_ATTACH_ITEM, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_BUSINESS_CARD, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_CALENDAR, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_SIGNATURE, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_PAGELAYOUT_THEMES, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_PAGELAYOUT_COLORS, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_PAGELAYOUT_EFFECTS, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_PAGELAYOUT_FONTS, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_PAGELAYOUT_PAGEBACKGROUND_PAGECOLOR, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_SHOW_BCC, OnUpdateDummy)
	ON_UPDATE_COMMAND_UI(ID_MAIL_EDIT_SHOW_FROM, OnUpdateDummy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailFrame message handlers

BOOL CMailFrame::LoadPanelImages ()
{
	m_PanelImages.SetImageSize (CSize (16, 16));
	return m_PanelImages.Load (IDB_MAIL_BUTTONS);
}

BOOL CMailFrame::CreateStatusBar ()
{
	return TRUE;
}

BOOL CMailFrame::CreateOtherBars ()
{
	CBCGPDialogBar* pBar = NULL;

	if (m_bReadOnly)
	{
		if (!m_wndDialogBar1.Create (_T(""), this, FALSE, MAKEINTRESOURCE(IDD_MAIL_DIALOGBAR1), 
				WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR, 0, 0))
		{
			return FALSE;
		}

		pBar = &m_wndDialogBar1;
	}
	else
	{
		if (!m_wndDialogBar2.Create (_T(""), this, FALSE, MAKEINTRESOURCE(IDD_MAIL_DIALOGBAR2), 
				WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR, 0, 0))
		{
			return FALSE;
		}

		pBar = &m_wndDialogBar2;
	}

	EnableDocking (CBRS_ALIGN_ANY);
	DockControlBar (pBar);

	CRect rectBar;
	pBar->GetClientRect (rectBar);
	pBar->SetMinSize (rectBar.Size ());

	ShowControlBar (pBar, TRUE, FALSE, TRUE);

	return TRUE;
}

void CMailFrame::CreateThemeList ()
{
	m_arThemes.RemoveAll ();
	m_arColorThemes.RemoveAll ();

	m_arThemes.Add (_T("Office"));
	m_arThemes.Add (_T("Apex"));
	m_arThemes.Add (_T("Aspect"));
	m_arThemes.Add (_T("Civic"));
	m_arThemes.Add (_T("Concource"));
	m_arThemes.Add (_T("Equite"));
	m_arThemes.Add (_T("Flow"));
	m_arThemes.Add (_T("Foundry"));
	m_arThemes.Add (_T("Median"));
	m_arThemes.Add (_T("Metro"));
	m_arThemes.Add (_T("Module"));
	m_arThemes.Add (_T("Opulent"));
	m_arThemes.Add (_T("Oriel"));
	m_arThemes.Add (_T("Origin"));
	m_arThemes.Add (_T("Paper"));
	m_arThemes.Add (_T("Solstice"));
	m_arThemes.Add (_T("Technic"));
	m_arThemes.Add (_T("Trek"));
	m_arThemes.Add (_T("Urban"));
	m_arThemes.Add (_T("Verve"));

	m_arColorThemes.Copy (m_arThemes);
	m_arColorThemes.InsertAt (1, _T("Grayscale"));
}

void CMailFrame::CreateFontsList ()
{
	m_arFonts.RemoveAll ();

	{
		CRibbonListFontButton::XItem item;

		item.m_Caption = _T("Office Classic");
		lstrcpy (item.m_Font[0].lfFaceName, _T("Arial"));
		lstrcpy (item.m_Font[1].lfFaceName, _T("Times New Roman"));

		m_arFonts.Add (item);
	}

	{
		CRibbonListFontButton::XItem item;

		item.m_Caption = _T("Office Classic 2");
		lstrcpy (item.m_Font[0].lfFaceName, _T("Arial"));
		lstrcpy (item.m_Font[1].lfFaceName, _T("Arial"));

		m_arFonts.Add (item);
	}

	{
		CRibbonListFontButton::XItem item;

		item.m_Caption = _T("Aspect");
		lstrcpy (item.m_Font[0].lfFaceName, _T("Verdana"));
		lstrcpy (item.m_Font[1].lfFaceName, _T("Verdana"));

		m_arFonts.Add (item);
	}
}

void CMailFrame::AddMainCategory ()
{
	CEditFrameDialog::AddMainCategory ();

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("Main Menu"), IDB_MAIL_FILE_SMALL, IDB_MAIL_FILE_LARGE);

	if (!m_bReadOnly)
	{
		pMainPanel->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_SEND, _T("S&end..."), 8, 7, TRUE));
		pMainPanel->Add (new CBCGPRibbonSeparator (TRUE));
	}	

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE, _T("&Save"), 0, 0, TRUE));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("Save &As..."), 1, 1, TRUE));
	pMainPanel->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_DELETE, _T("&Delete"), 2, 2, TRUE));

	pMainPanel->Add (new CBCGPRibbonSeparator (TRUE));

	CBCGPRibbonButton* pBtnPrint = new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 3, 3);
	pBtnPrint->AddSubItem (new CBCGPRibbonLabel (_T("Preview and print the document")));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 3, 3, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_DIRECT, _T("&Quick Print"), 5, 5, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_PREVIEW, _T("Print Pre&view"), 6, 6, TRUE));
	pMainPanel->Add (pBtnPrint);

	pMainPanel->Add (new CBCGPRibbonSeparator (TRUE));

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_CLOSE, _T("&Close"), 4, 4));

	pMainPanel->AddToRight (new CMainButtonsGroup (_T("Actions")));

	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_TOOLS_OPTIONS, _T("Opt&ions"), 7));
}

void CMailFrame::AddTabs ()
{
	AddTab_Home ();

	if (!m_bReadOnly)
	{
		AddTab_Options ();

		CEditFrameDialog::AddTabs ();
	}	
}

void CMailFrame::AddTab_Home ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("Message\nh"), IDB_MAIL_HOME_SMALL, IDB_MAIL_HOME_LARGE);

	if (m_bReadOnly)
	{
		CBCGPRibbonPanel* pPanelRespond = pCategory->AddPanel (_T("Respond"), m_PanelImages.ExtractIcon (3));
		pPanelRespond->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_REPLY, _T("Reply\nrp"), 0, 0));
		pPanelRespond->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_REPLY_ALL, _T("Reply to All\nra"), 1, 1));
		pPanelRespond->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_FORWARD, _T("Forward\nfw"), 2, 2));

		CBCGPRibbonPanel* pPanelActions = pCategory->AddPanel (_T("Actions"), m_PanelImages.ExtractIcon (4));
		pPanelActions->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_DELETE, _T("Delete\nd"), 3, 3));
		pPanelActions->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_MOVE, _T("Move to Folder\nm"), 4, 4));
		pPanelActions->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_ACTIONS, _T("Other Actions\nx"), 5, 5));

		CBCGPRibbonPanel* pPanelOptions = pCategory->AddPanel (_T("Options"), m_PanelImages.ExtractIcon (5));
		CBCGPRibbonButton* pLabel = new CBCGPRibbonButton (ID_MAIL_EDIT_LABEL, _T("Categorize\ng"), 6, 6);
		pPanelOptions->Add (pLabel);
		CompleteCategories (*pLabel);

		CBCGPRibbonButton* pFollow = new CBCGPRibbonButton (ID_MAIL_EDIT_FOLLOW, _T("Follow Up\nw"), 7, 7);
		pFollow->SetMenu (IDR_FOLLOW_MENU);
		pPanelOptions->Add (pFollow);

		pPanelOptions->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_MARK_AS_UNREAD, _T("Mark As Unread\nu"), 8, 8));
	}
	else
	{
		CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel (_T("Clipboard"), m_PanelImages.ExtractIcon (0));
		pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_PASTE, _T("Paste"), 9, 9));
		pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CUT, _T("Cut"), 10, -1));
		pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_COPY, _T("Copy"), 11, -1));

		CBCGPRibbonFontComboBox::m_bDrawUsingFont = TRUE;
		CBCGPRibbonPanel* pPanelFont = pCategory->AddPanel (_T("Basic Text"), m_PanelImages.ExtractIcon (1));
		CBCGPRibbonButtonsGroup* pFontGroup = new CBCGPRibbonButtonsGroup;

		CBCGPRibbonFontComboBox* pFontCombo = new CBCGPRibbonFontComboBox (ID_FONT_FONT);
		pFontCombo->SelectItem (_T("Arial"));
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
		pFontSizeCombo->SelectItem (4);
		pFontGroup->AddButton (pFontSizeCombo);

		pPanelFont->Add (pFontGroup);

		pPanelFont->AddToolBar (IDR_EDITCTRL_FONT);

		CBCGPRibbonColorButton* pFontColorHighlightBtn = new CBCGPRibbonColorButton ();
		pFontColorHighlightBtn->EnableOtherButton (_T("Other..."));
		pFontColorHighlightBtn->SetColor (RGB (255, 255, 255));

		pPanelFont->ReplaceByID (ID_FONT_TEXTHIGHLIGHT, pFontColorHighlightBtn);

		CBCGPRibbonColorButton* pFontColorBtn = new CBCGPRibbonColorButton ();
		pFontColorBtn->SetDefaultCommand (FALSE);
		pFontColorBtn->EnableAutomaticButton (_T("&Automatic"), RGB (0, 0, 0));
		pFontColorBtn->EnableOtherButton (_T("&More Colors..."), _T("More Colors"));
		pFontColorBtn->SetColumns (10);
		pFontColorBtn->SetColorBoxSize (CSize (17, 17));
		pFontColorBtn->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
		pFontColorBtn->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE);
		pFontColorBtn->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);

		pPanelFont->ReplaceByID (ID_FONT_COLOR, pFontColorBtn);

		CBCGPRibbonPanel* pPanelNames = pCategory->AddPanel (_T("Names"), m_PanelImages.ExtractIcon (6));
		pPanelNames->Add (new CBCGPRibbonButton (ID_MAIL_NAMES_AB, _T("Address Book\nab"), 12, 10));
		pPanelNames->Add (new CBCGPRibbonButton (ID_MAIL_NAMES_CHECK, _T("Check Names\nm"), 13, 11));

		CBCGPRibbonPanel* pPanelInclude = pCategory->AddPanel (_T("Include"), m_PanelImages.ExtractIcon (7));
		pPanelInclude->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_ATTACH_FILE, _T("Attach File\naf"), 14, 12));
		pPanelInclude->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_ATTACH_ITEM, _T("Attach Item\nam"), 15, 13));
		pPanelInclude->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_BUSINESS_CARD, _T("Business Card\naa"), 16, 14));
		pPanelInclude->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_CALENDAR, _T("Calendar\noc"), 17, 15));
		pPanelInclude->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_SIGNATURE, _T("Signature\ng"), 18, 16));

		CBCGPRibbonPanel* pPanelOptions = pCategory->AddPanel (_T("Options"), m_PanelImages.ExtractIcon (5));
		CBCGPRibbonButton* pLabel = new CBCGPRibbonButton (ID_MAIL_EDIT_LABEL, _T("Categorize\ng"), 6, 6);
		pPanelOptions->Add (pLabel);
		CompleteCategories (*pLabel);

		CBCGPRibbonButton* pFollow = new CBCGPRibbonButton (ID_MAIL_EDIT_FOLLOW, _T("Follow Up\nw"), 7, 7);
		pFollow->SetMenu (IDR_FOLLOW_MENU);
		pPanelOptions->Add (pFollow);

		pPanelOptions->Add (new CBCGPRibbonSeparator);
		pPanelOptions->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_IMPORTANCE_HIGH, _T("High Importance\nh"), 19, -1));
		pPanelOptions->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_IMPORTANCE_LOW, _T("Low Importance\nl"), 20, -1));
	}
}

void CMailFrame::AddTab_Options ()
{
	CreateThemeList ();
	CreateFontsList ();

	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("Options\np"), IDB_MAIL_OPTIONS_SMALL, IDB_MAIL_OPTIONS_LARGE);

	CBCGPRibbonPanel* pPanelThemes = pCategory->AddPanel (_T("Themes\nzt"), m_PanelImages.ExtractIcon (8));

	CRibbonListButton* pListBtn = new CRibbonListButton (ID_PAGELAYOUT_THEMES, _T("Themes\nth"), 0, 0, FALSE);
	pListBtn->AddGroup (_T("Built-In"), IDB_THEME_THEMES, 64, m_arThemes);
	pListBtn->AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_THEMES_RESETFROMTEMPLATE, _T("&Reset to Theme from Template")));
	pListBtn->AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_THEMES_MORETHEMES, _T("More Themes on Microsoft &Office Online...")));
	pListBtn->AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_THEMES_BROWSEFORTHEMES, _T("&Browse for Themes..."), 24));
	pListBtn->AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_THEMES_SAVECURRENTTHEME, _T("&Save Current Theme..."), 25));
	pListBtn->SetIconsInRow (4);
	pListBtn->EnableMenuResize ();
	pPanelThemes->Add (pListBtn);

	pListBtn = new CRibbonListButton (ID_PAGELAYOUT_COLORS, _T("Colors\ntc"), 1, -1);
	pListBtn->AddGroup (_T("Built-In"), IDB_THEME_COLORS, 103, m_arColorThemes);
	pListBtn->AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_COLORS_CREATENEWTHEMECOLORS, _T("&Create New Theme Colors...")));
	pListBtn->EnableMenuResize (TRUE, TRUE);	// Vertical only
	pPanelThemes->Add (pListBtn);

	CRibbonListFontButton* pFontsBtn = new CRibbonListFontButton (ID_PAGELAYOUT_FONTS, _T("Fonts\ntf"), 2, -1);
	pFontsBtn->AddGroup (_T("Built-In"), IDB_THEME_FONTS, 43, m_arFonts);
	pFontsBtn->AddSubItem (new CBCGPRibbonButton (ID_PAGELAYOUT_FONTS_CREATENEWTHEMEFONTS, _T("&Create New Theme Fonts...")));
	pFontsBtn->EnableMenuResize (TRUE, TRUE);	// Vertical only
	pPanelThemes->Add (pFontsBtn);

	pListBtn = new CRibbonListButton (ID_PAGELAYOUT_EFFECTS, _T("Effects\nte"), 3, -1, FALSE);
	pListBtn->AddGroup (_T("Built-In"), IDB_THEME_EFFECTS, 64, m_arThemes);
	pListBtn->SetIconsInRow (4);
	pListBtn->EnableMenuResize ();
	pPanelThemes->Add (pListBtn);

	pPanelThemes->Add (new CBCGPRibbonSeparator);

	CBCGPRibbonColorButton* pPageBackBtn = new CBCGPRibbonColorButton (
		ID_PAGELAYOUT_PAGEBACKGROUND_PAGECOLOR, _T("Page Color\npc"), TRUE, 4, 1);
	pPageBackBtn->EnableOtherButton (_T("&More Colors..."), _T("More Colors"));
	pPageBackBtn->SetColor ((COLORREF)-1);
	pPageBackBtn->SetDefaultCommand (FALSE);
	pPageBackBtn->SetColumns (10);
	pPageBackBtn->AddColorsGroup (_T("Theme Colors"), m_lstMainColors);
	pPageBackBtn->AddColorsGroup (_T(""), m_lstAdditionalColors, TRUE /* Contiguous Columns*/);
	pPageBackBtn->AddColorsGroup (_T("Standard Colors"), m_lstStandardColors);
	pPageBackBtn->SetColorBoxSize (CSize (17, 17));
	pPageBackBtn->EnableAutomaticButton (_T("&No Color"), (COLORREF)-1, TRUE, NULL, FALSE /* Bottom */);
	pPanelThemes->Add (pPageBackBtn);

	CBCGPRibbonPanel* pPanelFields = pCategory->AddPanel (_T("Fields"), m_PanelImages.ExtractIcon (9));
	pPanelFields->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_SHOW_BCC, _T("Show Bcc\nb"), 5, 2));
	pPanelFields->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_SHOW_FROM, _T("Show From\nf"), 6, 3));

	CBCGPRibbonPanel* pPanelFormat = pCategory->AddPanel (_T("Format"), m_PanelImages.ExtractIcon (10));
	pPanelFormat->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_FORMAT_PLAIN, _T("Plain Text\nl"), 7, -1));
	pPanelFormat->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_FORMAT_HTML, _T("HTML\nh"), 8, -1));
	pPanelFormat->Add (new CBCGPRibbonButton (ID_MAIL_EDIT_FORMAT_RTF, _T("Rich Text\nr"), 9, -1));
}


void CMailFrame::OnPrivate ()
{
	m_bPrivate = !m_bPrivate;
}

void CMailFrame::OnUpdatePrivate (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_bPrivate);
}

void CMailFrame::OnImportanceLow ()
{
	m_Importance = m_Importance == e_ImportanceLow ? e_ImportanceNormal : e_ImportanceLow;
}

void CMailFrame::OnUpdateImportanceLow (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_Importance == e_ImportanceLow);
}

void CMailFrame::OnImportanceHigh ()
{
	m_Importance = m_Importance == e_ImportanceHigh ? e_ImportanceNormal : e_ImportanceHigh;
}

void CMailFrame::OnUpdateImportanceHigh (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_Importance == e_ImportanceHigh);
}

void CMailFrame::OnFileClose ()
{
	OnCancel ();
}

void CMailFrame::OnSaveClose ()
{
	OnOK ();
}

void CMailFrame::OnDelete ()
{
	m_bDeleted = TRUE;

	OnCancel ();
}

void CMailFrame::OnUpdateDummy (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CMailFrame::OnOK() 
{
/*
	m_wndDialogBar1.UpdateData ();

	m_Appointment.SetAllDay (m_wndDialogBar2.m_bAllDay);

	if (!m_Appointment.IsRecurrence () || m_Appointment.IsRecurrenceClone ())
	{
		COleDateTime dtS = m_wndDialogBar2.m_DateStart.GetDate ();
		COleDateTime dtF = m_wndDialogBar2.m_DateEnd.GetDate ();

		COleDateTime tmS = m_wndDialogBar2.m_TimeStart.GetDate ();
		COleDateTime tmF = m_wndDialogBar2.m_TimeEnd.GetDate ();

		dtS = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
			tmS.GetHour (), tmS.GetMinute (), 0);

		dtF = COleDateTime (dtF.GetYear (), dtF.GetMonth (), dtF.GetDay (),
			tmF.GetHour (), tmF.GetMinute (), 0);

		if (dtS > dtF)
		{
			AfxMessageBox (IDS_APPOINTMENT_1);
			return;
		}

		m_Appointment.SetInterval (dtS, dtF);
	}
	
	m_Appointment.SetDescription (m_wndDialogBar1.m_strSubject);
//	m_Appointment.SetBackgroundColor (m_nLabel == 0 ? CLR_DEFAULT : m_wndLabel.GetColor (m_nLabel));
//	m_Appointment.SetDurationColor (m_nShowTime == 0 ? CLR_DEFAULT : m_wndShowTime.GetColor (m_nShowTime));

	m_Appointment.RemoveAllImages ();

	if (m_wndDialogBar1.m_bMeeting)
	{
		m_Appointment.AddImage (3);
	}

	if (m_wndDialogBar1.m_bPhoneCall)
	{
		m_Appointment.AddImage (5);
	}

	CAppointment* pAppDemo = DYNAMIC_DOWNCAST (CAppointment, &m_Appointment);
	if (pAppDemo != NULL)
	{
		pAppDemo->SetImportance (m_bImportanceLow
			? CAppointment::e_ImportanceLow
			: m_bImportanceHigh
				? CAppointment::e_ImportanceHigh
				: CAppointment::e_ImportanceNormal);
		pAppDemo->SetPrivate (m_bPrivate);

		pAppDemo->SetLocation (m_wndDialogBar1.m_strLocation);

		CString strMemo;
		GetText (strMemo);
		pAppDemo->SetMemo (strMemo);
	}
*/
	CEditFrameDialog::OnOK();
}

void CMailFrame::OnFormatPlain ()
{
	m_Format = e_FormatPlain;
	OnUpdateFrameTitle (TRUE);
}

void CMailFrame::OnUpdateFormatPlain (CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_Format == e_FormatPlain);
}

void CMailFrame::OnFormatHTML ()
{
	m_Format = e_FormatHTML;
	OnUpdateFrameTitle (TRUE);
}

void CMailFrame::OnUpdateFormatHTML (CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_Format == e_FormatHTML);
}

void CMailFrame::OnFormatRTF ()
{
	m_Format = e_FormatRTF;
	OnUpdateFrameTitle (TRUE);
}

void CMailFrame::OnUpdateFormatRTF (CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_Format == e_FormatRTF);
}
