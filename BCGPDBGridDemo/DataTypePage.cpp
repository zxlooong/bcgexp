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
// DataTypePage.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPDBGridDemo.h"
#include "DataTypePage.h"
#include "BCGPDBGridDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataTypePage property page

IMPLEMENT_DYNCREATE(CDataTypePage, CPropertyPage)

CDataTypePage::CDataTypePage() : CPropertyPage(CDataTypePage::IDD)
{
	//{{AFX_DATA_INIT(CDataTypePage)
	//}}AFX_DATA_INIT
}

CDataTypePage::~CDataTypePage()
{
}

void CDataTypePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataTypePage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataTypePage, CPropertyPage)
	//{{AFX_MSG_MAP(CDataTypePage)
	ON_BN_CLICKED(IDC_RADIO_ADO, OnRadioAdo)
	ON_BN_CLICKED(IDC_RADIO_DAO, OnRadioDao)
	ON_BN_CLICKED(IDC_RADIO_ODBC, OnRadioOdbc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataTypePage message handlers

BOOL CDataTypePage::OnSetActive() 
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent ();
	ASSERT_VALID (pSheet);
	
	pSheet->SetWizardButtons (PSWIZB_NEXT);		
	
	return CPropertyPage::OnSetActive();
}

LRESULT CDataTypePage::OnWizardNext() 
{
	//Set Proper Grid

/*	switch (m_pView->m_nDataType)
	{
	case 0: //ODBC
		{ 
			m_pView->m_pNewGrid  = new CBCGPODBCGridCtrl;
		}
		break;
	case 1: //ADO
		{
			m_pView->m_pNewGrid = new CBCGPADOGridCtrl;

		}
		break;
	case 2: //DAO
		{
			m_pView->m_pNewGrid = new CBCGPDAOGridCtrl;
		}
		break;
	}*/
	
	return CPropertyPage::OnWizardNext();
}

void CDataTypePage::OnRadioAdo() 
{
	m_pView->m_nDataType = 1;
}

void CDataTypePage::OnRadioDao() 
{
	m_pView->m_nDataType = 2;	
}

void CDataTypePage::OnRadioOdbc() 
{
	m_pView->m_nDataType = 0;
}

BOOL CDataTypePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd ();
	m_pView = (CBCGPDBGridDemoView*)pFrame->GetActiveView ();
	m_pView->m_nDataType = 0;

	CButton* pRadio = (CButton*)GetDlgItem (IDC_RADIO_ODBC);
	pRadio->SetCheck (1);

#ifdef _WIN64
	GetDlgItem  (IDC_RADIO_DAO)->EnableWindow(false); // DAO not available on WIN64!
#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
