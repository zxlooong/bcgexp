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
// VisualManager.h: interface for the CVisualManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALMANAGER_H__423B8BA6_D991_4C1A_AF1B_DDA4B12CB1BC__INCLUDED_)
#define AFX_VISUALMANAGER_H__423B8BA6_D991_4C1A_AF1B_DDA4B12CB1BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bcgglobals.h"

class CVisualManager : public CBCGPWinXPVisualManager  
{
	friend class CExplorerBar;

	DECLARE_DYNCREATE(CVisualManager)

public:
	struct XLinkImages
	{
		CBCGPToolBarImages* bmpSrc;
		CBCGPToolBarImages* bmpDst;

		XLinkImages (CBCGPToolBarImages* bmpS = NULL, CBCGPToolBarImages* bmpD = NULL)
			: bmpSrc (bmpS)
			, bmpDst (bmpD)
		{
		}
	};

	typedef CArray<XLinkImages, XLinkImages> XLinkImagesArray;

protected:
	CVisualManager();
	virtual ~CVisualManager();

public:
	void LoadImages ();
	void UpdateImages (double h, double s);
	
	void UpdateLinkImages ();

	virtual void OnUpdateSystemColors ();
	void OnUpdateCaptionButtons (CRect rectCaption, const CObList& lstSysButtons,	CWnd* pWnd);

	virtual BOOL IsOwnerDrawCaption ()
	{
		return CanDrawImage () && !globalData.DwmIsCompositionEnabled ();
	}

	virtual COLORREF GetURLLinkColor (CBCGPURLLinkButton* pButton, BOOL bHover);
	virtual BOOL OnNcActivate (CWnd* pWnd, BOOL bActive);
	virtual BOOL OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw);
	virtual BOOL OnSetWindowRegion (CWnd* pWnd, CSize sizeWindow);

	virtual void OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL bNCArea = FALSE);

	virtual COLORREF OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
		BOOL bActive, CRect rectCaption, CRect rectButtons);
	virtual void OnDrawCaptionButton (CDC* pDC, CBCGPCaptionButton* pButton, BOOL bActive, BOOL bHorz,
										BOOL bMaximized, BOOL bDisabled, int nImageID = -1);

	virtual void OnDrawSliderChannel (CDC* pDC, CBCGPSliderCtrl* pSlider, BOOL bVert, CRect rect, BOOL bDrawOnGlass);

	virtual void OnDrawSliderThumb (CDC* pDC, CBCGPSliderCtrl* pSlider, 
			CRect rect, BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled,
			BOOL bVert, BOOL bLeftTop, BOOL bRightBottom,
			BOOL bDrawOnGlass);

	virtual void OnDrawSlider (CDC* pDC, CBCGPSlider* pSlider, CRect rect, BOOL bAutoHideMode);

	virtual COLORREF OnFillMiniFrameCaption (CDC* pDC, CRect rectCaption, 
											CBCGPMiniFrameWnd* pFrameWnd,
											BOOL bActive);
	virtual void OnDrawMiniFrameBorder (CDC* pDC, CBCGPMiniFrameWnd* pFrameWnd,
										CRect rectBorder, CRect rectBorderSize);

	virtual void GetTabFrameColors (const CBCGPBaseTabWnd* pTabWnd,
				   COLORREF& clrDark,
				   COLORREF& clrBlack,
				   COLORREF& clrHighlight,
				   COLORREF& clrFace,
				   COLORREF& clrDarkShadow,
				   COLORREF& clrLight,
				   CBrush*& pbrFace,
				   CBrush*& pbrBlack);

	BOOL IsLargeNaviControl () const;

	CBCGPToolBarImages& GetArrowDownIcon ()
	{
		return m_iconArrowDown;
	}

	int GetExplorerBarButtonWidth (BOOL bLogo) const
	{
		return bLogo ? 33 : 100;
	}
	
	int GetExplorerBarSeparatorWidth () const
	{
		return 17;
	}
	
	CRect GetExplorerBarBorders () const
	{
		return CRect (4, 0, 0, 0);
	}

	CBCGPControlRenderer& GetExplorerBarBackImage ()
	{
		return m_backExplorer;
	}
	
	CBCGPControlRenderer& GetExplorerBarButtonImage (BOOL bLogo)
	{
		if (bLogo)
		{
			return m_btnExplorerLogo;
		}

		return m_btnExplorer;
	}
	
	CBCGPToolBarImages& GetExplorerBarSeparatorImage ()
	{
		return m_btnExplorerSep;
	}

	CBCGPControlRenderer& GetNaviBarBackImage ()
	{
		return m_backNavi [IsLargeNaviControl () ? 1 : 0];
	}
	
	CBCGPToolBarImages& GetNaviBarControlImage ()
	{
		int indexNavi = IsLargeNaviControl () ? 1 : 0;
		if (globalData.DwmIsCompositionEnabled ())
		{
			indexNavi += 2;
		}

		return m_NaviControl [indexNavi];
	}
	
	int GetNaviBarSeparatorWidth () const
	{
		return 8;
	}
	
	CRect GetNaviBarBorders () const
	{
		return CRect (0, 0, 0, 0);
	}

	CPoint GetEqualizerOffset ()
	{
		return CPoint (10, 0);
	}
	
	CBCGPToolBarImages& GetEqualizerChannelImage ()
	{
		return m_ChannelEqualizerV;
	}

	double GetImagesH () const
	{
		return m_dblHue;
	}

	double GetImagesS () const
	{
		return m_dblSaturation;
	}

	COLORREF GetSliderColor (int index) const
	{
		return m_clrSlider[index];
	}

	CBrush& GetViewBrush ()
	{
		return m_brView;
	}

