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
// BCGPOrganizerView.cpp : implementation of the CBCGPOrganizerView class
//

#include "stdafx.h"
#include "BCGPOrganizer.h"

#include "BCGPOrganizerDoc.h"
#include "BCGPOrganizerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerView

IMPLEMENT_DYNCREATE(CBCGPOrganizerView, CView)

CBCGPOrganizerView::CBCGPOrganizerView()
{
}

CBCGPOrganizerView::~CBCGPOrganizerView()
{
}


BEGIN_MESSAGE_MAP(CBCGPOrganizerView, CView)
	//{{AFX_MSG_MAP(CBCGPOrganizerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerView drawing

void CBCGPOrganizerView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerView diagnostics

#ifdef _DEBUG
void CBCGPOrganizerView::AssertValid() const
{
	CView::AssertValid();
}

void CBCGPOrganizerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerView message handlers
