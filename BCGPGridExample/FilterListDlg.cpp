// FilterListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpgridexample.h"
#include "FilterListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterListDlg dialog


CFilterListDlg::CFilterListDlg(CStringList& lstStrings, FILTER_PARAM& param,
							   CWnd* pParent /*=NULL*/)
	: CDialog(CFilterListDlg::IDD, pParent),
	m_lstStrings (lstStrings),
	m_Param (param)
{
	//{{AFX_DATA_INIT(CFilterListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFilterListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterListDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_FILTER_LIST, m_wndFilterList);
}


BEGIN_MESSAGE_MAP(CFilterListDlg, CDialog)
	//{{AFX_MSG_MAP(CFilterListDlg)
	//}}AFX_MSG_MAP
	ON_CLBN_CHKCHANGE(IDC_FILTER_LIST, OnCheckchangeFilterList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterListDlg message handlers

BOOL CFilterListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FillList ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFilterListDlg::FillList ()
{
	ASSERT_VALID (this);

	m_wndFilterList.ResetContent();

	m_wndFilterList.AddString (_T("(Select All)"));
	m_wndFilterList.SetCheck( 0, m_Param.bAll ? 1 : 0);

	int i = 1;
	BOOL bSomeChecked = FALSE;
	for (POSITION pos = m_lstStrings.GetHeadPosition (); pos != NULL; i++)
	{
		CString& str = m_lstStrings.GetNext (pos);
		m_wndFilterList.AddString (str);

		if (m_Param.bAll)
		{
			m_wndFilterList.SetCheck( i, 1);
		}
		else if (m_Param.lstStrings.Find (str))
		{
			m_wndFilterList.SetCheck( i, 1);
			bSomeChecked = TRUE;
		}
	}

	if (bSomeChecked)
	{
		m_wndFilterList.SetCheck( 0, 2);
	}
}

void CFilterListDlg::OnCheckchangeFilterList() 
{
	int nCurSel = m_wndFilterList.GetCurSel ();
	if (nCurSel == LB_ERR)
	{
		return;
	}

	// "(Select All)" item has been changed
	if (nCurSel == 0)
	{
		int nNewState = m_wndFilterList.GetCheck (0);

		//-------------------
		// Apply to all items
		//-------------------
		int nCount = m_wndFilterList.GetCount ();
		for (int i = 0; i < nCount; i++)
		{
			m_wndFilterList.SetCheck (i, nNewState);
		}
	}
	else
	{
		int nNewState = m_wndFilterList.GetCheck (nCurSel);
		if (nNewState != m_wndFilterList.GetCheck (0))
		{
			//---------------------------
			// Update "(Select All)" item
			//---------------------------
			m_wndFilterList.SetCheck (0, 2);
		}
	}
}

void CFilterListDlg::OnOK() 
{
	UpdateData ();

	//--------------
	// Update params
	//--------------
	m_Param.bAll = m_wndFilterList.GetCheck (0) == 1;
	m_Param.lstStrings.RemoveAll ();

	if (!m_Param.bAll)
	{
		// Add only checked items
		int nCount = m_wndFilterList.GetCount ();

		for (int i = 0; i < nCount; i++)
		{
			CString strNewText;
			m_wndFilterList.GetText (i, strNewText);

			if (m_wndFilterList.GetCheck (i) == 1)
			{
				m_Param.lstStrings.AddTail (strNewText);
			}
		}
	}
	
	CDialog::OnOK();
}
