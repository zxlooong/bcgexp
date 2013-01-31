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

#if !defined(AFX_GANTTFRAME_H__FC33E18B_2A94_4A2E_A655_742DC0D0DCE0__INCLUDED_)
#define AFX_GANTTFRAME_H__FC33E18B_2A94_4A2E_A655_742DC0D0DCE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GanttFrame.h : header file
//

#include "../EditDialogBar.h"
#include "../EditFrameDialog.h"
#include "BCGPRecurrenceRule.h"

/////////////////////////////////////////////////////////////////////////////
// CGanttFrame frame

class CGanttDialogBar1: public CEditDialogBar
{
	friend class CGanttFrame;
	DECLARE_SERIAL(CGanttDialogBar1)

public:
	CGanttDialogBar1 ();
	virtual ~CGanttDialogBar1 ();

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

	void EnableDateControls (BOOL bEnable);

protected:
	BOOL				m_bFirstTime;
	CString				m_strName;
	CBCGPDateTimeCtrl	m_DateStart;
	CBCGPDateTimeCtrl	m_TimeStart;
	COleDateTime		m_dtStart;
};

class CGanttDialogBar2: public CEditDialogBar
{
	friend class CGanttFrame;
	DECLARE_SERIAL(CGanttDialogBar2)

public:
	CGanttDialogBar2 ();
	virtual ~CGanttDialogBar2 ();

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

	void EnableDateControls (BOOL bEnable);

protected:
	BOOL				m_bFirstTime;
	CBCGPDateTimeCtrl	m_DateEnd;
	CBCGPDateTimeCtrl	m_TimeEnd;	
	COleDateTime		m_dtFinish;
	CBCGPEdit			m_Progress;
	CBCGPSpinButtonCtrl	m_ProgressSpin;
	long				m_lProgress;
};

class CGanttFrame : public CEditFrameDialog
{
	DECLARE_DYNAMIC(CGanttFrame)

public:
	enum XImportance
	{
		e_ImportanceNormal,
		e_ImportanceHigh,
		e_ImportanceLow
	};

// Attributes
public:
	CGanttFrame(CBCGPGanttItem& item, 
					BOOL bIsMilestone = FALSE,
					BOOL bReadOnly = FALSE,
					CWnd* pParent = NULL);

	virtual ~CGanttFrame();

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

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGanttFrame)
	public:
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGanttFrame)
	afx_msg void OnFileClose();
	afx_msg void OnSaveClose ();
	afx_msg void OnDelete ();
	afx_msg void OnUpdateDelete (CCmdUI* pCmdUI);
	afx_msg void OnPrivate ();
	afx_msg void OnUpdatePrivate (CCmdUI* pCmdUI);
	afx_msg void OnImportanceLow ();
	afx_msg void OnUpdateImportanceLow (CCmdUI* pCmdUI);
	afx_msg void OnImportanceHigh ();
	afx_msg void OnUpdateImportanceHigh (CCmdUI* pCmdUI);
	afx_msg void OnUpdateLabel (CCmdUI* pCmdUI);
	afx_msg void OnCategory(UINT nID);
	afx_msg void OnUpdateCategory (CCmdUI* pCmdUI);
	afx_msg void OnMarkComplete();
	afx_msg void OnUpdateMarkComplete(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CGanttDialogBar1	m_wndDialogBar1;
	CGanttDialogBar2	m_wndDialogBar2;

	BOOL	m_bCompleted;
	BOOL	m_bMilestone;
	BOOL	m_bPrivate;
	XImportance m_Importance;
	int		m_nLabel;

	CBCGPGanttItem& m_Item;
	BOOL	m_bReadOnly;
	BOOL	m_bDeleted;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GANTTFRAME_H__FC33E18B_2A94_4A2E_A655_742DC0D0DCE0__INCLUDED_)
