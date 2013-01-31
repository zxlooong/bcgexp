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
// BCGPMSMToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSMToolBar.h"

#include "BCGPMSMVisualManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBCGPToolBarImages CBCGPMSMToolBar::m_PressedImages;

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMToolBar

IMPLEMENT_DYNCREATE(CBCGPMSMToolBar, CBCGPToolBar)

CBCGPMSMToolBar::CBCGPMSMToolBar()
{
}


CBCGPMSMToolBar::~CBCGPMSMToolBar()
{
}

BOOL CBCGPMSMToolBar::LoadToolBar(UINT uiResID, UINT uiColdResID, UINT uiMenuResID, 
							  BOOL bLocked,
							  UINT uiDisabledResID, UINT uiMenuDisabledResID,
							  UINT uiHotResID, UINT uiPressedResID)
{
	if (!CBCGPToolBar::LoadToolBar (uiResID, uiColdResID, uiMenuResID, bLocked, 
		uiDisabledResID, uiMenuDisabledResID, uiHotResID))
	{
		return FALSE;
	}

	if (uiPressedResID != 0)
	{
		m_PressedImages.SetImageSize (m_sizeImage);

		if (!m_PressedImages.Load (uiPressedResID, AfxGetResourceHandle (), TRUE))
		{
			return FALSE;
		}

		ASSERT (m_Images.GetCount () == m_PressedImages.GetCount ());
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CBCGPMSMToolBar, CBCGPToolBar)
	//{{AFX_MSG_MAP(CBCGPMSMToolBar)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMToolBar message handlers

int CBCGPMSMToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetBarStyle((GetBarStyle () & 
		~(CBRS_GRIPPER | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT))
		| CBRS_SIZE_DYNAMIC);
	SetBorders ();
	
	SetGrayDisabledButtons (FALSE);

	return 0;
}

BOOL CBCGPMSMToolBar::DrawButton(CDC* pDC, CBCGPToolbarButton* pButton,
							CBCGPToolBarImages* pImages,
							BOOL bHighlighted, BOOL bDrawDisabledImages)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	CBCGPToolBarImages* pNewImages = pImages;

	CBCGPDrawState ds;

	if (!m_bMenuMode && (pButton->m_nStyle & (TBBS_PRESSED)) && 
		m_PressedImages.GetCount () > 0)
	{
		pNewImages = &m_PressedImages;
	
		pNewImages->SetTransparentColor (globalData.clrBtnFace);

		pNewImages->PrepareDrawImage (ds, GetImageSize (), FALSE);
	}

	if (!CBCGPToolBar::DrawButton (pDC, pButton, pNewImages, bHighlighted, 
			bDrawDisabledImages))
	{
		return FALSE;
	}

	if (pNewImages != pImages)
	{
		pNewImages->EndDrawImage (ds);
	}

	return TRUE;
}


void CBCGPMSMToolBar::OnSysColorChange ()
{
	CBCGPToolBar::OnSysColorChange ();

	m_PressedImages.OnSysColorChange ();
}
