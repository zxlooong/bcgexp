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
// BCGControls.h : main header file for the BCGCONTROLS application
//

#if !defined(AFX_BCGCONTROLS_H__49B6759A_C3E1_11D3_A722_009027900694__INCLUDED_)
#define AFX_BCGCONTROLS_H__49B6759A_C3E1_11D3_A722_009027900694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPControlsApp:
// See BCGPControls.cpp for the implementation of this class
//

class CBCGPControlsApp :	public CWinApp,
							public CBCGPWorkspace
{
public:
	CBCGPControlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPControlsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBCGPControlsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CBCGPControlsApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGCONTROLS_H__49B6759A_C3E1_11D3_A722_009027900694__INCLUDED_)
