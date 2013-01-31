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

#if !defined(AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_)
#define AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CMDIFrameWnd CBCGPMDIFrameWnd

#include "WatchBar.h"
#include "ClassViewBar.h"
#include "ResourceView.h"
#include "FileViewBar.h"
#include "OutputView.h"
#include "DynamicHelpView.h"
#include "PropertiesViewBar.h"
#include "ToolBox.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	void OnChangeLook (BOOL bOneNoteTabs, BOOL bMDITabColors, BOOL bIsVSDotNetLook, 
		BOOL bDockTabColors, BOOL bMDITabsVS2005Look, BOOL bIsToolBoxEx,
		BOOL bActiveTabCloseButton);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	virtual CBCGPMDIChildWnd* CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* pObj);
	virtual BOOL OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop);

// Implementation
public:
	static CBCGPToolbarComboBoxButton* GetFindCombo();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPStatusBar			m_wndStatusBar;
	CBCGPToolBar			m_wndToolBar;
	CBCGPToolBar			m_wndToolbarBuild;
	CBCGPToolBar			m_wndToolbarEdit;
	CBCGPDropDownToolBar	m_wndToolbarResource;

	CClassViewBar			m_wndClassView;
	CResourceViewBar		m_wndResourceView;
	CFileViewBar			m_wndFileView;

	CDynamicHelpViewBar		m_wndDynamicHelpView;
	COutputViewBar			m_wndOutputView;
	CPropertiesViewBar		m_wndPropertiesBar;

	CBCGPDockingControlBar*	m_pWndToolBoxBar;
	BOOL					m_bIsToolBoxEx;

	CWatchBar				m_wndWatchBar;

	CBCGPToolBarImages		m_UserImages;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnHelpKeyboardmap();
	afx_msg void OnFileNewProject();
	afx_msg void OnFileNewBlankSolution();
	afx_msg void OnFileOpenSolution();
	afx_msg void OnFileCloseSolution();
	afx_msg void OnFileSaveAll();
	afx_msg void OnViewRefresh();
	afx_msg void OnToolsConnectToDatabase();
	afx_msg void OnToolsDebugProcesses();
	afx_msg void OnViewFullScreen();
	afx_msg void OnToolsOptions();
	afx_msg void OnHelpWeb();
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	afx_msg void OnClose();
	afx_msg void OnViewClass();
	afx_msg void OnUpdateViewClass(CCmdUI* pCmdUI);
	afx_msg void OnViewFile();
	afx_msg void OnUpdateViewFile(CCmdUI* pCmdUI);
	afx_msg void OnViewResource();
	afx_msg void OnUpdateViewResource(CCmdUI* pCmdUI);
	afx_msg void OnViewProperties();
	afx_msg void OnUpdateViewProperties(CCmdUI* pCmdUI);
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI* pCmdUI);
	afx_msg void OnViewWatch();
	afx_msg void OnUpdateViewWatch(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbox();
	afx_msg void OnUpdateViewToolbox(CCmdUI* pCmdUI);
	afx_msg void OnViewDynamichelp();
	afx_msg void OnUpdateViewDynamichelp(CCmdUI* pCmdUI);
	afx_msg void OnMdiTabbedDocument();
	afx_msg void OnUpdateMdiTabbedDocument(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnGetTabToolTip(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp);
	LRESULT OnToolbarCreateNew(WPARAM wp,LPARAM lp);
	afx_msg void OnToolBox();
	afx_msg void OnUpdateCaretPos(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingBars ();
	void SetDockingBarsIcons (BOOL bHiColorIcons);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1E4CD94D_CB6E_4FAD_9DDE_3E2B96D11CE2__INCLUDED_)
