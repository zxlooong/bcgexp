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

#if !defined(AFX_MAINFRM_H__D8DF7DCE_BECB_4A0A_A6EA_305CABE1AAB0__INCLUDED_)
#define AFX_MAINFRM_H__D8DF7DCE_BECB_4A0A_A6EA_305CABE1AAB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExplorerBar.h"
#include "NavigationBar.h"
#include "ColorChooserBar.h"
#include "EqualizerBar.h"

#define CFrameWnd CBCGPFrameWnd

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CNavigationBar& GetNavigationBar ()
	{
		return m_wndNavigationBar;
	}

// Operations
public:

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
	CExplorerBar				m_wndExplorerBar;
	CNavigationBar			m_wndNavigationBar;
	CColorChooserBar		m_wndColorChooserBar;
	CEqualizerBar			m_wndEqualizerBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnViewColorChooser();
	afx_msg void OnUpdateViewColorChooser(CCmdUI* pCmdUI);
	afx_msg void OnViewEqualizer();
	afx_msg void OnUpdateViewEqualizer(CCmdUI* pCmdUI);
	afx_msg void OnColorChooserReset();
	afx_msg void OnColorChooserPresetPrev();
	afx_msg void OnColorChooserPresetNext();
	afx_msg void OnExplorerWeb();
	//}}AFX_MSG
	afx_msg LRESULT OnDWMCompositionChanged(WPARAM,LPARAM);
	afx_msg LRESULT OnAfterUpdateCaption(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D8DF7DCE_BECB_4A0A_A6EA_305CABE1AAB0__INCLUDED_)
