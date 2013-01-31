// MPVisualManager.cpp: implementation of the CMPVisualManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPMediaPlayer.h"
#include "MPVisualManager.h"
#include "AddressBar.h"
#include "NavigationBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const BOOL c_bSysButtonsMin8 = FALSE;

IMPLEMENT_DYNCREATE(CMPVisualManager, CBCGPWinXPVisualManager)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMPVisualManager::CMPVisualManager()
{
	m_szNcBtnSize[0]    = CSize (0, 0);
	m_szNcBtnSize[1]    = CSize (0, 0);
}

CMPVisualManager::~CMPVisualManager()
{
}

BOOL CMPVisualManager::IsLargeNaviControl () const
{
	CWnd* pWnd = AfxGetMainWnd ();
	if (pWnd->GetSafeHwnd () != NULL)
	{
		CRect rtWindow;
		pWnd->GetWindowRect (rtWindow);

		return rtWindow.Width () > 479;
	}

	return FALSE;
}

void CMPVisualManager::CleanUp ()
{
	m_ctrlMainBorderCaption.CleanUp ();
	m_ctrlMainBorderCaptionB.CleanUp ();
	m_ctrlMainBorderAddressL.CleanUp ();
	m_ctrlMainBorderAddressR.CleanUp ();
	m_ctrlMainBorderL.CleanUp ();
	m_ctrlMainBorderR.CleanUp ();
	m_ctrlMainBorderNaviL[0].CleanUp ();
	m_ctrlMainBorderNaviL[1].CleanUp ();
	m_ctrlMainBorderNaviR[0].CleanUp ();
	m_ctrlMainBorderNaviR[1].CleanUp ();
	m_ctrlMainBorderNaviB[0].CleanUp ();
	m_ctrlMainBorderNaviB[1].CleanUp ();
	m_ctrlMainBorderNaviBCtrl.Clear ();

	m_SysBtnBack[0].Clear ();
	m_SysBtnBack[1].Clear ();
	m_SysBtnBack[2].Clear ();
	m_SysBtnBack[3].Clear ();
	m_SysBtnClose.Clear ();
	m_SysBtnRestore.Clear ();
	m_SysBtnMaximize.Clear ();
	m_SysBtnMinimize.Clear ();

	m_CaptionBtnClose.Clear ();

	m_AppCaptionFont.DeleteObject ();

	m_iconArrowDown.Clear ();

	m_BackAddress.CleanUp ();
	m_btnAddress.CleanUp ();
	m_btnAddressSep.Clear ();

	m_BackNavi[0].CleanUp ();
	m_BackNavi[1].CleanUp ();
	m_NaviControl[0].Clear ();
	m_NaviControl[1].Clear ();
	m_NaviControl[2].Clear ();
	m_NaviControl[3].Clear ();
	m_NaviProgressBack.CleanUp ();

	m_ActivateFlag.RemoveAll ();
}

