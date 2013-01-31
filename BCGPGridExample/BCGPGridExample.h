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
// BCGPGridExample.h : main header file for the BCGPGRIDEXAMPLE application
//

#if !defined(AFX_BCGPGRIDEXAMPLE_H__56CA9C55_E311_454E_BF94_2E4580932819__INCLUDED_)
#define AFX_BCGPGRIDEXAMPLE_H__56CA9C55_E311_454E_BF94_2E4580932819__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define BCGGRID_VIEWS_NUM	7

#define BCGGRID_BASIC		0
#define BCGGRID_REPORT		1
#define BCGGRID_CELLTYPES	2
#define BCGGRID_COLOR		3
#define BCGGRID_VIRTUAL		4
#define BCGGRID_MERGE		5
#define BCGGRID_FILTER		6

class CGridOptions
{
public:
	CGridOptions();

	BOOL	m_bFieldChooser;
	BOOL	m_bGroupByBox;
	BOOL	m_bReportPreview;
	int		m_nColorTheme;

	void Load ();
	void Save ();
};

/////////////////////////////////////////////////////////////////////////////
// CBCGPGridExampleApp:
// See BCGPGridExample.cpp for the implementation of this class
//

class CBCGPGridExampleApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CBCGPGridExampleApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
	void UpdateGrid ();

	CGridOptions m_Options;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPGridExampleApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPGridExampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPGridExampleApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPGRIDEXAMPLE_H__56CA9C55_E311_454E_BF94_2E4580932819__INCLUDED_)
