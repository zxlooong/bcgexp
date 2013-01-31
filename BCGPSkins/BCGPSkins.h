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
// BCGPSkins.h : main header file for the BCGPSkins application
//

#if !defined(AFX_BCGPSKINS_H__265BD696_35C4_4525_827F_5253118C0867__INCLUDED_)
#define AFX_BCGPSKINS_H__265BD696_35C4_4525_827F_5253118C0867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsApp:
// See BCGPSkins.cpp for the implementation of this class
//

class CBCGPSkinsApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CBCGPSkinsApp();

	void SetSkin (UINT nSkin);
	UINT	m_uiCurrSkin;

	// Override from CBCGWorkspace
	virtual void PreLoadState ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPSkinsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPSkinsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPSkinsApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPSKINS_H__265BD696_35C4_4525_827F_5253118C0867__INCLUDED_)
