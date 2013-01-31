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
// ColorChooserBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"
#include "ColorChooserBar.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const long c_PresetCount = 23;
static long c_Presets[c_PresetCount][2] =
{
	{180, 100},
	{150,  75},
	{150, 100},
	{120,  75},
	{120, 100},
	{ 60,  75},
	{ 60, 100},
	{ 30,  75},
	{ 30, 100},
	{360,  25},
	{360, 100},
	{350, 135},
	{330,  75},
	{330, 100},
	{300, 100},
	{270, 100},
	{240,  75},
	{240, 100},
	{210,  75},
	{210, 100},
	{180,   0},
	{180,  25},
	{180,  75}
};


IMPLEMENT_DYNCREATE(CColorChooserButton, CBCGPButton)

CColorChooserButton::CColorChooserButton (const CSize& sizeImage, const CString& strImage)
{
	if (!strImage.IsEmpty ())
	{
		m_Image.SetImageSize (sizeImage);
		m_Image.LoadStr (strImage);

		m_bTransparent = TRUE;
	}
}

void CColorChooserButton::OnDraw (CDC* pDC, const CRect& rect, UINT uiState)
{
	if (!m_Image.IsValid ())
	{
		CBCGPButton::OnDraw (pDC, rect, uiState);
		return;
	}

	BOOL bPressed     = IsPressed ();
	BOOL bHighlighted = IsHighlighted ();

	int index = 0;
	if (bPressed)
	{
		if (bHighlighted)
		{
			index = 2;
		}
	}
	else if (bHighlighted)
	{
		index = 1;
	}

	m_Image.DrawEx (pDC, rect, index, 
		CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);
}

/////////////////////////////////////////////////////////////////////////////
// CColorChooserBar dialog

IMPLEMENT_SERIAL(CColorChooserBar, CBCGPDialogBar, VERSIONABLE_SCHEMA | 1)

CColorChooserBar::CColorChooserBar()
	: CBCGPDialogBar  ()
	, m_btnPresetPrev (CSize (18, 18), _T("IDB_BTN_BAR_PREV"))
	, m_btnPresetNext (CSize (18, 18), _T("IDB_BTN_BAR_NEXT"))
	, m_Preset (0)
{
	EnableVisualManagerStyle ();

	SetBorders (0, 0, 0, 0);

	//{{AFX_DATA_INIT(CColorChooserBar)
	m_nHue = 0;
	m_nSaturation = 0;
	//}}AFX_DATA_INIT
}

void CColorChooserBar::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorChooserBar)
	DDX_Control(pDX, IDC_CH_PRESET_PREV, m_btnPresetPrev);
	DDX_Control(pDX, IDC_CH_PRESET_NEXT, m_btnPresetNext);
	DDX_Control(pDX, IDC_CH_RESET, m_btnReset);
	DDX_Control(pDX, IDC_CH_SLIDER_S, m_wndSliderS);
	DDX_Control(pDX, IDC_CH_SLIDER_H, m_wndSliderH);
	DDX_Slider(pDX, IDC_CH_SLIDER_H, m_nHue);
	DDX_Slider(pDX, IDC_CH_SLIDER_S, m_nSaturation);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorChooserBar, CBCGPDialogBar)
	//{{AFX_MSG_MAP(CColorChooserBar)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorChooserBar message handlers

LRESULT CColorChooserBar::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
	if (!CBCGPDialogBar::HandleInitDialog(wParam, lParam))
	{
		return FALSE;
	}

	m_btnReset.m_bDefaultClickProcess = TRUE;
	m_btnReset.SizeToContent ();

	m_wndSliderH.SetRange (0, 360);
	m_wndSliderH.SetPos ((int)(GetVisualManager ()->GetImagesH () + 180.0));

	double value = GetVisualManager ()->GetImagesS () + 1.0;
	value = value * value * 100.0;

	m_wndSliderS.SetRange (0, 200);
	m_wndSliderS.SetPos ((int)value);

	return TRUE;
}

void CColorChooserBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar != NULL)
	{
		UpdateData ();
		UpdateHS ();
	}
	
	CBCGPDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CColorChooserBar::Reset ()
{
	m_nHue = 180;
	m_nSaturation = 100;

	UpdateData (FALSE);
	UpdateHS ();
}

void CColorChooserBar::Preset (BOOL bNext)
{
	if (bNext)
	{
		m_Preset++;
		if (m_Preset >= c_PresetCount)
		{
			m_Preset = 0;
		}
	}
	else
	{
		m_Preset--;
		if (m_Preset < 0)
		{
			m_Preset = c_PresetCount - 1;
		}
	}

	m_nHue = c_Presets[m_Preset][0];
	m_nSaturation = c_Presets[m_Preset][1];

	UpdateData (FALSE);
	UpdateHS ();
}

void CColorChooserBar::UpdateHS ()
{
	GetVisualManager ()->UpdateImages (m_nHue - 180, sqrt (m_nSaturation / 100.0) - 1.0);
	AfxGetMainWnd ()->RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
	CBCGPMiniFrameWnd::RedrawAll ();
}
