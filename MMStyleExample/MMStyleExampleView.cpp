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
// MMStyleExampleView.cpp : implementation of the CMMStyleExampleView class
//

#include "stdafx.h"
#include "MMStyleExample.h"

#include "MMStyleExampleDoc.h"
#include "MMStyleExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT idPlay = 1;

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView

IMPLEMENT_DYNCREATE(CMMStyleExampleView, CView)

BEGIN_MESSAGE_MAP(CMMStyleExampleView, CView)
	//{{AFX_MSG_MAP(CMMStyleExampleView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView construction/destruction

CMMStyleExampleView::CMMStyleExampleView()
{
	// TODO: add construction code here

}

CMMStyleExampleView::~CMMStyleExampleView()
{
}

BOOL CMMStyleExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView drawing

void CMMStyleExampleView::OnDraw(CDC* pDC)
{
	ASSERT_VALID (pDC);

	CMMStyleExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPDrawManager dm (*pDC);

	//-------------------
	// Redraw background:
	//-------------------
	COLORREF color1 = RGB (83, 113, 235);
	COLORREF color2 = RGB (122, 186, 243);

	dm.FillGradient2 (rectClient, color2, color1, 55);

	//-----------------------------
	// Draw total/current position:
	//-----------------------------
	pDC->SetBkMode (TRANSPARENT);

	PrintText (pDC, pDoc->GetSong (), 10, 10, m_fntSong);
	PrintText (pDC, m_strProgress, m_rectProgress.left, m_rectProgress.top, m_fntProgress);
}

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView printing

void CMMStyleExampleView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CMMStyleExampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMMStyleExampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMMStyleExampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView diagnostics

#ifdef _DEBUG
void CMMStyleExampleView::AssertValid() const
{
	CView::AssertValid();
}

void CMMStyleExampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMMStyleExampleDoc* CMMStyleExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMMStyleExampleDoc)));
	return (CMMStyleExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView message handlers

void CMMStyleExampleView::OnTimer(UINT_PTR nIDEvent) 
{
	CView::OnTimer(nIDEvent);

	if (nIDEvent != idPlay)
	{
		return;
	}

	CMMStyleExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->m_bIsPause)
	{
		return;
	}

	PrepareProgressText ();
	RedrawWindow (m_rectProgress);
}

void CMMStyleExampleView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* /*pHint*/) 
{
	switch (lHint)
	{
	case MMS_OPEN:
		RedrawWindow ();
		break;

	case MMS_PLAY:
		SetTimer (idPlay, 1000, NULL);

		PrepareProgressText ();
		RedrawWindow (m_rectProgress);
		break;

	case MMS_STOP:
		KillTimer (idPlay);
		m_strProgress.Empty ();
		RedrawWindow (m_rectProgress);
		break;
	}
}

int CMMStyleExampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc (this);

	LOGFONT	lf;
	memset (&lf, 0, sizeof (LOGFONT));

	lstrcpy (lf.lfFaceName, _T("Times New Roman"));
	lf.lfWeight = FW_BOLD;
	lf.lfCharSet = (BYTE) GetTextCharsetInfo (dc.GetSafeHdc (), NULL, 0);
	lf.lfHeight = -24;

	m_fntSong.CreateFontIndirect (&lf);

	lf.lfHeight = -16;
	m_fntProgress.CreateFontIndirect (&lf);

	CFont* pOldFont = dc.SelectObject (&m_fntProgress);
	ASSERT (pOldFont != NULL);

	CString strProgress = _T("00:00 / 00:00");
	CSize sizeProgress = dc.GetTextExtent (strProgress);
	
	m_rectProgress = CRect (CPoint (30, 50), sizeProgress);

	dc.SelectObject (pOldFont);
	return 0;
}

void CMMStyleExampleView::PrintText (CDC* pDC, CString str, 
									 int x, int y, CFont& font)
{
	ASSERT_VALID (pDC);

	if (str.IsEmpty ())
	{
		return;
	}

	CFont* pOldFont = pDC->SelectObject (&font);
	ASSERT (pOldFont != NULL);

	pDC->SetTextColor (RGB (100, 100, 100));
	pDC->TextOut (x + 1, y + 1, str);

	pDC->SetTextColor (RGB (255, 255, 255));
	pDC->TextOut (x, y, str);

	pDC->SelectObject (pOldFont);
}

BOOL CMMStyleExampleView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

void CMMStyleExampleView::PrepareProgressText ()
{
	CMMStyleExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int nCurr = pDoc->GetCurrent () / 1000;
	int nTotal = pDoc->GetTotal () / 1000;

	m_strProgress.Format (_T("%02d:%02d / %02d:%02d"), 
		nCurr / 60, nCurr % 60,
		nTotal / 60, nTotal / 60);
}
