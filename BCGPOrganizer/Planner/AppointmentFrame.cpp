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
// AppointmentFrame.cpp : implementation file
//

#include "stdafx.h"
#include "../bcgporganizer.h"
#include "AppointmentFrame.h"

#include "RecurrenceDlg.h"
#include "Appointment.h"

#include "../MainButtonsGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CAppointmentDialogBar1, CEditDialogBar, VERSIONABLE_SCHEMA | 1)

CAppointmentDialogBar1::CAppointmentDialogBar1 ()
{
}

CAppointmentDialogBar1::~CAppointmentDialogBar1 ()
{
}

BEGIN_MESSAGE_MAP(CAppointmentDialogBar1, CEditDialogBar)
END_MESSAGE_MAP()

void CAppointmentDialogBar1::DoDataExchange(CDataExchange* pDX)
{
	CEditDialogBar::DoDataExchange (pDX);

	DDX_Text(pDX, IDC_APP_EDIT_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_APP_EDIT_LOCATION, m_strLocation);
	DDX_Check(pDX, IDC_APP_EDIT_MEETING, m_bMeeting);
	DDX_Check(pDX, IDC_APP_EDIT_PHONECALL, m_bPhoneCall);
}

BOOL CAppointmentDialogBar1::OnInitDialogBar()
{
	AddResize (IDC_APP_EDIT_SUBJECT, CEditDialogBar::e_ResizeSizeH);
	AddResize (IDC_APP_EDIT_LOCATION, CEditDialogBar::e_ResizeSizeH);
	AddResize (IDC_APP_EDIT_MEETING, CEditDialogBar::e_ResizeMoveH);
	AddResize (IDC_APP_EDIT_PHONECALL, CEditDialogBar::e_ResizeMoveH);

	return CEditDialogBar::OnInitDialogBar();
}

IMPLEMENT_SERIAL(CAppointmentDialogBar2, CEditDialogBar, VERSIONABLE_SCHEMA | 1)

CAppointmentDialogBar2::CAppointmentDialogBar2 ()
	: m_bFirstTime (TRUE)
{
}

CAppointmentDialogBar2::~CAppointmentDialogBar2 ()
{
}

BEGIN_MESSAGE_MAP(CAppointmentDialogBar2, CEditDialogBar)
	ON_BN_CLICKED(ID_APP_EDIT_ALLDAY, OnAllDay)
END_MESSAGE_MAP()

void CAppointmentDialogBar2::DoDataExchange(CDataExchange* pDX)
{
	CEditDialogBar::DoDataExchange (pDX);

	DDX_Control(pDX, IDC_APP_EDIT_DATE_START, m_DateStart);
	DDX_Control(pDX, IDC_APP_EDIT_TIME_START, m_TimeStart);
	DDX_Control(pDX, IDC_APP_EDIT_DATE_END, m_DateEnd);
	DDX_Control(pDX, IDC_APP_EDIT_TIME_END, m_TimeEnd);
	DDX_Control(pDX, ID_APP_EDIT_ALLDAY, m_AllDay);
	DDX_Check(pDX, ID_APP_EDIT_ALLDAY, m_bAllDay);

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

		m_DateEnd.SetState (CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_DROPCALENDAR | nFlags, nMask);
		m_DateEnd.SetDate (m_dtFinish);

		m_TimeEnd.SetState (CBCGPDateTimeCtrl::DTM_TIME | nFlags, nMask);
		m_TimeEnd.SetDate (m_dtFinish);

		OnAllDay ();
	}
}

BOOL CAppointmentDialogBar2::OnInitDialogBar()
{
	AddResize (IDC_APP_EDIT_SEPARATOR, CEditDialogBar::e_ResizeSizeH);

	return CEditDialogBar::OnInitDialogBar();
}

