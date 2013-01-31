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
// BCGPMSMoneyDemoDoc.cpp : implementation of the CBCGPMSMoneyDemoDoc class
//

#include "stdafx.h"
#include "BCGPMSMoneyDemo.h"

#include "BCGPMSMoneyDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoDoc

IMPLEMENT_DYNCREATE(CBCGPMSMoneyDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPMSMoneyDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPMSMoneyDemoDoc)
	ON_COMMAND(ID_GO_BACK, OnGoBack)
	ON_UPDATE_COMMAND_UI(ID_GO_BACK, OnUpdateGoBack)
	ON_COMMAND(ID_GO_FORWARD, OnGoForward)
	ON_UPDATE_COMMAND_UI(ID_GO_FORWARD, OnUpdateGoForward)
	ON_COMMAND(ID_GO_ADDRESS, OnGoAddress)
	ON_UPDATE_COMMAND_UI(ID_GO_ADDRESS, OnUpdateGoAddress)
	ON_COMMAND(ID_VIEW_STOP, OnViewStop)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STOP, OnUpdateViewStop)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REFRESH, OnUpdateViewRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoDoc construction/destruction

CBCGPMSMoneyDemoDoc::CBCGPMSMoneyDemoDoc()
{
}

CBCGPMSMoneyDemoDoc::~CBCGPMSMoneyDemoDoc()
{
}

BOOL CBCGPMSMoneyDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoDoc serialization

void CBCGPMSMoneyDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoDoc diagnostics

#ifdef _DEBUG
void CBCGPMSMoneyDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPMSMoneyDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoDoc commands

void CBCGPMSMoneyDemoDoc::OnGoBack() 
{
}

void CBCGPMSMoneyDemoDoc::OnUpdateGoBack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (IsBackAvailable ());
}

void CBCGPMSMoneyDemoDoc::OnGoForward() 
{
}

void CBCGPMSMoneyDemoDoc::OnUpdateGoForward(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (IsFrwdAvailable ());
}

void CBCGPMSMoneyDemoDoc::OnGoAddress() 
{
}

void CBCGPMSMoneyDemoDoc::OnUpdateGoAddress(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CBCGPMSMoneyDemoDoc::OnViewStop() 
{
}

void CBCGPMSMoneyDemoDoc::OnUpdateViewStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}

void CBCGPMSMoneyDemoDoc::OnViewRefresh() 
{
}

void CBCGPMSMoneyDemoDoc::OnUpdateViewRefresh(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (TRUE);
}
