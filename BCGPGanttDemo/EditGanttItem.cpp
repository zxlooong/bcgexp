// CEditGanttItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditGanttItem.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditGanttItemDlg dialog


CEditGanttItemDlg::CEditGanttItemDlg(CBCGPGanttItem& item, CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CEditGanttItemDlg::IDD, pParent)
	, m_pGanttItem (&item)
	, m_bMilestoneItem (FALSE)
{

	//{{AFX_DATA_INIT(CEditGanttItemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEditGanttItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditGanttItemDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_DATETIME1, m_wndStartDate);
	DDX_Control(pDX, IDC_DATETIME2, m_wndFinishDate);
	DDX_Control(pDX, IDC_COLOR1, m_wndColorBar);
	DDX_Control(pDX, IDC_COLOR2, m_wndColorComplete);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditGanttItemDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CEditGanttItemDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditGanttItemDlg message handlers

BOOL CEditGanttItemDlg::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();

	// Create color picker buttons:

	m_wndColorBar.EnableAutomaticButton (_T("Automatic"), CLR_DEFAULT);
	m_wndColorBar.EnableOtherButton (_T("Other"));
	m_wndColorBar.SetColumnsNumber (10);

	m_wndColorComplete.EnableAutomaticButton (_T("Automatic"), CLR_DEFAULT);
	m_wndColorComplete.EnableOtherButton (_T("Other"));
	m_wndColorComplete.SetColumnsNumber (10);

	const UINT stateFlags =
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME;

	const UINT stateMask = 
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME | 
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;

	m_wndStartDate.SetState (stateFlags, stateMask);
	m_wndFinishDate.SetState (stateFlags, stateMask);

	ReadItemData ();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEditGanttItemDlg::ReadItemData ()
{
	m_bMilestoneItem = m_pGanttItem->IsMileStone ();

	SetDlgItemText (IDC_EDITNAME, m_pGanttItem->GetName ());
	m_wndStartDate.SetDate ((DATE)m_pGanttItem->GetStartTime ());
	m_wndFinishDate.SetDate ((DATE)m_pGanttItem->GetFinishTime ());
	m_wndFinishDate.EnableWindow (!m_bMilestoneItem);
	SetDlgItemInt (IDC_EDITPROGRESS, (UINT)(m_pGanttItem->GetProgress () * 100), FALSE);

	COLORREF clr = m_pGanttItem->GetPrimaryColor ();
	m_wndColorBar.SetColor (clr == CLR_DEFAULT ? (COLORREF)-1 : clr);
	clr = m_pGanttItem->GetCompleteColor ();
	m_wndColorComplete.SetColor (clr == CLR_DEFAULT ? (COLORREF)-1 : clr);
}

BOOL CEditGanttItemDlg::WriteItemData ()
{
	CString sName;
	GetDlgItemText (IDC_EDITNAME, sName);

	COleDateTime dtStart = (COleDateTime)m_wndStartDate.GetDate ();
	COleDateTime dtFinish = m_bMilestoneItem ? dtStart : (COleDateTime)m_wndFinishDate.GetDate ();

	if (!m_bMilestoneItem && dtFinish <= dtStart)
	{
		return FALSE;
	}

	BOOL bTrans;
	UINT nProgress = GetDlgItemInt (IDC_EDITPROGRESS, &bTrans, FALSE);
	if (!bTrans)
	{
		return FALSE;
	}

	m_pGanttItem->SetName (sName);
	m_pGanttItem->SetInterval (dtStart, dtFinish);
	m_pGanttItem->SetProgress (nProgress / 100.0);
	m_pGanttItem->SetPrimaryColor (m_wndColorBar.GetColor ());
	m_pGanttItem->SetCompleteColor (m_wndColorComplete.GetColor ());
	return TRUE;
}

void CEditGanttItemDlg::OnOK ()
{
	if (WriteItemData ())
	{
		CBCGPDialog::OnOK ();
	}
}
