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
// GanttTooltipCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpganttdemo.h"
#include "GanttTooltipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGanttTooltipCtrl

IMPLEMENT_DYNCREATE(CGanttTooltipCtrl, CBCGPToolTipCtrl)

CGanttTooltipCtrl::CGanttTooltipCtrl()
{
	m_pWndGantt = NULL;
	m_pHotItem = NULL;

	m_hIconComplete = (HICON) ::LoadImage (
			AfxGetResourceHandle (),
			MAKEINTRESOURCE (IDI_COMPLETE),
			IMAGE_ICON,
			32,
			32,
			LR_DEFAULTCOLOR);

	m_hIconMilestone = (HICON) ::LoadImage (
			AfxGetResourceHandle (),
			MAKEINTRESOURCE (IDI_MILESTONE),
			IMAGE_ICON,
			32,
			32,
			LR_DEFAULTCOLOR);

	m_hIconMilestoneC = (HICON) ::LoadImage (
			AfxGetResourceHandle (),
			MAKEINTRESOURCE (IDI_MILESTONE_COMPLETE),
			IMAGE_ICON,
			32,
			32,
			LR_DEFAULTCOLOR);
}

CGanttTooltipCtrl::~CGanttTooltipCtrl()
{
	if (m_hIconComplete != NULL)
	{
		::DestroyIcon (m_hIconComplete);
	}

	if (m_hIconMilestone != NULL)
	{
		::DestroyIcon (m_hIconMilestone);
	}

	if (m_hIconMilestoneC != NULL)
	{
		::DestroyIcon (m_hIconMilestoneC);
	}
}

CBCGPGanttItem*	CGanttTooltipCtrl::GetHotItem ()
{
	if (m_pHotItem != NULL && m_pWndGantt->GetStorage()->Contains(m_pHotItem))
	{
		return m_pHotItem;
	}
	else
	{
		m_pHotItem = NULL;
		return NULL;
	}
}

BEGIN_MESSAGE_MAP(CGanttTooltipCtrl, CBCGPToolTipCtrl)
	//{{AFX_MSG_MAP(CGanttTooltipCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TTN_SHOW, OnShow)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGanttTooltipCtrl message handlers

void CGanttTooltipCtrl::OnShow(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_pWndGantt->GetSafeHwnd () != NULL)
	{
		ASSERT_VALID (m_pWndGantt);

		CPoint ptGantt;

		::GetCursorPos (&ptGantt);
		m_pWndGantt->ScreenToClient (&ptGantt);

		m_pHotItem = m_pWndGantt->ItemFromPoint (ptGantt);
	}

	CBCGPToolTipCtrl::OnShow (pNMHDR, pResult);
}

int CGanttTooltipCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolTipCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pWndGantt = DYNAMIC_DOWNCAST (CBCGPGanttChart,
		CWnd::FromHandlePermanent (lpCreateStruct->hwndParent));
	
	return 0;
}

CSize CGanttTooltipCtrl::GetIconSize ()
{
	CBCGPGanttItem* pItem = GetHotItem ();
	if (pItem == NULL)
	{
		return CSize (0, 0);
	}

	return	pItem->IsMileStone () || pItem->IsCompleted ()
				? CSize (32, 32)
				: CSize (0, 0);
}

CString CGanttTooltipCtrl::GetLabel ()
{
	CString strText;
	GetWindowText (strText);
	
	CBCGPGanttItem* pItem = GetHotItem ();
	if (pItem != NULL)
	{
		if (pItem->IsMileStone ())
		{
			strText = _T ("Milestone");
		}
		else
		{
			strText = _T ("Task");
		}
	}

	return strText;
}

BOOL CGanttTooltipCtrl::OnDrawIcon (CDC* pDC, CRect rectImage)
{
	ASSERT_VALID (pDC);

	HICON hIcon = NULL;

	CBCGPGanttItem* pItem = GetHotItem ();
	if (pItem != NULL)
	{
		if (pItem->IsMileStone ())
		{
			if (pItem->IsCompleted ())
			{
				hIcon = m_hIconMilestoneC;
			}
			else
			{
				hIcon = m_hIconMilestone;
			}
		}
		else if (pItem->IsCompleted () == 1.0f)
		{
			hIcon = m_hIconComplete;
		}
	}

	if (hIcon != NULL)
	{
		::DrawIconEx (pDC->GetSafeHdc (),
			rectImage.left, rectImage.top, hIcon,
			0, 0, 0, NULL, DI_NORMAL);
	}

	return TRUE;
}

void CGanttTooltipCtrl::SetDescription (const CString strDescription)
{
	CBCGPGanttItem* pItem = GetHotItem ();
	if (pItem == NULL)
	{
		CBCGPToolTipCtrl::SetDescription (strDescription);
		return;
	}

	CString strName;
	strName = pItem->GetName ();
	if (strName.IsEmpty ())
	{
		strName = _T("Unnamed");
	}

	CString strDesc (strDescription);
	if (pItem->IsMileStone ())
	{
		SYSTEMTIME st;
		pItem->GetStartTime ().GetAsSystemTime (st);

		::GetDateFormat (LOCALE_USER_DEFAULT, DATE_SHORTDATE, &st, NULL, strDesc.GetBuffer (_MAX_PATH), _MAX_PATH);
		strDesc.ReleaseBuffer ();

		if (st.wHour != 0 || st.wMinute != 0)
		{
			CString strTime;
			::GetTimeFormat (LOCALE_USER_DEFAULT, TIME_NOSECONDS, &st, NULL, strTime.GetBuffer (_MAX_PATH), _MAX_PATH);
			strTime.ReleaseBuffer ();

			if (!strDesc.IsEmpty ())
			{
				strDesc += _T (" ");
			}

			strDesc += strTime;
		}
	}

	CString str;
	str = _T("Name: ") + strName;

	if (!strDesc.IsEmpty ())
	{
		str += _T("\n") + strDesc;
	}	

	CString strFormat;
	if (pItem->IsCompleted ())
	{
		strFormat = _T("Completed!");
	}
	else if (!pItem->IsMileStone ())
	{
		strFormat.Format (_T("%2d%% complete"), (int)(pItem->GetProgress () * 100.0f + 0.5f));
	}

	if (!strFormat.IsEmpty ())
	{
		str += _T("\n") + strFormat;
	}	

	CBCGPToolTipCtrl::SetDescription (str);
}
