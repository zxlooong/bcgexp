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
// BCGPCalendarDemoView.cpp : implementation of the CBCGPCalendarDemoView class
//

#include "stdafx.h"
#include "BCGPCalendarDemo.h"

#include "BCGPCalendarDemoDoc.h"
#include "BCGPCalendarDemoView.h"

#include "GotoDayDialog.h"
#include "PrintTypeDlg.h"
#include "AppointmentDlg.h"
#include "RecurrenceConfirmDlg.h"
#include "ResourceDlg.h"

#include "MainFrm.h"
#include "BCGPAppointmentDemo.h"
#include "BCGPPlannerClockIconsDemo.h"
#include "BCGPAppointmentStorage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoView

IMPLEMENT_DYNCREATE(CBCGPCalendarDemoView, CBCGPPlannerManagerView)

BEGIN_MESSAGE_MAP(CBCGPCalendarDemoView, CBCGPPlannerManagerView)
	//{{AFX_MSG_MAP(CBCGPCalendarDemoView)
	ON_COMMAND(ID_PLANNER_MODE_DAY, OnModeDay)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_DAY, OnUpdateModeDay)
	ON_COMMAND(ID_PLANNER_MODE_MONTH, OnModeMonth)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_MONTH, OnUpdateModeMonth)
	ON_COMMAND(ID_PLANNER_MODE_WEEK, OnModeWeek)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_WEEK, OnUpdateModeWeek)
	ON_COMMAND(ID_PLANNER_MODE_WORKWEEK, OnModeWorkweek)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_WORKWEEK, OnUpdateModeWorkweek)
	ON_COMMAND(ID_PLANNER_MODE_MULTI, OnModeMulti)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_MODE_MULTI, OnUpdateModeMulti)
	ON_COMMAND(ID_PLANNER_TIMELINE_60, OnTimeLine60)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_60, OnUpdateTimeLine60)
	ON_COMMAND(ID_PLANNER_TIMELINE_30, OnTimeLine30)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_30, OnUpdateTimeLine30)
	ON_COMMAND(ID_PLANNER_TIMELINE_20, OnTimeLine20)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_20, OnUpdateTimeLine20)
	ON_COMMAND(ID_PLANNER_TIMELINE_15, OnTimeLine15)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_15, OnUpdateTimeLine15)
	ON_COMMAND(ID_PLANNER_TIMELINE_10, OnTimeLine10)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_10, OnUpdateTimeLine10)
	ON_COMMAND(ID_PLANNER_TIMELINE_6, OnTimeLine6)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_6, OnUpdateTimeLine6)
	ON_COMMAND(ID_PLANNER_TIMELINE_5, OnTimeLine5)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_TIMELINE_5, OnUpdateTimeLine5)
	ON_COMMAND(ID_PLANNER_GOTO_TODAY, OnGotoToday)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_GOTO_TODAY, OnUpdateGotoToday)
	ON_COMMAND(ID_PLANNER_GOTO_THISDAY, OnGotoThisday)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_GOTO_THISDAY, OnUpdateGotoThisday)
	ON_COMMAND(ID_PLANNER_GOTO_DAY, OnGotoDay)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_GOTO_DAY, OnUpdateGotoDay)
	ON_COMMAND(ID_PLANNER_COMPRESS_WEEKEND, OnCompressWeekend)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_COMPRESS_WEEKEND, OnUpdateCompressWeekend)
	ON_COMMAND(ID_PLANNER_DRAW_TIME_FINISH, OnDrawTimeFinish)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_DRAW_TIME_FINISH, OnUpdateDrawTimeFinish)
	ON_COMMAND(ID_PLANNER_DRAW_TIME_AS_ICONS, OnDrawTimeAsIcons)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_DRAW_TIME_AS_ICONS, OnUpdateDrawTimeAsIcons)
	ON_COMMAND(ID_PLANNER_SHOWTOOLTIP, OnShowToolTip)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_SHOWTOOLTIP, OnUpdateShowToolTip)
	ON_COMMAND(ID_PLANNER_OPEN_APP, OnPlannerOpenApp)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_OPEN_APP, OnUpdatePlannerOpenApp)
	ON_COMMAND(ID_PLANNER_REMOVE_APP, OnPlannerRemoveApp)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_REMOVE_APP, OnUpdatePlannerRemoveApp)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_PLANNER_NEW, OnPlannerNewAppointment)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_NEW_APPOINTMENT, OnPlannerNewAppointment)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW_APPOINTMENT, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_NEW_EVENT, OnPlannerNewEvent)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW_EVENT, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_NEW_REC_APPOINTMENT, OnPlannerNewRecAppointment)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW_REC_APPOINTMENT, OnUpdatePlannerNew)
	ON_COMMAND(ID_PLANNER_NEW_REC_EVENT, OnPlannerNewRecEvent)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_NEW_REC_EVENT, OnUpdatePlannerNew)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_CBN_SELENDOK(ID_PLANNER_RESOURCE, OnResource)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_RESOURCE, OnUpdateResource)
	ON_COMMAND(ID_PLANNER_RESOURCE_ADD, OnResourceAdd)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_RESOURCE_ADD, OnUpdateResourceAdd)
	ON_COMMAND(ID_PLANNER_RESOURCE_REMOVE, OnResourceRemove)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_RESOURCE_REMOVE, OnUpdateResourceRemove)
	ON_COMMAND(ID_PLANNER_RESOURCE_PROP, OnResourceProp)
	ON_UPDATE_COMMAND_UI(ID_PLANNER_RESOURCE_PROP, OnUpdateResourceProp)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CBCGPPlannerManagerView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPPlannerManagerView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoView construction/destruction

CBCGPCalendarDemoView::CBCGPCalendarDemoView()
	: m_bFirstTime      (TRUE)
	, m_LastClickedTime ()
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	rMan.SetUseMultiResourceDefault (TRUE);
	rMan.SetStorageRTC ();

	if (rMan.IsMultiResourceStorage () && rMan.GetStorage () != NULL)
	{
		CBCGPAppointmentDemoResourceInfo* pInfo = new CBCGPAppointmentDemoResourceInfo ();
		pInfo->SetDescription (_T("Resource 1"));
		rMan.AddResourceRTC (1, NULL, pInfo, TRUE, FALSE);

		pInfo = new CBCGPAppointmentDemoResourceInfo ();
		pInfo->SetDescription (_T("Resource 2"));
		pInfo->SetWorkInterval (COleDateTime (1899, 12, 30, 6, 0, 0), COleDateTime (1899, 12, 30, 12, 30, 0));
		rMan.AddResourceRTC (2, NULL, pInfo, TRUE, FALSE);
	}
}

CBCGPCalendarDemoView::~CBCGPCalendarDemoView()
{
}

