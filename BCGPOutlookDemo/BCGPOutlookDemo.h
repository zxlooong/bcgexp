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
// BCGPOutlookDemo.h : main header file for the BCGPOutlookDemo application
//

#if !defined(AFX_BCGPOUTLOOKDEMO_H__44F51EBD_8316_4061_87B4_C5F2D792A42C__INCLUDED_)
#define AFX_BCGPOUTLOOKDEMO_H__44F51EBD_8316_4061_87B4_C5F2D792A42C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoApp:
// See BCGPOutlookDemo.cpp for the implementation of this class
//

class CBCGPOutlookDemoApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CBCGPOutlookDemoApp();

	// Override from CBCGWorkspace
	virtual void PreLoadState ();

	enum OUTLOOK_FRAME
	{
		MainFrame,
		MailFrame
	};

	void SetActiveFrame (OUTLOOK_FRAME frame);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPOutlookDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPOutlookDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnViewAppLook();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPOutlookDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPOUTLOOKDEMO_H__44F51EBD_8316_4061_87B4_C5F2D792A42C__INCLUDED_)
