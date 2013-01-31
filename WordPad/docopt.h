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
// docopt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDocOptPage dialog

class CDocOptPage : public CCSPropertyPage
{
// Construction
public:
	CDocOptPage();
	CDocOptPage(UINT nIDCaption);
	~CDocOptPage();

// Dialog Data
	//{{AFX_DATA(CDocOptPage)
	enum { IDD = IDD_OPTIONS_WRAP };
	int     m_nWordWrap;
	BOOL    m_bFormatBar;
	BOOL    m_bRulerBar;
	BOOL    m_bStatusBar;
	BOOL    m_bToolBar;
	//}}AFX_DATA


// Overrides
	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDocOptPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDocOptPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

class CEmbeddedOptPage : public CDocOptPage
{
// Construction
public:
	CEmbeddedOptPage();
// Overrides
	BOOL OnInitDialog();
};