void CMPVisualManager::OnUpdateSystemColors ()
{
	CleanUp ();

	CBCGPWinXPVisualManager::OnUpdateSystemColors ();

	if (globalData.bIsWindows9x)
	{
		return;
	}

	if (!globalData.bIsOSAlphaBlendingSupport ||
		globalData.IsHighContastMode () ||
		globalData.m_nBitsPerPixel <= 8)
	{
		return;
	}

	globalData.clrBarText = RGB (255, 255, 255);
	globalData.clrBarFace = RGB (0, 0, 0);

	globalData.brBarFace.DeleteObject ();
	globalData.brBarFace.CreateSolidBrush (globalData.clrBarFace);
	
	m_nMenuBorderSize = 1;

	m_clrAppCaptionActiveText        = RGB (255, 255, 255);
	m_clrAppCaptionInactiveText      = RGB (255, 255, 255);
	m_clrAppCaptionActiveTitleText   = RGB (255, 255, 255);
	m_clrAppCaptionInactiveTitleText = RGB (255, 255, 255);

	NONCLIENTMETRICS ncm;
	if (globalData.GetNonClientMetrics  (ncm))
	{
		ncm.lfCaptionFont.lfQuality = 5;
		m_AppCaptionFont.DeleteObject ();
		m_AppCaptionFont.CreateFontIndirect (&ncm.lfCaptionFont);
	}

	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_CAPTION"), CRect (0, 0, 35, 25), CRect (5, 20, 5, 1));
		m_ctrlMainBorderCaption.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_CAPTION_B"), CRect (0, 0, 21, 3), CRect (4, 1, 4, 1));
		m_ctrlMainBorderCaptionB.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_ADDRESS_L"), CRect (0, 0, 8, 36), CRect (2, 3, 2, 3));
		m_ctrlMainBorderAddressL.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_ADDRESS_R"), CRect (0, 0, 8, 36), CRect (2, 3, 2, 3));
		m_ctrlMainBorderAddressR.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_L"), CRect (0, 0, 8, 530), CRect (2, 1, 2, 1));
		m_ctrlMainBorderL.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_R"), CRect (0, 0, 8, 530), CRect (2, 1, 2, 1));
		m_ctrlMainBorderR.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI1_L"), CRect (0, 0, 8, 53), CRect (2, 36, 2, 1));
		m_ctrlMainBorderNaviL[0].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI1_R"), CRect (0, 0, 8, 53), CRect (2, 36, 2, 2));
		m_ctrlMainBorderNaviR[0].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI1_B"), CRect (0, 0, 17, 16), CRect (8, 2, 8, 14));
		m_ctrlMainBorderNaviB[0].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI2_L"), CRect (0, 0, 8, 53), CRect (2, 36, 2, 2));
		m_ctrlMainBorderNaviL[1].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI2_R"), CRect (0, 0, 8, 53), CRect (2, 36, 2, 2));
		m_ctrlMainBorderNaviR[1].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI2_B"), CRect (0, 0, 17, 16), CRect (8, 2, 8, 14));
		m_ctrlMainBorderNaviB[1].Create (params);
	}

	m_ctrlMainBorderNaviBCtrl.SetTransparentColor ((COLORREF)-1);
	m_ctrlMainBorderNaviBCtrl.SetImageSize (CSize (296, 15));
	m_ctrlMainBorderNaviBCtrl.LoadStr (_T("IDB_MP_BORDER_NAVI2_B_CTRL"));

	m_SysBtnBack[0].SetTransparentColor ((COLORREF)-1);
	m_SysBtnBack[0].SetImageSize (CSize (97, 20));
	m_SysBtnBack[0].LoadStr (_T("IDB_MP_BTN_SYS"));
	m_SysBtnBack[1].SetTransparentColor ((COLORREF)-1);
	m_SysBtnBack[1].SetImageSize (CSize (25, 18));
	m_SysBtnBack[1].LoadStr (_T("IDB_MP_BTN_SYS_1"));
	m_SysBtnBack[2].SetTransparentColor ((COLORREF)-1);
	m_SysBtnBack[2].SetImageSize (CSize (25, 18));
	m_SysBtnBack[2].LoadStr (_T("IDB_MP_BTN_SYS_2"));
	m_SysBtnBack[3].SetTransparentColor ((COLORREF)-1);
	m_SysBtnBack[3].SetImageSize (CSize (43, 18));
	m_SysBtnBack[3].LoadStr (_T("IDB_MP_BTN_SYS_3"));

	m_SysBtnClose.SetTransparentColor ((COLORREF)-1);
	m_SysBtnClose.SetImageSize (CSize (41, 20));
	m_SysBtnClose.LoadStr (_T("IDB_MP_ICON_CLOSE"));
	m_SysBtnRestore.SetTransparentColor ((COLORREF)-1);
	m_SysBtnRestore.SetImageSize (CSize (24, 20));
	m_SysBtnRestore.LoadStr (_T("IDB_MP_ICON_RESTORE"));
	m_SysBtnMaximize.SetTransparentColor ((COLORREF)-1);
	m_SysBtnMaximize.SetImageSize (CSize (24, 20));
	m_SysBtnMaximize.LoadStr (_T("IDB_MP_ICON_MAXIMIZE"));
	m_SysBtnMinimize.SetTransparentColor ((COLORREF)-1);
	m_SysBtnMinimize.SetImageSize (CSize (24, 20));
	m_SysBtnMinimize.LoadStr (_T("IDB_MP_ICON_MINIMIZE"));

	m_CaptionBtnClose.SetTransparentColor ((COLORREF)-1);
	m_CaptionBtnClose.SetImageSize (CSize (11, 11));
	m_CaptionBtnClose.LoadStr (_T("IDB_MP_CAPTION_BTN_CLOSE"));

	m_iconArrowDown.SetTransparentColor ((COLORREF)-1);
	m_iconArrowDown.SetImageSize (CSize (7, 7));
	m_iconArrowDown.LoadStr (_T("IDB_ICON_ARROW_DOWN"));

	{
		CBCGPControlRendererParams params (_T("IDB_BACK_ADDRESS"), CRect (0, 0, 9, 36), CRect (4, 16, 4, 18));
		m_BackAddress.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_BTN_ADDRESS"), CRect (0, 0, 66, 33), CRect (5, 14, 5, 2));
		m_btnAddress.Create (params);
	}
	m_btnAddressSep.SetTransparentColor ((COLORREF)-1);
	m_btnAddressSep.SetImageSize (CSize (2, 33));
	m_btnAddressSep.LoadStr (_T("IDB_BTN_ADDRESS_SEP"));

	{
		CBCGPControlRendererParams params (_T("IDB_BACK_NAVI1"), CRect (0, 0, 3, 69), CRect (1, 36, 1, 14));
		m_BackNavi[0].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_BACK_NAVI2"), CRect (0, 0, 9, 69), CRect (4, 36, 4, 14));
		m_BackNavi[1].Create (params);
	}
	m_NaviControl[0].SetTransparentColor ((COLORREF)-1);
	m_NaviControl[0].SetImageSize (CSize (268, 69));
	m_NaviControl[0].LoadStr (_T("IDB_BACK_NAVI1_CTRL"));
	m_NaviControl[1].SetTransparentColor ((COLORREF)-1);
	m_NaviControl[1].SetImageSize (CSize (422, 69));
	m_NaviControl[1].LoadStr (_T("IDB_BACK_NAVI2_CTRL"));
	m_NaviControl[2].SetTransparentColor ((COLORREF)-1);
	m_NaviControl[2].SetImageSize (CSize (268, 69));
	m_NaviControl[2].LoadStr (_T("IDB_BACK_NAVI1_CTRL_A"));
	m_NaviControl[3].SetTransparentColor ((COLORREF)-1);
	m_NaviControl[3].SetImageSize (CSize (422, 69));
	m_NaviControl[3].LoadStr (_T("IDB_BACK_NAVI2_CTRL_A"));
	{
		CBCGPControlRendererParams params (_T("IDB_NAVI_PROGRESS_BACK"), CRect (0, 0, 21, 9), CRect (10, 4, 10, 4));
		m_NaviProgressBack.Create (params);
	}

	m_szNcBtnSize[0] = CSize (::GetSystemMetrics (SM_CXSIZE),
							  ::GetSystemMetrics (SM_CYSIZE));
	m_szNcBtnSize[1] = CSize (::GetSystemMetrics (SM_CXSMSIZE),
							  ::GetSystemMetrics (SM_CYSMSIZE));
}

