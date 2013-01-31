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

#if !defined(AFX_LINEWEIGHTDLG_H__1E4C8AEF_11E7_46F0_8C40_2975A011AA0D__INCLUDED_)
#define AFX_LINEWEIGHTDLG_H__1E4C8AEF_11E7_46F0_8C40_2975A011AA0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineWeightDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineWeightDlg dialog

class CLineWeightDlg : public CDialog
{
// Construction
public:
	CLineWeightDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLineWeightDlg)
	enum { IDD = IDD_LINEWEIGHT };
	CSpinButtonCtrl m_SpinCtrl;
	UINT    m_penSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineWeightDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineWeightDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEWEIGHTDLG_H__1E4C8AEF_11E7_46F0_8C40_2975A011AA0D__INCLUDED_)
