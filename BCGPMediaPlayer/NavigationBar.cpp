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
// NavigationBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"
#include "NavigationBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class CNavigationToolbarButton: public CBCGPToolbarButton
{
	DECLARE_DYNCREATE(CNavigationToolbarButton)

public:
	CNavigationToolbarButton (){}
	CNavigationToolbarButton (UINT nCmdID, 
		const CSize& sizeImage, const CString& strImage,
		const CSize& sizeIcon, const CString& strIcon,
		LPCTSTR lpszText = NULL) :
		CBCGPToolbarButton (nCmdID, -1, lpszText)
	{
		if (!strImage.IsEmpty ())
		{
			m_Image.SetImageSize (sizeImage);
			m_Image.LoadStr (strImage);
		}

		if (!strIcon.IsEmpty ())
		{
			m_Icon.SetImageSize (sizeIcon);
			m_Icon.LoadStr (strIcon);
		}
	}

	virtual void OnDraw (CDC* /*pDC*/, const CRect& /*rect*/, CBCGPToolBarImages* /*pImages*/,
						BOOL /*bHorz*/ = TRUE, BOOL /*bCustomizeMode*/ = FALSE,
						BOOL /*bHighlight*/ = FALSE,
						BOOL /*bDrawBorder*/ = TRUE,
						BOOL /*bGrayDisabledButtons*/ = TRUE)
	{
	}
	virtual SIZE OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz)
	{
		CSize size (CBCGPToolbarButton::OnCalculateSize (pDC, sizeDefault, bHorz));

		if (m_nStyle & TBBS_SEPARATOR)
		{
			size.cx = GetVisualManager ()->GetNaviBarSeparatorWidth ();
		}
		else
		{
			size = m_Image.GetImageSize ();
			if (m_nID == ID_NAVI_PREV || m_nID == ID_NAVI_NEXT)
			{
				size.cx--;
			}
			else if (m_nID == ID_NAVI_PLAY)
			{
				size.cx -= 2;
			}
		}

		return size;
	}
	virtual const CRect GetInvalidateRect () const
	{
		CRect rect (m_rect);

		switch (m_nID)
		{
		case ID_NAVI_PREV:
			rect.right++;
			break;
		case ID_NAVI_NEXT:
			rect.left--;
			break;
		case ID_NAVI_PLAY:
			rect.top++;
			rect.InflateRect (5, 5);
			break;
		case ID_NAVI_SOUND:
			rect.right += 15;
			break;
		case ID_NAVI_VOLUME:
			rect.left -= 24;
			break;
		}

		return rect;
	}
	virtual void CopyFrom (const CBCGPToolbarButton& s)
	{
		CBCGPToolbarButton::CopyFrom (s);

		CNavigationToolbarButton& src = const_cast<CNavigationToolbarButton&>((const CNavigationToolbarButton&)s);
		src.m_Image.CopyTo (m_Image);
		src.m_Icon.CopyTo (m_Icon);
	}

	CBCGPToolBarImages& GetImage ()
	{
		return m_Image;
	}
	CBCGPToolBarImages& GetIcon ()
	{
		return m_Icon;
	}

protected:
	CBCGPToolBarImages m_Image;
	CBCGPToolBarImages m_Icon;
};

IMPLEMENT_DYNCREATE(CNavigationToolbarButton, CBCGPToolbarButton)

/////////////////////////////////////////////////////////////////////////////
// CNavigationBar

IMPLEMENT_DYNCREATE (CNavigationBar, CBCGPToolBar)

CNavigationBar::CNavigationBar()
{
	m_bShowHotBorder = FALSE;
	m_bPlay = TRUE;
	m_dProgress = -1.0;
	m_nVolume = 50;
}

CNavigationBar::~CNavigationBar()
{
	
}

BEGIN_MESSAGE_MAP(CNavigationBar, CBCGPToolBar)
	//{{AFX_MSG_MAP(CNavigationBar)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CNavigationBar::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
{
	return CreateEx(pParentWnd, 0, dwStyle, nID);
}

BOOL CNavigationBar::CreateEx (CWnd* pParentWnd, DWORD /*dwCtrlStyle*/, DWORD dwStyle, 
							 UINT nID)
{
	ASSERT_VALID(pParentWnd);   // must have a parent

	m_dwStyle |= CBRS_HIDE_INPLACE;

	dwStyle &= ~CBRS_GRIPPER;

	// save the style
	SetBarAlignment (dwStyle & CBRS_ALL);

	// create the HWND
	CRect rect;
	rect.SetRectEmpty();

	m_dwBCGStyle = 0; // can't float, resize, close, slide

	if (!CWnd::Create (globalData.RegisterWindowClass (_T("NavigationBar")),
		NULL, dwStyle | WS_CLIPSIBLINGS, rect, pParentWnd, nID))
	{
		return FALSE;
	}

	return TRUE;
}

int CNavigationBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetBorders (GetVisualManager ()->GetNaviBarBorders ());

	return 0;
}

int CNavigationBar::GetRowHeight () const
{
	int nHeight = GetVisualManager ()->GetNaviBarBackImage ().GetParams ().m_rectImage.Height ();

	if (nHeight == 0)
	{
		nHeight = CBCGPToolBar::GetRowHeight ();
	}
	else
	{
		nHeight -= ::GetSystemMetrics (SM_CYSIZEFRAME);
	}

	return nHeight;
}

void CNavigationBar::DrawSeparator (CDC* /*pDC*/, const CRect& /*rect*/, BOOL /*bHorz*/)
{
}

void CNavigationBar::CreateButtons ()
{
	CNavigationToolbarButton sep;
	sep.m_nStyle = TBBS_SEPARATOR;

	InsertButton (CNavigationToolbarButton (ID_NAVI_STOP, 
		CSize (25, 25), _T("IDB_BTN_NORMAL"), 
		CSize (25, 25), _T("IDB_NAVI_STOP_ICON"),
		_T("Stop")));

	InsertButton (sep);

	InsertButton (CNavigationToolbarButton (ID_NAVI_PREV, 
		CSize (54, 27), _T("IDB_NAVI_PREV"), 
		CSize (54, 25), _T("IDB_NAVI_PREV_ICON"),
		_T("Previous")));

	InsertButton (CNavigationToolbarButton (ID_NAVI_PLAY, 
		CSize (42, 43), _T("IDB_NAVI_PLAY"), 
		CSize (42, 43), _T("IDB_NAVI_PLAY_ICON"),
		_T("Play")));

	InsertButton (CNavigationToolbarButton (ID_NAVI_NEXT, 
		CSize (54, 27), _T("IDB_NAVI_NEXT"), 
		CSize (54, 25), _T("IDB_NAVI_NEXT_ICON"),
		_T("Next")));

	InsertButton (sep);

	InsertButton (CNavigationToolbarButton (ID_NAVI_SOUND, 
		CSize (24, 25), _T("IDB_BTN_SPLIT"), 
		CSize (25, 25), _T("IDB_NAVI_SOUND_ICON"),
		_T("Sound")));

	InsertButton (CNavigationToolbarButton (ID_NAVI_VOLUME, 
		CSize (15, 25), _T("IDB_BTN_SPLIT_M"), 
		CSize (0, 0), _T(""),
		_T("Volume")));

	m_PlayH.SetImageSize (CSize (52, 52));
	m_PlayH.LoadStr (_T("IDB_NAVI_PLAY_H"));

	{
		CBCGPControlRendererParams params (_T("IDB_NAVI_PROGRESS_ICON"), CRect (0, 0, 11, 9), CRect (9, 4, 1, 4));
		m_Progress.Create (params);
	}
	m_ProgressR.SetImageSize (CSize (30, 9));
	m_ProgressR.LoadStr (_T("IDB_NAVI_PROGRESS_ICON_R"));
}

void CNavigationBar::AdjustLayout ()
{
	CBCGPToolBar::AdjustLayout ();

	BOOL bOnGlass = m_bOnGlass;

	m_bOnGlass = FALSE;

	if (globalData.DwmIsCompositionEnabled ())
	{
		CRect rectWindow;
		GetWindowRect (rectWindow);

		BCGPMARGINS margins;
		margins.cxLeftWidth = 0;
		margins.cxRightWidth = 0;
		margins.cyTopHeight = 0;
		margins.cyBottomHeight = rectWindow.Height ();

		if (globalData.DwmExtendFrameIntoClientArea (
			GetParent ()->GetSafeHwnd (), &margins))
		{
			m_bOnGlass = TRUE;
		}
	}

	if (bOnGlass != m_bOnGlass)
	{
		SendMessage (BCGM_ONSETCONTROLAERO, (WPARAM) m_bOnGlass);
	}
}

void CNavigationBar::AdjustLocations ()
{
	ASSERT_VALID(this);
	
	CBCGPToolBar::AdjustLocations ();

	if (m_Buttons.IsEmpty () || GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect (rectClient);

	CPoint ptBegin (0, 14);
	ptBegin.x = (rectClient.Width () - GetVisualManager ()->GetNaviBarControlImage ().GetImageSize ().cx) / 2;

	if (GetVisualManager ()->IsLargeNaviControl ())
	{
		ptBegin.x += 101;
	}
	else
	{
		ptBegin.x += 24;
	}

	// Center buttons vertically:
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGPToolbarButton* pButton = (CBCGPToolbarButton*) m_Buttons.GetNext (pos);
		if (pButton == NULL || pButton == (CBCGPToolbarButton*)m_pCustomizeBtn)
		{
			break;
		}

		ASSERT_VALID (pButton);

		if (pButton->IsVisible ())
		{
			CRect rectButton = pButton->Rect ();

			rectButton.OffsetRect (ptBegin.x, ptBegin.y + (43 - rectButton.Height ()) / 2);

			pButton->SetRect (rectButton);
		}
	}

	UpdateTooltips ();
}

