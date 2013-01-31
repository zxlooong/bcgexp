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
#if !defined(AFX_DATATYPEPAGE_H__201EC62E_0EB2_4725_9F2E_903A7A21696B__INCLUDED_)
#define AFX_DATATYPEPAGE_H__201EC62E_0EB2_4725_9F2E_903A7A21696B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataTypePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataTypePage dialog
class CBCGPDBGridDemoView;

class CDataTypePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDataTypePage)

// Construction
public:
	CDataTypePage();
	~CDataTypePage();

// Dialog Data
	//{{AFX_DATA(CDataTypePage)
	enum { IDD = IDD_DATA_TYPE_DLG };
	//}}AFX_DATA

	CBCGPDBGridDemoView* m_pView;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDataTypePage)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataTypePage)
	afx_msg void OnRadioAdo();
	afx_msg void OnRadioDao();
	afx_msg void OnRadioOdbc();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATYPEPAGE_H__201EC62E_0EB2_4725_9F2E_903A7A21696B__INCLUDED_)
