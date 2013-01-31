//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2007 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPControlsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPControls.h"
#include "BCGPControlsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CBCGPURLLinkButton	m_bntURL;
	CBCGPURLLinkButton	m_btnMail;
	CString	m_strVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strVersion = _T("");
	//}}AFX_DATA_INIT
	m_strVersion.Format (_T("%d.%d"), _BCGCBPRO_VERSION_MAJOR, _BCGCBPRO_VERSION_MINOR);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_btnMail.SetURLPrefix (_T("mailto:"));
	m_btnMail.SetURL (_T("info@bcgsoft.com"));
	m_btnMail.SizeToContent ();
	m_btnMail.SetTooltip (_T("Send mail to author"));

	m_bntURL.SizeToContent ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_URL, m_bntURL);
	DDX_Control(pDX, IDC_MAIL, m_btnMail);
	DDX_Text(pDX, IDC_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBCGPControlsDlg dialog

CBCGPControlsDlg::CBCGPControlsDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CBCGPControlsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBCGPControlsDlg)
	m_bIsRightImage = FALSE;
	m_strToolTip = _T("ToolTip");
	m_bRightArrow = FALSE;
	m_iFrameRate = 200;
	m_iImage = 2;
	m_iBorderStyle = 0;
	m_iCursor = 0;
	m_strRGB = _T("");
	m_bMenuStayPressed = FALSE;
	m_bBackImage = FALSE;
	m_bXPButtons = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Color = RGB (255, 0, 255);
}

void CBCGPControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBCGPControlsDlg)
	DDX_Control(pDX, IDC_XP_BUTTONS, m_wndXPButtons);
	DDX_Control(pDX, IDC_COLOR_PICKER, m_ColorPicker);
	DDX_Control(pDX, IDC_IMAGE_AREA, m_wndImageArea);
	DDX_Control(pDX, IDC_EDIT_IMAGE, m_btnImageEdit);
	DDX_Control(pDX, IDC_FRAME_RATE, m_wndFrameRate);
	DDX_Control(pDX, IDC_STOP_ANIMATION, m_wndStopAnimation);
	DDX_Control(pDX, IDC_START_ANIMATION, m_wndStartAnimation);
	DDX_Control(pDX, IDC_ANIMATION, m_wndAnimation);
	DDX_Control(pDX, IDC_BUTTON_URL, m_btnLink);
	DDX_Control(pDX, IDC_EDIT_LIST, m_wndEditListBox);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btnMenu);
	DDX_Control(pDX, IDC_BUTTON, m_Button);
	DDX_Check(pDX, IDC_RIGHT_IMAGE, m_bIsRightImage);
	DDX_Text(pDX, IDC_TOOLTIP, m_strToolTip);
	DDX_Check(pDX, IDC_RIGHT_ARROW, m_bRightArrow);
	DDX_Slider(pDX, IDC_FRAME_RATE, m_iFrameRate);
	DDX_CBIndex(pDX, IDC_IMAGE, m_iImage);
	DDX_CBIndex(pDX, IDC_BORDER, m_iBorderStyle);
	DDX_CBIndex(pDX, IDC_CURSOR, m_iCursor);
	DDX_Text(pDX, IDC_RGB, m_strRGB);
	DDX_Check(pDX, IDC_PRESSED_ON_MENU, m_bMenuStayPressed);
	DDX_Check(pDX, IDC_BACKGROUND, m_bBackImage);
	DDX_Check(pDX, IDC_XP_BUTTONS, m_bXPButtons);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBCGPControlsDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CBCGPControlsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SET_TOOLTIP, OnSetTooltip)
	ON_BN_CLICKED(IDC_RIGHT_IMAGE, OnResetButton)
	ON_CBN_SELCHANGE(IDC_CURSOR, OnSetCursor)
	ON_BN_CLICKED(IDC_RIGHT_ARROW, OnRightArrow)
	ON_BN_CLICKED(IDC_BUTTON_MENU, OnButtonMenu)
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
	ON_BN_CLICKED(IDC_START_ANIMATION, OnStartAnimation)
	ON_BN_CLICKED(IDC_STOP_ANIMATION, OnStopAnimation)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_EDIT_IMAGE, OnEditImage)
	ON_BN_CLICKED(IDC_COLOR_DLG, OnColorDlg)
	ON_BN_CLICKED(IDC_COLOR_PICKER, OnColorPicker)
	ON_BN_CLICKED(IDC_PRESSED_ON_MENU, OnPressedOnMenu)
	ON_BN_CLICKED(IDC_BACKGROUND, OnBackground)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ITEM_1, OnItem1)
	ON_COMMAND(ID_ITEM_2, OnItem2)
	ON_COMMAND(ID_DIALOG_ABOUT, OnDialogAbout)
	ON_CBN_SELCHANGE(IDC_IMAGE, OnResetButton)
	ON_CBN_SELCHANGE(IDC_BORDER, OnResetButton)
	ON_UPDATE_COMMAND_UI(ID_ITEM_2, OnUpdateItem2)
	ON_BN_CLICKED(IDC_XP_BUTTONS, OnXpButtons)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPControlsDlg message handlers

