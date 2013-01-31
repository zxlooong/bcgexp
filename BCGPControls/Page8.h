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
#if !defined(AFX_PAGE8_H__FFF017D4_497E_4FB3_BF73_A80960133655__INCLUDED_)
#define AFX_PAGE8_H__FFF017D4_497E_4FB3_BF73_A80960133655__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page8.h : header file
//

class CMyCalc : public CBCGPCalculator
{ 
	virtual void OnUserCommand (UINT uiCmd);
};

class CMyEdit : public CBCGPEdit
{
	virtual void OnCalculatorUserCommand (CBCGPCalculator* pCalculator, UINT uiCmd);
};

/////////////////////////////////////////////////////////////////////////////
// CPage8 dialog

class CPage8 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPage8)

// Construction
public:
	CPage8();
	~CPage8();

// Dialog Data
	//{{AFX_DATA(CPage8)
	enum { IDD = IDD_PAGE8 };
	CMyEdit	m_wndEdit;
	CStatic	m_wndCalcRect;
	double	m_dblValue;
	BOOL	m_bUserCommands;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage8)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage8)
	virtual BOOL OnInitDialog();
	afx_msg void OnUserCommands();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CMyCalc	m_wndCalc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE8_H__FFF017D4_497E_4FB3_BF73_A80960133655__INCLUDED_)
