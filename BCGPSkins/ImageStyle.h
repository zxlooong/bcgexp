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
// ImageStyle.h: interface for the CImageStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGESTYLE_H__C8AD9B11_B11B_4413_8825_CD3A4DAB2AF4__INCLUDED_)
#define AFX_IMAGESTYLE_H__C8AD9B11_B11B_4413_8825_CD3A4DAB2AF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageStyle : public CBCGPVisualManagerXP  
{
	DECLARE_DYNCREATE(CImageStyle)

public:
	CImageStyle();
	virtual ~CImageStyle();

	virtual void OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
									CRect rectClient, CRect rectClip,
									BOOL bNCArea = FALSE);
	virtual void OnEraseTabsArea (CDC* pDC, CRect rect, const CBCGPBaseTabWnd* pTabWnd);

	virtual COLORREF OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
		BOOL bActive, CRect rectCaption, CRect rectButtons);

	virtual COLORREF GetToolbarButtonTextColor (CBCGPToolbarButton* pButton,
												CBCGPVisualManagerXP::BCGBUTTON_STATE state);
	virtual void OnFillOutlookPageButton (CDC* pDC, const CRect& rect,
										BOOL bIsHighlighted, BOOL bIsPressed,
										COLORREF& clrText);

public:
	static CString	m_strImagePath;
	static BOOL		m_bIsInternalImage;
	static int		m_nHighlight;
	static COLORREF	m_clrText;

protected:
	CBitmap		m_bmpBack;
	CSize		m_sizeBmp;

	void FillArea (CDC* pDC, CRect rect, const CWnd* pWnd, BOOL bIsFloating, BOOL bNCArea);
};

#endif // !defined(AFX_IMAGESTYLE_H__C8AD9B11_B11B_4413_8825_CD3A4DAB2AF4__INCLUDED_)
