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
#if !defined(AFX_RESOURCEPAGE_H__336866C1_4F49_4803_B555_E2D7320951B3__INCLUDED_)
#define AFX_RESOURCEPAGE_H__336866C1_4F49_4803_B555_E2D7320951B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResourcePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResourcePage dialog

class CResourcePage : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CResourcePage)

// Construction
public:
	CResourcePage();
	~CResourcePage();

// Dialog Data
	//{{AFX_DATA(CResourcePage)
	enum { IDD = IDD_OPTIONS_RES_PAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CResourcePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CResourcePage)
	afx_msg void OnHome();
	afx_msg void OnContact();
	afx_msg void OnProduct();
	afx_msg void OnSupport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESOURCEPAGE_H__336866C1_4F49_4803_B555_E2D7320951B3__INCLUDED_)
