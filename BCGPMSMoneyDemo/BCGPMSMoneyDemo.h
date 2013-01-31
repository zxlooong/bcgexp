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
// BCGPMSMoneyDemo.h : main header file for the BCGPMSMONEY application
//

#if !defined(AFX_BCGPMSMONEY_H__0DA8B983_B1E6_43A4_BD3D_2593588E713B__INCLUDED_)
#define AFX_BCGPMSMONEY_H__0DA8B983_B1E6_43A4_BD3D_2593588E713B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoApp:
// See BCGPMSMoneyDemo.cpp for the implementation of this class
//

class CBCGPMSMoneyDemoApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CBCGPMSMoneyDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSMoneyDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPMSMoneyDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPMSMoneyDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMONEY_H__0DA8B983_B1E6_43A4_BD3D_2593588E713B__INCLUDED_)
