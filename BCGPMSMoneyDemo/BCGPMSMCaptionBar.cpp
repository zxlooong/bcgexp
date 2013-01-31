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
// BCGPMSMCaptionBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMSMCaptionBar.h"
#include "BCGPMSMVisualManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCaptionBar

IMPLEMENT_DYNCREATE(CBCGPMSMCaptionBar, CBCGPControlBar)

CBCGPMSMCaptionBar::CBCGPMSMCaptionBar ()
	: CBCGPControlBar   ()
	, m_hIcon           (NULL)
	, m_szIcon          (0, 0)
	, m_bParentActive   (false)
	, m_bParentMaximize (false)
{
}

CBCGPMSMCaptionBar::~CBCGPMSMCaptionBar ()
{
}

BOOL CBCGPMSMCaptionBar::PreCreateWindow (CREATESTRUCT& cs)
{
	// in Win4, status bars do not have a border at all, since it is
	//  provided by the client area.
	if ((m_dwStyle & (CBRS_ALIGN_ANY | CBRS_BORDER_ANY)) == CBRS_TOP)
	{
		m_dwStyle &= ~(CBRS_BORDER_ANY | CBRS_BORDER_3D);
	}
	
	return CBCGPControlBar::PreCreateWindow(cs);
}

BOOL CBCGPMSMCaptionBar::Create (CWnd* pParentWnd, UINT nID)
{
	return CreateEx(pParentWnd, nID);
}

BOOL CBCGPMSMCaptionBar::CreateEx (CWnd* pParentWnd, UINT nID)
{
    ASSERT_VALID(pParentWnd);   // must have a parent

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | CBRS_TOP;

	// save the style
	SetBarAlignment (dwStyle & CBRS_ALL);

	// create the HWND
	CRect rect(0, 0, 0, 0);

	LPCTSTR lpszClass = AfxRegisterWndClass(CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_BTNFACE+1), NULL);

	m_dwBCGStyle = 0; // can't float, resize, close, slide
/*
	if (pParentWnd->GetStyle() & WS_THICKFRAME)
	{
		dwStyle |= SBARS_SIZEGRIP;
	}	
*/

	BOOL bSystemSmall = (pParentWnd->GetExStyle() & WS_EX_TOOLWINDOW) != 0;

	if (!CWnd::Create(lpszClass, NULL, dwStyle | WS_CLIPSIBLINGS, rect, pParentWnd, nID))
	{
		return FALSE;
	}

	if (pParentWnd->IsKindOf (RUNTIME_CLASS (CBCGPFrameWnd)))
	{
		((CBCGPFrameWnd*) pParentWnd)->AddControlBar (this);
	}
	else
	{
		ASSERT (FALSE);
		return FALSE;
	}

	HINSTANCE hInstance = AfxFindResourceHandle (MAKEINTRESOURCE (nID), RT_GROUP_ICON);

	if (hInstance != NULL)
	{
		CSize szIcon (::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON));

		HICON hIcon = (HICON)::LoadImage (hInstance, MAKEINTRESOURCE (nID), IMAGE_ICON, 
			szIcon.cx, szIcon.cy, LR_DEFAULTCOLOR);

		if (hIcon != NULL)
		{
			SetIcon (hIcon);
		}
	}

	CString strCaption;

	pParentWnd->GetWindowText (strCaption);

	if (strCaption.IsEmpty ())
	{
		strCaption.LoadString (nID);
	}

	if (!strCaption.IsEmpty ())
	{
		SetWindowText (strCaption);
	}

	NONCLIENTMETRICS ncm;
	ZeroMemory (&ncm, sizeof (NONCLIENTMETRICS));
	ncm.cbSize = sizeof (NONCLIENTMETRICS);

	globalData.GetNonClientMetrics (ncm);

	m_SystemHeight  = ::GetSystemMetrics (bSystemSmall ? SM_CYSMCAPTION : SM_CYCAPTION);
	m_CaptionHeight = m_SystemHeight;

	SetCaptionFont (bSystemSmall ? ncm.lfSmCaptionFont : ncm.lfCaptionFont);

	CRect rt (0, 0, bSystemSmall ? ncm.iSmCaptionWidth : ncm.iCaptionWidth, 
		            bSystemSmall ? ncm.iSmCaptionHeight : ncm.iCaptionHeight);


	CBCGPMSMVisualManager* pManager = DYNAMIC_DOWNCAST (CBCGPMSMVisualManager,
		CBCGPVisualManager::GetInstance ());

	if (pManager != NULL)
	{
		if (pManager->LoadBCGPMSMCaptionButtonsIcons (_T("IDB_BCGPMSM_CAPTION_BTNS")))
		{
			rt.right  = pManager->GetBCGPMSMCaptionButtonsSize ().cx;
			rt.bottom = pManager->GetBCGPMSMCaptionButtonsSize ().cx;
		};

		m_CaptionHeight = rt.bottom + 2;
	}


	m_BtnClose.Create (_T(""), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 
		               rt, this, SC_CLOSE);
	m_BtnClose.SetTooltip (_T("Close"));

	m_BtnMaximize.Create (_T(""), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 
		               rt, this, SC_MAXIMIZE);
	m_BtnMaximize.SetTooltip (_T("Maximize"));

	m_BtnMinimize.Create (_T(""), BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 
		               rt, this, SC_MINIMIZE);
	m_BtnMinimize.SetTooltip (_T("Minimize"));

	return TRUE;
}