BOOL CBCGPCalendarDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPPlannerManagerView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoView drawing

void CBCGPCalendarDemoView::OnDraw(CDC* /*pDC*/)
{
	CBCGPCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoView printing

void CBCGPCalendarDemoView::OnFilePrintPreview() 
{
#ifndef _BCGPCALENDAR_STANDALONE
	BCGPPrintPreview (this);
#else
	CBCGPPlannerManagerView::OnFilePrintPreview();
#endif
}

BOOL CBCGPCalendarDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	CRuntimeClass* pPrinterClass = NULL;

	if (!pInfo->m_bPreview)
	{
		CPrintTypeDlg dlg (AfxGetMainWnd ());

		switch (GetType ())
		{
		case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY:
			dlg.SetType (GetViewDuration () == 1 ? 0 : 3);
			break;
		case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK:
			dlg.SetType (1);
			break;
		case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK:
			dlg.SetType (1);
			break;
		case CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH:
			dlg.SetType (2);
			break;
		}

		if (dlg.DoModal () != IDOK)
		{
			return FALSE;
		}
		else
		{
			switch (dlg.GetType ())
			{
			case 0:
				pPrinterClass = RUNTIME_CLASS(CBCGPPlannerPrintDay);
				break;
			case 1:
				pPrinterClass = RUNTIME_CLASS(CBCGPPlannerPrintWeek);
				break;
			case 2:
				pPrinterClass = RUNTIME_CLASS(CBCGPPlannerPrintMonth);
				break;
			case 3:
				pPrinterClass = RUNTIME_CLASS(CBCGPPlannerPrintDual);
				break;
			}
		}
	}

	GetManagerCtrl ().OnPreparePrinting (pInfo, pPrinterClass);

	return DoPreparePrinting(pInfo);
}

void CBCGPCalendarDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	GetManagerCtrl ().OnBeginPrinting (pDC, pInfo);
}

void CBCGPCalendarDemoView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPPlannerManagerView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoView diagnostics

#ifdef _DEBUG
void CBCGPCalendarDemoView::AssertValid() const
{
	CBCGPPlannerManagerView::AssertValid();
}

void CBCGPCalendarDemoView::Dump(CDumpContext& dc) const
{
	CBCGPPlannerManagerView::Dump(dc);
}

CBCGPCalendarDemoDoc* CBCGPCalendarDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPCalendarDemoDoc)));
	return (CBCGPCalendarDemoDoc*)m_pDocument;
}
#endif //_DEBUG

void CBCGPCalendarDemoView::CompleteResourceCombo (CBCGPToolbarComboBoxButton* button) const
{
	if (button == NULL)
	{
		return;
	}

	if (button->GetCount ())
	{
		button->RemoveAllItems ();
	}	

	if (GetManagerCtrl ().IsMultiResourceStorage ())
	{
		UINT nResourceID = GetManagerCtrl ().GetCurrentResourceID ();
		int nIndex = -1;

		CBCGPAppointmentBaseMultiStorage* pStorage = 
			DYNAMIC_DOWNCAST(CBCGPAppointmentBaseMultiStorage, GetManagerCtrl ().GetStorage ());

		CBCGPAppointmentBaseMultiStorage::XResourceIDArray ar;
		pStorage->GetResourceIDs (ar);

		for (int i = 0; i < ar.GetSize (); i++)
		{
			const CBCGPAppointmentBaseResourceInfo* pInfo = pStorage->GetResourceInfo (ar[i]);
			CString str;
			if (pInfo != NULL)
			{
				str = pInfo->GetDescription ();
			}

			button->AddItem (str, ar[i]);
			if (ar[i] == nResourceID)
			{
				nIndex = i;
			}
		}

		if (nIndex != -1)
		{
			button->SelectItem (nIndex, FALSE);

			if (button->GetParentWnd ()->GetSafeHwnd () != NULL)
			{
				button->GetParentWnd ()->RedrawWindow (button->Rect ());
			}
		}
	}
}

void CBCGPCalendarDemoView::CompleteResourceCombo () const
{
	CMainFrame* pFrameWnd = DYNAMIC_DOWNCAST (CMainFrame, AfxGetMainWnd ());
	if (pFrameWnd->GetSafeHwnd () == NULL)
	{
		return;
	}

	CBCGPToolbarComboBoxButton* pButton = pFrameWnd->GetResourceCombo ();
	if (pButton == NULL)
	{
		return;
	}

	CompleteResourceCombo (pFrameWnd->GetResourceCombo ());
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoView message handlers

void CBCGPCalendarDemoView::OnContextMenu(CWnd*, CPoint point)
{
	UINT nID = 0;

	CPoint pt (point);
	ScreenToClient (&pt);

	CBCGPPlannerView::BCGP_PLANNER_HITTEST nHit = HitTest (pt);

	if (nHit >= CBCGPPlannerView::BCGP_PLANNER_HITTEST_APPOINTMENT)
	{
		nID = IDR_PLANNER_APPOINTMENT;
	}
	else if (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_TIMEBAR)
	{
		nID = IDR_PLANNER_TIMEBAR;
	}
	else if (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_CLIENT ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_DAY_CAPTION ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_RESOURCE ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_ICON_UP ||
			 nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_ICON_DOWN)
	{
		if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY)
		{
			nID = (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_CLIENT ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY)
					? IDR_PLANNER_CLIENT_DAY
					: IDR_PLANNER_TIMEBAR;
		}
		else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK)
		{
			nID = (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_CLIENT ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY)
					? IDR_PLANNER_CLIENT_WORK_WEEK
					: IDR_PLANNER_TIMEBAR;
		}
		else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI)
		{
			nID = (nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_CLIENT ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_RESOURCE ||
				   nHit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY)
					? IDR_PLANNER_CLIENT_MULTI
					: IDR_PLANNER_TIMEBAR;
		}
		else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
		{
			nID = IDR_PLANNER_CLIENT_WEEK;
		}
		else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
		{
			if (nHit != CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER)
			{
				nID = IDR_PLANNER_CLIENT_MONTH;
			}
		}

		m_LastClickedTime = GetDateFromPoint (pt);
	}

	if (nID != 0)
	{
#ifndef _BCGPCALENDAR_STANDALONE
		theApp.ShowPopupMenu (nID, point, this);
#else
		CMenu menu;
		menu.LoadMenu (nID);

		CMenu* pPopupMenu = menu.GetSubMenu (0);
		pPopupMenu->TrackPopupMenu (0, point.x, point.y, this);
#endif
	}
}

void CBCGPCalendarDemoView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/) 
{
	CBCGPCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	GetManagerCtrl ().SetDateInterval (pDoc->GetDate1 (), pDoc->GetDate2 ());

	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetType ();

	if (theApp.m_Options.m_Type != type && !m_bFirstTime)
	{
		theApp.m_Options.m_Type = type;
		theApp.UpdateCalendar (FALSE);
	}
}

