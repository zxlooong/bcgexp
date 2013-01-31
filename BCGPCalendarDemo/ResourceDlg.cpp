// ResourceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcalendardemo.h"
#include "ResourceDlg.h"

#include "BCGPAppointmentDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceDlg dialog


CResourceDlg::CResourceDlg(CBCGPAppointmentDemoResourceInfo& rInfo, CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CResourceDlg::IDD, pParent)
	, m_Info (rInfo)
{
#ifndef _BCGPCALENDAR_STANDALONE
	EnableVisualManagerStyle ();
#endif

	//{{AFX_DATA_INIT(CResourceDlg)
	m_strDescription = m_Info.GetDescription ();
	m_bVisible = FALSE;
	//}}AFX_DATA_INIT
}


void CResourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResourceDlg)
	DDX_Control(pDX, IDC_INTERVAL_CHECK, m_btnInterval);
	DDX_Control(pDX, IDC_DATETIME_START_STATIC, m_stDateTimeStart);
	DDX_Control(pDX, IDC_TIME_START, m_TimeStart);
	DDX_Control(pDX, IDC_DATETIME_END_STATIC, m_stDateTimeEnd);
	DDX_Control(pDX, IDC_TIME_END, m_TimeEnd);
	DDX_Text(pDX, IDC_DESCRIPTION, m_strDescription);
	DDX_Check(pDX, IDC_VISIBLE_CHECK, m_bVisible);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResourceDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CResourceDlg)
	ON_BN_CLICKED(IDC_INTERVAL_CHECK, OnIntervalCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceDlg message handlers

BOOL CResourceDlg::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();

	UINT nMask = 
		CBCGPDateTimeCtrl::DTM_SPIN         |
		CBCGPDateTimeCtrl::DTM_DATE         |
		CBCGPDateTimeCtrl::DTM_TIME         |
		CBCGPDateTimeCtrl::DTM_CHECKBOX     |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_CHECKED;

	UINT nFlags = 
		CBCGPDateTimeCtrl::DTM_TIME    | 
		CBCGPDateTimeCtrl::DTM_CHECKED | 
		CBCGPDateTimeCtrl::DTM_SPIN;

	m_TimeStart.SetState (nFlags, nMask);
	m_TimeEnd.SetState (nFlags, nMask);

	m_TimeStart.SetDate (m_Info.GetWorkStart ());
	m_TimeEnd.SetDate (m_Info.GetWorkEnd ());

	if (m_Info.GetWorkStart () != COleDateTime () ||
		m_Info.GetWorkEnd () != COleDateTime ())
	{
		m_btnInterval.SetCheck (BST_CHECKED);
	}

	OnIntervalCheck ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResourceDlg::OnOK() 
{
	UpdateData ();

	COleDateTime tmS;
	COleDateTime tmE;

	if (m_btnInterval.GetCheck () == BST_CHECKED)
	{
		tmS = m_TimeStart.GetDate ();
		tmS.SetTime (tmS.GetHour (), tmS.GetMinute (), 0);
		tmE = m_TimeEnd.GetDate ();
		tmE.SetTime (tmE.GetHour (), tmE.GetMinute (), 0);

		if (tmS >= tmE)
		{
			AfxMessageBox (IDS_APPOINTMENT_1);
			return;
		}
	}

	m_Info.SetDescription (m_strDescription);
	m_Info.SetWorkInterval (tmS, tmE);

	CBCGPDialog::OnOK();
}


void CResourceDlg::OnIntervalCheck() 
{
	BOOL bEnabled = m_btnInterval.GetCheck () == BST_CHECKED;

	m_stDateTimeStart.EnableWindow (bEnabled);
	m_TimeStart.EnableWindow (bEnabled);
	m_stDateTimeEnd.EnableWindow (bEnabled);
	m_TimeEnd.EnableWindow (bEnabled);
}
