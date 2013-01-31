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
// BCGPMSMoneyDemoView.cpp : implementation of the CBCGPMSMoneyDemoView class
//

#include "stdafx.h"
#include "BCGPMSMoneyDemo.h"

#include "BCGPMSMoneyDemoDoc.h"
#include "BCGPMSMoneyDemoView.h"

#include "MainFrm.h"

#include "BCGPMSMVisualManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoView

IMPLEMENT_DYNCREATE(CBCGPMSMoneyDemoView, CView)

BEGIN_MESSAGE_MAP(CBCGPMSMoneyDemoView, CView)
	//{{AFX_MSG_MAP(CBCGPMSMoneyDemoView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoView construction/destruction

CBCGPMSMoneyDemoView::CBCGPMSMoneyDemoView()
{
	m_ptOffset = CPoint (20, 20);
}

CBCGPMSMoneyDemoView::~CBCGPMSMoneyDemoView()
{
	m_sizeImage = CSize (0, 0);
}

BOOL CBCGPMSMoneyDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~WS_BORDER;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoView drawing

void CBCGPMSMoneyDemoView::OnDraw(CDC* pDCView)
{
	CBCGPMemDC memDC (*pDCView, this);
	CDC* pDC = &memDC.GetDC ();

	CBCGPMSMoneyDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rectClient;
	GetClientRect (rectClient);

	pDC->FillSolidRect (rectClient, RGB (255, 255, 255));

	pDC->DrawState (m_ptOffset, m_sizeImage, &m_Image, DSS_NORMAL);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoView printing

BOOL CBCGPMSMoneyDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBCGPMSMoneyDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBCGPMSMoneyDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoView diagnostics

#ifdef _DEBUG
void CBCGPMSMoneyDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CBCGPMSMoneyDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBCGPMSMoneyDemoDoc* CBCGPMSMoneyDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPMSMoneyDemoDoc)));
	return (CBCGPMSMoneyDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPMSMoneyDemoView message handlers
// these are all simple one-liners to do simple controlling of the browser

BOOL CBCGPMSMoneyDemoView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

static BCGP_GRID_COLOR_DATA theme = 
{
	(COLORREF)-1,	// Grid background color
	(COLORREF)-1,	// Grid foreground color
	(COLORREF)-1,	// Header foreground color

	{	// Even rows colors:
		RGB (246, 250, 253), (COLORREF)-1, (COLORREF)-1, 0, (COLORREF)-1
	},

	{	// Odd rows colors:
		(COLORREF)-1, (COLORREF)-1, (COLORREF)-1, 0, (COLORREF)-1
	},

	{	// Group colors:
		RGB (210, 230, 249), RGB (16, 37, 127), RGB (228, 241, 251), 90, (COLORREF)-1
	},

	{	// Selected group colors:
		RGB (250, 199, 97), RGB (0, 0, 0), (COLORREF)-1, 0, RGB (192, 192, 192)
	},

	{	// Selected rows colors:
		RGB (255, 229, 153), (COLORREF)-1, (COLORREF)-1, 0, RGB (192, 192, 192)
	},

	{	// Header item colors:
		RGB (154, 194, 237), RGB (16, 37, 127), RGB (189, 214, 242), 90, RGB (136, 176, 228)
	},

	{	// Selected header item colors:
		(COLORREF)-1, (COLORREF)-1, (COLORREF)-1, 0, (COLORREF)-1
	},

	{	// Left offset colors:
		RGB (207, 221, 240), (COLORREF)-1, RGB (227, 234, 244), 90, RGB (136, 176, 228)
	},

	(COLORREF)-1,	// Grid horizontal line text
	(COLORREF)-1,	// Grid vertical line text
	(COLORREF)-1,	// Description text color
};

int CBCGPMSMoneyDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_Image.LoadBitmap (IDB_BCGPMSM_VIEW_BKGND);

	BITMAP bitmap;
	m_Image.GetBitmap (&bitmap);

	m_sizeImage = CSize (bitmap.bmWidth, bitmap.bmHeight);

	CRect rectGrid (CPoint (m_ptOffset.x, m_ptOffset.y + m_sizeImage.cy), CSize (m_sizeImage.cx, 200));

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE, rectGrid, this, 1);
	m_wndGrid.SetColorTheme (theme);

	FillGrid ();

	return 0;
}

void CBCGPMSMoneyDemoView::FillGrid ()
{
	ASSERT_VALID (this);

	m_wndGrid.InsertColumn (0, _T(""), 0);
	m_wndGrid.InsertColumn (1, _T("Quarter"), 185);
	m_wndGrid.InsertColumn (2, _T("Amount"), 80);
	m_wndGrid.InsertColumn (3, _T("Change"), 80);

	m_wndGrid.SetColumnAlign (0, HDF_RIGHT);
	m_wndGrid.SetColumnAlign (2, HDF_RIGHT);
	m_wndGrid.SetColumnAlign (3, HDF_RIGHT);
	m_wndGrid.SetHeaderAlign (2, HDF_RIGHT);
	m_wndGrid.SetHeaderAlign (3, HDF_RIGHT);
	m_wndGrid.SetColumnLocked (0);

	AddData (_T("I"), _T("$2,554.00"), 0.0021);
	AddData (_T("II"), _T("$2,370.00"), -0.0052);
	AddData (_T("III"), _T("$1,825.00"), -0.027);
	AddData (_T("IV"), _T("$4,778.00"), 0.0911);

	CBCGPGridRow* pRow5 = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());
	
	pRow5->GetItem (0)->SetValue (_T("Total:"));
	pRow5->GetItem (2)->SetValue (_T("$ 1,1527.00"));

	m_wndGrid.AddRow (pRow5);

	m_wndGrid.MergeRange (CBCGPGridRange (0, 4, 1, 4));
	m_wndGrid.MergeRange (CBCGPGridRange (2, 4, 3, 4));

	m_wndGrid.EnableHeader (TRUE, 0);
	m_wndGrid.EnableColumnAutoSize (TRUE);
	m_wndGrid.SetReadOnly (TRUE);
}

BOOL CBCGPMSMoneyDemoView::AddData (LPCTSTR strPeriod, LPCTSTR strValue, double dDifference)
{
	CBCGPGridRow* pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());

	CString strCurrDate = __DATE__;
	
	CString strQaurter;
	strQaurter.Format (_T("%s %s"), strPeriod, strCurrDate.Right (4));

	pRow->GetItem (1)->SetValue ((LPCTSTR)strQaurter);

	pRow->GetItem (2)->SetValue (strValue);
	CBCGPGridPercentItem* pPercItem = new CBCGPGridPercentItem (dDifference);
	pPercItem->SetPrecision (2);
	pPercItem->SetTextColor (dDifference < 0 ? RGB (255, 0, 0) : RGB (0, 127, 0));
	pRow->ReplaceItem (3, pPercItem);
	m_wndGrid.AddRow (pRow);

	return TRUE;
}
