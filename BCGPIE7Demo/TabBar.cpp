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
// TempDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "TabBar.h"

#include "BCGPTagManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL (CTabBar, CMyDialogBar, VERSIONABLE_SCHEMA | 1)

CTabBar::CTabBar()
{
}

CTabBar::~CTabBar()
{
}

void CTabBar::DrawButton(CBCGPButton& btn, CDC* pDC, const CRect& rect, UINT uiState)
{
	CMyDialogBar::DrawButton (btn, pDC, rect, uiState);

	int index      = theApp.IsLargeIcons () ? 1 : 0;
	int indexImage = -1;

	UINT CtlID = ::GetWindowLong (btn.GetSafeHwnd (), GWL_ID);

	switch (CtlID)
	{
	case ID_VIEW_FAVORITES_CENTER:
		indexImage = 0;
		break;
	case ID_VIEW_ADD_TO_FAVORITES:
		indexImage = 1;
		break;
	}

	if (indexImage != -1)
	{
		m_Favorites[index].DrawEx (pDC, rect, indexImage, 
			CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);
	}
}

BOOL CTabBar::LoadImages()
{
	CString style;
	style.Format(_T("_%d"), theApp.m_Style);

	CBCGPTagManager xml;
	if (!xml.LoadFromResource (_T("IDX_ADDRESS_XML") + style, _T("XML")))
	{
		ASSERT(FALSE);
		return FALSE;
	}

	CString strStyle;
	if (!xml.ExcludeTag (_T("STYLE"), strStyle))
	{
		ASSERT(FALSE);
		return FALSE;
	}

	CString state = _T("NORMAL");
	if (theApp.IsLargeIcons ())
	{
		state = _T("LARGE");
	}

	CBCGPTagManager tmStyle (strStyle);

	CString strState;
	if (!tmStyle.ExcludeTag (state, strState))
	{
		ASSERT(FALSE);
		return FALSE;
	}

	CBCGPTagManager tmState (strState);

	CString strTab;
	if (tmState.ExcludeTag (_T("TAB"), strTab))
	{
		CBCGPTagManager tmTab (strTab);

		if (!tmTab.ReadToolBarImages (_T("SIDE"), m_Sides, _T("IDB_TAB_SIDES")))
		{
			ASSERT(FALSE);
			return FALSE;
		}
	}

	return TRUE;
}

void CTabBar::Resize (BOOL bFull)
{
	CRect rectClient;
	GetClientRect (rectClient);

	rectClient.right  = rectClient.left + max (rectClient.Width (), m_sizeDefault.cx);
	rectClient.bottom = rectClient.top + GetHeight (rectClient.Height ());

	HDWP hdwp = ::BeginDeferWindowPos (3);

	DWORD flags = SWP_NOZORDER | SWP_NOOWNERZORDER;

	BOOL bWinXP = CBCGPWinXPVisualManager::IsWinXPThemeAvailible ();

	CPoint pt (bWinXP ? 2 : 0, 1);
	CSize size = rectClient.Size ();

	size.cy--;
	if (bWinXP)
	{
		size.cy -= m_Sides.GetImageSize ().cy;
	}
	size.cx = size.cy - 2;

	if (bFull)
	{
		::DeferWindowPos (hdwp, m_btnFavorites.GetSafeHwnd (), HWND_TOP, 
			pt.x, pt.y, size.cx, size.cy, SWP_NOZORDER | SWP_NOOWNERZORDER);

		pt.x += size.cx;

		::DeferWindowPos (hdwp, m_btnFavoritesMenu.GetSafeHwnd (), HWND_TOP, 
			pt.x, pt.y, size.cx, size.cy, SWP_NOZORDER | SWP_NOOWNERZORDER);

		pt.x += size.cx;
	}
	else
	{
		pt.x += size.cx * 2;
	}
	
	pt.x++;
	size.cy = rectClient.Size ().cy;
	size.cx = rectClient.Width () - pt.x;

	::DeferWindowPos (hdwp, m_wndTab.GetSafeHwnd (), HWND_TOP, 
		pt.x, 0, size.cx, size.cy, flags);

	::EndDeferWindowPos (hdwp);
}

