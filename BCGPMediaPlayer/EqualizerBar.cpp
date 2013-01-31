//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// EqualizerBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"
#include "EqualizerBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEqualizerBar dialog

IMPLEMENT_SERIAL(CEqualizerBar, CBCGPDialogBar, VERSIONABLE_SCHEMA | 1)

CEqualizerBar::CEqualizerBar()
	: CBCGPDialogBar()
{
	EnableVisualManagerStyle ();

	SetBorders (0, 0, 0, 0);

	//{{AFX_DATA_INIT(CEqualizerBar)
	//}}AFX_DATA_INIT
}

void CEqualizerBar::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEqualizerBar)
	DDX_Control(pDX, IDC_EQ_SLIDER_1, m_wndSlider[0]);
	DDX_Control(pDX, IDC_EQ_SLIDER_2, m_wndSlider[1]);
	DDX_Control(pDX, IDC_EQ_SLIDER_3, m_wndSlider[2]);
	DDX_Control(pDX, IDC_EQ_SLIDER_4, m_wndSlider[3]);
	DDX_Control(pDX, IDC_EQ_SLIDER_5, m_wndSlider[4]);
	DDX_Control(pDX, IDC_EQ_SLIDER_6, m_wndSlider[5]);
	DDX_Control(pDX, IDC_EQ_SLIDER_7, m_wndSlider[6]);
	DDX_Control(pDX, IDC_EQ_SLIDER_8, m_wndSlider[7]);
	DDX_Control(pDX, IDC_EQ_SLIDER_9, m_wndSlider[8]);
	DDX_Control(pDX, IDC_EQ_SLIDER_10, m_wndSlider[9]);
	DDX_Control(pDX, IDC_LABEL1, m_wndLabel[0]);
	DDX_Control(pDX, IDC_LABEL2, m_wndLabel[1]);
	DDX_Control(pDX, IDC_LABEL3, m_wndLabel[2]);
	DDX_Control(pDX, IDC_LABEL4, m_wndLabel[3]);
	DDX_Control(pDX, IDC_LABEL5, m_wndLabel[4]);
	DDX_Control(pDX, IDC_LABEL6, m_wndLabel[5]);
	DDX_Control(pDX, IDC_LABEL7, m_wndLabel[6]);
	DDX_Control(pDX, IDC_LABEL8, m_wndLabel[7]);
	DDX_Control(pDX, IDC_LABEL9, m_wndLabel[8]);
	DDX_Control(pDX, IDC_LABEL10, m_wndLabel[9]);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEqualizerBar, CBCGPDialogBar)
	//{{AFX_MSG_MAP(CEqualizerBar)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEqualizerBar message handlers

LRESULT CEqualizerBar::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
	if (!CBCGPDialogBar::HandleInitDialog(wParam, lParam))
	{
		return FALSE;
	}

	LPCTSTR lpLabels [] =
	{
		_T("31Hz"),
		_T("62"),
		_T("125"),
		_T("250"),
		_T("500"),
		_T("1KHz"),
		_T("2"),
		_T("4"),
		_T("8"),
		_T("16KHz")
	};

	//-------------------
	// Create small font:
	//-------------------
	LOGFONT lf;
	memset (&lf, 0, sizeof (LOGFONT));

	globalData.fontRegular.GetLogFont (&lf);

	LONG lfHeightSaved = lf.lfHeight;

	lf.lfHeight = 9;
	if (lfHeightSaved < 0)
	{
		lf.lfHeight = -lf.lfHeight;
	}

	m_LabelFont.CreateFontIndirect (&lf);

	CRect rectSlider (GetVisualManager ()->GetEqualizerOffset (), 
		GetVisualManager ()->GetEqualizerChannelImage ().GetImageSize ());
	rectSlider.OffsetRect (2, 0);

	for (int i = 0; i < 10; i++)
	{
		CBCGPSliderCtrl& slider = m_wndSlider[i];
		CBCGPStatic& label = m_wndLabel[i];

		slider.m_bDrawFocus = FALSE;

		slider.SetWindowPos (this, rectSlider.left, rectSlider.top, 
			rectSlider.Width (), rectSlider.Height (), SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOREDRAW);

		slider.SetRange (0, 100);
		slider.SetPos (50);

		CRect rectLabel = rectSlider;
		rectLabel.InflateRect (2, 0);
		rectLabel.top = rectLabel.bottom + 4;
		rectLabel.bottom = rectLabel.top + globalData.GetTextHeight () * 2;

		label.SetWindowPos (this, rectLabel.left, rectLabel.top, 
			rectLabel.Width (), rectLabel.Height (), SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOREDRAW);

		label.SetWindowText (lpLabels [i]);
		label.SetFont (&m_LabelFont);

		rectSlider.OffsetRect (rectSlider.Width (), 0);
	}

	return TRUE;
}
