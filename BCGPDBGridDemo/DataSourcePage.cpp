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
// DataSourcePage.cpp : implementation file
//

#include "stdafx.h"
#include <io.h>
#include "BCGPDBGridDemo.h"
#include "DataSourcePage.h"
#include "DataTablePage.h"

#include "BCGPDBGridDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSourcePage property page

IMPLEMENT_DYNCREATE(CDataSourcePage, CPropertyPage)

CDataSourcePage::CDataSourcePage() : CPropertyPage(CDataSourcePage::IDD)
{
	//{{AFX_DATA_INIT(CDataSourcePage)
	m_bAllowEdit = FALSE;
	m_strMdbFile = _T("");
	m_nDataSource = 0;
	m_bVirtualMode = FALSE;
	//}}AFX_DATA_INIT
}

CDataSourcePage::~CDataSourcePage()
{
}

void CDataSourcePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataSourcePage)
	DDX_Control(pDX, IDC_CHECK_ALLOWEDIT, m_btnAllowEdit);
	DDX_Control(pDX, IDC_EDIT_DSN_CONNECT, m_editConnect);
	DDX_Control(pDX, IDC_BROWSE_MDB_FILE, m_wndEditMdbFile);
	DDX_Check(pDX, IDC_CHECK_ALLOWEDIT, m_bAllowEdit);
	DDX_Text(pDX, IDC_BROWSE_MDB_FILE, m_strMdbFile);
	DDX_Radio(pDX, IDC_RADIO_DEFAULT, m_nDataSource);
	DDX_Check(pDX, IDC_VIRTUAL_MODE, m_bVirtualMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataSourcePage, CPropertyPage)
	//{{AFX_MSG_MAP(CDataSourcePage)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT, OnDataSource)
	ON_BN_CLICKED(IDC_RADIO_MDB, OnDataSource)
	ON_BN_CLICKED(IDC_RADIO_DNS, OnDataSource)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataSourcePage message handlers

BOOL CDataSourcePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_wndEditMdbFile.EnableFileBrowseButton (NULL, _T("MDB Files (*.mdb)|*.mdb|All Files (*.*)|*.*||"));
	m_editConnect.EnableBrowseButton ();

	CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd ();
	m_pView = (CBCGPDBGridDemoView*)pFrame->GetActiveView ();

	ASSERT_VALID (m_pView);

	OnDataSource();

	m_strMdbFile = theApp.GetString (_T("MSAccessPath"));
	m_bVirtualMode = (BOOL) theApp.GetInt (_T("VirtualMode"), TRUE);

	UpdateData (FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDataSourcePage::OnSetActive() 
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent ();
	ASSERT_VALID (pSheet);
	pSheet->SetWizardButtons (PSWIZB_NEXT|PSWIZB_BACK);	

	CWnd* pRadio = GetDlgItem (IDC_RADIO_DNS);
	pRadio->EnableWindow (m_pView->m_nDataType == 2 ? FALSE : TRUE);
	
	return CPropertyPage::OnSetActive();
}

void CDataSourcePage::OnChooseDSN ()
{
	CDatabase m_database;
	m_database.Open(NULL, FALSE, TRUE, _T("ODBC;"), FALSE);
	CString strConnectString = m_database.GetConnect();
	m_editConnect.SetWindowText (strConnectString);
	m_pView->m_strDSNString = strConnectString;
	m_database.Close ();
}

void CCustomBrowseEdit::OnBrowse ()
{
	CDataSourcePage* page = (CDataSourcePage*)GetParent ();
	ASSERT_VALID (page);
	page->OnChooseDSN ();
}

LRESULT CDataSourcePage::OnWizardNext() 
{
	UpdateData ();

	theApp.WriteInt (_T("VirtualMode"), m_bVirtualMode);

	m_pView->m_nSourceType = m_nDataSource + 1;
	m_pView->m_bAllowEdit = m_nDataSource == 0 && m_bAllowEdit;

	if (m_pView->m_nSourceType == 2)
	{
		theApp.WriteString (_T("MSAccessPath"), m_strMdbFile);

		if (m_strMdbFile.IsEmpty ())
		{
			AfxMessageBox (_T("You should choose MDB file first!"));
			return -1;
		}

		if (_taccess (m_strMdbFile, 0) != 0)
		{
			AfxMessageBox (_T("The file does not exist."));
			m_wndEditMdbFile.SetFocus ();
			return -1;
		}

		m_pView->m_strDBPath = m_strMdbFile;
	}

	if (m_pView->m_nSourceType == 1)
	{
		if (_taccess (m_pView->m_strDefaultDBPath, 0) != 0)
		{
			AfxMessageBox (_T("The file bcgpaddressbook.mdb does not exist\n in the same directory as .exe file"));
			return -1;
		}
	}

	SetProperGrid ();

	CBCGPDBGridCtrl* pGrid = DYNAMIC_DOWNCAST(CBCGPDBGridCtrl, 
	m_pView->GetNewGrid ());
	ASSERT_VALID (pGrid);

	pGrid->SetReadOnly (!m_pView->m_bAllowEdit);
	
	if (m_pView->m_nSourceType == 3)
	{
		CString strConnectString = _T ("");
		if (m_pView->m_nDataType == 1) // ADO
		{
			CDatabase m_database;
			m_database.Open (NULL, FALSE, TRUE, _T("ODBC;"), FALSE);
			strConnectString = m_database.GetConnect();

			if (strConnectString.GetLength () <= 0) 	 
			{
				AfxMessageBox (_T("You should choose Database! Try again!"));
				return -1;
			}

			if (strConnectString.Find(_T("ODBC;")) != -1)
			{
				strConnectString = strConnectString.Mid(5);
			}
		}

		if (!pGrid->OpenDB (strConnectString))
		{
			AfxMessageBox (_T("Error Open Database! Try again!"));
			return -1;
		}
	}

	return CPropertyPage::OnWizardNext ();
}

void CDataSourcePage::OnDataSource() 
{
	UpdateData ();

	m_btnAllowEdit.EnableWindow (m_nDataSource == 0);
	m_wndEditMdbFile.EnableWindow (m_nDataSource == 1);
	m_editConnect.EnableWindow (m_nDataSource == 2);

	if (m_nDataSource == 1)
	{
		m_wndEditMdbFile.SetFocus ();
	}
}

void CDataSourcePage::SetProperGrid ()
{
	switch (m_pView->m_nDataType)
	{
	case 0: // ODBC
		{ 
			m_pView->m_pNewGrid  = m_nDataSource == 0 ?
				new CMyODBCGridCtrl : new CBCGPODBCGridCtrl;
		}
		break;
	case 1: // ADO
		{
			m_pView->m_pNewGrid = m_nDataSource == 0 ?
				new CMyADOGridCtrl : new CBCGPADOGridCtrl;

		}
		break;
#ifndef _WIN64
	case 2: // DAO
		{
			m_pView->m_pNewGrid = m_nDataSource == 0 ?
				new CMyDAOGridCtrl : new CBCGPDAOGridCtrl;
		}
		break;
#endif // !_WIN64
	}

	if (m_bVirtualMode && m_pView->m_pNewGrid != NULL)
	{
		m_pView->m_pNewGrid->EnableVirtualMode ();
	}
}
