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
// BCGPCalendarDemoDoc.cpp : implementation of the CBCGPCalendarDemoDoc class
//

#include "stdafx.h"
#include "BCGPCalendarDemo.h"

#include "BCGPCalendarDemoDoc.h"
#include "BCGPCalendarDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoDoc

IMPLEMENT_DYNCREATE(CBCGPCalendarDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPCalendarDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPCalendarDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoDoc construction/destruction

CBCGPCalendarDemoDoc::CBCGPCalendarDemoDoc()
{
	m_date1 = COleDateTime::GetCurrentTime ();
	m_date1 = COleDateTime (m_date1.GetYear (), m_date1.GetMonth (), m_date1.GetDay (), 0, 0, 0);
	m_date2 = m_date1;

	m_dwVersion = 1;
}

CBCGPCalendarDemoDoc::~CBCGPCalendarDemoDoc()
{
}

BOOL CBCGPCalendarDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	for (POSITION pos = GetFirstViewPosition (); pos != NULL;)
	{
		CBCGPCalendarDemoView* pView = DYNAMIC_DOWNCAST (CBCGPCalendarDemoView,
			GetNextView (pos));

		if (pView != NULL)
		{
			pView->GetManagerCtrl ().RemoveAllAppointments ();
		}
	}

	return TRUE;
}

const DWORD c_dwHeader = MAKELONG (MAKEWORD ('B', 'C'), MAKEWORD ('G', 'S'));

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoDoc serialization

void CBCGPCalendarDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring ())
	{
		ar << c_dwHeader;
		ar << m_dwVersion;
	}
	else
	{
		DWORD dwHeader = 0;
		ar >> dwHeader;

		if (dwHeader != c_dwHeader)
		{
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}

		ar >> m_dwVersion;
	}

	for (POSITION pos = GetFirstViewPosition (); pos != NULL;)
	{
		CBCGPCalendarDemoView* pView = DYNAMIC_DOWNCAST (CBCGPCalendarDemoView,
			GetNextView (pos));

		if (pView != NULL)
		{
			pView->Serialize (ar);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoDoc diagnostics

#ifdef _DEBUG
void CBCGPCalendarDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPCalendarDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPCalendarDemoDoc commands

void CBCGPCalendarDemoDoc::SetDateInterval (const COleDateTime& date1, const COleDateTime& date2)
{
	m_date1 = date1;
	m_date2 = date2;
	UpdateAllViews (NULL);
}

void CBCGPCalendarDemoDoc::UpdateCalendar (const CCalendarOptions& options)
{
	for (POSITION pos = GetFirstViewPosition (); pos != NULL;)
	{
		CBCGPCalendarDemoView* pView = DYNAMIC_DOWNCAST (CBCGPCalendarDemoView,
			GetNextView (pos));

		if (pView != NULL)
		{
			pView->UpdateCalendar (options);
		}
	}
}
