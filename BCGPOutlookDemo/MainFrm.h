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

#if !defined(AFX_MAINFRM_H__EE0C81ED_53C5_49C1_AEA9_08ED849A24D0__INCLUDED_)
#define AFX_MAINFRM_H__EE0C81ED_53C5_49C1_AEA9_08ED849A24D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CFrameWnd CBCGPFrameWnd

#include "FolderListBar.h"
#include "CalendarBar.h"

class CWorkspaceObj;

class CMyOutlookBar : public CBCGPOutlookBar
{
	virtual BOOL AllowShowOnControlMenu () const;
	virtual void GetBarName (CString& strName) const
	{
		strName = _T("Outlook Bar");
	}
};

class CShellTree : public CBCGPShellTree
{
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
	{
		BOOL bRes = CBCGPShellTree::OnNotify(wParam, lParam, pResult);

		NMHDR* pNMHDR = (NMHDR*)lParam;
		ASSERT (pNMHDR != NULL);

		if (pNMHDR->code == TTN_SHOW && GetToolTips () != NULL)
		{
			GetToolTips ()->SetWindowPos (&wndTop, -1, -1, -1, -1,
				SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
		}

		return bRes;
	}
};

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	BOOL IsOutlookBar2003 () const
	{
		return m_bOutlookBar2003;
	}

// Operations
public:
	void SetWorkSpace (CWorkspaceObj* pWorkSpace);
	void OnCloseFoldersPopup (BOOL bKeep);
	virtual void AdjustDockingLayout (HDWP hdwp = NULL);

	void OnChangeLook (BOOL bOutlookBar2003);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPMenuBar		m_wndMenuBar;
	CBCGPStatusBar		m_wndStatusBar;

	CImageList			m_imlStatusAnimation;

	CBCGPToolBar		m_wndToolBar;
	CBCGPToolBar		m_wndToolBarAdvanced;
	CBCGPToolBar		m_wndToolBarWeb;

	CMyOutlookBar		m_wndBarOutlook;
	CMyOutlookBar		m_wndBarOutlook2003;

	// Outlook bar panes:
	CBCGPOutlookBarPane	m_wndOutlookPane1;
	CBCGPOutlookBarPane	m_wndOutlookPane2;
	CShellTree			m_wndTree;
	CCalendarBar		m_wndCalendar;

	// Outlook bar-2003 panes:
	CBCGPOutlookBarPane	m_wndOutlookPane12003;
	CBCGPOutlookBarPane	m_wndOutlookPane22003;
	CShellTree			m_wndTree2003;
	CCalendarBar		m_wndCalendar2003;

	UINT				m_uiHilightedPage;

	CBCGPCaptionBar		m_wndCaption;

	CFolderListBar		m_wndFolderList;

	CBCGPSplitterWnd	m_wndSplitter;

	CBCGPToolBarImages	m_UserImages;
	CImageList			m_ImagesSmall;

	CObList				m_lstWorkspaces;	// List of CWorkspaceObj
	CWorkspaceObj*		m_pCurrWorkSpace;

	BOOL				m_bOutlookBar2003;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnOutlookAddPage();
	afx_msg void OnOutlookAnimation();
	afx_msg void OnOutlookDeletePage();
	afx_msg void OnOutlookRenamePage();
	afx_msg void OnOutlookShowTextLabels();
	afx_msg void OnUpdateOutlookRenamePage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOutlookDeletePage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOutlookAnimation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOutlookShowTextLabels(CCmdUI* pCmdUI);
	afx_msg void OnResetPage();
	afx_msg void OnUpdateResetPage(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnUpdateOutlookAddPage(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnEnable( BOOL bEnable );
	afx_msg void OnViewCaptionbar();
	afx_msg void OnUpdateViewCaptionbar(CCmdUI* pCmdUI);
	afx_msg void OnViewFolderList();
	afx_msg void OnUpdateViewFolderList(CCmdUI* pCmdUI);
	afx_msg void OnViewOutlookbar();
	afx_msg void OnUpdateViewOutlookbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarCreateNew(WPARAM,LPARAM);
	afx_msg void OnUpdateIndicatorSendReceive (CCmdUI* pCmdUI);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg void OnViewWorkSpace (UINT ud);
	afx_msg void OnViewMyComputer();
	afx_msg void OnViewFoldersPopup();
	DECLARE_MESSAGE_MAP()

	BOOL CreateOutlookBar (CBCGPOutlookBar& bar, UINT uiID,
		CBCGPOutlookBarPane& pane1, CBCGPOutlookBarPane& pane2,
		CBCGPShellTree& tree, CCalendarBar& calendar,
		int nInitialWidth);
	BOOL CreateCaptionBar ();

	void SetBasicCommands ();

	void AddWorkSpace (const CString& strName, const int iIconIndex, const UINT uiCmd,
				   CBCGPOutlookBarPane& pane, const UINT uiNewCmdID,
				   CImageList& images);
	int FindFocusedOutlookWnd (CBCGPOutlookWnd** ppOutlookWnd);
	CBCGPOutlookWnd* FindOutlookParent (CWnd* pWnd);
	CBCGPOutlookWnd* m_pCurrOutlookWnd;

	CBCGPOutlookBarPane* m_pCurrOutlookPage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EE0C81ED_53C5_49C1_AEA9_08ED849A24D0__INCLUDED_)