void CAppointmentDialogBar2::OnAllDay ()
{
	m_bAllDay = m_AllDay.GetCheck () == BST_CHECKED;

	int nCmd = m_bAllDay ? SW_HIDE : SW_SHOW;

	m_TimeStart.ShowWindow (nCmd);
	m_TimeStart.EnableWindow (!m_bAllDay);
	m_TimeEnd.ShowWindow (nCmd);
	m_TimeEnd.EnableWindow (!m_bAllDay);

	CBCGPFrameWnd* pFrame = DYNAMIC_DOWNCAST(CBCGPFrameWnd, GetParentFrame ());
	if (pFrame != NULL)
	{
		pFrame->OnUpdateFrameTitle (TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAppointmentFrame

IMPLEMENT_DYNAMIC(CAppointmentFrame, CEditFrameDialog)

CAppointmentFrame::CAppointmentFrame(CBCGPAppointment& app, 
								 const CBCGPRecurrenceBaseRule* pRule /*=NULL*/,
								 BOOL bEcp /*= FALSE*/,
								 BOOL bNewRecur /*= FALSE*/,
								 BOOL bReadOnly /*= FALSE*/,
								 CWnd* pParent /*=NULL*/)
	: CEditFrameDialog(IDR_APPOINTMENTFRAME, pParent)
	, m_Appointment (app)
	, m_Rule        (NULL)
	, m_bEcp        (bEcp)
	, m_bNewRecur   (bNewRecur)
	, m_bReadOnly   (bReadOnly)
	, m_bDeleted    (FALSE)
	, m_bPrivate    (FALSE)
	, m_Importance  (e_ImportanceNormal)
{
	if (pRule != NULL)
	{
		ASSERT_VALID (pRule);
		m_Rule = pRule->CreateCopy ();
	}

	m_wndDialogBar1.m_strLocation = _T("");
	m_wndDialogBar1.m_strSubject  = m_Appointment.GetDescription ();
	m_wndDialogBar1.m_bMeeting    = m_Appointment.HasImage (3);
	m_wndDialogBar1.m_bPhoneCall  = m_Appointment.HasImage (5);
	m_wndDialogBar2.m_bAllDay     = m_Appointment.IsAllDay ();
	m_wndDialogBar2.m_dtStart     = m_Appointment.GetStart ();
	m_wndDialogBar2.m_dtFinish    = m_Appointment.GetFinish ();

	m_nLabel    = -1;
	m_nShowTime = 0;

	int i = 0;

	for (i = 0; i < c_CategoryCount; i++)
	{
		if (m_Appointment.GetBackgroundColor () == c_CategoryColors[i])
		{
			m_nLabel = i;
			break;
		}
	}

	for (i = 0; i < c_ShowasCount; i++)
	{
		if (m_Appointment.GetDurationColor () == c_ShowasColors[i])
		{
			m_nShowTime = i;
			break;
		}
	}

	CAppointment* pAppDemo = DYNAMIC_DOWNCAST (CAppointment, &m_Appointment);
	if (pAppDemo != NULL)
	{
		m_wndDialogBar1.m_strLocation = pAppDemo->GetLocation ();

		m_bPrivate        = pAppDemo->IsPrivate ();
		if (pAppDemo->GetImportance () == CAppointment::e_ImportanceLow)
		{
			m_Importance = e_ImportanceLow;
		}
		else if (pAppDemo->GetImportance () == CAppointment::e_ImportanceHigh)
		{
			m_Importance = e_ImportanceHigh;
		}
	}
}

CAppointmentFrame::~CAppointmentFrame()
{
}

void CAppointmentFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if ((GetStyle() & FWS_ADDTOTITLE) == 0)
		return;     // leave it alone!

	SetTitle (m_wndDialogBar2.m_bAllDay ? _T("Event") : _T("Appointment"));

	if (bAddToTitle)
	{
		UpdateFrameTitleForDocument (m_Appointment.GetDescription ().IsEmpty () ?
			_T("Untitled") : m_Appointment.GetDescription ());
	}
	else
	{
		UpdateFrameTitleForDocument(NULL);
	}
}

BEGIN_MESSAGE_MAP(CAppointmentFrame, CEditFrameDialog)
	//{{AFX_MSG_MAP(CAppointmentFrame)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_APP_EDIT_SAVE_CLOSE, OnSaveClose)
	ON_COMMAND(ID_APP_EDIT_DELETE, OnDelete)
	ON_UPDATE_COMMAND_UI(ID_APP_EDIT_DELETE, OnUpdateDelete)
	ON_COMMAND(ID_APP_EDIT_RECURRENCE, OnRecurrence)
	ON_COMMAND(ID_APP_EDIT_PRIVATE, OnPrivate)
	ON_UPDATE_COMMAND_UI(ID_APP_EDIT_PRIVATE, OnUpdatePrivate)
	ON_COMMAND(ID_APP_EDIT_IMPORTANCE_LOW, OnImportanceLow)
	ON_UPDATE_COMMAND_UI(ID_APP_EDIT_IMPORTANCE_LOW, OnUpdateImportanceLow)
	ON_COMMAND(ID_APP_EDIT_IMPORTANCE_HIGH, OnImportanceHigh)
	ON_UPDATE_COMMAND_UI(ID_APP_EDIT_IMPORTANCE_HIGH, OnUpdateImportanceHigh)
	ON_UPDATE_COMMAND_UI(IDC_APP_EDIT_LABEL, OnUpdateLabel)
	ON_COMMAND_RANGE(ID_CATEGORY_1, ID_CATEGORY_6, OnCategory)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CATEGORY_1, ID_CATEGORY_6, OnUpdateCategory)
	ON_UPDATE_COMMAND_UI(IDC_APP_EDIT_SHOW_TIME, OnUpdateShowTime)
	ON_COMMAND_RANGE(ID_SHOWAS_1, ID_SHOWAS_4, OnShowAs)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SHOWAS_1, ID_SHOWAS_4, OnUpdateShowAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppointmentFrame message handlers

BOOL CAppointmentFrame::LoadPanelImages ()
{
	m_PanelImages.SetImageSize (CSize (16, 16));
	return m_PanelImages.Load (IDB_PLANNER_BUTTONS);
}

BOOL CAppointmentFrame::CreateStatusBar ()
{
	return TRUE;
}

BOOL CAppointmentFrame::CreateOtherBars ()
{
	if (!m_wndDialogBar1.Create (_T(""), this, FALSE, MAKEINTRESOURCE(IDD_APP_DIALOGBAR1), 
			WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR, 0, 0))
	{
		return FALSE;
	}

	if (!m_wndDialogBar2.Create (_T(""), this, FALSE, MAKEINTRESOURCE(IDD_APP_DIALOGBAR2), 
			WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR + 1, 0, 0))
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
	ShowControlBar (&m_wndDialogBar2, TRUE, FALSE, FALSE);
	EnableDateControls (!m_Appointment.IsRecurrence () || 
		m_Appointment.IsRecurrenceClone ());

	CAppointment* pAppDemo = DYNAMIC_DOWNCAST (CAppointment, &m_Appointment);
	if (pAppDemo != NULL)
	{
		SetText (pAppDemo->GetMemo());
	}

	if (m_bNewRecur)
	{
		PostMessage (WM_COMMAND, ID_APP_EDIT_RECURRENCE, NULL);
	}

	return TRUE;
}

void CAppointmentFrame::AddMainCategory ()
{
	CEditFrameDialog::AddMainCategory ();

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		_T("Main Menu"), IDB_PLANNER_FILE_SMALL, IDB_PLANNER_FILE_LARGE);

	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE, _T("&Save"), 0, 0, TRUE));
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE_AS, _T("Save &As..."), 1, 1, TRUE));
	pMainPanel->Add (new CBCGPRibbonButton (ID_APP_EDIT_DELETE, _T("&Delete"), 2, 2, TRUE));

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

