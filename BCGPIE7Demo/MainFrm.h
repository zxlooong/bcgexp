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
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__94D15405_9DF5_48FA_B9A6_4CB1285144EA__INCLUDED_)
#define AFX_MAINFRM_H__94D15405_9DF5_48FA_B9A6_4CB1285144EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MenuBar.h"
#include "LinksBar.h"
#include "ExplorerBar.h"

#include "TabBar.h"

#define CMDIFrameWnd CBCGPMDIFrameWnd

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
		
	friend class CChildFrame;

public:
	CMainFrame();

// Attributes
public:

// Operations
public:

	CHtmlView* GetActiveHTML() const;
	void SetAddress(LPCTSTR lpszUrl);
	void StartAnimation();
	void SetProgress (long nCurr, long nTotal);

	void Navigate(LPCTSTR lpszUrl);

	BOOL IsFavoritesMenu (const CBCGPToolbarMenuButton* pMenuButton);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPExplorerToolBar	m_wndAddressBar;
	CBCGPStatusBar			m_wndStatusBar;
	CBCGPReBar				m_wndReBar;
	CMenuBar				m_wndMenuBar;
	CLinksBar				m_wndLinksBar;
	CExplorerBar			m_wndExplorer;

	CMenu					m_menuFavotites;
	BOOL					m_bMainToolbarMenu;

	CTabBar					m_wndTabBar;

// Generated message map functions
protected:
	virtual BOOL OnDrawMenuImage (CDC* pDC,
									const CBCGPToolbarMenuButton* pMenuButton, 
									const CRect& rectImage);	
	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);
	virtual BOOL OnMenuButtonToolHitTest (CBCGPToolbarButton* pButton, TOOLINFO* pTI);
	virtual BOOL GetToolbarButtonToolTipText (CBCGPToolbarButton* pButton, CString& strTTText);

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg void OnWindowManager();
	afx_msg void OnViewMenuBar();
	afx_msg void OnUpdateViewMenuBar(CCmdUI* pCmdUI);
	afx_msg void OnViewLinksBar();
	afx_msg void OnUpdateViewLinksBar(CCmdUI* pCmdUI);
	afx_msg void OnNewTab();
	afx_msg void OnNewWindow();
	afx_msg void OnFileOpen();
	afx_msg void OnFavorite(UINT nID);
	afx_msg void OnHistory(UINT nID);
	afx_msg void OnViewFavorites();
	afx_msg void OnUpdateViewFavorites(CCmdUI* pCmdUI);
	afx_msg void OnViewHistory();
	afx_msg void OnUpdateViewHistory(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLink(CCmdUI* pCmdUI);
	afx_msg void OnHelpWebTutorial();
	afx_msg void OnHelpOnlineSupport();
	afx_msg void OnHelpSendFeedback();
	afx_msg void OnWorkOffline();
	afx_msg void OnUpdateWorkOffline(CCmdUI* pCmdUI);
	afx_msg void OnFullScreen();
	afx_msg void OnViewUseLargeIcons();
	afx_msg void OnUpdateViewUseLargeIcons(CCmdUI* pCmdUI);
	afx_msg void OnAddFavoritesMenu();
	afx_msg LRESULT OnMDIActivate (WPARAM wParam, LPARAM);
	afx_msg LRESULT OnDWMCompositionChanged(WPARAM,LPARAM);
	//}}AFX_MSG
	afx_msg void OnAddress();
	afx_msg void OnSearch ();
	DECLARE_MESSAGE_MAP()

	virtual CBCGPMDIChildWnd* CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/);
public:
	afx_msg void OnToolbarLockthetoolbars();
	afx_msg void OnUpdateToolbarLockthetoolbars(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__94D15405_9DF5_48FA_B9A6_4CB1285144EA__INCLUDED_)
