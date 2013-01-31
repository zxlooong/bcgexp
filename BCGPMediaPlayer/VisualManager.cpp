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
// VisualManager.cpp: implementation of the CVisualManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPMediaPlayer.h"
#include "VisualManager.h"
#include "ExplorerBar.h"
#include "NavigationBar.h"
#include "ColorChooserBar.h"
#include "EqualizerBar.h"
#include "BCGPAutoHideDockBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define UPDATE_COLOR(clr, dblHue, dblSaturation) \
{ \
	double H, L, S; \
	CBCGPDrawManager::RGBtoHSL (clr, &H, &S, &L); \
	H = H * 360.0 + dblHue; \
	H = H - ((int)(H / 360)) * 360; \
	S = max (0.0, min (S + dblSaturation, 1.0)); \
	clr = CBCGPDrawManager::HLStoRGB_TWO (H, L, S); \
} \

IMPLEMENT_DYNCREATE(CVisualManager, CBCGPWinXPVisualManager)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVisualManager::CVisualManager()
{
	m_szNcBtnSize[0]    = CSize (0, 0);
	m_szNcBtnSize[1]    = CSize (0, 0);
	m_bUpdateColors		= FALSE;

	m_dblHue = theApp.GetInt (_T("ColorChooserH"), 0) / 1000.0;
	m_dblSaturation = theApp.GetInt (_T("ColorChooserS"), 0) / 1000.0;

	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderCaption.GetImages (), &m_ctrlMainBorderCaption.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderCaptionB.GetImages (), &m_ctrlMainBorderCaptionB.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderExplorerL.GetImages (), &m_ctrlMainBorderExplorerL.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderExplorerR.GetImages (), &m_ctrlMainBorderExplorerR.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderL.GetImages (), &m_ctrlMainBorderL.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderR.GetImages (), &m_ctrlMainBorderR.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderNaviL[0].GetImages (), &m_ctrlMainBorderNaviL[0].GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderNaviR[0].GetImages (), &m_ctrlMainBorderNaviR[0].GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderNaviB[0].GetImages (), &m_ctrlMainBorderNaviB[0].GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderNaviL[1].GetImages (), &m_ctrlMainBorderNaviL[1].GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderNaviR[1].GetImages (), &m_ctrlMainBorderNaviR[1].GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderNaviB[1].GetImages (), &m_ctrlMainBorderNaviB[1].GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMainBorderNaviBCtrl, &m_ctrlMainBorderNaviBCtrl));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMiniBorderCaption.GetImages (), &m_ctrlMiniBorderCaption.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMiniBorderCaptionB.GetImages (), &m_ctrlMiniBorderCaptionB.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_ctrlBaseMiniBorder.GetImages (), &m_ctrlMiniBorder.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_BaseSysBtnBack, &m_SysBtnBack[0]));
	m_arLinkImages.Add (XLinkImages (&m_backBaseExplorer.GetImages (), &m_backExplorer.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_btnBaseExplorer.GetImages (), &m_btnExplorer.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_btnBaseExplorerSep, &m_btnExplorerSep));
	m_arLinkImages.Add (XLinkImages (&m_btnBaseExplorerLogo.GetImages (), &m_btnExplorerLogo.GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_backBaseNavi[0].GetImages (), &m_backNavi[0].GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_backBaseNavi[1].GetImages (), &m_backNavi[1].GetImages ()));
	m_arLinkImages.Add (XLinkImages (&m_BaseNaviControl[0], &m_NaviControl[0]));
	m_arLinkImages.Add (XLinkImages (&m_BaseNaviControl[1], &m_NaviControl[1]));

	LoadImages ();
}

CVisualManager::~CVisualManager()
{
}

BOOL CVisualManager::IsLargeNaviControl () const
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

