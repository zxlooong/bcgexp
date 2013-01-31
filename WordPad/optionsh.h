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
// optionsh.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionSheet

class COptionSheet : public CCSPropertySheet
{
// Construction
public:
	COptionSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CUnitsPage units;
	CDocOptPage pageText;
	CDocOptPage pageRTF;
	CDocOptPage pageWord;
	CDocOptPage pageWrite;
	CEmbeddedOptPage pageEmbedded;

// Operations
public:
	INT_PTR DoModal();
	void SetPageButtons(CDocOptPage& page, CDockState& ds);
	void SetState(CDocOptPage& page, CDockState& ds);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionSheet)
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionSheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
