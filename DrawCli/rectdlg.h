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
// rectdlg.h : header file

/////////////////////////////////////////////////////////////////////////////
// CRectDlg dialog

class CRectDlg : public CPropertyPage
{
// Construction
public:
	CRectDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
	//{{AFX_DATA(CRectDlg)
	enum { IDD = IDD_PROP_RECT };
	CSpinButtonCtrl m_SpinCtrl;
	BOOL    m_bNoFill;
	UINT    m_penSize;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CRectDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
