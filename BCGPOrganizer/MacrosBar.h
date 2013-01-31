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
#if !defined(AFX_MACROSBAR_H__00D25365_98E4_44F5_A634_A01A7101B338__INCLUDED_)
#define AFX_MACROSBAR_H__00D25365_98E4_44F5_A634_A01A7101B338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MacrosBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMacrosBar window

class CMacrosBar : public CTreeCtrl
{
// Construction
public:
	CMacrosBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacrosBar)
	virtual BOOL Create(CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMacrosBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMacrosBar)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CImageList		m_ImageList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACROSBAR_H__00D25365_98E4_44F5_A634_A01A7101B338__INCLUDED_)
