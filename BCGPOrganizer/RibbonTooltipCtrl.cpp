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
// RibbonTooltipCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "RibbonTooltipCtrl.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonTooltipCtrl

IMPLEMENT_DYNCREATE(CRibbonTooltipCtrl, CBCGPToolTipCtrl)

CRibbonTooltipCtrl::CRibbonTooltipCtrl()
{
	m_pParentMenuBar = NULL;
	m_pParentRibbon = NULL;
}

CRibbonTooltipCtrl::~CRibbonTooltipCtrl()
{
}


BEGIN_MESSAGE_MAP(CRibbonTooltipCtrl, CBCGPToolTipCtrl)
	//{{AFX_MSG_MAP(CRibbonTooltipCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TTN_SHOW, OnShow)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonTooltipCtrl message handlers

void CRibbonTooltipCtrl::OnShow(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_nID = 0;

	CPoint point;
	::GetCursorPos (&point);

	if (m_pParentRibbon != NULL)
	{
		ASSERT_VALID (m_pParentRibbon);

		m_pParentRibbon->ScreenToClient (&point);

		CBCGPBaseRibbonElement* pHit = m_pParentRibbon->HitTest (point, TRUE);

		if (pHit != NULL)
		{
			ASSERT_VALID (pHit);
			m_nID = pHit->GetID ();
		}
	}
	else if (m_pParentMenuBar != NULL)
	{
		ASSERT_VALID (m_pParentMenuBar);

		m_pParentMenuBar->ScreenToClient (&point);
		
		CBCGPBaseRibbonElement* pHit = m_pParentMenuBar->HitTest (point);

		if (pHit != NULL)
		{
			ASSERT_VALID (pHit);
			m_nID = pHit->GetID ();
		}
	}

	CBCGPToolTipCtrl::OnShow (pNMHDR, pResult);
}

int CRibbonTooltipCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolTipCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pParentRibbon = DYNAMIC_DOWNCAST (CBCGPRibbonBar, 
		CWnd::FromHandlePermanent (lpCreateStruct->hwndParent));

	m_pParentMenuBar = DYNAMIC_DOWNCAST (CBCGPRibbonPanelMenuBar,
		CWnd::FromHandlePermanent (lpCreateStruct->hwndParent));

	return 0;
}

CSize CRibbonTooltipCtrl::GetIconSize ()
{
	CBCGPToolBarImages* pBmp = ((CMainFrame*) GetTopLevelFrame ())->GetTooltipImage (m_nID);
	if (pBmp != NULL)
	{
		ASSERT_VALID (pBmp);
		return pBmp->GetImageSize ();
	}

	return CBCGPToolTipCtrl::GetIconSize ();
}

BOOL CRibbonTooltipCtrl::OnDrawIcon (CDC* pDC, CRect rectImage)
{
	ASSERT_VALID (pDC);

	CBCGPToolBarImages* pBmp = ((CMainFrame*) GetTopLevelFrame ())->GetTooltipImage (m_nID);
	if (pBmp != NULL)
	{
		ASSERT_VALID (pBmp);

		pBmp->SetTransparentColor (globalData.clrBtnFace);
		pBmp->DrawEx (pDC, rectImage, 0);

		return TRUE;
	}

	return CBCGPToolTipCtrl::OnDrawIcon (pDC, rectImage);
}
