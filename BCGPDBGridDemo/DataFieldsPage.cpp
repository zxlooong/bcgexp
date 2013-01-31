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
#include "DataFieldsPage.h"
#include "BCGPDBGridDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDataFieldsPage, CPropertyPage)

CDataFieldsPage::CDataFieldsPage() : CPropertyPage(CDataFieldsPage::IDD)
{
	//{{AFX_DATA_INIT(CDataFieldsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bOrderWasChanged = FALSE;
}

CDataFieldsPage::~CDataFieldsPage()
{
}
//*******************************************************************************
void CDataFieldsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataFieldsPage)
	DDX_Control(pDX, IDC_BCGBARRES_MOVEUP, m_btnMoveUp);
	DDX_Control(pDX, IDC_BCGBARRES_MOVEDOWN, m_wndMoveDown);
	DDX_Control(pDX, IDC_BCGBARRES_LIST, m_wndList);
	DDX_Control(pDX, IDC_BCGBARRES_RESET, m_wndReset);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDataFieldsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDataFieldsPage)
	ON_LBN_SELCHANGE(IDC_BCGBARRES_LIST, OnSelchange)
	ON_LBN_DBLCLK(IDC_BCGBARRES_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_BCGBARRES_MOVEDOWN, OnMoveDown)
	ON_BN_CLICKED(IDC_BCGBARRES_MOVEUP, OnMoveUp)
	ON_BN_CLICKED(IDC_BCGBARRES_RESET, OnReset)
	ON_BN_CLICKED(ID_BTN_SELECT_ALL, OnSelectAll)
	ON_BN_CLICKED(ID_BTN_SELECT_NONE, OnSelectNone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataFieldsPage message handlers

BOOL CDataFieldsPage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent ();
	ASSERT_VALID (pSheet);
	pSheet->SetWizardButtons (PSWIZB_NEXT|PSWIZB_FINISH);

	return CPropertyPage::OnSetActive ();
}

BOOL CDataFieldsPage::OnWizardFinish() 
{
	CStringList lstFields;
	
	for (int nIndex = 0; nIndex < m_wndList.GetCount (); nIndex++)
	{
		if (m_wndList.GetCheck (nIndex))
		{
			if (m_wndList.GetCheck (nIndex))
			{
				CString strField;
				m_wndList.GetText (nIndex, strField);

				lstFields.AddTail (strField);
			}
		}
	}

	if (lstFields.IsEmpty ())
	{
		AfxMessageBox (_T("Please select display fields!"));
		return 0;
	}

	//----------------------
	//Prepare SQL statement:
	//----------------------
	CString strSQL = _T("SELECT ");

	if (lstFields.GetCount () == m_wndList.GetCount () && !m_bOrderWasChanged)
	{
		//------------
		// All fields:
		//------------
		strSQL += _T(" * ");
	}
	else
	{
		for (POSITION pos = lstFields.GetHeadPosition (); pos != NULL;)
		{
			CString strField (lstFields.GetNext (pos));

			if (strField.Find(_T(" ")) != -1)
			{
				strField = _T("[") + strField;
				strField += _T("]");
			}

			strSQL += strField;

			if (pos != NULL)
			{
				strSQL += _T(",");
			}
		}
	}

	strSQL += _T(" FROM ");
	strSQL += m_pView->m_strTable;

	CBCGPDBGridCtrl* pGrid = DYNAMIC_DOWNCAST(CBCGPDBGridCtrl, 
	m_pView->GetNewGrid ());
	ASSERT_VALID (pGrid);

	CWaitCursor wait;

	if (!pGrid->OpenSQL (strSQL))
	{
		pGrid->Close ();	
	}
	
	m_pView->ReplaceGrid (m_pView->m_pNewGrid);

	return CPropertyPage::OnWizardFinish();
}

void CDataFieldsPage::OnSelchange() 
{
	m_btnMoveUp.EnableWindow (m_wndList.GetCurSel () > 0);
	m_wndMoveDown.EnableWindow (m_wndList.GetCurSel () < m_wndList.GetCount () - 1);
}

void CDataFieldsPage::OnDblclkList() 
{
	int nSel = m_wndList.GetCurSel ();
	if (nSel >= 0)
	{
		m_wndList.SetCheck (nSel, !m_wndList.GetCheck (nSel));
	}
}

void CDataFieldsPage::OnMoveDown() 
{
	MoveItem (FALSE);
}

void CDataFieldsPage::OnMoveUp() 
{
	MoveItem (TRUE);
}

BOOL CDataFieldsPage::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd ();
	m_pView = (CBCGPDBGridDemoView*)pFrame->GetActiveView ();

	PopulateList ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataFieldsPage::OnOK() 
{
	CDialog::OnOK();
}

void CDataFieldsPage::OnReset() 
{
	m_wndList.ResetContent ();
	PopulateList ();
}

void CDataFieldsPage::MoveItem (BOOL bMoveUp)
{
	int nSel = m_wndList.GetCurSel ();

	CString str;
	m_wndList.GetText (nSel, str);
	DWORD_PTR dwData = m_wndList.GetItemData (nSel);
	BOOL bCheck = m_wndList.GetCheck (nSel);

	m_wndList.DeleteString (nSel);

	int nNewIndex = bMoveUp ? nSel - 1 : nSel + 1;

	int nIndex = m_wndList.InsertString (nNewIndex, str);

	m_wndList.SetItemData (nIndex, dwData);
	m_wndList.SetCheck (nIndex, bCheck);

	m_wndList.SetCurSel (nIndex);
	OnSelchange();

	m_bOrderWasChanged = TRUE;
}

void CDataFieldsPage::PopulateList (BOOL bCheckItems)
{
	CWaitCursor wait;

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

		CStringList lstField;
		if (!pGrid->OpenMSAccessFile (strDBPath))
		{
			return;
		}

		pGrid->GetFieldList (m_pView->m_strTable, lstField);

		int i = 0;
		for(POSITION pos = lstField.GetHeadPosition(); pos != NULL; i++)
		{
			int nIndex = m_wndList.AddString (lstField.GetNext(pos));
			m_wndList.SetItemData (nIndex, (DWORD_PTR) i);
			m_wndList.SetCheck (nIndex, bCheckItems);
		}
	}

	if (m_pView->m_nSourceType == 3)
	{
		CStringList lstField;
		pGrid->GetFieldList (m_pView->m_strTable, lstField);

		int i = 0;
		for(POSITION pos = lstField.GetHeadPosition(); pos != NULL; i++)
		{
			int nIndex = m_wndList.AddString (lstField.GetNext(pos));
			m_wndList.SetItemData (nIndex, (DWORD_PTR) i);
			m_wndList.SetCheck (nIndex, bCheckItems);
		}
	}

	m_wndList.SetCurSel (0);
	OnSelchange();
}


void CDataFieldsPage::OnSelectAll() 
{
	m_wndList.ResetContent ();	
	PopulateList (TRUE);
}

void CDataFieldsPage::OnSelectNone() 
{
	m_wndList.ResetContent ();	
	PopulateList (FALSE);
}
