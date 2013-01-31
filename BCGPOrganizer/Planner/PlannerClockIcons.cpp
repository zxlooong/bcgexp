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
// PlannerClockIcons.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "PlannerClockIcons.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlannerClockIcons

IMPLEMENT_DYNCREATE(CPlannerClockIcons, CBCGPPlannerClockIcons)

CPlannerClockIcons::CPlannerClockIcons()
{
}

CPlannerClockIcons::~CPlannerClockIcons()
{
}

BOOL CPlannerClockIcons::Initialize ()
{
	if (IsInitialized ())
	{
		return TRUE;
	}

	CBCGPToolBarImages ilClock;
	ilClock.SetTransparentColor ((COLORREF)-1);
	ilClock.SetPreMultiplyAutoCheck (TRUE);

	if (!ilClock.Load (IDB_PLANNER_CLOCK_C))
	{
		return FALSE;
	}

	ilClock.SetSingleImage ();

	CSize szSize (ilClock.GetImageSize ());
	szSize.cx = szSize.cx / 2;
	
	ilClock.SetImageSize (szSize, TRUE);

	CBCGPToolBarImages ilHours;
	ilHours.SetImageSize (szSize);
	ilHours.SetPreMultiplyAutoCheck (TRUE);

	if (!ilHours.Load (IDB_PLANNER_CLOCK_H))
	{
		return FALSE;
	}

	CBCGPToolBarImages ilMinuts;
	ilMinuts.SetImageSize (szSize);
	ilMinuts.SetPreMultiplyAutoCheck (TRUE);

	if (!ilMinuts.Load (IDB_PLANNER_CLOCK_M))
	{
		return FALSE;
	}

	CBitmap bmp;

	HDC hDC = ::GetDC (NULL);
	CDC* pDC = CDC::FromHandle (hDC);

	CDC dc;
	if (dc.CreateCompatibleDC (pDC))
	{
		BITMAPINFO bi;

		// Fill in the BITMAPINFOHEADER
		bi.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth         = szSize.cx * 24 * 12;
		bi.bmiHeader.biHeight        = szSize.cy;
		bi.bmiHeader.biPlanes        = 1;
		bi.bmiHeader.biBitCount      = 32;
		bi.bmiHeader.biCompression   = BI_RGB;
		bi.bmiHeader.biSizeImage     = bi.bmiHeader.biWidth * bi.bmiHeader.biHeight;
		bi.bmiHeader.biXPelsPerMeter = 0;
		bi.bmiHeader.biYPelsPerMeter = 0;
		bi.bmiHeader.biClrUsed       = 0;
		bi.bmiHeader.biClrImportant  = 0;

		COLORREF* pBits = NULL;
		HBITMAP hmbpDib = CreateDIBSection (
			dc.GetSafeHdc (), &bi, DIB_RGB_COLORS, (void **)&pBits,
			NULL, NULL);

		if (hmbpDib == NULL)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		bmp.Attach (hmbpDib);

		if (bmp.GetSafeHandle () != NULL)
		{
			CBitmap* pOld = dc.SelectObject (&bmp);

			for (int nHour = 0; nHour < 24; nHour++)
			{
				BOOL bPM = nHour >= 12;

				for (int nMinuts = 0; nMinuts < 12; nMinuts++)
				{
					CRect rect (CPoint ((nHour * 12 + nMinuts) * szSize.cx, 0), szSize);

					ilClock.DrawEx (&dc, rect, bPM ? 1 : 0);

					ilHours.DrawEx (&dc, rect, (nHour - (bPM ? 12 : 0)) * 2 + (nMinuts >= 5 ? 1 : 0));

					ilMinuts.DrawEx(&dc, rect, nMinuts);
				}
			}

		    dc.SelectObject (pOld);
		}
	}

	::ReleaseDC (NULL, hDC);

	if (bmp.GetSafeHandle () != NULL)
	{
		m_szSize = szSize;

		m_ilClockIcons.Create (m_szSize.cx, m_szSize.cy, ILC_COLOR32, 
			24 * 12, 0);
		m_ilClockIcons.Add (&bmp, (CBitmap*)NULL);
		m_bInitialized = TRUE;
	}

	return m_bInitialized;
}

#ifdef _DEBUG
void CPlannerClockIcons::AssertValid() const
{
	CBCGPPlannerClockIcons::AssertValid();
}

void CPlannerClockIcons::Dump(CDumpContext& dc) const
{
	CBCGPPlannerClockIcons::Dump(dc);
}
#endif
