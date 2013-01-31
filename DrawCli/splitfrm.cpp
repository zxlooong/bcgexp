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
// splitfrm.cpp : implementation file

#include "stdafx.h"
#include "drawcli.h"
#include "splitfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame

IMPLEMENT_DYNCREATE(CSplitFrame, CMDIChildWnd)

CSplitFrame::CSplitFrame()
{
}

CSplitFrame::~CSplitFrame()
{
}

BOOL CSplitFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	return m_wndSplitter.Create(this,
		2, 2,       // TODO: adjust the number of rows, columns
		CSize(10, 10),  // TODO: adjust the minimum pane size
		pContext);
}

BEGIN_MESSAGE_MAP(CSplitFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSplitFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame message handlers
