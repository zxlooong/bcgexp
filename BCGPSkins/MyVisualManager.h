//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2007 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MyVisualManager.h: interface for the CXPVisualManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYVISUALMANAGER_H__5BC0C042_AC10_11D4_95C7_00A0C9289F1B__INCLUDED_)
#define AFX_MYVISUALMANAGER_H__5BC0C042_AC10_11D4_95C7_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXPVisualManager : public CBCGVisualManager  
{
public:
	CXPVisualManager();
	virtual ~CXPVisualManager();

protected:
	virtual void OnUpdateSystemColors ();

	virtual void OnDrawBarGripper (CDC* pDC, CRect rectGripper, BOOL bHorz, CControlBar* pBar);
	virtual void OnFillBarBackground (CDC* pDC, CControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL bNCArea);
	virtual void OnDrawBarBorder (CDC* pDC, CControlBar* pBar, CRect& rect);
	virtual void OnDrawMenuBorder (CDC* pDC, CBCGPopupMenu* pMenu, CRect rect);
	virtual void OnDrawSeparator (CDC* pDC, CControlBar* pBar, CRect rect, BOOL bIsHoriz);
	
	virtual void OnFillButtonInterior (CDC* pDC,
		CBCGToolbarButton* pButton, CRect rect, CBCGVisualManager::BCGBUTTON_STATE state);

	virtual void OnDrawButtonBorder (CDC* pDC,
		CBCGToolbarButton* pButton, CRect rect, CBCGVisualManager::BCGBUTTON_STATE state);

	virtual void OnHighlightMenuItem (CDC*pDC, CBCGToolbarMenuButton* pButton,
		CRect rect, COLORREF& clrText);

	virtual void OnEraseTabsArea (CDC* pDC, CRect rect, const CBCGTabWnd* pTabWnd);
	virtual void OnDrawTab (CDC* pDC, CRect rectTab,
							int iTab, BOOL bIsActive, const CBCGTabWnd* pTabWnd);

	virtual void OnDrawCaptionButton (CDC* pDC, CBCGSCBButton* pButton,
									BOOL bHorz, BOOL bMaximized, BOOL bDisabled);

	CBrush	m_brGripperHorz;
	CBrush	m_brGripperVert;

	COLORREF	m_clrBarBkgnd;			// Control bar background color (expect menu bar)
	CBrush		m_brBarBkgnd;

	COLORREF	m_clrMenuLight;			// Color of the light menu area
	CBrush		m_brMenuLight;

	COLORREF	m_clrHighlight;			// Highlighted toolbar/menu item color
	CBrush		m_brHighlight;

	COLORREF	m_clrHighlightDn;		// Highlighted and pressed toolbar item color
	CBrush		m_brHighlightDn;

	COLORREF	m_clrHighlightChecked;
	CBrush		m_brHighlightChecked;
};

#endif // !defined(AFX_MYVISUALMANAGER_H__5BC0C042_AC10_11D4_95C7_00A0C9289F1B__INCLUDED_)
