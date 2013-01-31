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
// BCGPMSMoneyDemoDoc.h : interface of the CBCGPMSMoneyDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPMSMoneyDemoDOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_BCGPMSMoneyDemoDOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FIRST_HISTORY_COMMAND	0x1000
#define HISTORY_LEN	10

class CBCGPMSMoneyDemoDoc : public CDocument
{
protected: // create from serialization only
	CBCGPMSMoneyDemoDoc();
	DECLARE_DYNCREATE(CBCGPMSMoneyDemoDoc)

// Attributes
public:
// Operations
public:
	BOOL IsBackAvailable () const
	{
		return TRUE;
	}

	BOOL IsFrwdAvailable ()
	{
		return TRUE;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPMSMoneyDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPMSMoneyDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPMSMoneyDemoDoc)
	afx_msg void OnGoBack();
	afx_msg void OnUpdateGoBack(CCmdUI* pCmdUI);
	afx_msg void OnGoForward();
	afx_msg void OnUpdateGoForward(CCmdUI* pCmdUI);
	afx_msg void OnGoAddress();
	afx_msg void OnUpdateGoAddress(CCmdUI* pCmdUI);
	afx_msg void OnViewStop();
	afx_msg void OnUpdateViewStop(CCmdUI* pCmdUI);
	afx_msg void OnViewRefresh();
	afx_msg void OnUpdateViewRefresh(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMoneyDemoDOC_H__F83C8E11_F33E_11D2_A713_0090274409AC__INCLUDED_)
