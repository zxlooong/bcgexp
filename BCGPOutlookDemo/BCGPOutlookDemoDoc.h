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
// BCGPOutlookDemoDoc.h : interface of the CBCGPOutlookDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPOUTLOOKDEMODOC_H__AFE0CB53_FDBF_426F_BB86_598BA0E79C2B__INCLUDED_)
#define AFX_BCGPOUTLOOKDEMODOC_H__AFE0CB53_FDBF_426F_BB86_598BA0E79C2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPOutlookDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPOutlookDemoDoc();
	DECLARE_DYNCREATE(CBCGPOutlookDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPOutlookDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPOutlookDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPOutlookDemoDoc)
	afx_msg void OnNewAppoinment();
	afx_msg void OnNewContract();
	afx_msg void OnNewDistributionList();
	afx_msg void OnNewFax();
	afx_msg void OnNewFolder();
	afx_msg void OnNewJournalEntry();
	afx_msg void OnNewMail();
	afx_msg void OnNewMeeting();
	afx_msg void OnNewNote();
	afx_msg void OnNewPostFolder();
	afx_msg void OnNewShortcut();
	afx_msg void OnNewTask();
	afx_msg void OnNewTaskRequest();
	afx_msg void OnSendReceive();
	afx_msg void OnAddressBook();
	afx_msg void OnFindContact();
	afx_msg void OnWebAddress();
	afx_msg void OnWebBack();
	afx_msg void OnWebFind();
	afx_msg void OnWebRefresh();
	afx_msg void OnWebStart();
	afx_msg void OnViewUp();
	afx_msg void OnViewBack();
	afx_msg void OnRulesWizard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPOUTLOOKDEMODOC_H__AFE0CB53_FDBF_426F_BB86_598BA0E79C2B__INCLUDED_)
