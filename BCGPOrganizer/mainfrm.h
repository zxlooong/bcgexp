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

#if !defined(AFX_MAINFRM_H__A7F5FB91_6B05_459C_A8BF_9D5EFCB90F7F__INCLUDED_)
#define AFX_MAINFRM_H__A7F5FB91_6B05_459C_A8BF_9D5EFCB90F7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OutlookBar.h"
#include "OutputBar.h"

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

	CCalendarBar* GetCalendar ()
	{
		return &m_wndOutlookBar.m_wndCalendarBar;
	}
	COutlookBar* GetOutlookBar ()
	{
		return &m_wndOutlookBar;
	}
	COutputBar* GetOutputBar ()
	{
		return &m_wndOutputBar;
	}

	CBCGPToolBarImages* GetTooltipImage (UINT uiID);

	COLORREF GetCalendarBackground () const;
	COLORREF GetGanttBackground () const;

	CBCGPRibbonSlider* GetZoomSlider ()
	{
		return m_pZoomSlider;
	}
	

// Operations
public:
	void SetDateInterval (const COleDateTime& date1, const COleDateTime& date2);
	void SetCaptionText (const CString& strText);

	void UpdateCalendar ()
	{
		GetCalendar ()->UpdateCalendar ();
	}

	void ActivateCategory (CBCGPRibbonCategory* pCategory);
	void SetActiveView (int nView);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRefresh();
	afx_msg void OnUpdateRefresh(CCmdUI* pCmdUI);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	afx_msg LRESULT OnActivateShortcut(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnActivateCategory(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateDummy(CCmdUI* pCmdUI);
	afx_msg void OnShortcutsHome();
	afx_msg void OnShortcutsMail();
	afx_msg void OnShortcutsDownload();
	afx_msg void OnShortcutsAbout();
	afx_msg void OnToolsOptions ();
	afx_msg void OnActivateView (UINT nID);
	afx_msg void OnUpdateActivateView (CCmdUI* pCmdUI);
	afx_msg void OnZoom100 ();
	afx_msg void OnZoom ();
	//}}AFX_MSG
	afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnHighlightRibbonListItem (WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	BOOL CreateRibbonBar ();
	BOOL CreateOutlookBar ();
	BOOL CreateCaptionBar ();
	BOOL CreateStatusBar ();
	void CreateDocumentColors ();

	void ShowOptions (int nPage);
	void SetKeys ();

	void AddMainCategory ();
	CBCGPRibbonCategory* AddTab_Shortcuts ();
	CBCGPRibbonCategory* AddTab_Mail ();
	CBCGPRibbonCategory* AddTab_Calendar ();
	CBCGPRibbonCategory* AddTab_Tasks ();
	CBCGPRibbonCategory* AddTab_Macros ();
	CBCGPRibbonCategory* AddTab_Gantt ();

protected:
	CBCGPRibbonBar			m_wndRibbonBar;	// Ribbon control bar
	CBCGPRibbonCategory*	m_pRibbonCategory[6];
	CBCGPRibbonMainButton	m_MainButton;	// Ribbon main button
	CBCGPRibbonStatusBar	m_wndStatusBar;
	COutlookBar				m_wndOutlookBar;
	CBCGPCaptionBar			m_wndCaptionBar;
	COutputBar				m_wndOutputBar;

	CBCGPToolBarImages		m_PanelImages;	// Ribbon panel images
											// (appear when pane is collapsed)

	CMap<UINT,UINT,CBCGPToolBarImages*,CBCGPToolBarImages*>
							m_TooltipImages;

	// Document colors:
	CList<COLORREF,COLORREF> m_lstMainColors;
	CList<COLORREF,COLORREF> m_lstAdditionalColors;
	CList<COLORREF,COLORREF> m_lstStandardColors;
	CList<COLORREF,COLORREF> m_lstCalendarColors;

	void ShowProgress (BOOL bShow = TRUE);

	CBitmap					m_bmpCaption;
	int						m_nProgressValue;
	BOOL					m_bInfiniteProgressMode;

	CBCGPRibbonColorButton*	m_pCalendarColors;
	CBCGPRibbonColorButton*	m_pGanttColors;
	CBCGPRibbonSlider*		m_pZoomSlider;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A7F5FB91_6B05_459C_A8BF_9D5EFCB90F7F__INCLUDED_)
