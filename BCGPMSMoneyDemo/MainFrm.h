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

#if !defined(AFX_MAINFRM_H__675129D0_A332_436E_8259_EB6714C84A3E__INCLUDED_)
#define AFX_MAINFRM_H__675129D0_A332_436E_8259_EB6714C84A3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCGPMSMCaptionBar.h"
#include "BCGPMSMMenuBar.h"
#include "BCGPMSMToolBar.h"
#include "BCGPMSMTasksPane.h"
#include "BCGPMSMCategorieBar.h"
#include "BCGPMSMLinksBar.h"

#include <BCGPDockBar.h>

#define CFrameWnd CBCGPFrameWnd

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();

	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CMainFrame();

	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg void OnUpdateGoAddressEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBackward1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBackward2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateForward1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateForward2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCustomize(CCmdUI* pCmdUI);
	afx_msg void OnCategorie(UINT nID);
	afx_msg void OnUpdateCategorie(CCmdUI* pCmdUI);
	afx_msg void OnLinks(UINT nID);
	afx_msg void OnUpdateLinks(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnHelpBcgsoft();
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetupMemoryBitmapSize (const CSize& sz);

	CBCGPMSMLinksBar*	 GetLinksBar (UINT nID);

	CBCGPMSMCaptionBar	 m_wndCaptionBar;
	CBCGPMSMMenuBar 	 m_wndMenuBar;
	CBCGPMSMToolBar 	 m_wndToolBar;
	CBCGPMSMCategorieBar m_wndCategorieBar;
	CBCGPMSMLinksBar	 m_wndLinksBars[8];
	CBCGPMSMTasksPane	 m_wndTaskPane;

	CMenu				 m_menuFavotites;

	BOOL				 m_bIsHighColor;
	BOOL				 m_bMainToolbarMenu;

	UINT				 m_nCategorie;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__675129D0_A332_436E_8259_EB6714C84A3E__INCLUDED_)
