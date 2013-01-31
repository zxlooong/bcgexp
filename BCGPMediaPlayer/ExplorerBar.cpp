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
// ExplorerBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"
#include "ExplorerBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static void DrawButton (CDC* pDC, CRect rect, const CString& strText, BOOL bIsMenuButton,
						UINT nStyle, BOOL bHighlight, BOOL bIsDroppedDown,
						BOOL bLogo)
{
	int nIndex = -1;

	if ((nStyle & TBBS_DISABLED) == 0)
	{
		if ((nStyle & TBBS_PRESSED) || bIsDroppedDown)
		{
			nIndex = 1;
		}
		else if (bHighlight)
		{
			nIndex = 0;
		}

		if (bLogo)
		{
			nIndex += 1;
		}
	}

	CRect rt (rect);
	CBCGPControlRenderer& rRen = GetVisualManager ()->GetExplorerBarButtonImage (bLogo);
	rt.top += rect.Height () - rRen.GetParams ().m_rectImage.Height ();

	if (nIndex != -1)
	{
		rRen.Draw (pDC, rt, nIndex);
	}

	rt.bottom = rt.top + rt.Height () * 3 / 4;

	COLORREF clr = pDC->SetTextColor (RGB (255, 255, 255));
	pDC->DrawText (strText, rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SetTextColor (clr);

	if (bIsMenuButton)
	{
		rt.bottom = rect.bottom;

		GetVisualManager ()->GetArrowDownIcon ().DrawEx (pDC, rt, 0, 
			CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertBottom);
	}
}

class CExplorerToolbarButton: public CBCGPToolbarButton
{
	DECLARE_DYNCREATE(CExplorerToolbarButton)

public:
	CExplorerToolbarButton ()
		: m_bLogo (FALSE)
	{
	}

	CExplorerToolbarButton (UINT nCmdID, LPCTSTR lpszText = NULL, BOOL bLogo = FALSE)
		: CBCGPToolbarButton (nCmdID, -1, lpszText)
		, m_bLogo (bLogo)
	{
	}

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* /*pImages*/,
						BOOL /*bHorz*/ = TRUE, BOOL /*bCustomizeMode*/ = FALSE,
						BOOL bHighlight = FALSE,
						BOOL /*bDrawBorder*/ = TRUE,
						BOOL /*bGrayDisabledButtons*/ = TRUE)
	{
		DrawButton (pDC, rect, m_strText, FALSE, m_nStyle, bHighlight, FALSE, m_bLogo);
	}

	virtual SIZE OnCalculateSize (CDC* /*pDC*/, const CSize& sizeDefault, BOOL /*bHorz*/)
	{
		return CSize (
			(m_nStyle & TBBS_SEPARATOR)
				? GetVisualManager ()->GetExplorerBarSeparatorWidth ()
				: GetVisualManager ()->GetExplorerBarButtonWidth (m_bLogo), 
			sizeDefault.cy);
	}

	virtual void CopyFrom (const CBCGPToolbarButton& s)
	{
		CBCGPToolbarButton::CopyFrom (s);

		CExplorerToolbarButton& src = const_cast<CExplorerToolbarButton&>((const CExplorerToolbarButton&)s);
		m_bLogo = src.m_bLogo;
	}

private:
	BOOL	m_bLogo;
};

IMPLEMENT_DYNCREATE(CExplorerToolbarButton, CBCGPToolbarButton)

class CExplorerToolbarMenuButton: public CBCGPToolbarMenuButton
{
	DECLARE_DYNCREATE(CExplorerToolbarMenuButton)

public:
	CExplorerToolbarMenuButton () 
	{
	}

	CExplorerToolbarMenuButton (HMENU hMenu, LPCTSTR lpszText = NULL)
		: CBCGPToolbarMenuButton ((UINT)-1, hMenu, -1, lpszText)
	{
		SetMenuOnly (TRUE);
	}

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* /*pImages*/,
						BOOL /*bHorz*/ = TRUE, BOOL /*bCustomizeMode*/ = FALSE,
						BOOL bHighlight = FALSE,
						BOOL /*bDrawBorder*/ = TRUE,
						BOOL /*bGrayDisabledButtons*/ = TRUE)
	{
		DrawButton (pDC, rect, m_strText, TRUE, m_nStyle, bHighlight, IsDroppedDown (), FALSE);
	}

	virtual SIZE OnCalculateSize (CDC* /*pDC*/, const CSize& sizeDefault, BOOL /*bHorz*/)
	{
		return CSize (GetVisualManager ()->GetExplorerBarButtonWidth (FALSE), sizeDefault.cy);
	}
};

