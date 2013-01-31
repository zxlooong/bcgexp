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
// ReportGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPGridExample.h"
#include "ReportGridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportGridCtrl

CReportGridCtrl::CReportGridCtrl()
{
}

CReportGridCtrl::~CReportGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CReportGridCtrl, CBCGPReportCtrl)
	//{{AFX_MSG_MAP(CReportGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReportGridCtrl message handlers

inline int Rand (int nMax)
{
	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

int CReportGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPReportCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	//------------------
	// Load grid images:
	//------------------
	CBitmap bmp;
	bmp.LoadBitmap (IDB_LIST_IMAGES);

	m_Images.Create (16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
	m_Images.Add (&bmp, RGB (255, 0, 255));

	SetImageList (&m_Images);

	//------------------------------
	// Load images for "flag" items:
	//------------------------------
	m_Flags.SetImageSize (CSize (14, 14));
	m_Flags.SetTransparentColor (RGB (255, 0, 255));
	m_Flags.Load (IDB_FLAGS256);

	//----------------
	// Insert columns:
	//----------------
	InsertColumn (0, _T("Importance"), 20, 1);
	InsertColumn (1, _T("Icon"), 20, 0);
	InsertColumn (2, _T("Attachment"), 20, 2);
	InsertColumn (3, _T("From"), 150);
	InsertColumn (4, _T("Subject"), 150);
	InsertColumn (5, _T("To"), 140);
	InsertColumn (6, _T("CC"), 120);
	InsertColumn (7, _T("Created"), 130);
	InsertColumn (8, _T("Received"), 130);
	InsertColumn (9, _T("Size"), 80);
	InsertColumn (10, _T("Categories"), 80);
	InsertColumn (11, _T("Flag Status"), 20, 3);

	SetColumnAlign (1, HDF_RIGHT);	// Icon
	SetColumnAlign (9, HDF_RIGHT);	// Size

	SetColumnLocked (0);
	SetColumnLocked (2);
	SetColumnLocked (11);

	SetColumnVisible (4, FALSE);
	SetColumnVisible (5, FALSE);
	SetColumnVisible (6, FALSE);
	SetColumnVisible (8, FALSE);
	SetColumnVisible (10, FALSE);

	SetTextColumn (0, FALSE);
	SetTextColumn (1, FALSE);
	SetTextColumn (2, FALSE);
	SetTextColumn (11, FALSE);

	//-------------------
	// Set group columns:
	//-------------------
	InsertGroupColumn (0, 8 /* Received */);
	InsertGroupColumn (1, 4 /* Subject */);

	//--------------------------
	// Create header image list:
	//--------------------------
	const int nImageWidth = 12;
	m_ImagesHeader.Create (IDB_HEADER_IMAGES, nImageWidth, 0, RGB (255, 0, 255));

	SetHeaderImageList (&m_ImagesHeader);

	EnableHeader ();
	EnableColumnAutoSize (TRUE);

	SetWholeRowSel (TRUE);
	SetSingleSel (TRUE);
	EnableMarkSortedColumn (TRUE);
	EnableGroupByBox (TRUE);

	EnablePreviewRow (TRUE, FALSE);
	SetPreviewRowAutoLeftMargin ();

	//---------------
	// Add demo data:
	//---------------
	#define NAMES_NUM	7
	LPCTSTR arNames [NAMES_NUM] =
	{
		_T("John Smith"),
		_T("Support Team"),
		_T("Peter Brown"),
		_T("Matt Johnson"),
		_T("James Lee"),
		_T("Customer Service"),
		_T("Webmaster"),
	};

	#define SUBJ_NUM	8
	LPCTSTR arSubjs [SUBJ_NUM] =
	{
		_T("Important information"),
		_T("Customer Newsletter"),
		_T("Question"),
		_T("Business proposal"),
		_T("Request more info about your products"),
		_T("Thank you!"),
		_T("Your application has been approved"),
		_T("Please read this message"),
	};

	#define DESCR_NUM	3
	LPCTSTR arDescrs [DESCR_NUM] =
	{
		_T("We have been trying to contact you since friday about your records - please confirm some details below"),
		_T("Hi, how are you? Hope, everthing is going well. I'm sending now the required price list. If you've any additional questions regarding our products, please don't hesitate to contact us."),
		_T("Standard Disclaimer: This message is confidential. You should not copy it or disclose its contents to anyone. You may use and apply the information only for the intended purpose. If this email has come to you in error please delete it and any attachments."),
	};

	srand( (unsigned)time( NULL ) );

	for (int i = 0; i < 100; i++)
	{
		COleDateTime now = COleDateTime::GetCurrentTime ();
		COleDateTimeSpan span (
			Rand (5),
			Rand (23),
			Rand (59),
			0);
		COleDateTimeSpan span2 (
			0,
			Rand (2),
			Rand (59),
			Rand (59));
	AddMail (Rand (2), // Icon
			arNames [Rand (NAMES_NUM)],
			arNames [Rand (NAMES_NUM)],
			arSubjs [Rand (SUBJ_NUM)],
			now - span - span2,
			now - span, 
			Rand (200),
			(IMPORTANCE)Rand (3),
			Rand (2), 
			Rand (7),
			arDescrs [Rand (DESCR_NUM)]);
	}

	LoadState (_T("ReportGrid"));
	AdjustLayout ();

	return 0;
}

void CReportGridCtrl::OnDestroy() 
{
	SaveState (_T("ReportGrid"));
	CBCGPReportCtrl::OnDestroy();
}

BOOL CReportGridCtrl::AddMail (int nIcon, LPCTSTR strFrom, LPCTSTR strTo,
		 LPCTSTR strSubject, COleDateTime dateCreated, COleDateTime dateReceived, long lSize, 
		 IMPORTANCE importance/* = IMPORTANCE_NORMAL*/,
		 BOOL bHasAttachment/* = FALSE*/,
		 int nFlag/* = 0*/,
		 LPCTSTR lpcstrDescr/* = NULL*/)
{
	CBCGPGridRow* pRow = CreateRow (GetColumnCount ());

	//----------------
	// Set importance:
	//----------------
	int nImportanceIcon = -1;
	switch (importance)
	{
	case IMPORTANCE_HIGH:
		nImportanceIcon = 2;
		break;

	case IMPORTANCE_LOW:
		nImportanceIcon = 3;
		break;
	}

	pRow->GetItem (0)->SetImage (nImportanceIcon);
	pRow->GetItem (1)->SetImage (nIcon);
	pRow->GetItem (2)->SetImage (bHasAttachment ? 5 : -1);

	pRow->GetItem (3)->SetValue (strFrom);
	pRow->GetItem (4)->SetValue (strSubject);
	pRow->GetItem (5)->SetValue (strTo);

	pRow->ReplaceItem (7, new CBCGPGridDateTimeItem (dateCreated));
	pRow->ReplaceItem (8, new CBCGPGridDateTimeItem (dateReceived));

	pRow->GetItem (9)->SetValue (lSize);

	pRow->ReplaceItem (11, new CFlagItem (m_Flags, nFlag));

	if (lpcstrDescr != NULL)
	{
		CBCGPReportRow* pReportRow = DYNAMIC_DOWNCAST (CBCGPReportRow, pRow);
		if (pReportRow != NULL)
		{
			CString str = lpcstrDescr;
			pReportRow->SetDescription (str);
		}
	}

	AddRow (pRow, FALSE);

	return TRUE;
}

BOOL DoCompare (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	switch (iColumn)
	{
	case 7:	// Created
	case 8:	// Received
		{
			COleDateTime date1 = (DATE) pRow1->GetItem (iColumn)->GetValue ();
			COleDateTime date2 = (DATE) pRow2->GetItem (iColumn)->GetValue ();

			return date1.GetYear () == date2.GetYear () &&
				date1.GetMonth () == date2.GetMonth () &&
				date1.GetDay () == date2.GetDay ();
		}
	}

	return FALSE;
}

int CReportGridCtrl::CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pRow1);
	ASSERT_VALID (pRow2);

	if (DoCompare (pRow1, pRow2, iColumn))
	{
		return 0;
	}

	return CBCGPReportCtrl::CompareGroup (pRow1, pRow2, iColumn);
}

