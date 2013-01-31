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
// MMStyleExample.h : main header file for the MMSTYLEEXAMPLE application
//

#if !defined(AFX_MMSTYLEEXAMPLE_H__97549C6F_F66F_4873_A98C_F1B2FDC9B607__INCLUDED_)
#define AFX_MMSTYLEEXAMPLE_H__97549C6F_F66F_4873_A98C_F1B2FDC9B607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleApp:
// See MMStyleExample.cpp for the implementation of this class
//

class CMMStyleExampleApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CMMStyleExampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMStyleExampleApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMMStyleExampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CMMStyleExampleApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MMSTYLEEXAMPLE_H__97549C6F_F66F_4873_A98C_F1B2FDC9B607__INCLUDED_)
