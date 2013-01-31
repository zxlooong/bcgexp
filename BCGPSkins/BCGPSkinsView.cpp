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
// BCGPSkinsView.cpp : implementation of the CBCGPSkinsView class
//

#include "stdafx.h"
#include "BCGPSkins.h"

#include "BCGPSkinsDoc.h"
#include "BCGPSkinsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsView

IMPLEMENT_DYNCREATE(CBCGPSkinsView, CScrollView)

BEGIN_MESSAGE_MAP(CBCGPSkinsView, CScrollView)
	//{{AFX_MSG_MAP(CBCGPSkinsView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsView construction/destruction

CBCGPSkinsView::CBCGPSkinsView()
{
	m_sizeImage = CSize (0, 0);
}

CBCGPSkinsView::~CBCGPSkinsView()
{
}

BOOL CBCGPSkinsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsView drawing

void CBCGPSkinsView::OnDraw(CDC* pDCPaint)
{
	CDC*		pDC = pDCPaint;
	BOOL		m_bMemDC = FALSE;
	CDC			dcMem;
	CBitmap		bmp;
	CBitmap*	pOldBmp = NULL;

	CRect rect;
	GetClientRect (rect);

	rect.right += GetScrollPos (SB_HORZ);
	rect.bottom += GetScrollPos (SB_VERT);

	if (dcMem.CreateCompatibleDC (pDCPaint) &&
		bmp.CreateCompatibleBitmap (pDCPaint, rect.Width (),
								  rect.Height ()))
	{
		//-------------------------------------------------------------
		// Off-screen DC successfully created. Better paint to it then!
		//-------------------------------------------------------------
		m_bMemDC = TRUE;
		pOldBmp = dcMem.SelectObject (&bmp);
		pDC = &dcMem;
	}

	pDC->FillSolidRect (rect, RGB (255, 255, 255));
	pDC->DrawState (CPoint (0, 0), m_sizeImage, &m_Bmp, DSS_NORMAL);

	if (m_bMemDC)
	{
		//--------------------------------------
		// Copy the results to the on-screen DC:
		//-------------------------------------- 
		CRect rectClip;
		int nClipType = pDCPaint->GetClipBox (rectClip);
		if (nClipType != NULLREGION)
		{
			if (nClipType != SIMPLEREGION)
			{
				rectClip = rect;
			}

			pDCPaint->BitBlt (rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(),
						   &dcMem, rectClip.left, rectClip.top, SRCCOPY);
		}

		dcMem.SelectObject(pOldBmp);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsView printing

void CBCGPSkinsView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CBCGPSkinsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBCGPSkinsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBCGPSkinsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsView diagnostics

#ifdef _DEBUG
void CBCGPSkinsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CBCGPSkinsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CBCGPSkinsDoc* CBCGPSkinsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPSkinsDoc)));
	return (CBCGPSkinsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPSkinsView message handlers


void CBCGPSkinsView::OnInitialUpdate() 
{
	if (m_Bmp.GetSafeHandle () == NULL)
	{
		m_Bmp.LoadBitmap (IDB_VIEW);

		BITMAP bmp;
		m_Bmp.GetBitmap (&bmp);

		m_sizeImage.cx = bmp.bmWidth;
		m_sizeImage.cy = bmp.bmHeight;

		SetScrollSizes (MM_TEXT, m_sizeImage);
	}
}

BOOL CBCGPSkinsView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}
