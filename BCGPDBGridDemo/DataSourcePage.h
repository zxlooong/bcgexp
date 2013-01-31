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
#if !defined(AFX_DATASOURCEPAGE_H__697B4628_7AB2_495C_B3C9_572200C4EAFF__INCLUDED_)
#define AFX_DATASOURCEPAGE_H__697B4628_7AB2_495C_B3C9_572200C4EAFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataSourcePage.h : header file



class CCustomBrowseEdit : public CBCGPEdit
{
	virtual void OnBrowse ();

};

/////////////////////////////////////////////////////////////////////////////
// CDataSourcePage dialog
class CBCGPDBGridDemoView;

class CDataSourcePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataSourcePage)

// Construction
public:
	CDataSourcePage();
	~CDataSourcePage();

// Dialog Data
	//{{AFX_DATA(CDataSourcePage)
	enum { IDD = IDD_DATA_SOURCE_DLG };
	CButton	m_btnAllowEdit;
	CCustomBrowseEdit	m_editConnect;
	CBCGPEdit	m_wndEditMdbFile;
	BOOL	m_bAllowEdit;
	CString	m_strMdbFile;
	int		m_nDataSource;
	BOOL	m_bVirtualMode;
	//}}AFX_DATA

	CBCGPDBGridDemoView* m_pView;

public:
	void OnChooseDSN ();
	void SetProperGrid ();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDataSourcePage)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataSourcePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDataSource();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASOURCEPAGE_H__697B4628_7AB2_495C_B3C9_572200C4EAFF__INCLUDED_)