protected:
	BOOL CanDrawImage () const
	{
#ifdef BCGP_EXCLUDE_PNG_SUPPORT
		return FALSE;
#else
		return globalData.m_nBitsPerPixel > 8 && 
			!globalData.IsHighContastMode ();
#endif
	}

	virtual void CleanUp ();

	void DrawNcBtn (CDC* pDC, const CRect& rect, UINT nButton, 
							BCGBUTTON_STATE state, BOOL bSmall, 
							BOOL bActive, BOOL bMDI = FALSE);
	void DrawNcText (CDC* pDC, CRect& rect, const CString& strTitle, 
							const CString& strDocument, BOOL bPrefix, 
							BOOL bActive, BOOL bIsRTL, BOOL bTextCenter,
							BOOL bGlass = FALSE, int nGlassGlowSize = 0, 
							COLORREF clrGlassText = (COLORREF)-1);
	void DrawNcCaption (CDC* pDC, CRect rectCaption, 
						   DWORD dwStyle, DWORD dwStyleEx,
						   const CString& strTitle, const CString& strDocument,
						   HICON hIcon, BOOL bPrefix, BOOL bActive, BOOL bTextCenter,
						   const CObList& lstSysButtons);

	BOOL	IsWindowActive (CWnd* pWnd) const;
	CSize	GetSystemBorders () const;

	void LoadBaseImages ();
	void CleanUpBaseImages ();

	void SetHS ();

