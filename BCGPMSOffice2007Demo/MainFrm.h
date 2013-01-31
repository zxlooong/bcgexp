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
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__CF400043_4CD2_41E4_80C1_5580326AEBA7__INCLUDED_)
#define AFX_MAINFRM_H__CF400043_4CD2_41E4_80C1_5580326AEBA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClipboardPane.h"
#include "RibbonListButton.h"

class CMainFrame : public CBCGPFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CBCGPRibbonBar* GetRibbonBar ()
	{
		return &m_wndRibbonBar;
	}

	CBCGPRibbonStatusBar* GetRibbonStatusBar ()
	{
		return &m_wndStatusBar;
	}

	CScrollBar* GetScrollBar ()
	{
		return &m_wndScrollBar;
	}

// Operations
public:
	CBCGPToolBarImages* GetTooltipImage (UINT uiID);
	
	void SetRibbonContextCategory (UINT uiCategoryID);
	void ActivateRibbonContextCategory (UINT uiCategoryID);

	void OnChangeLayout (CWnd* pWnd = NULL, BOOL bNoLoopOverPopup = FALSE);

protected:
	void AddMainCategory ();

	void AddTab_Home ();
	void AddTab_Insert ();
	void AddTab_PageLayout ();
	void AddTab_References ();
	void AddTab_Mailings ();
	void AddTab_Review ();
	void AddTab_View ();
	void AddTab_Developer ();

	void AddContextTab_Picture ();
	void AddContextTab_Chart ();
	void AddContextTab_Table ();
	
	CBCGPRibbonPanel* AddPanelArrange (CBCGPRibbonCategory* pCategory, 
					UINT imageP, UINT imageS, UINT imageL);

	void InitBulletPalette (CBCGPRibbonPaletteButton* pPalette);
	void InitNumberingPalette (CBCGPRibbonPaletteButton* pPalette);
	void InitMultilevelPalette (CBCGPRibbonPaletteButton* pPalette);
	void InitPositionPalette (CBCGPRibbonPaletteButton* pPalette);

	void SetKeys ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	virtual void AdjustClientArea ();
	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPRibbonBar			m_wndRibbonBar;	// Ribbon control bar
	CBCGPRibbonMainButton	m_MainButton;	// Ribbon main button
	CClipboardPane			m_wndClipboardPane;
	CBCGPRibbonStatusBar	m_wndStatusBar;
	CBCGPCaptionBar			m_wndMessageBar;

	CBCGPToolBarImages		m_PanelImages;	// Ribbon panel images
											// (appear when pane is collapsed)

	CMap<UINT,UINT,CBCGPToolBarImages*,CBCGPToolBarImages*>
							m_TooltipImages;

	void CreateDocumentColors ();
	void CreateStyleList ();
	void CreateThemeList ();
	void CreateFontsList ();
	void CreateLookColor ();

	void ShowProgress (BOOL bShow = TRUE);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnWriteClipboard();
	afx_msg void OnUpdateWriteClipboard(CCmdUI* pCmdUI);
	afx_msg void OnViewRtl();
	afx_msg void OnUpdateViewRtl(CCmdUI* pCmdUI);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnViewApplookCustomColor();
	//}}AFX_MSG
	afx_msg void OnRefresh();
	afx_msg void OnSpell();
	afx_msg void OnUpdateRefresh(CCmdUI* pCmdUI);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	afx_msg void OnToolsOptions ();
	afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	afx_msg void OnLink();
	afx_msg LRESULT OnHighlightRibbonListItem (WPARAM wp, LPARAM lp);
	afx_msg void OnViewMessageBar();
	afx_msg void OnUpdateViewMessageBar(CCmdUI* pCmdUI);
	afx_msg LRESULT OnShowRibbonItemMenu(WPARAM wp, LPARAM lp);
	afx_msg void OnDummy(UINT id);	
	afx_msg void OnZoom();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnClipboardPasteAll();
	afx_msg void OnClipboardClearAll();
	afx_msg void OnClipboardOption1();
	afx_msg void OnClipboardOption2();
	afx_msg LRESULT OnCustomizeGalleryContextMenu(WPARAM wp, LPARAM lp);
	afx_msg void OnCopyColor();
	DECLARE_MESSAGE_MAP()

	BOOL CreateRibbonBar ();
	BOOL CreateStatusBar ();
	BOOL CreateMessageBar ();

	void ShowOptions (int nPage);

	CBCGPScrollBar	m_wndScrollBar;

	CBCGPControlRenderer m_Pat[4];

	CRect		m_rectFill;
    CBitmap		m_MemBitmap;
	CRect		m_rectSizing;

	int			m_nProgressValue;
	BOOL		m_bInfiniteProgressMode;

	// Document colors for demo:
	CList<COLORREF,COLORREF> m_lstMainColors;
	CList<COLORREF,COLORREF> m_lstAdditionalColors;
	CList<COLORREF,COLORREF> m_lstStandardColors;

	// Theme names for demo:
	CStringArray	m_arStyles;
	CStringArray	m_arThemes;
	CStringArray	m_arColorThemes;
	CStringArray	m_arStyleSets;
	CRibbonListFontButton::XItems m_arFonts;

	CBCGPRibbonColorButton* m_pLookColor;

	COLORREF		m_clrHighlighted;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CF400043_4CD2_41E4_80C1_5580326AEBA7__INCLUDED_)
