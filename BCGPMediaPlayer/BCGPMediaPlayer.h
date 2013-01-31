//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPMediaPlayer.h : main header file for the BCGPMEDIAPLAYER application
//

#if !defined(AFX_BCGPMEDIAPLAYER_H__1C1B8DF6_920B_43E5_B0D0_CF754D711A40__INCLUDED_)
#define AFX_BCGPMEDIAPLAYER_H__1C1B8DF6_920B_43E5_B0D0_CF754D711A40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "VisualManager.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerApp:
// See BCGPMediaPlayer.cpp for the implementation of this class
//

class CBCGPMediaPlayerApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CBCGPMediaPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMediaPlayerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPMediaPlayerApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPMediaPlayerApp theApp;

CVisualManager* GetVisualManager ();
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMEDIAPLAYER_H__1C1B8DF6_920B_43E5_B0D0_CF754D711A40__INCLUDED_)
