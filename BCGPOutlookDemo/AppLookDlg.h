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
#if !defined(AFX_APPLOOKDLG_H__5E5DD121_FBA2_4B84_92A7_32A9B7788FF2__INCLUDED_)
#define AFX_APPLOOKDLG_H__5E5DD121_FBA2_4B84_92A7_32A9B7788FF2__INCLUDED_

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
	CComboBox	m_wndStyle2007;
	CButton	m_wndOutlookBar2003;
	CButton	m_wndOK;
	CButton	m_wndCancel;
	int		m_nAppLook;
	BOOL	m_bShowAtStartup;
	BOOL	m_bOutlookBar2003;
	int		m_nStyle2007;
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

#endif // !defined(AFX_APPLOOKDLG_H__5E5DD121_FBA2_4B84_92A7_32A9B7788FF2__INCLUDED_)