BOOL CBCGPControlsDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	OnResetButton();
	OnSetCursor();
	OnSetTooltip();

	m_menu.LoadMenu (IDR_MENU1);
	m_btnMenu.m_hMenu = m_menu.GetSubMenu (0)->GetSafeHmenu ();
	m_btnMenu.SizeToContent ();

	m_wndEditListBox.SetStandardButtons ();
	m_wndEditListBox.EnableBrowseButton ();

	m_wndEditListBox.AddItem (_T("Item 1"));
	m_wndEditListBox.AddItem (_T("Item 2"));
	m_wndEditListBox.AddItem (_T("Item 3"));

	m_btnLink.SetURL (_T("http://www.bcgsoft.com"));
	m_btnLink.SetTooltip (_T("Visit BCGSoft site"));
	m_btnLink.SizeToContent ();

	m_wndAnimation.SetBitmap (IDB_GLOBE, 32, RGB (255, 0, 255), TRUE);

	m_Button.m_bTransparent = TRUE;

	m_wndStartAnimation.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
	m_wndStartAnimation.SetImage (IDB_PLAY, IDB_PLAY_HOT);
	m_wndStartAnimation.SizeToContent ();
	m_wndStartAnimation.SetTextHotColor (RGB (0, 0, 255));

	m_wndStopAnimation.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
	m_wndStopAnimation.SetImage (IDB_STOP, IDB_STOP_HOT);
	m_wndStopAnimation.SizeToContent ();
	m_wndStopAnimation.SetTextHotColor (RGB (0, 0, 255));

	m_wndFrameRate.SetRange (50, 1000);
	m_iFrameRate = 200;

	m_btnImageEdit.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
	m_btnImageEdit.SetImage (IDB_IMAGE);
	m_btnImageEdit.SizeToContent ();
	m_btnImageEdit.SetTextHotColor (RGB (0, 0, 255));

	m_bmpImage.LoadBitmap (IDB_TEST_BITMAP);

	BITMAP bmp;
	m_bmpImage.GetBitmap (&bmp);

	m_wndImageArea.GetClientRect (m_rectImage);
	m_wndImageArea.MapWindowPoints (this, m_rectImage);

	m_rectImage.right = m_rectImage.left + bmp.bmWidth;
	m_rectImage.bottom = m_rectImage.top + bmp.bmHeight;

	m_ColorPicker.EnableAutomaticButton (_T("Automatic"), RGB (255, 0, 255));
	m_ColorPicker.EnableOtherButton (_T("Other"));
	m_ColorPicker.SetColor ((COLORREF)-1);
	m_ColorPicker.SetColumnsNumber (10);
	m_strRGB = _T("255,0,255");

	CBCGPToolBar::AddToolBarForImageCollection (IDR_TOOLBAR_MENU_IMAGES);

	if (!CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
	{
		m_bXPButtons = FALSE;
		m_wndXPButtons.EnableWindow (FALSE);
	}

	UpdateData (FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBCGPControlsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBCGPDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBCGPControlsDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// Draw image:
		CRect rectFrame = m_rectImage;

		rectFrame.InflateRect (1, 1);
		dc.Draw3dRect (rectFrame, GetSysColor (COLOR_3DLIGHT), GetSysColor (COLOR_3DSHADOW));
		rectFrame.InflateRect (1, 1);
		dc.Draw3dRect (rectFrame, GetSysColor (COLOR_3DHILIGHT), GetSysColor (COLOR_3DDKSHADOW));

		dc.DrawState (m_rectImage.TopLeft (), m_rectImage.Size (), &m_bmpImage, 0);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBCGPControlsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBCGPControlsDlg::OnSetTooltip() 
{
	UpdateData ();
	m_Button.SetTooltip (m_strToolTip);
}

void CBCGPControlsDlg::OnResetButton() 
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
		m_Button.SetImage (IDB_BTN1, IDB_BTN1_HOT);
	}

	if (m_iImage == 0)
	{
		m_Button.SetWindowText (_T(""));
	}
	else
	{
		m_Button.SetWindowText (_T("BCGButton"));
	}

	m_Button.m_bRighImage = m_bIsRightImage;
	m_Button.SizeToContent ();
	m_Button.Invalidate ();
}

