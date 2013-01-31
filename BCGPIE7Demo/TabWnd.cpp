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
// TabWnd.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"
#include "TabWnd.h"

#include "BCGPTagManager.h"
#include "TrackMouse.h"
#include "MyDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class XTabWnd: public CBCGPTabWnd
{
	friend class CTabMenuButton;
	friend class CTabWnd;
};

#define IDC_BTN_MENU		100
#define IDC_BTN_SCROLL_PREV	101
#define IDC_BTN_SCROLL_NEXT	102
#define IDC_BTN_NEW			103

const int n_MarginHorz   = 8;
const int n_SizeNewX     = 29;
const int n_SizeMenuX    = 15;
const int n_SizeScrollX  = 20;

const int n_SizeTabMinX  = 68;
const int n_SizeTabMid1X = 167;
const int n_SizeTabMid2X = 178;
const int n_SizeTabMaxX  = 299;
const int n_SizeTabSMinX = 90;

const UINT n_idStart = (UINT) -100;

IMPLEMENT_DYNCREATE(CTabButton, CBCGPButton)

CTabButton::CTabButton()
{
	m_bTransparent = TRUE;
	m_nFlatStyle   = BUTTONSTYLE_NOBORDERS;
	m_bDrawFocus   = FALSE;
}

CTabButton::~CTabButton()
{

}

BEGIN_MESSAGE_MAP(CTabButton, CBCGPButton)
END_MESSAGE_MAP()

void CTabButton::OnDraw (CDC* pDC, const CRect& rect, UINT uiState)
{
	CTabWnd* pParent = DYNAMIC_DOWNCAST(CTabWnd, GetParent ());
	if (pParent != NULL)
	{
		pParent->DrawButton (*this, pDC, rect, uiState);
	}
}

void CTabButton::OnFillBackground (CDC* pDC, const CRect& rectClient)
{
	OnDrawParentBackground (pDC, rectClient);
}

void CTabButton::OnDrawParentBackground (CDC* pDC, CRect rectClient)
{
	CTabWnd* pParent = DYNAMIC_DOWNCAST(CTabWnd, GetParent ());
	if (pParent != NULL)
	{
		pParent->DrawBackground (*this, pDC, rectClient);
	}
}


IMPLEMENT_DYNCREATE(CTabMenuButton, CBCGPMenuButton)

CTabMenuButton::CTabMenuButton()
{
	m_bTransparent = TRUE;
	m_nFlatStyle   = BUTTONSTYLE_NOBORDERS;
	m_bDrawFocus   = FALSE;
	m_bStayPressed = TRUE;
	m_bOSMenu      = FALSE;
}

CTabMenuButton::~CTabMenuButton()
{

}

BEGIN_MESSAGE_MAP(CTabMenuButton, CBCGPMenuButton)
	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()

void CTabMenuButton::OnDraw (CDC* pDC, const CRect& rect, UINT uiState)
{
	CTabWnd* pParent = DYNAMIC_DOWNCAST(CTabWnd, GetParent ());
	if (pParent != NULL)
	{
		pParent->DrawButton (*this, pDC, rect, uiState);
	}
}

void CTabMenuButton::OnFillBackground (CDC* pDC, const CRect& rectClient)
{
	OnDrawParentBackground (pDC, rectClient);
}

void CTabMenuButton::OnDrawParentBackground (CDC* pDC, CRect rectClient)
{
	CTabWnd* pParent = DYNAMIC_DOWNCAST(CTabWnd, GetParent ());
	if (pParent != NULL)
	{
		pParent->DrawBackground (*this, pDC, rectClient);
	}
}

void CTabMenuButton::OnShowMenu ()
{
	BOOL bRes = TRUE;

	CTabWnd* pParent = DYNAMIC_DOWNCAST(CTabWnd, GetParent ());
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

	XTabWnd::m_mapDocIcons.RemoveAll ();
}

UINT CTabMenuButton::OnGetDlgCode() 
{
	return CBCGPButton::OnGetDlgCode ();
}



/////////////////////////////////////////////////////////////////////////////
// CTabWnd

IMPLEMENT_DYNCREATE(CTabWnd, CWnd)

CTabWnd::CTabWnd()
	: m_Active        (-1)
	, m_Highlighted   (-1)
	, m_bInitialized  (FALSE)
	, m_pToolTip      (NULL)
	, m_pToolTipClose (NULL)
	, m_FirstVisible  (0)
	, m_bTracked      (FALSE)
	, m_ClosePressed  (FALSE)
	, m_CloseHighlighted(FALSE)
{
}