void CBCGPCalendarDemoView::OnModeDay() 
{
	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY);
}

void CBCGPCalendarDemoView::OnUpdateModeDay(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == 
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY);
}

void CBCGPCalendarDemoView::OnModeMonth() 
{
	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
}

void CBCGPCalendarDemoView::OnUpdateModeMonth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == 
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
}

void CBCGPCalendarDemoView::OnModeWeek() 
{
	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK);
}

void CBCGPCalendarDemoView::OnUpdateModeWeek(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == 
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK);
}

void CBCGPCalendarDemoView::OnModeWorkweek() 
{
	SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
}

void CBCGPCalendarDemoView::OnUpdateModeWorkweek(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK);
}

void CBCGPCalendarDemoView::OnModeMulti() 
{
	if (GetManagerCtrl ().IsMultiResourceStorage ())
	{
		SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
	}
}

void CBCGPCalendarDemoView::OnUpdateModeMulti(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetManagerCtrl ().IsMultiResourceStorage ());
	pCmdUI->SetRadio (GetManagerCtrl ().GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
}

void CBCGPCalendarDemoView::OnTimeLine60()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_60);
}

void CBCGPCalendarDemoView::OnUpdateTimeLine60(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
					GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_60);
}

void CBCGPCalendarDemoView::OnTimeLine30()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_30);
}

void CBCGPCalendarDemoView::OnUpdateTimeLine30(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
					GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_30);
}

void CBCGPCalendarDemoView::OnTimeLine20()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_20);
}

void CBCGPCalendarDemoView::OnUpdateTimeLine20(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
					GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_20);
}

void CBCGPCalendarDemoView::OnTimeLine15()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_15);
}

void CBCGPCalendarDemoView::OnUpdateTimeLine15(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
					GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_15);
}

void CBCGPCalendarDemoView::OnTimeLine10()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_10);
}

void CBCGPCalendarDemoView::OnUpdateTimeLine10(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
					GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_10);
}

void CBCGPCalendarDemoView::OnTimeLine6()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_6);
}

void CBCGPCalendarDemoView::OnUpdateTimeLine6(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
					GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_6);
}

void CBCGPCalendarDemoView::OnTimeLine5()
{
	SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_5);
}

void CBCGPCalendarDemoView::OnUpdateTimeLine5(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
					GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
	pCmdUI->SetRadio (GetTimeDelta () == CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_5);
}

void CBCGPCalendarDemoView::OnGotoToday() 
{
	SetToday ();
}

void CBCGPCalendarDemoView::OnUpdateGotoToday(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command update UI handler code here
}

void CBCGPCalendarDemoView::OnGotoThisday() 
{
	COleDateTime day (m_LastClickedTime);

	if (day == COleDateTime ())
	{
		day = GetDate ();
	}

	m_LastClickedTime = COleDateTime ();

	if (GetType () != CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY ||
		GetType () != CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI)
	{
		SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY);
	}

	CBCGPCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetDateInterval (day, day);
}

void CBCGPCalendarDemoView::OnUpdateGotoThisday(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK ||
		GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);	
}

void CBCGPCalendarDemoView::OnGotoDay() 
{
	CGotoDayDialog dlg(GetDate (), GetType (), GetManagerCtrl ().IsMultiResourceStorage (), 
		CBCGPPlannerManagerCtrl::GetFirstDayOfWeek (), this);

	if (dlg.DoModal () == IDOK)
	{
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = dlg.GetType ();
		COleDateTime dt (dlg.GetDate ());

		if (GetType () == type && GetDate () == dt)
		{
			return;
		}

		if (GetType () != type)
		{
			GetManagerCtrl ().SetType (type, FALSE);

			theApp.m_Options.m_Type = type;
			theApp.UpdateCalendar (FALSE);
		}

		CBCGPCalendarDemoDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		GetManagerCtrl ().SetDate (dt, FALSE);
		GetManagerCtrl ().RedrawWindow ();
	}
}

void CBCGPCalendarDemoView::OnUpdateGotoDay(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command handler code here
}

void CBCGPCalendarDemoView::OnCompressWeekend() 
{
	SetCompressWeekend (!IsCompressWeekend ());

	theApp.m_Options.m_MonthCompressWeekend = IsCompressWeekend ();
	theApp.UpdateCalendar (FALSE);
}

void CBCGPCalendarDemoView::OnUpdateCompressWeekend(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
	pCmdUI->SetCheck (IsCompressWeekend ());
}

void CBCGPCalendarDemoView::OnDrawTimeFinish() 
{
	SetDrawTimeFinish (!IsDrawTimeFinish ());
	
	if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
	{
		theApp.m_Options.m_WeekDrawTimeFinish = IsDrawTimeFinish ();
	}
	else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
	{
		theApp.m_Options.m_MonthDrawTimeFinish = IsDrawTimeFinish ();
	}

	theApp.UpdateCalendar (FALSE);
}

void CBCGPCalendarDemoView::OnUpdateDrawTimeFinish(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK ||
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
	pCmdUI->SetCheck (IsDrawTimeFinish ());
}

void CBCGPCalendarDemoView::OnDrawTimeAsIcons() 
{
	SetDrawTimeAsIcons (!IsDrawTimeAsIcons ());

	if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
	{
		theApp.m_Options.m_WeekDrawTimeIcons = IsDrawTimeAsIcons ();
	}
	else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
	{
		theApp.m_Options.m_MonthDrawTimeIcons = IsDrawTimeAsIcons ();
	}

	theApp.UpdateCalendar (FALSE);
}

void CBCGPCalendarDemoView::OnUpdateDrawTimeAsIcons(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK ||
		            GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);
	pCmdUI->SetCheck (IsDrawTimeAsIcons ());
}

void CBCGPCalendarDemoView::OnShowToolTip() 
{
	GetManagerCtrl ().SetShowToolTip (!GetManagerCtrl ().IsShowToolTip ());
	
	theApp.m_Options.m_ShowToolTip = GetManagerCtrl ().IsShowToolTip () ? 2 : 0;

	theApp.UpdateCalendar (FALSE);
}

void CBCGPCalendarDemoView::OnUpdateShowToolTip(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (GetManagerCtrl ().IsShowToolTip ());
}

void CBCGPCalendarDemoView::OnPlannerOpenApp() 
{
	if (GetManagerCtrl ().GetSelectedAppointmentsCount () == 1)
	{
		POSITION pos = GetManagerCtrl ().GetFirstSelectedAppointment ();
		CBCGPAppointment* pApp = const_cast<CBCGPAppointment*>(
			GetManagerCtrl ().GetNextSelectedAppointment (pos));

		AddEditAppointment (pApp);
	}
}

