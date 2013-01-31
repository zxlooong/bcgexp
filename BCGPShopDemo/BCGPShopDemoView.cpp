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
// BCGPShopDemoView.cpp : implementation of the CBCGPShopDemoView class
//

#include "stdafx.h"
#include "BCGPShopDemo.h"

#include "BCGPShopDemoDoc.h"
#include "BCGPShopDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoView

IMPLEMENT_DYNCREATE(CBCGPShopDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CBCGPShopDemoView, CScrollView)
	//{{AFX_MSG_MAP(CBCGPShopDemoView)
    ON_WM_ERASEBKGND()
    ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoView construction/destruction

CBCGPShopDemoView::CBCGPShopDemoView()
    : m_nHorizontalViewMargin (30), m_nVerticalViewMargin (20)
{
	// TODO: add construction code here

}

CBCGPShopDemoView::~CBCGPShopDemoView()
{
}

BOOL CBCGPShopDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
    CScrollView::PreCreateWindow (cs);
    cs.style &= ~(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME);
	return TRUE;
}

int CBCGPShopDemoView::OnCreate(LPCREATESTRUCT lpcs)
{
    int iResult = CScrollView::OnCreate (lpcs);
    if (iResult != -1)
    {
        ASSERT (GetDocument () != NULL);
        CSize szView = GetDocument ()->GetSize ();
        szView.cx += m_nHorizontalViewMargin * 2;
        szView.cy += m_nVerticalViewMargin * 2;
        SetScrollSizes (MM_TEXT, szView);
    }
    return iResult;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoView drawing

void CBCGPShopDemoView::OnDraw(CDC* pDC)
{
    CRect rcClip;
    pDC->GetClipBox (&rcClip);

	CRect rcPage = GetPageRect ();

    CBCGPDrawManager dm (*pDC);
    dm.DrawRect (rcPage, 0xFFFFFF, 0x000000); // Page

    pDC->ExcludeClipRect (rcPage);
    pDC->FillSolidRect (&rcClip, 0xA0A0A0); // Background
}

BOOL CBCGPShopDemoView::OnEraseBkgnd( CDC * )
{
    return TRUE; // Omit erasing background
}

CRect CBCGPShopDemoView::GetPageRect ()
{
    CBCGPShopDemoDoc* pDoc = GetDocument ();
    if (pDoc == NULL)
	{
		return CRect (0, 0, 0 ,0);
	}

    CSize szDoc = pDoc->GetSize ();

    CRect rcClient;
    GetClientRect(&rcClient);

    int xPage = rcClient.left + (rcClient.Width() - szDoc.cx) / 2;
    int yPage = rcClient.top + (rcClient.Height() - szDoc.cy) / 2;

    xPage = max (xPage, m_nHorizontalViewMargin);
    yPage = max (yPage, m_nVerticalViewMargin);

    return CRect (xPage, yPage, xPage + szDoc.cx, yPage + szDoc.cy);
}

BOOL CBCGPShopDemoView::MapScreenPoint (CPoint& ptInOut)
{
    ScreenToClient (&ptInOut);

    CRect rcPage = GetPageRect ();
    CPoint ptScrollPos = GetScrollPosition ();
    ptInOut.Offset (ptScrollPos.x, ptScrollPos.y);
    
	BOOL bPtInPage = rcPage.PtInRect (ptInOut);
    ptInOut.Offset (-rcPage.left, -rcPage.top);

    return bPtInPage;
}

COLORREF CBCGPShopDemoView::GetPixelColor (const CPoint& ptView) const
{
    UNUSED_ALWAYS (ptView);
    return 0xFFFFFF; // always white
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoView diagnostics

#ifdef _DEBUG
void CBCGPShopDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CBCGPShopDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CBCGPShopDemoDoc* CBCGPShopDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPShopDemoDoc)));
	return (CBCGPShopDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPShopDemoView message handlers