void CVisualManager::LoadBaseImages ()
{
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_CAPTION"), CRect (0, 0, 35, 25), CRect (5, 20, 5, 1));
		m_ctrlBaseMainBorderCaption.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_CAPTION_B"), CRect (0, 0, 21, 3), CRect (4, 1, 4, 1));
		m_ctrlBaseMainBorderCaptionB.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_EXPLORER_L"), CRect (0, 0, 8, 36), CRect (2, 3, 2, 3));
		m_ctrlBaseMainBorderExplorerL.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_EXPLORER_R"), CRect (0, 0, 8, 36), CRect (2, 3, 2, 3));
		m_ctrlBaseMainBorderExplorerR.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_L"), CRect (0, 0, 8, 530), CRect (2, 1, 2, 1));
		m_ctrlBaseMainBorderL.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_R"), CRect (0, 0, 8, 530), CRect (2, 1, 2, 1));
		m_ctrlBaseMainBorderR.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI1_L"), CRect (0, 0, 8, 53), CRect (2, 36, 2, 1));
		m_ctrlBaseMainBorderNaviL[0].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI1_R"), CRect (0, 0, 8, 53), CRect (2, 36, 2, 2));
		m_ctrlBaseMainBorderNaviR[0].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI1_B"), CRect (0, 0, 17, 16), CRect (8, 2, 8, 14));
		m_ctrlBaseMainBorderNaviB[0].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI2_L"), CRect (0, 0, 8, 53), CRect (2, 36, 2, 2));
		m_ctrlBaseMainBorderNaviL[1].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI2_R"), CRect (0, 0, 8, 53), CRect (2, 36, 2, 2));
		m_ctrlBaseMainBorderNaviR[1].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_NAVI2_B"), CRect (0, 0, 17, 16), CRect (8, 2, 8, 14));
		m_ctrlBaseMainBorderNaviB[1].Create (params);
	}

	m_ctrlBaseMainBorderNaviBCtrl.SetImageSize (CSize (296, 15));
	m_ctrlBaseMainBorderNaviBCtrl.LoadStr (_T("IDB_MP_BORDER_NAVI2_B_CTRL"));

	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_CAPTION_M"), CRect (0, 0, 11, 23), CRect (5, 9, 5, 1));
		m_ctrlBaseMiniBorderCaption.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_CAPTION_M_B"), CRect (0, 0, 5, 3), CRect (2, 1, 2, 1));
		m_ctrlBaseMiniBorderCaptionB.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_MP_BORDER_M"), CRect (0, 0, 7, 4), CRect (3, 1, 3, 2));
		m_ctrlBaseMiniBorder.Create (params);
	}

	m_BaseSysBtnBack.SetImageSize (CSize (97, 20));
	m_BaseSysBtnBack.LoadStr (_T("IDB_MP_BTN_SYS"));

	{
		CBCGPControlRendererParams params (_T("IDB_BACK_EXPLORER"), CRect (0, 0, 9, 36), CRect (4, 16, 4, 18));
		m_backBaseExplorer.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_BTN_EXPLORER"), CRect (0, 0, 66, 33), CRect (5, 14, 5, 2));
		m_btnBaseExplorer.Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_BTN_EXPLORER_LOGO"), CRect (0, 0, 33, 33), CRect (1, 1, 2, 2));
		m_btnBaseExplorerLogo.Create (params);
	}
	m_btnBaseExplorerBF.SetImageSize (CSize (25, 25));
	m_btnBaseExplorerBF.LoadStr (_T("IDB_EXPLORER_BF"));
	m_btnBaseExplorerFrameBF.SetImageSize (CSize (76, 29));
	m_btnBaseExplorerFrameBF.LoadStr (_T("IDB_EXPLORER_BF_FRAME"));
	m_btnBaseExplorerSep.SetImageSize (CSize (2, 33));
	m_btnBaseExplorerSep.LoadStr (_T("IDB_BTN_EXPLORER_SEP"));

	{
		CBCGPControlRendererParams params (_T("IDB_BACK_NAVI1"), CRect (0, 0, 3, 69), CRect (1, 36, 1, 14));
		m_backBaseNavi[0].Create (params);
	}
	{
		CBCGPControlRendererParams params (_T("IDB_BACK_NAVI2"), CRect (0, 0, 9, 69), CRect (4, 36, 4, 14));
		m_backBaseNavi[1].Create (params);
	}
	m_BaseNaviControl[0].SetImageSize (CSize (268, 69));
	m_BaseNaviControl[0].LoadStr (_T("IDB_BACK_NAVI1_CTRL"));
	m_BaseNaviControl[1].SetImageSize (CSize (422, 69));
	m_BaseNaviControl[1].LoadStr (_T("IDB_BACK_NAVI2_CTRL"));

	m_ctrlBaseMainBorderCaption.CopyTo (m_ctrlMainBorderCaption);
	m_ctrlBaseMainBorderCaptionB.CopyTo (m_ctrlMainBorderCaptionB);
	m_ctrlBaseMainBorderExplorerL.CopyTo (m_ctrlMainBorderExplorerL);
	m_ctrlBaseMainBorderExplorerR.CopyTo (m_ctrlMainBorderExplorerR);
	m_ctrlBaseMainBorderL.CopyTo (m_ctrlMainBorderL);
	m_ctrlBaseMainBorderR.CopyTo (m_ctrlMainBorderR);
	m_ctrlBaseMainBorderNaviL[0].CopyTo (m_ctrlMainBorderNaviL[0]);
	m_ctrlBaseMainBorderNaviR[0].CopyTo (m_ctrlMainBorderNaviR[0]);
	m_ctrlBaseMainBorderNaviB[0].CopyTo (m_ctrlMainBorderNaviB[0]);
	m_ctrlBaseMainBorderNaviL[1].CopyTo (m_ctrlMainBorderNaviL[1]);
	m_ctrlBaseMainBorderNaviR[1].CopyTo (m_ctrlMainBorderNaviR[1]);
	m_ctrlBaseMainBorderNaviB[1].CopyTo (m_ctrlMainBorderNaviB[1]);
	m_ctrlBaseMainBorderNaviBCtrl.CopyTo (m_ctrlMainBorderNaviBCtrl);
	m_ctrlBaseMiniBorderCaption.CopyTo (m_ctrlMiniBorderCaption);
	m_ctrlBaseMiniBorderCaptionB.CopyTo (m_ctrlMiniBorderCaptionB);
	m_ctrlBaseMiniBorder.CopyTo (m_ctrlMiniBorder);
	m_BaseSysBtnBack.CopyTo (m_SysBtnBack[0]);
	m_backBaseExplorer.CopyTo (m_backExplorer);
	m_btnBaseExplorer.CopyTo (m_btnExplorer);
	m_btnBaseExplorerSep.CopyTo (m_btnExplorerSep);
	m_btnBaseExplorerLogo.CopyTo (m_btnExplorerLogo);
	m_backBaseNavi[0].CopyTo (m_backNavi[0]);
	m_backBaseNavi[1].CopyTo (m_backNavi[1]);
	m_BaseNaviControl[0].CopyTo (m_NaviControl[0]);
	m_BaseNaviControl[1].CopyTo (m_NaviControl[1]);
}