void CAppointmentFrame::AddTabs ()
{
	AddTab_Home ();

	CEditFrameDialog::AddTabs ();
}

void CAppointmentFrame::AddTab_Home ()
{
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		_T("Appointment\nh"), IDB_PLANNER_HOME_SMALL, IDB_PLANNER_HOME_LARGE);

	CBCGPRibbonPanel* pPanelActions = pCategory->AddPanel (_T("Actions"), m_PanelImages.ExtractIcon (3));
	pPanelActions->Add (new CBCGPRibbonButton (ID_APP_EDIT_SAVE_CLOSE, _T("Save && Close\nav"), 0, 0));
	pPanelActions->Add (new CBCGPRibbonSeparator ());
	pPanelActions->Add (new CBCGPRibbonButton (ID_APP_EDIT_DELETE, _T("Delete\nd"), 1, 1));

	CBCGPRibbonPanel* pPanelOptions = pCategory->AddPanel (_T("Options"), m_PanelImages.ExtractIcon (4));

	pPanelOptions->Add (new CBCGPRibbonButton (ID_APP_EDIT_RECURRENCE, _T("Recurrence\ne"), 2, 2));

	CBCGPRibbonButton* pShowAs = new CBCGPRibbonButton (IDC_APP_EDIT_SHOW_TIME, _T("Show As\nb"), 3, 3);
	pPanelOptions->Add (pShowAs);
	CompleteShowAs (*pShowAs);

	CBCGPRibbonButton* pLabel = new CBCGPRibbonButton (IDC_APP_EDIT_LABEL, _T("Categorize\nt"), 4, 4);
	pPanelOptions->Add (pLabel);
	CompleteCategories (*pLabel);

	pPanelOptions->Add (new CBCGPRibbonButton (ID_APP_EDIT_PRIVATE, _T("Private\nv"), 5, -1));
	pPanelOptions->Add (new CBCGPRibbonButton (ID_APP_EDIT_IMPORTANCE_HIGH, _T("High Importance\nh"), 6, -1));
	pPanelOptions->Add (new CBCGPRibbonButton (ID_APP_EDIT_IMPORTANCE_LOW, _T("Low Importance\nl"), 7, -1));
}

