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
#if !defined(AFX_GANTTDLG_H__57DADDA2_DC8A_4BF0_AB01_2A475BD9F962__INCLUDED_)
#define AFX_GANTTDLG_H__57DADDA2_DC8A_4BF0_AB01_2A475BD9F962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GanttDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGanttDlg dialog

class CGanttDlg : public CDialog
{
// Construction
public:
	CGanttDlg(CBCGPGanttItem& item, 
					BOOL bMilestone = FALSE,
					BOOL bReadOnly = FALSE,
					CWnd* pParent = NULL);   // standard constructor
	
	virtual ~CGanttDlg ();

// Dialog Data
	//{{AFX_DATA(CGanttDlg)
	enum { IDD = IDD_GANTT_EDIT_DLG };
	CBCGPEdit			m_EditMemo;
	CStatic				m_stDateTimeStart;
	CStatic				m_stDateTimeEnd;
	CBCGPDateTimeCtrl	m_DateStart;
	CBCGPDateTimeCtrl	m_TimeStart;
	CBCGPDateTimeCtrl	m_DateEnd;
	CBCGPDateTimeCtrl	m_TimeEnd;
    CBCGPColorButton    m_Color1;
    CBCGPColorButton    m_Color2;
	CStatic				m_stProgress;
	CEdit				m_Progress;
	CSpinButtonCtrl		m_ProgressSpin;
	CString				m_strName;
	CString				m_strMemo;
	long				m_lProgress;
	//}}AFX_DATA

	BOOL IsDeleted () const
	{
		return m_bDeleted;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGanttDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGanttDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBCGPGanttItem& m_Item;
	BOOL	m_bMilestone;
	BOOL	m_bCompleted;
	BOOL	m_bReadOnly;
	BOOL	m_bDeleted;

	void EnableDateControls (BOOL bEnable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GANTTDLG_H__57DADDA2_DC8A_4BF0_AB01_2A475BD9F962__INCLUDED_)
