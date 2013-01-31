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
// unitspag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnitsPage dialog

class CUnitsPage : public CCSPropertyPage
{
// Construction
public:
	CUnitsPage();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUnitsPage)
	enum { IDD = IDD_OPTIONS_UNITS };
	int     m_nUnits;
	BOOL    m_bWordSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnitsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}

	// Generated message map functions
	//{{AFX_MSG(CUnitsPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