void CAppointmentFrame::CompleteShowAs (CBCGPRibbonButton& btn)
{
	CBCGPToolBarImages& images = btn.GetParentCategory ()->GetSmallImages ();
	int count = images.GetCount ();
	images.Load (IDB_SHOWAS_HC, NULL, TRUE);

	for (int i = 0; i < c_ShowasCount; i++)
	{
		btn.AddSubItem (new CBCGPRibbonButton (ID_SHOWAS_1 + i, c_ShowasNames[i], count + i, -1));
	}

	btn.SetDefaultCommand (FALSE);
}

void CAppointmentFrame::OnPrivate ()
{
	m_bPrivate = !m_bPrivate;
}

void CAppointmentFrame::OnUpdatePrivate (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_bPrivate);
}

void CAppointmentFrame::OnImportanceLow ()
{
	m_Importance = m_Importance == e_ImportanceLow ? e_ImportanceNormal : e_ImportanceLow;
}

void CAppointmentFrame::OnUpdateImportanceLow (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_Importance == e_ImportanceLow);
}

void CAppointmentFrame::OnImportanceHigh ()
{
	m_Importance = m_Importance == e_ImportanceHigh ? e_ImportanceNormal : e_ImportanceHigh;
}

void CAppointmentFrame::OnUpdateImportanceHigh (CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_Importance == e_ImportanceHigh);
}

void CAppointmentFrame::OnFileClose ()
{
	OnCancel ();
}

void CAppointmentFrame::OnSaveClose ()
{
	OnOK ();
}

void CAppointmentFrame::OnDelete ()
{
	m_bDeleted = TRUE;

	OnCancel ();
}

