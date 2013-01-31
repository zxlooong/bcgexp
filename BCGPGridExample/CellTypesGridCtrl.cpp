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
// CellTypesGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPGridExample.h"
#include "CellTypesGridCtrl.h"
#include "CustomCells.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define idProgressAnim	100

inline int Rand (int nMax)
{
	if (nMax <= 0)
	{
		return 0;
	}

	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

#define COLORS_NUM	7

LPCTSTR colors [COLORS_NUM] =
{
	_T("Red"),
	_T("Orange"),
	_T("Yellow"),
	_T("Green"),
	_T("Blue"),
	_T("Indigo"),
	_T("Violet"),
};

/////////////////////////////////////////////////////////////////////////////
// CCellTypesGridCtrl

CCellTypesGridCtrl::CCellTypesGridCtrl()
{
	m_pProgressItem = NULL;
	m_bProgressIsOn = FALSE;
}

CCellTypesGridCtrl::~CCellTypesGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CCellTypesGridCtrl, CBCGPGridCtrl)
	//{{AFX_MSG_MAP(CCellTypesGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_ANIMATE, OnAnimateProgress)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCellTypesGridCtrl message handlers

int CCellTypesGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	srand ((unsigned) time (NULL));

	SetWholeRowSel (FALSE);
	EnableMarkSortedColumn (FALSE);
	EnableHeader (TRUE, 0);

	InsertColumn (0, _T("A"), 30);
	InsertColumn (1, _T("B"), 80);
	InsertColumn (2, _T("C"), 120);
	InsertColumn (3, _T("D"), 50);
	InsertColumn (4, _T("E"), 80);
	InsertColumn (5, _T("F"), 120);

	AddEmptyRow();

	CBCGPGridRow* pRow = CreateNewRow ();
	ASSERT_VALID (pRow);

	//-------------
	// Simple text:
	//-------------
	pRow->GetItem (1)->SetValue (_T("Text:"));
	pRow->ReplaceItem (2, new CBCGPGridItem (_T("Hello, world!")));

	//-------------
	// Masked text:
	//-------------
	pRow->GetItem (4)->SetValue (_T("Masked Edit:"));
	pRow->ReplaceItem (5, new CBCGPGridItem (_T("(123) 123-12-12"),
		0, _T(" ddd  ddd dd dd"),
		_T("(___) ___-__-__")));
		
	AddRow (pRow, FALSE);

	AddEmptyRow ();
	pRow = CreateNewRow ();

	//----------
	// Password:
	//----------
	pRow->GetItem (1)->SetValue (_T("Password"));
	pRow->ReplaceItem (2, new CPasswordItem("mypassword"));

	//-----
	// URL:
	//-----
	pRow->GetItem (4)->SetValue (_T("URL:"));
	CBCGPGridItem* pURLItem =
		new CBCGPGridURLItem(_T("www.bcgsoft.com"), _T("http://www.bcgsoft.com"));
	pRow->ReplaceItem (5, pURLItem);
	AddRow (pRow, FALSE);

	AddEmptyRow();
	pRow = CreateNewRow ();

	//--------
	// Number:
	//--------
	pRow->GetItem (1)->SetValue (_T("Number:"));
	pRow->ReplaceItem (2, new CBCGPGridItem ((long) Rand (100)));

	//----------------------
	// Number + spin button:
	//----------------------
	pRow->GetItem (4)->SetValue (_T("Number + spin:"));

	CBCGPGridItem* pSpinItem = new CBCGPGridItem ((long) Rand (1000)); 
	pSpinItem->EnableSpinControl(TRUE, 0, 1000);

	pRow->ReplaceItem (5, pSpinItem);
	
	AddRow (pRow, FALSE);

	AddEmptyRow();
	pRow = CreateNewRow ();

	//----------------
	// Slider control:
	//----------------
	pRow->GetItem (1)->SetValue (_T("Slider:"));
	pRow->ReplaceItem (2, new CSliderItem(Rand (100)));

	pRow->GetItem (4)->SetValue (_T("Double:"));
	pRow->ReplaceItem (5, new CBCGPGridItem (239.6));

	AddRow (pRow, FALSE);

	AddEmptyRow();
	pRow = CreateNewRow ();

	//----------
	// Combobox:
	//----------
	pRow->GetItem (1)->SetValue (_T("ComboBox:"));

	CBCGPGridItem* pItem = new CBCGPGridItem (colors [Rand (COLORS_NUM)]);

	for (int i = 0; i < COLORS_NUM; i++)
	{
		pItem->AddOption (colors [i], 1);
	}

	pRow->ReplaceItem (2, pItem);

	//----------
	// Checkbox:
	//----------
	pRow->GetItem (4)->SetValue (_T("CheckBox:"));
	pRow->ReplaceItem (5, new CBCGPGridCheckItem (TRUE));

	AddRow (pRow, FALSE);

	AddEmptyRow();
	pRow = CreateNewRow ();

	//--------------
	// Color Picker:
	//--------------
	pRow->GetItem (1)->SetValue (_T("Color Picker:"));

	CBCGPGridColorItem* pColorItem = new CBCGPGridColorItem (
			RGB (Rand (255), Rand (255), Rand (255)));
	ASSERT_VALID (pColorItem);

	pColorItem->EnableOtherButton (_T("Other"));

	pRow->ReplaceItem (2, pColorItem);
	
	//-------------
	// Font Picker:
	//-------------
	pRow->GetItem (4)->SetValue (_T("Font Picker:"));
	
	CFont* pFont = CFont::FromHandle ((HFONT) GetStockObject (DEFAULT_GUI_FONT));

	LOGFONT lf;
	pFont->GetLogFont (&lf);

	lstrcpy (lf.lfFaceName, _T("Arial"));
	lf.lfHeight = 10;

	pRow->ReplaceItem (5, new CFontItem(lf));
	
	AddRow (pRow, FALSE);

	AddEmptyRow();
	pRow = CreateNewRow ();

	//-------------------
	// Fle Browse button:
	//-------------------
	pRow->GetItem (1)->SetValue (_T("File Browse:"));

	CString strName;	
	strName.Format (_T("File_%d"), Rand (20));

	pRow->ReplaceItem (2, new CFileItem (strName));

	//-------------------
	// Path Browse button:
	//-------------------
	pRow->GetItem (4)->SetValue (_T("Folder Picker:"));
	pRow->ReplaceItem (5, new CFolderItem (_T("c:\\")));

	AddRow (pRow, FALSE);
	AddEmptyRow();

	pRow = CreateNewRow ();

	//-------------
	// Date picker:
	//-------------
	pRow->GetItem (1)->SetValue (_T("Date:"));

	pRow->ReplaceItem (2, new CBCGPGridDateTimeItem (
		COleDateTime::GetCurrentTime (), 0, CBCGPDateTimeCtrl::DTM_DATE));

	//-------------
	// Time picker:
	//-------------
	pRow->GetItem (4)->SetValue (_T("Time:"));

	pRow->ReplaceItem (5, new CBCGPGridDateTimeItem (
		COleDateTime::GetCurrentTime (), 0, CBCGPDateTimeCtrl::DTM_TIME));

	AddRow (pRow, FALSE);
	AddEmptyRow();

	pRow = CreateNewRow ();

	//--------------
	// Progress Bar:
	//--------------
	pRow->GetItem (1)->SetValue (_T("Progress Bar:"));

	m_pProgressItem = new CProgressItem (15, 100);

	pRow->ReplaceItem (2, m_pProgressItem);
	pRow->ReplaceItem (3, new CButtonItem (_T("Animate!"), IDC_ANIMATE));

	AddRow (pRow, FALSE);
	AddEmptyRow();
	
	pRow = CreateNewRow ();

	//------
	// Icon:
	//------
	pRow->GetItem (1)->SetValue (_T("Icon:"));

	CBitmap bmp;
	bmp.LoadBitmap (IDB_PROP_ICONS);

	CImageList  imageList;

	imageList.Create (16, 16, ILC_MASK | ILC_COLOR24, 0, 0);
	imageList.Add (&bmp, RGB (192, 192, 192));

	pRow->ReplaceItem (2, 
		new CIconGridItem (imageList, Rand (imageList.GetImageCount ())));

	//-----------
	// Icon List:
	//-----------
	pRow->GetItem (4)->SetValue (_T("Icon List:"));
	
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

	pRow->ReplaceItem (5, new CIconListItem (
		(long)Rand (6), imageList, &lstIconNames));
	
	AddRow (pRow, FALSE);
	AddEmptyRow ();
	
	AdjustLayout ();
	
	LoadState (_T("CellTypesGrid"));
	AdjustLayout ();

	return 0;
}