BOOL CMPVisualManager::OnNcActivate (CWnd* pWnd, BOOL bActive)
{
	ASSERT_VALID (pWnd);

	if (pWnd->GetSafeHwnd () == NULL)
	{
		return FALSE;
	}

	if (globalData.DwmIsCompositionEnabled ())
	{
		return FALSE;
	}

	// stay active if WF_STAYACTIVE bit is on
	if (pWnd->m_nFlags & WF_STAYACTIVE)
	{
		bActive = TRUE;
	}

	// but do not stay active if the window is disabled
	if (!pWnd->IsWindowEnabled())
	{
		bActive = FALSE;
	}

	m_ActivateFlag[pWnd->GetSafeHwnd ()] = bActive;
	pWnd->SendMessage (WM_NCPAINT, 0, 0);

	return TRUE;
}

BOOL CMPVisualManager::IsWindowActive (CWnd* pWnd) const
{
	BOOL bActive = FALSE;

	HWND hWnd = pWnd->GetSafeHwnd ();

	if (hWnd != NULL)
	{
		if(!m_ActivateFlag.Lookup (pWnd->GetSafeHwnd (), bActive))
		{
			//ASSERT(FALSE);
			bActive = TRUE;
		}
	}

	return bActive;
}

CSize CMPVisualManager::GetSystemBorders () const
{
	CSize size (::GetSystemMetrics (SM_CYSIZEFRAME), 
			    ::GetSystemMetrics (SM_CXSIZEFRAME));

	return size;
}

