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
// MyDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "MyDialogBar.h"

#include "MainFrm.h"
#include "BCGPTagManager.h"

#include "BCGPIE7DemoDoc.h"
#include "BCGPIE7DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMyDialogBarButton, CBCGPButton)

CMyDialogBarButton::CMyDialogBarButton()
{
	m_bTransparent = TRUE;
	m_nFlatStyle   = BUTTONSTYLE_NOBORDERS;
	m_bDrawFocus   = FALSE;
}

CMyDialogBarButton::~CMyDialogBarButton()
{

}

BEGIN_MESSAGE_MAP(CMyDialogBarButton, CBCGPButton)
END_MESSAGE_MAP()

void CMyDialogBarButton::OnDrawBorder (CDC* pDC, CRect& rectClient, UINT /*uiState*/)
{
	if (!CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
	{
		if (m_nFlatStyle == BUTTONSTYLE_FLAT)
		{
			if (m_bPushed)
			{
				pDC->Draw3dRect (&rectClient, globalData.clrBarShadow, globalData.clrBarHilite);
			}
			else if (m_bHighlighted)
			{
				pDC->Draw3dRect (&rectClient, globalData.clrBarHilite, globalData.clrBarShadow);
			}

			rectClient.DeflateRect (1, 1);
		}
	}
}

void CMyDialogBarButton::OnDraw (CDC* pDC, const CRect& rect, UINT uiState)
{
	CMyDialogBar* pParent = DYNAMIC_DOWNCAST(CMyDialogBar, GetParent ());
	if (pParent != NULL)
	{
		pParent->DrawButton (*this, pDC, rect, uiState);
	}
}

void CMyDialogBarButton::OnFillBackground (CDC* pDC, const CRect& rectClient)
{
	OnDrawParentBackground (pDC, rectClient);
}

void CMyDialogBarButton::OnDrawParentBackground (CDC* pDC, CRect rectClient)
{
	CMyDialogBar* pParent = DYNAMIC_DOWNCAST(CMyDialogBar, GetParent ());
	if (pParent != NULL)
	{
		pParent->DrawBackground (*this, pDC, rectClient);
	}
}



IMPLEMENT_DYNCREATE(CMyDialogBarMenuButton, CBCGPMenuButton)

CMyDialogBarMenuButton::CMyDialogBarMenuButton()
{
	m_bTransparent = TRUE;
	m_nFlatStyle   = BUTTONSTYLE_NOBORDERS;
	m_bDrawFocus   = FALSE;
	m_bStayPressed = TRUE;
	m_bOSMenu      = FALSE;
}

CMyDialogBarMenuButton::~CMyDialogBarMenuButton()
{

}

BEGIN_MESSAGE_MAP(CMyDialogBarMenuButton, CBCGPMenuButton)
	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()

void CMyDialogBarMenuButton::OnDrawBorder (CDC* pDC, CRect& rectClient, UINT /*uiState*/)
{
	if (!CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
	{
		if (m_nFlatStyle == BUTTONSTYLE_FLAT)
		{
			if (m_bPushed)
			{
				pDC->Draw3dRect (&rectClient, globalData.clrBarShadow, globalData.clrBarHilite);
			}
			else if (m_bHighlighted)
			{
				pDC->Draw3dRect (&rectClient, globalData.clrBarHilite, globalData.clrBarShadow);
			}

			rectClient.DeflateRect (1, 1);
		}
	}
}

void CMyDialogBarMenuButton::OnDraw (CDC* pDC, const CRect& rect, UINT uiState)
{
	CMyDialogBar* pParent = DYNAMIC_DOWNCAST(CMyDialogBar, GetParent ());
	if (pParent != NULL)
	{
		pParent->DrawButton (*this, pDC, rect, uiState);
	}
}

void CMyDialogBarMenuButton::OnFillBackground (CDC* pDC, const CRect& rectClient)
{
	OnDrawParentBackground (pDC, rectClient);
}

void CMyDialogBarMenuButton::OnDrawParentBackground (CDC* pDC, CRect rectClient)
{
	CMyDialogBar* pParent = DYNAMIC_DOWNCAST(CMyDialogBar, GetParent ());
	if (pParent != NULL)
	{
		pParent->DrawBackground (*this, pDC, rectClient);
	}
}

void CMyDialogBarMenuButton::OnShowMenu ()
{
	BOOL bRes = TRUE;

	CMyDialogBar* pParent = DYNAMIC_DOWNCAST(CMyDialogBar, GetParent ());
	if (pParent != NULL)
	{
		bRes = pParent->PrepareButtonMenu (*this);
	}

	if (bRes)
	{
		CBCGPMenuButton::OnShowMenu ();

		if (m_pToolTip->GetSafeHwnd () != NULL)
		{
			m_pToolTip->Pop ();

			CString str;
			m_pToolTip->GetText (str, this);
			m_pToolTip->UpdateTipText (str, this);
		}
	}
}

UINT CMyDialogBarMenuButton::OnGetDlgCode() 
{
	return CBCGPButton::OnGetDlgCode ();
}


/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar

IMPLEMENT_SERIAL (CMyDialogBar, CBCGPDialogBar, VERSIONABLE_SCHEMA | 1)

CMyDialogBar::CMyDialogBar()
{
	m_bInitialized = FALSE;
}

CMyDialogBar::~CMyDialogBar()
{
	
}

void CMyDialogBar::DrawBackground (CWnd& wnd, CDC* pDC, CRect rectClient)
{
	CRect rect = rectClient;
	wnd.ClientToScreen (rect);
	ScreenToClient (rect);

	pDC->BitBlt (rectClient.left, rectClient.top, 
		rectClient.Width (), rectClient.Height (), &m_memDC.GetDC (), rect.left, rect.top, SRCCOPY);
}

void CMyDialogBar::DrawButton(CBCGPButton& btn, CDC* pDC, const CRect& rect, UINT uiState)
{
	CBCGPToolbarButton btnTB;
	CBCGPVisualManager::BCGBUTTON_STATE state = CBCGPVisualManager::ButtonsIsRegular;

	if ((uiState & ODS_DISABLED) == ODS_DISABLED)
	{	
		btnTB.m_nStyle = TBBS_DISABLED;
	}
	else
	{
		if (btn.IsPushed ())
		{
			btnTB.m_nStyle = TBBS_PRESSED;
		}
		
		if (btn.IsHighlighted ())
		{
			state = CBCGPVisualManager::ButtonsIsHighlighted;
		}
	}

	CBCGPVisualManager::GetInstance ()->OnFillButtonInterior (pDC, &btnTB, rect, state);
}

void CMyDialogBar::ChangeStyle()
{
	LoadImages ();
}

BEGIN_MESSAGE_MAP(CMyDialogBar, CBCGPDialogBar)
	//{{AFX_MSG_MAP(CMyDialogBar)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SYSCOLORCHANGE()
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar message handlers

BOOL CMyDialogBar::OnInitDialog ()
{
	CRect rectClient;
	GetClientRect (rectClient);

	m_sizeDefault = rectClient.Size ();

	return TRUE;
}

LRESULT CMyDialogBar::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
	if (!CBCGPDialogBar::HandleInitDialog (wParam, lParam))
	{
		return FALSE;
	}

	m_bInitialized = OnInitDialog ();

	if (!IsInitialized ())
	{
		return FALSE;
	}

	ChangeStyle ();

	Resize (TRUE);

	return TRUE;
}

void CMyDialogBar::OnPaint ()
{
	CRect rectClient;
	GetClientRect (rectClient);

	CPaintDC dc (this);

	dc.BitBlt (rectClient.left, rectClient.top, 
		rectClient.Width (), rectClient.Height (), &m_memDC.GetDC (), 
		rectClient.left, rectClient.top, SRCCOPY);
}

void CMyDialogBar::PaintMemDC ()
{
	CRect rectClient;
	GetClientRect (rectClient);

	CRect rect = rectClient;
	ClientToScreen (rect);
	CFrameWnd* pFrame = BCGPGetParentFrame (this);
	pFrame->ScreenToClient (rect);

	m_memDC.GetDC().BitBlt (rectClient.left, rectClient.top, 
		rectClient.Width (), rectClient.Height (), &CRebarDC::GetInstance ().GetDC (), 
		rect.left, rect.top, SRCCOPY);
}

BOOL CMyDialogBar::OnEraseBkgnd(CDC* /*pDC*/) 
{
/*
	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPVisualManager::GetInstance()->FillRebarPane(pDC, this, rectClient);
*/
	return TRUE;
}

void CMyDialogBar::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize (nType, cx, cy);

	if (cx != 0 && IsInitialized ())
	{
		m_memDC.SetSize (CSize (cx, cy));

		PaintMemDC ();
		if (IsWindowVisible ())
		{
			Invalidate ();
		}

		Resize (FALSE);
	}
}

CSize CMyDialogBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CSize size (CBCGPDockingControlBar::CalcFixedLayout (bStretch, bHorz));

	size.cy = GetHeight (size.cy);

	return size;
}

void CMyDialogBar::OnSysColorChange()
{
	CBCGPDockingControlBar::OnSysColorChange ();

	if (IsInitialized ())
	{
		Resize (TRUE);
		PaintMemDC ();
		Invalidate ();
	}
}