void CCellTypesGridCtrl::OnDestroy() 
{
	SaveState (_T("CellTypesGrid"));
	CBCGPGridCtrl::OnDestroy();
}

CBCGPGridRow* CCellTypesGridCtrl::CreateNewRow ()
{
	CBCGPGridRow* pRow = CreateRow (GetColumnCount ());

	for (int i = 0; i < GetColumnCount ();i++)
	{
		pRow->GetItem (i)->AllowEdit (FALSE);
	}

	return pRow;
}

void CCellTypesGridCtrl::AddEmptyRow ()
{
	AddRow (CreateNewRow (), FALSE);
}

void CCellTypesGridCtrl::OnAnimateProgress()
{
	if (m_bProgressIsOn)
	{
		KillTimer (idProgressAnim);
		m_bProgressIsOn = FALSE;
	}
	else
	{
		SetTimer (idProgressAnim, 50, NULL);
		m_bProgressIsOn = TRUE;
	}
}

void CCellTypesGridCtrl::OnTimer(UINT_PTR nIDEvent) 
{
	CBCGPGridCtrl::OnTimer(nIDEvent);

	if (nIDEvent == idProgressAnim)
	{
		ASSERT_VALID (m_pProgressItem);

		long nVal = (long) m_pProgressItem->GetValue ();

		if (nVal >= m_pProgressItem->GetTotal ())
		{
			KillTimer (idProgressAnim);
			m_pProgressItem->SetValue (15l);
			m_bProgressIsOn = FALSE;
		}
		else
		{
			m_pProgressItem->SetValue (nVal + 5l);
		}

		m_pProgressItem->Redraw ();
	}
}

void CCellTypesGridCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CItemSliderCtrl* pItemSliderCtrl = DYNAMIC_DOWNCAST
		(CItemSliderCtrl, pScrollBar);

	if (pItemSliderCtrl != NULL)
	{
		CWnd::OnHScroll (nSBCode, nPos, pScrollBar);
		pItemSliderCtrl->Redraw ();
	}
	else
	{
		CBCGPGridCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}
