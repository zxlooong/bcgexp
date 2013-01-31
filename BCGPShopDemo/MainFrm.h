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

#if !defined(AFX_MAINFRM_H__7C0D4277_DC67_4289_BC82_0B9FAB2472BA__INCLUDED_)
#define AFX_MAINFRM_H__7C0D4277_DC67_4289_BC82_0B9FAB2472BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Palette.h"
#include "ContextToolbar.h"

#define  WM_SETACTIVECOLOR  WM_APP
    // Application-defined message. Notifies main frame that one of active colors (left or right) has been changed.
    // wParam is 0 for left color or 1 for right. lParam specifies a new color value as COLORREF.

class CShopToolbarColorPicker;

class CMainFrame : public CBCGPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
    CShopToolbarColorPicker* GetColorPickerToolButton () const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CShopToolBase         m_wndPanel1;
    CShopToolBase         m_wndPanel2;
    CShopToolBase         m_wndPanel3;
    CShopToolBase         m_wndPanel4;
    CShopToolBase         m_wndPanel5;

    CToolPalette          m_wndToolPalette;
    CBCGPDropDownToolBar  m_wndToolSelect;
    CBCGPDropDownToolBar  m_wndToolLasso;

    CBCGPMenuBar          m_wndMenuBar;
    CContextToolbar       m_wndContextToolBar;

    // Creates tool panel by its ID if it does not exist.
    CShopToolBase*  CreatePanelByID(UINT id);

    // Returns a pointer to the tool panel associated with specified id or NULL if it does not exist.
    CShopToolBase*  GetToolPanelByID(UINT id);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnUpdateAlwaysEnabledButtons(CCmdUI* pCmdUI);
    afx_msg void OnSetToolBarColumns(UINT nID);
    afx_msg void OnCheckToolBarButton(UINT nID);
    afx_msg void OnUpdateViewTabPanels(CCmdUI *pCmdUI);
    afx_msg void OnViewTabPanels(UINT nID);
    afx_msg LRESULT OnSetActiveColor(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7C0D4277_DC67_4289_BC82_0B9FAB2472BA__INCLUDED_)