void CVisualManager::LoadImages ()
{
	LoadBaseImages ();

	m_SysBtnBack[1].SetImageSize (CSize (25, 18));
	m_SysBtnBack[1].LoadStr (_T("IDB_MP_BTN_SYS_1"));
	m_SysBtnBack[2].SetImageSize (CSize (25, 18));
	m_SysBtnBack[2].LoadStr (_T("IDB_MP_BTN_SYS_2"));
	m_SysBtnBack[3].SetImageSize (CSize (43, 18));
	m_SysBtnBack[3].LoadStr (_T("IDB_MP_BTN_SYS_3"));

	m_SysBtnClose.SetImageSize (CSize (41, 20));
	m_SysBtnClose.LoadStr (_T("IDB_MP_ICON_CLOSE"));
	m_SysBtnRestore.SetImageSize (CSize (24, 20));
	m_SysBtnRestore.LoadStr (_T("IDB_MP_ICON_RESTORE"));
	m_SysBtnMaximize.SetImageSize (CSize (24, 20));
	m_SysBtnMaximize.LoadStr (_T("IDB_MP_ICON_MAXIMIZE"));
	m_SysBtnMinimize.SetImageSize (CSize (24, 20));
	m_SysBtnMinimize.LoadStr (_T("IDB_MP_ICON_MINIMIZE"));

	m_CaptionBtnClose.SetImageSize (CSize (11, 11));
	m_CaptionBtnClose.LoadStr (_T("IDB_MP_CAPTION_BTN_CLOSE"));

	m_ThumbB.SetImageSize (CSize (8, 15));
	m_ThumbB.LoadStr (_T("IDB_THUMB_B"));
	m_ThumbV.SetImageSize (CSize (16, 8));
	m_ThumbV.LoadStr (_T("IDB_THUMB_V"));

	m_iconArrowDown.SetImageSize (CSize (7, 7));
	m_iconArrowDown.LoadStr (_T("IDB_ICON_ARROW_DOWN"));

	m_NaviControl[2].SetImageSize (CSize (268, 69));
	m_NaviControl[2].LoadStr (_T("IDB_BACK_NAVI1_CTRL_A"));
	m_NaviControl[3].SetImageSize (CSize (422, 69));
	m_NaviControl[3].LoadStr (_T("IDB_BACK_NAVI2_CTRL_A"));
	{
		CBCGPControlRendererParams params (_T("IDB_NAVI_PROGRESS_BACK"), CRect (0, 0, 21, 9), CRect (10, 4, 10, 4));
		m_NaviProgressBack.Create (params);
	}

	m_ChannelEqualizerV.SetImageSize (CSize (22, 75));
	m_ChannelEqualizerV.LoadStr (_T("IDB_CHANNEL_EQUALIZER_V"));
}

