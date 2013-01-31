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
// filenewd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileNewDialog dialog

class CFileNewDialog : public CCSDialog
{
// Construction
public:
	CFileNewDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileNewDialog)
	enum { IDD = IDD_FILENEWDIALOG };
	CListBox    m_listbox;
	int     m_nSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileNewDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}

	// Generated message map functions
	//{{AFX_MSG(CFileNewDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkDatedialogList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
