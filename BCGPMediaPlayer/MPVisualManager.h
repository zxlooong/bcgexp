// MPVisualManager.h: interface for the CMPVisualManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPVISUALMANAGER_H__423B8BA6_D991_4C1A_AF1B_DDA4B12CB1BC__INCLUDED_)
#define AFX_MPVISUALMANAGER_H__423B8BA6_D991_4C1A_AF1B_DDA4B12CB1BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bcgglobals.h"

class CMPVisualManager : public CBCGPWinXPVisualManager  
{
	DECLARE_DYNCREATE(CMPVisualManager)

protected:
	CMPVisualManager();
	virtual ~CMPVisualManager();

public:
	virtual void OnUpdateSystemColors ();
	void OnUpdateCaptionButtons (CRect rectCaption, CObList& lstSysButtons,	CWnd* pWnd);

	virtual BOOL IsOwnerDrawCaption ()
	{
		return CanDrawImage () && !globalData.DwmIsCompositionEnabled ();
	}

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

	BOOL IsLargeNaviControl () const;

	CBCGPToolBarImages& GetArrowDownIcon ()
	{
		return m_iconArrowDown;
	}

	int GetAddressBarButtonWidth () const
	{
		return 100;
	}
	int GetAddressBarSeparatorWidth () const
	{
		return 17;
	}
	CRect GetAddressBarBorders () const
	{
		return CRect (4, 0, 0, 0);
	}

	CBCGPControlRenderer& GetAddressBarBackImage ()
	{
		return m_BackAddress;
	}
	CBCGPControlRenderer& GetAddressBarButtonImage ()
	{
		return m_btnAddress;
	}
	CBCGPToolBarImages& GetAddressBarSeparatorImage ()
	{
		return m_btnAddressSep;
	}

	CBCGPControlRenderer& GetNaviBarBackImage ()
	{
		return m_BackNavi [IsLargeNaviControl () ? 1 : 0];
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

protected:
	CSize                   m_szNcBtnSize[2];

	CBCGPControlRenderer	m_ctrlMainBorderCaption;
	CBCGPControlRenderer	m_ctrlMainBorderCaptionB;
	CBCGPControlRenderer	m_ctrlMainBorderAddressL;
	CBCGPControlRenderer	m_ctrlMainBorderAddressR;
	CBCGPControlRenderer	m_ctrlMainBorderL;
	CBCGPControlRenderer	m_ctrlMainBorderR;
	CBCGPControlRenderer	m_ctrlMainBorderNaviL[2];
	CBCGPControlRenderer	m_ctrlMainBorderNaviR[2];
	CBCGPControlRenderer	m_ctrlMainBorderNaviB[2];
	CBCGPToolBarImages		m_ctrlMainBorderNaviBCtrl;

	CFont					m_AppCaptionFont;

	COLORREF				m_clrAppCaptionActiveText;
	COLORREF				m_clrAppCaptionInactiveText;
	COLORREF				m_clrAppCaptionActiveTitleText;
	COLORREF				m_clrAppCaptionInactiveTitleText;

	CBCGPToolBarImages	    m_SysBtnBack[4];
	CBCGPToolBarImages      m_SysBtnClose;
	CBCGPToolBarImages      m_SysBtnRestore;
	CBCGPToolBarImages      m_SysBtnMaximize;
	CBCGPToolBarImages      m_SysBtnMinimize;

	CBCGPToolBarImages      m_CaptionBtnClose;

	CBCGPToolBarImages		m_iconArrowDown;

	CBCGPControlRenderer	m_BackAddress;
	CBCGPControlRenderer	m_btnAddress;
	CBCGPToolBarImages      m_btnAddressSep;

	CBCGPControlRenderer	m_BackNavi[2];
	CBCGPToolBarImages		m_NaviControl[4];
	CBCGPControlRenderer	m_NaviProgressBack;	

	CMap<HWND, HWND, BOOL, BOOL>
							m_ActivateFlag;
};

#endif // !defined(AFX_MPVISUALMANAGER_H__423B8BA6_D991_4C1A_AF1B_DDA4B12CB1BC__INCLUDED_)