void CBCGPCalendarDemoView::OnUpdatePlannerOpenApp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetManagerCtrl ().GetSelectedAppointmentsCount () == 1);
}

void CBCGPCalendarDemoView::OnPlannerRemoveApp() 
{
	if (GetManagerCtrl ().GetSelectedAppointmentsCount () > 0)
	{
		GetManagerCtrl ().RemoveSelectedAppointments ();
	}
}

void CBCGPCalendarDemoView::OnUpdatePlannerRemoveApp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetManagerCtrl ().GetSelectedAppointmentsCount () > 0);
}

void CBCGPCalendarDemoView::OnEditPaste() 
{
	if (GetManagerCtrl ().IsEditPasteEnabled ())
	{
		GetManagerCtrl ().EditPaste (m_LastClickedTime);

		m_LastClickedTime = COleDateTime ();
	}		
}

void CBCGPCalendarDemoView::AddEditAppointment (CBCGPAppointment* pApp, 
												BOOL bAllDay /*= FALSE*/,
												BOOL bNewRecur /*= FALSE*/)
{
	CBCGPAppointment* pAppEdit = pApp;
	CBCGPRecurrenceBaseRule* pOldRule = NULL;

	BOOL bAdd = pAppEdit == NULL;
	BOOL bEcp = FALSE;
	
	COleDateTime dtOld;

	if (bAdd)
	{
		COleDateTime dtS (GetManagerCtrl ().GetSelectionStart ());
		COleDateTime dtF (GetManagerCtrl ().GetSelectionEnd ());

		if (dtF < dtS)
		{
			COleDateTime dt (dtS);
			dtS = dtF;
			dtF = dt;
		}

		if (!bAllDay)
		{
			CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetType ();

			if (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK || 
				type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
			{
				if (dtS.GetDayOfYear () == dtF.GetDayOfYear ())
				{
					dtS = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
						GetManagerCtrl ().GetFirstWorkingHour (), 0, 0);
					dtF = COleDateTime (dtS.GetYear (), dtS.GetMonth (), dtS.GetDay (),
						GetManagerCtrl ().GetFirstWorkingHour () + 1, 0, 0);
				}
				else
				{
					bAllDay = TRUE;
				}
			}
			else
			{
				dtF += COleDateTimeSpan (0, 0, 0, 1);
			}
		}

		pAppEdit = new CBCGPAppointmentDemo (
					dtS, dtF, _T(""),
					CLR_DEFAULT,
					CLR_DEFAULT,
					bAllDay ? CLR_DEFAULT : RGB (0, 0, 255));

		ASSERT_VALID(pAppEdit);

		if (bAllDay)
		{
			pAppEdit->SetAllDay (TRUE);
		}
	}
	else
	{
		bNewRecur = FALSE;

		if (pAppEdit->IsRecurrence ())
		{
			if (pAppEdit->IsRecurrenceClone ())
			{
				CRecurrenceConfirmDlg dlg (pAppEdit->GetDescription (), TRUE, this);

				if (dlg.DoModal () != IDOK)
				{
					return;
				}

				if (!dlg.IsOnlyOccurrence ())
				{
					pAppEdit = GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ());
					ASSERT_VALID(pAppEdit);
				}
			}

			if (pAppEdit->IsRecurrenceClone ())
			{
				pOldRule = GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ())->
					GetRecurrence ()->GetRule ();
				bEcp = !GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ())->
					GetRecurrence ()->IsExceptionsCollectionEmpty ();
			}
			else
			{
				pOldRule = pAppEdit->GetRecurrence ()->GetRule ();
				bEcp = !pAppEdit->GetRecurrence ()->IsExceptionsCollectionEmpty ();
			}

			ASSERT_VALID(pOldRule);
		}

		dtOld = pAppEdit->GetStart ();
	}

	ASSERT_VALID (pAppEdit);

	CAppointmentDlg dlg (*pAppEdit, pOldRule, bEcp, bNewRecur, 
		IsReadOnly (), this);
	if (dlg.DoModal () != IDOK)
	{
		if (bAdd)
		{
			delete pAppEdit;
		}
		else
		{
			if (dlg.IsDeleted ())
			{
				GetManagerCtrl ().RemoveSelectedAppointments ();
			}
		}

		return;
	}

	if (IsReadOnly ())
	{
		return;
	}

	const CBCGPRecurrenceBaseRule* pRule = dlg.GetRule ();

	if (bAdd)
	{
		if (pRule != NULL)
		{	
			pAppEdit->SetRecurrenceRule (pRule);
		}

		GetManagerCtrl ().AddAppointment (pAppEdit, TRUE, TRUE);
	}
	else
	{
		if (pAppEdit->IsRecurrence ())
		{
			if (!pAppEdit->IsRecurrenceClone ())
			{
				if (pRule == NULL)
				{
					// recurrence appointment -> ordinary appointment
					CBCGPAppointment* pApp = pAppEdit->CreateCopy ();

					GetManagerCtrl ().RemoveAppointment (pAppEdit, FALSE, FALSE);
					pAppEdit = pApp;
					GetManagerCtrl ().AddAppointment (pAppEdit, TRUE, TRUE);

					return;
				}
				else if (*pOldRule != *pRule)
				{
					// update rule
					pAppEdit->SetRecurrenceRule (pRule);
					pAppEdit->UpdateRecurrence ();
				}
			}
			else
			{
				if (pRule == NULL)
				{
					// cloned appointment -> ordinary appointment
					CBCGPAppointment* pApp = pAppEdit->CreateCopy ();

					pAppEdit = GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ());
					ASSERT_VALID(pAppEdit);

					GetManagerCtrl ().RemoveAppointment (pAppEdit, FALSE, FALSE);
					pAppEdit = pApp;
					GetManagerCtrl ().AddAppointment (pAppEdit, TRUE, TRUE);

					return;
				}
				else if (*pOldRule != *pRule)
				{
					// cloned appointment -> recurrence appointment
					CBCGPAppointmentPropertyList props;
					pAppEdit->GetProperties (props);

					pAppEdit = GetManagerCtrl ().GetRecurrence (pAppEdit->GetRecurrenceID ());
					ASSERT_VALID(pAppEdit);
					pAppEdit->SetProperties (props);

					pAppEdit->SetRecurrenceRule (pRule);
				}
			}
		}
		else
		{
			if (pRule != NULL)
			{
				// ordinary appointment -> recurrence appointment
				CBCGPAppointment* pApp = pAppEdit->CreateCopy ();

				GetManagerCtrl ().RemoveAppointment (pAppEdit, FALSE, FALSE);

				pAppEdit = pApp;

				pAppEdit->SetRecurrenceRule (pRule);

				GetManagerCtrl ().AddAppointment (pAppEdit, TRUE, TRUE);

				return;
			}
		}

		if(!GetManagerCtrl ().UpdateAppointment (pAppEdit, dtOld, TRUE, FALSE))
		{
			GetManagerCtrl ().QueryAppointments ();
		}

		GetManagerCtrl ().AdjustLayout (TRUE);
	}
}

