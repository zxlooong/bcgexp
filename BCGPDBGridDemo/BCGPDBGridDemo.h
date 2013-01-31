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
// BCGPDBGridDemo.h : main header file for the BCGPDBGRIDDEMO application
//

#if !defined(AFX_BCGPDBGRIDDEMO_H__E1FAA510_8B09_4352_A9AE_88D81063C209__INCLUDED_)
#define AFX_BCGPDBGRIDDEMO_H__E1FAA510_8B09_4352_A9AE_88D81063C209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPDBGridDemoApp:
// See BCGPDBGridDemo.cpp for the implementation of this class
//

class CBCGPDBGridDemoApp :	public CWinApp,
							public CBCGPWorkspace
{
public:
	CBCGPDBGridDemoApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPDBGridDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPDBGridDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnConnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPDBGridDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPDBGRIDDEMO_H__E1FAA510_8B09_4352_A9AE_88D81063C209__INCLUDED_)
