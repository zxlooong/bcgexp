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
// PreviewPane.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPOutlookDemo.h"
#include "PreviewPane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nHorzMargin = 2;
const int nVertMargin = 2;

/////////////////////////////////////////////////////////////////////////////
// CPreviewPane

IMPLEMENT_DYNCREATE(CPreviewPane, CView)

CPreviewPane::CPreviewPane()
{
}

CPreviewPane::~CPreviewPane()
{
}


BEGIN_MESSAGE_MAP(CPreviewPane, CView)
	//{{AFX_MSG_MAP(CPreviewPane)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewPane drawing

void CPreviewPane::OnDraw(CDC* pDC)
{
	CRect rectClient;
	GetClientRect (rectClient);

	CRect rectCaption = rectClient;
	rectCaption.bottom = rectCaption.top + globalData.GetTextHeight () + 4;

	CRect rectMessage = rectClient;
	rectMessage.top = rectCaption.bottom;

	pDC->FillRect (rectCaption, &globalData.brBarFace);
	pDC->FillRect (rectMessage, &globalData.brWindow);

	int nOldBkMode = pDC->SetBkMode (TRANSPARENT);
	COLORREF clrOldText = pDC->SetTextColor (globalData.clrBarText);
	CFont* pOldFont = (CFont*) pDC->SelectStockObject (DEFAULT_GUI_FONT);

	CRect rectText = rectCaption;
	rectText.left += 2 * nHorzMargin;
	rectText.right -= 2 * nHorzMargin + rectText.Height ();

	CString strCaption = _T("Preview area...");
	pDC->DrawText (strCaption, rectText, 
				DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER);

	pDC->SetTextColor (globalData.clrWindowText);

	rectText = rectMessage;
	rectText.DeflateRect (nHorzMargin, nVertMargin);

	CString strText = _T("Message body");
	pDC->DrawText (strText, rectText, DT_WORDBREAK | DT_END_ELLIPSIS);

	pDC->SelectObject (pOldFont);
	pDC->SetTextColor (clrOldText);
	pDC->SetBkMode (nOldBkMode);
}

/////////////////////////////////////////////////////////////////////////////
// CPreviewPane diagnostics

#ifdef _DEBUG
void CPreviewPane::AssertValid() const
{
	CView::AssertValid();
}

void CPreviewPane::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPreviewPane message handlers

BOOL CPreviewPane::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}