void CMPVisualManager::DrawNcBtn (CDC* pDC, const CRect& rect, UINT nButton, 
										BCGBUTTON_STATE state, BOOL /*bSmall*/, 
										BOOL bActive, BOOL /*bMDI*/)
{
	ASSERT_VALID (pDC);

	CBCGPToolBarImages* pImage = NULL;

	int nIndex = 1;

	if (nButton == SC_CLOSE)
	{
		pImage = &m_SysBtnClose;
		nIndex = 3;
	}
	else if (nButton == SC_MINIMIZE)
	{
		pImage = &m_SysBtnMinimize;
		nIndex = 1;
	}
	else if (nButton == SC_MAXIMIZE)
	{
		pImage = &m_SysBtnMaximize;
		nIndex = 2;
	}
	else if (nButton == SC_RESTORE)
	{
		pImage = &m_SysBtnRestore;
		nIndex = 2;
	}
	else
	{
		return;
	}

	if (bActive)
	{
		if (state != ButtonsIsRegular)
		{
			m_SysBtnBack[nIndex].DrawEx (pDC, rect, state == ButtonsIsHighlighted ? 0 : 1,
				CBCGPToolBarImages::ImageAlignHorzLeft, CBCGPToolBarImages::ImageAlignVertTop);
		}
	}

	pImage->DrawEx (pDC, rect, 0, 
		CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertTop);
}

void CMPVisualManager::DrawNcText (CDC* pDC, CRect& rect, 
										 const CString& strTitle, 
										 const CString& strDocument, 
										 BOOL bPrefix, BOOL bActive, BOOL bIsRTL, 
										 BOOL bTextCenter,
										 BOOL bGlass, int nGlassGlowSize, 
										 COLORREF clrGlassText)
{
	if ((strTitle.IsEmpty () && strDocument.IsEmpty ()) || 
		rect.right <= rect.left)
	{
		return;
	}

	ASSERT_VALID (pDC);

	int nOldMode = pDC->SetBkMode (TRANSPARENT);
	COLORREF clrOldText = pDC->GetTextColor ();

	DWORD dwTextStyle = DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER |
		(bIsRTL ? DT_RTLREADING : 0);

	if (strDocument.IsEmpty ())
	{
		COLORREF clrText = bActive 
			? m_clrAppCaptionActiveTitleText
			: m_clrAppCaptionInactiveTitleText;

		int widthFull = rect.Width ();
		int width = pDC->GetTextExtent (strTitle).cx;

		if (bTextCenter && width < widthFull)
		{
			rect.left += (widthFull - width) / 2;
		}

		rect.right = min (rect.left + width, rect.right);

		if (rect.right > rect.left)
		{
			if (bGlass)
			{
				DrawTextOnGlass (pDC, strTitle, rect, dwTextStyle, nGlassGlowSize, clrGlassText);
			}
			else
			{
				pDC->SetTextColor (clrText);
				pDC->DrawText (strTitle, rect, dwTextStyle);
			}
		}
	}
	else
	{
		const CString& str1 = bPrefix ? strDocument : strTitle;
		const CString& str2 = bPrefix ? strTitle : strDocument;

		COLORREF clrText1 = bActive 
			? m_clrAppCaptionActiveText
			: m_clrAppCaptionInactiveText;
		COLORREF clrText2 = bActive 
			? m_clrAppCaptionActiveTitleText
			: m_clrAppCaptionInactiveTitleText;

		if (!bPrefix)
		{
			COLORREF clr = clrText1;
			clrText1 = clrText2;
			clrText2 = clr;
		}

		int widthFull = rect.Width ();
		CSize sz1 = pDC->GetTextExtent (str1);
		CSize sz2 = pDC->GetTextExtent (str2);
		int width = sz1.cx + sz2.cx;
		int left = rect.left;

		if (bTextCenter && width < widthFull)
		{
			rect.left += (widthFull - width) / 2;
		}

		rect.right = min (rect.left + width, rect.right);

		if (bIsRTL)
		{
			if (width <= rect.Width ())
			{
				rect.left += sz2.cx;
			}
			else
			{
				if (sz1.cx < rect.Width ())
				{
					rect.left += max (0, sz2.cx + (rect.Width () - width));
				}
			}
		}

		if (bGlass)
		{
			DrawTextOnGlass (pDC, str1, rect, dwTextStyle, nGlassGlowSize, clrGlassText);
		}
		else
		{
			pDC->SetTextColor (clrText1);
			pDC->DrawText (str1, rect, dwTextStyle);
		}

		if (bIsRTL)
		{
			if (width <= (rect.right - left))
			{
				rect.right = rect.left;
				rect.left  = rect.right - sz2.cx;
			}
			else
			{
				rect.left = left;
				rect.right -= sz1.cx;
			}
		}
		else
		{
			rect.left += sz1.cx;
		}

		if (rect.right > rect.left)
		{
			if (bGlass)
			{
				DrawTextOnGlass (pDC, str2, rect, dwTextStyle, nGlassGlowSize, clrGlassText);
			}
			else
			{
				pDC->SetTextColor (clrText2);
				pDC->DrawText (str2, rect, dwTextStyle);
			}
		}
	}

	pDC->SetBkMode    (nOldMode);
	pDC->SetTextColor (clrOldText);
}