void CAppointmentFrame::OnUpdateDelete (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CAppointmentFrame::EnableDateControls (BOOL bEnable)
{
	ShowControlBar (&m_wndDialogBar2, bEnable, FALSE, FALSE);
	RecalcLayout ();
}

void CAppointmentFrame::OnOK() 
{
	m_wndDialogBar1.UpdateData ();

	m_Appointment.SetAllDay (m_wndDialogBar2.m_bAllDay);

	if (!m_Appointment.IsRecurrence () || m_Appointment.IsRecurrenceClone ())
	{
		COleDateTime dtS = m_wndDialogBar2.m_DateStart.GetDate ();
		COleDateTime dtF = m_wndDialogBar2.m_DateEnd.GetDate ();

		COleDateTime tmS = m_wndDialogBar2.m_TimeStart.GetDate ();
		COleDateTime tmF = m_wndDialogBar2.m_TimeEnd.GetDate ();

		dtS = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
			tmS.GetHour (), tmS.GetMinute (), 0);

		dtF = COleDateTime (dtF.GetYear (), dtF.GetMonth (), dtF.GetDay (),
			tmF.GetHour (), tmF.GetMinute (), 0);

		if (dtS > dtF)
		{
			AfxMessageBox (IDS_APPOINTMENT_1);
			return;
		}

		m_Appointment.SetInterval (dtS, dtF);
	}
	
	m_Appointment.SetDescription (m_wndDialogBar1.m_strSubject);
	m_Appointment.SetBackgroundColor (m_nLabel == -1 ? CLR_DEFAULT : c_CategoryColors[m_nLabel]);
	m_Appointment.SetDurationColor (m_nShowTime == 0 ? CLR_DEFAULT : c_ShowasColors[m_nShowTime]);

	m_Appointment.RemoveAllImages ();

	if (m_wndDialogBar1.m_bMeeting)
	{
		m_Appointment.AddImage (3);
	}

	if (m_wndDialogBar1.m_bPhoneCall)
	{
		m_Appointment.AddImage (5);
	}

	CAppointment* pAppDemo = DYNAMIC_DOWNCAST (CAppointment, &m_Appointment);
	if (pAppDemo != NULL)
	{
		pAppDemo->SetImportance (m_Importance == e_ImportanceLow
			? CAppointment::e_ImportanceLow
			: m_Importance == e_ImportanceHigh
				? CAppointment::e_ImportanceHigh
				: CAppointment::e_ImportanceNormal);
		pAppDemo->SetPrivate (m_bPrivate);

		pAppDemo->SetLocation (m_wndDialogBar1.m_strLocation);

		CString strMemo;
		GetText (strMemo);
		pAppDemo->SetMemo (strMemo);
	}

	CEditFrameDialog::OnOK();
}

void CAppointmentFrame::OnRecurrence ()
{
	CBCGPRecurrenceBaseRule* pRule = m_Rule;

	if (pRule == NULL)
	{
		pRule = CBCGPPlannerManagerCtrl::CreateRule (BCGP_PLANNER_RULE_DAILY);
		pRule->SetDateStart (m_Appointment.GetStart ());
		
		COleDateTimeSpan span (m_Appointment.GetStart () - pRule->GetDateStart ());
		pRule->SetTimeInterval (span, span + m_Appointment.GetDuration ());
	}

	CRecurrenceDlg dlg(pRule, m_Rule != NULL, m_bEcp, this);

	if (dlg.DoModal () == IDOK)
	{
		m_bEcp = FALSE;
		
		const CBCGPRecurrenceBaseRule* pRuleNew = dlg.GetRule ();

		if (pRuleNew == NULL)
		{
			if (m_Rule != NULL)
			{
				delete m_Rule;
				m_Rule = NULL;

				EnableDateControls (TRUE);

				if (m_Appointment.IsAllDay ())
				{
					m_wndDialogBar2.OnAllDay ();
				}
			}
		}
		else
		{
			if (m_Rule == NULL || m_Appointment.IsRecurrenceClone ())
			{
				delete pRule;
				EnableDateControls (FALSE);
			}
			else
			{
				delete m_Rule;
			}

			m_Rule = CBCGPPlannerManagerCtrl::CreateRule (pRuleNew->GetID ());


			CBCGPAppointmentPropertyList props;
			pRuleNew->GetProperties (props);
			m_Rule->SetProperties (props);
		}
	}
	else
	{
		if (m_Rule == NULL)
		{
			delete pRule;
		}
	}
}

void CAppointmentFrame::OnUpdateLabel (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CAppointmentFrame::OnCategory(UINT nID)
{
	int nLabel = (int)(nID - ID_CATEGORY_1);
	if (m_nLabel == nLabel)
	{
		m_nLabel = - 1;
	}
	else
	{
		m_nLabel = nLabel;
	}
}

void CAppointmentFrame::OnUpdateCategory(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nLabel == (int)(pCmdUI->m_nID - ID_CATEGORY_1));
}

void CAppointmentFrame::OnUpdateShowTime (CCmdUI* pCmdUI)
{
	pCmdUI->Enable (TRUE);
}

void CAppointmentFrame::OnShowAs(UINT nID)
{
	m_nShowTime = (int)(nID - ID_SHOWAS_1);
}

void CAppointmentFrame::OnUpdateShowAs(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nShowTime == (int)(pCmdUI->m_nID - ID_SHOWAS_1));
}

