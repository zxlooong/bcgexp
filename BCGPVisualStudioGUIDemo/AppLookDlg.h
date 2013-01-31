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
#if !defined(AFX_APPLOOKDLG_H__5B2B5394_3611_49AE_B2B6_F84D14BC5189__INCLUDED_)
#define AFX_APPLOOKDLG_H__5B2B5394_3611_49AE_B2B6_F84D14BC5189__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppLookDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg dialog

class CAppLookDlg : public CDialog
{
// Construction
public:
	CAppLookDlg(BOOL bStartup, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAppLookDlg)
	enum { IDD = IDD_APP_LOOK };
	CComboBox	m_wndStyle;
	CButton	m_wndRoundedTabs;
	CButton	m_wndDockTabColors;
	CButton	m_wndOneNoteTabs;
	CButton	m_wndOK;
	CButton	m_wndCancel;
	BOOL	m_bShowAtStartup;
	BOOL	m_bOneNoteTabs;
	BOOL	m_bDockTabColors;
	BOOL	m_bRoundedTabs;
	BOOL	m_bCustomTooltips;
	int		m_nAppLook;
	int		m_nStyle;
	BOOL	m_bActiveTabCloseButton;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppLookDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppLookDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnApply();
	afx_msg void OnAppLook();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	const BOOL	m_bStartup;

	void SetLook ();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLOOKDLG_H__5B2B5394_3611_49AE_B2B6_F84D14BC5189__INCLUDED_)
