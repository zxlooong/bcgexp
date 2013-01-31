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
// ChatEditor.h : main header file for the CHATEDITOR application
//

#if !defined(AFX_CHATEDITOR_H__C5FF334C_7198_4ECD_8A0C_CFE4ACE0D83A__INCLUDED_)
#define AFX_CHATEDITOR_H__C5FF334C_7198_4ECD_8A0C_CFE4ACE0D83A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatEditorApp:
// See ChatEditor.cpp for the implementation of this class
//

class CChatEditorApp : public CWinApp
{
public:
	CChatEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChatEditorApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATEDITOR_H__C5FF334C_7198_4ECD_8A0C_CFE4ACE0D83A__INCLUDED_)
