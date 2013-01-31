//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of the BCGControlBar Library
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
// VisualManager.h: interface for the CVisualManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALMANAGER_H__E6A18CE1_7A0C_48D0_BAA0_A79336BC033D__INCLUDED_)
#define AFX_VISUALMANAGER_H__E6A18CE1_7A0C_48D0_BAA0_A79336BC033D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVisualManager : public CBCGPWinXPVisualManager  
{
	DECLARE_DYNCREATE(CVisualManager)

public:
	CVisualManager();
	virtual ~CVisualManager();

	virtual CSize GetCaptionButtonExtraBorder () const;

	virtual void OnDrawCaptionButton (CDC* pDC, CBCGPCaptionButton* pButton, BOOL bActive, BOOL bHorz, 
										BOOL bMaximized, BOOL bDisabled, int nImageID = -1);
	virtual COLORREF OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
		BOOL bActive, CRect rectCaption, CRect rectButtons);

	virtual void OnUpdateSystemColors ();

	virtual void OnFillButtonInterior (CDC* pDC,
		CBCGPToolbarButton* pButton, CRect rect, CBCGPVisualManager::BCGBUTTON_STATE state);

	virtual void OnDrawButtonBorder (CDC* pDC,
		CBCGPToolbarButton* pButton, CRect rect, CBCGPVisualManager::BCGBUTTON_STATE state);

	virtual void OnDrawSeparator (CDC* pDC, CBCGPBaseControlBar* pBar, CRect rect, BOOL bIsHoriz);

	virtual BOOL IsOffsetPressedButton () const
	{
		return FALSE;
	}

	virtual void OnDrawButtonSeparator (CDC* pDC,
		CBCGPToolbarButton* pButton, CRect rect, CBCGPVisualManager::BCGBUTTON_STATE state,
		BOOL bHorz);

private:
	BOOL IsAddressBarButton (CBCGPToolbarButton* pButton);

	CBCGPToolBarImages	m_BtnPin;
	CBCGPToolBarImages	m_BtnClose;
	CBCGPToolBarImages	m_BtnAddressBar [2];
	CBCGPToolBarImages	m_BtnMenuAddressBar [2];
};

#endif // !defined(AFX_VISUALMANAGER_H__E6A18CE1_7A0C_48D0_BAA0_A79336BC033D__INCLUDED_)
