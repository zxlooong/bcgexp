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
#if !defined(AFX_DATATABLEPAGE_H__4EFE4FC9_EABA_40FF_AFC3_F673D234FD39__INCLUDED_)
#define AFX_DATATABLEPAGE_H__4EFE4FC9_EABA_40FF_AFC3_F673D234FD39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataTablePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataTablePage dialog
class CBCGPDBGridDemoView;

class CDataTablePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataTablePage)

// Construction
public:
	CDataTablePage();
	~CDataTablePage();

// Dialog Data
	//{{AFX_DATA(CDataTablePage)
	enum { IDD = IDD_TABLE_DLG };
	CListBox	m_listboxTables;
	//}}AFX_DATA

	CBCGPDBGridDemoView* m_pView;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDataTablePage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataTablePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATABLEPAGE_H__4EFE4FC9_EABA_40FF_AFC3_F673D234FD39__INCLUDED_)
