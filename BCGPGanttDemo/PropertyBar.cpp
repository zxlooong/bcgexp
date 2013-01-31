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
// PropertyBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPGanttDemo.h"
#include "PropertyBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;
const int nTextMargin = 5;

LPCTSTR lpszNo		= _T("No");
LPCTSTR lpszDefault = _T("Default");
LPCTSTR lpszCustom  = _T("Custom");

static COLORREF colors_light [] =
{
	CLR_DEFAULT, 
	RGB (255, 255, 213),
	RGB (255, 255, 255),
	RGB (213, 236, 188),
	RGB (207, 216, 230),
	RGB (227, 203, 214),
	RGB (193, 214, 209),
	RGB (250, 208, 174),
	RGB (239, 200, 201),
	RGB (208, 216, 203),
	RGB (168, 236, 236),
	RGB (221, 213, 236),
	RGB (230, 230, 230)
};

static COLORREF colors_dark [] =
{
	CLR_DEFAULT, 
	RGB (156, 191, 139),
	RGB (209, 149, 170),
	RGB (176, 182, 190),
	RGB (140, 191, 192),
	RGB (140, 140, 215),
	RGB (141, 193, 157),
	RGB (211, 150, 150),
	RGB (186, 186, 137),
	RGB (174, 153, 216),
	RGB (195, 176, 141),
	RGB (144, 182, 200),
	RGB (255, 223, 134)
};

/////////////////////////////////////////////////////////////////////////////
// CPropertyBar

CPropertyBar::CPropertyBar()
{
}

CPropertyBar::~CPropertyBar()
{
}


BEGIN_MESSAGE_MAP(CPropertyBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CPropertyBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyBar message handlers

int CPropertyBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 1))
	{
		TRACE0("Failed to create Properies Grid \n");
		return -1;      // fail to create
	}

	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_DEFAULT);

	CColorListProp* pColorProp = new CColorListProp (_T("Background color"), 
		theApp.m_Options.m_clrBackground, _T("Modify background color"), idBackground);
	m_wndPropList.AddProperty (pColorProp);

	CBCGPProp* pProp = new CBCGPProp (_T("Show ToolTips"), 
		theApp.m_Options.m_ShowToolTip == 0 ? lpszNo : 
		theApp.m_Options.m_ShowToolTip == 1 ? lpszDefault : lpszCustom,
		_T("Enable or disable ToolTips"), idShowToolTip);
	pProp->AddOption (lpszNo);
	pProp->AddOption (lpszDefault);
	pProp->AddOption (lpszCustom);
	pProp->AllowEdit (FALSE);
	m_wndPropList.AddProperty (pProp);

	return 0;
}

void CPropertyBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	m_wndPropList.SetWindowPos (NULL, nBorderSize, nBorderSize, 
		cx - 2 * nBorderSize, cy - 2 * nBorderSize,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void CPropertyBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectTree;
	m_wndPropList.GetWindowRect (rectTree);
	ScreenToClient (rectTree);

	rectTree.InflateRect (nBorderSize, nBorderSize);
	dc.Draw3dRect (rectTree,	::GetSysColor (COLOR_3DSHADOW), 
								::GetSysColor (COLOR_3DSHADOW));
}

LRESULT CPropertyBar::OnPropertyChanged (WPARAM,LPARAM lParam)
{
	CBCGPProp* pProp = (CBCGPProp*) lParam;

	CGanttOptions& opt = theApp.m_Options;

	switch ((int) pProp->GetData ())
	{
	case idBackground:
		{
			COLORREF color = (COLORREF) (long) pProp->GetValue ();
			opt.m_clrBackground = color;
		}
		break;
	case idShowToolTip:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());
			opt.m_ShowToolTip = 
				str == lpszNo ? 0 : str == lpszDefault ? 1 : 2;
		}
		break;
	}

	theApp.UpdateGantt ();
	return 0;
}

void CPropertyBar::Update ()
{
	CGanttOptions& opt = theApp.m_Options;

	CBCGPProp* pProp = m_wndPropList.GetProperty (0);
	pProp->SetValue ((long) opt.m_clrBackground);

	pProp = m_wndPropList.GetProperty (1);
	pProp->SetValue (opt.m_ShowToolTip == 0 ? lpszNo : 
		opt.m_ShowToolTip == 1 ? lpszDefault : lpszCustom);
}