void CBCGPMSMCaptionBar::SetCaptionHeight (int nHeight)
{
	if (m_CaptionHeight != nHeight)
	{
		m_CaptionHeight = nHeight;

		RecalcLayout ();
	}
}

CSize CBCGPMSMCaptionBar::CalcFixedLayout (BOOL, BOOL)
{
	ASSERT_VALID(this);

	// recalculate based on font height + icon height + borders
	TEXTMETRIC tm;
	{
		CClientDC dcScreen(NULL);
		HFONT hFont = GetCaptionFont ();

		HGDIOBJ hOldFont = dcScreen.SelectObject(hFont);
		VERIFY(dcScreen.GetTextMetrics(&tm));
		dcScreen.SelectObject(hOldFont);
	}

	int nHeight = max ( max (tm.tmHeight, m_szIcon.cy), GetCaptionHeight ());

	return CSize (32767, nHeight);// + CY_BORDER * 4 - rectSize.Height());
}

void CBCGPMSMCaptionBar::SetCaptionFont (const LOGFONT& lf)
{
	if (m_CaptionFont.GetSafeHandle () != NULL)
	{
		m_CaptionFont.DeleteObject ();
	}

	m_CaptionFont.CreateFontIndirect (&lf);
}

void CBCGPMSMCaptionBar::SetIcon (HICON hIcon)
{
	m_szIcon = CSize (0, 0);

	if (m_hIcon != NULL)
	{
		::DestroyIcon(m_hIcon);
	}

	m_hIcon = hIcon;

	if (m_hIcon != NULL)
	{
		ICONINFO ii;
		ZeroMemory (&ii, sizeof (ICONINFO));

		::GetIconInfo (m_hIcon, &ii);

		if (ii.hbmColor != NULL)
		{
			BITMAP bm;
			ZeroMemory (&bm, sizeof (BITMAP));

			if (::GetObject (ii.hbmColor, sizeof (BITMAP), &bm) != 0)
			{
				m_szIcon.cx = bm.bmWidth;
				m_szIcon.cy = bm.bmHeight;
			}
		}
	}
}

void CBCGPMSMCaptionBar::SetParentActive (BOOL bParentActive)
{
	if (m_bParentActive != bParentActive)
	{
		m_bParentActive = bParentActive;
		Invalidate ();
	}
}

void CBCGPMSMCaptionBar::SetParentMaximize (BOOL bParentMaximize)
{
	if (m_BtnMaximize.GetSafeHwnd () != NULL)
	{
		m_BtnMaximize.SetSysCommand (bParentMaximize ? SC_RESTORE : SC_MAXIMIZE);
		m_BtnMaximize.SetTooltip (bParentMaximize ? _T("Restore down") : _T("Maximize"));
	}

	if (m_bParentMaximize != bParentMaximize)
	{
		m_bParentMaximize = bParentMaximize;

		Invalidate ();
	}
}

COLORREF CBCGPMSMCaptionBar::GetCaptionTextColor () const
{
	return IsParentActive () ? globalData.clrCaptionText : globalData.clrInactiveCaptionText;
}

