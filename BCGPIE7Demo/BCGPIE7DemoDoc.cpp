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
// BCGPIE7DemoDoc.cpp : implementation of the CBCGPIE7DemoDoc class
//

#include "stdafx.h"
#include "BCGPIE7Demo.h"

#include "BCGPIE7DemoDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoDoc

IMPLEMENT_DYNCREATE(CBCGPIE7DemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPIE7DemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPIE7DemoDoc)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoDoc construction/destruction

CBCGPIE7DemoDoc::CBCGPIE7DemoDoc()
{
	m_iHistoryOffset = 0;
	m_arHistory.SetSize (0, 1);
}

CBCGPIE7DemoDoc::~CBCGPIE7DemoDoc()
{
	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		ASSERT (m_arHistory [i] != NULL);
		delete m_arHistory [i];
	}
}

BOOL CBCGPIE7DemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoDoc serialization

void CBCGPIE7DemoDoc::Serialize(CArchive& ar)
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
// CBCGPIE7DemoDoc diagnostics

#ifdef _DEBUG
void CBCGPIE7DemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPIE7DemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPIE7DemoDoc commands

CHistoryObj* CBCGPIE7DemoDoc::AddURLToHistory (const CString& strTitle, const CString& strURL)
{
	ASSERT (m_arHistory.GetSize () <= HISTORY_LEN);

	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		CHistoryObj* pObj = m_arHistory [i];
		ASSERT (pObj != NULL);

		if (pObj->GetTitle () == strTitle &&
			pObj->GetURL () == strURL)
		{
			return pObj;
		}
	}

	if (m_arHistory.GetSize () == HISTORY_LEN)
	{
		delete m_arHistory [0];
		m_arHistory.RemoveAt (0);
	}

	CHistoryObj* pObj = new CHistoryObj (strTitle, strURL, 
		ID_HISTORY_FIRST + (UINT)m_arHistory.GetSize ());
	m_arHistory.InsertAt (0, pObj);

	m_iHistoryOffset = 0;
	return pObj;
}
//****************************************************************************************
void CBCGPIE7DemoDoc::GetBackList (_T_HistotyList& lst) const
{
	lst.RemoveAll ();
	for (int i = m_iHistoryOffset + 1; i < m_arHistory.GetSize () ; i ++)
	{
		lst.AddTail (m_arHistory [i]);
	}
}
//****************************************************************************************
void CBCGPIE7DemoDoc::GetFrwdList (_T_HistotyList& lst) const
{
	lst.RemoveAll ();
	for (int i = m_iHistoryOffset - 1; i >= 0; i --)
	{
		ASSERT (i < m_arHistory.GetSize ());
		lst.AddTail (m_arHistory [i]);
	}
}
//****************************************************************************************
CHistoryObj* CBCGPIE7DemoDoc::Go (UINT uiCmd)
{
	for (int i = 0; i < m_arHistory.GetSize (); i ++)
	{
		CHistoryObj* pObj = m_arHistory [i];
		ASSERT (pObj != NULL);

		if (pObj->GetCommand () == uiCmd)
		{
			m_arHistory.RemoveAt (i);
			m_arHistory.Add (pObj);

			m_iHistoryOffset = 0;
			return pObj;
		}
	}

	return NULL;
}

class XMainFrame : public CMainFrame
{
	friend class CBCGPIE7DemoDoc;
};

void CBCGPIE7DemoDoc::OnFileClose()
{
	XMainFrame* pFrame = (XMainFrame*)DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
	if (pFrame != NULL && pFrame->m_wndTabBar.GetTabsNum () == 1)
	{
		pFrame->PostMessage (WM_CLOSE);
		return;
	}

	CDocument::OnFileClose();
}
