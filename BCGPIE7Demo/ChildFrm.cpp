//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"

#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CBCGPMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_MDIACTIVATE()
	ON_MESSAGE(WM_SETTEXT,OnSetText)
	ON_MESSAGE(WM_SETICON,OnSetIcon)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~WS_SYSMENU;

	return TRUE;
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Modify this function to change how the frame is activated.

	nCmdShow = SW_SHOWMAXIMIZED;
	CBCGPMDIChildWnd::ActivateFrame(nCmdShow);
}


/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CBCGPMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, m_pMDIFrame);
	ASSERT_VALID (pFrame);

	if (bActivate)
	{
		pFrame->m_wndTabBar.SetActiveTab (GetSafeHwnd ());
	}
}

LRESULT CChildFrame::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = CBCGPMDIChildWnd::OnSetText(wParam, lParam);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, m_pMDIFrame);
	ASSERT_VALID (pFrame);

	pFrame->m_wndTabBar.SetTabText (GetSafeHwnd ());

	return lRes;
}

LRESULT CChildFrame::OnSetIcon(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = CBCGPMDIChildWnd::OnSetIcon(wParam, lParam);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, m_pMDIFrame);
	ASSERT_VALID (pFrame);

	pFrame->m_wndTabBar.SetTabIcon (GetSafeHwnd ());

	return lRes;
}

void CChildFrame::OnUpdateFrameTitle (BOOL bAddToTitle)
{
	CBCGPMDIChildWnd::OnUpdateFrameTitle (bAddToTitle);
}

void CChildFrame::OnDestroy ()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, m_pMDIFrame);
	ASSERT_VALID (pFrame);

	pFrame->m_wndTabBar.RemoveTab (GetSafeHwnd ());

	CMDIChildWnd::OnDestroy ();
}