protected:

	CSize					m_szNcBtnSize[2];

	CBCGPControlRenderer	m_ctrlBaseMainBorderCaption;
	CBCGPControlRenderer	m_ctrlBaseMainBorderCaptionB;
	CBCGPControlRenderer	m_ctrlBaseMainBorderExplorerL;
	CBCGPControlRenderer	m_ctrlBaseMainBorderExplorerR;
	CBCGPControlRenderer	m_ctrlBaseMainBorderL;
	CBCGPControlRenderer	m_ctrlBaseMainBorderR;
	CBCGPControlRenderer	m_ctrlBaseMainBorderNaviL[2];
	CBCGPControlRenderer	m_ctrlBaseMainBorderNaviR[2];
	CBCGPControlRenderer	m_ctrlBaseMainBorderNaviB[2];
	CBCGPToolBarImages		m_ctrlBaseMainBorderNaviBCtrl;
	CBCGPControlRenderer	m_ctrlBaseMiniBorderCaption;
	CBCGPControlRenderer	m_ctrlBaseMiniBorderCaptionB;
	CBCGPControlRenderer	m_ctrlBaseMiniBorder;
	CBCGPToolBarImages		m_BaseSysBtnBack;
	CBCGPControlRenderer	m_backBaseExplorer;
	CBCGPToolBarImages		m_btnBaseExplorerBF;
	CBCGPToolBarImages		m_btnBaseExplorerFrameBF;
	CBCGPControlRenderer	m_btnBaseExplorer;
	CBCGPToolBarImages		m_btnBaseExplorerSep;
	CBCGPControlRenderer	m_btnBaseExplorerLogo;
	CBCGPControlRenderer	m_backBaseNavi[2];
	CBCGPToolBarImages		m_BaseNaviControl[2];

	CBCGPControlRenderer	m_ctrlMainBorderCaption;
	CBCGPControlRenderer	m_ctrlMainBorderCaptionB;
	CBCGPControlRenderer	m_ctrlMainBorderExplorerL;
	CBCGPControlRenderer	m_ctrlMainBorderExplorerR;
	CBCGPControlRenderer	m_ctrlMainBorderL;
	CBCGPControlRenderer	m_ctrlMainBorderR;
	CBCGPControlRenderer	m_ctrlMainBorderNaviL[2];
	CBCGPControlRenderer	m_ctrlMainBorderNaviR[2];
	CBCGPControlRenderer	m_ctrlMainBorderNaviB[2];
	CBCGPToolBarImages		m_ctrlMainBorderNaviBCtrl;
	CBCGPControlRenderer	m_ctrlMiniBorderCaption;
	CBCGPControlRenderer	m_ctrlMiniBorderCaptionB;
	CBCGPControlRenderer	m_ctrlMiniBorder;

	CFont					m_AppCaptionFont;

	COLORREF				m_clrAppCaptionActiveText;
	COLORREF				m_clrAppCaptionInactiveText;
	COLORREF				m_clrAppCaptionActiveTitleText;
	COLORREF				m_clrAppCaptionInactiveTitleText;

	CBCGPToolBarImages		m_SysBtnBack[4];
	CBCGPToolBarImages		m_SysBtnClose;
	CBCGPToolBarImages		m_SysBtnRestore;
	CBCGPToolBarImages		m_SysBtnMaximize;
	CBCGPToolBarImages		m_SysBtnMinimize;

	CBCGPToolBarImages		m_CaptionBtnClose;

	CBCGPToolBarImages		m_ThumbB;
	CBCGPToolBarImages		m_ThumbV;	

	CBCGPToolBarImages		m_iconArrowDown;

	CBCGPControlRenderer	m_backExplorer;
	CBCGPControlRenderer	m_btnExplorer;
	CBCGPToolBarImages		m_btnExplorerSep;
	CBCGPControlRenderer	m_btnExplorerLogo;

	CBCGPControlRenderer	m_backNavi[2];
	CBCGPToolBarImages		m_NaviControl[4];
	CBCGPControlRenderer	m_NaviProgressBack;	

	CBCGPToolBarImages		m_ChannelEqualizerV;

	CMap<HWND, HWND, BOOL, BOOL>
							m_ActivateFlag;

	BOOL					m_bUpdateColors;

	XLinkImagesArray		m_arLinkImages;

	double					m_dblHue;
	double					m_dblSaturation;

	CBrush					m_brView;
	COLORREF				m_clrSlider[4];
};

#endif // !defined(AFX_VISUALMANAGER_H__423B8BA6_D991_4C1A_AF1B_DDA4B12CB1BC__INCLUDED_)
