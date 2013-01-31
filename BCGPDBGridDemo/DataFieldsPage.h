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
#if !defined(AFX_DATAFIELDPAGE_H__4EFE4FC9_EABA_40FF_AFC3_F673D234FD39__INCLUDED_)
#define AFX_DATAFIELDPAGE_H__4EFE4FC9_EABA_40FF_AFC3_F673D234FD39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataFieldsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataFieldsPage dialog
class CBCGPDBGridDemoView;


class CDataFieldsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataFieldsPage)
// Construction
public:
	public:
	CDataFieldsPage();
	~CDataFieldsPage();

// Dialog Data
	//{{AFX_DATA(CDataFieldsPage)
	enum { IDD = IDD_DATA_FIELDS_DLG };
	CButton	m_btnMoveUp;
	CButton	m_wndMoveDown;
	CButton m_wndReset;
	CBCGPExCheckList	m_wndList;
	//}}AFX_DATA

	CBCGPDBGridDemoView* m_pView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataFieldsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataFieldsPage)
	afx_msg void OnSelchange();
	afx_msg void OnDblclkList();
	afx_msg void OnMoveDown();
	afx_msg void OnMoveUp();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnReset();
	afx_msg void OnSelectAll();
	afx_msg void OnSelectNone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void MoveItem (BOOL bMoveUp);
	void PopulateList (BOOL bCheckItems = TRUE);

	BOOL	m_bOrderWasChanged;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAFIELDPAGE_H__4EFE4FC9_EABA_40FF_AFC3_F673D234FD39__INCLUDED_)