IMPLEMENT_DYNCREATE(CExplorerToolbarMenuButton, CBCGPToolbarMenuButton)


/////////////////////////////////////////////////////////////////////////////
// CExplorerBar

IMPLEMENT_DYNCREATE (CExplorerBar, CBCGPExplorerToolBar)

CExplorerBar::CExplorerBar()
{
	m_bIsAeroEnabled = FALSE;
	m_bShowHotBorder = FALSE;
}

CExplorerBar::~CExplorerBar()
{
	
}

BEGIN_MESSAGE_MAP(CExplorerBar, CBCGPExplorerToolBar)
	//{{AFX_MSG_MAP(CExplorerBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CExplorerBar::OnLoadNavImages ()
{
	CVisualManager* pVM = GetVisualManager ();
	if (pVM != NULL)
	{
		pVM->m_arLinkImages.Add (CVisualManager::XLinkImages (&pVM->m_btnBaseExplorerBF, &m_NavImages));
		pVM->m_arLinkImages.Add (CVisualManager::XLinkImages (&pVM->m_btnBaseExplorerFrameBF, &m_NavFrames));

		pVM->m_btnBaseExplorerBF.CopyTo (m_NavImages);
		pVM->m_btnBaseExplorerFrameBF.CopyTo (m_NavFrames);

		pVM->UpdateLinkImages ();
	}
}

int CExplorerBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPExplorerToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetBorders (GetVisualManager ()->GetExplorerBarBorders ());

	return 0;
}

int CExplorerBar::GetRowHeight () const
{
	int nHeight = GetVisualManager ()->GetExplorerBarBackImage ().GetParams ().m_rectImage.Height ();

	if (nHeight == 0)
	{
		nHeight = CBCGPExplorerToolBar::GetRowHeight ();
	}	

	return nHeight;
}

void CExplorerBar::DrawSeparator (CDC* pDC, const CRect& rect, BOOL /*bHorz*/)
{
	CBCGPToolBarImages& rImage = GetVisualManager ()->GetExplorerBarSeparatorImage ();

	CRect rt (rect);
	rt.top += rect.Height () - rImage.GetImageSize ().cy;
	rImage.DrawEx (pDC, rt, 0, CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertBottom);
}

void CExplorerBar::CreateButtons ()
{
	{
		CMenu menu;
		menu.LoadMenu (IDR_EXPLORER_OPEN);
		InsertButton (CExplorerToolbarMenuButton (menu.GetSafeHmenu (), _T("Open &Media")));
	}

	{
		CMenu menu;
		menu.LoadMenu (IDR_EXPLORER_VIEW);
		InsertButton (CExplorerToolbarMenuButton (menu.GetSafeHmenu (), _T("&View")));
	}

	CExplorerToolbarButton sep;
	sep.m_nStyle = TBBS_SEPARATOR;
	InsertButton (sep);

	{
		CMenu menu;
		menu.LoadMenu (IDR_EXPLORER_HELP);
		InsertButton (CExplorerToolbarMenuButton (menu.GetSafeHmenu (), _T("&Help")));
	}

	InsertButton (CExplorerToolbarButton (ID_EXPLORER_WEB, NULL, TRUE));
}

void CExplorerBar::AdjustLocations ()
{
	CBCGPExplorerToolBar::AdjustLocations ();

	CBCGPToolbarButton* pButton = GetButton (CommandToIndex (ID_EXPLORER_WEB));
	CBCGPToolbarButton* pButtonLast = GetButton (GetCount () - 2);
	if (pButton != NULL && pButtonLast != NULL)
	{
		CRect rectClient;
		GetClientRect (rectClient);

		CRect rect = pButton->Rect ();
		CRect rectNew (rect);

		rectNew.right = rectClient.right;
		rectNew.left  = rectNew.right - rect.Width ();

		pButton->SetRect (rectNew);
		pButton->SetVisible (pButtonLast->Rect ().right < rectNew.left);

		UpdateTooltips ();
	}
}
