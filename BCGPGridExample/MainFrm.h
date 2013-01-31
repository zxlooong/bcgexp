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

#if !defined(AFX_MAINFRM_H__2715D3B6_162C_4BDC_BE39_6FBFE81A89E1__INCLUDED_)
#define AFX_MAINFRM_H__2715D3B6_162C_4BDC_BE39_6FBFE81A89E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CFrameWnd CBCGPFrameWnd

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	int GetCurrentViewType () const
	{
		return m_nCurrType - ID_SHORTCUT_1;
	}

	void UpdateCurrentView (int nViewType);
	void UpdateGrid ();

	CBCGPToolbarComboBoxButton* GetColorCombo ();
	void SetHiddenCommands (CList<UINT, UINT>& lstHiddenCommands);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
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
	CBCGPStatusBar			m_wndStatusBar;
	CBCGPExplorerToolBar	m_wndToolBar;
	CBCGPOutlookBar			m_wndShortcutsBar;
	CBCGPOutlookBarPane		m_wndShortcutsPane1;
	CBCGPOutlookBarPane		m_wndShortcutsPane2;
	CBCGPCaptionBar			m_wndCaptionBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGridTreeDlg();
	afx_msg void OnGridVirtualDlg();
	//}}AFX_MSG
	afx_msg void OnViewCustomize();
	afx_msg void OnOutlookBarShortcut(UINT id);
	afx_msg void OnUpdateOutlookBarShortcut (CCmdUI* pCmdUI);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateShortcutsBar ();

	UINT				m_nAppLook;
	UINT				m_nCurrType;
	CList<UINT, UINT>	m_lstHiddenCommands;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2715D3B6_162C_4BDC_BE39_6FBFE81A89E1__INCLUDED_)
