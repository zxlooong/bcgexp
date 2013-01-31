//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a part of BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPMediaPlayerView.cpp : implementation of the CBCGPMediaPlayerView class
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"

#include "BCGPMediaPlayerDoc.h"
#include "BCGPMediaPlayerView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int c_TimerPlay = 111;

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerView

IMPLEMENT_DYNCREATE(CBCGPMediaPlayerView, CView)

BEGIN_MESSAGE_MAP(CBCGPMediaPlayerView, CView)
	//{{AFX_MSG_MAP(CBCGPMediaPlayerView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(MCIWNDM_NOTIFYMODE, OnMCIMode)
	ON_MESSAGE(MCIWNDM_NOTIFYSIZE, OnMCISize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerView construction/destruction

CBCGPMediaPlayerView::CBCGPMediaPlayerView()
{
	m_Timer = NULL;
}

CBCGPMediaPlayerView::~CBCGPMediaPlayerView()
{
}

BOOL CBCGPMediaPlayerView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerView drawing

void CBCGPMediaPlayerView::OnDraw(CDC* pDC)
{
	if (::IsWindowVisible (GetMCIControl ().GetSafeHwnd ()))
	{
		return;
	}

	CBCGPMediaPlayerDoc* pDoc = GetDocument ();
	ASSERT_VALID (pDoc);

	CRect rect;
	GetClientRect (rect);

	CDC dc;
	dc.CreateCompatibleDC (pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap (pDC, rect.Width (), rect.Height ());
	CBitmap* pOldBitmap = dc.SelectObject (&bitmap);

	dc.FillRect (rect, &GetVisualManager ()->GetViewBrush ());
	//-----------------------------
	// Draw total/current position:
	//-----------------------------
	dc.SetBkMode (TRANSPARENT);

	PrintText (&dc, pDoc->GetFileName (), 10, 10, m_fntSong);
	PrintText (&dc, m_strProgress, m_rectProgress.left, m_rectProgress.top, m_fntProgress);

	pDC->BitBlt (0, 0, rect.Width (), rect.Height (), &dc, 0, 0, SRCCOPY);

	dc.SelectObject (pOldBitmap);
}

void CBCGPMediaPlayerView::PrintText (CDC* pDC, const CString& str, 
									 int x, int y, CFont& font)
{
	ASSERT_VALID (pDC);

	if (str.IsEmpty ())
	{
		return;
	}

	CVisualManager* pVM = GetVisualManager ();

	CFont* pOldFont = pDC->SelectObject (&font);
	ASSERT (pOldFont != NULL);

	pDC->SetTextColor (pVM->GetSliderColor (3));
	pDC->TextOut (x + 1, y + 1, str);

	pDC->SetTextColor (pVM->GetSliderColor (0));
	pDC->TextOut (x, y, str);

	pDC->SelectObject (pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerView diagnostics

#ifdef _DEBUG
void CBCGPMediaPlayerView::AssertValid() const
{
	CView::AssertValid();
}

void CBCGPMediaPlayerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBCGPMediaPlayerDoc* CBCGPMediaPlayerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPMediaPlayerDoc)));
	return (CBCGPMediaPlayerDoc*)m_pDocument;
}

CMCIControl& CBCGPMediaPlayerView::GetMCIControl()
   { return GetDocument ()->GetMCIControl (); }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPMediaPlayerView message handlers

BOOL CBCGPMediaPlayerView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

int CBCGPMediaPlayerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!GetMCIControl ().Create (GetSafeHwnd ()))
	{
		return -1;
	}

	CClientDC dc (this);

	LOGFONT	lf;
	memset (&lf, 0, sizeof (LOGFONT));

	if (globalData.bIsWindows9x || globalData.bIsWindowsNT4)
	{
		lstrcpy (lf.lfFaceName, _T("Times New Roman"));
		lf.lfHeight = -24;
	}
	else
	{
		lstrcpy (lf.lfFaceName, _T("Verdana"));
		lf.lfHeight = -22;
	}
	lf.lfQuality = 5;
	lf.lfWeight  = FW_BOLD;
	lf.lfCharSet = (BYTE) GetTextCharsetInfo (dc.GetSafeHdc (), NULL, 0);


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

void CBCGPMediaPlayerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (GetMCIControl ().GetSafeHwnd () != NULL)
	{
		::SetWindowPos (GetMCIControl ().GetSafeHwnd (), HWND_TOP, 0, 0, cx, cy, 
			SWP_NOZORDER | SWP_NOOWNERZORDER);
	}
}

LRESULT CBCGPMediaPlayerView::OnMCIMode (WPARAM /*wParam*/, LPARAM lParam)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd ();
	if (pFrame != NULL)
	{
		pFrame->GetNavigationBar ().SetPlay (lParam != MCI_MODE_PLAY);

		if (lParam == MCI_MODE_PLAY && m_Timer == NULL)
		{
			m_Timer = SetTimer (c_TimerPlay, GetMCIControl ().GetActiveTimer (), NULL);
		}
		else if (lParam == MCI_MODE_STOP && m_Timer != NULL)
		{
			OnTimer (c_TimerPlay);
			KillTimer (c_TimerPlay);
			m_Timer = NULL;
		}
	}

	SendMessage (WM_NCPAINT);

	return 0L;
}

LRESULT CBCGPMediaPlayerView::OnMCISize (WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	CRect rect;
	GetClientRect (rect);

	CRect rectMCI;
	::GetWindowRect (GetMCIControl ().GetSafeHwnd (), rectMCI);

	if (rect.Width () != rectMCI.Width () ||
		rect.Height () != rectMCI.Height ())
	{
		::SetWindowPos (GetMCIControl ().GetSafeHwnd (), HWND_TOP, 0, 0, rect.Width (), rect.Height (), 
			SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE);
	}

	GetMCIControl ().AdjustSize ();

	return 0L;
}

void CBCGPMediaPlayerView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);

	if (nIDEvent != c_TimerPlay)
	{
		return;
	}

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd ();
	if (pFrame != NULL)
	{
		CString str;

		LONG mode = GetMCIControl ().GetMode ();
		if (mode == MCI_MODE_PLAY ||
			mode == MCI_MODE_PAUSE)
		{
			LONG nCurr = GetMCIControl ().GetPosition () / 1000;
			LONG nTotal = GetMCIControl ().GetLength () / 1000;

			str.Format (_T("%02d:%02d / %02d:%02d"), 
				nCurr / 60, nCurr % 60,
				nTotal / 60, nTotal / 60);
		}

		pFrame->GetNavigationBar ().SetProgress (GetMCIControl ().GetPositionPerc ());

		if (str != m_strProgress)
		{
			m_strProgress = str;
			Invalidate ();
		}	
	}
}

void CBCGPMediaPlayerView::OnNcPaint ()
{
	CWindowDC dc (this);

	CRect rtWindow;
	GetWindowRect (rtWindow);
	ScreenToClient (rtWindow);

	CRect rtClient;
	GetClientRect (rtClient);

	rtClient.OffsetRect (-rtWindow.TopLeft ());
	dc.ExcludeClipRect (rtClient);

	rtWindow.OffsetRect (-rtWindow.TopLeft ());

	HBRUSH hbr = (HBRUSH)GetVisualManager ()->GetViewBrush ().GetSafeHandle ();

	if (::IsWindowVisible (GetMCIControl ().GetSafeHwnd ()))
	{
		hbr = (HBRUSH)::GetStockObject (BLACK_BRUSH);
	}

	::FillRect (dc.GetSafeHdc (), rtWindow, hbr);
}

void CBCGPMediaPlayerView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd ();
	if (pFrame != NULL)
	{
		pFrame->GetNavigationBar ().SetVolume ((LONG)GetMCIControl ().GetVolumePerc ());
	}	
}
