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
// GanttFrame.cpp : implementation file
//

#include "stdafx.h"
#include "../bcgporganizer.h"
#include "GanttFrame.h"

//#include "Appointment.h"

#include "../MainButtonsGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CGanttDialogBar1, CEditDialogBar, VERSIONABLE_SCHEMA | 1)

CGanttDialogBar1::CGanttDialogBar1 ()
	: m_bFirstTime (TRUE)
{
}

CGanttDialogBar1::~CGanttDialogBar1 ()
{
}

BEGIN_MESSAGE_MAP(CGanttDialogBar1, CEditDialogBar)
END_MESSAGE_MAP()

void CGanttDialogBar1::DoDataExchange(CDataExchange* pDX)
{
	CEditDialogBar::DoDataExchange (pDX);

	DDX_Text(pDX, IDC_GANTT_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_GANTT_EDIT_DATE_START, m_DateStart);
	DDX_Control(pDX, IDC_GANTT_EDIT_TIME_START, m_TimeStart);

	if (m_bFirstTime)
	{
		m_bFirstTime = FALSE;

		UINT nMask = 
			CBCGPDateTimeCtrl::DTM_SPIN         |
			CBCGPDateTimeCtrl::DTM_DATE         |
			CBCGPDateTimeCtrl::DTM_TIME         |
			CBCGPDateTimeCtrl::DTM_CHECKBOX     |
			CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
			CBCGPDateTimeCtrl::DTM_CHECKED;

		UINT nFlags = CBCGPDateTimeCtrl::DTM_CHECKED | CBCGPDateTimeCtrl::DTM_SPIN;
		//-------------------
		// Setup date fields:
		//-------------------
		m_DateStart.SetState (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | nFlags, nMask);
		m_DateStart.SetDate (m_dtStart);

		m_TimeStart.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
		m_TimeStart.SetDate (m_dtStart);
	}
}

BOOL CGanttDialogBar1::OnInitDialogBar()
{
	AddResize (IDC_GANTT_EDIT_NAME, CEditDialogBar::e_ResizeSizeH);
	AddResize (IDC_GANTT_EDIT_SEPARATOR, CEditDialogBar::e_ResizeSizeH);

	return CEditDialogBar::OnInitDialogBar();
}


IMPLEMENT_SERIAL(CGanttDialogBar2, CEditDialogBar, VERSIONABLE_SCHEMA | 1)

CGanttDialogBar2::CGanttDialogBar2 ()
	: m_bFirstTime (TRUE)
{
}

CGanttDialogBar2::~CGanttDialogBar2 ()
{
}

BEGIN_MESSAGE_MAP(CGanttDialogBar2, CEditDialogBar)
END_MESSAGE_MAP()

void CGanttDialogBar2::DoDataExchange(CDataExchange* pDX)
{
	CEditDialogBar::DoDataExchange (pDX);

	DDX_Control(pDX, IDC_GANTT_EDIT_DATE_END, m_DateEnd);
	DDX_Control(pDX, IDC_GANTT_EDIT_TIME_END, m_TimeEnd);
	DDX_Control (pDX, IDC_GANTT_EDIT_PROGRESS, m_Progress);
	DDX_Control (pDX, IDC_GANTT_EDIT_PROGRESS_SPIN, m_ProgressSpin);
	DDX_Text (pDX, IDC_GANTT_EDIT_PROGRESS, m_lProgress);

	if (m_bFirstTime)
	{
		m_bFirstTime = FALSE;

		UINT nMask = 
			CBCGPDateTimeCtrl::DTM_SPIN         |
			CBCGPDateTimeCtrl::DTM_DATE         |
			CBCGPDateTimeCtrl::DTM_TIME         |
			CBCGPDateTimeCtrl::DTM_CHECKBOX     |
			CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
			CBCGPDateTimeCtrl::DTM_CHECKED;

		UINT nFlags = CBCGPDateTimeCtrl::DTM_CHECKED | CBCGPDateTimeCtrl::DTM_SPIN;
		//-------------------
		// Setup date fields:
		//-------------------
		m_DateEnd.SetState (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | nFlags, nMask);
		m_DateEnd.SetDate (m_dtFinish);

		m_TimeEnd.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
		m_TimeEnd.SetDate (m_dtFinish);
	}
}

BOOL CGanttDialogBar2::OnInitDialogBar()
{
	return CEditDialogBar::OnInitDialogBar();
}


