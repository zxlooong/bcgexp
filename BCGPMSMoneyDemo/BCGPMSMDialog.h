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
#if !defined(AFX_BCGPMSMDIALOG_H__8065E653_F537_4D79_AB3E_F646AF610270__INCLUDED_)
#define AFX_BCGPMSMDIALOG_H__8065E653_F537_4D79_AB3E_F646AF610270__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPMSMDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMDialog dialog

class CBCGPMSMDialog : public CBCGPDialog
{
	DECLARE_DYNAMIC(CBCGPMSMDialog)

// Construction
public:
	CBCGPMSMDialog();
	CBCGPMSMDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	CBCGPMSMDialog(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);

// Implementation
protected:

	void CommonConstruct ();

	// Generated message map functions
	//{{AFX_MSG(CBCGPMSMDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPMSMDIALOG_H__8065E653_F537_4D79_AB3E_F646AF610270__INCLUDED_)
