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
#if !defined(AFX_RECURRENCECONFIRMDLG_H__AB16AC34_774C_4CF0_89B0_00D1A4A43363__INCLUDED_)
#define AFX_RECURRENCECONFIRMDLG_H__AB16AC34_774C_4CF0_89B0_00D1A4A43363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecurrenceConfirmDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceConfirmDlg dialog

class CRecurrenceConfirmDlg : public CBCGPDialog
{
// Construction
public:
	CRecurrenceConfirmDlg(const CString& strDescription, BOOL bOpen,
		CWnd* pParent = NULL);   // standard constructor

	BOOL IsOnlyOccurrence () const
	{
		return m_bOccurrence;
	}
// Dialog Data
	//{{AFX_DATA(CRecurrenceConfirmDlg)
	CBCGPStatic	m_stIcon;
	CBCGPStatic	m_stQuestion;
	CBCGPButton m_btnOccurrence;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecurrenceConfirmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL	m_bOccurrence;
	CString	m_strDescription;

	// Generated message map functions
	//{{AFX_MSG(CRecurrenceConfirmDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECURRENCECONFIRMDLG_H__AB16AC34_774C_4CF0_89B0_00D1A4A43363__INCLUDED_)
