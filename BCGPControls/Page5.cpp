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
// Page5.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpcontrols.h"
#include "CustomProperties.h"
#include "Page5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage5 property page

IMPLEMENT_DYNCREATE(CPage5, CBCGPPropertyPage)

CPage5::CPage5() : CBCGPPropertyPage(CPage5::IDD)
{
	//{{AFX_DATA_INIT(CPage5)
	m_bDescrArea = TRUE;
	m_bDotNetLook = TRUE;
	m_bHeader = TRUE;
	m_bMarkSortedColumn = TRUE;
	m_bColor = TRUE;
	m_bModifyFont = TRUE;
	m_bPropListCustomColors = FALSE;
	m_bPropListCategorized = TRUE;
	m_bShowDragContext = TRUE;
	m_bMarkChanged = TRUE;
	m_bHideFontProps = FALSE;
	//}}AFX_DATA_INIT

	m_wndList.m_bColor = TRUE;
	m_wndList.m_bModifyFont = TRUE;

	pGroupFont = NULL;
}

CPage5::~CPage5()
{
}

void CPage5::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage5)
	DDX_Control(pDX, IDC_PROPLIST_EXPAND_ALL, m_btnExpandAll);
	DDX_Control(pDX, IDC_PROPLIST_LOCATION, m_wndPropListLocation);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
	DDX_Check(pDX, IDC_DESCRIPTION_AREA, m_bDescrArea);
	DDX_Check(pDX, IDC_DOT_NET_LOOK, m_bDotNetLook);
	DDX_Check(pDX, IDC_HEADER, m_bHeader);
	DDX_Check(pDX, IDC_MARK_SORTED_COLUMN, m_bMarkSortedColumn);
	DDX_Check(pDX, IDC_COLOR_ROWS, m_bColor);
	DDX_Check(pDX, IDC_MODIFY_FONT, m_bModifyFont);
	DDX_Check(pDX, IDC_CUSTOM_COLORS, m_bPropListCustomColors);
	DDX_Check(pDX, IDC_PROPLIST_CATEGORIZED, m_bPropListCategorized);
	DDX_Check(pDX, IDC_PROPLIST_CATEGORIZED2, m_bShowDragContext);
	DDX_Check(pDX, IDC_MARK_CHANGED, m_bMarkChanged);
	DDX_Check(pDX, IDC_HIDE_FONT_PROPS, m_bHideFontProps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage5, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(CPage5)
	ON_BN_CLICKED(IDC_HEADER, OnHeader)
	ON_BN_CLICKED(IDC_DOT_NET_LOOK, OnDotNetLook)
	ON_BN_CLICKED(IDC_DESCRIPTION_AREA, OnDescriptionArea)
	ON_BN_CLICKED(IDC_MARK_SORTED_COLUMN, OnMarkSortedColumn)
	ON_BN_CLICKED(IDC_COLOR_ROWS, OnColorRows)
	ON_BN_CLICKED(IDC_MODIFY_FONT, OnModifyFont)
	ON_BN_CLICKED(IDC_CUSTOM_COLORS, OnPropListCustomColors)
	ON_BN_CLICKED(IDC_PROPLIST_EXPAND_ALL, OnProplistExpandAll)
	ON_BN_CLICKED(IDC_PROPLIST_CATEGORIZED, OnProplistCategorized)
	ON_BN_CLICKED(IDC_PROPLIST_CATEGORIZED2, OnProplistCategorized2)
	ON_BN_CLICKED(IDC_RESET_VALUES, OnResetValues)
	ON_BN_CLICKED(IDC_MARK_CHANGED, OnMarkChanged)
	ON_BN_CLICKED(IDC_HIDE_FONT_PROPS, OnHideFontProps)
	ON_BN_CLICKED(IDC_COMMIT_CHANGES, OnCommitChanges)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage5 message handlers

const int nColumns = 4;
const int nRows = 50;

BOOL CPage5::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();
	
	m_wndList.InsertColumn (0, _T("#"), LVCFMT_LEFT, 20);

	int nColumn;
	for (nColumn = 1; nColumn < nColumns - 1; nColumn++)
	{
		m_wndList.InsertColumn (nColumn, CString ((TCHAR)(_T('A') + nColumn - 1)), LVCFMT_LEFT, 70);
	}

	for (int i = 0; i < nRows; i++)
	{
		CString str;
		str.Format (_T("%d"), i);
		m_wndList.InsertItem (i, str);
		m_wndList.SetItemData (i, i);

		for (nColumn = 1; nColumn < nColumns - 1; nColumn++)
		{
			str.Format (_T("Item (%d, %d)"), nColumn - 1, i);
			m_wndList.SetItemText (i, nColumn, str);
		}
	}
	
	m_wndList.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
						LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndList.EnableMarkSortedColumn ();


	CRect rectPropList;
	m_wndPropListLocation.GetClientRect (&rectPropList);
	m_wndPropListLocation.MapWindowPoints (this, &rectPropList);

	m_wndPropList.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this, (UINT)-1);
	
	m_wndPropList.EnableHeaderCtrl ();
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook (m_bDotNetLook);
	m_wndPropList.MarkModifiedProperties (m_bMarkChanged);

	m_wndPropList.SetAlphabeticMode (!m_bPropListCategorized);
	m_wndPropList.SetShowDragContext (m_bShowDragContext);

	CBCGPProp* pGroup1 = new CBCGPProp (_T("Appearance"));

	pGroup1->AddSubItem (new CBCGPProp (_T("3D Look"), (_variant_t) false,
		_T("Specifies the dialog's font will be nonbold and controls will have a 3D border")));

	CBCGPProp* pProp = new CBCGPProp (_T("Border"), _T("Dialog Frame"),
		_T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption (_T("None"));
	pProp->AddOption (_T("Thin"));
	pProp->AddOption (_T("Resizable"));
	pProp->AddOption (_T("Dialog Frame"));
	pProp->AllowEdit (FALSE);

	pGroup1->AddSubItem (pProp);
	pGroup1->AddSubItem (new CBCGPProp (_T("Caption"), (_variant_t) _T("About BCGProTest"),
		_T("Specifies the text that will be displayed in the dialog's title bar")));

	m_wndPropList.AddProperty (pGroup1);

	CBCGPProp* pSize = new CBCGPProp (_T("Window Size"), 0, TRUE);

	pProp = new CBCGPProp (_T("Height"), (_variant_t) 250l,
							_T("Specifies the dialog's height"));
	pProp->EnableSpinControl (TRUE, 0, 1000);
	pSize->AddSubItem (pProp);

	pProp = new CBCGPProp (	_T("Width"), (_variant_t) 150l,
							_T("Specifies the dialog's width"));
	pProp->EnableSpinControl ();
	pSize->AddSubItem (pProp);

	m_wndPropList.AddProperty (pSize);

	pGroupFont = new CBCGPProp (_T("Font"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle ((HFONT) GetStockObject (DEFAULT_GUI_FONT));
	font->GetLogFont (&lf);
	lstrcpy (lf.lfFaceName, _T("Arial"));

	pGroupFont->AddSubItem (new CBCGPFontProp (_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the dialog")));
	pGroupFont->AddSubItem (new CBCGPProp (_T("Use System Font"), (_variant_t) true, _T("Specifies that the dialog uses MS Shell Dlg font")));

	m_wndPropList.AddProperty (pGroupFont);

	CBCGPProp* pGroup3 = new CBCGPProp (_T("Misc"));
	pProp = new CBCGPProp (_T("(Name)"), _T("IDD_ABOUT_BOX (dialog)"));
	pProp->Enable (FALSE);
	pGroup3->AddSubItem (pProp);

	CBCGPColorProp* pColorProp = new CBCGPColorProp (_T("Window Color"), RGB (210, 192, 254), NULL, _T("Specifies the default dialog color"));
	pColorProp->EnableOtherButton (_T("Other..."));
	pColorProp->EnableAutomaticButton (_T("Default"), ::GetSysColor (COLOR_3DFACE));
	pGroup3->AddSubItem (pColorProp);

	static TCHAR BASED_CODE szFilter[] = _T("Icon Files (*.ico)|*.ico|All Files (*.*)|*.*||");
	pGroup3->AddSubItem (new CBCGPFileProp (_T("Icon"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the dialog icon")));

	pGroup3->AddSubItem (new CBCGPFileProp (_T("Folder"), _T("c:\\")));

	COleDateTime date = COleDateTime::GetCurrentTime ();
	pGroup3->AddSubItem (new CBCGPDateTimeProp (_T("Date"), date,
		_T("Set a date"), 0, CBCGPDateTimeCtrl::DTM_DATE));

	pGroup3->AddSubItem (new CBCGPDateTimeProp (_T("Time"), date,
		_T("Set a time"), 0, CBCGPDateTimeCtrl::DTM_TIME));

	pGroup3->AddSubItem (new CBCGPProp (_T("Phone"), _T("(123) 123-12-12"),
		_T("Enter a phone number"), 0, _T(" ddd  ddd dd dd"),
		_T("(___) ___-__-__")));

	m_wndPropList.AddProperty (pGroup3);

	CBCGPProp* pGroup4 = new CBCGPProp (_T("Hierarchy"));

	CBCGPProp* pGroup41 = new CBCGPProp (_T("First sub-level"));
	pGroup4->AddSubItem (pGroup41);

	CBCGPProp* pGroup411 = new CBCGPProp (_T("Second sub-level"));
	pGroup41->AddSubItem (pGroup411);

	pGroup411->AddSubItem (new CBCGPProp (_T("Item 1"), (_variant_t) _T("Value 1"),
		_T("This is a description")));
	pGroup411->AddSubItem (new CBCGPProp (_T("Item 2"), (_variant_t) _T("Value 2"),
		_T("This is a description")));
	pGroup411->AddSubItem (new CBCGPProp (_T("Item 3"), (_variant_t) _T("Value 3"),
		_T("This is a description")));

	pGroup4->Expand (FALSE);
	m_wndPropList.AddProperty (pGroup4);

	// Add custom properties:
	CBCGPProp* pGroup5 = new CBCGPProp (_T("Custom Properties"));

	pGroup5->AddSubItem (new CDurationProp (_T("Duration"), 
		COleDateTimeSpan (1, 2, 3, 0),
		_T("Set a duration")));

	pGroup5->AddSubItem (new CCheckBoxProp (_T("Check Box"), TRUE, _T("Check Box Property")));

	pGroup5->AddSubItem (new CPasswordProp (_T("Password"), _T("123456"), _T("Password Property")));

	pGroup5->AddSubItem (new CSliderProp (_T("Slider"), 0, _T("Slider Property")));

	CBitmap bmp;
	bmp.LoadBitmap (IDB_PROPICONS);

	m_imageList.Create (16, 16, ILC_MASK | ILC_COLOR24, 0, 0);
	m_imageList.Add (&bmp, RGB (192, 192, 192));

	CStringList lstIconNames;
	lstIconNames.AddTail (_T("Icon 1"));
	lstIconNames.AddTail (_T("Icon 2"));
	lstIconNames.AddTail (_T("Icon 3"));
	lstIconNames.AddTail (_T("Icon 4"));
	lstIconNames.AddTail (_T("Icon 5"));
	lstIconNames.AddTail (_T("Icon 6"));
	lstIconNames.AddTail (_T("Icon 7"));
	lstIconNames.AddTail (_T("Icon 8"));
	lstIconNames.AddTail (_T("Icon 9"));
	lstIconNames.AddTail (_T("Icon 10"));
	lstIconNames.AddTail (_T("Icon 11"));

	pGroup5->AddSubItem (new CIconListProp (_T("Icon List"), m_imageList, 0, &lstIconNames,
		_T("Icon List Property")));

	CComboBoxExProp* pComboEx = new CComboBoxExProp (_T("ComboBoxEx"), _T("Test"),
		_T("ComboBoxEx Property"), 0, &m_imageList);
	pComboEx->AddOption (_T("New"), 0, 0);
	pComboEx->AddOption (_T("Open"), 1, 1);
	pComboEx->AddOption (_T("Save"), 2, 0);

	pGroup5->AddSubItem (pComboEx);

	pGroup5->AddSubItem (new COwnerDrawDescrProp (_T("Owner-draw descr."), 0l));
	pGroup5->AddSubItem (new CTwoButtonsProp (_T("2 Buttons"), _T("text")));
	pGroup5->AddSubItem (new CCustomDlgProp (_T("Custom Dialog"), _T("value")));

	m_wndPropList.AddProperty (pGroup5);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage5::OnHeader() 
{
	UpdateData ();
	m_wndPropList.EnableHeaderCtrl (m_bHeader);
}

void CPage5::OnDotNetLook() 
{
	UpdateData ();
	m_wndPropList.SetVSDotNetLook (m_bDotNetLook);
}

void CPage5::OnDescriptionArea() 
{
	UpdateData ();
	m_wndPropList.EnableDesciptionArea (m_bDescrArea);
}

void CPage5::OnMarkSortedColumn() 
{
	UpdateData ();
	m_wndList.EnableMarkSortedColumn (m_bMarkSortedColumn);
}

COLORREF CMyListCtrl::OnGetCellTextColor (int nRow, int nColum)
{
	if (!m_bColor)
	{
		return CBCGPListCtrl::OnGetCellTextColor (nRow, nColum);
	}

	return (nRow % 2) == 0 ? RGB (128, 37, 0) : RGB (0, 0, 0);
}

COLORREF CMyListCtrl::OnGetCellBkColor (int nRow, int nColum)
{
	if (!m_bColor)
	{
		return CBCGPListCtrl::OnGetCellBkColor (nRow, nColum);
	}

	if (m_bMarkSortedColumn && nColum == m_iSortedColumn)
	{
		return (nRow % 2) == 0 ? RGB (233, 221, 229) : RGB (176, 218, 234);
	}

	return (nRow % 2) == 0 ? RGB (253, 241, 249) : RGB (196, 238, 254);
}

HFONT CMyListCtrl::OnGetCellFont (int nRow, int nColum, DWORD /*dwData = 0*/)
{
	if (!m_bModifyFont)
	{
		return NULL;
	}

	if (nColum == 2 && (nRow >= 4 && nRow <= 8))
	{
		return globalData.fontDefaultGUIBold;
	}

	return NULL;
}

void CPage5::OnColorRows() 
{
	UpdateData ();
	m_wndList.m_bColor = m_bColor;
	m_wndList.RedrawWindow ();
}

void CPage5::OnModifyFont() 
{
	UpdateData ();
	m_wndList.m_bModifyFont = m_bModifyFont;
	m_wndList.RedrawWindow ();
}

void CPage5::OnPropListCustomColors() 
{
	UpdateData ();

	if (m_bPropListCustomColors)
	{
		m_wndPropList.SetCustomColors (
			RGB (228, 243, 254),
			RGB (46, 70, 165),
			RGB (200, 236, 209),
			RGB (33, 102, 49),
			RGB (255, 229, 216),
			RGB (128, 0, 0),
			RGB (159, 159, 255));
	}
	else
	{
		m_wndPropList.SetCustomColors (	(COLORREF)-1, (COLORREF)-1, (COLORREF)-1, 
										(COLORREF)-1, (COLORREF)-1, (COLORREF)-1, (COLORREF)-1);
	}

	m_wndPropList.RedrawWindow ();
}

void CPage5::OnProplistExpandAll() 
{
	static BOOL bExpanded = FALSE;

	m_wndPropList.ExpandAll (!bExpanded);
	
	m_btnExpandAll.SetWindowText (bExpanded ?
		_T("Expand &All") : _T("Collapse &All"));

	bExpanded = !bExpanded;
}

void CPage5::OnProplistCategorized() 
{
	UpdateData ();

	m_wndPropList.SetAlphabeticMode (!m_bPropListCategorized);
	m_btnExpandAll.EnableWindow (m_bPropListCategorized);
}

void CPage5::OnProplistCategorized2() 
{
	UpdateData ();
	m_wndPropList.SetShowDragContext (m_bShowDragContext);
}

void CPage5::OnResetValues() 
{
	m_wndPropList.ResetOriginalValues ();
}

void CPage5::OnMarkChanged() 
{
	UpdateData ();
	m_wndPropList.MarkModifiedProperties (m_bMarkChanged);
}

void CPage5::OnHideFontProps() 
{
	UpdateData ();

	ASSERT_VALID (pGroupFont);
	pGroupFont->Show (!m_bHideFontProps);
}

void CPage5::OnCommitChanges() 
{
	m_wndPropList.CommitModifiedValues ();
}
