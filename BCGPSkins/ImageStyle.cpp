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
// ImageStyle.cpp: implementation of the CImageStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPSkins.h"
#include "ImageStyle.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString		CImageStyle::m_strImagePath;
BOOL		CImageStyle::m_bIsInternalImage = TRUE;
int			CImageStyle::m_nHighlight = 100;
COLORREF	CImageStyle::m_clrText = (COLORREF)-1;

IMPLEMENT_DYNCREATE(CImageStyle, CBCGPVisualManagerXP)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageStyle::CImageStyle()
{
}
//*********************************************************************************
CImageStyle::~CImageStyle()
{

}
//****************************************************************************************
void CImageStyle::OnFillBarBackground  (CDC* pDC, CBCGPBaseControlBar* pBar,
										CRect rectClient, CRect /*rectClip*/,
										BOOL bNCArea)
{
	if (!bNCArea)
	{
		CRgn rgn;
		rgn.CreateRectRgnIndirect (&rectClient);

		pDC->SelectClipRgn (&rgn);
	}

	FillArea (pDC, rectClient, pBar, pBar->IsFloating (), bNCArea);
	pDC->SelectClipRgn (NULL);
}

void CImageStyle::OnEraseTabsArea (CDC* pDC, CRect rect, const CBCGPBaseTabWnd* pTabWnd)
{
	ASSERT_VALID (pDC);
	FillArea (pDC, rect, pTabWnd, FALSE, FALSE);
}

void CImageStyle::FillArea (CDC* pDC, CRect rect, const CWnd* pWnd, BOOL bIsFloating,
							BOOL bNCArea)
{
	if (m_bmpBack.GetSafeHandle () == NULL)
	{
		globalData.clrBtnText = m_clrText;

		// Load background bitmap:
		if (!m_bIsInternalImage)
		{
			HBITMAP hbmp = (HBITMAP) ::LoadImage (
				AfxGetInstanceHandle (),
				m_strImagePath,
				IMAGE_BITMAP,
				0, 0,
				LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			VERIFY (hbmp != NULL);

			m_bmpBack.Attach (hbmp);
		}
		else
		{
			m_bmpBack.LoadBitmap (IDB_BACKGROUND);
		}

		BITMAP bmp;
		m_bmpBack.GetBitmap (&bmp);

		m_sizeBmp = CSize (bmp.bmWidth, bmp.bmHeight);
	}

	int xOffset = rect.left;
	int yOffset = rect.top;

	if (!bIsFloating &&
		!pWnd->IsKindOf (RUNTIME_CLASS (CBCGPPopupMenuBar)))
	{
		CRect rectMainFrame;
		pWnd->GetTopLevelFrame ()->GetWindowRect (rectMainFrame);

		pWnd->ScreenToClient (&rectMainFrame);

		xOffset = rectMainFrame.left % m_sizeBmp.cx;
		yOffset = rectMainFrame.top % m_sizeBmp.cy;

		if (bNCArea)
		{
			CRect rectWindow;
			pWnd->GetWindowRect (rectWindow);

			pWnd->ScreenToClient (rectWindow);

			CRect rectClientActual;
			pWnd->GetClientRect (rectClientActual);

			xOffset += rectClientActual.left - rectWindow.left;
			yOffset += rectClientActual.top - rectWindow.top;
		}
	}

	for (int x = xOffset; x < rect.right; x += m_sizeBmp.cx)
	{
		for (int y = yOffset; y < rect.bottom; y += m_sizeBmp.cy)
		{
			pDC->DrawState (CPoint (x, y), m_sizeBmp, &m_bmpBack, 0);
		}
	}

	CBCGPDrawManager dm (*pDC);
	dm.HighlightRect (rect, m_nHighlight);
}
//****************************************************************************************
COLORREF CImageStyle::OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* pBar, 
	BOOL /*bActive*/, CRect rectCaption, CRect /*rectButtons*/)
{
	CRgn rgn;
	rgn.CreateRectRgnIndirect (rectCaption);

	pDC->SelectClipRgn (&rgn);
	FillArea (pDC, rectCaption, pBar, FALSE, TRUE);

	return RGB (0, 0, 0);
}
//**************************************************************************************
COLORREF CImageStyle::GetToolbarButtonTextColor (	CBCGPToolbarButton* /*pButton*/,
												CBCGPVisualManagerXP::BCGBUTTON_STATE /*state*/)
{
	return m_clrText;
}
//*********************************************************************************
void CImageStyle::OnFillOutlookPageButton (CDC* pDC, const CRect& rect,
										BOOL /*bIsHighlighted*/, BOOL /*bIsPressed*/,
										COLORREF& clrText)
{
	CRgn rgn;
	rgn.CreateRectRgnIndirect (rect);

	pDC->SelectClipRgn (&rgn);
	FillArea (pDC, rect, &((CMainFrame*) AfxGetMainWnd ())->GetOutlookBar (), FALSE, FALSE);

	pDC->SelectClipRgn (NULL);

	clrText = m_clrText;
}