void CMPVisualManager::DrawNcCaption (CDC* pDC, CRect rectCaption, 
											   DWORD dwStyle, DWORD dwStyleEx,
											   const CString& strTitle, const CString& strDocument,
											   HICON hIcon, BOOL bPrefix, BOOL bActive, 
											   BOOL bTextCenter,
											   const CObList& lstSysButtons)
{
	const BOOL bIsRTL           = (dwStyleEx & WS_EX_LAYOUTRTL) == WS_EX_LAYOUTRTL;
	const int nSysCaptionHeight = ::GetSystemMetrics (SM_CYCAPTION);
	CSize szSysBorder (GetSystemBorders ());

    CDC memDC;
    memDC.CreateCompatibleDC (pDC);
    CBitmap memBmp;
    memBmp.CreateCompatibleBitmap (pDC, rectCaption.Width (), rectCaption.Height ());
    CBitmap* pBmpOld = memDC.SelectObject (&memBmp);
	memDC.BitBlt (0, 0, rectCaption.Width (), rectCaption.Height (), pDC, 0, 0, SRCCOPY);

	BOOL bMaximized = (dwStyle & WS_MAXIMIZE) == WS_MAXIMIZE;

	CRect rectBorderCaption (rectCaption);
	if (bMaximized)
	{
		rectBorderCaption.OffsetRect (-rectBorderCaption.TopLeft ());
		rectBorderCaption.bottom -= szSysBorder.cy;
	}
	m_ctrlMainBorderCaption.Draw (&memDC, rectBorderCaption, 0);

	CRect rectSysBtn (rectCaption);
	if (bMaximized)
	{
		rectSysBtn.top = 0;
		rectSysBtn.OffsetRect (szSysBorder.cx, 0);
	}

	int nDelta = szSysBorder.cx;
	if (c_bSysButtonsMin8 && nDelta < 8)
	{
		nDelta = 8;
	}
	rectSysBtn.right -= (nDelta - 3);
	rectSysBtn.left   = rectSysBtn.right - m_SysBtnBack[0].GetImageSize ().cx;
	m_SysBtnBack[0].DrawEx (&memDC, rectSysBtn, 0,
				CBCGPToolBarImages::ImageAlignHorzLeft, CBCGPToolBarImages::ImageAlignVertTop);

	CRect rectCaptionB (rectCaption);
	rectCaptionB.DeflateRect ((bMaximized ? 0 : szSysBorder.cx) - 1, 0);
	rectCaptionB.top = rectCaptionB.bottom - m_ctrlMainBorderCaptionB.GetParams ().m_rectImage.Height ();
	m_ctrlMainBorderCaptionB.Draw (&memDC, rectCaptionB, 0);

	CRect rect (rectCaption);
	rect.DeflateRect (szSysBorder.cx, szSysBorder.cy, szSysBorder.cx, 0);

	rect.top = rect.bottom - nSysCaptionHeight - 1;

	// Draw icon:
	if (hIcon != NULL)
	{
		CSize szIcon (::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON));

		long x = rect.left + (bMaximized ? szSysBorder.cx : 0) + 2;
		long y = rect.top + max (0, (nSysCaptionHeight - szIcon.cy) / 2);

		::DrawIconEx (memDC.GetSafeHdc (), x, y, hIcon, szIcon.cx, szIcon.cy,
			0, NULL, DI_NORMAL);

		rect.left = x + szIcon.cx + (bMaximized ? szSysBorder.cx : 4);
	}

	// Draw system buttons:
	int xButtonsRight = rect.right;

	for (POSITION pos = lstSysButtons.GetHeadPosition (); pos != NULL;)
	{
		CBCGPFrameCaptionButton* pButton = (CBCGPFrameCaptionButton*)
			lstSysButtons.GetNext (pos);
		ASSERT_VALID (pButton);

		BCGBUTTON_STATE state = ButtonsIsRegular;

		if (pButton->m_bPushed && pButton->m_bFocused)
		{
			state = ButtonsIsPressed;
		}
		else if (pButton->m_bFocused)
		{
			state = ButtonsIsHighlighted;
		}

		UINT uiHit = pButton->GetHit ();
		UINT nButton = 0;

		switch (uiHit)
		{
		case HTCLOSE_BCG:
			nButton = SC_CLOSE;
			break;

		case HTMAXBUTTON_BCG:
			nButton = 
				(dwStyle & WS_MAXIMIZE) == WS_MAXIMIZE ? SC_RESTORE : SC_MAXIMIZE;
			break;

		case HTMINBUTTON_BCG:
			nButton = 
				(dwStyle & WS_MINIMIZE) == WS_MINIMIZE ? SC_RESTORE : SC_MINIMIZE;
			break;
		}

		CRect rectBtn (pButton->GetRect ());
		if (bMaximized)
		{
			rectBtn.OffsetRect (szSysBorder.cx, szSysBorder.cy);
		}

		DrawNcBtn (&memDC, rectBtn, nButton, state, FALSE, bActive, FALSE);

		xButtonsRight = min (xButtonsRight, pButton->GetRect ().left);
	}

	// Draw text:
	if ((!strTitle.IsEmpty () || !strDocument.IsEmpty ()) && 
		rect.left < rect.right)
	{
		CFont* pOldFont = (CFont*)memDC.SelectObject (&m_AppCaptionFont);

		CRect rectText = rect;
		rectText.right = xButtonsRight - 1;

		DrawNcText (&memDC, rectText, strTitle, strDocument, bPrefix, bActive, bIsRTL, bTextCenter);

		memDC.SelectObject (pOldFont);
	}

    pDC->BitBlt (rectCaption.left, rectCaption.top, rectCaption.Width (), rectCaption.Height (),
        &memDC, 0, 0, SRCCOPY);

    memDC.SelectObject (pBmpOld);
}