void CNavigationBar::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CBCGPToolBar::OnShowWindow(bShow, nStatus);
	
	if (!bShow && m_bOnGlass)
	{
		BCGPMARGINS margins;
		margins.cxLeftWidth = 0;
		margins.cxRightWidth = 0;
		margins.cyTopHeight = 0;
		margins.cyBottomHeight = 0;

		globalData.DwmExtendFrameIntoClientArea (
			GetParent ()->GetSafeHwnd (), &margins);
	}
}

void CNavigationBar::DWMCompositionChanged ()
{
	AdjustLayout ();
	RedrawWindow ();
}

void CNavigationBar::InvalidateProgress ()
{
	CRect rectClient;
	GetClientRect (rectClient);

	CRect rectProgress (rectClient);
	rectProgress.top += 2;
	rectProgress.bottom = rectProgress.top + m_ProgressR.GetImageSize ().cy;

	InvalidateRect (rectProgress);
}

void CNavigationBar::OnFillBackground (CDC* pDC)
{
	ASSERT_VALID (pDC);

	CRect rectClip;
	pDC->GetClipBox (rectClip);

	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPVisualManager::GetInstance ()->OnFillBarBackground (pDC, this,
		rectClient, rectClip);

	if (m_dProgress != -1.0)
	{
		CRect rectProgress (rectClient);
		rectProgress.top += 2;
		rectProgress.bottom = rectProgress.top + m_ProgressR.GetImageSize ().cy;

		rectProgress.right = rectProgress.left + 
			(int)((rectProgress.Width () - m_ProgressR.GetImageSize ().cx) * m_dProgress / 100.0);
		if (rectProgress.right > rectProgress.left)
		{
			CRect rectPart (rectProgress);
			rectPart.right += m_Progress.GetParams ().m_rectCorners.left;
			m_Progress.Draw (pDC, rectPart);
		}

		rectProgress.right += m_ProgressR.GetImageSize ().cx;
		m_ProgressR.DrawEx (pDC, rectProgress, 0, CBCGPToolBarImages::ImageAlignHorzRight);
	}

	UINT nID[6] = 
	{
		ID_NAVI_STOP,
		ID_NAVI_PREV,
		ID_NAVI_NEXT,
		ID_NAVI_PLAY,
		ID_NAVI_SOUND,
		ID_NAVI_VOLUME
	};

	for (int i = 0; i < sizeof (nID) / sizeof (UINT); i++)
	{
		CNavigationToolbarButton* pButton = 
			DYNAMIC_DOWNCAST (CNavigationToolbarButton, GetButton (CommandToIndex (nID[i])));
		if (pButton == NULL)
		{
			continue;
		}

		CBCGPToolbarButton* pHighlighted = GetHighlightedButton ();
		CRect rect (pButton->Rect ());

		int indexImage = 1;
		int indexIcon = 0;

		if (pButton->m_nStyle & TBBS_DISABLED)
		{
			indexImage = 0;
			indexIcon = 1;
		}
		else if (pButton->m_nStyle & TBBS_PRESSED)
		{
			indexImage = 3;
		}
		else if (pHighlighted == pButton)
		{
			indexImage = 2;
		}

		switch (nID[i])
		{
		case ID_NAVI_PREV:
			rect.right++;
			break;
		case ID_NAVI_NEXT:
			rect.left--;
			break;
		case ID_NAVI_PLAY:
			rect.left--;
			rect.right++;
			if (!m_bPlay)
			{
				indexIcon += 2;
			}
			break;
		case ID_NAVI_SOUND:
			if (indexImage > 1)
			{
				indexImage++;
			}
			else if (pHighlighted != NULL && pHighlighted->m_nID == ID_NAVI_VOLUME)
			{
				indexImage = 2;
			}
			
			indexIcon = 0;
			if (m_nVolume == -1)
			{
				indexIcon = 4;
			}
			else if (m_nVolume > 0)
			{
				indexIcon = 3 * m_nVolume / 100;
			}
			break;
		case ID_NAVI_VOLUME:
			if (indexImage > 1)
			{
				indexImage++;
			}
			else if (pHighlighted != NULL && pHighlighted->m_nID == ID_NAVI_SOUND)
			{
				indexImage = 2;
			}
			break;
		}

		if (pButton->GetImage ().IsValid ())
		{
			pButton->GetImage ().DrawEx (pDC, rect, indexImage);
		}

		if (pButton->GetIcon ().IsValid ())
		{
			pButton->GetIcon ().DrawEx (pDC, rect, indexIcon);
		}

		if (nID[i] == ID_NAVI_PLAY && indexImage == 2)
		{
			rect.top++;
			rect.InflateRect (5, 5);
			m_PlayH.DrawEx (pDC, rect, 0);
		}
	}
}
