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
// BCGPGanttDemo.h : main header file for the BCGPCHARTEXAMPLE application
//

#if !defined(AFX_BCGPCHARTEXAMPLE_H__45158E5B_8E8F_4604_9DFE_CCF2B7D00012__INCLUDED_)
#define AFX_BCGPCHARTEXAMPLE_H__45158E5B_8E8F_4604_9DFE_CCF2B7D00012__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPGanttDemoApp:
// See BCGPGanttDemo.cpp for the implementation of this class
//

class CBCGPGanttDemoApp : public CWinApp
#ifndef _BCGPGANTT_STANDALONE
							,public CBCGPWorkspace
#endif
{
public:
	CBCGPGanttDemoApp();

#ifndef _BCGPGANTT_STANDALONE
	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
#else
	int GetSectionInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault = 0);
	BOOL WriteSectionInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPGanttDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPGanttDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPGanttDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCHARTEXAMPLE_H__45158E5B_8E8F_4604_9DFE_CCF2B7D00012__INCLUDED_)