void CBCGPMSMCaptionBar::DoPaint (CDC* pDCPaint)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDCPaint);

	CRect rectClip;
	pDCPaint->GetClipBox (rectClip);

	CRect rect;
	GetClientRect(rect);

	CBCGPMemDC memDC (*pDCPaint, this);
	CDC* pDC = &memDC.GetDC ();

	CBCGPVisualManager::GetInstance ()->OnFillBarBackground (pDC, this,
		rect, rectClip);

	HGDIOBJ  hOldFont    = pDC->SelectObject (GetCaptionFont());

	int      nOldMode    = pDC->SetBkMode    (TRANSPARENT);
	COLORREF crTextColor = pDC->SetTextColor (GetCaptionTextColor());
	COLORREF crBkColor   = pDC->SetBkColor   (globalData.clrBtnFace);

	if (m_hIcon != NULL && m_szIcon != CSize (0, 0))
	{
		CRect rectIcon (0, 0, m_SystemHeight, rect.Height ());

		int x = max (0, (rectIcon.Width ()  - m_szIcon.cx) / 2);
		int y = max (0, (rectIcon.Height () - m_szIcon.cy) / 2);

		::DrawIconEx (pDC->GetSafeHdc (), x, y, m_hIcon, m_szIcon.cx, m_szIcon.cy,
					  0, NULL, DI_NORMAL);

		rect.left  += m_SystemHeight;

		CRect rt;
		m_BtnMinimize.GetWindowRect (rt);
		ScreenToClient (rt);

		rect.right = rt.left - 1;
	}

	if (!m_strCaption.IsEmpty ())
	{
		pDC->DrawText (m_strCaption, rect, DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER);
	}

	pDC->SetTextColor (crTextColor);
	pDC->SetBkColor   (crBkColor);
	pDC->SetBkMode    (nOldMode);

	pDC->SelectObject (hOldFont);
}

BEGIN_MESSAGE_MAP(CBCGPMSMCaptionBar, CBCGPControlBar)
	//{{AFX_MSG_MAP(CBCGPMSMCaptionBar)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMCaptionBar message handlers