void CBCGPCalendarDemoView::OnDblClkCtrl (UINT /*nFlags*/, CPoint point)
{
	CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetType ();
	CBCGPPlannerView::BCGP_PLANNER_HITTEST hit = GetManagerCtrl ().HitTest (point);

	if (hit != CBCGPPlannerView::BCGP_PLANNER_HITTEST_NOWHERE &&
		!((hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
		   hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_WEEKBAR ||
		   hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_WEEK_CAPTION) &&
		 type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH))
	{
		CBCGPAppointment* pApp = GetManagerCtrl ().GetAppointmentFromPoint (point);

		BOOL bAllDay = (((type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
			              type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
						  type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI) &&
			             (hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER ||
						  hit == CBCGPPlannerView::BCGP_PLANNER_HITTEST_HEADER_ALLDAY)) ||
		                (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK || 
			             type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH));

		AddEditAppointment (pApp, bAllDay);
	}
}

void CBCGPCalendarDemoView::OnKeyDownCtrl(UINT nChar, UINT /*nRepCnt*/, UINT /*nFlags*/) 
{
	if ((VK_F1 <= nChar && nChar <= VK_F12) || IsReadOnly ())
	{
		return;
	}

	if (_istalpha (nChar) || _istdigit (nChar) || nChar == VK_RETURN)
	{
		if (GetManagerCtrl ().GetSelectedAppointmentsCount () == 1)
		{
			POSITION pos = GetManagerCtrl ().GetFirstSelectedAppointment ();
			CBCGPAppointment* pApp = const_cast<CBCGPAppointment*>(
				GetManagerCtrl ().GetNextSelectedAppointment (pos));

			AddEditAppointment (pApp);

			return;
		}

		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetType ();

		BOOL bAllDay = (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK || 
						type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH);

		AddEditAppointment (NULL, bAllDay);

		return;
	}
	else if (nChar == VK_DELETE)
	{
		GetManagerCtrl ().RemoveSelectedAppointments ();
	}

	return;
}

void CBCGPCalendarDemoView::OnAppointmentAdded (CBCGPAppointment* /*pApp*/)
{
	CBCGPCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetModifiedFlag ();
}

UINT CBCGPCalendarDemoView::OnUpdateAppointment (CBCGPAppointment* /*pApp*/)
{
	CBCGPCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	return 0L;
}

void CBCGPCalendarDemoView::OnAppointmentUpdated (CBCGPAppointment* /*pApp*/)
{
	CBCGPCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetModifiedFlag ();
}

UINT CBCGPCalendarDemoView::OnRemoveAppointment (CBCGPAppointment* pApp)
{
	CBCGPCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetModifiedFlag ();

	LRESULT lResult = 0L;

	if (GetManagerCtrl().GetChangeOperation () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_CHANGE_OPERATION_NONE &&
		pApp != NULL && pApp->IsRecurrenceClone ())
	{
		CRecurrenceConfirmDlg dlg (pApp->GetDescription (), FALSE, this);

		if (dlg.DoModal () != IDOK)
		{
			lResult = LRESULT(-1L);
		}
		else
		{
			lResult = dlg.IsOnlyOccurrence () ? 0L : 1L;
		}
	}

	return (UINT)lResult;
}

void CBCGPCalendarDemoView::OnAllAppointmentsRemoved ()
{
	CBCGPCalendarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetModifiedFlag ();
}

void CBCGPCalendarDemoView::OnInitialUpdate() 
{
	CBCGPPlannerManagerView::OnInitialUpdate();

	if (m_bFirstTime)
	{
		m_bFirstTime = FALSE;

		CompleteResourceCombo ();

		CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

		rMan.SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);

		CMainFrame* pFrame = DYNAMIC_DOWNCAST (CMainFrame, GetTopLevelFrame ());
		if (pFrame != NULL)
		{
			rMan.SetCalendar (pFrame->GetCalendar ());
		}

		UpdateCalendar (theApp.m_Options, FALSE);
		rMan.SetDate (COleDateTime::GetCurrentTime (), FALSE);

		CreateDemo (TRUE);
		rMan.SendMessage (WM_KEYDOWN, VK_HOME, 0);
	}
}

void CBCGPCalendarDemoView::OnPlannerNewAppointment() 
{
	m_LastClickedTime = COleDateTime ();
	AddEditAppointment (NULL, FALSE, FALSE);
}

void CBCGPCalendarDemoView::OnPlannerNewEvent() 
{
	m_LastClickedTime = COleDateTime ();
	AddEditAppointment (NULL, TRUE, FALSE);
}

void CBCGPCalendarDemoView::OnPlannerNewRecAppointment() 
{
	m_LastClickedTime = COleDateTime ();
	AddEditAppointment (NULL, FALSE, TRUE);
}

void CBCGPCalendarDemoView::OnPlannerNewRecEvent() 
{
	m_LastClickedTime = COleDateTime ();
	AddEditAppointment (NULL, TRUE, TRUE);
}

void CBCGPCalendarDemoView::OnUpdatePlannerNew(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (!IsReadOnly ());
}

