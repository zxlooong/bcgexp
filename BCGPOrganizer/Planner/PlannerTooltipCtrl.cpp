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
// PlannerTooltipCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "Appointment.h"
#include "PlannerTooltipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlannerTooltipCtrl

IMPLEMENT_DYNCREATE(CPlannerTooltipCtrl, CBCGPToolTipCtrl)

CPlannerTooltipCtrl::CPlannerTooltipCtrl()
{
	m_pWndPlanner = NULL;
	m_pHotAppointment = NULL;

	m_hIconMeeting = (HICON) ::LoadImage (
			AfxGetResourceHandle (),
			MAKEINTRESOURCE (IDI_USERS),
			IMAGE_ICON,
			32,
			32,
			LR_DEFAULTCOLOR);

	m_hIconPrivate = (HICON) ::LoadImage (
			AfxGetResourceHandle (),
			MAKEINTRESOURCE (IDI_SECURITY),
			IMAGE_ICON,
			32,
			32,
			LR_DEFAULTCOLOR);
}

CPlannerTooltipCtrl::~CPlannerTooltipCtrl()
{
	if (m_hIconMeeting != NULL)
	{
		::DestroyIcon (m_hIconMeeting);
	}

	if (m_hIconPrivate != NULL)
	{
		::DestroyIcon (m_hIconPrivate);
	}	
}


BEGIN_MESSAGE_MAP(CPlannerTooltipCtrl, CBCGPToolTipCtrl)
	//{{AFX_MSG_MAP(CPlannerTooltipCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TTN_SHOW, OnShow)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlannerTooltipCtrl message handlers

void CPlannerTooltipCtrl::OnShow(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_pWndPlanner->GetSafeHwnd () != NULL)
	{
		ASSERT_VALID (m_pWndPlanner);

		CPoint ptPlanner;

		::GetCursorPos (&ptPlanner);
		m_pWndPlanner->ScreenToClient (&ptPlanner);

		m_pHotAppointment = 
			DYNAMIC_DOWNCAST (CAppointment,
				m_pWndPlanner->GetAppointmentFromPoint (ptPlanner));

		SetDescription (_T(""));
	}

	CBCGPToolTipCtrl::OnShow (pNMHDR, pResult);
}

int CPlannerTooltipCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolTipCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pWndPlanner = DYNAMIC_DOWNCAST (CBCGPPlannerManagerCtrl,
		CWnd::FromHandlePermanent (lpCreateStruct->hwndParent));
	
	return 0;
}

void CPlannerTooltipCtrl::SetDescription (const CString strDesrciption)
{
	CBCGPToolTipCtrl::SetDescription (strDesrciption);

	if (m_pHotAppointment == NULL)
	{
		return;
	}

	m_strDesrciption.Empty ();
	if (m_pHotAppointment->GetImportance () == CAppointment::e_ImportanceLow)
	{
		m_strDesrciption = _T("Low Importance\n\n");
	}
	else if (m_pHotAppointment->GetImportance () == CAppointment::e_ImportanceHigh)
	{
		m_strDesrciption = _T("High Importance\n\n");
	}

	ASSERT_VALID (m_pHotAppointment);

	const CString& strMemo = m_pHotAppointment->GetMemo ();

	if (!strMemo.IsEmpty ())
	{
		m_strDesrciption += strMemo;
	}
	else
	{
		m_strDesrciption += _T("No description");
	}
}

CSize CPlannerTooltipCtrl::GetIconSize ()
{
	if (m_pHotAppointment == NULL)
	{
		return CSize (0, 0);
	}

	return	m_pHotAppointment->IsPrivate () ||
			m_pHotAppointment->HasImage (3) ? CSize (32, 32) : CSize (0, 0);
}

BOOL CPlannerTooltipCtrl::OnDrawIcon (CDC* pDC, CRect rectImage)
{
	ASSERT_VALID (pDC);

	if (m_pHotAppointment->IsPrivate ())
	{
		::DrawIconEx (pDC->GetSafeHdc (),
			rectImage.left, rectImage.top, m_hIconPrivate,
			0, 0, 0, NULL, DI_NORMAL);
	}
	else if (m_pHotAppointment->HasImage (3))
	{
		::DrawIconEx (pDC->GetSafeHdc (),
			rectImage.left, rectImage.top, m_hIconMeeting,
			0, 0, 0, NULL, DI_NORMAL);
	}

	return TRUE;
}
