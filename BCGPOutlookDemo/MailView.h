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
#if !defined(AFX_MAILVIEW_H__24814C6F_FC94_4DCA_9DC6_B975F6DD0783__INCLUDED_)
#define AFX_MAILVIEW_H__24814C6F_FC94_4DCA_9DC6_B975F6DD0783__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMailView view

class CMailView : public CEditView
{
protected:
	CMailView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMailView)

// Attributes
public:
	int	m_nPriority;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailView)
	public:
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMailView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMailView)
	afx_msg void OnMailAttachment();
	afx_msg void OnMailCheckNames();
	afx_msg void OnMailCopyToFolder();
	afx_msg void OnMailDelete();
	afx_msg void OnMailFlag();
	afx_msg void OnMailFontsize();
	afx_msg void OnMailHightPriority();
	afx_msg void OnUpdateMailHightPriority(CCmdUI* pCmdUI);
	afx_msg void OnMailItem();
	afx_msg void OnMailLowPriority();
	afx_msg void OnUpdateMailLowPriority(CCmdUI* pCmdUI);
	afx_msg void OnMailMoveToFolder();
	afx_msg void OnMailOptions();
	afx_msg void OnMailProperties();
	afx_msg void OnMailSave();
	afx_msg void OnMailSaveAttachments();
	afx_msg void OnMailSaveStationery();
	afx_msg void OnMailSend();
	afx_msg void OnMailSignature();
	afx_msg void OnMailSpell();
	//}}AFX_MSG
	afx_msg void OnMailTo();
	afx_msg void OnMailCc();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILVIEW_H__24814C6F_FC94_4DCA_9DC6_B975F6DD0783__INCLUDED_)
