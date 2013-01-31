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
#include "BCGPCalendarDemo.h"
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

static LPCTSTR s_TypeNames [] = 
	{
		_T("Day"),
		_T("Work Week"),
		_T("Week"),
		_T("Month"),
		_T("Multi")
	};
static LPCTSTR s_TimeDeltaNames [] = 
	{
		_T("60"),
		_T("30"),
		_T("20"),
		_T("15"),
		_T("10"),
		_T("6"),
		_T("5")
	};

static CString s_TimeIntervalNames [48];

static CString s_FirstDayNames [8];

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
	//RGB (150, 169, 209)
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

	int i;
	
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
	m_wndPropList.SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);

	CBCGPProp* pProp = new CBCGPProp (_T("View"), s_TypeNames [(int) theApp.m_Options.m_Type],
		_T("Modify type"), idType);
	for (i = 0; i < sizeof (s_TypeNames) / sizeof (LPCTSTR); i++)
	{
		pProp->AddOption (s_TypeNames [i]);
	}
	pProp->AllowEdit (FALSE);
	m_wndPropList.AddProperty (pProp);

	CColorListProp* pColorProp = new CColorListProp (_T("Background color"), 
		theApp.m_Options.m_clrBackground, _T("Modify background color"), idBackground);
	m_wndPropList.AddProperty (pColorProp);

	pProp = new CBCGPProp (_T("Images"), theApp.m_Options.m_DefaultImages ? lpszDefault : lpszCustom,
		_T("Modify images"), idImages);
	pProp->AddOption (lpszDefault);
	pProp->AddOption (lpszCustom);
	pProp->AllowEdit (FALSE);
	m_wndPropList.AddProperty (pProp);

	pProp = new CBCGPProp (_T("Clock icons"), theApp.m_Options.m_DefaultClockIcons ? lpszDefault : lpszCustom,
		_T("Modify clock icons"), idClockIcons);
	pProp->AddOption (lpszDefault);
	pProp->AddOption (lpszCustom);
	pProp->AllowEdit (FALSE);
	m_wndPropList.AddProperty (pProp);
	
	pProp = new CBCGPProp (_T("Show ToolTips"), 
		theApp.m_Options.m_ShowToolTip == 0 ? lpszNo : 
		theApp.m_Options.m_ShowToolTip == 1 ? lpszDefault : lpszCustom,
		_T("Enable or disable ToolTips"), idShowToolTip);
	pProp->AddOption (lpszNo);
	pProp->AddOption (lpszDefault);
	pProp->AddOption (lpszCustom);
	pProp->AllowEdit (FALSE);
	m_wndPropList.AddProperty (pProp);
	
	pProp = new CBCGPProp (_T("Use Day View"), (_variant_t) (theApp.m_Options.m_UseDayInsteadWeek ? true : false),
		_T("Use day view instead week view"), idUseDayInsteadWeek); 
	m_wndPropList.AddProperty (pProp);

	CBCGPProp* pGroup1 = new CBCGPProp (_T("Day, Work week & Multi view"));
	{
		s_FirstDayNames [0] = _T("System default");
		for (i = 0; i < 7; i++)
		{
			s_FirstDayNames [i + 1] = 
				CBCGPPlannerManagerCtrl::GetSystemWeekDayName (i == 0 ? 6 : i - 1);
		}

		pProp = new CBCGPProp (_T("First day of week"), 
			(LPCTSTR) (theApp.m_Options.m_WorkFirstDayOfWeek == -1 
				? s_FirstDayNames [0]
				: s_FirstDayNames [theApp.m_Options.m_WorkFirstDayOfWeek + 1]),
			_T("Modify first day of week"), idFirstDayOfWeek);

		for (i = 0; i < 8; i++)
		{
			pProp->AddOption (s_FirstDayNames [i]);
		}
		pProp->AllowEdit (FALSE);
		pGroup1->AddSubItem (pProp);

		CBCGPProp* pGroup11 = new CBCGPProp (_T("Working interval"));

		COleDateTime hour (COleDateTime::GetCurrentTime ());
		hour = COleDateTime (hour.GetYear (), hour.GetMonth (), hour.GetDay (), 0, 0, 0);

		for (i = 0; i < 48; i++)
		{
			s_TimeIntervalNames [i] = 
				CBCGPAppointment::GetFormattedTimeString (hour + 
				COleDateTimeSpan (0, i / 2, i % 2 == 0 ? 0 : 30, 0), TIME_NOSECONDS, FALSE);
		}

		CBCGPProp* pProp11 = new CBCGPProp
			(
				_T("Start time"), 
				(LPCTSTR) s_TimeIntervalNames
					[(int)(theApp.m_Options.m_WorkHourFirst) * 2 + 
					 ((int)((theApp.m_Options.m_WorkHourFirst - (int)(theApp.m_Options.m_WorkHourFirst)) * 100.0) > 0 ? 1 : 0)],
				_T("Start hour"),
				idDayWorkingHourFirst
			);
		CBCGPProp* pProp12 = new CBCGPProp 
			(
				_T("End time"), 
				(LPCTSTR) s_TimeIntervalNames
					[(int)(theApp.m_Options.m_WorkHourLast) * 2 + 
					 ((int)((theApp.m_Options.m_WorkHourLast - (int)(theApp.m_Options.m_WorkHourLast)) * 100.0) > 0 ? 1 : 0)],
				_T("End time"),
				idDayWorkingHourLast
			);

		for (i = 0; i < 48; i++)
		{
			pProp11->AddOption (s_TimeIntervalNames [i]);
			pProp12->AddOption (s_TimeIntervalNames [i]);
		}

		pGroup11->AddSubItem (pProp11);
		pGroup11->AddSubItem (pProp12);

		pGroup1->AddSubItem (pGroup11);

		pProp = new CBCGPProp (_T("Time scale"), s_TimeDeltaNames [(int) theApp.m_Options.m_DayTimeDelta],
			_T("Modify time scale"), idDayTimeDelta);
		for (i = 0; i < sizeof (s_TimeDeltaNames) / sizeof (LPCTSTR); i++)
		{
			pProp->AddOption (s_TimeDeltaNames [i]);
		}
		pProp->AllowEdit (FALSE);
		pGroup1->AddSubItem (pProp);
	}

	m_wndPropList.AddProperty (pGroup1);

	CBCGPProp* pGroup3 = new CBCGPProp (_T("Week view"));
	pGroup3->AddSubItem (new CBCGPProp (_T("End time"), (_variant_t) (theApp.m_Options.m_WeekDrawTimeFinish ? true : false),
		_T("Show end time"), idWeekDrawTimeFinish));
	pGroup3->AddSubItem (new CBCGPProp (_T("Time as clocks"), (_variant_t) (theApp.m_Options.m_WeekDrawTimeIcons ? true : false),
		_T("Show time as clocks"), idWeekDrawTimeIcons));
	m_wndPropList.AddProperty (pGroup3);

	CBCGPProp* pGroup4 = new CBCGPProp (_T("Month view"));
	pGroup4->AddSubItem (new CBCGPProp (_T("End time"), (_variant_t) (theApp.m_Options.m_MonthDrawTimeFinish ? true : false),
		_T("Show end time"), idMonthDrawTimeFinish));
	pGroup4->AddSubItem (new CBCGPProp (_T("Time as clocks"), (_variant_t) (theApp.m_Options.m_MonthDrawTimeIcons ? true : false),
		_T("Show time as clocks"), idMonthDrawTimeIcons));
	pGroup4->AddSubItem (new CBCGPProp (_T("Compress weekend"), (_variant_t) (theApp.m_Options.m_MonthCompressWeekend ? true : false),
		_T("Compress weekend days"), idMonthCompressWeekend));
	m_wndPropList.AddProperty (pGroup4);

	CBCGPProp* pGroup5 = new CBCGPProp (_T("Calendar"));
	pGroup5->AddSubItem (new CBCGPProp (_T("Week numbers"), (_variant_t) (theApp.m_Options.m_CalendarWeekNumbers ? true : false),
		_T("Show week numbers"), idCalendarWeekNumbers));
	pGroup5->AddSubItem (new CBCGPProp (_T("Gradient fill"), (_variant_t) (theApp.m_Options.m_CalendarGradientFill ? true : false),
		_T("Enable gradient fill"), idCalendarGradientFill));
	m_wndPropList.AddProperty (pGroup5);

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

	CCalendarOptions& opt = theApp.m_Options;

	switch ((int) pProp->GetData ())
	{
	case idType:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());

			for (int i = 0; i < sizeof (s_TypeNames) / sizeof (LPCTSTR); i++)
			{
				if (str == s_TypeNames [i])
				{
					opt.m_Type = (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE) (i);
					break;
				}
			}
		}
		break;
	case idBackground:
		{
			COLORREF color = (COLORREF) (long) pProp->GetValue ();
			opt.m_clrBackground = color;
		}
		break;
	case idFirstDayOfWeek:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());

			for (int i = 0; i < 8; i++)
			{
				if (str == s_FirstDayNames [i])
				{
					opt.m_WorkFirstDayOfWeek = i - 1;
					break;
				}
			}
		}
		break;
	case idImages:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());

			BOOL bDefault = str == lpszDefault;
			if (bDefault != opt.m_DefaultImages)
			{
				opt.m_DefaultImages  = bDefault;
				opt.m_bImagesChanged = TRUE;
			}
		}
		break;
	case idClockIcons:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());

			BOOL bDefault = str == lpszDefault;
			if (bDefault != opt.m_DefaultClockIcons)
			{
				opt.m_DefaultClockIcons  = bDefault;
				opt.m_bClockIconsChanged = TRUE;
			}
		}
		break;
	case idShowToolTip:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());
			opt.m_ShowToolTip = 
				str == lpszNo ? 0 : str == lpszDefault ? 1 : 2;
		}
		break;

	case idDayTimeDelta:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());

			for (int i = 0; i < sizeof (s_TimeDeltaNames) / sizeof (LPCTSTR); i++)
			{
				if (str == s_TimeDeltaNames [i])
				{
					opt.m_DayTimeDelta = (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA) (i);
					break;
				}
			}
		}
		break;
	case idDayWorkingHourFirst:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());
			int nValue = 0;

			for (int i = 0; i < 48; i++)
			{
				if (str == s_TimeIntervalNames [i])
				{
					nValue = i;
					break;
				}
			}

			double dValue = (int)(nValue / 2) + (nValue % 2 == 0 ? 0.0 : 0.30);

			if (dValue < opt.m_WorkHourLast)
			{
				opt.m_WorkHourFirst = dValue;
			}
			else
			{
				pProp->SetValue 
					(
						(LPCTSTR) s_TimeIntervalNames
							[(int)(theApp.m_Options.m_WorkHourFirst) * 2 + 
							 (int)((theApp.m_Options.m_WorkHourFirst - (int)(theApp.m_Options.m_WorkHourFirst)) * 100.0) > 0 ? 1 : 0]
					);

				return -1;
			}
		}
		break;
	case idDayWorkingHourLast:
		{
			CString str ((LPCTSTR) (_bstr_t) pProp->GetValue ());
			int nValue = 0;

			for (int i = 0; i < 48; i++)
			{
				if (str == s_TimeIntervalNames [i])
				{
					nValue = i;
					break;
				}
			}

			double dValue = (int)(nValue / 2) + (nValue % 2 == 0 ? 0.0 : 0.30);

			if (dValue > opt.m_WorkHourFirst)
			{
				opt.m_WorkHourLast = dValue;
			}
			else
			{
				pProp->SetValue 
					(
						(LPCTSTR) s_TimeIntervalNames
							[(int)(theApp.m_Options.m_WorkHourLast) * 2 + 
							 (int)((theApp.m_Options.m_WorkHourLast - (int)(theApp.m_Options.m_WorkHourLast)) * 100.0) > 0 ? 1 : 0]
					);

				return -1;
			}
		}
		break;
	case idWeekDrawTimeFinish:
		opt.m_WeekDrawTimeFinish = (BOOL) (bool) pProp->GetValue ();
		break;
	case idWeekDrawTimeIcons:
		opt.m_WeekDrawTimeIcons = (BOOL) (bool) pProp->GetValue ();
		break;
	case idMonthDrawTimeFinish:
		opt.m_MonthDrawTimeFinish = (BOOL) (bool) pProp->GetValue ();
		break;
	case idMonthDrawTimeIcons:
		opt.m_MonthDrawTimeIcons = (BOOL) (bool) pProp->GetValue ();
		break;
	case idMonthCompressWeekend:
		opt.m_MonthCompressWeekend = (BOOL) (bool) pProp->GetValue ();
		break;

	case idCalendarGradientFill:
		opt.m_CalendarGradientFill = (BOOL) (bool) pProp->GetValue ();
		break;

	case idCalendarWeekNumbers:
		opt.m_CalendarWeekNumbers = (BOOL) (bool) pProp->GetValue ();
		break;
	case idUseDayInsteadWeek:
		opt.m_UseDayInsteadWeek = (BOOL) (bool) pProp->GetValue ();
		break;
	}

	theApp.UpdateCalendar ();
	return 0;
}