/////////////////////////////////////////////////////////////////////////////
// CGanttFrame

IMPLEMENT_DYNAMIC(CGanttFrame, CEditFrameDialog)

CGanttFrame::CGanttFrame(CBCGPGanttItem& item,
							BOOL bIsMilestone /*= FALSE*/,
							BOOL bReadOnly /*= FALSE*/,
							CWnd* pParent /*=NULL*/)
	: CEditFrameDialog(IDR_GANTTFRAME, pParent)
	, m_Item	    (item)
	, m_bMilestone  (bIsMilestone)
	, m_bReadOnly   (bReadOnly)
	, m_bDeleted    (FALSE)
	, m_bPrivate    (FALSE)
	, m_Importance  (e_ImportanceNormal)
{
	m_wndDialogBar1.m_strName  = m_Item.GetName ();
	m_wndDialogBar1.m_dtStart  = m_Item.GetStartTime ();

	m_wndDialogBar2.m_dtFinish = m_Item.GetFinishTime ();
	m_wndDialogBar2.m_lProgress = (long)(m_Item.GetProgress () * 100.0 + 0.5);

	m_bCompleted = m_Item.IsCompleted ();

	m_nLabel    = -1;

	for (int i = 0; i < c_CategoryCount; i++)
	{
		if (m_Item.GetPrimaryColor () == c_CategoryColors[i])
		{
			m_nLabel = i;
			break;
		}
	}
}

CGanttFrame::~CGanttFrame()
{
}

void CGanttFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if ((GetStyle() & FWS_ADDTOTITLE) == 0)
		return;     // leave it alone!

	SetTitle (m_bMilestone ? _T("Milestone") : _T("Task"));

	if (bAddToTitle)
	{
		UpdateFrameTitleForDocument (m_Item.GetName ().IsEmpty () ?
			_T("Untitled") : m_Item.GetName ());
	}
	else
	{
		UpdateFrameTitleForDocument(NULL);
	}
}

