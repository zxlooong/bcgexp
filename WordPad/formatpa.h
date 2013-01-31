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
// formatpa.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormatParaDlg dialog

class CFormatParaDlg : public CCSDialog
{
// Construction
public:
	CFormatParaDlg(WPD_PARAFORMAT& pf, CWnd* pParent = NULL);   // standard constructor
	WPD_PARAFORMAT m_pf;

// Attributes
	int m_nWordWrap;

// Dialog Data
	//{{AFX_DATA(CFormatParaDlg)
	enum { IDD = IDD_FORMAT_PARA };
	int     m_nAlignment;
	int     m_nFirst;
	int     m_nLeft;
	int     m_nRight;
	//}}AFX_DATA

// Implementation
protected:
	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

	// Generated message map functions
	//{{AFX_MSG(CFormatParaDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
