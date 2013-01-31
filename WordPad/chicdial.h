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
// chicdial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCSDialog dialog

class CCSDialog : public CDialog
{
// Construction
public:
	CCSDialog();
	CCSDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	CCSDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);

// Implementation
protected:
	virtual const DWORD* GetHelpIDs() = 0;

	// Generated message map functions
	//{{AFX_MSG(CCSDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHelpContextMenu(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

class CCSPropertyPage : public CPropertyPage
{
// Construction
public:
	CCSPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0);
	CCSPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0);

// Implementation
protected:
	virtual const DWORD* GetHelpIDs() = 0;

	// Generated message map functions
	//{{AFX_MSG(CCSPropertyPage)
	//}}AFX_MSG
	afx_msg LRESULT OnHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHelpContextMenu(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

class CCSPropertySheet : public CPropertySheet
{
// Construction
public:
	CCSPropertySheet(UINT nIDCaption, CWnd *pParentWnd = NULL,
		UINT iSelectPage = 0);
	CCSPropertySheet(LPCTSTR pszCaption, CWnd *pParentWnd = NULL,
		UINT iSelectPage = 0);
// Implementation
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	// Generated message map functions
	//{{AFX_MSG(CCSPropertySheet)
	//}}AFX_MSG
	afx_msg LRESULT OnHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHelpContextMenu(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
