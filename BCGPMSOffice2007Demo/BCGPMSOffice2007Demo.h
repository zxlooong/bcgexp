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
// BCGPMSOffice2007Demo.h : main header file for the BCGPMSOFFICE2007DEMO application
//

#if !defined(AFX_BCGPMSOFFICE2007DEMO_H__35D904CD_2A9E_40CD_95DA_0986A2D134BC__INCLUDED_)
#define AFX_BCGPMSOFFICE2007DEMO_H__35D904CD_2A9E_40CD_95DA_0986A2D134BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSOffice2007DemoApp:
// See BCGPMSOffice2007Demo.cpp for the implementation of this class
//

class CBCGPMSOffice2007DemoApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CBCGPMSOffice2007DemoApp();

	BOOL						m_bShowFloaty;
	UINT						m_nAppLook;
	BOOL						m_bShowDevTab;
	BOOL						m_bShowToolTips;
	BOOL						m_bShowToolTipDescr;
	BOOL						m_bShowKeyTips;
	BOOL						m_bIsRTL;

	CList<COLORREF, COLORREF>	m_lstCustomColors;
	COLORREF					m_clrCustomDef;
	COLORREF					m_clrCustom;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSOffice2007DemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPMSOffice2007DemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPMSOffice2007DemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSOFFICE2007DEMO_H__35D904CD_2A9E_40CD_95DA_0986A2D134BC__INCLUDED_)
