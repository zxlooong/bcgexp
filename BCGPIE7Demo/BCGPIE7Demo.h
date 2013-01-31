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
// BCGPIE7Demo.h : main header file for the BCGPIE7DEMO application
//

#if !defined(AFX_BCGPIE7DEMO_H__08CA8A6A_C67F_4DEA_9DCA_EE38404AB1E1__INCLUDED_)
#define AFX_BCGPIE7DEMO_H__08CA8A6A_C67F_4DEA_9DCA_EE38404AB1E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoApp:
// See BCGPIE7Demo.cpp for the implementation of this class
//

#include "FavoritesManager.h"
#include "HistoryObj.h"

class CBCGPIE7DemoApp : public CWinApp,
					  public CBCGPWorkspace
{
public:
	CBCGPIE7DemoApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();

	WORD	m_nColorMode;
	int		m_Style;

	BOOL IsLargeIcons () const
	{
		return m_bLargeIcons;
	}

	BOOL	m_bLargeIcons;
	CFavoritesManager	m_Favorites;
	CHistoryManager		m_History;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPIE7DemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL SaveAllModified();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPIE7DemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPIE7DemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPIE7DEMO_H__08CA8A6A_C67F_4DEA_9DCA_EE38404AB1E1__INCLUDED_)