BEGIN_MESSAGE_MAP(CTabBar, CMyDialogBar)
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTempDialogBar message handlers

BOOL CTabBar::OnInitDialog ()
{
	if (!CMyDialogBar::OnInitDialog ())
	{
		return FALSE;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	m_btnFavorites.SubclassDlgItem (ID_VIEW_FAVORITES_CENTER, this);
	m_btnFavorites.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
	m_btnFavorites.SetTooltip (_T("View favorites and history (Alt+C)"));
	m_btnFavoritesMenu.SubclassDlgItem (ID_VIEW_ADD_TO_FAVORITES, this);
	m_btnFavoritesMenu.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
	m_btnFavoritesMenu.SetTooltip (_T("Add to Favorites (Alt+Z)"));
	m_menuFavorites.LoadMenu (IDR_ADD_FAVORITES_POPUP);
	m_btnFavoritesMenu.m_hMenu = m_menuFavorites.GetSubMenu (0)->GetSafeHmenu ();

	if (!m_wndTab.Create (rectClient, this, 1))
	{
		return FALSE;
	}

	m_Favorites[0].SetImageSize (CSize (16, 16));
	m_Favorites[0].Load (IDB_FAVORITES_32);
	m_Favorites[1].SetImageSize (CSize (24, 24));
	m_Favorites[1].Load (IDB_FAVORITES_32_120);

	return TRUE;
}

void CTabBar::PaintMemDC ()
{
	CMyDialogBar::PaintMemDC ();

	if (CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
	{
		int nBorder = m_Sides.GetImageSize ().cy;

		CRect rectClient;
		GetClientRect (rectClient);
		rectClient.bottom -= nBorder;

		CRect rect = rectClient;
		rect.top = rect.bottom;
		rect.bottom += nBorder;
		m_Sides.DrawEx (&m_memDC.GetDC (), rect, 0, CBCGPToolBarImages::ImageAlignHorzStretch);
	}
}

void CTabBar::OnPaint()
{
	CRect rectClient;
	GetClientRect (rectClient);

	CPaintDC dc (this);

	dc.BitBlt (rectClient.left, rectClient.top, 
		rectClient.Width (), rectClient.Height (), &m_memDC.GetDC (), 
		rectClient.left, rectClient.top, SRCCOPY);

	m_btnFavorites.Invalidate ();
	m_btnFavoritesMenu.Invalidate ();

	m_wndTab.Invalidate ();
}

int CTabBar::GetHeight (int height) const
{
	height = theApp.IsLargeIcons () ? 38 : 28;

	if (m_Sides.IsValid () && CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
	{
		height += m_Sides.GetImageSize ().cy;
	}

	height += 2;

	return height;
}

void CTabBar::ShowFavoritesMenu ()
{
	m_btnFavoritesMenu.SendMessage(WM_KEYDOWN, VK_SPACE, 0);
}

void CTabBar::AddTab (HWND hWnd)
{
	m_wndTab.AddTab (hWnd);
}

void CTabBar::RemoveTab (HWND hWnd)
{
	m_wndTab.RemoveTab (hWnd);
}

void CTabBar::SetTabText (HWND hWnd)
{
	m_wndTab.SetTabText (hWnd);
}

void CTabBar::SetTabIcon (HWND hWnd)
{
	m_wndTab.SetTabIcon (hWnd);
}

void CTabBar::SetActiveTab (HWND hWnd)
{
	m_wndTab.SetActiveTab (hWnd);
}

void CTabBar::UpdateTabs (BOOL bRedraw)
{
	m_wndTab.UpdateTabs (bRedraw);
}