void CBCGPCalendarDemoView::CreateDemo (BOOL bRedraw /*= TRUE*/)
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	COleDateTime dt (COleDateTime::GetCurrentTime ());
	dt = COleDateTime (dt.GetYear (), dt.GetMonth (), dt.GetDay (), 0, 0, 0);
	dt = CBCGPPlannerView::GetFirstWeekDay (dt, 2);//rMan.GetFirstDayOfWeek ());

	CBCGPAppointmentDemo* pApp = NULL;

	//--------------------------------------------------
	// Create multi day appointment: 
	//--------------------------------------------------
	pApp = new CBCGPAppointmentDemo
			(
				dt + COleDateTimeSpan (1,  9, 0, 0),
				dt + COleDateTimeSpan (3, 18, 0, 0),
				_T("Multi day"),
				CLR_DEFAULT,
				CLR_DEFAULT,
				RGB(0, 0, 255)
			);
	pApp->AddImage (3);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	//--------------------------------------------------
	// Create all day appointment: 
	//--------------------------------------------------
	pApp = new CBCGPAppointmentDemo
			(
				dt + COleDateTimeSpan (2, 0, 0, 0),
				dt + COleDateTimeSpan (2, 0, 0, 0),
				_T("All day"),
				CLR_DEFAULT,
				CLR_DEFAULT,
				RGB(0, 0, 255)
			);
	pApp->AddImage (3);
	pApp->SetAllDay (TRUE);

	rMan.AddAppointment (pApp, FALSE, FALSE);

	//--------------------------------------------------
	// Create recurring appointment: every week, on 
	// Monday, Wednesday and Friday, 9:00 AM -  9:15 AM
	//--------------------------------------------------
	pApp = new CBCGPAppointmentDemo
			(
				dt,
				dt,
				_T("Meeting"),
				RGB (255, 148, 132),
				CLR_DEFAULT,
				RGB(0, 0, 255)
			);
	pApp->AddImage (3);

	{
		CBCGPRecurrenceRuleWeekly* pRule = DYNAMIC_DOWNCAST(CBCGPRecurrenceRuleWeekly, 
			CBCGPPlannerManagerCtrl::CreateRule (BCGP_PLANNER_RULE_WEEKLY));
		pRule->SetDateStart (dt);
		pRule->SetTimeInterval (COleDateTimeSpan (0, 9, 0, 0), COleDateTimeSpan (0, 9, 15, 0));
		pRule->SetDays (CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_1 | 
			CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_3 |
			CBCGPRecurrenceRuleWeekly::BCGP_REC_RULE_WEEKLY_5);

		pApp->SetRecurrenceRule (pRule);
		delete pRule;
	}

	rMan.AddAppointment (pApp, FALSE, FALSE);

	//--------------------------------------------------------
	// Create recurring appointment: every weekday, 2 weeks
	// 6:0 PM-8:00 PM:
	//--------------------------------------------------------
	pApp = new CBCGPAppointmentDemo
				(
					dt,
					dt,
					_T("Training"),
					CLR_DEFAULT,
					CLR_DEFAULT,
					RGB(128, 0, 128)
				);

	{
		CBCGPRecurrenceRuleDaily* pRule = DYNAMIC_DOWNCAST(CBCGPRecurrenceRuleDaily, 
			CBCGPPlannerManagerCtrl::CreateRule (BCGP_PLANNER_RULE_DAILY));
		pRule->SetDateStart (dt);
		pRule->SetTimeInterval (COleDateTimeSpan (0, 18, 0, 0), COleDateTimeSpan (0, 20, 0, 0));
		pRule->SetType (CBCGPRecurrenceRuleDaily::BCGP_REC_RULE_DAILY_TYPE_WEEKDAYS);

		pRule->SetLimitType (CBCGPRecurrenceRuleDaily::BCGP_RECURRENCE_RULE_LIMIT_COUNT);
		pRule->SetLimitCount (10);

		pApp->SetRecurrenceRule (pRule);
		delete pRule;
	}

	rMan.AddAppointment (pApp, FALSE, FALSE);

	//-----------------------------------------------------
	// Create single appointment: 1-st day of week, 8:15 AM:
	//-----------------------------------------------------
	dt += COleDateTimeSpan (1, 0, 0, 0);

	pApp = new CBCGPAppointmentDemo
			(
				dt + COleDateTimeSpan (0,  8, 15, 0),
				dt + COleDateTimeSpan (0,  8, 15, 0),
				_T("Phone call"),
				RGB (255, 231, 115),
				CLR_DEFAULT,
				RGB(128, 0, 128)
			);
	pApp->AddImage (2);
	pApp->AddImage (5);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	dt += COleDateTimeSpan (1, 0, 0, 0);
	
	//-----------------------------------------------------
	// Create single appointment: 2-nd day of week, 9:30 AM:
	//-----------------------------------------------------
	rMan.AddAppointment
		(
			new CBCGPAppointmentDemo
			(
				dt + COleDateTimeSpan (0,  9, 30, 0),
				dt + COleDateTimeSpan (0, 12,  0, 0),
				_T("Briefing"),
				CLR_DEFAULT,
				CLR_DEFAULT,
				RGB(0, 0, 255)
			),
			FALSE, FALSE
		);

	dt += COleDateTimeSpan (1, 0, 0, 0);

	//-----------------------------------------------------
	// Create single appointment: 3-d day of week, 2:00 PM:
	//-----------------------------------------------------
	pApp = new CBCGPAppointmentDemo
			(
				dt + COleDateTimeSpan (0, 14, 30, 0),
				dt + COleDateTimeSpan (0, 15,  0, 0),
				_T("Meeting (friends)"),
				RGB (165, 222, 99),
				CLR_DEFAULT,
				RGB(128, 0, 128)
			);
	pApp->AddImage (2);
	pApp->AddImage (3);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	dt += COleDateTimeSpan (1, 0, 0, 0);

	//-----------------------------------------------------
	// Create single appointment: 4-th day of week, 3:30 PM:
	//-----------------------------------------------------
	pApp = new CBCGPAppointmentDemo
			(
				dt + COleDateTimeSpan (0, 15, 30, 0),
				dt + COleDateTimeSpan (0, 17,  0, 0),
				_T("Business lunch"),
				RGB (132, 156, 231),
				CLR_DEFAULT,
				RGB(0, 0, 255)
			);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	dt += COleDateTimeSpan (2, 0, 0, 0);

	//-----------------------------------------------------
	// Create single appointment: 6 day of week, 2:00 PM:
	//-----------------------------------------------------
	pApp = new CBCGPAppointmentDemo
			(
				dt + COleDateTimeSpan (0, 14,  0, 0),
				dt + COleDateTimeSpan (0, 18,  0, 0),
				_T("John's birthday"),
				RGB (198, 165, 247),
				CLR_DEFAULT,
				RGB(0, 0, 255)
			);
	rMan.AddAppointment (pApp, FALSE, FALSE);

	rMan.QueryAppointments ();
	rMan.AdjustLayout (bRedraw);
	rMan.UpdateCalendarsState ();

	GetDocument ()->SetModifiedFlag (FALSE);
}

int CBCGPCalendarDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPPlannerManagerView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	if (theApp.m_Options.m_WorkFirstDayOfWeek != -1)
	{
		rMan.SetFirstDayOfWeek (theApp.m_Options.m_WorkFirstDayOfWeek);
	}

	return 0;
}