LRESULT CBCGPMSMCaptionBar::OnSetText (WPARAM, LPARAM lParam)
{
	TRY
	{
		if (lParam == NULL)
		{
			// NULL lParam means set caption to nothing
			m_strCaption.Empty();
		}
		else
		{
			// non-NULL sets caption to that specified by lParam
			lstrcpy(m_strCaption.GetBufferSetLength((int)_tcslen((LPCTSTR)lParam)),
				(LPCTSTR)lParam);

		}

		Invalidate ();
	}
	CATCH_ALL(e)
	{
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

void CBCGPMSMCaptionBar::OnSize (UINT nType, int cx, int cy) 
{
	CBCGPControlBar::OnSize(nType, cx, cy);

	if (m_BtnClose.GetSafeHwnd () != NULL && m_BtnMaximize.GetSafeHwnd () != NULL &&
		m_BtnMinimize.GetSafeHwnd () != NULL)
	{
		int nHeight = cy;

		DWORD dwFlag = SWP_NOOWNERZORDER | SWP_NOZORDER;

		CRect rt;
		m_BtnClose.GetWindowRect (rt);
		rt.OffsetRect (-rt.TopLeft ());

		CSize szBtnSize (0, 0);

		CBCGPMSMVisualManager* pManager = DYNAMIC_DOWNCAST (CBCGPMSMVisualManager,
			CBCGPVisualManager::GetInstance ());

		if (pManager != NULL)
		{
			szBtnSize = pManager->GetBCGPMSMCaptionButtonsSize ();
		}

		if (szBtnSize == CSize (0, 0))
		{
			szBtnSize = rt.Size ();
		}

		if (szBtnSize.cy > nHeight)
		{
			rt.right   = szBtnSize.cy;
			rt.bottom  = szBtnSize.cy;
			rt.DeflateRect (1, 1);
		}
		else
		{
			rt.right   = szBtnSize.cx;
			rt.top     = (nHeight - szBtnSize.cy) / 2;
			rt.bottom  = rt.top + szBtnSize.cy;
		}

		rt.OffsetRect (cx - rt.Width (), 0);
		m_BtnClose.SetWindowPos(&wndTop, rt.left, rt.top, rt.Width(), rt.Height(), dwFlag);
		
		rt.OffsetRect(-rt.Width()-1, 0);
		m_BtnMaximize.SetWindowPos(&wndTop, rt.left, rt.top, rt.Width(), rt.Height(), dwFlag);

		rt.OffsetRect(-rt.Width()-1, 0);
		m_BtnMinimize.SetWindowPos(&wndTop, rt.left, rt.top, rt.Width(), rt.Height(), dwFlag);
	}
}

BOOL CBCGPMSMCaptionBar::PreTranslateMessage (MSG* pMsg) 
{
	if (!CBCGPControlBar::PreTranslateMessage (pMsg))
	{
		return FALSE;
	}

	CWnd* pParentWnd = GetParent ();

	if (pParentWnd != NULL)
	{
		CPoint pt;
		::GetCursorPos (&pt);

		UINT uiHit = HitTest (pt);

		if (uiHit == HTCAPTION || uiHit == HTSYSMENU)
		{
			UINT   message = 0;
			WPARAM wParam  = uiHit;
			LPARAM lParam  = MAKELPARAM (pt.x, pt.y);

			switch (pMsg->message)
			{
			case WM_LBUTTONDOWN:
				message = WM_NCLBUTTONDOWN;
				break;
			case WM_LBUTTONUP:
				message = WM_NCLBUTTONUP;
				break;
			case WM_LBUTTONDBLCLK:
				message = WM_NCLBUTTONDBLCLK;
				break;
			}

			if (message != 0)
			{
				if (message == WM_NCLBUTTONDOWN && uiHit == HTSYSMENU)
				{
					CRect rt;
					GetWindowRect (rt);

					ShowSysMenu (CPoint (rt.left, rt.bottom));
				}
				else
				{
					pParentWnd->SendMessage (message, wParam, lParam);
				}
			}
		}
	}

	return TRUE;
}

UINT CBCGPMSMCaptionBar::HitTest (const CPoint& pt) const
{
	UINT uiHit = HTNOWHERE;

	CPoint ptHit  (pt);
	ScreenToClient (&ptHit);

	CRect rtClient;
	GetClientRect (rtClient);

	if (rtClient.PtInRect (ptHit))
	{
		uiHit = HTCAPTION;

		CRect rt (0, 0, m_SystemHeight, GetCaptionHeight ());

		if (m_hIcon != NULL && m_szIcon != CSize (0, 0))
		{
			if (rt.PtInRect (ptHit))
			{
				uiHit = HTSYSMENU;
			}
		}

		if (uiHit == HTCAPTION)
		{
			const CWnd* pCapture = GetCapture ();

			const CBCGPMSMCaptionBarButton* pBtns[3] = 
				{
					&m_BtnClose, &m_BtnMaximize, &m_BtnMinimize
				};

			for (long i = 0; i < 3; i++)
			{
				const CBCGPMSMCaptionBarButton* pBtn = pBtns[i];

				if (pBtn != NULL && pBtn->GetSafeHwnd () != NULL && 
					pBtn->IsWindowVisible ())
				{
					pBtn->GetWindowRect (rt);
					if (rt.PtInRect (pt) || pCapture == pBtn)
					{
						switch (pBtn->GetSysCommand ())
						{
						case SC_CLOSE:
							uiHit = HTCLOSE;
							break;
						case SC_MINIMIZE:
							uiHit = HTMINBUTTON; // or HTREDUCE
							break;
						case SC_RESTORE:
						case SC_MAXIMIZE:
							uiHit = HTMAXBUTTON; // or HTZOOM
							break;
						case SC_CONTEXTHELP:
							uiHit = HTHELP;
							break;
						default:
							ASSERT (FALSE);
						}
						break;
					}
				}
			}
		}
	}

	return uiHit;
}

void CBCGPMSMCaptionBar::ShowSysMenu (const CPoint& point)
{
	CWnd* pParentWnd = GetParent ();

	if (pParentWnd != NULL)
	{
		CMenu* pMenu = pParentWnd->GetSystemMenu (FALSE);

		if (pMenu == NULL || pMenu->GetSafeHmenu () == NULL)
		{
			return;
		}

		pMenu->SetDefaultItem (SC_CLOSE);

		if (m_bParentMaximize)
		{
			pMenu->EnableMenuItem (SC_SIZE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem (SC_MOVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem (SC_MAXIMIZE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

			pMenu->EnableMenuItem (SC_RESTORE, MF_BYCOMMAND | MF_ENABLED);
		}
		else
		{
			pMenu->EnableMenuItem (SC_RESTORE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

			pMenu->EnableMenuItem (SC_SIZE, MF_BYCOMMAND | MF_ENABLED);
			pMenu->EnableMenuItem (SC_MOVE, MF_BYCOMMAND | MF_ENABLED);
			pMenu->EnableMenuItem (SC_MAXIMIZE, MF_BYCOMMAND | MF_ENABLED);
		}

		GetWorkspace ()->GetContextMenuManager ()->ShowPopupMenu
			(pMenu->GetSafeHmenu(), point.x, point.y, this, TRUE, TRUE, FALSE);
	}
}

void CBCGPMSMCaptionBar::OnContextMenu (CWnd* /*pWnd*/, CPoint point) 
{
	UINT uiHit = HitTest (point);

	if (uiHit == HTCAPTION || uiHit == HTSYSMENU)
	{
		ShowSysMenu (point);
	}
}

BOOL CBCGPMSMCaptionBar::OnCommand (WPARAM wParam, LPARAM lParam)
{
	UINT nID = LOWORD (wParam);

	if (SC_SIZE <= nID && nID <= SC_CONTEXTHELP)
	{
		OnSysCommand (nID, 0);
		return TRUE;
	}

	return CBCGPControlBar::OnCommand(wParam, lParam);
}

void CBCGPMSMCaptionBar::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CWnd* pParentWnd = GetParent ();

	if (pParentWnd != NULL)
	{
		pParentWnd->PostMessage (WM_SYSCOMMAND, nID, lParam);
	}
}
