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
// FunnyStyle.cpp: implementation of the CFunnyStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPSkins.h"
#include "FunnyStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CFunnyStyle, CBCGPVisualManager2003)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFunnyStyle::CFunnyStyle()
{

}
//****************************************************************************************
CFunnyStyle::~CFunnyStyle()
{

}
//****************************************************************************************
void CFunnyStyle::OnDrawBarGripper (CDC* pDC, CRect rectGripper, BOOL bHorz,
									   CBCGPBaseControlBar* /*pBar*/)
{
	if (bHorz)
	{
		rectGripper.DeflateRect (3, 4);
	}
	else
	{
		rectGripper.DeflateRect (4, 3);
	}

	CBCGPDrawManager dm (*pDC);
	dm.FillGradient (rectGripper, RGB (255, 255, 255), RGB (0, 159, 98), bHorz);

	if (bHorz)
	{
		rectGripper.InflateRect (1, 0);
	}
	else
	{
		rectGripper.InflateRect (0, 1);
	}

	dm.DrawShadow (rectGripper, 3);
}
//****************************************************************************************
COLORREF CFunnyStyle::OnFillMiniFrameCaption (CDC* pDC, CRect rectCaption, 
											CBCGPMiniFrameWnd* /*pFrameWnd*/, 
											BOOL /*bActive*/)
{
	CBCGPDrawManager dm (*pDC);
	dm.FillGradient (rectCaption, RGB (255, 255, 255), RGB (0, 159, 98), FALSE);

	return RGB (0, 0, 0);
}
//*****************************************************************************************
void CFunnyStyle::OnFillBarBackground  (CDC* pDC, CBCGPBaseControlBar* pBar,
										CRect rectClient, CRect rectClip,
										BOOL bNCArea)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pBar);

	CBCGPDrawManager dm (*pDC);

	if (pBar->IsKindOf (RUNTIME_CLASS (CBCGPOutlookBarPane)))
	{
		dm.FillGradient (rectClip, RGB (113, 175, 210), RGB (255, 255, 255), FALSE);
		return;
	}

	if (!bNCArea)
	{
		CRgn rgn;
		rgn.CreateRectRgnIndirect (&rectClient);

		pDC->SelectClipRgn (&rgn);
	}

	CRect rectFill = rectClient;

	if (!pBar->IsFloating () &&
		!pBar->IsKindOf (RUNTIME_CLASS (CBCGPPopupMenuBar)))
	{
		CRect rectMainFrame;
		pBar->GetTopLevelFrame ()->GetWindowRect (rectMainFrame);

		pBar->ScreenToClient (&rectMainFrame);
		rectFill = rectMainFrame;

		if (bNCArea)
		{
			CRect rectWindow;
			pBar->GetWindowRect (rectWindow);

			pBar->ScreenToClient (rectWindow);

			CRect rectClientActual;
			pBar->GetClientRect (rectClientActual);

			rectFill.left += rectClientActual.left - rectWindow.left;
			rectFill.top += rectClientActual.top - rectWindow.top;
			rectFill.right += 10;
		}
	}

	dm.FillGradient (rectFill, RGB (113, 175, 210), RGB (255, 255, 255), FALSE);

	if (!bNCArea)
	{
		pDC->SelectClipRgn (NULL);
	}
}
//************************************************************************************
void CFunnyStyle::OnHighlightMenuItem (CDC* pDC, CBCGPToolbarMenuButton* /*pButton*/,
											CRect rect, COLORREF& clrText)
{
	ASSERT_VALID (pDC);

	CBCGPDrawManager dm (*pDC);

	rect.DeflateRect (1, 2);
	dm.FillGradient (rect, RGB (255, 255, 255), RGB (0, 159, 98), FALSE);

	rect.InflateRect (0, 1);
	dm.DrawShadow (rect, 3);

	clrText = RGB (0, 0, 0);
}
//**************************************************************************************
void CFunnyStyle::OnDrawSeparator (CDC* pDC, CBCGPBaseControlBar* pBar, CRect rect, BOOL bHorz)
{
	rect.DeflateRect (2, 2);
	CBCGPVisualManager2003::OnDrawSeparator (pDC, pBar, rect, bHorz);
}
//**************************************************************************************
void CFunnyStyle::OnEraseTabsArea (CDC* pDC, CRect rect, const CBCGPBaseTabWnd* /*pTabWnd*/)
{
	CBCGPDrawManager dm (*pDC);
	dm.FillGradient (rect, RGB (113, 175, 210), RGB (255, 255, 255), FALSE);
}
//****************************************************************************************
COLORREF CFunnyStyle::OnDrawControlBarCaption (CDC* pDC, CBCGPDockingControlBar* /*pBar*/, 
	BOOL /*bActive*/, CRect rectCaption, CRect rectButtons)
{
	rectCaption.right = rectButtons.left - 1;
	rectCaption.DeflateRect (2, 2);

	CBCGPDrawManager dm (*pDC);
	dm.FillGradient (rectCaption, RGB (255, 255, 255), RGB (0, 159, 98), TRUE);

	dm.DrawShadow (rectCaption, 3);
	return RGB (0, 0, 0);
}
//*********************************************************************************
void CFunnyStyle::OnFillOutlookPageButton (CDC* pDC, const CRect& rect,
										BOOL bIsHighlighted, BOOL bIsPressed,
										COLORREF& clrText)
{
	CBCGPDrawManager dm (*pDC);

	COLORREF clr1 = RGB (155, 255, 255);
	COLORREF clr2 = RGB (100, 159, 198);

	dm.FillGradient2 (rect, bIsPressed ? clr2 : clr1, bIsPressed ? clr1 : clr2,
		bIsHighlighted ? 135 : 45);

	clrText = RGB (0, 0, 0);
}
//*********************************************************************************
void CFunnyStyle::OnDrawOutlookPageButtonBorder (CDC* pDC, CRect& rectBtn, BOOL bIsHighlighted, BOOL /*bIsPressed*/)
{
	COLORREF clr = bIsHighlighted ? RGB (155, 255, 255) : RGB (100, 159, 198);
	pDC->Draw3dRect (rectBtn, clr, clr);
}
//**************************************************************************************
COLORREF CFunnyStyle::GetToolbarButtonTextColor (CBCGPToolbarButton* pButton,
												  CBCGPVisualManager2003::BCGBUTTON_STATE state)
{
	ASSERT_VALID (pButton);

	if (pButton->IsKindOf (RUNTIME_CLASS (CBCGPOutlookButton)))
	{
		return RGB (98, 100, 155);
	}

	return CBCGPVisualManager2003::GetToolbarButtonTextColor (pButton, state);
}
//*********************************************************************************
void CFunnyStyle::OnDrawSlider (CDC* pDC, CBCGPSlider* pSlider, CRect rect, BOOL bAutoHideMode)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pSlider);

	if (bAutoHideMode)
	{
		CBCGPVisualManager2003::OnDrawSlider (pDC, pSlider, rect, bAutoHideMode);
		return;
	}

	CBCGPDrawManager dm (*pDC);

	COLORREF clr1 = RGB (155, 255, 255);
	COLORREF clr2 = RGB (100, 159, 198);

	dm.FillGradient (rect, clr1, clr2, FALSE);
}
