// AddressBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPMediaPlayer.h"
#include "AddressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static void DrawButton (CDC* pDC, CRect rect, const CString& strText, BOOL bIsMenuButton,
						UINT nStyle, BOOL bHighlight, BOOL bIsDroppedDown)
{
	int nIndex = -1;

	if ((nStyle & TBBS_DISABLED) == 0)
	{
		if ((nStyle & TBBS_PRESSED) || bIsDroppedDown)
		{
			nIndex = 1;
		}
		else if (bHighlight)
		{
			nIndex = 0;
		}
	}

	CRect rt (rect);
	CBCGPControlRenderer& rRen = GetVisualManager ()->GetAddressBarButtonImage ();
	rt.top += rect.Height () - rRen.GetParams ().m_rectImage.Height ();

	if (nIndex != -1)
	{
		rRen.Draw (pDC, rt, nIndex);
	}

	rt.bottom = rt.top + rt.Height () * 3 / 4;

	COLORREF clr = pDC->SetTextColor (RGB (255, 255, 255));
	pDC->DrawText (strText, rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SetTextColor (clr);

	if (bIsMenuButton)
	{
		rt.bottom = rect.bottom;

		GetVisualManager ()->GetArrowDownIcon ().DrawEx (pDC, rt, 0, 
			CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertBottom);
	}
}

class CAddressToolbarButton: public CBCGPToolbarButton
{
	DECLARE_DYNCREATE(CAddressToolbarButton)

public:
	CAddressToolbarButton ()
	{
	}

	CAddressToolbarButton (UINT nCmdID, LPCTSTR lpszText = NULL) :
		CBCGPToolbarButton (nCmdID, -1, lpszText)
	{
	}

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* /*pImages*/,
						BOOL /*bHorz*/ = TRUE, BOOL /*bCustomizeMode*/ = FALSE,
						BOOL bHighlight = FALSE,
						BOOL /*bDrawBorder*/ = TRUE,
						BOOL /*bGrayDisabledButtons*/ = TRUE)
	{
		DrawButton (pDC, rect, m_strText, FALSE, m_nStyle, bHighlight, FALSE);
	}

	virtual SIZE OnCalculateSize (CDC* /*pDC*/, const CSize& sizeDefault, BOOL /*bHorz*/)
	{
		return CSize (
			(m_nStyle & TBBS_SEPARATOR)
				? GetVisualManager ()->GetAddressBarSeparatorWidth ()
				: GetVisualManager ()->GetAddressBarButtonWidth (), 
			sizeDefault.cy);
	}
};

IMPLEMENT_DYNCREATE(CAddressToolbarButton, CBCGPToolbarButton)

class CAddressToolbarMenuButton: public CBCGPToolbarMenuButton
{
	DECLARE_DYNCREATE(CAddressToolbarMenuButton)

public:
	CAddressToolbarMenuButton () 
	{
	}

	CAddressToolbarMenuButton (HMENU hMenu, LPCTSTR lpszText = NULL) :
		CBCGPToolbarMenuButton ((UINT)-1, hMenu, -1, lpszText)
	{
		SetMenuOnly (TRUE);
	}

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* /*pImages*/,
						BOOL /*bHorz*/ = TRUE, BOOL /*bCustomizeMode*/ = FALSE,
						BOOL bHighlight = FALSE,
						BOOL /*bDrawBorder*/ = TRUE,
						BOOL /*bGrayDisabledButtons*/ = TRUE)
	{
		DrawButton (pDC, rect, m_strText, TRUE, m_nStyle, bHighlight, IsDroppedDown ());
	}

	virtual SIZE OnCalculateSize (CDC* /*pDC*/, const CSize& sizeDefault, BOOL /*bHorz*/)
	{
		return CSize (GetVisualManager ()->GetAddressBarButtonWidth (), sizeDefault.cy);
	}
};

IMPLEMENT_DYNCREATE(CAddressToolbarMenuButton, CBCGPToolbarMenuButton)

/////////////////////////////////////////////////////////////////////////////
// CAddressBar

IMPLEMENT_DYNCREATE (CAddressBar, CBCGPExplorerToolBar)

CAddressBar::CAddressBar()
{
	m_bIsAeroEnabled = FALSE;
	m_bShowHotBorder = FALSE;
}

CAddressBar::~CAddressBar()
{
	
}

BEGIN_MESSAGE_MAP(CAddressBar, CBCGPExplorerToolBar)
	//{{AFX_MSG_MAP(CAddressBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAddressBar::OnLoadNavImages ()
{
	CVisualManager* pVM = GetVisualManager ();
	if (pVM != NULL)
	{
		pVM->m_arLinkImages.Add (CVisualManager::XLinkImages (&pVM->m_btnBaseAddressBF, &m_NavImages));
		pVM->m_arLinkImages.Add (CVisualManager::XLinkImages (&pVM->m_btnBaseAddressFrameBF, &m_NavFrames));

		pVM->m_btnBaseAddressBF.CopyTo (m_NavImages);
		pVM->m_btnBaseAddressFrameBF.CopyTo (m_NavFrames);

		pVM->UpdateLinkImages ();
	}
}

int CAddressBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPExplorerToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetBorders (GetVisualManager ()->GetAddressBarBorders ());

	return 0;
}

int CAddressBar::GetRowHeight () const
{
	int nHeight = GetVisualManager ()->GetAddressBarBackImage ().GetParams ().m_rectImage.Height ();

	if (nHeight == 0)
	{
		nHeight = CBCGPExplorerToolBar::GetRowHeight ();
	}	

	return nHeight;
}

void CAddressBar::DrawSeparator (CDC* pDC, const CRect& rect, BOOL /*bHorz*/)
{
	CBCGPToolBarImages& rImage = GetVisualManager ()->GetAddressBarSeparatorImage ();

	CRect rt (rect);
	rt.top += rect.Height () - rImage.GetImageSize ().cy;
	rImage.DrawEx (pDC, rt, 0, CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertBottom);
}

void CAddressBar::CreateButtons ()
{
	InsertButton (CAddressToolbarButton (ID_FILE_OPEN, _T("Open Media...")));

	CMenu menu;
	menu.LoadMenu (IDR_ADDRESS_VIEW);
	InsertButton (CAddressToolbarMenuButton (menu.GetSafeHmenu (), _T("View")));

	CAddressToolbarButton sep;
	sep.m_nStyle = TBBS_SEPARATOR;
	InsertButton (sep);
}