void CVisualManager::UpdateImages (double h, double s)
{
	if (m_dblHue != h || m_dblSaturation != s)
	{
		m_dblHue = h;
		m_dblSaturation = s;

		UpdateLinkImages ();

		theApp.WriteInt (_T("ColorChooserH"), (int)(m_dblHue * 1000.0)); 
		theApp.WriteInt (_T("ColorChooserS"), (int)(m_dblSaturation * 1000.0));
	}
}

void CVisualManager::CleanUpBaseImages ()
{
	m_ctrlBaseMainBorderCaption.CleanUp ();
	m_ctrlBaseMainBorderCaptionB.CleanUp ();
	m_ctrlBaseMainBorderExplorerL.CleanUp ();
	m_ctrlBaseMainBorderExplorerR.CleanUp ();
	m_ctrlBaseMainBorderL.CleanUp ();
	m_ctrlBaseMainBorderR.CleanUp ();
	m_ctrlBaseMainBorderNaviL[0].CleanUp ();
	m_ctrlBaseMainBorderNaviL[1].CleanUp ();
	m_ctrlBaseMainBorderNaviR[0].CleanUp ();
	m_ctrlBaseMainBorderNaviR[1].CleanUp ();
	m_ctrlBaseMainBorderNaviB[0].CleanUp ();
	m_ctrlBaseMainBorderNaviB[1].CleanUp ();
	m_ctrlBaseMainBorderNaviBCtrl.Clear ();
	m_ctrlBaseMiniBorderCaption.CleanUp ();
	m_ctrlBaseMiniBorderCaptionB.CleanUp ();
	m_ctrlBaseMiniBorder.CleanUp ();
	m_BaseSysBtnBack.Clear ();
	m_backBaseExplorer.CleanUp ();
	m_btnBaseExplorerBF.Clear ();
	m_btnBaseExplorerFrameBF.Clear ();
	m_btnBaseExplorer.CleanUp ();
	m_btnBaseExplorerSep.Clear ();
	m_btnBaseExplorerLogo.CleanUp ();
	m_backBaseNavi[0].CleanUp ();
	m_backBaseNavi[1].CleanUp ();
	m_BaseNaviControl[0].Clear ();
	m_BaseNaviControl[1].Clear ();
}

void CVisualManager::CleanUp ()
{
	if (m_bUpdateColors)
	{
		return;
	}

	CleanUpBaseImages ();

	m_ctrlMainBorderCaption.CleanUp ();
	m_ctrlMainBorderCaptionB.CleanUp ();
	m_ctrlMainBorderExplorerL.CleanUp ();
	m_ctrlMainBorderExplorerR.CleanUp ();
	m_ctrlMainBorderL.CleanUp ();
	m_ctrlMainBorderR.CleanUp ();
	m_ctrlMainBorderNaviL[0].CleanUp ();
	m_ctrlMainBorderNaviL[1].CleanUp ();
	m_ctrlMainBorderNaviR[0].CleanUp ();
	m_ctrlMainBorderNaviR[1].CleanUp ();
	m_ctrlMainBorderNaviB[0].CleanUp ();
	m_ctrlMainBorderNaviB[1].CleanUp ();
	m_ctrlMainBorderNaviBCtrl.Clear ();
	m_ctrlMiniBorderCaption.CleanUp ();
	m_ctrlMiniBorderCaptionB.CleanUp ();
	m_ctrlMiniBorder.CleanUp ();

	m_SysBtnBack[0].Clear ();
	m_SysBtnBack[1].Clear ();
	m_SysBtnBack[2].Clear ();
	m_SysBtnBack[3].Clear ();
	m_SysBtnClose.Clear ();
	m_SysBtnRestore.Clear ();
	m_SysBtnMaximize.Clear ();
	m_SysBtnMinimize.Clear ();

	m_CaptionBtnClose.Clear ();
	
	m_ThumbB.Clear ();
	m_ThumbV.Clear ();

	m_AppCaptionFont.DeleteObject ();

	m_iconArrowDown.Clear ();

	m_backExplorer.CleanUp ();
	m_btnExplorer.CleanUp ();
	m_btnExplorerSep.Clear ();

	m_backNavi[0].CleanUp ();
	m_backNavi[1].CleanUp ();
	m_NaviControl[0].Clear ();
	m_NaviControl[1].Clear ();
	m_NaviControl[2].Clear ();
	m_NaviControl[3].Clear ();
	m_NaviProgressBack.CleanUp ();

	m_ChannelEqualizerV.Clear ();

	m_ActivateFlag.RemoveAll ();
}

