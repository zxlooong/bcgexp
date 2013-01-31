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
#if !defined(AFX_PAGE4_H__30996968_E024_4F26_8824_DC7D8A92340C__INCLUDED_)
#define AFX_PAGE4_H__30996968_E024_4F26_8824_DC7D8A92340C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage4 dialog

class CPage4 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPage4)

// Construction
public:
	CPage4();
	~CPage4();

// Dialog Data
	//{{AFX_DATA(CPage4)
	enum { IDD = IDD_PAGE4 };
	CBCGPMaskEdit	m_wndMaskEdit5;
	CBCGPMaskEdit	m_wndMaskEdit4;
	CBCGPMaskEdit	m_wndMaskEdit3;
	CBCGPMaskEdit	m_wndMaskEdit2;
	CBCGPMaskEdit	m_wndMaskEdit1;
	CString	m_strValue1;
	CString	m_strValue2;
	CString	m_strValue3;
	CString	m_strValue4;
	CString	m_strValue5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage4)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE4_H__30996968_E024_4F26_8824_DC7D8A92340C__INCLUDED_)