CTabWnd::~CTabWnd()
{

}


BOOL CTabWnd::Create (const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if (!CWnd::Create (
		globalData.RegisterWindowClass (_T("TabWnd")), _T(""),
		WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, rect,
		pParentWnd, nID))
	{
		return FALSE;
	}

	return TRUE;
}


BEGIN_MESSAGE_MAP(CTabWnd, CWnd)
	//{{AFX_MSG_MAP(CTabWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_REGISTERED_MESSAGE(BCGM_UPDATETOOLTIPS, OnBCGUpdateToolTips)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnNeedTipText)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTabWnd message handlers

void CTabWnd::ActivateMDI(int index)
{
	if (index != -1 && index != m_Active)
	{
		CMDIFrameWnd* pFrame = DYNAMIC_DOWNCAST (CMDIFrameWnd, AfxGetMainWnd ());
		if (pFrame != NULL)
		{
			pFrame->PostMessage (WM_MDIACTIVATE, (WPARAM)m_Tabs[index]->m_hWnd, 0);
		}
	}
}

void CTabWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);

	if (!m_rectClose.IsRectEmpty () &&
		m_rectClose.PtInRect (point))
	{
		if (!m_ClosePressed)
		{
			m_CloseHighlighted = TRUE;
			m_ClosePressed = TRUE;

			SetCapture ();

			RedrawWindow ();
		}
	}
	else
	{
		ActivateMDI (GetTabIndexFromPoint (point));
	}
}

void CTabWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);

	if (m_ClosePressed || m_CloseHighlighted)
	{
		BOOL bClose = m_ClosePressed && m_CloseHighlighted;
		m_ClosePressed = FALSE;
		m_CloseHighlighted = FALSE;

		ReleaseCapture ();

		RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		if (bClose)
		{
			AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_FILE_CLOSE);
		}
	}
}

void CTabWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);

	BOOL bRedraw = FALSE;

	if (!m_rectClose.IsRectEmpty () &&
		m_rectClose.PtInRect (point))
	{
		if (!m_CloseHighlighted)
		{
			m_CloseHighlighted = TRUE;
			bRedraw = TRUE;
		}
	}
	else
	{
		if (m_CloseHighlighted)
		{
			m_CloseHighlighted = FALSE;
			bRedraw = TRUE;
		}
	}

	int index = GetTabIndexFromPoint (point);
	if (index == m_Active)
	{
		index = -1;
	}

	if (m_Highlighted != index)
	{
		m_Highlighted = index;
		bRedraw = TRUE;
	}

	if (!m_bTracked)
	{
		m_bTracked = TRUE;
		
		TRACKMOUSEEVENT trackmouseevent;
		trackmouseevent.cbSize = sizeof(trackmouseevent);
		trackmouseevent.dwFlags = TME_LEAVE;
		trackmouseevent.hwndTrack = GetSafeHwnd();
		trackmouseevent.dwHoverTime = HOVER_DEFAULT;
		::BCGPTrackMouse (&trackmouseevent);	
	}

	if (bRedraw)
	{
		RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
}

LRESULT CTabWnd::OnMouseLeave(WPARAM, LPARAM)
{
	m_bTracked = FALSE;

	if (m_Highlighted != -1 || m_CloseHighlighted)
	{	
		m_Highlighted = -1;
		m_CloseHighlighted = FALSE;

		RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}	

	return 0;
}

