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
// BCGPVisualManagerOffice10.h: interface for the CBCGPVisualManagerOffice10 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPVISUALMANAGEROFFICE10_H__5BC0C042_AC10_11D4_95C7_00A0C9289F1B__INCLUDED_)
#define AFX_BCGPVISUALMANAGEROFFICE10_H__5BC0C042_AC10_11D4_95C7_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGVisualManager.h"

class BCGCONTROLBARDLLEXPORT CBCGPVisualManagerOffice10 : public CBCGVisualManager  {
public:

	CBCGPVisualManagerOffice10();
	virtual ~CBCGPVisualManagerOffice10();

protected:
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

	CBrush	m_brGripperHorz;
	CBrush	m_brGripperVert;

	COLORREF	m_clrPlum;
	COLORREF	m_clrLight;
	COLORREF	m_clrSteel;

	CBrush		m_brPlum;
	CBrush		m_brLight;
	CBrush		m_brSteel;
};

#endif // !defined(AFX_BCGPVISUALMANAGEROFFICE10_H__5BC0C042_AC10_11D4_95C7_00A0C9289F1B__INCLUDED_)
