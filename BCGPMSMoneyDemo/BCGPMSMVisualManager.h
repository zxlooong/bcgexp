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
#if !defined(AFX_BCGPMSMVISUALMANAGER_H__B23D1771_F72E_43D2_A3DD_E1343DB5A5DC__INCLUDED_)
#define AFX_BCGPMSMVISUALMANAGER_H__B23D1771_F72E_43D2_A3DD_E1343DB5A5DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPMSMVisualManager.h : header file
//

class CBCGPMSMVisualManager : public CBCGPVisualManager2003
{
	DECLARE_DYNCREATE(CBCGPMSMVisualManager)

// Construction
public:
	CBCGPMSMVisualManager();

	virtual ~CBCGPMSMVisualManager();

	virtual void BCGPMSMDrawCaptionButton (CDC* pDC, CRect rect, BCGBUTTON_STATE state, UINT id);

	void SetupMemoryBitmapSize (CDC* pDC, const CSize& size);

	BOOL LoadBCGPMSMCaptionButtonsIcons (LPCTSTR lpszID);

	const CSize& GetBCGPMSMCaptionButtonsSize () const;

protected:
	virtual void OnUpdateSystemColors ();

	virtual void OnDrawSeparator (CDC* pDC, CBCGPBaseControlBar* pBar,
							  CRect rect, BOOL bHorz);

	virtual COLORREF GetToolbarButtonTextColor (CBCGPToolbarButton* pButton,
										 CBCGPVisualManager::BCGBUTTON_STATE state);

	virtual void OnFillBarBackground (CDC* pDC, CBCGPBaseControlBar* pBar,
					 CRect rectClient, CRect rectClip, BOOL bNCArea = FALSE);

	virtual void OnFillHighlightedArea (CDC* pDC, CRect rect, 
						 CBrush* pBrush, CBCGPToolbarButton* pButton);

	virtual void OnDrawMenuBorder (CDC* pDC, CBCGPPopupMenu* pMenu, CRect rect);

	virtual void OnDrawButtonBorder (CDC* pDC,
						 CBCGPToolbarButton* pButton, CRect rect, BCGBUTTON_STATE state);

	virtual void OnHighlightMenuItem (CDC*pDC, CBCGPToolbarMenuButton* pButton,
								 CRect rect, COLORREF& clrText);

	virtual void OnDrawComboBorder (CDC* pDC, CRect rect,
									 BOOL bDisabled,
									 BOOL bIsDropped,
									 BOOL bIsHighlighted,
									 CBCGPToolbarComboBoxButton* pButton);

	virtual void OnDrawComboDropButton (CDC* pDC, CRect rect,
									 BOOL bDisabled,
									 BOOL bIsDropped,
									 BOOL bIsHighlighted,
									 CBCGPToolbarComboBoxButton* pButton);

	virtual void OnFillTasksPaneBackground(CDC* pDC, CRect rectWorkArea);
	virtual void OnFillTasksGroupInterior(CDC* /*pDC*/, CRect /*rect*/, BOOL /*bSpecial*/ = FALSE) {}
	virtual void OnDrawTasksGroupAreaBorder(CDC* /*pDC*/, CRect /*rect*/, BOOL /*bSpecial*/ = FALSE, BOOL /*bNoTitle*/ = FALSE) {}
	virtual void OnDrawTask(CDC* pDC, CBCGPTask* pTask, CImageList* pIcons, BOOL bIsHighlighted = FALSE, BOOL bIsSelected = FALSE);

private:
	CSize	   m_MemorySize;
	CDC 	   m_MemoryDC;
	CBitmap    m_MemoryBitmap;
	BOOL	   m_MemoryFilled;

	CImageList m_CaptionButtonIconst;
	CSize	   m_CaptionButtonSize;

	CBitmap    m_BCGPMSMFrameBitmap;
	CBitmap    m_BCGPMSMViewBitmap;

	CBrush	   m_brMenuBarButtonHighlighted;
	COLORREF   m_clrMenuBarButtonBorderHighlighted;

	COLORREF   m_clrMenuBarButtonTextRegular;
	COLORREF   m_clrMenuBarButtonTextPressed;
	COLORREF   m_clrMenuBarButtonTextHighlighted;

	COLORREF   m_clrToolBarButtonTextRegular;
	COLORREF   m_clrToolBarButtonTextPressed;
	COLORREF   m_clrToolBarButtonTextHighlighted;

	COLORREF   m_clrCategorieBarButtonTextRegular;
	COLORREF   m_clrCategorieBarButtonTextPressed;
	COLORREF   m_clrCategorieBarButtonTextHighlighted;

	COLORREF   m_clrToolBarSeparatorS;
	COLORREF   m_clrToolBarSeparatorM;
	COLORREF   m_clrToolBarSeparatorF;

	COLORREF   m_clrComboBoxBorder;

	COLORREF   m_clrComboBoxBtnRegularF;
	COLORREF   m_clrComboBoxBtnRegularL;
	COLORREF   m_clrComboBoxBtnRegularBorder;
	COLORREF   m_clrComboBoxBtnHighlightedF;
	COLORREF   m_clrComboBoxBtnHighlightedL;
	COLORREF   m_clrComboBoxBtnHighlightedBorder;
	COLORREF   m_clrComboBoxBtnPressedF;
	COLORREF   m_clrComboBoxBtnPressedL;
	COLORREF   m_clrComboBoxBtnPressedBorder;

	COLORREF   m_clrCategorieBarButtonBorder;
	COLORREF   m_clrCategorieBarButtonBorderM;
	COLORREF   m_clrCategorieBarButtonLine;
	COLORREF   m_clrCategorieBarButtonF;
	COLORREF   m_clrCategorieBarButtonL;

	CBrush	   m_brLinksBarBack;
	CBrush	   m_brLinksBarButtonHighlighted;
	COLORREF   m_clrLinksBarButtonBorderHighlighted;
};


inline
const CSize&
CBCGPMSMVisualManager::GetBCGPMSMCaptionButtonsSize () const
{
	return m_CaptionButtonSize;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMVISUALMANAGER_H__B23D1771_F72E_43D2_A3DD_E1343DB5A5DC__INCLUDED_)
