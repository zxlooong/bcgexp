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
// BCGPOutlookDemoView.cpp : implementation of the CBCGPOutlookDemoView class
//

#include "stdafx.h"
#include "BCGPOutlookDemo.h"

#include "BCGPOutlookDemoDoc.h"
#include "BCGPOutlookDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoView

IMPLEMENT_DYNCREATE(CBCGPOutlookDemoView, CBCGPReportView)

BEGIN_MESSAGE_MAP(CBCGPOutlookDemoView, CBCGPReportView)
	//{{AFX_MSG_MAP(CBCGPOutlookDemoView)
	ON_COMMAND(ID_VIEW_PREVIEW_PANE, OnViewPreviewPane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIEW_PANE, OnUpdateViewPreviewPane)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CBCGPReportView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPReportView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoView construction/destruction

CBCGPOutlookDemoView::CBCGPOutlookDemoView()
{
	// TODO: add construction code here

}

CBCGPOutlookDemoView::~CBCGPOutlookDemoView()
{
}

BOOL CBCGPOutlookDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT;
	return CBCGPReportView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoView drawing

void CBCGPOutlookDemoView::OnDraw(CDC* /*pDC*/)
{
	CBCGPOutlookDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

BOOL CBCGPOutlookDemoView::AddMail (int nIcon, LPCTSTR strFrom,
		 LPCTSTR strSubject,
		 IMPORTANCE importance/* = IMPORTANCE_NORMAL*/,
		 BOOL bHasAttachment/* = FALSE*/)
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	CBCGPGridRow* pRow = pReportCtrl->CreateRow (pReportCtrl->GetColumnCount ());

	//----------------
	// Set importance:
	//----------------
	int nImportanceIcon = -1;
	switch (importance)
	{
	case IMPORTANCE_HIGH:
		nImportanceIcon = 2;
		break;

	case IMPORTANCE_LOW:
		nImportanceIcon = 3;
		break;
	}

	pRow->GetItem (0)->SetImage (nImportanceIcon, FALSE);
	pRow->GetItem (1)->SetImage (nIcon, FALSE);
	pRow->GetItem (2)->SetImage (bHasAttachment ? 5 : -1, FALSE);

	pRow->GetItem (3)->SetValue (strFrom, FALSE);
	pRow->GetItem (4)->SetValue (strSubject, FALSE);

	pReportCtrl->AddRow (pRow, FALSE);

	return TRUE;
}

void CBCGPOutlookDemoView::OnInitialUpdate()
{
	CBCGPReportView::OnInitialUpdate();

	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);

	pReportCtrl->RemoveAll ();

	AddMail (0, _T("BCGSoft"), _T("Welcome to BCGControlBar Pro!"));
	AddMail (1, _T("George"), _T("Test message..."), IMPORTANCE_HIGH, TRUE);

	pReportCtrl->AdjustLayout ();
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoView printing

void CBCGPOutlookDemoView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoView diagnostics

#ifdef _DEBUG
void CBCGPOutlookDemoView::AssertValid() const
{
	CBCGPReportView::AssertValid();
}

void CBCGPOutlookDemoView::Dump(CDumpContext& dc) const
{
	CBCGPReportView::Dump(dc);
}

CBCGPOutlookDemoDoc* CBCGPOutlookDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPOutlookDemoDoc)));
	return (CBCGPOutlookDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPOutlookDemoView message handlers

void CBCGPOutlookDemoView::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
}

void CBCGPOutlookDemoView::OnViewPreviewPane() 
{
	// TODO: Add your command handler code here
	
}

void CBCGPOutlookDemoView::OnUpdateViewPreviewPane(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command update UI handler code here
	
}

int CBCGPOutlookDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);

	pReportCtrl->SetScrollBarsStyle (
			CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);

	const int nImageWidth = 12;

	m_ImagesHeader.Create (IDB_HEADER_IMAGES, nImageWidth, 0, RGB (255, 0, 255));
	pReportCtrl->SetHeaderImageList (&m_ImagesHeader);

	CBitmap bmp;
	bmp.LoadBitmap (IDB_LIST_IMAGES);

	m_ImagesList.Create (16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
	m_ImagesList.Add (&bmp, RGB (255, 0, 255));
	pReportCtrl->SetImageList (&m_ImagesList);

	//----------------
	// Insert columns:
	//----------------
	pReportCtrl->InsertColumn (0, _T("Importance"), 20, 1);
	pReportCtrl->InsertColumn (1, _T("Icon"), 20, 0);
	pReportCtrl->InsertColumn (2, _T("Attachment"), 20, 2);
	pReportCtrl->InsertColumn (3, _T("From"), 150);
	pReportCtrl->InsertColumn (4, _T("Subject"), 200);

	pReportCtrl->SetColumnLocked (0);
	pReportCtrl->SetColumnLocked (1);
	pReportCtrl->SetColumnLocked (2);

	return 0;
}
