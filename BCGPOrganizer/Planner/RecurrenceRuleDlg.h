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
#if !defined(AFX_RECURRENCERULEDLG_H__C0687A37_21FB_416B_8835_BB69958E29BB__INCLUDED_)
#define AFX_RECURRENCERULEDLG_H__C0687A37_21FB_416B_8835_BB69958E29BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecurrenceRuleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecurrenceRuleDlg dialog

class CRecurrenceRuleDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CRecurrenceRuleDlg)

// Construction
public:
	CRecurrenceRuleDlg();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecurrenceRuleDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecurrenceRuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL Create(CWnd* pParentWnd);

	CBCGPRecurrenceBaseRule* GetRule () const
	{
		return m_Rule;
	}

	virtual void SetRule (CBCGPRecurrenceBaseRule* pRule)
	{
		ASSERT_VALID(pRule);
		m_Rule = pRule;
	}

	virtual BOOL UpdateRule (const COleDateTime& /*dtStart*/)
	{
		return FALSE;
	}

protected:
	virtual UINT GetID () const
	{
		ASSERT (FALSE);
		return 0;
	}

	// Generated message map functions
	//{{AFX_MSG(CRecurrenceRuleDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPRecurrenceBaseRule* m_Rule;
	COleDateTime m_dtStart;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECURRENCERULEDLG_H__C0687A37_21FB_416B_8835_BB69958E29BB__INCLUDED_)