CString CReportGridCtrl::GetGroupName (int iColumn, CBCGPGridItem* pItem)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pItem);

	if (iColumn == 7 ||	// Created
		iColumn == 8)	// Received
	{
		COleDateTime date = (DATE) pItem->GetValue ();

		CString strGroup;
		strGroup.Format (_T("%s: %s"), 
			m_Columns.GetColumnName (iColumn),
			date.Format (VAR_DATEVALUEONLY));

		return strGroup;
	}

	return CBCGPReportCtrl::GetGroupName (iColumn, pItem);
}

/////////////////////////////////////////////////////////////////////////////
// CFlagItem class

CFlagItem::CFlagItem(
	CBCGPToolBarImages&	icons,
	int nSelectedIcon) :
	m_Icons (icons)
{
	m_varValue = (long) nSelectedIcon;
	AllowEdit (FALSE);
}

BOOL CFlagItem::OnClickValue (UINT uiMsg, CPoint point)
{
	if (CBCGPGridItem::OnClickValue (uiMsg, point))
	{
		return TRUE;
	}

	if (uiMsg == WM_LBUTTONDOWN)
	{
		int nIndex = (long) m_varValue;

		if (nIndex < 0)
		{
			return FALSE;
		}

		if (nIndex > m_Icons.GetCount ())
		{
			return FALSE;
		}

		// shift nIndex
		nIndex++;
		nIndex %= m_Icons.GetCount ();

		m_varValue = (long) nIndex;

		CBCGPGridItemID id = GetGridItemID ();
		m_pGridRow->OnItemChanged (this, id.m_nRow, id.m_nColumn);
		Redraw ();

		return TRUE;
	}

	return FALSE;
}

void CFlagItem::OnDrawValue (CDC* pDC, CRect rect)
{
	int nIndex = (long) m_varValue;

	// fill background
	CRect rectFill = rect;
	rectFill.top++;
	rectFill.right++;
	pDC->FillRect (rectFill, &globalData.brLight);

	if (nIndex < 0)
	{
		return;
	}

	if (nIndex > m_Icons.GetCount ())
	{
		return;
	}

	IMAGEINFO imageInfo;
	memset (&imageInfo, 0, sizeof (IMAGEINFO));

	CPoint pt = rect.TopLeft ();
	CSize sizeIcon = m_Icons.GetImageSize ();

	int xOffset = (rect.Width () - sizeIcon.cx) / 2;
	int yOffset = (rect.Height () - sizeIcon.cy) / 2;
	pt.Offset (max (0, xOffset), max (0, yOffset));

	CBCGPDrawState ds;
	m_Icons.PrepareDrawImage (ds);
	m_Icons.Draw (pDC, pt.x, pt.y, nIndex);
	m_Icons.EndDrawImage (ds);
}

