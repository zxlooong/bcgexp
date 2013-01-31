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
#if !defined(AFX_GOTODAYDIALOG_H__FBCA9FF2_E17E_4C9E_8717_567E168A58E6__INCLUDED_)
#define AFX_GOTODAYDIALOG_H__FBCA9FF2_E17E_4C9E_8717_567E168A58E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GotoDayDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGotoDayDialog dialog

class CGotoDayDialog : public CBCGPDialog
{
// Construction
public:
	CGotoDayDialog(const COleDateTime& date, CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type, 
		int nFirstDayOfWeek = 0, CWnd* pParent = NULL);   // standard constructor

	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE GetType () const
	{
		return m_Type;
	}

	const COleDateTime& GetDate () const
	{
		return m_Date;
	}

// Dialog Data
	//{{AFX_DATA(CGotoDayDialog)
	enum { IDD = IDD_PLANNER_GOTO_DAY };
	CBCGPDateTimeCtrl	m_DateTimePicker;
	int		m_TypeIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGotoDayDialog)
	protected:
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGotoDayDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int									m_nFirstDayOfWeek;
	COleDateTime						m_Date;
	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE	m_Type;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTODAYDIALOG_H__FBCA9FF2_E17E_4C9E_8717_567E168A58E6__INCLUDED_)