void CVisualManager::OnUpdateSystemColors ()
{
	m_bUpdateColors = TRUE;

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

	m_brTabBack.DeleteObject ();
	m_brTabBack.CreateSolidBrush (globalData.clrBarFace);

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

	m_szNcBtnSize[0] = CSize (::GetSystemMetrics (SM_CXSIZE),
							  ::GetSystemMetrics (SM_CYSIZE));
	m_szNcBtnSize[1] = CSize (::GetSystemMetrics (SM_CXSMSIZE),
							  ::GetSystemMetrics (SM_CYSMSIZE));

	m_bUpdateColors = FALSE;
}

BOOL CVisualManager::OnNcActivate (CWnd* pWnd, BOOL bActive)
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

BOOL CVisualManager::IsWindowActive (CWnd* pWnd) const
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

CSize CVisualManager::GetSystemBorders () const
{
	CSize size (::GetSystemMetrics (SM_CYSIZEFRAME), 
			    ::GetSystemMetrics (SM_CXSIZEFRAME));

	return size;
}

void CVisualManager::DrawNcBtn (CDC* pDC, const CRect& rect, UINT nButton, 
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

void CVisualManager::DrawNcText (CDC* pDC, CRect& rect, 
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

void CVisualManager::DrawNcCaption (CDC* pDC, CRect rectCaption, 
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

	rectSysBtn.right -= (szSysBorder.cx - 3);
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

BOOL CVisualManager::OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw)
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
			m_ctrlMainBorderExplorerL.GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderExplorerL.Draw (&dc, rtPart, indexBorder);
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
			m_ctrlMainBorderExplorerR.GetParams ().m_rectImage.Height ();
		m_ctrlMainBorderExplorerR.Draw (&dc, rtPart, indexBorder);
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

BOOL CVisualManager::OnSetWindowRegion (CWnd* pWnd, CSize sizeWindow)
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

void CVisualManager::OnUpdateCaptionButtons (CRect rectCaption, const CObList& lstSysButtons, CWnd* /*pWnd*/)
{
	if (!CanDrawImage ())
	{
		return;
	}

	CSize szSysBorder (GetSystemBorders ());

	int nIndex = 3;

	int x = rectCaption.right + szSysBorder.cx - (szSysBorder.cx - 1);

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

void CVisualManager::OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL bNCArea)
{
	if (CanDrawImage ())
	{
		ASSERT_VALID(pDC);
		ASSERT_VALID(pBar);

		if (DYNAMIC_DOWNCAST (CExplorerBar, pBar) != NULL)
		{
			if (!bNCArea)
			{
				CRect rectBorders (GetExplorerBarBorders ());
				rectClient.InflateRect (rectBorders.left, rectBorders.top, rectBorders.right, rectBorders.bottom);
			}
			m_backExplorer.Draw (pDC, rectClient, globalData.DwmIsCompositionEnabled () ? 1 : 0);
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
		else if (DYNAMIC_DOWNCAST (CBCGPAutoHideDockBar, pBar) != NULL)
		{
			pDC->FillRect (rectClip, &m_brTabBack);
			return;
		}
	}

	CBCGPWinXPVisualManager::OnFillBarBackground (pDC, pBar, rectClient, rectClip, bNCArea);
}

COLORREF CVisualManager::OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
			BOOL bActive, CRect rectCaption, CRect rectButtons)
{
	if (!CanDrawImage ())
	{
		return CBCGPWinXPVisualManager::OnDrawControlBarCaption (pDC, pBar, 
			bActive, rectCaption, rectButtons);
	}

	ASSERT_VALID (pDC);

	rectCaption.bottom += 2;
	pDC->FillRect (rectCaption, &globalData.brBarFace);

    // get the text color
	return bActive ? m_clrAppCaptionActiveText : m_clrAppCaptionInactiveText;
}

void CVisualManager::OnDrawCaptionButton (
						CDC* pDC, CBCGPCaptionButton* pButton, BOOL bActive,
						BOOL bHorz, BOOL bMaximized, BOOL bDisabled, 
						int nImageID/* = -1*/)
{
	if (!CanDrawImage ())
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

void CVisualManager::OnDrawSliderChannel (CDC* pDC, CBCGPSliderCtrl* pSlider, 
											BOOL bVert, CRect rect, BOOL bDrawOnGlass)
{
	CBCGPDialogBar* pBar = NULL;
	if (pSlider != NULL)
	{
		pBar = DYNAMIC_DOWNCAST (CBCGPDialogBar, pSlider->GetParent ());
	}

	if (CanDrawImage () && pBar != NULL)
	{
		CRect rectSlider;
		pSlider->GetClientRect (rectSlider);

		if (DYNAMIC_DOWNCAST (CColorChooserBar, pBar) != NULL)
		{
			ASSERT_VALID (pDC);

			rect.OffsetRect (0, -1);
			int nSize = rect.Width ();

			int nOldBK = pDC->GetBkColor ();

			UINT nID = pSlider->GetDlgCtrlID ();
			if (nID == IDC_CH_SLIDER_H)
			{
				for (int i = 0; i < nSize; i++)
				{
					COLORREF clr = CBCGPDrawManager::HLStoRGB_TWO (i * 359.0 / (double)(nSize - 1) + 45.0, 0.5, 1.0);
					pDC->FillSolidRect (rect.left + i, rect.top, 1, rect.Height (), clr);
				}
			}
			else
			{
				COLORREF clrSrc = CBCGPDrawManager::HLStoRGB_TWO (m_dblHue + 180.0 + 45.0, 0.5, 1.0);
				double clrSrcR = GetRValue (clrSrc);
				double clrSrcG = GetGValue (clrSrc);
				double clrSrcB = GetBValue (clrSrc);

				for (int i = 0; i < nSize; i++)
				{
					double value = i / (double)(nSize - 1);
					double value255 = 255.0 * (1.0 - value);

					COLORREF clr = RGB 
						(
							value255 + clrSrcR * value,
							value255 + clrSrcG * value,
							value255 + clrSrcB * value
						);
					pDC->FillSolidRect (rect.left + i, rect.top, 1, rect.Height (), clr);
				}
			}

			pDC->SetBkColor (nOldBK);

			return;
		}
		else if (DYNAMIC_DOWNCAST (CEqualizerBar, pBar) != NULL)
		{
			ASSERT_VALID (pDC);

			m_ChannelEqualizerV.DrawEx (pDC, rectSlider, 0, 
				CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);

			return;
		}
	}

	CBCGPWinXPVisualManager::OnDrawSliderChannel (pDC, pSlider, bVert, rect, bDrawOnGlass);
}

void CVisualManager::OnDrawSliderThumb (CDC* pDC, CBCGPSliderCtrl* pSlider,
			CRect rect, BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled,
			BOOL bVert, BOOL bLeftTop, BOOL bRightBottom, BOOL bDrawOnGlass)
{
	CBCGPDialogBar* pBar = NULL;
	if (pSlider != NULL)
	{
		pBar = DYNAMIC_DOWNCAST (CBCGPDialogBar, pSlider->GetParent ());
	}

	if (CanDrawImage () && pBar != NULL)
	{
		CRect rectSlider;
		pSlider->GetClientRect (rectSlider);

		if (DYNAMIC_DOWNCAST (CColorChooserBar, pBar) != NULL ||
			DYNAMIC_DOWNCAST (CEqualizerBar, pBar) != NULL)
		{
			ASSERT_VALID (pDC);

			int nIndex = 0;
			if (bIsPressed)
			{
				nIndex = 2;
			}
			else if (bIsHighlighted)
			{
				nIndex = 1;
			}

			if (bVert)
			{
				if (bLeftTop && bRightBottom)
				{
					rect.left  = rectSlider.left;
					rect.right = rectSlider.right;
					m_ThumbV.DrawEx (pDC, rect, nIndex, 
						CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);
				}
			}
			else
			{
				if (!bLeftTop && bRightBottom)
				{
					rect.top    = rectSlider.top;
					rect.bottom = rectSlider.bottom;
					m_ThumbB.DrawEx (pDC, rect, nIndex, 
						CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertCenter);
				}
			}

			return;
		}
	}

	CBCGPWinXPVisualManager::OnDrawSliderThumb (pDC, pSlider, rect, bIsHighlighted, 
		bIsPressed, bIsDisabled, bVert, bLeftTop, bRightBottom, bDrawOnGlass);
}

COLORREF CVisualManager::GetURLLinkColor (CBCGPURLLinkButton* pButton, BOOL bHover)
{
	ASSERT_VALID (pButton);

	if (pButton->GetParent ()->IsKindOf (RUNTIME_CLASS (CColorChooserBar)))
	{
		return RGB (171, 213, 253);
	}

	return CBCGPWinXPVisualManager::GetURLLinkColor (pButton, bHover);
}

void CVisualManager::UpdateLinkImages ()
{
	const int count = (const int)m_arLinkImages.GetSize ();
	if (count == 0)
	{
		return;
	}

	for (int i = 0; i < count; i++)
	{
		HBITMAP bmpSrc = m_arLinkImages[i].bmpSrc->GetImageWell ();
		HBITMAP bmpDst = m_arLinkImages[i].bmpDst->GetImageWell ();

		if (bmpSrc == NULL ||
			bmpDst == NULL)
		{
			continue;
		}

		DIBSECTION dibSrc;
		ZeroMemory (&dibSrc, sizeof (DIBSECTION));
		if (::GetObject (bmpSrc, sizeof (DIBSECTION), &dibSrc) != sizeof (DIBSECTION) ||
			dibSrc.dsBm.bmBits == NULL)
		{
			continue;
		}

		DIBSECTION dibDst;
		ZeroMemory (&dibDst, sizeof (DIBSECTION));
		if (::GetObject (bmpDst, sizeof (DIBSECTION), &dibDst) != sizeof (DIBSECTION) ||
			dibDst.dsBm.bmBits == NULL)
		{
			continue;
		}

		if (dibSrc.dsBm.bmWidth != dibDst.dsBm.bmWidth ||
			dibSrc.dsBm.bmHeight != dibDst.dsBm.bmHeight ||
			dibSrc.dsBm.bmBitsPixel != dibDst.dsBm.bmBitsPixel)
		{
			continue;
		}

		const int width  = dibSrc.dsBm.bmWidth;
		const int height = dibSrc.dsBm.bmHeight;
		const int pitch  = dibSrc.dsBm.bmWidthBytes;
		LPBYTE pBitsSrc  = (LPBYTE)dibSrc.dsBm.bmBits;
		LPBYTE pBitsDst  = (LPBYTE)dibDst.dsBm.bmBits;

		for (int y = 0; y < height; y++)
		{
			LPBYTE pRowSrc = pBitsSrc;
			LPBYTE pRowDst = pBitsDst;

			for (int x = 0; x < width; x++)
			{
				if (pRowSrc[2] != pRowSrc[1] || pRowSrc[1] != pRowSrc[0])
				{
					COLORREF clr = RGB (pRowSrc[2], pRowSrc[1], pRowSrc[0]);
					UPDATE_COLOR (clr, m_dblHue, m_dblSaturation);

					*pRowDst++ = GetBValue(clr);
					*pRowDst++ = GetGValue(clr);
					*pRowDst++ = GetRValue(clr);
					*pRowDst++;
				}
				else
				{
					memcpy (pRowDst, pRowSrc, 4);
					pRowDst += 4;
				}

				pRowSrc += 4;
			}

			pBitsSrc += pitch;
			pBitsDst += pitch;
		}
	}

	m_clrSlider[0] = RGB ( 93, 104, 132);
	UPDATE_COLOR (m_clrSlider[0], m_dblHue, m_dblSaturation);
	m_clrSlider[1] = RGB ( 47,  52,  66);
	UPDATE_COLOR (m_clrSlider[1], m_dblHue, m_dblSaturation);
	m_clrSlider[2] = RGB ( 40,  45,  57);
	UPDATE_COLOR (m_clrSlider[2], m_dblHue, m_dblSaturation);
	m_clrSlider[3] = RGB ( 20,  23,  59);
	UPDATE_COLOR (m_clrSlider[3], m_dblHue, m_dblSaturation);

	COLORREF clr = RGB (238, 243, 250);
	UPDATE_COLOR (clr, m_dblHue, m_dblSaturation);

	m_brView.DeleteObject ();
	m_brView.CreateSolidBrush (clr);
}

void CVisualManager::OnDrawSlider (CDC* pDC, CBCGPSlider* pSlider, CRect rect, BOOL bAutoHideMode)
{
	if (!CanDrawImage ())
	{
		CBCGPWinXPVisualManager::OnDrawSlider (pDC, pSlider, rect, bAutoHideMode);
		return;
	}

	ASSERT_VALID (pDC);
	ASSERT_VALID (pSlider);

	pDC->FillRect (rect, &globalData.brBarFace);

	COLORREF clr1E = m_clrSlider[0];
	COLORREF clr1S = m_clrSlider[1];
	COLORREF clr2E = m_clrSlider[2];
	COLORREF clr2S = m_clrSlider[3];

	CBCGPDrawManager dm (*pDC);

	if (pSlider->IsHorizontal ())
	{
		rect.top += rect.Height () / 2 - 2;
		rect.bottom = rect.top + 3;

		dm.Fill4ColorsGradient (rect, clr1S, clr1E, clr1E, clr1S, FALSE);

		rect.DeflateRect (0, 1);

		dm.Fill4ColorsGradient (rect, clr2S, clr2E, clr2E, clr2S, FALSE);
	}
	else
	{
		rect.left += rect.Width () / 2 - 2;
		rect.right = rect.left + 3;

		dm.Fill4ColorsGradient (rect, clr1E, clr1S, clr1S, clr1E, TRUE);

		rect.DeflateRect (1, 0);

		dm.Fill4ColorsGradient (rect, clr2E, clr2S, clr2S, clr2E, TRUE);
	}
}

COLORREF CVisualManager::OnFillMiniFrameCaption (CDC* pDC, 
								CRect rectCaption, 
								CBCGPMiniFrameWnd* /*pFrameWnd*/, BOOL bActive)
{
	ASSERT_VALID (pDC);

	CRect rectCaptionB (rectCaption);

	CSize szSysBorder (::GetSystemMetrics (SM_CYSIZEFRAME), ::GetSystemMetrics (SM_CXSIZEFRAME));
	rectCaption.InflateRect (szSysBorder.cx, szSysBorder.cy, szSysBorder.cx, 0);

	m_ctrlMiniBorderCaption.Draw (pDC, rectCaption);

	rectCaptionB.InflateRect (2, 0);
	rectCaptionB.top = rectCaptionB.bottom - m_ctrlMiniBorderCaptionB.GetParams ().m_rectImage.Height ();
	m_ctrlMiniBorderCaptionB.Draw (pDC, rectCaptionB, 0);

	//rectCaption

    // get the text color
	return bActive 
			? m_clrAppCaptionActiveTitleText
			: m_clrAppCaptionInactiveTitleText;
}

void CVisualManager::OnDrawMiniFrameBorder (
										CDC* pDC, CBCGPMiniFrameWnd* /*pFrameWnd*/,
										CRect rectBorder, CRect /*rectBorderSize*/)
{
	ASSERT_VALID (pDC);

	CSize szSysBorder (::GetSystemMetrics (SM_CYSIZEFRAME), ::GetSystemMetrics (SM_CXSIZEFRAME));
	rectBorder.top += szSysBorder.cy + ::GetSystemMetrics (SM_CYSMCAPTION);

	CRect rtPart (rectBorder);
	rtPart.right  = rtPart.left + szSysBorder.cx;
	rtPart.bottom -= szSysBorder.cy;
	m_ctrlMainBorderL.Draw (pDC, rtPart);

	rtPart = rectBorder;
	rtPart.left   = rtPart.right - szSysBorder.cx;
	rtPart.bottom -= szSysBorder.cy;
	m_ctrlMainBorderR.Draw (pDC, rtPart);

	rectBorder.top = rtPart.bottom;
	m_ctrlMiniBorder.Draw (pDC, rectBorder);

	rectBorder.DeflateRect (::GetSystemMetrics (SM_CXSIZEFRAME), 0);
	rectBorder.InflateRect (2, 0);
	rectBorder.bottom = rectBorder.top + m_ctrlMiniBorderCaptionB.GetParams ().m_rectImage.Height ();
	m_ctrlMiniBorderCaptionB.Draw (pDC, rectBorder, 1);
}

void CVisualManager::GetTabFrameColors (const CBCGPBaseTabWnd* pTabWnd,
				   COLORREF& clrDark,
				   COLORREF& clrBlack,
				   COLORREF& clrHighlight,
				   COLORREF& clrFace,
				   COLORREF& clrDarkShadow,
				   COLORREF& clrLight,
				   CBrush*& pbrFace,
				   CBrush*& pbrBlack)
{
	CBCGPWinXPVisualManager::GetTabFrameColors (pTabWnd,
			   clrDark, clrBlack,
			   clrHighlight, clrFace,
			   clrDarkShadow, clrLight,
			   pbrFace, pbrBlack);

	clrBlack = clrLight = clrHighlight = m_clrSlider[0];
	clrDark = RGB (0, 0, 0);
}
