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
#if !defined(AFX_VIRTUALGRIDDLG_H__D63AE30C_24F5_434A_9009_32BFA437CA64__INCLUDED_)
#define AFX_VIRTUALGRIDDLG_H__D63AE30C_24F5_434A_9009_32BFA437CA64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VirtualGridDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVirtualGridDlg dialog

class CVirtualGridDlg : public CDialog
{
// Construction
public:
	CVirtualGridDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVirtualGridDlg)
	enum { IDD = IDD_VIRTUAL_MODE };
	CStatic	m_wndGridLocation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVirtualGridDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVirtualGridDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBCGPGridCtrl	m_wndGrid;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIRTUALGRIDDLG_H__D63AE30C_24F5_434A_9009_32BFA437CA64__INCLUDED_)
