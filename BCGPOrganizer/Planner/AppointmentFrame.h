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

#if !defined(AFX_APPOINTMENTFRAME_H__FC33E18B_2A94_4A2E_A655_742DC0D0DCE0__INCLUDED_)
#define AFX_APPOINTMENTFRAME_H__FC33E18B_2A94_4A2E_A655_742DC0D0DCE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppointmentFrame.h : header file
//

#include "../EditDialogBar.h"
#include "../EditFrameDialog.h"
#include "BCGPRecurrenceRule.h"

/////////////////////////////////////////////////////////////////////////////
// CAppointmentFrame frame

class CAppointmentDialogBar1: public CEditDialogBar
{
	friend class CAppointmentFrame;
	DECLARE_SERIAL(CAppointmentDialogBar1)

public:
	CAppointmentDialogBar1 ();
	virtual ~CAppointmentDialogBar1 ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL LoadState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1)
	{
		return TRUE;
	}
	virtual BOOL SaveState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1)
	{
		return TRUE;
	}

	virtual BOOL OnInitDialogBar();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	CString	m_strSubject;
	CString	m_strLocation;
	BOOL	m_bAllDay;

	BOOL	m_bMeeting;
	BOOL	m_bPhoneCall;
};

class CAppointmentDialogBar2: public CEditDialogBar
{
	friend class CAppointmentFrame;
	DECLARE_SERIAL(CAppointmentDialogBar2)

public:
	CAppointmentDialogBar2 ();
	virtual ~CAppointmentDialogBar2 ();

protected:
	void EnableDateControls (BOOL bEnable);

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL LoadState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1)
	{
		return TRUE;
	}
	virtual BOOL SaveState (LPCTSTR /*lpszProfileName*/ = NULL, int /*nIndex*/ = -1, UINT /*uiID*/ = (UINT) -1)
	{
		return TRUE;
	}

	virtual BOOL OnInitDialogBar();

protected:
	afx_msg void OnAllDay();
	
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPButton			m_AllDay;
	CBCGPDateTimeCtrl	m_DateStart;
	CBCGPDateTimeCtrl	m_TimeStart;
	CBCGPDateTimeCtrl	m_DateEnd;
	CBCGPDateTimeCtrl	m_TimeEnd;
	BOOL				m_bAllDay;

	COleDateTime		m_dtStart;
	COleDateTime		m_dtFinish;

	BOOL				m_bFirstTime;
};

class CAppointmentFrame : public CEditFrameDialog
{
	DECLARE_DYNAMIC(CAppointmentFrame)

public:
	enum XImportance
	{
		e_ImportanceNormal,
		e_ImportanceHigh,
		e_ImportanceLow
	};

// Attributes
public:
	CAppointmentFrame(CBCGPAppointment& app, 
					const CBCGPRecurrenceBaseRule* pRule = NULL,
					BOOL bEcp = FALSE,
					BOOL bNewRecur = FALSE,
					BOOL bReadOnly = FALSE,
					CWnd* pParent = NULL);

	virtual ~CAppointmentFrame();

	const CBCGPRecurrenceBaseRule* GetRule () const
	{
		return m_Rule;
	}

	BOOL IsDeleted () const
	{
		return m_bDeleted;
	}

// Operations
protected:
	virtual void OnOK();

	virtual BOOL CreateStatusBar ();

	virtual BOOL CreateOtherBars ();

	virtual BOOL LoadPanelImages ();

	virtual void AddMainCategory ();	
	virtual void AddTabs ();

	void AddTab_Home ();

	void EnableDateControls (BOOL bEnable);

	void CompleteShowAs (CBCGPRibbonButton& btn);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppointmentFrame)
	public:
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAppointmentFrame)
	afx_msg void OnFileClose();
	afx_msg void OnSaveClose ();
	afx_msg void OnDelete ();
	afx_msg void OnUpdateDelete (CCmdUI* pCmdUI);
	afx_msg void OnRecurrence ();
	afx_msg void OnPrivate ();
	afx_msg void OnUpdatePrivate (CCmdUI* pCmdUI);
	afx_msg void OnImportanceLow ();
	afx_msg void OnUpdateImportanceLow (CCmdUI* pCmdUI);
	afx_msg void OnImportanceHigh ();
	afx_msg void OnUpdateImportanceHigh (CCmdUI* pCmdUI);
	afx_msg void OnUpdateLabel (CCmdUI* pCmdUI);
	afx_msg void OnCategory(UINT nID);
	afx_msg void OnUpdateCategory (CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowTime (CCmdUI* pCmdUI);
	afx_msg void OnShowAs(UINT nID);
	afx_msg void OnUpdateShowAs (CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CAppointmentDialogBar1	m_wndDialogBar1;
	CAppointmentDialogBar2	m_wndDialogBar2;

	BOOL	m_bPrivate;
	XImportance m_Importance;
	int		m_nLabel;
	int		m_nShowTime;

	CBCGPAppointment& m_Appointment;
	CBCGPRecurrenceBaseRule* m_Rule;
	BOOL	m_bEcp;
	BOOL	m_bNewRecur;
	BOOL	m_bReadOnly;
	BOOL	m_bDeleted;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPOINTMENTFRAME_H__FC33E18B_2A94_4A2E_A655_742DC0D0DCE0__INCLUDED_)
