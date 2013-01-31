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
// MacStyle.h: interface for the CMacStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MACSTYLE_H__6D93BBDC_8E86_467D_9024_64B691FE0408__INCLUDED_)
#define AFX_MACSTYLE_H__6D93BBDC_8E86_467D_9024_64B691FE0408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMacStyle : public CBCGPVisualManagerXP  
{
	DECLARE_DYNCREATE(CMacStyle)

public:
	CMacStyle();
	virtual ~CMacStyle();

protected:
	virtual void OnDrawBarGripper (CDC* pDC, CRect rectGripper, BOOL bHorz, CBCGPBaseControlBar* pBar);
	virtual void OnDrawMenuBorder (CDC* pDC, CBCGPPopupMenu* pMenu, CRect rect);
	virtual void OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL bNCArea);
	virtual void OnEraseTabsArea (CDC* pDC, CRect rect, const CBCGPBaseTabWnd* pTabWnd);
	virtual void OnDrawSeparator (CDC* pDC, CBCGPBaseControlBar* pBar, CRect rect, BOOL bIsHoriz);
	
	virtual void OnFillButtonInterior (CDC* pDC,
		CBCGPToolbarButton* pButton, CRect rect, CBCGPVisualManagerXP::BCGBUTTON_STATE state);

	virtual void OnDrawButtonBorder (CDC* pDC,
		CBCGPToolbarButton* pButton, CRect rect, CBCGPVisualManagerXP::BCGBUTTON_STATE state);

	virtual void OnDrawCaptionButton (CDC* pDC, CBCGPCaptionButton* pButton, BOOL bActive, BOOL bHorz, BOOL bMaximized, BOOL bDisabled);
	virtual COLORREF OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
		BOOL bActive, CRect rectCaption, CRect rectButtons);

	virtual COLORREF GetToolbarButtonTextColor (CBCGPToolbarButton* pButton,
												CBCGPVisualManagerXP::BCGBUTTON_STATE state);

	virtual void OnFillOutlookPageButton (CDC* pDC, const CRect& rect,
										BOOL bIsHighlighted, BOOL bIsPressed,
										COLORREF& clrText);
	virtual void OnDrawOutlookPageButtonBorder (CDC* pDC, CRect& rectBtn, BOOL bIsHighlighted, BOOL bIsPressed);
	virtual void OnDrawStatusBarPaneBorder (CDC* pDC, CBCGPStatusBar* pBar,
					CRect rectPane, UINT uiID, UINT nStyle);
	virtual void OnDrawStatusBarSizeBox (CDC* pDC, CBCGPStatusBar* pStatBar,
				CRect rectSizeBox);

	void DrawNcBtn (CDC* pDC, const CRect& rect, UINT nButton, 
							BCGBUTTON_STATE state, BOOL bActive);
	void DrawNcText (CDC* pDC, CRect& rect, const CString& strTitle, 
							BOOL bActive, BOOL bIsRTL, BOOL bTextCenter);
	void DrawNcCaption (CDC* pDC, CRect rectCaption, 
							DWORD dwStyle, DWORD dwStyleEx,
							const CString& strTitle,
							HICON hIcon, BOOL bActive, BOOL bTextCenter,
							const CObList& lstSysButtons);

	virtual BOOL IsOwnerDrawCaption ()	{	return !globalData.DwmIsCompositionEnabled ();	}
	virtual BOOL OnNcActivate (CWnd* pWnd, BOOL bActive);
	virtual BOOL OnNcPaint (CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw);
	virtual BOOL OnSetWindowRegion (CWnd* pWnd, CSize sizeWindow);

	CSize	GetSystemBorders () const;
	virtual CSize	GetNcBtnSize (BOOL bSmall) const;

	COLORREF m_crFace;
	COLORREF m_crShadow;
	COLORREF m_crHilight;

	CBrush  m_brOutlook;
	CBrush	m_brFace;
	CBrush	m_brHighlight;

	CPen	m_penGripper1;
	CPen	m_penGripper2;

	CBCGPControlRenderer	m_ctrlMainBorder;
	CBCGPControlRenderer	m_ctrlMainBorderCaption;

	CBCGPControlRenderer	m_ctrlBtn;
	CBCGPControlRenderer	m_ctrlStatusBarBack;
	CBCGPControlRenderer	m_ctrlStatusBarPaneBorder;
	CBCGPToolBarImages		m_StatusBarSizeBox;

	CBCGPControlRenderer    m_ctrlSysBtnBack;
	CBCGPToolBarImages      m_SysBtnClose;
	CBCGPToolBarImages      m_SysBtnRestore;
	CBCGPToolBarImages      m_SysBtnMaximize;
	CBCGPToolBarImages      m_SysBtnMinimize;

	BOOL	m_bActive;
	CFont   m_AppCaptionFont;
};

#endif // !defined(AFX_MACSTYLE_H__6D93BBDC_8E86_467D_9024_64B691FE0408__INCLUDED_)
