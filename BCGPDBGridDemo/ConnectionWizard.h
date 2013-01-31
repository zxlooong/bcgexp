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
#if !defined(AFX_CONNECTIONWIZARD_H__6C13AAE7_8EB6_463F_90F6_E8732F9BEF33__INCLUDED_)
#define AFX_CONNECTIONWIZARD_H__6C13AAE7_8EB6_463F_90F6_E8732F9BEF33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectionWizard.h : header file
//

#include "DataSourcePage.h"
#include "DataTypePage.h"
#include "DataTablePage.h"
#include "DataFieldsPage.h"

/////////////////////////////////////////////////////////////////////////////
// CConnectionWizard

class CBCGPDBGridDemoDoc;

class CConnectionWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CConnectionWizard)

// Construction
public:
	CConnectionWizard (CWnd* pParentWnd);

// Attributes
public:
	CBCGPDBGridDemoDoc* GetDocument ()
	{
		return m_pDoc;
	}

protected:
	CDataTypePage			m_pageDataType;
	CDataSourcePage			m_pageDataSource;
	CDataTablePage			m_pageDataTable;
	CDataFieldsPage			m_pageFields;

	CBCGPDBGridDemoDoc*		m_pDoc;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectionWizard)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConnectionWizard();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConnectionWizard)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTIONWIZARD_H__6C13AAE7_8EB6_463F_90F6_E8732F9BEF33__INCLUDED_)
