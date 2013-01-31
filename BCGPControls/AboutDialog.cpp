// AboutDialog.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcontrols.h"
#include "AboutDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog

CAboutDialog::CAboutDialog() : CDialog(CAboutDialog::IDD)
{
	//{{AFX_DATA_INIT(CAboutDialog)
	m_strVersion = _T("");
	//}}AFX_DATA_INIT
	m_strVersion.Format (_T("%d.%d"), _BCGCBPRO_VERSION_MAJOR, _BCGCBPRO_VERSION_MINOR);
}

BOOL CAboutDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_btnMail.SetURLPrefix (_T("mailto:"));
	m_btnMail.SetURL (_T("info@bcgsoft.com"));
	m_btnMail.SizeToContent ();
	m_btnMail.SetTooltip (_T("Send mail to author"));

	m_bntURL.SizeToContent ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDialog)
	DDX_Control(pDX, IDC_URL, m_bntURL);
	DDX_Control(pDX, IDC_MAIL, m_btnMail);
	DDX_Text(pDX, IDC_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDialog, CDialog)
	//{{AFX_MSG_MAP(CAboutDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