void CBCGPControlsDlg::OnSetCursor() 
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

void CBCGPControlsDlg::OnRightArrow() 
{
	UpdateData ();
	m_btnMenu.m_bRightArrow = m_bRightArrow;
	m_btnMenu.Invalidate ();
}

void CBCGPControlsDlg::OnButtonMenu() 
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
		return;
	}

	MessageBox (strItem);
}

void CBCGPControlsDlg::OnButton() 
{
	MessageBox (_T("Button Clicked!"));
}

void CBCGPControlsDlg::OnStartAnimation() 
{
	UpdateData ();

	m_wndAnimation.Play (m_iFrameRate);
	m_wndStartAnimation.EnableWindow (FALSE);
	m_wndStopAnimation.EnableWindow (TRUE);
}

void CBCGPControlsDlg::OnStopAnimation() 
{
	m_wndAnimation.Stop ();
	m_wndStartAnimation.EnableWindow (TRUE);
	m_wndStopAnimation.EnableWindow (FALSE);
}

void CBCGPControlsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CBCGPDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar != NULL && pScrollBar->GetDlgCtrlID () == IDC_FRAME_RATE)
	{
		// Slider notification...
		UpdateData ();
		m_wndAnimation.SetFrameRate (m_iFrameRate);
	}
}

void CBCGPControlsDlg::OnEditImage() 
{
	HBITMAP hBmpCopy = (HBITMAP) ::CopyImage (
		m_bmpImage.GetSafeHandle (), IMAGE_BITMAP, 0, 0, 0);
	ASSERT (hBmpCopy != NULL);

	CBCGPImageEditDlg dlg (CBitmap::FromHandle (hBmpCopy), this);
	if (dlg.DoModal () == IDOK)
	{
		m_bmpImage.DeleteObject ();
		m_bmpImage.Attach (hBmpCopy);

		InvalidateRect (m_rectImage);
		UpdateWindow ();
	}
	else
	{
		::DeleteObject (hBmpCopy);
	}
}

void CBCGPControlsDlg::OnColorDlg() 
{
	CBCGPColorDialog dlg (m_Color, 0, this);
	if (dlg.DoModal () == IDOK)
	{
		m_Color = dlg.GetColor ();
	}
}

void CBCGPControlsDlg::OnColorPicker() 
{
	COLORREF color = m_ColorPicker.GetColor ();

	m_strRGB.Format (_T("%d,%d,%d"), 
		GetRValue (color),
		GetGValue (color),
		GetBValue (color));

	UpdateData (FALSE);
}

void CBCGPControlsDlg::OnPressedOnMenu() 
{
	UpdateData ();
	m_btnMenu.m_bStayPressed = m_bMenuStayPressed;
}

void CBCGPControlsDlg::OnBackground() 
{
	UpdateData ();

	if (m_bBackImage)
	{
		SetBackgroundColor (RGB (255, 255, 255));
		SetBackgroundImage (IDB_BACK, CBCGPControlsDlg::BACKGR_TOPLEFT);
	}
	else
	{
		SetBackgroundColor (-1);
		SetBackgroundImage ((UINT) 0);
	}
}

void CBCGPControlsDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu (IDR_DIALOG_MENU);

	theApp.GetContextMenuManager ()->ShowPopupMenu (
		menu.GetSubMenu (0)->GetSafeHmenu (), point.x, point.y, this,
		TRUE);
}

void CBCGPControlsDlg::OnItem1() 
{
	MessageBox ("Command 1....");
}

void CBCGPControlsDlg::OnItem2() 
{
	MessageBox ("Command 2....");
}

void CBCGPControlsDlg::OnDialogAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CBCGPControlsDlg::OnUpdateItem2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck ();
}

void CBCGPControlsDlg::OnXpButtons() 
{
	UpdateData ();

	CBCGPButton::EnableWinXPTheme (m_bXPButtons);
	RedrawWindow ();
}

