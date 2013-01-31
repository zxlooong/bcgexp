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
// BCGPOutlookDemoDoc.cpp : implementation of the CBCGPOutlookDemoDoc class
//

#include "stdafx.h"
#include "BCGPOutlookDemo.h"

#include "BCGPOutlookDemoDoc.h"
#include "MailFrame.h"
#include "MailView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoDoc

IMPLEMENT_DYNCREATE(CBCGPOutlookDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPOutlookDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPOutlookDemoDoc)
	ON_COMMAND(ID_NEW_APPOINMENT, OnNewAppoinment)
	ON_COMMAND(ID_NEW_CONTRACT, OnNewContract)
	ON_COMMAND(ID_NEW_DISTRIBUTION_LIST, OnNewDistributionList)
	ON_COMMAND(ID_NEW_FAX, OnNewFax)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_COMMAND(ID_NEW_JOURNAL_ENTRY, OnNewJournalEntry)
	ON_COMMAND(ID_NEW_MAIL, OnNewMail)
	ON_COMMAND(ID_NEW_MEETING, OnNewMeeting)
	ON_COMMAND(ID_NEW_NOTE, OnNewNote)
	ON_COMMAND(ID_NEW_POST_FOLDER, OnNewPostFolder)
	ON_COMMAND(ID_NEW_SHORTCUT, OnNewShortcut)
	ON_COMMAND(ID_NEW_TASK, OnNewTask)
	ON_COMMAND(ID_NEW_TASK_REQUEST, OnNewTaskRequest)
	ON_COMMAND(ID_SEND_RECEIVE, OnSendReceive)
	ON_COMMAND(ID_ADDRESS_BOOK, OnAddressBook)
	ON_COMMAND(ID_FIND_CONTACT, OnFindContact)
	ON_COMMAND(ID_WEB_ADDRESS, OnWebAddress)
	ON_COMMAND(ID_WEB_BACK, OnWebBack)
	ON_COMMAND(ID_WEB_FIND, OnWebFind)
	ON_COMMAND(ID_WEB_REFRESH, OnWebRefresh)
	ON_COMMAND(ID_WEB_START, OnWebStart)
	ON_COMMAND(ID_VIEW_UP, OnViewUp)
	ON_COMMAND(ID_VIEW_BACK, OnViewBack)
	ON_COMMAND(ID_RULES_WIZARD, OnRulesWizard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoDoc construction/destruction

CBCGPOutlookDemoDoc::CBCGPOutlookDemoDoc()
{
	// TODO: add one-time construction code here

}

CBCGPOutlookDemoDoc::~CBCGPOutlookDemoDoc()
{
}

BOOL CBCGPOutlookDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoDoc serialization

void CBCGPOutlookDemoDoc::Serialize(CArchive& ar)
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
// CBCGPOutlookDemoDoc diagnostics

#ifdef _DEBUG
void CBCGPOutlookDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPOutlookDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoDoc commands

void CBCGPOutlookDemoDoc::OnNewAppoinment() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewContract() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewDistributionList() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewFax() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewFolder() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewJournalEntry() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewMeeting() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewNote() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewPostFolder() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewShortcut() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewTask() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewTaskRequest() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnSendReceive() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnAddressBook() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnFindContact() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnWebAddress() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnWebBack() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnWebFind() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnWebRefresh() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnWebStart() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnViewUp() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnViewBack() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnRulesWizard() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoDoc::OnNewMail() 
{
	theApp.SaveState ();

	CMailFrame* pMailFrame = new CMailFrame;

	CCreateContext context;

	context.m_pCurrentDoc = this;
	context.m_pCurrentFrame = NULL;
	context.m_pNewDocTemplate = NULL;
	context.m_pLastView = NULL;
	context.m_pNewViewClass = RUNTIME_CLASS (CMailView);

	pMailFrame->LoadFrame (IDR_MAILFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		&context);

	pMailFrame->ShowWindow (SW_SHOW);
}

