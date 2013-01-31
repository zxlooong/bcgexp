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
// DataTablePage.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPDBGridDemo.h"
#include "DataTablePage.h"
#include "BCGPDBGridDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDataTablePage property page

IMPLEMENT_DYNCREATE(CDataTablePage, CPropertyPage)

CDataTablePage::CDataTablePage() : CPropertyPage(CDataTablePage::IDD)
{
	//{{AFX_DATA_INIT(CDataTablePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDataTablePage::~CDataTablePage()
{
}

void CDataTablePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataTablePage)
	DDX_Control(pDX, IDC_LIST_TABLES, m_listboxTables);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataTablePage, CPropertyPage)
	//{{AFX_MSG_MAP(CDataTablePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataTablePage message handlers

BOOL CDataTablePage::OnSetActive() 
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent ();
	ASSERT_VALID (pSheet);
	pSheet->SetWizardButtons (PSWIZB_NEXT);	

	CBCGPDBGridCtrl* pGrid = DYNAMIC_DOWNCAST(CBCGPDBGridCtrl, 
	m_pView->GetNewGrid ());
	ASSERT_VALID (pGrid);

	if (m_pView->m_nSourceType == 1 || m_pView->m_nSourceType == 2)
	{
		CString strDBPath;
		if (m_pView->m_nSourceType == 1)
		{
			strDBPath = m_pView->m_strDefaultDBPath;
		}
		else
		{
			strDBPath = m_pView->m_strDBPath;
		}

		if (!pGrid->OpenMSAccessFile (strDBPath))
		{
			return CPropertyPage::OnSetActive();
		}

		CStringList lstTable;
		pGrid->GetTableList (lstTable);

		if (lstTable.IsEmpty ())
		{
			return CPropertyPage::OnSetActive();
		}

		for(POSITION pos = lstTable.GetHeadPosition(); pos != NULL; )
		{
			 m_listboxTables.AddString (lstTable.GetNext(pos));
		}

		m_listboxTables.SetCurSel (0);
	}

	if (m_pView->m_nSourceType == 3)
	{
		CStringList lstTable;
		pGrid->GetTableList (lstTable);

		if (lstTable.IsEmpty ())
		{
			return CPropertyPage::OnSetActive();
		}

		for(POSITION pos = lstTable.GetHeadPosition(); pos != NULL; )
		{
			 m_listboxTables.AddString (lstTable.GetNext(pos));
		}

		m_listboxTables.SetCurSel (0);
	}
	
	return CPropertyPage::OnSetActive();
}

BOOL CDataTablePage::OnWizardFinish() 
{	
	return CPropertyPage::OnWizardFinish();
}

LRESULT CDataTablePage::OnWizardNext()
{
	int nIndex  = m_listboxTables.GetCurSel ();
	if (nIndex != -1 && nIndex != LB_ERR)
	{
		CString strTable;
		m_listboxTables.GetText (nIndex, strTable);

		if (strTable.Find (_T(' ')) >= 0)
		{
			m_pView->m_strTable = _T('[');
			m_pView->m_strTable += strTable;
			m_pView->m_strTable += _T(']');
		}
		else
		{
			m_pView->m_strTable = strTable;
		}
	}

	return CPropertyPage::OnWizardNext();
}

BOOL CDataTablePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd ();
	m_pView = (CBCGPDBGridDemoView*)pFrame->GetActiveView ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
