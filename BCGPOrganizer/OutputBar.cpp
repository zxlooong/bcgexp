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
// OutputBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "MainFrm.h"
#include "OutputBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputBar::COutputBar()
{
}

COutputBar::~COutputBar()
{
}

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COutputBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	CRect rect;
	GetClientRect (rect);

	pDC->FillSolidRect (rect, globalData.clrBarLight);

	CRect rectBorder = rect;
	rectBorder.DeflateRect (1, 1);

	CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);
	pDC->SetTextColor (globalData.clrBarText);
	pDC->SetBkMode (TRANSPARENT);

	rect.DeflateRect (10, 10);

	pDC->DrawText (m_strText, rect, DT_WORDBREAK);

	pDC->SelectObject (pOldFont);
	
	pDC->Draw3dRect (rectBorder, globalData.clrBarShadow, globalData.clrBarShadow);
}

void COutputBar::UpdateInfo (int nType)
{
	m_strText.Empty ();

	switch (nType)
	{
	case 0:
		m_strText = _T("Welcome to BCGControlBar Pro Demonstration! Please click Ribbon Control tab to activate appropriate view.");
		break;

	case 1:
		m_strText = _T("The current view demonstrates Report Control in read-only mode. You can organize the structure by using \"Field Chooser\" and \"Group By Box\".  Click \"Flag\" to set the message status.");
		break;

	case 2:
		m_strText = _T("This view demonstrates fully functional Calendar (Planner) control. You can create/edit/remove appointments and recurring events.");
		break;

	case 3:
		m_strText = _T("This view demonstrates usage of Database Grid control in read-only mode. You can organize the structure by using \"Field Chooser\" and \"Group By Box\". Use Tasks | Current View to filter out the data.");
		break;

	case 4:
		m_strText = _T("This view demonstrates advanced Edit control that can be used in development environments. In addition, you can see how to use Office 2007-style mini-toolbar (\"floaty\") in order to manipulate selected text. You can see IntelliSense in action by typing \"System.\", \"Drawing.\" or \"IO.\" (case-sensitive!)");
		break;
		
	case 5:
		m_strText = _T("This view demonstrates Gantt control.");
		break;
	}

	RedrawWindow ();
}

void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	RedrawWindow ();
	
}

BOOL COutputBar::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
