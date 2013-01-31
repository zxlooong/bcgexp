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
// Page3.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcontrols.h"
#include "Page3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage3 property page

IMPLEMENT_DYNCREATE(CPage3, CBCGPPropertyPage)

CPage3::CPage3() : CBCGPPropertyPage(CPage3::IDD)
{
	//{{AFX_DATA_INIT(CPage3)
	m_iFrameRate = 200;
	m_bTrueType = TRUE;
	m_bRaster = TRUE;
	m_bDeviceFont = TRUE;
	m_bDrawUsingFont = FALSE;
	//}}AFX_DATA_INIT
}

CPage3::~CPage3()
{
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage3)
	DDX_Control(pDX, IDC_CUSTOM_EDIT, m_wndCustomEdit);
	DDX_Control(pDX, IDC_FOLDER_EDIT, m_wndFolderEdit);
	DDX_Control(pDX, IDC_FILE_EDIT, m_wndFileEdit);
	DDX_Control(pDX, IDC_FONT, m_wndFont);
	DDX_Control(pDX, IDC_IMAGE_AREA, m_wndImageArea);
	DDX_Control(pDX, IDC_EDIT_IMAGE, m_btnImageEdit);
	DDX_Control(pDX, IDC_FRAME_RATE, m_wndFrameRate);
	DDX_Control(pDX, IDC_STOP_ANIMATION, m_wndStopAnimation);
	DDX_Control(pDX, IDC_START_ANIMATION, m_wndStartAnimation);
	DDX_Control(pDX, IDC_ANIMATION, m_wndAnimation);
	DDX_Control(pDX, IDC_BUTTON_URL, m_btnLink);
	DDX_Control(pDX, IDC_EDIT_LIST, m_wndEditListBox);
	DDX_Slider(pDX, IDC_FRAME_RATE, m_iFrameRate);
	DDX_Check(pDX, IDC_TRUETYPE, m_bTrueType);
	DDX_Check(pDX, IDC_RASTER, m_bRaster);
	DDX_Check(pDX, IDC_DEVICE, m_bDeviceFont);
	DDX_Check(pDX, IDC_DRAW_USING_FONT, m_bDrawUsingFont);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage3, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CPage3)
	ON_BN_CLICKED(IDC_START_ANIMATION, OnStartAnimation)
	ON_BN_CLICKED(IDC_STOP_ANIMATION, OnStopAnimation)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_EDIT_IMAGE, OnEditImage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RASTER, OnFontType)
	ON_BN_CLICKED(IDC_TRUETYPE, OnFontType)
	ON_BN_CLICKED(IDC_DEVICE, OnFontType)
	ON_BN_CLICKED(IDC_DRAW_USING_FONT, OnDrawUsingFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage3 message handlers

BOOL CPage3::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();
	
	m_wndEditListBox.SetStandardButtons ();
	m_wndEditListBox.EnableBrowseButton ();

	m_wndEditListBox.AddItem (_T("Item 1"));
	m_wndEditListBox.AddItem (_T("Item 2"));
	m_wndEditListBox.AddItem (_T("Item 3"));

	m_btnLink.SetURL (_T("http://www.bcgsoft.com"));
	m_btnLink.SetTooltip (_T("Visit BCGSoft site"));
	m_btnLink.SizeToContent ();

	m_wndAnimation.SetBitmap (IDB_GLOBE, 32, RGB (255, 0, 255), TRUE);

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

	m_wndFont.SelectFont (_T("Arial"));

	m_wndFolderEdit.EnableFolderBrowseButton ();
	m_wndFileEdit.EnableFileBrowseButton ();
	m_wndCustomEdit.EnableBrowseButton ();

	UpdateData (FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage3::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectFrame = m_rectImage;

	rectFrame.InflateRect (1, 1);
	dc.Draw3dRect (rectFrame, GetSysColor (COLOR_3DLIGHT), GetSysColor (COLOR_3DSHADOW));
	rectFrame.InflateRect (1, 1);
	dc.Draw3dRect (rectFrame, GetSysColor (COLOR_3DHILIGHT), GetSysColor (COLOR_3DDKSHADOW));

	dc.DrawState (m_rectImage.TopLeft (), m_rectImage.Size (), &m_bmpImage, 0);
}

void CPage3::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CBCGPPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar != NULL && pScrollBar->GetDlgCtrlID () == IDC_FRAME_RATE)
	{
		// Slider notification...
		UpdateData ();
		m_wndAnimation.SetFrameRate (m_iFrameRate);
	}
}

void CPage3::OnEditImage() 
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

void CPage3::OnStartAnimation() 
{
	UpdateData ();

	m_wndAnimation.Play (m_iFrameRate);
	m_wndStartAnimation.EnableWindow (FALSE);
	m_wndStopAnimation.EnableWindow (TRUE);
}

void CPage3::OnStopAnimation() 
{
	m_wndAnimation.Stop ();
	m_wndStartAnimation.EnableWindow (TRUE);
	m_wndStopAnimation.EnableWindow (FALSE);
}


void CPage3::OnFontType() 
{
	UpdateData ();

	int nFontType = 0;

	if (m_bTrueType)
	{
		nFontType |= TRUETYPE_FONTTYPE;
	}

	if (m_bRaster)
	{
		nFontType |= RASTER_FONTTYPE;
	}

	if (m_bDeviceFont)
	{
		nFontType |= DEVICE_FONTTYPE;
	}

	CWaitCursor wait;
	m_wndFont.Setup (nFontType);
}

void CPage3::OnDrawUsingFont() 
{
	UpdateData ();
	CBCGPFontComboBox::m_bDrawUsingFont = m_bDrawUsingFont;
	m_wndFont.RedrawWindow ();
}
