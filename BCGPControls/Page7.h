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
#if !defined(AFX_PAGE7_H__9B9FEE61_700A_426F_9CC6_572115A93FF7__INCLUDED_)
#define AFX_PAGE7_H__9B9FEE61_700A_426F_9CC6_572115A93FF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page7.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage7 dialog

class CPage7 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPage7)

// Construction
public:
	CPage7();
	~CPage7();

// Dialog Data
	//{{AFX_DATA(CPage7)
	enum { IDD = IDD_PAGE7 };
	CBCGPShellList	m_wndShellList;
	CBCGPShellTree	m_wbdShellTree;
	CString	m_strSelectedFolder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage7)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage7)
	afx_msg void OnSelectFolder();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE7_H__9B9FEE61_700A_426F_9CC6_572115A93FF7__INCLUDED_)