BEGIN_MESSAGE_MAP(CGanttFrame, CEditFrameDialog)
	//{{AFX_MSG_MAP(CGanttFrame)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_GANTT_EDIT_SAVE_CLOSE, OnSaveClose)
	ON_COMMAND(ID_GANTT_EDIT_DELETE, OnDelete)
	ON_UPDATE_COMMAND_UI(ID_GANTT_EDIT_DELETE, OnUpdateDelete)
	ON_COMMAND(ID_GANTT_EDIT_PRIVATE, OnPrivate)
	ON_UPDATE_COMMAND_UI(ID_GANTT_EDIT_PRIVATE, OnUpdatePrivate)
	ON_COMMAND(ID_GANTT_EDIT_IMPORTANCE_LOW, OnImportanceLow)
	ON_UPDATE_COMMAND_UI(ID_GANTT_EDIT_IMPORTANCE_LOW, OnUpdateImportanceLow)
	ON_COMMAND(ID_GANTT_EDIT_IMPORTANCE_HIGH, OnImportanceHigh)
	ON_UPDATE_COMMAND_UI(ID_GANTT_EDIT_IMPORTANCE_HIGH, OnUpdateImportanceHigh)
	ON_UPDATE_COMMAND_UI(IDC_GANTT_EDIT_LABEL, OnUpdateLabel)
	ON_COMMAND_RANGE(ID_CATEGORY_1, ID_CATEGORY_6, OnCategory)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CATEGORY_1, ID_CATEGORY_6, OnUpdateCategory)
	ON_COMMAND(ID_GANTT_MARK_COMPLETE, OnMarkComplete)
	ON_UPDATE_COMMAND_UI(ID_GANTT_MARK_COMPLETE, OnUpdateMarkComplete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGanttFrame message handlers

BOOL CGanttFrame::LoadPanelImages ()
{
	m_PanelImages.SetImageSize (CSize (16, 16));
	return m_PanelImages.Load (IDB_GANTT_BUTTONS);
}

BOOL CGanttFrame::CreateStatusBar ()
{
	return TRUE;
}

BOOL CGanttFrame::CreateOtherBars ()
{
	if (!m_wndDialogBar1.Create (_T(""), this, FALSE, MAKEINTRESOURCE(IDD_GANTT_DIALOGBAR1), 
			WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR, 0, 0))
	{
		return FALSE;
	}

	if (!m_wndDialogBar2.Create (_T(""), this, FALSE, MAKEINTRESOURCE(IDD_GANTT_DIALOGBAR2), 
			WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR, 0, 0))
	{
		return FALSE;
	}

	EnableDocking (CBRS_ALIGN_ANY);
	DockControlBar (&m_wndDialogBar1);
	DockControlBar (&m_wndDialogBar2);

	CRect rectBar;
	m_wndDialogBar1.GetClientRect (rectBar);
	m_wndDialogBar1.SetMinSize (rectBar.Size ());
	m_wndDialogBar2.GetClientRect (rectBar);
	m_wndDialogBar2.SetMinSize (rectBar.Size ());

	ShowControlBar (&m_wndDialogBar1, TRUE, FALSE, TRUE);
	ShowControlBar (&m_wndDialogBar2, !m_bMilestone, FALSE, FALSE);

	if (!m_bMilestone)
	{
		m_wndDialogBar2.m_Progress.EnableWindow (!m_bCompleted);
		m_wndDialogBar2.m_ProgressSpin.EnableWindow (!m_bCompleted);
	}

	return TRUE;
}

void CGanttFrame::AddMainCategory ()
{
	CEditFrameDialog::AddMainCategory ();

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("Main Menu"), IDB_PLANNER_FILE_SMALL, IDB_PLANNER_FILE_LARGE);

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE, _T("&Save"), 0, 0, TRUE));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("Save &As..."), 1, 1, TRUE));
	pMainPanel->Add (new CBCGPRibbonButton (ID_GANTT_EDIT_DELETE, _T("&Delete"), 2, 2, TRUE));

	pMainPanel->Add (new CBCGPRibbonSeparator (TRUE));

	CBCGPRibbonButton* pBtnPrint = new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 3, 3);
	pBtnPrint->AddSubItem (new CBCGPRibbonLabel (_T("Preview and print the document")));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT, _T("&Print"), 3, 3, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_DIRECT, _T("&Quick Print"), 5, 5, TRUE));
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_PREVIEW, _T("Print Pre&view"), 6, 6, TRUE));
	pMainPanel->Add (pBtnPrint);

	pMainPanel->Add (new CBCGPRibbonSeparator (TRUE));

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_CLOSE, _T("&Close"), 4, 4));

	pMainPanel->AddToRight (new CMainButtonsGroup (_T("Actions")));

	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_TOOLS_OPTIONS, _T("Opt&ions"), 7));
}

void CGanttFrame::AddTabs ()
{
	AddTab_Home ();

	CEditFrameDialog::AddTabs ();
}

void CGanttFrame::AddTab_Home ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("Appointment\nh"), IDB_GANTT_HOME_SMALL, IDB_GANTT_HOME_LARGE);

	CBCGPRibbonPanel* pPanelActions = pCategory->AddPanel (_T("Actions"), m_PanelImages.ExtractIcon (3));
	pPanelActions->Add (new CBCGPRibbonButton (ID_GANTT_EDIT_SAVE_CLOSE, _T("Save && Close\nav"), 0, 0));
	pPanelActions->Add (new CBCGPRibbonSeparator ());
	pPanelActions->Add (new CBCGPRibbonButton (ID_GANTT_EDIT_DELETE, _T("Delete\nd"), 1, 1));

	CBCGPRibbonPanel* pPanelOptions = pCategory->AddPanel (_T("Options"), m_PanelImages.ExtractIcon (4));

	pPanelOptions->Add (new CBCGPRibbonButton (ID_GANTT_MARK_COMPLETE, _T("Mark Complete\nm"), 2, 2));
	CBCGPRibbonButton* pLabel = new CBCGPRibbonButton (IDC_GANTT_EDIT_LABEL, _T("Categorize\nt"), 3, 3);
	pPanelOptions->Add (pLabel);
	CompleteCategories (*pLabel);

	pPanelOptions->Add (new CBCGPRibbonButton (ID_GANTT_EDIT_PRIVATE, _T("Private\nv"), 4, -1));
	pPanelOptions->Add (new CBCGPRibbonButton (ID_GANTT_EDIT_IMPORTANCE_HIGH, _T("High Importance\nh"), 5, -1));
	pPanelOptions->Add (new CBCGPRibbonButton (ID_GANTT_EDIT_IMPORTANCE_LOW, _T("Low Importance\nl"), 6, -1));
}

