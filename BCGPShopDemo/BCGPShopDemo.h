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
// BCGPShopDemo.h : main header file for the BCGPSHOPDEMO application
//

#if !defined(AFX_BCGPSHOPDEMO_H__A6B95D5E_FD69_495D_9930_911ABA693630__INCLUDED_)
#define AFX_BCGPSHOPDEMO_H__A6B95D5E_FD69_495D_9930_911ABA693630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoApp:
// See BCGPShopDemo.cpp for the implementation of this class
//

class CBCGPShopDemoApp :	public CWinApp,
							public CBCGPWorkspace
{
public:
	CBCGPShopDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPShopDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPShopDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    //virtual BOOL LoadState(LPCTSTR, CBCGPFrameImpl*) { return TRUE; } // disable for debug purposes
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPSHOPDEMO_H__A6B95D5E_FD69_495D_9930_911ABA693630__INCLUDED_)
