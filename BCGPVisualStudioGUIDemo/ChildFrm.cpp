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
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "StartView.h"

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
	ON_WM_CREATE()
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
	cs.style &= ~WS_SYSMENU;

	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
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

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	nCmdShow = SW_MAXIMIZE;
	CBCGPMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CChildFrame::IsReadOnly ()
{
	return DYNAMIC_DOWNCAST (CStartView, GetActiveView ()) != NULL;
}

LPCTSTR CChildFrame::GetDocumentName (CObject** pObj)
{
	if (DYNAMIC_DOWNCAST (CStartView, GetActiveView ()) != NULL)
	{
		return g_strStartViewName;
	}
	return CBCGPMDIChildWnd::GetDocumentName (pObj);
}