void CGanttFrame::OnPrivate ()
{
	m_bPrivate = !m_bPrivate;
}

void CGanttFrame::OnUpdatePrivate (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_bPrivate);
}

void CGanttFrame::OnImportanceLow ()
{
	m_Importance = m_Importance == e_ImportanceLow ? e_ImportanceNormal : e_ImportanceLow;
}

void CGanttFrame::OnUpdateImportanceLow (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_Importance == e_ImportanceLow);
}

void CGanttFrame::OnImportanceHigh ()
{
	m_Importance = m_Importance == e_ImportanceHigh ? e_ImportanceNormal : e_ImportanceHigh;
}

void CGanttFrame::OnUpdateImportanceHigh (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_Importance == e_ImportanceHigh);
}

void CGanttFrame::OnFileClose ()
{
	OnCancel ();
}

void CGanttFrame::OnSaveClose ()
{
	OnOK ();
}

void CGanttFrame::OnDelete ()
{
	m_bDeleted = TRUE;

	OnCancel ();
}

void CGanttFrame::OnUpdateDelete (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CGanttFrame::OnOK() 
{
	m_wndDialogBar1.UpdateData ();

	COleDateTime dtS = m_wndDialogBar1.m_DateStart.GetDate ();
	COleDateTime tmS = m_wndDialogBar1.m_TimeStart.GetDate ();

	COleDateTime dtF = dtS;
	COleDateTime tmF = tmS;

	if (!m_bMilestone)
	{
		m_wndDialogBar2.UpdateData ();

		dtF = m_wndDialogBar2.m_DateEnd.GetDate ();
		tmF = m_wndDialogBar2.m_TimeEnd.GetDate ();
	}

	dtS = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
		tmS.GetHour (), tmS.GetMinute (), 0);

	dtF = COleDateTime (dtF.GetYear (), dtF.GetMonth (), dtF.GetDay (),
		tmF.GetHour (), tmF.GetMinute (), 0);

	if (!m_bMilestone)
	{
		if (dtS >= dtF)
		{
			AfxMessageBox (IDS_GANTT_1);
			return;
		}
	}	

	m_Item.SetInterval (dtS, dtF);

	m_Item.SetName (m_wndDialogBar1.m_strName);

	if (m_bCompleted)
	{
		m_Item.SetCompleted ();
	}
	else
	{
		m_Item.SetProgress (m_bMilestone ? 0.0 : (m_wndDialogBar2.m_lProgress / 100.0));
	}

	if (m_nLabel == -1)
	{
		m_Item.SetPrimaryColor (CLR_DEFAULT);
		m_Item.SetCompleteColor (CLR_DEFAULT);
	}
	else
	{
		COLORREF clr = c_CategoryColors[m_nLabel];

		m_Item.SetPrimaryColor (clr);
/*
		double H, L, S;
		CBCGPDrawManager::RGBtoHSL (clr, &H, &S, &L);
		H = H * 360.0 + 235.0;
		H = H - ((int)(H / 360)) * 360;
		clr = CBCGPDrawManager::HLStoRGB_TWO (H, L, S);

		m_Item.SetCompleteColor (clr);
*/
	}

	CEditFrameDialog::OnOK();
}

void CGanttFrame::OnUpdateLabel (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CGanttFrame::OnCategory(UINT nID)
{
	int nLabel = (int)(nID - ID_CATEGORY_1);
	if (m_nLabel == nLabel)
	{
		m_nLabel = -1;
	}
	else
	{
		m_nLabel = nLabel;
	}
}

void CGanttFrame::OnUpdateCategory(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nLabel == (int)(pCmdUI->m_nID - ID_CATEGORY_1));
}

void CGanttFrame::OnMarkComplete()
{
	m_bCompleted = !m_bCompleted;

	if (!m_bMilestone)
	{
		m_wndDialogBar2.m_lProgress = m_bCompleted 
			? 100
			: (long)(m_Item.GetProgress () * 100.0 + 0.5);

		m_wndDialogBar2.m_Progress.EnableWindow (!m_bCompleted);
		m_wndDialogBar2.m_ProgressSpin.EnableWindow (!m_bCompleted);

		m_wndDialogBar2.UpdateData (FALSE);
	}
}

void CGanttFrame::OnUpdateMarkComplete(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_bCompleted);
}
