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
// DefaultView.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "DefaultView.h"

#include "../BCGPOrganizer.h"
#include "../mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDefaultView

IMPLEMENT_DYNCREATE(CDefaultView, CView)

BEGIN_MESSAGE_MAP(CDefaultView, CView)
	//{{AFX_MSG_MAP(CDefaultView)
	ON_WM_ERASEBKGND ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefaultView construction/destruction

CDefaultView::CDefaultView()
	: m_nAppLook (0)
{
	m_Pat[0].Create (CBCGPControlRendererParams (IDB_VIEWPAT_2, (COLORREF)-1, 
		CRect (0, 0, 499, 157), CRect (0, 0, 0, 0), CRect (480, 0, 0, 0), CRect (480, 0, 499, 157)));
	m_Pat[1].Create (CBCGPControlRendererParams (IDB_VIEWPAT_3, (COLORREF)-1, 
		CRect (0, 0, 499, 157), CRect (0, 0, 0, 0), CRect (480, 0, 0, 0), CRect (480, 0, 499, 157)));
	m_Pat[2].Create (CBCGPControlRendererParams (IDB_VIEWPAT_4, (COLORREF)-1, 
		CRect (0, 0, 499, 157), CRect (0, 0, 0, 0), CRect (480, 0, 0, 0), CRect (480, 0, 499, 157)));	
}

CDefaultView::~CDefaultView()
{
}

BOOL CDefaultView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDefaultView drawing

BOOL CDefaultView::OnEraseBkgnd(CDC*)
{
	return FALSE;
}

void CDefaultView::OnDrawMemDC (CDC* /*pDC*/)
{
}

void CDefaultView::OnDraw(CDC* pDC)
{
	UINT nAppLook = theApp.m_nAppLook;

	CRect rectScreen;
	GetClientRect (rectScreen);

	if (m_MemDC.GetSafeHdc () == NULL)
	{
		m_pOldBitmap = NULL;
		m_MemDC.CreateCompatibleDC (pDC);
	}

	if (m_MemBitmap.GetSafeHandle () != NULL)
	{
		BITMAP bmp;
		m_MemBitmap.GetBitmap (&bmp);

		if (bmp.bmWidth != rectScreen.Width () || bmp.bmHeight != rectScreen.Height () ||
			m_nAppLook != nAppLook)
		{
			m_MemBitmap.DeleteObject ();
		}
	}

	m_nAppLook = nAppLook;

	if (m_MemBitmap.GetSafeHandle () == NULL)
	{
		m_MemBitmap.CreateCompatibleBitmap (pDC, rectScreen.Width (), rectScreen.Height ());

		if (m_pOldBitmap != NULL)
		{
			m_MemDC.SelectObject (m_pOldBitmap);
		}

		m_pOldBitmap = m_MemDC.SelectObject (&m_MemBitmap);

		CBCGPDrawManager dm (m_MemDC);

		switch (m_nAppLook)
		{
		case 0:
			dm.FillGradient (rectScreen, RGB (114, 125, 152), RGB (178, 185, 202), TRUE);
			break;

		default:
			{
				const BOOL bLuna     = m_nAppLook == 1;
				const BOOL bObsidian = m_nAppLook == 2;

				CBCGPControlRenderer& pat = bLuna
					? m_Pat[0]
					: bObsidian 
						? m_Pat[1]
						: m_Pat[2];

				COLORREF clrF = bLuna
					? RGB (136, 170, 214)
					: bObsidian
						? RGB ( 71,  71,  71)
						: RGB (164, 170, 186);
				COLORREF clrM = bLuna
					? RGB ( 86, 125, 176)
					: bObsidian
						? RGB ( 56,  56,  56)
						: RGB (156, 160, 167);
				COLORREF clrL = bLuna
					? RGB (101, 145, 205)
					: bObsidian
						? RGB ( 11,  11,  11)
						: RGB (204, 207, 216);

				const CSize szPat = pat.GetParams ().m_rectImage.Size ();

				CRect rectPat = rectScreen;

				rectPat.bottom = rectPat.top + szPat.cy;

				CRect rectGradient = rectScreen;
				rectGradient.top += szPat.cy;

				if (rectGradient.Height () < 50 ||
					(rectGradient.Height () - 120) < 50)
				{
					rectGradient.bottom = rectGradient.top + 50;
				}
				else
				{
					rectGradient.bottom -= 120;
				}

				dm.FillGradient (rectGradient, clrM, clrF, TRUE);

				if (rectGradient.bottom < rectScreen.bottom)
				{
					rectGradient.top    = rectGradient.bottom;
					rectGradient.bottom = rectScreen.bottom;

					dm.FillGradient (rectGradient, clrL, clrM, TRUE);
				}

				pat.Draw (&m_MemDC, rectPat, 0);

				OnDrawMemDC (&m_MemDC);
			}
		}
	}

	pDC->BitBlt (0, 0, rectScreen.Width (), rectScreen.Height (), &m_MemDC, 0, 0, SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CDefaultView diagnostics

#ifdef _DEBUG
void CDefaultView::AssertValid() const
{
	CView::AssertValid();
}

void CDefaultView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDefaultView message handlers
