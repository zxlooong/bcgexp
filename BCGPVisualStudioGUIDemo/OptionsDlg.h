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
#if !defined(AFX_OPTIONSDLG_H__8C61C1D5_B379_4D85_BD46_4F783E2FD13F__INCLUDED_)
#define AFX_OPTIONSDLG_H__8C61C1D5_B379_4D85_BD46_4F783E2FD13F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//

#include "OptionsPages.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg

class COptionsDlg : public CBCGPPropertySheet
{
	DECLARE_DYNAMIC(COptionsDlg)

// Construction
public:
	COptionsDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	COptionsPage1	m_Page11;
	COptionsPage12	m_Page12;
	COptionsPage21	m_Page21;
	COptionsPage22	m_Page22;
	COptionsPage31	m_Page31;
	COptionsPage32	m_Page32;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptionsDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionsDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__8C61C1D5_B379_4D85_BD46_4F783E2FD13F__INCLUDED_)