void CBCGPCalendarDemoView::OnDateChanged ()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());

	if (pFrame != NULL)
	{
		COleDateTime dtStart (GetManagerCtrl ().GetDateStart ());
		COleDateTime dtEnd (GetManagerCtrl ().GetDateEnd ());

		CString strText;

		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE type = GetManagerCtrl ().GetType ();

		if (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY || 
			type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
			type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK ||
			type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI)
		{
			SYSTEMTIME st;
			CString str;

			if ((dtEnd - dtStart).GetDays () != 0)
			{
				if (dtEnd.GetYear () != dtStart.GetYear ())
				{
					dtStart.GetAsSystemTime (st);
					::GetDateFormat
						(
							LOCALE_USER_DEFAULT,
							0,
							&st,
							_T("d MMMM yyyy"),
							str.GetBuffer (100),
							100
						);
					str.ReleaseBuffer ();

					strText = str + _T(" - ");

					dtEnd.GetAsSystemTime (st);
					::GetDateFormat
						(
							LOCALE_USER_DEFAULT,
							0,
							&st,
							_T("d MMMM yyyy"),
							str.GetBuffer (100),
							100
						);
					str.ReleaseBuffer ();

					strText += str;
				}
				else
				{
					dtStart.GetAsSystemTime (st);
					::GetDateFormat
						(
							LOCALE_USER_DEFAULT,
							0,
							&st,
							_T("d MMMM"),
							str.GetBuffer (100),
							100
						);
					str.ReleaseBuffer ();

					strText = str + _T(" - ");

					dtEnd.GetAsSystemTime (st);
					::GetDateFormat
						(
							LOCALE_USER_DEFAULT,
							0,
							&st,
							_T("d MMMM"),
							str.GetBuffer (100),
							100
						);
					str.ReleaseBuffer ();

					strText += str;
				}
			}
			else
			{		
				dtStart.GetAsSystemTime (st);
				::GetDateFormat
					(
						LOCALE_USER_DEFAULT,
						0,
						&st,
						_T("d MMMM yyyy"),
						str.GetBuffer (100),
						100
					);
				str.ReleaseBuffer ();

				strText = str;
			}
		}
		else if (type == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
		{
			SYSTEMTIME st;
			CString str;
			
			if ((dtStart + COleDateTimeSpan (7, 0, 0, 0)).GetMonth () != 
				dtStart.GetMonth ())
			{
				dtStart += COleDateTimeSpan (7, 0, 0, 0);
			}

			if ((dtEnd - COleDateTimeSpan (7, 0, 0, 0)).GetMonth () != 
				 dtEnd.GetMonth ())
			{
				dtEnd -= COleDateTimeSpan (7, 0, 0, 0);
			}

			dtStart.GetAsSystemTime (st);
			::GetDateFormat
				(
					LOCALE_USER_DEFAULT,
					0,
					&st,
					_T("MMMM yyyy"),
					str.GetBuffer (100),
					100
				);
			str.ReleaseBuffer ();

			strText = str;

			if (dtStart.GetMonth () != dtEnd.GetMonth ())
			{
				dtEnd.GetAsSystemTime (st);
				::GetDateFormat
					(
						LOCALE_USER_DEFAULT,
						0,
						&st,
						_T("MMMM yyyy"),
						str.GetBuffer (100),
						100
					);
				str.ReleaseBuffer ();

				strText += _T(" - ");
				strText += str;
			}
		}

#ifndef _BCGPCALENDAR_STANDALONE
		pFrame->SetCaptionText (strText);
#endif
	}
}

void CBCGPCalendarDemoView::OnTypeChanged (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE /*oldType*/,
		CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE /*newType*/)
{
	theApp.m_Options.m_Type = GetType ();
	theApp.UpdateCalendar (FALSE);
	theApp.UpdateCalendar ();

	OnDateChanged ();
}

void CBCGPCalendarDemoView::SetTimeDelta2 (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA delta)
{
	theApp.m_Options.m_DayTimeDelta = delta;
	theApp.UpdateCalendar (FALSE);
	theApp.UpdateCalendar ();
}

void CBCGPCalendarDemoView::UpdateCalendar (const CCalendarOptions& options, BOOL bRedraw /*= TRUE*/)
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	rMan.SetRedraw (FALSE);

	if (options.m_Type != GetType ())
	{
		rMan.SetType (options.m_Type, FALSE);
		OnNotifyDateChanged (0, 0);
	}
	rMan.SetBackgroundColor (options.m_clrBackground);

	int nFirstDayOfWeek = options.m_WorkFirstDayOfWeek == -1
		? CBCGPPlannerManagerCtrl::GetSystemFirstDayOfWeek ()
		: options.m_WorkFirstDayOfWeek;

	if (nFirstDayOfWeek != rMan.GetFirstDayOfWeek ())
	{
		rMan.SetFirstDayOfWeek (nFirstDayOfWeek);
		OnNotifyDateChanged (0, 0);
	}

	rMan.SetWorkingHourMinuteInterval (options.m_WorkHourFirst, options.m_WorkHourLast, FALSE);

	if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY ||
		GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WORK_WEEK ||
		GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI)
	{
		rMan.SetTimeDelta (options.m_DayTimeDelta, FALSE);
	}
	else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_WEEK)
	{
		rMan.SetDrawTimeFinish (options.m_WeekDrawTimeFinish);
		rMan.SetDrawTimeAsIcons (options.m_WeekDrawTimeIcons);
	}
	else if (GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MONTH)
	{
		rMan.SetDrawTimeFinish (options.m_MonthDrawTimeFinish);
		rMan.SetDrawTimeAsIcons (options.m_MonthDrawTimeIcons);
		rMan.SetCompressWeekend (options.m_MonthCompressWeekend);
	}

	CWindowDC dc (NULL);
	int nBitsPerPixel = dc.GetDeviceCaps (BITSPIXEL);

	if (options.m_bImagesChanged)
	{
		(const_cast<CCalendarOptions&>(options)).m_bImagesChanged = FALSE;

		if (nBitsPerPixel > 8)
		{
			rMan.SetImages (options.m_DefaultImages ? (UINT) NULL : IDB_CALENDAR_ICONS, 
				16, CLR_DEFAULT);
		}
	}

	if (options.m_bClockIconsChanged)
	{
		(const_cast<CCalendarOptions&>(options)).m_bClockIconsChanged = FALSE;

		if (nBitsPerPixel > 8)
		{
			rMan.SetClockIconsRTC (options.m_DefaultClockIcons 
				? (CRuntimeClass*) NULL 
				: RUNTIME_CLASS(CBCGPPlannerClockIconsDemo));
		}
	}

	rMan.SetUseDayViewInsteadWeekView (options.m_UseDayInsteadWeek);
	rMan.SetScrollBarVisible (options.m_ScrollVisible);

	rMan.SetRedraw (TRUE);

	if (bRedraw)
	{
		rMan.RedrawWindow ();
	}
	
	if (options.m_ShowToolTip != rMan.IsShowToolTip ())
	{
		rMan.SetShowToolTip (options.m_ShowToolTip != 0);
	}
}