void CPropertyBar::InitializeColors (BOOL bDark)
{
	if (m_wndPropList.GetPropertyCount () == 0)
	{
		return;
	}

	CColorListProp* pProp = (CColorListProp*)m_wndPropList.GetProperty (0);

	if (pProp->IsDark () != bDark)
	{
		CGanttOptions& opt = theApp.m_Options;

		pProp->Initialize (bDark);

		BOOL bFound = FALSE;
		CString str;
		str.Format ("%ld", opt.m_clrBackground);
		for (int i = 0; i < pProp->GetOptionCount (); i++)
		{
			if (str == pProp->GetOption (i))
			{
				bFound = TRUE;
				break;
			}
		}

		if (!bFound)
		{
			opt.m_clrBackground = CLR_DEFAULT;
			pProp->SetValue ((long) opt.m_clrBackground);

			theApp.UpdateGantt ();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// CColorListProp class

CColorListProp::CColorListProp(const CString& strName, 
							COLORREF colorSelected,
							LPCTSTR lpszDescr, DWORD dwData)
	:	CBCGPProp (strName, (long) colorSelected, lpszDescr, dwData)
{
	Initialize (FALSE);

	AllowEdit (FALSE);
}

void CColorListProp::Initialize (BOOL bDark)
{
	m_bDark = bDark;

	RemoveAllOptions ();

	int nColors = 0;
	COLORREF* pColors = NULL;

	if (m_bDark)
	{
		nColors = sizeof (colors_dark) / sizeof(COLORREF);
		pColors = colors_dark;
	}
	else
	{
		nColors = sizeof (colors_light) / sizeof(COLORREF);
		pColors = colors_light;
	}

	m_arColors.RemoveAll ();
	m_arColors.SetSize (nColors);

	for (int i = 0; i < nColors; i++)
	{
		m_arColors [i] = pColors [i];

		CString str;
		str.Format ("%ld", m_arColors [i]);
		AddOption (str);
	}
}

CComboBox* CColorListProp::CreateCombo (CWnd* pWndParent, CRect rect)
{
	rect.bottom = rect.top + 400;

	CColorPropComboBox* pWndCombo = new CColorPropComboBox (m_arColors);
	if (!pWndCombo->Create (WS_CHILD | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS,
		rect, pWndParent, BCGPROPLIST_ID_INPLACE))
	{
		delete pWndCombo;
		return NULL;
	}

	return pWndCombo;
}

void CColorListProp::OnDrawValue (CDC* pDC, CRect rect)
{
	ASSERT_VALID (m_pWndList);
	ASSERT_VALID (pDC);

	if ((COLORREF)(long) m_varValue == CLR_DEFAULT)
	{
		CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);

		CString str = lpszDefault;

		CRect rectText = rect;
		rectText.DeflateRect (nTextMargin, 0);

		pDC->DrawText (str, rectText, DT_SINGLELINE | DT_VCENTER);

		pDC->SelectObject (pOldFont);
	}
	else
	{
		CBrush br ((COLORREF)(long) m_varValue);

		if (!m_rectButton.IsRectEmpty ())
		{
			rect.right = m_rectButton.left;
		}

		rect.DeflateRect (2, 2);
		pDC->FillRect (rect, &br);
		pDC->Draw3dRect (rect, globalData.clrBtnShadow, globalData.clrBtnShadow);
	}

	m_bValueIsTrancated = FALSE;
}

BOOL CColorListProp::OnUpdateValue ()
{
	ASSERT_VALID (this);

	if (m_pWndInPlace == NULL)
	{
		return FALSE;
	}

	ASSERT_VALID (m_pWndInPlace);
	ASSERT (::IsWindow (m_pWndInPlace->GetSafeHwnd ()));

	CString strText;
	m_pWndInPlace->GetWindowText (strText);

	long lCurVal = (long) m_varValue;
	long lNewVal = 0;

#if _MSC_VER < 1400
	_stscanf (strText, _T("%ld"), &lNewVal);
#else
	_stscanf_s (strText, _T("%ld"), &lNewVal);
#endif

	if (lCurVal != lNewVal && lNewVal != 0)
	{
		m_varValue = (long) lNewVal;
		m_pWndList->OnPropertyChanged (this);
		Redraw ();
	}

	return TRUE;
}

CWnd* CColorListProp::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	CWnd* pWnd = CBCGPProp::CreateInPlaceEdit (rectEdit, bDefaultFormat);
	if (pWnd != NULL)
	{
		pWnd->ShowWindow (SW_HIDE);
	}

	return pWnd;
}

/////////////////////////////////////////////////////////////////////////////
// CColorPropComboBox

CColorPropComboBox::CColorPropComboBox(CArray<COLORREF,COLORREF>& arColors) :
	m_arColors (arColors)
{
}

CColorPropComboBox::~CColorPropComboBox()
{
}

BEGIN_MESSAGE_MAP(CColorPropComboBox, CComboBox)
	//{{AFX_MSG_MAP(CColorPropComboBox)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPropComboBox message handlers

void CColorPropComboBox::OnDrawItem(int /*nIDCtl*/, LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle (lpDIS->hDC);
	ASSERT_VALID (pDC);

	CRect rect = lpDIS->rcItem;
	int nIndex = lpDIS->itemID;

	CBrush br (nIndex <= 0 ? globalData.clrWindow : m_arColors [nIndex]);
	pDC->FillRect (rect, &br);

	if (nIndex < 0)
	{
		return;
	}

	if (nIndex == 0)
	{
		CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);

		CString str = lpszDefault;

		CRect rectText = rect;
		rectText.DeflateRect (nTextMargin, 0);

		pDC->DrawText (str, rectText, DT_SINGLELINE | DT_VCENTER);

		pDC->SelectObject (pOldFont);
	}

	if (lpDIS->itemState & ODS_FOCUS)
	{
		pDC->DrawFocusRect (rect);
	}
}

void CColorPropComboBox::OnMeasureItem(int /*nIDCtl*/, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	CClientDC dc (this);
	CFont* pOldFont = dc.SelectObject (&globalData.fontRegular);

	CString str = lpszDefault;
	CSize sizeText  = dc.GetTextExtent (str);

	dc.SelectObject (pOldFont);

	lpMeasureItemStruct->itemWidth = sizeText.cx + 10;
	lpMeasureItemStruct->itemHeight = sizeText.cy + 4;
}
