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
// mainfrm.h : interface of the CMainFrame class

#define CBCGPMDIFrameWnd	CBCGPMDIFrameWnd

class CDrawView;
#include "drawobj.h"

#define ID_FORMAT_CONTEXT_TAB	1

class CMainFrame : public CBCGPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	struct XStyle
	{
		COLORREF clrFill;
		COLORREF clrLine;
	};

public:
	CMainFrame();

// Attributes
public:
	CBCGPRibbonBar* GetRibbonBar () {return &m_wndRibbonBar;}

// Operations
public:
	void UpdateUI (CDrawView* pCurrView);
	void UpdateContextTab (CDrawView* pCurrView);
	void UpdateContextTabFromObject (CDrawObjList& list);

	COLORREF GetColorFromColorButton (int nButtonID);
	int GetWeightFromLineWeight (int nButtonID);
	BOOL GetStyleFromStyles (XStyle& style);

	void SetRibbonContextCategory (UINT uiCategoryID);
	void ActivateRibbonContextCategory (UINT uiCategoryID);

// Overrides
public:

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// control bar embedded members
	CBCGPRibbonStatusBar	m_wndStatusBar;
	CBCGPRibbonBar			m_wndRibbonBar;
	CBCGPRibbonMainButton	m_MainButton;

	// panel images
	CBCGPToolBarImages		m_PanelImages;

	// Document colors for demo:
	CList<COLORREF,COLORREF> m_lstMainColors;
	CList<COLORREF,COLORREF> m_lstAdditionalColors;
	CList<COLORREF,COLORREF> m_lstStandardColors;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	afx_msg void OnWindowManager();
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnHighlightRibbonListItem (WPARAM wp, LPARAM lp);
	afx_msg void OnToolsOptions();
	afx_msg void OnDummy();

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop);
	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);

	void ShowOptions (int nPage);
	void CreateDocumentColors ();

private:
	BOOL CreateRibbonBar ();
	BOOL CreateStatusBar ();

	void InitMainButton ();
	void InitHomeCategory ();
	void InitViewCategory ();
	void InitTabButtons ();

	void AddContextTab_Format ();

	void AdjustObjectSubmenu (CBCGPPopupMenu* pMenuPopup);
	void UpdateStatusBarCountPane (int nID, CString strText, int nCount);

	UINT	m_nAppLook;
};

/////////////////////////////////////////////////////////////////////////////
