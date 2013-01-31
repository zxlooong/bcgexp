// FilterStringDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpgridexample.h"
#include "FilterStringDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterStringDlg dialog


CFilterStringDlg::CFilterStringDlg(FILTER_PARAM& param, CWnd* pParent /*=NULL*/)
	: CDialog(CFilterStringDlg::IDD, pParent),
	m_param (param)
{
	//{{AFX_DATA_INIT(CFilterStringDlg)
	m_strFilter = param.strFilter;
	//}}AFX_DATA_INIT
}


void CFilterStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterStringDlg)
	DDX_Text(pDX, IDC_FILTER, m_strFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterStringDlg, CDialog)
	//{{AFX_MSG_MAP(CFilterStringDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterStringDlg message handlers

void CFilterStringDlg::OnOK() 
{
	UpdateData ();

	m_param.strFilter = m_strFilter;
	m_param.bAll = m_strFilter.IsEmpty ();
	
	CDialog::OnOK();
}