void CPropertyBar::Update ()
{
	CCalendarOptions& opt = theApp.m_Options;

	CBCGPProp* pProp = m_wndPropList.GetProperty (0);
	pProp->SetValue (s_TypeNames [(int) opt.m_Type]);

	pProp = m_wndPropList.GetProperty (1);
	pProp->SetValue ((long) opt.m_clrBackground);

	pProp = m_wndPropList.GetProperty (2);
	pProp->SetValue (opt.m_DefaultImages ? lpszDefault : lpszCustom);

	pProp = m_wndPropList.GetProperty (3);
	pProp->SetValue (opt.m_DefaultClockIcons ? lpszDefault : lpszCustom);

	pProp = m_wndPropList.GetProperty (4);
	pProp->SetValue (opt.m_ShowToolTip == 0 ? lpszNo : 
		opt.m_ShowToolTip == 1 ? lpszDefault : lpszCustom);

	pProp = m_wndPropList.GetProperty (5);
	pProp->SetValue (opt.m_UseDayInsteadWeek ? true : false);

	pProp = m_wndPropList.GetProperty (6)->GetSubItem (2);
	pProp->SetValue (s_TimeDeltaNames [(int) opt.m_DayTimeDelta]);

	pProp = m_wndPropList.GetProperty (7)->GetSubItem (0);
	pProp->SetValue (opt.m_WeekDrawTimeFinish ? true : false);
	pProp = m_wndPropList.GetProperty (7)->GetSubItem (1);
	pProp->SetValue (opt.m_WeekDrawTimeIcons ? true : false);

	pProp = m_wndPropList.GetProperty (8)->GetSubItem (0);
	pProp->SetValue (opt.m_MonthDrawTimeFinish ? true : false);
	pProp = m_wndPropList.GetProperty (8)->GetSubItem (1);
	pProp->SetValue (opt.m_MonthDrawTimeIcons ? true : false);
	pProp = m_wndPropList.GetProperty (8)->GetSubItem (2);
	pProp->SetValue (opt.m_MonthCompressWeekend ? true : false);
}

void CPropertyBar::InitializeColors (BOOL bDark)
{
	if (m_wndPropList.GetPropertyCount () == 0)
	{
		return;
	}

	CColorListProp* pProp = (CColorListProp*)m_wndPropList.GetProperty (1);

	if (pProp->IsDark () != bDark)
	{
		CCalendarOptions& opt = theApp.m_Options;

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

			theApp.UpdateCalendar ();
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

BEGIN_MESSAGE_MAP(CColorPropComboBox, CBCGPComboBox)
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

