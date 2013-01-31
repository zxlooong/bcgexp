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
#if !defined(AFX_PAGE6_H__F20D6496_FE28_4A2A_A064_8734BB76CE25__INCLUDED_)
#define AFX_PAGE6_H__F20D6496_FE28_4A2A_A064_8734BB76CE25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page6.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CPage6 dialog

class CPage6 : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPage6)

// Construction
public:
	CPage6();
	~CPage6();

// Dialog Data
	//{{AFX_DATA(CPage6)
	enum { IDD = IDD_PAGE6 };
	CComboBox	m_weekStart;
	CBCGPDurationCtrl	m_wndDuration;
	CBCGPDateTimeCtrl	m_wndDateTimePicker;
	CStatic	m_calendarLocation;
	BOOL	m_bDurationDays;
	BOOL	m_bDurationHours;
	BOOL	m_bDurationSpin;
	BOOL	m_bDateTimeCheckBox;
	BOOL	m_bDateTimeDrop;
	BOOL	m_bDateTimeSpin;
	BOOL	m_bCalendarMultSel;
	BOOL	m_bCalendarShowWeekNumber;
	int		m_nDateTimeParts;
	int		m_nTimeFormat;
	BOOL	m_bDurationSeconds;
	BOOL	m_bCalendarShowToday;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBCGPCalendar  m_wndCalendarCtrl;

	// Generated message map functions
	//{{AFX_MSG(CPage6)
	virtual BOOL OnInitDialog();
	afx_msg void SetDurationState();
	afx_msg void OnDuration();
	afx_msg void SetDateTimeState();
	afx_msg void OnDatetimepicker();
	afx_msg void SetCalendarBarSate();
	afx_msg void OnSelchangeWeekstart();
	//}}AFX_MSG
	afx_msg LRESULT OnCalendarSelectionChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE6_H__F20D6496_FE28_4A2A_A064_8734BB76CE25__INCLUDED_)