BOOL CMPVisualManager::OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw)
{
	if (!CanDrawImage ())
	{
		return CBCGPWinXPVisualManager::OnNcPaint (pWnd, lstSysButtons, rectRedraw);
	}

	ASSERT_VALID (pWnd);

	if (pWnd->GetSafeHwnd () == NULL)
	{
		return FALSE;
	}

	CWindowDC dc (pWnd);

	if (dc.GetSafeHdc () != NULL)
	{
		CRgn rgn;
		if (!rectRedraw.IsRectEmpty ())
		{
			rgn.CreateRectRgnIndirect (rectRedraw);
			dc.SelectClipRgn (&rgn);
		}

		CRect rtWindow;
		pWnd->GetWindowRect (rtWindow);
		pWnd->ScreenToClient (rtWindow);

		CRect rtClient;
		pWnd->GetClientRect (rtClient);

		rtClient.OffsetRect (-rtWindow.TopLeft ());
		dc.ExcludeClipRect (rtClient);

		rtWindow.OffsetRect (-rtWindow.TopLeft ());

        BOOL bActive = IsWindowActive (pWnd);

		CRect rectCaption (rtWindow);
		CSize szSysBorder (GetSystemBorders ());

		rectCaption.bottom = rectCaption.top + szSysBorder.cy;

		const DWORD dwStyle = pWnd->GetStyle ();
		BOOL bMaximized = (dwStyle & WS_MAXIMIZE) == WS_MAXIMIZE;

		const int nSysCaptionHeight = ::GetSystemMetrics (SM_CYCAPTION);
		rectCaption.bottom += nSysCaptionHeight;

		const DWORD dwStyleEx = pWnd->GetExStyle ();

		BOOL bDestroyIcon = FALSE;
		HICON hIcon = globalUtils.GetWndIcon (pWnd, &bDestroyIcon);

		CString strText;
		pWnd->GetWindowText (strText);

		CString strTitle (strText);
		CString strDocument;

		BOOL bPrefix = FALSE;
		if ((dwStyle & FWS_ADDTOTITLE) == FWS_ADDTOTITLE)
		{
			bPrefix = (dwStyle & FWS_PREFIXTITLE) == FWS_PREFIXTITLE;
			CFrameWnd* pFrameWnd = DYNAMIC_DOWNCAST(CFrameWnd, pWnd);

			if (pFrameWnd != NULL)
			{
				strTitle = pFrameWnd->GetTitle();

				if (!strTitle.IsEmpty ())
				{
					if (strText.GetLength () >= strTitle.GetLength ())
					{
						if (bPrefix)
						{
							int pos = strText.Find (strTitle, strText.GetLength () - strTitle.GetLength ());
							if (pos != -1)
							{
								strTitle = strText.Right (strTitle.GetLength () + 3);
								strDocument = strText.Left (strText.GetLength () - strTitle.GetLength ());
							}
						}
						else
						{
							int pos = strText.Find (strTitle);
							if (pos != -1)
							{
								strTitle = strText.Left (strTitle.GetLength () + 3);
								strDocument = strText.Right (strText.GetLength () - strTitle.GetLength ());
							}	
						}
					}
				}
				else
				{
					strDocument = strText;
				}
			}
		}

		if (bMaximized)
		{
			rectCaption.InflateRect (szSysBorder.cx, szSysBorder.cy, szSysBorder.cx, 0);
		}

		DrawNcCaption (&dc, rectCaption, dwStyle, dwStyleEx, 
						strTitle, strDocument, hIcon, bPrefix, bActive, FALSE,
						lstSysButtons);

		if (bDestroyIcon)
		{
			::DestroyIcon (hIcon);
		}

		if (bMaximized)
		{
			return TRUE;
		}

		rtWindow.top = rectCaption.bottom;

		dc.ExcludeClipRect (rectCaption);

		int indexBorder = 0;
		int indexNavi   = IsLargeNaviControl () ? 1 : 0;

		CRect rtPart (rtWindow);
		rtPart.right  = rtPart.left + szSysBorder.cx;
		rtPart.bottom = rtPart.top + 
			m_ctrlMainBorderAddressL.GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderAddressL.Draw (&dc, rtPart, indexBorder);
		rtPart.top = rtPart.bottom;
		rtPart.bottom = rtWindow.bottom - 
			(m_ctrlMainBorderNaviL[indexNavi].GetParams ().m_rectImage.Height () + 
			 m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ());
		m_ctrlMainBorderL.Draw (&dc, rtPart, indexBorder);
		rtPart.top = rtPart.bottom;
		rtPart.bottom = rtWindow.bottom - m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderNaviL[indexNavi].Draw (&dc, rtPart, indexBorder);

		rtPart = rtWindow;
		rtPart.left   = rtPart.right - szSysBorder.cx;
		rtPart.bottom = rtPart.top + 
			m_ctrlMainBorderAddressR.GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderAddressR.Draw (&dc, rtPart, indexBorder);
		rtPart.top = rtPart.bottom;
		rtPart.bottom = rtWindow.bottom - 
			(m_ctrlMainBorderNaviR[indexNavi].GetParams ().m_rectImage.Height () + 
			 m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ());
		m_ctrlMainBorderR.Draw (&dc, rtPart, indexBorder);
		rtPart.top = rtPart.bottom;
		rtPart.bottom = rtWindow.bottom - m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderNaviR[indexNavi].Draw (&dc, rtPart, indexBorder);

		rtPart = rtWindow;
		rtPart.top = rtPart.bottom - m_ctrlMainBorderNaviB[indexNavi].GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderNaviB[indexNavi].Draw (&dc, rtPart, indexBorder);

		if (indexNavi == 1)
		{
			m_ctrlMainBorderNaviBCtrl.DrawEx (&dc, rtPart, 0, CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertBottom);
		}

		dc.SelectClipRgn (NULL);

		return TRUE;
	}

	return CBCGPWinXPVisualManager::OnNcPaint (pWnd, lstSysButtons, rectRedraw);
}

