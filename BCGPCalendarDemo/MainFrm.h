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

#if !defined(AFX_MAINFRM_H__308236A9_EAF6_4D4B_B43C_4B9589CCD1E0__INCLUDED_)
#define AFX_MAINFRM_H__308236A9_EAF6_4D4B_B43C_4B9589CCD1E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalendarBar.h"
#include "PropertyBar.h"

#define CFrameWnd CBCGPFrameWnd

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CBCGPCalendar* GetCalendar ()
	{
		return &m_wndCalendarBar.m_wndCalendars;
	}

	CPropertyBar& GetPropBar ()
	{
		return m_wndPropBar;
	}

	void UpdateCalendar ()
	{
		m_wndCalendarBar.UpdateCalendar ();
	}

// Operations
public:
	void SetDateInterval (const COleDateTime& date1, const COleDateTime& date2);
	void SetCaptionText (const CString& strText);

	CBCGPToolbarComboBoxButton* GetResourceCombo () const;

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
	CBCGPMenuBar	m_wndMenuBar;
	CBCGPStatusBar	m_wndStatusBar;
	CBCGPToolBar	m_wndToolBar;
	CBCGPToolBar	m_wndPlannerToolBar;
	CBCGPToolBar	m_wndPlannerMultiToolBar;
	CCalendarBar	m_wndCalendarBar;
	CPropertyBar	m_wndPropBar;
	CBCGPCaptionBar	m_wndCaptionBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimeChange();
	afx_msg void OnViewCustomize();
	afx_msg void OnViewCalendarBar();
	afx_msg void OnUpdateViewCalendarBar(CCmdUI* pCmdUI);
	afx_msg void OnViewPropBar();
	afx_msg void OnUpdateViewPropBar(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnViewPlannerBar();
	afx_msg void OnUpdateViewPlannerBar(CCmdUI* pCmdUI);
	afx_msg void OnViewPlannerMultiBar();
	afx_msg void OnUpdateViewPlannerMultiBar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);

	UINT	m_nAppLook;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__308236A9_EAF6_4D4B_B43C_4B9589CCD1E0__INCLUDED_)
