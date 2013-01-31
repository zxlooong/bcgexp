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
// StartView.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "StartView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartView

#define IDC_START_IMAGE	1

IMPLEMENT_DYNCREATE(CStartView, CView)

CStartView::CStartView()
{
}

CStartView::~CStartView()
{
}

BEGIN_MESSAGE_MAP(CStartView, CView)
	//{{AFX_MSG_MAP(CStartView)
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnDisableUpdate)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnDisableUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnDisableUpdate)
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDS_CARET_POS, OnCaretPos)
	ON_BN_CLICKED(IDC_START_IMAGE, OnClickHotSpot)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartView diagnostics

#ifdef _DEBUG
void CStartView::AssertValid() const
{
	CView::AssertValid();
}

void CStartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStartView message handlers

void CStartView::OnInitialUpdate() 
{
	CDocument* pDoc = GetDocument ();
	ASSERT_VALID (pDoc);

	CRect rectClient;
	GetClientRect (rectClient);

	m_Image.Create (rectClient, this, IDC_START_IMAGE);
	SetBitmap ();

	pDoc->SetTitle (_T("Start Page"));
}

void CStartView::OnDraw(CDC* /*pDC*/)
{
}

void CStartView::OnCaretPos(CCmdUI* pCmdUI)
{
	pCmdUI->SetText (_T(""));
	pCmdUI->Enable(FALSE);
}

BOOL CStartView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

void CStartView::OnDisableUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CStartView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_Image.GetSafeHwnd () != NULL)
	{
		m_Image.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

void CStartView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	if (m_Image.GetSafeHwnd () != NULL)
	{
		m_Image.SetFocus ();
	}	
}

void CStartView::OnClickHotSpot()
{
	UINT uiCmd = m_Image.GetHotSpot ();
	if (uiCmd == 1)
	{
		uiCmd = ID_HELP_WEB;
	}

	AfxGetMainWnd ()->SendMessage (WM_COMMAND, uiCmd);
}

void CStartView::OnSysColorChange() 
{
	CView::OnSysColorChange();
	SetBitmap ();	
}

void CStartView::SetBitmap ()
{
	if (m_Image.GetSafeHwnd () == NULL)
	{
		return;
	}

	m_Image.SetImage (IDB_START_HC);
	m_Image.SetBackgroundColor (RGB (227, 232, 242));
	m_Image.SetHighlightHotArea (82, 45);

	m_Image.AddHotSpot (1, CRect (CPoint (33, 302), CSize (125, 50)));
	m_Image.AddHotSpot (ID_VIEW_CUSTOMIZE, CRect (CPoint (360, 139), CSize (186, 29)));
	m_Image.AddHotSpot (ID_VIEW_APP_LOOK, CRect (CPoint (360, 175), CSize (186, 18)));
	m_Image.AddHotSpot (ID_FILE_NEW, CRect (CPoint (360, 193), CSize (186, 29)));
	m_Image.AddHotSpot (ID_HELP_WEB, CRect (CPoint (360, 229), CSize (186, 29)));
}