BOOL CMPVisualManager::OnSetWindowRegion (CWnd* pWnd, CSize sizeWindow)
{
	ASSERT_VALID (pWnd);

	if (pWnd->GetSafeHwnd () == NULL)
	{
		return FALSE;
	}

	if (!CanDrawImage ())
	{
		return FALSE;
	}

	if (globalData.DwmIsCompositionEnabled ())
	{
		return FALSE;
	}

    CSize sz (0, 0);

	if (DYNAMIC_DOWNCAST (CBCGPFrameWnd, pWnd) != NULL)
	{
		if (pWnd->IsZoomed ())
		{
			pWnd->SetWindowRgn (NULL, TRUE);
			return TRUE;
		}

		sz  = CSize (9, 9);
	}

	if (sz != CSize (0, 0))
	{
        CRgn rgn;
		BOOL bCreated = FALSE;

		bCreated = rgn.CreateRoundRectRgn (0, 0, sizeWindow.cx + 1, sizeWindow.cy + 1, sz.cx, sz.cy);

		if (bCreated)
		{
			if (pWnd->IsKindOf (RUNTIME_CLASS (CMDIChildWnd)))
			{
				CRgn rgnWinodw;
				rgnWinodw.CreateRectRgn (0, sz.cy, sizeWindow.cx, sizeWindow.cy);

				rgn.CombineRgn (&rgn, &rgnWinodw, RGN_OR);
			}

			pWnd->SetWindowRgn ((HRGN)rgn.Detach (), TRUE);
			return TRUE;
		}
	}

	return FALSE;
}

