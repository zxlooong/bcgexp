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
// datedial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDateDialog dialog

class CDateDialog : public CCSDialog
{
// Construction
public:
	CDateDialog(CWnd* pParent = NULL);   // standard constructor

// Attributes
	static SYSTEMTIME m_time;
	static LCID m_id;
	static CListBox* m_pListBox;
	static BOOL CALLBACK DateFmtEnumProc(LPTSTR lpszFormatString);
	static BOOL CALLBACK TimeFmtEnumProc(LPTSTR lpszFormatString);

// Dialog Data
	//{{AFX_DATA(CDateDialog)
	enum { IDD = IDD_DATEDIALOG };
	CListBox    m_listBox;
	CString m_strSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}

	// Generated message map functions
	//{{AFX_MSG(CDateDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkDatedialogList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
