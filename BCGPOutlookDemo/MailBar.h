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
#if !defined(AFX_MAILBAR_H__FA32B087_AD91_4244_A810_F869713D0D20__INCLUDED_)
#define AFX_MAILBAR_H__FA32B087_AD91_4244_A810_F869713D0D20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMailBar dialog

class CMailBar : public CBCGPDialogBar
{
// Construction
public:
	CMailBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMailBar)
	enum { IDD = IDD_MAILBAR };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual BOOL AllowShowOnControlMenu () const
	{
		return FALSE;
	}

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMailBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustWidth (int cx, UINT uiCtrlID);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILBAR_H__FA32B087_AD91_4244_A810_F869713D0D20__INCLUDED_)