void CMPVisualManager::OnUpdateCaptionButtons (CRect rectCaption, CObList& lstSysButtons, CWnd* pWnd)
{
	ASSERT_VALID (pWnd);

	if (!CanDrawImage ())
	{
		return;
	}

	CSize szSysBorder (GetSystemBorders ());

	int nIndex = 3;

	int nDelta = szSysBorder.cx;
	if (c_bSysButtonsMin8 && nDelta < 8)
	{
		nDelta = 8;
	}
	int x = rectCaption.right + szSysBorder.cx - (nDelta - 1);

	rectCaption.top -= szSysBorder.cy;

	for (POSITION pos = lstSysButtons.GetHeadPosition (); pos != NULL;)
	{
		CSize sizeButton (m_SysBtnBack[nIndex--].GetImageSize ());
		x -= sizeButton.cx;
		
		CBCGPFrameCaptionButton* pButton = (CBCGPFrameCaptionButton*)
			lstSysButtons.GetNext (pos);
		ASSERT_VALID (pButton);

		pButton->SetRect (CRect (CPoint (x, rectCaption.top), sizeButton));
	}

	return;
}

void CMPVisualManager::OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL bNCArea)
{
	if (CanDrawImage ())
	{
		ASSERT_VALID(pDC);
		ASSERT_VALID(pBar);

		if (DYNAMIC_DOWNCAST (CAddressBar, pBar) != NULL)
		{
			if (!bNCArea)
			{
				CRect rectBorders (GetAddressBarBorders ());
				rectClient.InflateRect (rectBorders.left, rectBorders.top, rectBorders.right, rectBorders.bottom);
			}
			m_BackAddress.Draw (pDC, rectClient, globalData.DwmIsCompositionEnabled () ? 1 : 0);
			return;
		}
		else if (DYNAMIC_DOWNCAST (CNavigationBar, pBar) != NULL)
		{
			if (!bNCArea)
			{
				CRect rectBorders (GetNaviBarBorders ());
				rectClient.InflateRect (rectBorders.left, rectBorders.top, rectBorders.right, rectBorders.bottom);
			}

			if (!globalData.DwmIsCompositionEnabled ())
			{
				rectClient.bottom += GetSystemBorders ().cy;
				GetNaviBarBackImage ().Draw (pDC, rectClient, 0);
			}

			GetNaviBarControlImage ().DrawEx (pDC, rectClient, 0, 
				CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertTop);

			rectClient.top += 2;
			rectClient.bottom = rectClient.top + m_NaviProgressBack.GetParams ().m_rectImage.Height ();
			m_NaviProgressBack.Draw (pDC, rectClient, 0);
			return;
		}
		else if (DYNAMIC_DOWNCAST (CBCGPDialogBar, pBar) != NULL)
		{
			pDC->FillRect (rectClient, &globalData.brBarFace);
			return;
		}
	}

	CBCGPWinXPVisualManager::OnFillBarBackground (pDC, pBar, rectClient, rectClip, bNCArea);
}

COLORREF CMPVisualManager::OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
			BOOL bActive, CRect rectCaption, CRect rectButtons)
{
	if (!CanDrawImage ())
	{
		return CBCGPWinXPVisualManager::OnDrawControlBarCaption (pDC, pBar, 
			bActive, rectCaption, rectButtons);
	}

	ASSERT_VALID (pDC);

	::FillRect (pDC->GetSafeHdc (), rectCaption, (HBRUSH)::GetStockObject (BLACK_BRUSH));

    // get the text color
	return bActive ? m_clrAppCaptionActiveText : m_clrAppCaptionInactiveText;
}

void CMPVisualManager::OnDrawCaptionButton (
						CDC* pDC, CBCGPCaptionButton* pButton, BOOL bActive,
						BOOL bHorz, BOOL bMaximized, BOOL bDisabled, 
						int nImageID/* = -1*/)
{
	if (!CanDrawImage () || pButton->IsMiniFrameButton ())
	{
		CBCGPWinXPVisualManager::OnDrawCaptionButton (pDC, pButton, 
			bActive, bHorz, bMaximized, bDisabled, nImageID);
		return;
	}

	if (bDisabled)
	{
		return;
	}

	ASSERT_VALID (pDC);
    CRect rc = pButton->GetRect ();

	BOOL bPushed = pButton->m_bPushed;
	BOOL bFocused = pButton->m_bFocused || pButton->m_bDroppedDown;

	int nIndex = 0;
	if (bPushed && bFocused)
	{
		nIndex = 2;
	}
	else if (bFocused)
	{
		nIndex = 1;
	}

	m_CaptionBtnClose.DrawEx (pDC, rc, nIndex, 
		CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);
}