void CBCGPCalendarDemoView::OnResourceIDChanged ()
{
	if (GetManagerCtrl ().IsMultiResourceStorage ())
	{
		CMainFrame* pFrameWnd = DYNAMIC_DOWNCAST (CMainFrame, AfxGetMainWnd ());
		if (pFrameWnd->GetSafeHwnd () == NULL)
		{
			return;
		}

		CBCGPToolbarComboBoxButton* pButton = pFrameWnd->GetResourceCombo ();
		if (pButton == NULL)
		{
			return;
		}

		UINT nResourceID = GetManagerCtrl ().GetCurrentResourceID ();

		for (int i = 0; i < pButton->GetCount (); i++)
		{
			if (pButton->GetItemData (i) == nResourceID)
			{
				if (i != pButton->GetCurSel ())
				{
					pButton->SelectItem (i, FALSE);
					pButton->GetParentWnd ()->RedrawWindow (pButton->Rect ());
				}

				break;
			}
		}
	}
}

void CBCGPCalendarDemoView::OnResource()
{
	if (GetManagerCtrl ().IsMultiResourceStorage ())
	{
		CMainFrame* pFrameWnd = DYNAMIC_DOWNCAST (CMainFrame, AfxGetMainWnd ());
		if (pFrameWnd->GetSafeHwnd () == NULL)
		{
			return;
		}

		CBCGPToolbarComboBoxButton* pButton = pFrameWnd->GetResourceCombo ();
		if (pButton == NULL)
		{
			return;
		}

		UINT nResourceID = (UINT) pButton->GetItemData ();

		if (nResourceID != CBCGPAppointmentBaseMultiStorage::e_UnknownResourceID)
		{
			GetManagerCtrl ().SetCurrentResourceID (nResourceID);
		}
	}
}

void CBCGPCalendarDemoView::OnUpdateResource(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (GetManagerCtrl ().IsMultiResourceStorage () &&
		GetType () != CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI);
}

void CBCGPCalendarDemoView::AddEditResource (BOOL bAdd)
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	if (!rMan.IsMultiResourceStorage ())
	{
		return;
	}

	CBCGPAppointmentDemoResourceInfo* pDemoInfo = NULL;

	if (!bAdd)
	{
		UINT nResourceID = rMan.GetCurrentResourceID ();

		if (nResourceID != CBCGPAppointmentBaseMultiStorage::e_UnknownResourceID)
		{
			pDemoInfo = (CBCGPAppointmentDemoResourceInfo*)
				const_cast<CBCGPAppointmentBaseResourceInfo*>(rMan.GetResourceInfo (nResourceID));
		}
	}
	else
	{
		pDemoInfo = new CBCGPAppointmentDemoResourceInfo ();
	}

	if (pDemoInfo != NULL)
	{
		CResourceDlg dlg (*pDemoInfo);
		if (dlg.DoModal () == IDOK)
		{
			if (bAdd)
			{
				rMan.AddResourceRTC (CBCGPAppointmentBaseMultiStorage::e_UnknownResourceID, NULL, pDemoInfo);
			}
			else
			{
				rMan.UpdateStorage (FALSE);
				rMan.AdjustLayout ();
			}

			CompleteResourceCombo ();

			GetDocument ()->SetModifiedFlag ();
		}
		else if (bAdd)
		{
			delete pDemoInfo;
		}
	}
}

void CBCGPCalendarDemoView::OnResourceAdd() 
{
	AddEditResource (TRUE);
}

void CBCGPCalendarDemoView::OnUpdateResourceAdd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetManagerCtrl ().IsMultiResourceStorage ());
}

void CBCGPCalendarDemoView::OnResourceRemove() 
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();

	if (!rMan.IsMultiResourceStorage ())
	{
		return;
	}

	if (rMan.RemoveResource (CBCGPAppointmentBaseMultiStorage::e_UnknownResourceID) != NULL)
	{
		CompleteResourceCombo ();
		GetDocument ()->SetModifiedFlag ();
	}
}

void CBCGPCalendarDemoView::OnUpdateResourceRemove(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetManagerCtrl ().IsMultiResourceStorage () &&
		((CBCGPAppointmentBaseMultiStorage*) GetManagerCtrl ().GetStorage ())->GetCount () > 1);
}

void CBCGPCalendarDemoView::OnResourceProp() 
{
	AddEditResource (FALSE);
}

void CBCGPCalendarDemoView::OnUpdateResourceProp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (GetManagerCtrl ().IsMultiResourceStorage ());	
}

void CBCGPCalendarDemoView::Serialize(CArchive& ar)
{
	CBCGPPlannerManagerCtrl& rMan = GetManagerCtrl ();
	BOOL bMulti = rMan.IsMultiResourceStorage ();
	DWORD dwCount = 0;

	if (ar.IsStoring ())
	{
		ar << bMulti;

		if (bMulti)
		{
			CBCGPAppointmentBaseMultiStorage* pStorage = 
				DYNAMIC_DOWNCAST(CBCGPAppointmentBaseMultiStorage, rMan.GetStorage ());

			CBCGPAppointmentMultiStorage::XResourceIDArray id;
			pStorage->GetResourceIDs (id);

			dwCount = (DWORD) id.GetSize ();

			ar << dwCount;

			for (DWORD i = 0; i < dwCount; i++)
			{
				ar << id[i];

				CBCGPAppointmentBaseResourceInfo* pInfo = 
					(CBCGPAppointmentBaseResourceInfo*)pStorage->GetResourceInfo (id[i]);

				pInfo->Serialize (ar);
			}
		}	
	}
	else
	{
		ar >> bMulti;

		rMan.ClearAppointmentSelection (FALSE);
		rMan.ClearQuery ();

		rMan.SetUseMultiResourceDefault (bMulti);
		rMan.SetStorageRTC ();

		if (bMulti)
		{
			CBCGPAppointmentBaseMultiStorage* pStorage = 
				DYNAMIC_DOWNCAST(CBCGPAppointmentBaseMultiStorage, rMan.GetStorage ());

			if (pStorage != NULL)
			{
				ar >> dwCount;

				if (dwCount == 0)
				{
					ASSERT (FALSE);
					return;
				}

				for (DWORD i = 0; i < dwCount; i++)
				{
					UINT nResourceID = 0;

					ar >> nResourceID;

					CBCGPAppointmentDemoResourceInfo* pInfo = new CBCGPAppointmentDemoResourceInfo;

					pInfo->Serialize (ar);

					if (rMan.AddResourceRTC (nResourceID, NULL, pInfo, TRUE, FALSE))
					{
						if (i == 0)
						{
							pStorage->SetCurrentResourceID (nResourceID);
						}
					}
				}

				rMan.SetCurrentResourceID (pStorage->GetCurrentResourceID (), FALSE);
			}
		}
		else
		{
			if (rMan.GetType () == CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_MULTI)
			{
				rMan.SetType (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_DAY, FALSE);
			}
		}
	}

	CompleteResourceCombo ();

	rMan.SerializeRaw (ar);
}