BOOL CTabWnd::PreTranslateMessage(MSG* pMsg) 
{
	if (GetTabsNum () > 0)
	{
		CPoint point;
		::GetCursorPos (&point);
		ScreenToClient (&point);

		if (pMsg->message == WM_CANCELMODE)
		{
			if (m_CloseHighlighted || m_ClosePressed)
			{
				m_CloseHighlighted = FALSE;
				m_ClosePressed = FALSE;

				ReleaseCapture ();

				RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}	
		}

		if (m_pToolTipClose->GetSafeHwnd () != NULL &&
			!m_rectClose.IsRectEmpty () &&
			m_rectClose.PtInRect (point))
		{
			if (m_pToolTip->GetSafeHwnd () != NULL)
			{
				m_pToolTip->Pop ();
			}
			m_pToolTipClose->RelayEvent(pMsg);
		}
		else if (m_pToolTip->GetSafeHwnd () != NULL)
		{
			m_pToolTip->RelayEvent(pMsg);
		}
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

int CTabWnd::GetTabsNum () const
{
	return (int)m_Tabs.GetSize ();
}

void CTabWnd::RecalcLayout ()
{
	CRect rectClient;
	GetClientRect (rectClient);

	rectClient.DeflateRect (n_MarginHorz, 4, n_MarginHorz, 0);
	if (CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
	{
		rectClient.bottom -= m_Sides.GetImageSize ().cy;
	}
	m_rectTabs = rectClient;

	int count = GetTabsNum ();

	BOOL bNeedMenu   = FALSE;
	BOOL bNeedScroll = FALSE;
	if (count > 0)
	{
		m_rectTabs.right -= n_SizeNewX;

		if (count > 1)
		{
			bNeedMenu = TRUE;
			m_rectTabs.left += n_SizeMenuX;
		}

		if (count == 1)
		{
			if (n_SizeTabMaxX < m_rectTabs.Width ())
			{
				m_rectTabs.right = m_rectTabs.left + min (m_rectTabs.Width (), n_SizeTabMaxX);
			}
			else
			{
				m_rectTabs.right = m_rectTabs.left + max (m_rectTabs.Width (), n_SizeTabMid1X);
			}
		}
		else 
		{
			m_rectTabs.right = m_rectTabs.left + min (m_rectTabs.Width (), n_SizeTabMid2X * count);
		}

		bNeedScroll = (m_rectTabs.Width () / count) <= n_SizeTabMinX;

		if (bNeedScroll)
		{
			m_rectTabs.left += n_SizeScrollX;
			m_rectTabs.right -= n_SizeScrollX;

			if (m_rectTabs.Width () < n_SizeTabSMinX)
			{
				m_rectTabs.right = m_rectTabs.left + n_SizeTabSMinX;
			}
		}
	}

	m_btnMenu.ShowWindow (bNeedMenu ? SW_SHOW : SW_HIDE);
	m_btnScroll[0].ShowWindow (bNeedScroll ? SW_SHOW : SW_HIDE);
	m_btnScroll[1].ShowWindow (bNeedScroll ? SW_SHOW : SW_HIDE);
	if (bNeedMenu)
	{
		m_btnMenu.SetWindowPos (this, rectClient.left, rectClient.top,
			n_SizeMenuX, rectClient.Height (), SWP_NOZORDER | SWP_NOOWNERZORDER);
	}
	if (bNeedScroll)
	{
		m_btnScroll[0].SetWindowPos (this, m_rectTabs.left - n_SizeScrollX, rectClient.top,
			n_SizeScrollX, rectClient.Height (), SWP_NOZORDER | SWP_NOOWNERZORDER);

		m_btnScroll[1].SetWindowPos (this, m_rectTabs.right, rectClient.top,
			n_SizeScrollX, rectClient.Height (), SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	if (count == 0)
	{
		m_rectTabs.right = m_rectTabs.left = rectClient.left;
	}	

	m_btnNew.SetWindowPos (this, m_rectTabs.right + (bNeedScroll ? n_SizeScrollX : 0), rectClient.top,
		n_SizeNewX, rectClient.Height (), SWP_NOZORDER | SWP_NOOWNERZORDER);

	AdjustTabs ();
}

void CTabWnd::AdjustTabs ()
{
	BOOL bScroll = m_btnScroll[1].GetSafeHwnd () != NULL && m_btnScroll[1].IsWindowVisible ();

	m_Highlighted      = -1;
	m_ClosePressed     = FALSE;
	m_CloseHighlighted = FALSE;

	m_TabRects.RemoveAll ();
	if (m_pToolTip->GetSafeHwnd () != NULL)
	{
		for (int i = 0; i < m_pToolTip->GetToolCount (); i++)
		{
			m_pToolTip->DelTool (this, i + 1);
		}
	}

	CRect rect (m_rectTabs);

	int count = (int)m_Tabs.GetSize ();
	if (bScroll)
	{
		count = max (rect.Width () / n_SizeTabMinX, 1);
	}

	m_rectClose.SetRectEmpty ();

	if (count > 0)
	{
		rect.right = rect.left + rect.Width () / count;

		for (int i = 0; i < count; i++)
		{
			if (i == count - 1)
			{
				rect.right = m_rectTabs.right;
			}

			m_TabRects.Add (rect);

			if (m_pToolTip->GetSafeHwnd () != NULL)
			{
				m_pToolTip->AddTool (this, LPSTR_TEXTCALLBACK, rect, i + 1);
			}

			rect.OffsetRect (rect.Width (), 0);
		}

		AdjustScroll ();

		if (count > 1)
		{
			int active = m_Active - m_FirstVisible;
			if (0 <= active && active < count)
			{
				m_rectClose = m_TabRects[active];

				CSize sizeClose (m_Close.GetImageSize ());
				m_rectClose.right -= 4;
				m_rectClose.left   = m_rectClose.right - sizeClose.cx;
				m_rectClose.top    = m_rectClose.top + (m_rectClose.Height () - sizeClose.cy) / 2;
				m_rectClose.bottom = m_rectClose.top + sizeClose.cy;
			}
		}
	}

	if (m_pToolTipClose->GetSafeHwnd () != NULL)
	{
		if (m_rectClose.IsRectEmpty ())
		{
			if (m_pToolTipClose->GetToolCount () == 1)
			{
				m_pToolTipClose->DelTool (this, 1);
			}
		}
		else
		{
			if (m_pToolTipClose->GetToolCount () == 1)
			{
				m_pToolTipClose->SetToolRect (this, 1, m_rectClose);
			}
			else
			{
				m_pToolTipClose->AddTool (this, LPSTR_TEXTCALLBACK, m_rectClose, 1);
			}
		}
	}
}

void CTabWnd::AdjustScroll ()
{
	int count = (int)m_TabRects.GetSize ();
	if (GetTabsNum () <= count)
	{
		m_FirstVisible = 0;
		return;
	}

	int active = m_Active - m_FirstVisible;
	if (0 <= active && active < count)
	{
		m_FirstVisible = min (m_FirstVisible, GetTabsNum () - count);
	}
	else
	{
		if (active < 0)
		{
			m_FirstVisible = m_Active;
		}
		else
		{
			m_FirstVisible = m_Active - count + 1;
		}
	}

	m_btnScroll[0].EnableWindow (m_FirstVisible > 0);
	m_btnScroll[1].EnableWindow (m_FirstVisible < GetTabsNum () - count);
}

void CTabWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	if (m_bInitialized)
	{
		RecalcLayout ();
		RedrawWindow ();
	}
}

int CTabWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_btnMenu.Create (_T(""), WS_CHILD, CRect (0, 0, 0, 0), this, IDC_BTN_MENU);
	m_btnMenu.SetTooltip (_T("Tab List"));
	m_btnScroll[0].Create (_T(""), WS_CHILD, CRect (0, 0, 0, 0), this, IDC_BTN_SCROLL_PREV);
	m_btnScroll[1].Create (_T(""), WS_CHILD, CRect (0, 0, 0, 0), this, IDC_BTN_SCROLL_NEXT);
	m_btnNew.Create (_T(""), WS_CHILD | WS_VISIBLE, CRect (0, 0, 0, 0), this, IDC_BTN_NEW);
	m_btnNew.SetTooltip (_T("New Tab (Ctrl+T)"));

	m_ImagesDisabled.SetImageSize (CSize (14, 14));
	m_ImagesDisabled.Load (IDB_TAB_ICONS_D_32);
	m_ImagesNormal.SetImageSize (CSize (14, 14));
	m_ImagesNormal.Load (IDB_TAB_ICONS_N_32);
	m_ImagesHot.SetImageSize (CSize (14, 14));
	m_ImagesHot.Load (IDB_TAB_ICONS_H_32);

	if (CBCGPTooltipManager::CreateToolTip (m_pToolTip, this,
		BCGP_TOOLTIP_TYPE_TAB))
	{
		m_pToolTip->SetWindowPos (&wndTop, -1, -1, -1, -1,    
								SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}
	if (CBCGPTooltipManager::CreateToolTip (m_pToolTipClose, this,
		BCGP_TOOLTIP_TYPE_TAB))
	{
		m_pToolTipClose->SetWindowPos (&wndTop, -1, -1, -1, -1,    
								SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	ChangeStyle ();

	m_bInitialized = TRUE;
	
	return 0;
}

void CTabWnd::OnDestroy()
{
	CBCGPTooltipManager::DeleteToolTip (m_pToolTip);
	CBCGPTooltipManager::DeleteToolTip (m_pToolTipClose);

	CWnd::OnDestroy();
}

BOOL CTabWnd::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

void CTabWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTabWnd::DrawTab(CDC* pDC, CRect rect, int index)
{
	ASSERT_VALID (pDC);

	CTabInfo* pTabInfo = m_Tabs[index];

	rect.DeflateRect (4, 0);
	if (index == m_Active)
	{
		rect.right -= (m_Close.GetImageSize ().cx + 2);
	}

	CSize size (16, 16);

	if (pTabInfo->m_hIcon != NULL)
	{
		::DrawIconEx (pDC->GetSafeHdc (), rect.left, 
			rect.top + (rect.Height () - size.cy) / 2, 
			pTabInfo->m_hIcon, size.cx, size.cy, 0, NULL, DI_NORMAL);
	}

	rect.left += size.cx + 2;

	COLORREF clrText = pDC->SetTextColor (RGB (0, 0 ,0));
	int bkMode = pDC->SetBkMode (TRANSPARENT);

	pDC->DrawText (pTabInfo->m_strText, rect, 
		DT_END_ELLIPSIS | DT_SINGLELINE | DT_EXPANDTABS | DT_NOPREFIX | DT_LEFT | DT_VCENTER);

	pDC->SetBkMode (bkMode);
	pDC->SetTextColor (clrText);
}

void CTabWnd::DrawBackground (CWnd& wnd, CDC* pDC, CRect rectClient)
{
	CMyDialogBar* pBar = DYNAMIC_DOWNCAST(CMyDialogBar, GetParent ());
	if (pBar != NULL)
	{
		pBar->DrawBackground (wnd, pDC, rectClient);
	}
}

void CTabWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPMemDC memDC (dc, rectClient);
	CDC* pDC = &memDC.GetDC ();

	DrawBackground (*this, pDC, rectClient);

	BOOL bWinXP = CBCGPWinXPVisualManager::IsWinXPThemeAvailible ();

	CRect rect (rectClient);
	if (bWinXP)
	{
		rect.top = rect.bottom - m_Sides.GetImageSize ().cy;

		if (m_rectTabs.left <= m_rectTabs.right)
		{
			rect.right = m_rectTabs.left;
			m_Sides.DrawEx (pDC, rect, 0, CBCGPToolBarImages::ImageAlignHorzStretch);
			
			rect.left = m_rectTabs.right;
			rect.right = rectClient.right;
			m_Sides.DrawEx (pDC, rect, 0, CBCGPToolBarImages::ImageAlignHorzStretch);
		}
		else
		{
			m_Sides.DrawEx (pDC, rect, 0, CBCGPToolBarImages::ImageAlignHorzStretch);
		}
	}

	if (m_btnMenu.IsWindowVisible ())
	{
		m_btnMenu.Invalidate ();
	}
	if (m_btnScroll[0].IsWindowVisible ())
	{
		m_btnScroll[0].Invalidate ();
	}
	if (m_btnScroll[1].IsWindowVisible ())
	{
		m_btnScroll[1].Invalidate ();
	}
	m_btnNew.Invalidate ();

	if (m_rectTabs.left < m_rectTabs.right)
	{
		CFont* pFont = (CFont*) pDC->SelectObject (&globalData.fontRegular);

		// draw tabs
		int active = -1;
		int count = (int)m_TabRects.GetSize ();
		for (int i = 0; i < count; i++)
		{
			int index = i + m_FirstVisible;
			if (index == m_Active)
			{
				active = i;
				continue;
			}

			CRect rectTab (m_TabRects[i]);
			rect.left  = rectTab.left;
			rect.right = rectTab.right;

			if (bWinXP)
			{
				m_Sides.DrawEx (pDC, rect, 0, CBCGPToolBarImages::ImageAlignHorzStretch);

				CRgn rgn;
				rgn.CreateRectRgn (rectTab.left, rectTab.top, rectTab.right, rectTab.bottom);
				pDC->SelectClipRgn (&rgn);

				if (active == -1)
				{
					rectTab.right++;
				}
				else
				{
					rectTab.left--;
				}

				m_Items.Draw (pDC, rectTab, m_Highlighted == index ? 2 : 0);
			}
			else
			{
				rectTab.left++;
				rectTab.bottom += 2;

				pDC->Draw3dRect (rectTab,
							globalData.clrBtnLight, globalData.clrBtnDkShadow);
				rectTab.DeflateRect (1, 1);
				pDC->Draw3dRect (rectTab,
							globalData.clrBtnHilite, globalData.clrBtnShadow);
			}

			DrawTab (pDC, rectTab, index);

			pDC->SelectClipRgn (NULL);
		}

		if (active != -1)
		{
			// draw active tab
			CRect rectTab (m_TabRects[active]);
			rectTab.top -= 2;

			if (bWinXP)
			{
				m_Items.Draw (pDC, rectTab, 1);
			}
			else
			{
				rectTab.left++;
				rectTab.bottom += 2;

				pDC->Draw3dRect (rectTab,
							globalData.clrBtnLight, globalData.clrBtnDkShadow);
				rectTab.DeflateRect (1, 1);
				pDC->Draw3dRect (rectTab,
							globalData.clrBtnHilite, globalData.clrBtnShadow);
				rectTab.DeflateRect (1, 1);

				CBCGPDrawManager dm (*pDC);
				dm.FillGradient (rectTab, globalData.clrBarFace, globalData.clrBtnHilite, TRUE);
			}

			DrawTab (pDC, rectTab, active + m_FirstVisible);

			if (bWinXP)
			{
				rectTab.InflateRect (3, 0, 3, m_Sides.GetImageSize ().cy);
				rectTab.top = rectTab.bottom - m_Corners.GetParams ().m_rectImage.Height ();
				m_Corners.Draw (pDC, rectTab);
			}

			int indexClose = 0;
			if (m_ClosePressed)
			{
				indexClose = 1;
				if (m_CloseHighlighted)
				{
					indexClose = 2;
				}
			}
			else if (m_CloseHighlighted)
			{
				indexClose = 1;
			}

			m_Close.DrawEx (pDC, m_rectClose, indexClose);
		}

		if (pFont->GetSafeHandle () != NULL)
		{
			pDC->SelectObject (pFont);
		}
	}
}

BOOL CTabWnd::LoadImages()
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
		if (!tmTab.ReadControlRenderer (_T("CORNER"), m_Corners, _T("IDB_TAB_CORNERS")))
		{
			ASSERT(FALSE);
			return FALSE;
		}
		if (!tmTab.ReadControlRenderer (_T("ITEM"), m_Items, _T("IDB_TAB") + style))
		{
			ASSERT(FALSE);
			return FALSE;
		}
	}

	tmState.ReadToolBarImages (_T("BTN_SM_CLOSE"), m_Close, _T("IDB_BTN_SM_CLOSE"));

	return TRUE;
}

void CTabWnd::ChangeStyle()
{
	LoadImages ();
}

void CTabWnd::DrawButton(CBCGPButton& btn, CDC* pDC, const CRect& rect, UINT uiState)
{
	BOOL bActive = FALSE;
	BOOL bDisabled = (uiState & ODS_DISABLED) == ODS_DISABLED;
	if (!bDisabled)
	{
		bActive = btn.IsHighlighted () || btn.IsPressed () || btn.IsPushed ();
	}

	CRect rectBtn (rect);
	UINT CtlID = ::GetWindowLong (btn.GetSafeHwnd (), GWL_ID);

	if (CBCGPWinXPVisualManager::IsWinXPThemeAvailible ())
	{
		int count = GetTabsNum ();

		if (CtlID == IDC_BTN_MENU || CtlID == IDC_BTN_SCROLL_PREV)
		{
			rectBtn.right++;
		}
		else if (count > 0)
		{
			rectBtn.left--;
		}

		m_Items.Draw (pDC, rectBtn, bActive ? 2 : 0);
	}
	else
	{
		if (CtlID != IDC_BTN_MENU)
		{
			rectBtn.left++;
		}
		
		rectBtn.bottom += 2;

		pDC->Draw3dRect (rectBtn,
					globalData.clrBtnLight, globalData.clrBtnDkShadow);
		rectBtn.DeflateRect (1, 1);
		pDC->Draw3dRect (rectBtn,
					globalData.clrBtnHilite, globalData.clrBtnShadow);
	}

	CBCGPToolBarImages* pImages = &m_ImagesDisabled;
	if (!bDisabled)
	{
		if (bActive)
		{
			pImages = &m_ImagesHot;
		}
		else
		{
			pImages = &m_ImagesNormal;
		}
	}

	pImages->DrawEx (pDC, rect, CtlID - IDC_BTN_MENU, 
		CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);
}

BOOL CTabWnd::PrepareButtonMenu(CBCGPMenuButton& btn)
{
	UINT id = ::GetWindowLong (btn.GetSafeHwnd (), GWL_ID);
	
	if (id != IDC_BTN_MENU)
	{
		return TRUE;
	}

	if (m_menu.GetSafeHmenu () != NULL)
	{
		m_menu.DestroyMenu ();
	}

	m_menu.CreatePopupMenu ();

	for (int i = 0; i < m_Tabs.GetSize (); i ++)
	{
		CTabInfo* pTab = m_Tabs [i];
		ASSERT_VALID (pTab);

		const UINT uiID = n_idStart - i;
		CString strTabName = pTab->m_strText;

		//--------------------------------
		// Replace all single '&' by '&&':
		//--------------------------------
		const CString strDummyAmpSeq = _T("\001\001");

		strTabName.Replace (_T("&&"), strDummyAmpSeq);
		strTabName.Replace (_T("&"), _T("&&"));
		strTabName.Replace (strDummyAmpSeq, _T("&&"));

		m_menu.AppendMenu (MF_STRING, uiID, strTabName);

		if (i == m_Active)
		{
			m_menu.CheckMenuItem (uiID, MF_CHECKED | MF_BYCOMMAND);
		}
		else
		{
			if (pTab->m_hIcon != NULL)
			{
				XTabWnd::m_mapDocIcons.SetAt (uiID, pTab->m_hIcon);
			}
		}
	}

	if (m_Tabs.GetSize ())
	{
		m_btnMenu.m_hMenu = m_menu.GetSafeHmenu ();
	}

	return TRUE;
}

BOOL CTabWnd::OnCommand(WPARAM wParam, LPARAM /*lParam*/)
{
	UINT nID = LOWORD(wParam);

	if (nID == IDC_BTN_NEW)
	{
		AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_FILE_NEW_TAB);
		return TRUE;
	}
	else if (nID == IDC_BTN_MENU)
	{
		int iTab = n_idStart - m_btnMenu.m_nMenuResult;
		if (iTab >= 0 && iTab < GetTabsNum ())
		{
			ActivateMDI (iTab);
		}

		return TRUE;
	}
	else if (nID == IDC_BTN_SCROLL_PREV)
	{
		if (m_Active <= m_FirstVisible)
		{
			m_FirstVisible = max (0, m_FirstVisible - (int)m_TabRects.GetSize ());
		}

		ActivateMDI (m_FirstVisible);
	}
	else if (nID == IDC_BTN_SCROLL_NEXT)
	{
		int count = (int)m_TabRects.GetSize ();
		if ((m_FirstVisible + count - 1) <= m_Active)
		{
			m_FirstVisible = min (GetTabsNum () - count, m_FirstVisible + count);
		}

		ActivateMDI (m_FirstVisible + count - 1);
	}

	return FALSE;
}

int CTabWnd::FindTabInfoIndex (HWND hWnd)
{
	int index = -1;
	for (int i = 0; i < m_Tabs.GetSize (); i++)
	{
		if (m_Tabs[i]->m_hWnd == hWnd)
		{
			index = i;
			break;
		}
	}

	return index;
}

CTabInfo* CTabWnd::FindTabInfo (HWND hWnd)
{
	CTabInfo* pInfo = NULL;

	int index = FindTabInfoIndex (hWnd);
	if (index != -1)
	{
		pInfo = m_Tabs[index];
	}

	return pInfo;
}

int CTabWnd::GetTabIndexFromPoint (const CPoint& point)
{
	int index = -1;
	for (int i = 0; i < m_TabRects.GetSize (); i++)
	{
		if (m_TabRects[i].PtInRect (point))
		{
			index = i + m_FirstVisible;
			break;
		}
	}

	return index;
}

void CTabWnd::AddTab (HWND hWnd, BOOL bRecalc/* = TRUE*/)
{
	CTabInfo* pInfo = FindTabInfo (hWnd);

	if (pInfo == NULL)
	{
		pInfo = new CTabInfo (hWnd);
		m_Tabs.Add (pInfo);

		if (bRecalc)
		{
			RecalcLayout ();
			RedrawWindow ();
		}
	}
}

void CTabWnd::RemoveTab (HWND hWnd)
{
	int index = FindTabInfoIndex (hWnd);
	if (index != -1)
	{
		delete m_Tabs[index];
		m_Tabs.RemoveAt (index);

		if (index <= m_Active)
		{
			m_Active--;
		}

		RecalcLayout ();
		RedrawWindow ();
	}
}

void CTabWnd::SetTabText (HWND hWnd)
{
	CTabInfo* pInfo = FindTabInfo (hWnd);

	if (pInfo != NULL)
	{
		pInfo->CollectInfo ();

		RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
}

void CTabWnd::SetTabIcon (HWND hWnd)
{
	CTabInfo* pInfo = FindTabInfo (hWnd);

	if (pInfo != NULL)
	{
		pInfo->CollectInfo ();
		
		RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
}

void CTabWnd::SetActiveTab (HWND hWnd)
{
	BOOL bRecalc = FALSE;

	int index = FindTabInfoIndex (hWnd);
	if (index == -1)
	{
		index = (int)m_Tabs.GetSize ();
		AddTab (hWnd, FALSE);
		bRecalc = TRUE;
	}

	if (m_Active != index)
	{
		m_Active = index;

		if (bRecalc)
		{
			RecalcLayout ();
		}
		else
		{
			AdjustTabs ();
		}
	}

	RedrawWindow ();
}

LRESULT CTabWnd::OnBCGUpdateToolTips (WPARAM wParam, LPARAM /*lParam*/)
{
	UINT nTypes = (UINT) wParam;

	if ((nTypes & BCGP_TOOLTIP_TYPE_TAB) == 0)
	{
		return 0;
	}

	CBCGPTooltipManager::CreateToolTip (m_pToolTip, this,
		BCGP_TOOLTIP_TYPE_TAB);

	if (m_pToolTip->GetSafeHwnd () == NULL)
	{
		return 0;
	}

	CBCGPTooltipManager::CreateToolTip (m_pToolTipClose, this,
		BCGP_TOOLTIP_TYPE_TAB);

	if (m_pToolTip->GetSafeHwnd () == NULL)
	{
		return 0;
	}
	else
	{
		CRect rectDummy (0, 0, 0, 0);
		m_pToolTipClose->AddTool (this, LPSTR_TEXTCALLBACK, rectDummy, 1);
	}

	AdjustTabs ();

	return 0;
}

BOOL CTabWnd::OnNotify (WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CWnd::OnNotify (wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT (pNMHDR != NULL);

	if (pNMHDR->code == TTN_SHOW)
	{
		if (m_pToolTip->GetSafeHwnd () != NULL)
		{
			m_pToolTip->SetWindowPos (&wndTop, -1, -1, -1, -1,
				SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
		}
		
		if (m_pToolTipClose->GetSafeHwnd () != NULL && 
			pNMHDR->hwndFrom == m_pToolTipClose->GetSafeHwnd ())
		{
			m_pToolTipClose->SetWindowPos (&wndTop, -1, -1, -1, -1,
				SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
		}
	}

	return bRes;
}

BOOL CTabWnd::OnNeedTipText(UINT /*id*/, NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	LPNMTTDISPINFO	pTTDispInfo	= (LPNMTTDISPINFO) pNMHDR;
	ASSERT((pTTDispInfo->uFlags & TTF_IDISHWND) == 0);

	if (m_TabRects.GetSize () > 0)
	{
		if (m_pToolTipClose->GetSafeHwnd () != NULL &&
			pNMHDR->hwndFrom == m_pToolTipClose->GetSafeHwnd ())
		{
			pTTDispInfo->lpszText = _T("Close Tab (Ctrl+W)");
			return TRUE;
		}

		if (m_pToolTip->GetSafeHwnd () != NULL &&
			pNMHDR->hwndFrom == m_pToolTip->GetSafeHwnd ())
		{
			int nID = m_FirstVisible + (int)pTTDispInfo->hdr.idFrom - 1;

			if (0 <= nID && nID < m_Tabs.GetSize ())
			{
				pTTDispInfo->lpszText = const_cast<LPTSTR> ((LPCTSTR)m_Tabs[nID]->m_strText);
				return TRUE;
			}
		}	
	}

	return FALSE;
}

void CTabWnd::UpdateTabs (BOOL bRedraw)
{
	int count = GetTabsNum ();

	if (count > 0)
	{
		for (int i = 0; i < GetTabsNum (); i++)
		{
			m_Tabs[i]->CollectInfo ();
		}

		if (bRedraw)
		{
			Invalidate ();
		}
	}	
}
