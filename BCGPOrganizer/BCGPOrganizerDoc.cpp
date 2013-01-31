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
// BCGPOrganizerDoc.cpp : implementation of the CBCGPOrganizerDoc class
//

#include "stdafx.h"
#include "mainfrm.h"
#include "BCGPOrganizer.h"
#include "BCGPOrganizerDoc.h"

#include "Views/ShortcutsView.h"
#include "Views/MailView.h"
#include "Views/CalendarPlannerView.h"
#include "Views/TasksView.h"
#include "Views/MacrosEditView.h"
#include "Views/GanttView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerDoc

IMPLEMENT_DYNCREATE(CBCGPOrganizerDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPOrganizerDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPOrganizerDoc)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerDoc construction/destruction

CBCGPOrganizerDoc::CBCGPOrganizerDoc()
	: m_Mode                 (e_ModeUndefined)
	, m_bCalendarModified    (FALSE)
{
	for (int i = 0; i < c_ViewCount; i++)
	{
		m_pViews[i] = NULL;
	}

	m_date1 = COleDateTime::GetCurrentTime ();
	m_date1 = COleDateTime (m_date1.GetYear (), m_date1.GetMonth (), m_date1.GetDay (), 0, 0, 0);
	m_date2 = m_date1;

	TCHAR lpszFilePath [_MAX_PATH];
	if (::GetModuleFileName (NULL, lpszFilePath, _MAX_PATH) > 0)
	{
		TCHAR path_buffer[_MAX_PATH];   
		TCHAR drive[_MAX_DRIVE];   
		TCHAR dir[_MAX_DIR];

#if _MSC_VER < 1400
		_tsplitpath (lpszFilePath, drive, dir, NULL, NULL);
		_tmakepath (path_buffer, drive, dir, NULL, NULL);
#else
		_tsplitpath_s (lpszFilePath, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
		_tmakepath_s (path_buffer, drive, dir, NULL, NULL);
#endif

		m_strPath = path_buffer;
	}
}

CBCGPOrganizerDoc::~CBCGPOrganizerDoc()
{
	theApp.WriteProfileInt (_T("Document"), _T("Mode"), (int)m_Mode);
}

BOOL CBCGPOrganizerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (m_Mode == e_ModeUndefined)
	{
		XMode mode = (XMode)theApp.GetProfileInt (_T("Document"), _T("Mode"), (int)e_ModeShortcuts);
		SetMode (mode);
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerDoc serialization

void CBCGPOrganizerDoc::Serialize(CArchive& ar)
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
// CBCGPOrganizerDoc diagnostics

#ifdef _DEBUG
void CBCGPOrganizerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPOrganizerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CBCGPOrganizerDoc::SetMode(CBCGPOrganizerDoc::XMode mode)
{
    if(m_Mode != mode)
    {
        //bool PrinPreview = m_Mode == e_ModeClientPrintPreview;

        CBCGPFrameWnd* pFrameWnd = DYNAMIC_DOWNCAST(CBCGPFrameWnd, AfxGetMainWnd());

        CView* pOldView = pFrameWnd->GetActiveView();
		if (pOldView == NULL)
		{
			pOldView = DYNAMIC_DOWNCAST(CView, pFrameWnd->GetDescendantWindow (AFX_IDW_PANE_FIRST, TRUE));
		}

        CView* pView = NULL;

		XMode modeOld = m_Mode;
		m_Mode = mode;

		pView = GetView (m_Mode);

        if(pOldView != pView)
        {
			if ((modeOld == e_ModeMail || modeOld == e_ModeTasks) && 
				pOldView != NULL)
			{
				CBCGPGridCtrl* pGridCtrl = ((CBCGPGridView*)(pOldView))->GetGridCtrl ();
				ASSERT_VALID (pGridCtrl);

				if (pGridCtrl->IsColumnsChooserVisible ())
				{
					pGridCtrl->ShowColumnsChooser (FALSE);
				}
			}

			// exchange view window ID's so RecalcLayout() works
			UINT temp = ::GetWindowLong(pOldView->m_hWnd, GWL_ID);
			::SetWindowLong(pOldView->m_hWnd, GWL_ID, ::GetWindowLong(pView->m_hWnd, GWL_ID));
			::SetWindowLong(pView->m_hWnd, GWL_ID, temp);

			// Display and update the new current view - hide the old one    
			pOldView->ShowWindow(SW_HIDE);
			pView->ShowWindow(SW_SHOW);

			pFrameWnd->SetActiveView (pView);

			pFrameWnd->RecalcLayout();

			pView->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
			pFrameWnd->SendMessage(WM_SETMESSAGESTRING, (WPARAM)AFX_IDS_IDLEMESSAGE, 0L);
			pFrameWnd->UpdateWindow();
        }

		SetTitle (c_ViewNames[m_Mode]);
    }
}

BOOL CBCGPOrganizerDoc::CreateViews(CBCGPFrameWnd* pFrameWnd, CCreateContext* pContext)
{
    ASSERT_VALID(pFrameWnd);
    ASSERT(pContext != NULL);

    UINT nID = AFX_IDW_PANE_FIRST + 1;

    CRuntimeClass* pClass[c_ViewCount] = 
    {
		RUNTIME_CLASS(CShortcutsView),
		RUNTIME_CLASS(CMailView),
        RUNTIME_CLASS(CCalendarPlannerView),
		RUNTIME_CLASS(CTasksView),
        RUNTIME_CLASS(CMacrosEditView),
		RUNTIME_CLASS(CGanttView)
    };

    CCreateContext context = *pContext;

    for(long i = 0; i < c_ViewCount; i++)
    {
        m_pViews[i] = NULL;

        context.m_pNewViewClass = pClass[i];
        context.m_pLastView     = NULL;

        m_pViews[i] = (CView*)(pFrameWnd->CreateView(&context, nID));

        if(m_pViews[i] == NULL)
        {
            return FALSE;
        }

        m_pViews[i]->ShowWindow(SW_HIDE);

        nID++;
    }

	LoadMacros (IDR_EDITOR_MACROS_1, _T("Accessibility"));

    return TRUE;
}

void CBCGPOrganizerDoc::LoadMacros(UINT nID, CString strName)
{
	CMacrosEditView* pView = DYNAMIC_DOWNCAST(CMacrosEditView, GetView (e_ModeMacros));

	if (pView != NULL)
	{
		ASSERT_VALID (pView);
		pView->LoadExample (nID, strName);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CBCGPOrganizerDoc commands

void CBCGPOrganizerDoc::SetDateInterval (const COleDateTime& date1, const COleDateTime& date2)
{
	m_date1 = date1;
	m_date2 = date2;
	UpdateAllViews (NULL);
}

void CBCGPOrganizerDoc::UpdateCalendar (const CPlannerOptions& options)
{
	for (POSITION pos = GetFirstViewPosition (); pos != NULL;)
	{
		CCalendarPlannerView* pView = DYNAMIC_DOWNCAST (CCalendarPlannerView,
			GetNextView (pos));

		if (pView != NULL)
		{
			pView->UpdateCalendar (options);
		}
	}
}

void CBCGPOrganizerDoc::UpdateGantt (const CGanttOptions& options)
{
	for (POSITION pos = GetFirstViewPosition (); pos != NULL;)
	{
		CGanttView* pView = DYNAMIC_DOWNCAST (CGanttView,
			GetNextView (pos));

		if (pView != NULL)
		{
			pView->UpdateGantt (options);
		}
	}
}

void CBCGPOrganizerDoc::SetModifiedFlag(BOOL bModified/* = TRUE*/)
{
	if (m_Mode == e_ModeCalendar)
	{
		m_bCalendarModified = bModified;
	}
}

BOOL CBCGPOrganizerDoc::SaveModified()
{
	if (m_bCalendarModified)
	{
		CCalendarPlannerView* pView = DYNAMIC_DOWNCAST(CCalendarPlannerView, GetView (e_ModeCalendar));

		if (pView != NULL)
		{
			ASSERT_VALID (pView);
			pView->Save (m_strPath);
		}
	}

	return TRUE;
}

void CBCGPOrganizerDoc::OnFileClose() 
{
}

void CBCGPOrganizerDoc::UpdateZoom (int index)
{
	if (index == -1)
	{
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
		if (pFrame != NULL)
		{
			index = pFrame->GetZoomSlider ()->GetPos ();
		}
	}

	if (GetMode () == e_ModeGantt)
	{
		CGanttView* pView = DYNAMIC_DOWNCAST (CGanttView, GetView (CBCGPOrganizerDoc::e_ModeGantt));
		if (pView != NULL)
		{
			pView->UpdateZoom (index);
		}
	}
}
